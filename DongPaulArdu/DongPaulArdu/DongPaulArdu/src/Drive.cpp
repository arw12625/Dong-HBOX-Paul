/*
 * drive.cpp
 *
 * Created: 10/5/2017 5:43:09 PM
 *  Author: Andrew_2
 */ 

#include "Arduino.h"
#include "Drive.h"
#include "Message.h"

#define CS_THRESHOLD 100

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

bool driveEna = false;

unsigned int driveDirect[2] = {3, 3};
unsigned int drivePWM[2] = {0, 0};

void writeDrive(void);

void initDrive(void) {
	for(int motor = 0; motor <= 1; motor++) {
		pinMode(inApin[motor], OUTPUT);
		pinMode(inBpin[motor], OUTPUT);
		pinMode(pwmpin[motor], OUTPUT);
	}
	brakeDrive();
	driveEna = true;
}

void updateDrive(void) {
	
	if ((analogRead(cspin[0]) < CS_THRESHOLD) && (analogRead(cspin[1]) < CS_THRESHOLD)) {
		//current in range
	}
	else {
		driveEna = false;
	}
	
	if(driveEna) {
		writeDrive();
	} else {
		brakeDrive();
	}
}



void writeDrive(void) {

	for(int motor = 0; motor <= 1; motor++) {
		// Set inA[motor]
		if (driveDirect[motor] == 0 || driveDirect[motor] == 1) {
			digitalWrite(inApin[motor], HIGH);
		} else {
			digitalWrite(inApin[motor], LOW);
		}
		
		// Set inB[motor]
		if (driveDirect[motor] == 0 || driveDirect[motor] == 2) {
			digitalWrite(inBpin[motor], HIGH);
		} else {
			digitalWrite(inBpin[motor], LOW);
		}
		
		// Write PWM
		analogWrite(pwmpin[motor], drivePWM[motor]);
		
	}
}

void setDriveMotor(unsigned int motor, unsigned int direct, uint16_t pwm) {
	if (motor <= 1 && direct <=4 && pwm <= 1023) {
		driveDirect[motor] = direct;
		drivePWM[motor] = pwm;
	}
}

void brakeDrive() {
	setDriveMotor(DRIVE_MOTOR_LEFT, DRIVE_BRAKEGND, 0);
	setDriveMotor(DRIVE_MOTOR_RIGHT, DRIVE_BRAKEGND, 0);
	writeDrive();
}

void enableDrive(bool ena) {
	driveEna = ena;
}