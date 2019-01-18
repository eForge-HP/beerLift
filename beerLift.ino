////////////////////////////////////////////////////////////////////////////////////////////////////
/*  Project:        liftControl
 *  Author:         Hendrik P.
 *  Date:           2019-01-10
 *  Version:        0.1
 *  Add. Libs:      NONE
 *  License:        CC-BY-NC-SA
 *  
 *  Summary:        This is a firmware for the liftControlBoard, which is also designed by 
 *                  Hendrik P. This Firmware works statewise. The states are SAFESTATE, WAITSTATE                  
 *                  and DRIVESTATE (upwards or downwards). Everything is indicated by Lights.
 *                  SAFESTATE: The safety light is blinking. Press both direction buttons to go to 
 *                  the waitstate.Can be entered everytime by pressing the safety button.
 *                  WAITSTATE: The possible buttons are constantly lit up.
 *                  DRIVESTATE: The drive direction is shown with a blinking direction button, while
 *                  the opposite button is off.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include "motor.h"
#include "light.h"

Motor motor(MOTOREN1PIN, MOTORIN1PIN, MOTORIN2PIN);

Light safetyLight(SAFETYLEDPIN);
Light upwardsLight(UPLEDPIN);
Light downwardsLight(DOWNLEDPIN);
Light endSwitchTopLight(ENDSWITCHTOPLED);
Light endSwitchBotLight(ENDSWITCHBOTLED);
Light testLight(BOARDLED);

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
  #if SERIALOUT
    Serial.begin(BAUDRATE);
    Serial.println("Liftcontrol v0.1");
    Serial.println("by Hendrik P. \n");
  #endif
  pinMode(SAFETYSWITCHPIN, INPUT);
  pinMode(ENDSWITCHTOPPIN, INPUT);
  pinMode(ENDSWITCHBOTPIN, INPUT);
  pinMode(UPBUTTONPIN, INPUT);
  pinMode(DOWNBUTTONPIN, INPUT);
}

void loop(){
  if(digitalRead(SAFETYSWITCHPIN) == SAFETYSWACTIVE){
    // Safestate of the lift system
    #if SERIALOUT
      Serial.println("Entered Safestate!");
    #endif
    while(digitalRead(UPBUTTONPIN) == DIRBUTINACTIVE || digitalRead(DOWNBUTTONPIN) == DIRBUTINACTIVE){
      safetyLight.blinkLight(BLINKTIME);
      upwardsLight.turnOff();
      downwardsLight.turnOff();
      endSwitchLight();
    }
    safetyLight.turnOn();
    #if SERIALOUT
      Serial.println("Left Safestate.");
    #endif
    delay(500);
  }else{
    safetyLight.turnOn();
    endSwitchLight();
    driveDirectionLight();
    // Upwards drive
    if(startDriveCheck(UP)){
      #if SERIALOUT
        Serial.println("Driving Upwards.");
      #endif
      while(driveClearance(UP)){
        drive(UP);
        endSwitchLight();
      }
      stopDrive();
      #if SERIALOUT
        Serial.println("Ended driving");
      #endif
    }
    // Downwards drive
    if(startDriveCheck(DOWN)){
      #if SERIALOUT
        Serial.println("Driving Downwards.");
      #endif
      while(driveClearance(DOWN)){
        drive(DOWN);
        endSwitchLight();
      }
      stopDrive();
      #if SERIALOUT
        Serial.println("Ended driving");
      #endif
    }
  }  
  
}
////////////////////////////////////////////////////////////////////////////////////////////////////


void drive(bool driveDirection){
  motor.startMotor(driveDirection, OFF);
  if(driveDirection == UP){
    upwardsLight.blinkLight(BLINKTIME);
    downwardsLight.turnOff();
  }else{
    downwardsLight.blinkLight(BLINKTIME);
    upwardsLight.turnOff();
  }
  safetyLight.turnOn();
}

bool driveClearance(bool driveDirection){
  bool clearance = false;
  if(driveDirection == UP){
    if(digitalRead(ENDSWITCHTOPPIN) == ENDSWINACTIVE){
      clearance = true;
    }
  }else{
    if(digitalRead(ENDSWITCHBOTPIN) == ENDSWINACTIVE){
      clearance = true;
    }
  }
  if(digitalRead(SAFETYSWITCHPIN) == SAFETYSWACTIVE){
    clearance = false;
  }
  return clearance;
}

bool startDriveCheck(bool driveDirection){
  bool clearance = false;
  if(driveDirection == UP){
    clearance = digitalRead(UPBUTTONPIN)==DIRBUTACTIVE && digitalRead(ENDSWITCHTOPPIN)==ENDSWINACTIVE;
  }else{
    clearance = digitalRead(DOWNBUTTONPIN)==DIRBUTACTIVE && digitalRead(ENDSWITCHBOTPIN)==ENDSWINACTIVE;
  }
  return clearance;
}

void stopDrive(){
  motor.stopMotor();
  if(digitalRead(ENDSWITCHTOPPIN) ==  ENDSWACTIVE){
    endSwitchTopLight.turnOn();
    downwardsLight.turnOn();
    upwardsLight.turnOff();
  }else if(digitalRead(ENDSWITCHBOTLED) == ENDSWACTIVE){
    endSwitchBotLight.turnOn();
    downwardsLight.turnOff();
    upwardsLight.turnOn();
  }else{
    upwardsLight.turnOn();
    downwardsLight.turnOn();
  }
}


void endSwitchLight(){
  if(digitalRead(ENDSWITCHTOPPIN) ==  ENDSWACTIVE){
    endSwitchTopLight.turnOn();
  }else{
    endSwitchTopLight.turnOff();
  }
  if(digitalRead(ENDSWITCHBOTPIN) ==  ENDSWACTIVE){
    endSwitchBotLight.turnOn();
  }else{
    endSwitchBotLight.turnOff();
  }
}


void driveDirectionLight(){
  if(digitalRead(ENDSWITCHTOPPIN) ==  ENDSWACTIVE){
    upwardsLight.turnOff();
  }else{
    upwardsLight.turnOn();
  }
  if(digitalRead(ENDSWITCHBOTPIN) ==  ENDSWACTIVE){
    downwardsLight.turnOff();
  }else{
    downwardsLight.turnOn();
  }
}

