int airPurifier = 7;

// we assume expected Airquality is 75 for simplification

int sensorValue;

void setup() {
  Serial.begin(9600);
  pinMode(airPurifier,OUTPUT);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {
   sensorValue = random(100);// a random number is taken from 0 to 100 as sensor return value
  // to display the sensor value in serial monitor
  // we assume expected Air quality of air is 75 for simplification

   int exp = 75  ;// expected air quality(0 - 100).

   if(sensorValue<exp)
   {
    digitalWrite(airPurifier,HIGH);
   }

   else
    {
     digitalWrite(airPurifier,LOW);
    }

  delay(3000);
}