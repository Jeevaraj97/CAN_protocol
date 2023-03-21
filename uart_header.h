//uart0 serial communication header file
#include<stdio.h>
//uart0 pin selection.......
#define TXD0 0x00000001  
#define RXD0 0x00000004

//uart0 baudrate calculation....
//U0DLL and U0DLM register are used to set the baudrate
#define cry_osc 12000000
#define Cpu_clk cry_osc*5
#define Per_clk Cpu_clk/4
#define baudRate 9600
#define reg_val (Per_clk/(16*baudRate))

//uart0 initialization ....

void uart0_init(void)
{
	PINSEL0 |= TXD0|RXD0;
	U0LCR = 0X83;
	U0DLL = reg_val;
	U0DLM = reg_val>>8;
	U0LCR = 0X03;	
}

void uart0_tx(uc data)
{
	while((U0LSR&(1<<6))==0);
	U0THR = data;
}

void uart0_string_tx(char *d)
{
	while(*d)
	{
			uart0_tx(*d++);
	}
}

//uart0 integer display................
void uart0_integer(si n)
{ 
	uc arr[10];
	int i=0;
	if(n==0)
	{
		uart0_tx('0');
	}
	else if(n<0)
	{
		uart0_tx('-');
		n = -n;
	}
	while(n!=0)
	{
		arr[i++] = n%10;
		n = n/10;
	}
	for(--i;i>=0;i--)
	{
		uart0_tx(arr[i]+48);
	}
}
//uart float display..............
void uart0_float(f val)
{
	int t = val;
	uart0_integer(t);
	uart0_tx('.');
	if(val>0)
			t = (val-t)*1000000;
	else
			t = -(val-t)*1000000;

	uart0_integer(t);
}

//uart hexadecimal value function
void uart0_hexa(int hex)
{
	char a[10];
	sprintf(a,"%x",hex);
	uart0_string_tx(a);
}
