#include <REGX52.H>

long int i = 0;
int b = 0;
char c;
int flagakierunku = 0;
extern w6mS();
unsigned char data Var1, Var2, Var3;

extern void LcdInit();
extern void Lcd_DisplayCharacter(char a_char);
extern void Lcd_DisplayRow(char row, char *string);
extern void Lcd_WriteControl(unsigned char LcdCommand);
extern void Lcd_Cursor (char row, char column);
void sleep(double a){
	for(i = 0; i<a*200; i++){}
}
void wyswietlInfo(){
	while(1){
		if(b == 0) Lcd_DisplayRow(1,"Aquarius 2000X  ");
		if(b == 5) Lcd_DisplayRow(1,"Filtr: Aqua H501");
		if(b == 10) Lcd_DisplayRow(1,"LED: Philips 300");
		b++;
		if(b == 15) b = 0; 
		if(P1>32 || P1 == 0) {
			Lcd_DisplayRow(2,"KARMNIK STOP    ");
		}
		else if(P1>0){
			c = P1;
			Lcd_DisplayRow(2,"KARMNIK START         ");
			if(P1 == 1 || P1 == 32){
			 	Lcd_Cursor(3,1);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 2 || P1 == 31){
			 	Lcd_Cursor(3,2);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 3 || P1 == 30){
			 	Lcd_Cursor(3,3);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 4 || P1 == 29){
			 	Lcd_Cursor(3,4);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 5 || P1 == 28){
			 	Lcd_Cursor(3,5);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 6 || P1 == 27){
			 	Lcd_Cursor(3,6);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 7 || P1 == 26){
			 	Lcd_Cursor(3,7);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 8 || P1 == 25){
			 	Lcd_Cursor(3,8);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 9 || P1 == 24){
			 	Lcd_Cursor(3,9);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 10 || P1 == 23){
			 	Lcd_Cursor(3,10);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 11 || P1 == 22){
			 	Lcd_Cursor(3,11);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 12 || P1 == 21){
			 	Lcd_Cursor(3,12);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 13 || P1 == 20){
			 	Lcd_Cursor(3,13);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 14 || P1 == 19){
			 	Lcd_Cursor(3,14);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 15 || P1 == 18){
			 	Lcd_Cursor(3,15);
				Lcd_DisplayCharacter('+');
			}
			else if(P1 == 16 || P1 == 17){
			 	Lcd_Cursor(3,16);
				Lcd_DisplayCharacter('+');
			}
		}
		sleep(0.5);
		Lcd_DisplayRow(3,"----------------");
		Lcd_DisplayRow(4,"                ");
	}
}

void ISR_serial(void)interrupt 4
{
	if(TI==1) {TI=0;}
	if(RI==1) {
		P1=SBUF;
		RI=0;
	}
}
void Init(void)
{	
	EX0 = 1; IT0 = 1;
	EX1 = 1; IT1 = 1;
	TMOD = 1;
	TH0 = TH1 = 0xFF;
	RCAP2H=TH2=0xFF;
	RCAP2L=TL2=0xDC;
	T2CON=0x30;		
	ES=1;
	SCON=0x50;
	TR2=1;
	EA=1;
	P3_4=0;
	P1 = 0;
}
void main(){
	LcdInit();
	Init();
	Lcd_Cursor(3,1);
	Lcd_WriteControl(0x0C);
	while(1){
	   wyswietlInfo();
	}
}