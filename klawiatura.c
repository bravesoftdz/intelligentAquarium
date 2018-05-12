#include <REGX52.H>
//zmienne przechowujace wcisniete klawisze
long int i = 0;
int tab[3] ={4,5,6};
int blad = 0;
int flaga = 0;
int flaga2 = 0;
int j;
void sleep(a){
	for(i=0; i<a*500; i++);
}
void Init(void){
	RCAP2H=TH2=0xFF;  
	RCAP2L=TL2=0xDC;  
	T2CON=0x30; 
	SCON=0x40;  
	
	TR2=1;
	P3_4=1;
}
void wyslij(unsigned char znak){
	SBUF=znak;
}
void zapal_diode(){
	P0_0 = 0;
}
void zgas_diode(){
	P0_0 = 1;
}
void k1(){
	P2_3 = 0;
	P2_2 = 1;
	P2_1 = 1;
	//jeden
	if(!P2_4){
		while(!P2_4){}
		tab[i] = 1;
		i++;
		flaga2 = 1;	
	}
	//cztery
	if(!P2_5){
		while(!P2_5){}
		tab[i] = 4;
		i++;
		flaga2 = 1;
	}
	//siedem
	if(!P2_6){
		while(!P2_6){}
		tab[i] = 7;
		i++;
		flaga2 = 1;
	}
	//gwiazdka
	if(!P2_7){
		while(!P2_7){}
		tab[i] = 10;
		i++;
	}
}
void k2(){
	P2_3 = 1;
	P2_2 = 0;
	P2_1 = 1;
	//dwa
	if(!P2_4){
		while(!P2_4){}
		tab[i] = 2;
		i++;
	}
	//piec
	if(!P2_5){
		while(!P2_5){}
		tab[i] = 5;
		i++;
	}
	//osiem
	if(!P2_6){
		while(!P2_6){}
		tab[i] = 8;
		i++;
	}
	//zero
	if(!P2_7){
		while(!P2_7){}
		tab[i] = 0;
		i++;
	}
}
void k3(){
	P2_3 = 1;
	P2_2 = 1;
	P2_1 = 0;
	//trzy
	if(!P2_4){
		while(!P2_4){}
		tab[i] = 3;
		i++;
	}
	//szesc
	if(!P2_5){
		while(!P2_5){}
		tab[i] = 6;
		i++;
	}
	//dziewiec
	if(!P2_6){
		while(!P2_6){}
		tab[i] = 9;
		i++;
	}
	//hash
	if(!P2_7){
		while(!P2_7){}
		tab[i] = 11;
		i++;
	}
	
}

void sprawdz(){
	if(i == 3) i = 0;
	if(tab[0] == 1 && tab[1] == 2 && tab[2] == 3){
		zapal_diode();
		flaga = 1;
		blad = 0;
	}
	else if(tab[0] == 4 && tab[1] == 5 && tab[2] == 6){
		zgas_diode();
		flaga = 0;
		blad = 0;
	}
	else if(tab[0] == 7 && tab[1] == 8 && tab[2] == 9){
		wyslij(60);
		blad = 0;
		if(flaga == 1){
		tab[0] = 1;
		tab[1] = 2; 
		tab[2] = 3;
		}
		else{
		tab[0] = 4;
		tab[1] = 5;
		tab[2] = 6;
		}
	}
	else if(tab[0] == 10 && tab[1] == 0 && tab[2] == 11){
		wyslij(0);
		blad = 0;
		if(flaga == 1){
		tab[0] = 1;
		tab[1] = 2;
		tab[2] = 3;
		}
		else{
		tab[0] = 4;
		tab[1] = 5;
		tab[2] = 6;
		}
	}

}
void main(){
	init();
	while(1){
		k1();
		k2();
		k3();
		sprawdz();
	}	

}