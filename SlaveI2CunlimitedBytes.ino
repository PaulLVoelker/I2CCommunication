#define len(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))// number of items in an array
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


String i2c_buffer;
void receiveEvent(int howMany)
{
  //keep on searching and appending to i2c_buffer until "!#" is found
  bool awaitCommand = true;
  while (0 < Wire.available() && awaitCommand) {
    for (int i  = 0; i <= 32; i++) {
      char c = Wire.read(); // adds character to buffer
      if (c == '!') { // break if end pointe
        awaitCommand = false;
      }
      if (c == '#') { // break if end pointe
        break;
      }
      else if (awaitCommand) {
        i2c_buffer += c;
      }
    }
  }
  //reset i2c_buffer
  if (!awaitCommand) {
    Serial.print("Received by Master: ");
    Serial.println(i2c_buffer);
    i2c_buffer = "";
  }
}


unsigned int requestCount = 0;
void requestEvent() {
  String Message = "TestTTestTTestTTestTTestTTestTTestTTestTTEND";
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
  // write substring according to count call
  Serial.print("Send to Master(will be appended later): ");
  Serial.println(SubStrings[requestCount]);
  Wire.write((char*) SubStrings[requestCount].c_str());
  requestCount++;
  //reset counter
  if ( requestCount == len(SubStrings) ) {
    requestCount = 0;
  }

}
