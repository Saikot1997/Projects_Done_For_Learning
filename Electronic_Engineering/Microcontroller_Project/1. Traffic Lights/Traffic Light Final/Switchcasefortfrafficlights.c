#include <stdio.h>
#include<time.h>
int main(void){
	int carRed, carYellow, carGreen, pedGreen, pedRed;
	int button;
	
	for (int time=0; time<9000; time++)
	switch(time){
		case 0:
		digitalWrite(carGreen, HIGH);
		digitalWrite(carYellow, LOW);
		digitalWrite(carRed, LOW);
		digitalWrite(pedGreen, LOW);
		digitalWrite(pedRed, HIGH); 
		
		case 3000:
		digitalWrite(carGreen, LOW);
		digitalWrite(carYellow, HIGH);
		digitalWrite(carRed, LOW);
		digitalWrite(pedGreen, LOW);
		digitalWrite(pedRed, HIGH); 
		
		case 4000:
		digitalWrite(carGreen, LOW);
		digitalWrite(carYellow, LOW);
		digitalWrite(carRed, HIGH);
		digitalWrite(pedGreen, LOW);
		digitalWrite(pedRed, HIGH); 
		
		case 5000:
		digitalWrite(carGreen, LOW);
		digitalWrite(carYellow, LOW);
		digitalWrite(carRed, HIGH);
		digitalWrite(pedGreen, HIGH);
		digitalWrite(pedRed, LOW); 
		
		case 8000:
		digitalWrite(carGreen, LOW);
		digitalWrite(carYellow, LOW);
		digitalWrite(carRed, HIGH);
		digitalWrite(pedGreen, LOW);
		digitalWrite(pedRed, HIGH); 
		
		while (button=1)
		time = 3000;
	}
	return 0;
}