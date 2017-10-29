/*
 * Control.cpp
 *
 * Created: 10/5/2017 7:42:56 PM
 *  Author: Andrew_2
 */ 

#include "Control.h"
#include "Drive.h"
#include "Message.h"
#include "Sweeper.h"
#include "Arduino.h"

bool controlEna = false;

int driveInput[2] = {0,0};
unsigned char sweeperInput[1] = {0};
	
#define  WATCHDOG_TIMEOUT 500
unsigned long watchdogTimer;
	
#define BYTES_TO_INT(val, offset) (int)(((unsigned int)val[offset] << 8) | (val[offset + 1]))
#define CLAMP(val, minval, maxval) (val > maxval) ? maxval : ((val < minval) ? minval : val)

const unsigned int CONTROL_DRIVE_MOTOR[2] =  {DRIVE_MOTOR_LEFT, DRIVE_MOTOR_RIGHT};
const unsigned int FORWARD_DIRECT[2]  = {DRIVE_CW, DRIVE_CCW}; //relative to control numbering
const unsigned int BACKWARD_DIRECT[2] = {DRIVE_CCW, DRIVE_CW}; //relative to control numbering
#define CONTROL_DRIVE_DEADBAND 5

void initControl(void) {
	controlEna = true;
	watchdogTimer = millis();
}

void updateControl(void) {
	if(millis() - watchdogTimer > WATCHDOG_TIMEOUT) {
		
		sweeperInput[0] = 0;
		driveInput[0] = 0;
		driveInput[1] = 0;
		
	} 
	if(controlEna) {
		for(int i = 0; i <= 1; i++) {
			int motor = CONTROL_DRIVE_MOTOR[i];
			if(driveInput[i] < -CONTROL_DRIVE_DEADBAND) {
				setDriveMotor(motor,  BACKWARD_DIRECT[i], abs(driveInput[i]));
			} else if(driveInput[i] > CONTROL_DRIVE_DEADBAND)  {
				setDriveMotor(motor,  FORWARD_DIRECT[i], abs(driveInput[i]));
			} else {
				setDriveMotor(motor, DRIVE_BRAKEGND, 0);
			}
		}
		setSweepDir(sweeperInput[0]);
	}
}

void enableControl(bool ena) {
	controlEna = ena;
}

void parseControlMessage(unsigned char *data, unsigned char len) {
	if(data[0] == 'c' && len == 6) {
		watchdogTimer = millis();
		pinMode(A5, OUTPUT);
		digitalWrite(A5, HIGH);
		
		controlEna = (bool)data[1];
		driveInput[0] = CLAMP(BYTES_TO_INT(data, 2), -DRIVE_MAX, DRIVE_MAX);
		driveInput[1] = CLAMP(BYTES_TO_INT(data, 4), -DRIVE_MAX, DRIVE_MAX);
	} else if(data[0] == 's' && len == 3) {
		watchdogTimer = millis();
		controlEna = (bool)data[1];
		sweeperInput[0] = data[2];
	}
}