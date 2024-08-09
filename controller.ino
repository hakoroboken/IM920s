#include<SoftwareSerial.h>

SoftwareSerial IM920Serial(8, 9);

char buf[256];
int i = 0;

void setup() {
  Serial.begin(115200);
  IM920Serial.begin(115200);

  pinMode(10, INPUT);
}

void loop() {
  if(Serial.available())
  {
    buf[i] = Serial.read();
    if (buf[i] == 'e') 
    {
      String read(buf);
      //int si = read.indexOf('s');
      int ei = read.indexOf('e');
      String data = read.substring(1, ei);
      if(digitalRead(10) == LOW)
      {
        IM920Serial.print("TXDU0002,");
        IM920Serial.println(data);
      }
      for(int j = 0; j < 256; j++)
      {
        buf[j] = 0;
      }
      i = 0;
    }
    else
    {
      i++;
    }
  }
}
