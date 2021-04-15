#include
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int analogInput = A0;
int value =0;
float vin = 0.0; //vin = 0 when V2-V1!=0
float Time=0.0; // f=1/T
float frequency = 0.0; //w2
const int input = A1; 
float capacitance = 0.0; //C2
int N = 0; //Number of Covid-19 in the air 
int Npercentage = 0; //Number of Covid-19 in the air 
int X=0;
int Y=0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Covid-19 in the air:");
  pinMode(analogInput, INPUT);
  pinMode(frequency, INPUT);
  pinMode(input, INPUT);
}

void loop() {
  // read the value at analog input
   value = analogRead(analogInput);
   if (value<0.09 /*offset*/) {
   vin=1;//when V2=V1
   X=pulseIn(input,HIGH);
   Y=pulseIn(input, LOW);
   Time=X+Y;
   frequency=1/Time;
   capacitance = 1/(1.4889*(frequency*frequency));
   N = (((cpacitance/(4.2923*10^-12))-16)*10^8)/16;
   Npercentage = N/10^8;
   }
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
   lcd.print(Nercentage);
}
delay(10);




