#include <REGX52.H>
unsigned char xdata Ones _at_ 0xFD00;
unsigned char xdata Tens _at_ 0xFE00;
int i=0;
int a = 0;
int b = 0;
int licznik = 0;
int krotki = 0;
int dlugi = 0;
int flaga1 = 0;
int flaga2 = 0;
int flaga3 = 0;
int zliczarka=0;
int O,T;
int onesy[] = {42,110,21,48,121,84,0,113,48,56,120,80,0};
int tensy[] = {0,42,110,21,48,121,84,0,113,48,56,120,80};
int code onestimer[] = {0,  111, 127, 7, 125, 109, 102, 79, 91, 6,  63, 111, 127, 7, 125, 109, 102, 79, 91, 6,  63, 111, 127, 7, 125, 109, 102, 79, 91, 6,  63, 0, 63};
int code tenstimer[] = {79, 91,  91,  91, 91, 91,  91,  91, 91, 91, 91, 6,    6,  6,   6,  6,   6,   6,  6,  6, 6,   0,   0,  0,  0,   0,   0,   0,  0, 0,   0, 0, 63};
void init(){
	//int0
	EX0 = 1;
	IT0 = 1;
	//int1
	EX1 = 1;
	IT1 = 1;
	//Timer 0
	ET0 = 1;
	TR0 = 1;
	TMOD = 0 | T0_M0_;
	//Timer 1
	ET1 = 1;
	TR1 = 1;
	TMOD = 0 | T1_M0_;
	//enabled all
	EA = 1;
}					
void ISR_INT0() interrupt 0{   //przycisk 
	while(!P3_2){zliczarka++;}
	if(zliczarka < 100){
		//wlacz timer karmnika
		if(flaga3 == 0){
			flaga3 = 1;
		}
		//jezeli timer karmnika dziala to go wylacz
		//TODO
		zliczarka = 0;
	}
	if(zliczarka > 100){
		//jezeli timer w tle nie dziala to go wlacz
		if(flaga2 == 0){
			flaga1 = 1;
		}
		//jezeli timer w tle dziala to go wylacz
		if(flaga2 == 1){
			flaga1 = 0;
			flaga2 = 0;
			O = 0;
			T = 0;
			a = 0;
		}
		zliczarka = 0;
	}
}

void ISR_T0() interrupt 1{ 			//TIMER 0
	   if(flaga1 == 1){
			licznik++;
		}
		if(licznik == 80){
			flaga2 = 1;
			flaga1 = 0;
			licznik = 0;
		}
}
void ISR_T1() interrupt 3{			//TIMER 1
	   if(flaga2 == 1){
	   		O = onesy[a];
			T = tensy[a];
			a++;
			if(a == 12) a = 0;
	   } 
	    if(flaga3 == 1){
			O = onestimer[b];
			T = tenstimer[b];
			O = onestimer[b];
			T = tenstimer[b];
			b++;
			if(b == 32) {
			flaga3 = 0;
			b = 0;
			}
		}
}

void main(){
	init();
	while(1){
		 Ones = O;
		 Tens = T;

	}
}