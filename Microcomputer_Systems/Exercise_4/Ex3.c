#include <avr/io.h>
char x;
int main(void)
{
DDRA=0xFF;	 // Αρχικοποίηση PORTA ως output
DDRC=0x00;	// Αρχικοποίηση PORTC ως input
x = 1;		// Αρχικοποίηση μεταβλητής για αρχικά αναμμένο led
while(1)
	{
		if ((PINC & 0x01) == 1)		// Έλεγχος πατήματος push-button SW0
			{ 
				while ((PINC & 0x01) == 1); // Έλεγχος επαναφοράς push-button SW0
				if (x==128) // Έλεγχος υπεχείλισης
				x = 1;
				else
				x = x<<1; // Ολίσθηση αριστερά
			}
			
		if ((PINC & 0x02) == 2)		// Έλεγχος πατήματος push-button SW1
			{ 
				while ((PINC & 0x02) == 2); // Έλεγχος επαναφοράς push-button SW1
				if (x==1) // Έλεγχος υπεχείλισης
				x = 128;
				else
				x = x>>1; // Ολίσθηση δεξια
			}
			
		if ((PINC & 0x04) == 4)		// Έλεγχος πατήματος push-button SW2
			{ 
				while ((PINC & 0x04) == 4); // Έλεγχος επαναφοράς push-button SW2
				x = 128;				//Μετακινηση στο MSB
			}	
		if ((PINC & 0x08) == 8)		// Έλεγχος πατήματος push-button SW3
			{ 
				while ((PINC & 0x08) == 8); // Έλεγχος επαναφοράς push-button SW3
				x = 1;				// Μετακινηση στο LSB
			}			
	
	PORTA = x; // Έξοδος σε PORTA
	}
return 0;
}