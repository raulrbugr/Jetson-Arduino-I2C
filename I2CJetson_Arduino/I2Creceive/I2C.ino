#include <Wire.h>


#define TCAADDR 0x70

int clockSpeed = 100000;
char myOutput[32] = {0};
char sent[32] = {0};

void setup() {
  digitalWrite(6, HIGH);
  Wire.begin(0x04);
  Wire.setClock(clockSpeed);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  tcaselect(1);
}

void loop() {
  delay(100);
  Serial.println(myOutput);
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

/*
 * Receive 
 */
void receiveEvent() {
  char c[32] = {0};
  int count = 0;
  while (0 < Wire.available()) {
    c[count] = Wire.read();
    Serial.print(c[count]);
    count++;
  }
  Serial.println();
  strncpy(myOutput, c, 32);
}

/*
 * Send 
 */
void send(char c[]) {
  Wire.beginTransmission(0x40);
  Serial.print("Sending signal:\t");
  Wire.write(c);
  Serial.print(c);
  Serial.println();
  Wire.endTransmission();
}
