#include <avr/io.h>
#include <mega16.h>

usigned char x,A,B,C,D,CN,F0,F1;

void main(void){
	DDRA=0xF0;		//Set PORTA[3:0] as input, F0=1111 0000
	DDRB=0x03;		//Set PORTB[1:0] as output, 03=0000 0011

	x=PINA;			//diavazw tin eisodo
	x=x & 0x0F;		//apomonono ta 4LSB, 0000 1111=OF
	A=x & 0x01;		//apomonono to A(LSB) ,0000 0001=01
	if (A!=0){		//an to A den einai 0 tote tha einai 1
		A=0x01;} 
	B=x & 0x02;		//apomonono to B, 0000 0010=02
	if (B!=0){		//omoios me prin
		B=0x01;}
	C=x & 0x03;
	CN=~C;			//simpliroma tou C
	if (C!=0){
		C=0x01;}
	D=x & 0x04;
	if (D!=0){
		D=0x01;}
	F0=~((A&B&C)|(CN&D));
	F1=(A|B)&(C|D);		
	F1<<1;			//aristeri olisthisi tou F1 gia na paei sti sosti thesi
	PORTB= F0 & 0x01;	
	PORTB= F1 & 0x02;
}