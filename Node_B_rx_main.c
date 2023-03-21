//Node - B receiver program

#include<lpc21xx.h>
#include"common_define.h"
#include"CAN_delay.h"
#include"CAN_header.h"
#include"uart_header.h"

int main(void)
{
	CAN2_msg m1;
	CAN2_init();
	while(1)
	{
		CAN2_msg_rx(&m1);
		if(m1.rtr == 0)
		{
			uart0_string_tx("Node B get data frame from Node A\r\n");
			uart0_string_tx("Msg id : 0x");
			uart0_hexa(m1.id);
			uart0_string_tx("\t\tDLC : ");
			uart0_hexa(m1.dlc);
			uart0_string_tx("\t\tdata : ");
			uart0_hexa(m1.A_bytes);
		}
		else
		{
			uart0_string_tx("Node B get remote frame from Node A\r\n");
			uart0_string_tx("Msg id : 0x");
			uart0_hexa(m1.id);
			uart0_string_tx("\t\tDLC : ");
			uart0_hexa(m1.dlc);
		}
			uart0_string_tx("\r\n");			
	}
}
