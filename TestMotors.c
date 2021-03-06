#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ir_seeker,      sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     arm_touch,      sensorTouch)
#pragma config(Motor,  motorA,          blockPoll,     tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     drive1,        tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     drive2,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     armMotor,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    blockServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    flagServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

#define PID_CONTROL			(false) // Proportional, Integral, and Derivative
#define DRIVE_POWER_FL	(40)
#define DRIVE_POWER_FR	(35)
#define DRIVE_POWER_RL	(40)
#define DRIVE_POWER_RR	(33)


#define PI							(3.14159)
#define WHEEL_BASE			(13.75)
#define WHEEL_DIAM			(4)
#define TICKS_PER_ROTATION	(1440.0)
#define TICKS_PER_INCH	(TICKS_PER_ROTATION/(WHEEL_DIAM*PI))
#define FORWARD					(1)
#define REVERSE					(-1)
#define ADJ_YES					(true)
#define ADJ_NO					(false)


void startRobot() {
	disableDiagnosticsDisplay();

	if (PID_CONTROL == true) {
		nPidUpdateInterval = 20; // default is 25ms
		nMotorPIDSpeedCtrl[drive1] = mtrSpeedReg; // mtrSpeedReg or mtrNoReg
		nMotorPIDSpeedCtrl[drive2] = mtrSpeedReg; // mtrSpeedReg or mtrNoReg
	}

	nMotorEncoder[drive1] = 0;
	nMotorEncoder[drive2] = 0;
	motor[drive1] = 0;
	motor[drive2] = 0;
	wait1Msec(100);
	return;
}

int inchesToTicks(float inches) {
	int ticks = inches * TICKS_PER_INCH;
	return ticks;
}

float ticksToInches(int ticks) {
	float inches = ticks / TICKS_PER_INCH;
	return inches;
}

void metricsDisplay(int ticksLeft, int ticksRight) {
	eraseDisplay();
	nxtDisplayTextLine(0, "d1=%.02f %d", ticksToInches(nMotorEncoder[drive1]), nMotorEncoder[drive1]);
	nxtDisplayTextLine(1, "in=%.02f %d", ticksToInches(ticksRight), ticksRight);
	nxtDisplayTextLine(3, "d2=%.02f %d", ticksToInches(nMotorEncoder[drive2]), nMotorEncoder[drive2]);
	nxtDisplayTextLine(4, "in=%.02f %d", ticksToInches(ticksLeft), ticksLeft);
	nxtDisplayTextLine(6, "FL=%d FR=%d", DRIVE_POWER_FL, DRIVE_POWER_FR);
	nxtDisplayTextLine(7, "RL=%d RR=%d", DRIVE_POWER_RL, DRIVE_POWER_RR);
	return;
}

void driveDistance(float inches, int direction, bool adjustDistance) {
	int ticksLeft, ticksRight;
	static int deltaLeft = 0, deltaRight = 0;

	ticksLeft = inchesToTicks(inches);
	ticksRight = inchesToTicks(inches);
	if (adjustDistance == ADJ_YES) {
		ticksLeft -= deltaLeft;
		ticksRight -= deltaRight;
	}
	nMotorEncoder[drive1] = 0;
	nMotorEncoder[drive2] = 0;

	if (PID_CONTROL == false) {
		if (direction == FORWARD) {
			motor[drive1] = DRIVE_POWER_FR * direction;
			motor[drive2] = DRIVE_POWER_FL * direction;
		}
		else {
			motor[drive1] = DRIVE_POWER_RR * direction;
			motor[drive2] = DRIVE_POWER_RL * direction;
		}
		while (true) {
			if (abs(nMotorEncoder[drive1]) >= ticksRight) break;
			if (abs(nMotorEncoder[drive2]) >= ticksLeft) break;
		}
	}
	else {
		nMotorEncoderTarget[drive1] = ticksRight * direction;
		nMotorEncoderTarget[drive2] = ticksLeft * direction;
		motor[drive1] = DRIVE_POWER_FR * direction;
		motor[drive2] = DRIVE_POWER_FL * direction;
		while (true) {
			TNxtRunState state1, state2;
			// 0 = runStateIdle
			// 1 = runStateHoldPosition
			// 16 = runStateRampUp
			// 32 = runStateRunning
			// 64 = runStateRampDown
			state1 = nMotorRunState[drive1];
			state2 = nMotorRunState[drive2];
			if (state1 == runStateIdle || state2 == runStateIdle) break;
		}
	}

	motor[drive1] = 0;
	motor[drive2] = 0;
	metricsDisplay(ticksLeft, ticksRight);
	deltaLeft = nMotorEncoder[drive2] - ticksLeft;
	deltaRight = nMotorEncoder[drive1] - ticksRight;
	nMotorEncoder[drive1] = 0;
	nMotorEncoder[drive2] = 0;
	wait1Msec(100);
	return;
}

task main() {
	startRobot();
	waitForStart();

	driveDistance(75.0, FORWARD, ADJ_NO);
	wait1Msec(10000);
	driveDistance(75.0, REVERSE, ADJ_NO);
	wait1Msec(10000);
}
