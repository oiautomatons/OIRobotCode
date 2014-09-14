#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ir_seeker,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          blockPoll,     tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     drive1,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     drive2,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     armMotor,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    blockServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    flagServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
#pragma config(Sensor, S3,     arm_touch,      sensorTouch)

bool alternateDriver = false;


/**
 * Project Name: FTCTeleop
 * Description:  Teleop control program for FTC 2013-2014. Auto startds upon autonomous finish.
 * Version: 2
 *
 * This teleop file was generated using Teleop Catalyst for RobotC Version 1.4 beta on 1/8/2014.
 * Learn more about Teleop Catalyst at: http://ftc.kcastromechs.org/catalyst
 *
 * Feel free to modify this code as much as you'd like, as long as you keep this comment
 * block, in its unaltered form, somewhere in your code. Thanks!
**/

//// Include Files:
#include "JoystickDriver.c";

//// Function Prototypes:
// Initialize function (auto-executed when teleop period begins):
void initialize();

// "Event Handlers" for gamepad 1:
void g1_btn1_t_handler();
void g1_btn2_t_handler();
void g1_btn3_t_handler();
void g1_btn10_c_handler();
void g1_btn9_c_handler();
void g1_btn5_c_handler();
void g1_btn6_c_handler();
void g1_btn7_c_handler();
void g1_btn8_c_handler();

// "Event Handlers" for gamepad 2:
void g2_btn10_c_handler();
void g2_btn1_t_handler();
void g2_btn2_t_handler();
void g2_btn3_t_handler();
void g2_btn9_c_handler();
void g2_btn5_c_handler();
void g2_btn6_c_handler();
void g2_btn7_c_handler();
void g2_btn8_c_handler();

// Execute function(s) for gamepad 1:
void g1_btn1_t_execute();
void g1_btn2_t_execute();
void g1_btn3_t_execute();
void g1_btn10_c_execute();
void g1_btn9_c_execute();
void g1_btn5_c_execute();
void g1_btn6_c_execute();
void g1_btn7_c_execute();
void g1_btn8_c_execute();

// Execute function(s) for gamepad 2:
void g2_btn10_c_execute();
void g2_btn1_t_execute();
void g2_btn2_t_execute();
void g2_btn3_t_execute();
void g2_btn9_c_execute();
void g2_btn5_c_execute();
void g2_btn6_c_execute();
void g2_btn7_c_execute();
void g2_btn8_c_execute();

float deadband(float power);

// Your custom functions:

//// Global Booleans:
// Booleans for Gamepad 1:
bool g1_btn1_toggledOn = false;
bool g1_btn1_flag = false;
bool g1_btn2_toggledOn = false;
bool g1_btn2_flag = false;
bool g1_btn3_toggledOn = false;
bool g1_btn3_flag = false;
bool g1_btn10_flag = false;
bool g1_btn9_flag = false;
bool g1_btn5_flag = false;
bool g1_btn6_flag = false;
bool g1_btn7_flag = false;
bool g1_btn8_flag = false;
// Booleans for Gamepad 2:
bool g2_btn10_flag = false;
bool g2_btn1_toggledOn = false;
bool g2_btn1_flag = false;
bool g2_btn2_toggledOn = false;
bool g2_btn2_flag = false;
bool g2_btn3_toggledOn = false;
bool g2_btn3_flag = false;
bool g2_btn9_flag = false;
bool g2_btn5_flag = false;
bool g2_btn6_flag = false;
bool g2_btn7_flag = false;
bool g2_btn8_flag = false;

/// Joystick values:
float g1_joy1_y1;
float g1_joy1_y2;
float g2_joy1_y1;
float g2_joy1_y2;

/// Variables for driveSwap, slowDown, and deadban features:
float deadbandValue  = 10;   // Deadband is a "neutral zone" where nothing happens.
float slowDownFactor = 1;    // May be used to reduce the speed of the robot/increase sensitivity.
float joySwap = 1;           // May be used to swap the driving direction of the robot. 1 means forward = forward, -1 means forward = backwards

task main()
{
   initialize();   // Run the initialization code.

   while (true)
   {
      getJoystickSettings(joystick);

      if (!joystick.StopPgm && joystick.UserMode)
      {
         g1_btn1_t_handler();
         g1_btn2_t_handler();
         g1_btn3_t_handler();
         g1_btn10_c_handler();
         g1_btn9_c_handler();
         g1_btn5_c_handler();
         g1_btn6_c_handler();
         g1_btn7_c_handler();
         g1_btn8_c_handler();
         g2_btn10_c_handler();
         g2_btn1_t_handler();
         g2_btn2_t_handler();
         g2_btn3_t_handler();
         g2_btn9_c_handler();
         g2_btn5_c_handler();
         g2_btn6_c_handler();
         g2_btn7_c_handler();
         g2_btn8_c_handler();

         // Update variables with joystick values:
         g1_joy1_y1 = joystick.joy1_y1;
         g1_joy1_y2 = joystick.joy1_y2;
         g2_joy1_y1 = joystick.joy2_y1;
         g2_joy1_y2 = joystick.joy2_y2;

         // Update the power of the drive motors with that of the joystick values:
if (alternateDriver == false) {
   motor[drive1] = (deadband(g1_joy1_y2/slowDownFactor)*joySwap);
   motor[drive2] = (deadband(g1_joy1_y1/slowDownFactor)*joySwap);
}
else {
   motor[drive1] = (deadband(g2_joy1_y2/slowDownFactor)*joySwap);
   motor[drive2] = (deadband(g2_joy1_y1/slowDownFactor)*joySwap);
}
      }
   }
}

void initialize()
{
   /*
      Everything in here is executed at the beginning of the teleop period.
      When the music plays, this stuff happens!
   */

   nMotorEncoder[drive1] = 0;
nMotorEncoder[drive2] = 0;
servo[flagServo] = 65;

//slowDownFactor = 1.00;  // 100%
//slowDownFactor = 1.11;  // 90%
//slowDownFactor = 1.25;  // 80%
//slowDownFactor = 1.43;  // 70%
//slowDownFactor = 1.67;  // 60%
//slowDownFactor = 2.00;  // 50%
//slowDownFactor = 2.50;  // 40%
//slowDownFactor = 3.33;  // 30%
slowDownFactor = 4.00;  // 25%
//slowDownFactor = 5.00;  // 20%
//slowDownFactor = 10.0;  // 10%

#ifdef COPY_N_PASTE_FOR_2WAY_DRIVING
if (alternateDriver == false) {
   motor[drive1] = (deadband(g1_joy1_y2/slowDownFactor)*joySwap);
   motor[drive2] = (deadband(g1_joy1_y1/slowDownFactor)*joySwap);
}
else {
   motor[drive1] = (deadband(g2_joy1_y2/slowDownFactor)*joySwap);
   motor[drive2] = (deadband(g2_joy1_y1/slowDownFactor)*joySwap);
}
#endif

}

float deadband(float power) {
   if (abs(power) < deadbandValue) {
      return 0;
   } else {
      return power;
   }
}




void g1_btn1_t_handler()
{
   if (joy1Btn(1)) {
      g1_btn1_flag = true;
   } else if (g1_btn1_flag) {
      g1_btn1_flag = false;
      if (g1_btn1_toggledOn) {
         g1_btn1_toggledOn = false;
      } else {
         g1_btn1_toggledOn = true;
      }
      g1_btn1_t_execute();
   }
}

void g1_btn2_t_handler()
{
   if (joy1Btn(2)) {
      g1_btn2_flag = true;
   } else if (g1_btn2_flag) {
      g1_btn2_flag = false;
      if (g1_btn2_toggledOn) {
         g1_btn2_toggledOn = false;
      } else {
         g1_btn2_toggledOn = true;
      }
      g1_btn2_t_execute();
   }
}

void g1_btn3_t_handler()
{
   if (joy1Btn(3)) {
      g1_btn3_flag = true;
   } else if (g1_btn3_flag) {
      g1_btn3_flag = false;
      if (g1_btn3_toggledOn) {
         g1_btn3_toggledOn = false;
      } else {
         g1_btn3_toggledOn = true;
      }
      g1_btn3_t_execute();
   }
}

void g1_btn10_c_handler()
{
   if (joy1Btn(10)) {
      g1_btn10_c_execute();
      g1_btn10_flag = true;
   } else if (g1_btn10_flag) {

      g1_btn10_flag = false;
   }
}

void g1_btn9_c_handler()
{
   if (joy1Btn(9)) {
      g1_btn9_c_execute();
      g1_btn9_flag = true;
   } else if (g1_btn9_flag) {

      g1_btn9_flag = false;
   }
}

void g1_btn5_c_handler()
{
   if (joy1Btn(5)) {
      g1_btn5_c_execute();
      g1_btn5_flag = true;
   } else if (g1_btn5_flag) {
      motor[armMotor] = 0;
      g1_btn5_flag = false;
   }
}

void g1_btn6_c_handler()
{
   if (joy1Btn(6)) {
      g1_btn6_c_execute();
      g1_btn6_flag = true;
   } else if (g1_btn6_flag) {
      motor[armMotor] = 0;
      g1_btn6_flag = false;
   }
}

void g1_btn7_c_handler()
{
   if (joy1Btn(7)) {
      g1_btn7_c_execute();
      g1_btn7_flag = true;
   } else if (g1_btn7_flag) {
      motor[flagMotor] = 0;
      g1_btn7_flag = false;
   }
}

void g1_btn8_c_handler()
{
   if (joy1Btn(8)) {
      g1_btn8_c_execute();
      g1_btn8_flag = true;
   } else if (g1_btn8_flag) {
      motor[flagMotor] = 0;
      g1_btn8_flag = false;
   }
}

void g2_btn10_c_handler()
{
   if (joy2Btn(10)) {
      g2_btn10_c_execute();
      g2_btn10_flag = true;
   } else if (g2_btn10_flag) {

      g2_btn10_flag = false;
   }
}

void g2_btn1_t_handler()
{
   if (joy2Btn(1)) {
      g2_btn1_flag = true;
   } else if (g2_btn1_flag) {
      g2_btn1_flag = false;
      if (g2_btn1_toggledOn) {
         g2_btn1_toggledOn = false;
      } else {
         g2_btn1_toggledOn = true;
      }
      g2_btn1_t_execute();
   }
}

void g2_btn2_t_handler()
{
   if (joy2Btn(2)) {
      g2_btn2_flag = true;
   } else if (g2_btn2_flag) {
      g2_btn2_flag = false;
      if (g2_btn2_toggledOn) {
         g2_btn2_toggledOn = false;
      } else {
         g2_btn2_toggledOn = true;
      }
      g2_btn2_t_execute();
   }
}

void g2_btn3_t_handler()
{
   if (joy2Btn(3)) {
      g2_btn3_flag = true;
   } else if (g2_btn3_flag) {
      g2_btn3_flag = false;
      if (g2_btn3_toggledOn) {
         g2_btn3_toggledOn = false;
      } else {
         g2_btn3_toggledOn = true;
      }
      g2_btn3_t_execute();
   }
}

void g2_btn9_c_handler()
{
   if (joy2Btn(9)) {
      g2_btn9_c_execute();
      g2_btn9_flag = true;
   } else if (g2_btn9_flag) {

      g2_btn9_flag = false;
   }
}

void g2_btn5_c_handler()
{
   if (joy2Btn(5)) {
      g2_btn5_c_execute();
      g2_btn5_flag = true;
   } else if (g2_btn5_flag) {
      motor[armMotor] = 0;
      g2_btn5_flag = false;
   }
}

void g2_btn6_c_handler()
{
   if (joy2Btn(6)) {
      g2_btn6_c_execute();
      g2_btn6_flag = true;
   } else if (g2_btn6_flag) {
      motor[armMotor] = 0;
      g2_btn6_flag = false;
   }
}

void g2_btn7_c_handler()
{
   if (joy2Btn(7)) {
      g2_btn7_c_execute();
      g2_btn7_flag = true;
   } else if (g2_btn7_flag) {
      motor[flagMotor] = 0;
      g2_btn7_flag = false;
   }
}

void g2_btn8_c_handler()
{
   if (joy2Btn(8)) {
      g2_btn8_c_execute();
      g2_btn8_flag = true;
   } else if (g2_btn8_flag) {
      motor[flagMotor] = 0;
      g2_btn8_flag = false;
   }
}

void g1_btn1_t_execute()
{
   if (g1_btn1_toggledOn)
   {
      int val = ServoValue[blockServo];
if (val != 127) servo[blockServo] = 127;
else servo[blockServo] = 255;
   }
   else
   {
      int val = ServoValue[blockServo];
if (val != 127) servo[blockServo] = 127;
else servo[blockServo] = 255;
   }
}

void g1_btn2_t_execute()
{
   if (g1_btn2_toggledOn)
   {
      int val = ServoValue[flagServo];
if (val != 65) servo[flagServo] = 65;
else servo[flagServo] = 0;
   }
   else
   {
      int val = ServoValue[flagServo];
if (val != 65) servo[flagServo] = 65;
else servo[flagServo] = 0;
   }
}

void g1_btn3_t_execute()
{
   if (g1_btn3_toggledOn)
   {
      nVolume = 4;
if (slowDownFactor != 2.0) {
  slowDownFactor = 2.0;
  PlaySound(soundBeepBeep);
}
else {
  slowDownFactor = 4.0;
  PlaySound(soundLowBuzz);
}
   }
   else
   {
      nVolume = 4;
if (slowDownFactor != 2.0) {
  slowDownFactor = 2.0;
  PlaySound(soundBeepBeep);
}
else {
  slowDownFactor = 4.0;
  PlaySound(soundLowBuzz);
}
   }
}

void g1_btn10_c_execute()
{
   alternateDriver = true;
}

void g1_btn9_c_execute()
{
   alternateDriver = false;
}

void g1_btn5_c_execute()
{
   if (SensorValue[arm_touch] == 0) {
motor[armMotor] = 95;
}else{
motor[armMotor] = 0;}
}

void g1_btn6_c_execute()
{
   motor[armMotor] = -95;
}

void g1_btn7_c_execute()
{
   motor[flagMotor] = 95;
}

void g1_btn8_c_execute()
{
   motor[flagMotor] = -95;
}

void g2_btn10_c_execute()
{
   alternateDriver = true;
}

void g2_btn1_t_execute()
{
   if (g2_btn1_toggledOn)
   {
      int val = ServoValue[blockServo];
if (val != 127) servo[blockServo] = 127;
else servo[blockServo] = 255;
   }
   else
   {
      int val = ServoValue[blockServo];
if (val != 127) servo[blockServo] = 127;
else servo[blockServo] = 255;
   }
}

void g2_btn2_t_execute()
{
   if (g2_btn2_toggledOn)
   {
      int val = ServoValue[flagServo];
if (val != 65) servo[flagServo] = 65;
else servo[flagServo] = 0;
   }
   else
   {
      int val = ServoValue[flagServo];
if (val != 65) servo[flagServo] = 65;
else servo[flagServo] = 0;
   }
}

void g2_btn3_t_execute()
{
   if (g2_btn3_toggledOn)
   {
      nVolume = 4;
if (slowDownFactor != 2.0) {
  slowDownFactor = 2.0;
  PlaySound(soundBeepBeep);
}
else {
  slowDownFactor = 4.0;
  PlaySound(soundLowBuzz);
}
   }
   else
   {
      nVolume = 4;
if (slowDownFactor != 2.0) {
  slowDownFactor = 2.0;
  PlaySound(soundBeepBeep);
}
else {
  slowDownFactor = 4.0;
  PlaySound(soundLowBuzz);
}
   }
}

void g2_btn9_c_execute()
{
   alternateDriver = false;
}

void g2_btn5_c_execute()
{
   if (SensorValue[arm_touch] == 0) {
motor[armMotor] = 95;
}else{
motor[armMotor] = 0;}
}

void g2_btn6_c_execute()
{
   motor[armMotor] = -95;
}

void g2_btn7_c_execute()
{
   motor[flagMotor] = 95;
}

void g2_btn8_c_execute()
{
   motor[flagMotor] = -95;
}

// That's it! Enjoy, and good luck! :)
