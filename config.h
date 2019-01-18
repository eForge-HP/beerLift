#ifndef CONFIG_H
#define CONFIG_H

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Generals */
#define ON                1           // Don't change any of the general settings               
#define OFF               0           //

#define UP                1           
#define DOWN              0

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Pin config */
// Motor controlling
#define MOTOREN1PIN       9
#define MOTORIN1PIN       6
#define MOTORIN2PIN       5

#define MOTOREN2PIN       10
#define MOTORIN3PIN       8
#define MOTORIN4PIN       7

// Switches
#define SAFETYSWITCHPIN   2
#define ENDSWITCHTOPPIN   3
#define ENDSWITCHBOTPIN   4

#define UPBUTTONPIN       12
#define DOWNBUTTONPIN     11

// LED 
#define SAFETYLEDPIN      A0
#define UPLEDPIN          A1
#define DOWNLEDPIN        A2
#define ENDSWITCHTOPLED   A7
#define ENDSWITCHBOTLED   A6

#define BOARDLED          13

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Motor settings */
#define MAXSPEED          255         // max. 255 for PWM

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Button settings */
#define SAFETYSWACTIVE    LOW
#define SAFETYSWINACTIVE  HIGH

#define DIRBUTACTIVE      LOW
#define DIRBUTINACTIVE    HIGH

#define ENDSWACTIVE       LOW
#define ENDSWINACTIVE     HIGH

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Light settings */
#define BLINKTIME         1000        // [ms]

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Serial Settings */
#define SERIALOUT         ON
#define BAUDRATE          9600        // Standard: 9600

////////////////////////////////////////////////////////////////////////////////////////////////////


#endif /* CONFIG_H */
