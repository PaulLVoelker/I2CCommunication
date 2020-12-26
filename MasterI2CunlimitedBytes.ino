#include <Wire.h>
//No max Byte count Communation
#define len(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))// number of items in an array
void setup()
{
  Wire.begin(0);
  Serial.begin(9600);
  Serial.println("start");
}

void loop()
{

  String command = "MESSAGEMESSAGEMESSAGEMESSAGEMESSAGEMESSAGEMESSAGEMESSAGEMESSAGEEND";
  Serial.println("Send to Slave : " + command);
  sendI2c(1, command);
  
  Serial.print("Received by Slave: ");
  Serial.println(readI2C(1));
  delay(0);
}





void sendI2c(int Module, String Message) {
  //divide into substring for sending on I2C Bus(Max 32 Bytes)
  unsigned int StringLength = Message.length();
  int bufferSize = 30;//max bus byte size
  String SubStrings[(int)ceil((double)StringLength /  (double)bufferSize)];
  for (int i = 0; i < (StringLength / bufferSize); i++) {
    String k = Message.substring(i * bufferSize, (i + 1) * bufferSize);
    if (StringLength % bufferSize == 0 && i == (StringLength / bufferSize) - 1) {
      k += "!";
    }
    k += "#";
    SubStrings[i] = k;
  }
  if (StringLength % bufferSize) {
    String k = Message.substring(StringLength - StringLength % bufferSize);
    k += "!#";
    SubStrings[len(SubStrings) - 1] = k;
  }
  for (int i = 0; i < len(SubStrings); i++) {
    Wire.beginTransmission(Module);     //begin transmission with device address of module
    Wire.write((char*) SubStrings[i].c_str());
    Wire.endTransmission();

  }


}


String readI2C(int Module) {
  String i2c_buffer;
  bool awaitCommand = true;
  while (awaitCommand) {
    Wire.beginTransmission(1);     //begin transmission with device address of module
    Wire.requestFrom(1, 64);
    for (int i  = 0; i <= 32; i++) {
      char c = Wire.read(); // adds character to buffer
      if (c == '!') { // break if end pointe
        awaitCommand = false;
      }
      if (c == '#') { // break if end pointer
        break;
      }
      else if (awaitCommand) {
        i2c_buffer += c;
      }
    }
    Wire.endTransmission(1);
  }
  return i2c_buffer;

}






