//CAN protocol header file

#include<lpc21xx.h>

//pin selection for CAN2

#define RD2 0x00004000	//p0.23 
#define TD2 0x00010000	//p0.24  

//CAN frame details

typedef struct CAN2
{
	int id;
	int rtr;
	int dlc;
	int A_bytes;
	int B_bytes;
}CAN2_msg;

//CAN register bit details.............
//...............................................
//C2MOD ---> CAN MODE register....
#define RM 0

//C2BTR --> Bus Timer Register  >>>> set speed for communication 
#define Speed 0x0001C001D		// 125 kbps
//#define Speed 0x0001C0011		//  100 kbps

//AFMR ---> Acceptance Filter Mode Register 
#define AccBp 1		//accept all messages

//CANCMR  ---> CAN Command Register
#define TR 0		// transmit request
#define RRB 2		// Release receiver buffer
#define STB1 5  // Select buffer register 1

//C2GSR  --> CAN2 Golbal Status Register
#define	TCS 3 


void CAN2_init(void)
{
	PINSEL1 |= RD2|TD2;
	VPBDIV = 1;					//(CCLK = PCLK)
	C2MOD |= 1<<RM;			//RESET
	AFMR |= 1<<AccBp;		//Accept all msg
	C2BTR = Speed;			//125 kbps
	C2MOD &= ~(1<<RM);			//RESET
}

void CAN2_msg_tx(CAN2_msg M1)
{
	C2TID1 = M1.id;
	C2TFI1 = (M1.dlc<<16);
	
	if(M1.rtr == 0)
	{
			C2TFI1 &= ~(1<<30);		//rtr = 0
			C2TDA1 = M1.A_bytes;
			C2TDB1 = M1.B_bytes;		
	}
	else
	{
			C2TFI1 |= (1<<30);		//rtr = 1
	}
	C2CMR = (1<<TR)|(1<<STB1);
	while((C2GSR &(1<<TCS))==0);
}

void CAN2_msg_rx(CAN2_msg *M1)
{
	while((C2GSR &(0X1))==0);
	M1->id = C2RID;
	M1->dlc = (C2RFS>>16)&(0X0F);
	M1->rtr = (C2RFS>>30)&(0X01);
	
	if(M1->rtr == 0)
	{
		M1->A_bytes = C2RDA;
		M1->B_bytes = C2RDB;
	}
	C2CMR = 1<<RRB;
}
