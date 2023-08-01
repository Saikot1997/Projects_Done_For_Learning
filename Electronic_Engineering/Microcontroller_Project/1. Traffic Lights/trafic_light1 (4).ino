int carred = 11;
int caryellow = 10;
int cargreen = 9;

int padred = 13;
int padgreen = 12;

int padpushbutton = 3;
int buspushbutton = 2;
unsigned long event1 = 0;
unsigned long busevent = 1800000;
unsigned long event2 = 1800000;
unsigned long event3 = 1800000; 
unsigned long event4 = 1800000;
unsigned long padevent11 = 1800000;
unsigned long padevent12 = 1800000;
unsigned long padevent13 = 1800000;
unsigned long padevent14 = 1800000;
unsigned long padevent21 = 1800000;
unsigned long padevent31 = 1800000;
unsigned long padevent41 = 1800000;
unsigned long padevent42 = 1800000;
unsigned long padevent43 = 1800000;

const unsigned long Time1 = 2000;
const unsigned long Time2 = 4000;
volatile bool padpush = LOW;
volatile bool buspush = LOW;


void setup(){
  pinMode(carred , OUTPUT);
  pinMode(cargreen , OUTPUT);
  pinMode(caryellow , OUTPUT);
  
  pinMode(padgreen , OUTPUT);
  pinMode(padred , OUTPUT); 
  
  pinMode(padpushbutton, INPUT_PULLUP);
  pinMode(buspushbutton,INPUT);
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
  if(padpush == LOW){
             buspush = HIGH;
           }
  if(padpush == HIGH){
             buspush = LOW;
           }
     }


void changeLights(){
     unsigned long currentTime = millis();
  
  // This part of codes is normal sequencial coding, (any button pressed or not pressed  This will work.
  if(currentTime >= event1+2000 && currentTime < event1+2050) { 
  	  
      digitalWrite(carred, LOW);
      digitalWrite(caryellow,LOW);
      digitalWrite(padred, HIGH);
      digitalWrite(padgreen, LOW);
      digitalWrite(cargreen, HIGH);
                          
      if(padpush == HIGH){ 
      padevent11 = currentTime;
                      }
    
    }
  
 
  if(currentTime >= event1+3950 && currentTime < event1+4000) { 
  	  
      digitalWrite(carred, LOW);
      digitalWrite(caryellow,LOW);
      digitalWrite(padred, HIGH);
      digitalWrite(padgreen, LOW);
      digitalWrite(cargreen, HIGH);
      
    if(buspush == HIGH){
                      busevent = currentTime;
                     }
                         
    if(padpush == LOW){ 
      event2 = currentTime;
                      }
    
    }
  
 


  
  // If pedestrian button not pressed and bus button pressed while vehicle traffic light green on, Then This part of code work.
 
  if(currentTime >= busevent+2000 && currentTime < busevent+2050) { 
  	  
      digitalWrite(carred, LOW);
      digitalWrite(caryellow,LOW);
      digitalWrite(padred, HIGH);
      digitalWrite(padgreen, LOW);
      digitalWrite(cargreen, HIGH);    
    }
    if(currentTime >= busevent+9950 && currentTime < busevent+10000) { 
  	  
      digitalWrite(carred, LOW);
      digitalWrite(caryellow,LOW);
      digitalWrite(padred, HIGH);
      digitalWrite(padgreen, LOW);
      digitalWrite(cargreen, HIGH);

      buspush = LOW;
    
      if(padpush == HIGH){ 
      padevent11 = currentTime;
                      }
      if(padpush == LOW){
      event2 = currentTime;
               }
      
      
    }
  
  
  
  
   // if pedestrian button pressed while vehicle traffic light green on , then this part of codes work.
  
  if(currentTime >= padevent11+2000 && currentTime < padevent11+3000){
          digitalWrite(carred, LOW);
          digitalWrite(caryellow,HIGH);
          digitalWrite(padred, HIGH);
          digitalWrite(padgreen, LOW);
          digitalWrite(cargreen, LOW);
      }
  if(currentTime >= padevent11+3000 && currentTime < padevent11+10000){
          digitalWrite(carred, HIGH);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, LOW);
          digitalWrite(padgreen,HIGH);
          digitalWrite(cargreen, LOW);
      }

   if(currentTime >= padevent11+10000 && currentTime < padevent11+11000){
          digitalWrite(carred, HIGH);
          digitalWrite(caryellow,HIGH);
          digitalWrite(padgreen,LOW);
          digitalWrite(padred, HIGH);
          digitalWrite(cargreen, LOW);
      }
  
   if(currentTime >= padevent11+11000 && currentTime < padevent11+13000){
          digitalWrite(carred,LOW);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, HIGH);
          digitalWrite(padgreen,LOW);
          digitalWrite(cargreen, HIGH);
     
          padpush = LOW;
      
          event2 = currentTime;
      }
  
  
  
 
  
  
  
  
  
  
   
// This part of codes is normal sequencial coding, (any button pressed or not pressed  This will work.       
  if(currentTime >= event2+2000 && currentTime < event2+2050){
        
        digitalWrite(cargreen, LOW);
        digitalWrite(caryellow, HIGH);
        digitalWrite(carred,LOW);
        digitalWrite(padgreen,LOW);
        digitalWrite(padred, HIGH);
        
        if(padpush == HIGH){ 
                      padevent21 = currentTime;
                      }
  }  
  
if(currentTime >= event2+3900 && currentTime < event2+4000){
        
        digitalWrite(cargreen, LOW);
        digitalWrite(caryellow, HIGH);
        digitalWrite(carred,LOW);
        digitalWrite(padgreen,LOW);
        digitalWrite(padred, HIGH);
        
        if(padpush == LOW){ 
                      event3 = currentTime;
                      }
        if(padpush == HIGH){ 
                      padevent21 = currentTime;
                      }
  }  
  
 
  
  
   // if pedestrian button pressed while vehicle traffic light yellow on , then this part of codes work.
  if(currentTime >= padevent21+1000 && currentTime < padevent21+8000){
          digitalWrite(carred, HIGH);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, LOW);
          digitalWrite(padgreen,HIGH);
          digitalWrite(cargreen, LOW);
  
          padpush = LOW;
      
          event3 = currentTime;
      }

    
  
  
  
  
  // This part of codes is normal sequencial coding, (any button pressed or not pressed  This will work.)
  if(currentTime >= event3+2000 && currentTime < event3+2050){
   		       
         digitalWrite(caryellow, LOW);
         digitalWrite(cargreen, LOW);
     	 digitalWrite(padred,LOW);
         digitalWrite(padgreen,HIGH);
 		 digitalWrite(carred, HIGH);
        
        if(padpush == HIGH){ 
                      padevent31 = currentTime;
                      }
 }


  if(currentTime >= event3+3950 && currentTime < event3+4000){
   		       
         digitalWrite(caryellow, LOW);
         digitalWrite(cargreen, LOW);
     	 digitalWrite(padred,LOW);
         digitalWrite(padgreen,HIGH);
 		 digitalWrite(carred, HIGH);
        
        if(padpush == LOW){ 
                      event4 = currentTime;
                      }
        if(padpush == HIGH){ 
                      padevent31 = currentTime;
                      }
 } 
   
  
  
  
   // if pedestrian button pressed while vehicle traffic light red on , then this part of codes work.

  if(currentTime >= padevent31+1000 && currentTime < padevent31+8000){
          digitalWrite(carred, HIGH);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, LOW);
          digitalWrite(padgreen,HIGH);
          digitalWrite(cargreen, LOW);

          padpush = LOW; 
       
          event4 = currentTime;
      }
  
  
  
  
  
  // This part of codes is normal sequencial coding, (any button pressed or not pressed  This will work.
  if(currentTime >= event4+2000 && currentTime < event4+2050){
   		 
         digitalWrite(cargreen, LOW);
         digitalWrite(padgreen, LOW);
         digitalWrite(carred, HIGH);
         digitalWrite(padred, HIGH);
         digitalWrite(caryellow, HIGH);
         digitalWrite(padgreen,LOW);
  
        if(padpush == HIGH){ 
                      padevent41 = currentTime;
                      }
  } 
     if(currentTime >= event4+3950 && currentTime < event4+4000){
   		 
         digitalWrite(cargreen, LOW);
         digitalWrite(padgreen, LOW);
         digitalWrite(carred, HIGH);
         digitalWrite(padred, HIGH);
         digitalWrite(caryellow, HIGH);
         digitalWrite(padgreen,LOW);
         if(padpush == LOW){ 
                      event1 = currentTime;
                      }
  
        if(padpush == HIGH){ 
                      padevent41 = currentTime;
                      }
  } 

  // if pedestrian button pressed while vehicle traffic light red,yellow on , then this part of codes work.
   if(currentTime >= padevent41+1000 && currentTime < padevent41+3000){
          digitalWrite(carred,LOW);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, HIGH);
          digitalWrite(padgreen,LOW);
          digitalWrite(cargreen, HIGH);
      }
   if(currentTime >= padevent41+3000 && currentTime < padevent41+4000){
          digitalWrite(carred, LOW);
          digitalWrite(caryellow,HIGH);
          digitalWrite(padred, HIGH);
          digitalWrite(padgreen, LOW);
          digitalWrite(cargreen, LOW);
      
          padevent43 = currentTime;
      }
    if(currentTime >= padevent41+4000 && currentTime < padevent41+11000){
          digitalWrite(carred, HIGH);
          digitalWrite(caryellow,LOW);
          digitalWrite(padred, LOW);
          digitalWrite(padgreen,HIGH);
          digitalWrite(cargreen, LOW);
      
          padpush = LOW;
      
          event1 = currentTime;
      } 
  
  
  
  
  
  
}






