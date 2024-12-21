/*
 * tasks.c
 *
 * Created: 18/8/2024 4:49:08 pm
 *  Author: Yu Heng
 */ 

#include <tasks.h>
#include <protocol.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <uart.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

/*csp lib*/
#include <csp/csp.h>
#include <csp/interfaces/csp_if_i2c.h>
#include <csp/drivers/i2c.h>
#include <csp/csp_endian.h>

/* CCSDS Packet */
#include "project/include/packet.h"

TaskHandle_t I2C_task;

// This task lights up LED at digital pin 13 (built-in)
void task_led_blinky (void *pvParameters) {
	// Create tasks
	DDRB = 0b10000000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560)
	PORTB = 0b10000000; // set 7th bit to HIGH
	
	while (1) {
		if(PORTB == 0b10000000)
		{
			PORTB = 0b00000000; // set 7th bit to LOW
			printf("LED 1 lights up\r\n\r\n");
		}
		else
		{
			PORTB = 0b10000000; // set 7th bit to HIGH
			printf("LED 1 lights up\r\n\r\n");
		}
		vTaskDelay(2000);
	}
}

apid_map apid_subsys_port_map(int apid) {
	int apid_arr[1] = {10};
	int subsys[1] = {8};
	int port[1] = {1};
		
	apid_map mapped;
		
	int index;
	
	for (int i = 0; i < sizeof(apid_arr)/sizeof(apid_arr[0]); i++) {
		if (apid_arr[i] == apid) {
			index = i;
		}
	}
	
	mapped.addr = subsys[index];
	mapped.port = port[index];
	//printf("addr: %d, port: %d\r\n", mapped.addr, mapped.port);
	return mapped;
}

void command_handler(void *pvParameters) {
	
	TC_packet tc;
	int ret;
	int apid;
	
	// for receiving from TTNC
	csp_socket_t *socket;
	socket = csp_socket(0);
	csp_listen(socket, 1);
	csp_bind(socket, PROTOCOL_SUBSYS_PING_PORT);
	
	TM_packet tm;
	TM_packet_init(&tm);
	
	while (1) {
		//printf("remaining buf: %d\r\n", csp_buffer_remaining());
		
		csp_conn_t *conn_incoming;
		csp_packet_t *packet_incoming;
		conn_incoming = csp_accept(socket, 0.2 * configTICK_RATE_HZ);		
		if (conn_incoming == NULL) {
			continue;
		}
		
		// copy mem from packet data to csp packet
		printf("Reading packets from incoming connection...\r\n");
		packet_incoming = csp_read(conn_incoming, 0);
		memcpy(&tc, packet_incoming->data, sizeof(TC_packet));
		csp_buffer_free(packet_incoming);
		csp_close(conn_incoming);
		
		#if 0 // for debugging
		for(int i = 0; i < sizeof(tc); i++)
		{
			printf("%02x,",(unsigned int) ((char*)&tc)[i]); // get the bytes for a sample telecommand (temporary)
		}
		#endif
				
		apid = tc.header.p_ID.APID;
		printf("apid: %d\r\n", apid);
		apid_map mapped = apid_subsys_port_map(apid); // use APID to find address and port
		
		// send data to relevant subsys then receive response
		uint8_t response[100];
		
		if (apid == 255) {
			printf("Boot Up Command\r\n");
		}
		else {
			int ret_subsystem_conn = csp_transaction(PROTOCOL_PRIO_NORM, mapped.addr, mapped.port, PROTOCOL_TIMEOUT_HM, &(tc.data.app_data), sizeof(tc.data.app_data), &response, sizeof(100));
			printf("Forwarding to mapped addr, port: %d, %d\r\n", mapped.addr, mapped.port);
			if(ret_subsystem_conn != 0)
			{
				printf("OBC sent to Subsystem successful, response: ");
				for(int i = 0; i < sizeof(response); i++)
				{
					printf("%02x,",(unsigned int) ((char*)&response)[i]); // get the bytes for a sample telecommand (temporary)
				}
				printf("\r\n");
			}
			else
			{
				printf("OBC sent to Subsystem failed\r\n");
			}
		}

		// send data to TTNC for downlink
		csp_conn_t *conn_outgoing;
		csp_packet_t *packet_outgoing;
		conn_outgoing = csp_connect(PROTOCOL_PRIO_NORM, PROTOCOL_TTNC_ADDR, PROTOCOL_SUBSYS_DATA_PORT, PROTOCOL_TIMEOUT_HM, 0);
		packet_outgoing = csp_buffer_get(sizeof(response));
		
		set_APID(&(tm.header), 12);
		printf("new apid: %d\r\n", tm.header.p_ID.APID);
		set_source_data(&tm, &response, sizeof(tm.data.src_data));
		
		// TODO: rmb to add back apid!
		packet_outgoing->length = sizeof(tm);
		printf("size of tm: %d\r\n", packet_outgoing->length);
		memcpy(packet_outgoing->data, &tm, sizeof(tm));
		printf("content of tm: %d\r\n", packet_outgoing->data);
				
		printf("Sending: ");
		for(int i = 0; i < sizeof(response); i++) // LHM: sizeof(packet_outgoing->data) is always 0, can't use that, think it is size of pointer
		{
			printf("%02x,",(unsigned int) ((char*)&packet_outgoing->data)[i]); // get the bytes for a sample telecommand (temporary)
		}
		printf("\r\n");
		
		if (csp_send(conn_outgoing, packet_outgoing, PROTOCOL_TIMEOUT_HM) == 0) { // csp_send = 0 if unsuccessful
			printf("Send to ttnc not successful;\r\n");
			csp_buffer_free(packet_outgoing);
		}
		else
		{
			// Close the connection after use
			csp_close(conn_outgoing);
			printf("Sent to TTnC success, closing connection\r\n\r\n");
		}
		
		vTaskDelay(5);
	}
}