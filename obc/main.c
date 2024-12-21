#define F_CPU 16000000L // Specify oscillator frequency

#include <protocol.h>
#include <tasks.h>
#include <uart.h>

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

// CSP Libs
#include <csp/csp.h>
#include <csp/interfaces/csp_if_i2c.h>
#include <csp/drivers/i2c.h>

extern TaskHandle_t I2C_task;

int main(void)
{	
	// Initialize UART
	// Baud Rate: 57600
	uart_init();
	
	// CSP-related settings 
	csp_buffer_init(2, 300); // Creating 2 buffers of size 300 bytes each
	csp_init(PROTOCOL_OBC_ADDR); // Initialize to OBC's address
	csp_i2c_init(PROTOCOL_OBC_ADDR, 0, 400); // Setting the I2C node to OBC's address and speeds
	csp_route_set(PROTOCOL_TTNC_ADDR, &csp_if_i2c, CSP_NODE_MAC);
	csp_route_set(PROTOCOL_SUBSYS_ADDR, &csp_if_i2c, CSP_NODE_MAC);
	csp_route_start_task(500, 1); // Start the router task in CSP
	csp_rtable_print();
	printf("\r\n");
	
	//// Debugging task to see that the FreeRTOS works
	//extern void task_led_blinky(void *pvParameters);
	//xTaskCreate(task_led_blinky, "Task to blink led pin 7", 100, NULL, 2, NULL);
	//
	//// Setup the CSP OBC ping task
	//extern void csp_twoway_client(void *pvParameters);
	//xTaskCreate(csp_twoway_client, "Two-way Task to send client request", 250, NULL, 4, &I2C_task);
	
	extern void command_handler(void *pvParameters);
	xTaskCreate(command_handler, "ABC", 500, NULL, 2, NULL);
	
	// Start Scheduler
	vTaskStartScheduler();
	
	/*--------------------------------*/
	
	printf("Not enough to start scheduler\r\n");

	/* Execution will only reach here if there was insufficient heap to start the scheduler. */
	for ( ;; );
	
	return 0;
}
