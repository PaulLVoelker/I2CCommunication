#include <Wire.h>
//Max 32byte communctaion
void setup()
{
  Wire.begin(0);
  Serial.begin(9600);
  Serial.println("start");
}

void loop()
{
  Serial.println("SEndung:");
  String command = "S1x?GS?";
  Wire.beginTransmission(1);     //begin transmission with device address of module
  Wire.write((char*) command.c_str());
  Wire.endTransmission();
  Serial.println("SEndung:" + command);

  
  String i2c_buffer;
  Serial.println("Request from: " + String(1));
  Wire.beginTransmission(1);     //begin transmission with device address of module
  Wire.requestFrom(1, 64);
  while (0 < Wire.available())
  {
    char c = Wire.read(); // adds character to buffer
    Serial.print(c);
    i2c_buffer += c;
    if (c == '#') { // break if end pointer
      //i2c_buffer[i + 1] = '\0'; //adds empty character to end
      break;
    }
  }
  Wire.endTransmission(1);
  Serial.println("-");
  Serial.println(i2c_buffer);
  Wire.endTransmission();


  delay(2000);
}
