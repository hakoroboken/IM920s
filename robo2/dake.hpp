#ifndef DAKE_HPP_
#define DAKE_HPP_

#include <HardwareSerial.h>
// #include<ESP32Servo.h>
// Servo myservo1;

#define y_rate 0.5
#define rotation_rate 0.5

namespace dake
{
  HardwareSerial IM920Serial(0);

  inline void setup(void){
    pinMode(D1, OUTPUT); 
    pinMode(D3, OUTPUT); 
    pinMode(D5, OUTPUT);
    pinMode(D8, OUTPUT);
    // myservo1.attach(D5);

    IM920Serial.begin(115200, SERIAL_8N1, -1, -1);
  }

  inline void L_motor_pwm(int value){
    analogWrite(D0,value);
  }
  inline void R_motor_pwm(int value){
    analogWrite(D2,value);
  }
  inline void L_roller_pwm(int value){
    analogWrite(D4,value);
  }
  inline void R_roller_pwm(int value){
    analogWrite(D10,value);
  }

  inline void L_motor_cw_ccw(int status){
    digitalWrite(D1,status);
  }
  inline void R_motor_cw_ccw(int status){
    digitalWrite(D3,status);
  }
  inline void L_roller_cw_ccw(int status){
    digitalWrite(D5,status);
  }
  inline void R_roller_cw_ccw(int status){
    digitalWrite(D8,status);
  }

  // inline void servo1(int status)
  // {
  //   Serial.println(status);
  //   if(status > 0)
  //   {
  //     myservo1.write(180);
  //   }
  //   else if(status < 0)
  //   {
  //     myservo1.write(90);
  //   }
  // }

  inline void control(int y, int rotation)
  {
    y = y * y_rate;
    rotation = rotation * rotation_rate;

    int L_pwm = y + rotation;
    int R_pwm = -y + rotation;

    if(L_pwm > 0)
    {
      L_motor_cw_ccw(HIGH);
      L_motor_pwm(abs(L_pwm));
    }
    else
    {
      L_motor_cw_ccw(LOW);
      L_motor_pwm(abs(L_pwm));
    }

    if(R_pwm > 0)
    {
      R_motor_cw_ccw(HIGH);
      R_motor_pwm(abs(R_pwm));
    }
    else
    {
      R_motor_cw_ccw(LOW);
      R_motor_pwm(abs(R_pwm));
    }
  }
}
#endif