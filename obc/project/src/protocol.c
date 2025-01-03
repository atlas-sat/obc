/*
 * protocol.c
 *
 * Created: 20/8/2024 9:06:05 pm
 *  Author: huimin
 */ 
/*
    obc_task.c

    Created: 12/12/2020 10:36:43 PM
    Author: user
*/


/*avr libs*/
#include <stdio.h>
#include <string.h>
#include <delay.h>

/*freertos lib*/
#include "FreeRTOS.h"
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include <portable.h>

/*csp lib*/
#include <csp/csp.h>
#include <csp/interfaces/csp_if_i2c.h>
#include <csp/drivers/i2c.h>
#include <csp/csp_endian.h>

// OBC header
#include <proto.h>

TaskHandle_t I2C_task;


// This task is for CSP to send request
void csp_client (void *pvParameters) {
    csp_conn_t *conn;
    csp_packet_t *packet;
    int ret;
    conn = csp_connect(PRIO_NORM, SUBSYS_ADDR, SUBSYS_DATA_PORT, TIMEOUT, 0);

    csp_conn_print_table();
    printf("\r\n");

    packet = csp_buffer_get(sizeof(csp_packet_t));
    sprintf(packet->data, "hello");
    packet->length = strlen("hello");

    while (1) {
        printf("\r\n\r\nSending packet now\r\n");
        ret = csp_send(conn, packet, 0);

        if (ret == 1) {
            printf("\r\nSent successfully");
            //csp_close(conn);
        }
        else {
            printf("Sent failed\r\n");
        }

        vTaskDelay(10000);
    }
}

void csp_twoway_client(void *pvParameters) {
    int ret;
    char incoming[100];
    char outgoing_data[] = "hello_twoway";
    char outgoing_ping[] = "Ping";

    while (1) {
        /**
            Perform an entire request/reply transaction
            Copies both input buffer and reply to output buffer.
            @param prio CSP Prio
            @param dest CSP Dest
            @param port CSP Port
            @param timeout CSP timeout
            @param outbuf pointer to outgoing data buffer
            @param outlen length of request to send
            @param inbuf pointer to incoming data buffer
            @param inlen length of expected reply, -1 for unknown size (note inbuf MUST be large enough)
            @return Return 1 or reply size if successful, 0 if error or incoming length does not match or -1 if timeout was reached
        */
        ret = csp_transaction(PRIO_NORM, SUBSYS_ADDR, SUBSYS_PING_PORT, 1000, outgoing_ping, strlen(outgoing_ping), incoming,
                              -1);

        if (ret != -1 && ret != 0) {
            printf("Ping -- Success\r\n");
            //printf("Reply: %s, Length: %d\r\n\r\n", incoming, ret);
        }
        else if (ret == -1) {
            printf("Ping -- Timeout\r\n");
        }
        else {
            printf("Ping -- Failed\r\n");
        }

        //delay_ms(2000);

        //ret = csp_transaction(4, SUBSYS_ADDR, SUBSYS_DATA_PORT, 1000, outgoing_data, strlen(outgoing_data), incoming, -1);
        //if (ret != -1 || ret != 0) printf("Data -- Success\r\nReply: %s\r\n", incoming);
        //else if (ret == -1) printf("Data -- Timeout\r\n");
        //else printf("Data -- Failed\r\n");
        vTaskDelay(10000);
    }
}