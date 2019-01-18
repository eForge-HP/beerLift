#include "motor.h"

Motor::Motor(int8_t enPin, int8_t in1Pin, int8_t in2Pin){
  this->_enPin = enPin;
  this->_in1Pin = in1Pin;
  this->_in2Pin = in2Pin;
  pinMode(_enPin, OUTPUT);
  pinMode(_in1Pin, OUTPUT);
  pinMode(_in2Pin, OUTPUT);
}


bool Motor::startMotor(bool runDirection, bool slowStart){
  int8_t motorSpeed = 255;
  bool maxSpeedReached = false;
  #if MAXSPEED < 256
    motorSpeed = MAXSPEED;
  #else
    #error MAXSPEED is to high!
  #endif
  if(runDirection == UP){
    digitalWrite(_in1Pin, HIGH);
    digitalWrite(_in2Pin, LOW);
  }else{
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_in2Pin, HIGH);
  }
  if(slowStart){
    
  }else{
    maxSpeedReached = true;
  }
  analogWrite(_enPin, motorSpeed);
  return maxSpeedReached;
}


void Motor::stopMotor(){
  analogWrite(_enPin, 0);
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
}

