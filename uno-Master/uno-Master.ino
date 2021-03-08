#include <Wire.h>
#define SLAVE_ADDRESS 0X1F
const int buttonPin = 7; //Push button port

int LED_ON      = 0;
int buttonState = 0;

void setup()
{
  Serial.begin(115200);
  Wire.begin();     
  Wire.setClock(10000); //set i2c clock freq
  delay(1000);
    
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void send_value (int value)
{
  Wire.beginTransmission(SLAVE_ADDRESS); 
  Wire.write(value);            
  int error = Wire.endTransmission(); 
  if (error != 0) { 
    Serial.print("data send status ");
    Serial.println(error);
  }
}


void loop()
{
   buttonState = digitalRead(buttonPin);

  //send value only when if there is a change from 
  //previous state. i.e if LED already ON do need to write anything 
  //to slave device
  if (buttonState == HIGH && LED_ON == 0) {
    LED_ON = 1;
    send_value(1);
    Serial.println("LED ON");
  } else if (LED_ON == 1) {
    LED_ON = 0;
    send_value(0);
    Serial.println("LED OFF");
  }
  delay(100);
}
