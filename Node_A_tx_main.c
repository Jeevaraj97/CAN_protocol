//Node - A transmit program

#include<lpc21xx.h>
#include"common_define.h"
#include"CAN_delay.h"
#include"CAN_header.h"
#include"uart_header.h"

int main(void)
{
	CAN2_msg m1,m2;
	CAN2_init();
	uart0_init();
	m1.id = 0x1df;
	m1.dlc = 4;
	m1.rtr = 0;
	m1.A_bytes = 0xAABBCCDD;
	m1.B_bytes = 0x0;
	m2.id = 0x1a3;
	m2.dlc = 4;
	m2.rtr = 0;
	while(1)
	{
		uart0_string_tx("Node_A transmit the data frame to Node_B");
		CAN2_msg_tx(m1);
		delay_sec(5);
		uart0_string_tx("Node_A transmit the remote frame to Node_B for requesting the data");
		CAN2_msg_tx(m2);
		delay_sec(5);
	}
}
