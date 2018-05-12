#include<REGX52.H>
sbit in1 = P2^1; sbit in2 = P2^2; sbit en1 = P2^3;
sbit in3 = P2^5; sbit in4 = P2^6; sbit en2 = P2^4;
int wyslano = 0;
int i;
volatile unsigned char licznik1;
volatile int liczbaobrotow1 = 0;
volatile unsigned char stan;
void wyslij(unsigned char znak){
	SBUF=znak;
}
void stan1(){
  	in1 = 1;
	in2 = 0;
	stan = 1;
}
void stan2(){
	in1 = 0;
	in2 = 1;
	stan = 2;
}
void ISR_INT0() interrupt 0{
	   liczbaobrotow1++;
	   P3_4 = 1;
	    wyslij(liczbaobrotow1);
	   if(stan == 1 && liczbaobrotow1%16 == 0) stan2();
	   else if(stan == 2 && liczbaobrotow1%16 == 0) stan1();
	   if(liczbaobrotow1 == 32) liczbaobrotow1 = 0;
	   
}
void ISR_INT1() interrupt 2{
	P3_4 = 0;	
}
void ISR_T0() interrupt 1{

}
void ISR_serial(void)interrupt 4
{
	if(TI==1) {TI=0;}
	if(RI==1) {
		P1=SBUF;
			if(P1 == 60){
			licznik1++;
			if(licznik1%8 == 6 || licznik1%8 == 7) en1 = 0;
			else if(licznik1%5 == 1 || licznik1%5 == 2 ) en2 = 1;
			else{
				en1 = 1;
				en2 = 0;
			}
			}
			else if(P1 == 0){
				wyslij(0);
				P3_4 = 0;
				en1 = 0;
				en2 = 0;
			}
		RI=0;
	}

}

void Init(void)
{	
	EX0 = 1; IT0 = 1;
	EX1 = 1; IT1 = 1;
	stan = 1;
	P1 = 0;
	RCAP2H=TH2=0xFF;
	RCAP2L=TL2=0xDC;
	T2CON=0x30;		
	ES=1;
	SCON=0x50;
	TR2=1;
	EA=1;
	P3_4=0;
}

void main (void)
{
	Init();
	in2 = 0; en1 = 0;
	in3 = 0; en2 = 0;
	while(1)
	{
		if(P1 == 60){
			licznik1++;
			if(licznik1%8 == 6 || licznik1%8 == 7) en1 = 0;
			else if(licznik1%5 == 1 || licznik1%5 == 2 ) en2 = 1;
			else{
				en1 = 1;
				en2 = 0;
			}
		}
		else if(P1 == 0){
			wyslij(0);
			P3_4 = 0;
			en1 = 0;
			en2 = 0;
		}
	} 
}