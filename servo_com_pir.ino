#include <Servo.h>
#define SERVO 9

Servo s;
int pos;
int inputPIR = 10;
int pirState = HIGH;
int PIR = 0;
int led = 13;

void setup() {

  Serial.begin(9600);
  s.attach(SERVO);
  s.write(0); // Inicia motor posição zero

}

void loop() {

  PIR = digitalRead(inputPIR);
  
  if (PIR == HIGH) {
    if (pirState  == LOW) {

    	Serial.println("Movimento detectado");
      
      	  	for(pos = 0; pos < 90; pos++) {
   				s.write(pos);
                digitalWrite(led, HIGH);
  				delay(15);
          	}
      		delay(1000);
  
 			for(pos = 90; pos >= 0; pos--){
    			s.write(pos);
              	digitalWrite(led, LOW);
    			delay(15);
  			}
           	pirState = HIGH;
    } else {
      	if (pirState == HIGH) {
          	Serial.println("Movimento Encerrado");
          	pirState = LOW;
        }
    }
 }
  
  

  
}
