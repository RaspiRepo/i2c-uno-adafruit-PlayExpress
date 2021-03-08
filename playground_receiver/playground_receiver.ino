#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>

#define I2C_ADDRESS 0X1F

int cmd_type = 0;

//On Receive callback function 
void receiveEvent(int numBytes)
{
  cmd_type = Wire.read();
  Serial.println(cmd_type);
}


void setup() {
  CircuitPlayground.begin();
  Serial.begin(115200);  
  Wire.begin(I2C_ADDRESS); 
  Wire.onReceive(receiveEvent); // register callback to receive data on i2 bus
}

void loop() {
  switch (cmd_type) {
    case 0:
      CircuitPlayground.redLED(LOW);
      break;
    case 1:
      CircuitPlayground.redLED(HIGH);
      delay(100);
      break;  
    default:
      Serial.println("No Action");
      break;
  }
  
  delay(10);
}
