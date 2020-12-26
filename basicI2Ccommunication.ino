#include <Wire.h>

void setup()
{
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.println("start");
}

void loop()
{
  //nix.
}
volatile char buffer[40];
volatile boolean receiveFlag = false;

void receiveEvent(int howMany)
{
  
  while (0 < Wire.available()) {
    digitalWrite(11, HIGH); //PowerIndicator On
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
  Serial.println("#");             /* to newline */
  
  digitalWrite(11, LOW); //PowerIndicator On
}


void requestEvent() {
Serial.println("!");
  String InfoCache = "TestT#";
  Wire.write((char*) InfoCache.c_str());      //sends string
  Serial.print("Sending: ");
  Serial.println(InfoCache);


}
