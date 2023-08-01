
int carred = 11;
int caryellow = 10;
int cargreen = 9;

int padred = 13;
int padgreen = 12;

int padpushbutton = 3;
int buspushbutton = 2;

volatile bool padpush = LOW;
volatile bool buspush = LOW;


void setup(){
  pinMode(carred , OUTPUT);
  pinMode(cargreen , OUTPUT);
  pinMode(caryellow , OUTPUT);
  
  pinMode(padgreen , OUTPUT);
  pinMode(padred , OUTPUT); 
  
  pinMode(padpushbutton, INPUT_PULLUP);
  pinMode(buspushbutton,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(padpushbutton), padcontrol,CHANGE);
  attachInterrupt(digitalPinToInterrupt(buspushbutton), buscontrol,CHANGE);
}
void loop() {
    changeLights();
 }


void padcontrol(){
     padpush = HIGH;
      }

void buscontrol(){
  if( padpush == LOW){
             buspush = HIGH;
           }
  else if (padpush == HIGH){
           buspush = LOW;
           }
}


void changeLights(){

          digitalWrite(cargreen, HIGH);
          digitalWrite(carred, LOW);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, HIGH);
          digitalWrite(padgreen, LOW); 
          delay(5000);

          if(padpush == HIGH && buspush == LOW) {
              delay(0000);             
               }                        
          else if ( padpush == LOW && buspush == LOW){
              delay(5000);
              }
          else if (padpush == LOW && buspush == HIGH) {
              delay(15000);
              buspush = LOW;
          }

         


          digitalWrite(cargreen, LOW);
          digitalWrite(carred, LOW);
          digitalWrite(caryellow,HIGH);
          digitalWrite(padred, HIGH);
          digitalWrite(padgreen, LOW);
          delay(4000);
          if(padpush == HIGH) {
              delay(0000);
               }                        
          else if ( padpush == LOW){
              delay(3000);
              }
         
          
  
          
          digitalWrite(cargreen, LOW);
          digitalWrite(carred, HIGH);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, LOW);
          digitalWrite(padgreen,HIGH);
          delay(10000);
          if(padpush == HIGH) {
              delay(10000);
              padpush = LOW;
               }                        
         else if ( padpush == LOW){
              delay(0000);
              }
  

          digitalWrite(carred, HIGH);
          digitalWrite(caryellow,HIGH);
          digitalWrite(padgreen,LOW);
          digitalWrite(padred, HIGH);
          digitalWrite(cargreen, LOW);
          delay(2000);
          if(padpush == HIGH) {
              delay(000);
               }                        
         else if ( padpush == LOW){
              delay(2000);
              }
      }
  
