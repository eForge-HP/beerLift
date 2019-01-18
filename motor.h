#ifndef MOTOR_H
#define MOTOR_H

#include <arduino.h>
#include "config.h"

class Motor{
  public:
    Motor(int8_t enPin, int8_t in1Pin, int8_t in2Pin);
    bool startMotor(bool runDirection, bool slowStart);
    void stopMotor();
    
  private:
    int8_t _enPin;
    int8_t _in1Pin;
    int8_t _in2Pin;
};


#endif /* MOTOR_H */
