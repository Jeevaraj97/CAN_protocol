// delay in seconds...................
void delay_sec(uc sec)
{
	T0PR 	= 60000000-1;
	T0TCR = 0X01;
	while(T0TC < sec);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
// delay in milliseconds...................
void delay_ms(uc ms)
{
	T0PR 	= 60000-1;
	T0TCR = 0X01;
	while(T0TC < ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
// delay in microseconds...................
void delay_mic_sec(uc micsec)
{
	T0PR 	= 60-1;
	T0TCR = 0X01;
	while(T0TC < micsec);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
