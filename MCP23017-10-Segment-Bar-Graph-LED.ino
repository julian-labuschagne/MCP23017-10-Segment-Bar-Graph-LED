#include <Wire.h>

int delay_time = 80;

void setup() {

  //Serial.begin(9600);
  Wire.begin();
  
  Wire.beginTransmission(0x20);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // Set all ports on port A to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all ports on port B to outputs
  Wire.endTransmission();

  /** Set all ports on PORTA to LOW **/
  Wire.beginTransmission(0x20);
  Wire.write(0x12);
  Wire.write(0x00);
  Wire.endTransmission();

  /** Set all ports on PORTB to LOW **/
  Wire.beginTransmission(0x20);
  Wire.write(0x13);
  Wire.write(0x00);
  Wire.endTransmission();
  
}

void loop() {

  int potValue = map(analogRead(6), 0, 1023, 0, 10);
  display_bit(potValue);

}

void display_bit(int number) {

  uint8_t bitmask = 0xff;
  uint8_t shift_a;
  uint8_t shift_b;
  
  int value_portb;

  if(number == 0) {
    shift_a = 0x00;
    shift_b = 0x00;
  }
  else if(number > 8) {
    shift_a = 0xff;
    value_portb = (number % 8);
    shift_b = ~(bitmask << value_portb);
  } else {
    shift_a = ~(bitmask << number);
    shift_b = 0x00;
  }
  
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // GPIOA
  Wire.write(shift_a);
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x13); // GPIOB
  Wire.write(shift_b);
  Wire.endTransmission();
  
}

void setLow(int port) {
  Wire.beginTransmission(0x20);
  Wire.write(port);
  Wire.write(0x00);
  Wire.endTransmission();
}
