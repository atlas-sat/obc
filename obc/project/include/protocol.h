
/*
 * protocol.h
 *
 * Created: 20/8/2024 9:05:06 pm
 *  Author: huimin
 */ 

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#define PROTOCOL_OBC_ADDR 1
#define PROTOCOL_TTNC_ADDR 2
#define PROTOCOL_SUBSYS_ADDR 8
#define PROTOCOL_SUBSYS_PING_PORT 1
#define PROTOCOL_SUBSYS_DATA_PORT 8
#define PROTOCOL_PRIO_NORM 1
#define PROTOCOL_TIMEOUT 1000
#define PROTOCOL_TIMEOUT_HM 100

void csp_client (void *pvParameters);
void csp_twoway_client(void *pvParameters) ;

typedef struct {
	int addr;
	int port;
} apid_map;

#endif /* PROTOCOL_H_ */
