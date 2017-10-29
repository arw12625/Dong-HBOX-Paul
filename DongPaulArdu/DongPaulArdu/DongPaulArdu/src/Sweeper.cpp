/*
 * Sweeper.cpp
 *
 * Created: 10/25/2017 11:15:37 AM
 *  Author: Andrew_2
 */ 
#include "Sweeper.h"
#include "Arduino.h"

#define SWEEPER_IN_DIR LOW
#define SWEEPER_OUT_DIR HIGH
#define SWEEPER_ENABLE LOW
#define SWEEPER_DISABLE HIGH

int dirPin = 10;
int enaPin = 12;
unsigned char dir = SWEEPER_OFF; // direction of sweeper

void initSweeper(void) {
	pinMode(dirPin, OUTPUT);
	pinMode(enaPin, OUTPUT);
	digitalWrite(dirPin, SWEEPER_IN_DIR);
	digitalWrite(enaPin, SWEEPER_DISABLE);
}

void updateSweeper(void) {
	if(dir == SWEEPER_OFF) {
		digitalWrite(enaPin, SWEEPER_DISABLE);
	} else {
		digitalWrite(enaPin, SWEEPER_ENABLE);
	}
	
	if(dir == SWEEPER_IN) {
		digitalWrite(dirPin, SWEEPER_IN_DIR);
	} else if(dir == SWEEPER_OUT) {
		digitalWrite(dirPin, SWEEPER_OUT_DIR);
	}
}

void setSweepDir(unsigned char newDir) {
	dir = newDir;
}

/*
#include "Sweeper.h"
#include "Stepper.h"

// change this to the number of steps on your motor
#define STEPS 48
#define STEPS_PER_UPDATE 4

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 10, 11, 12, 13);

unsigned char speed = 80; // speed of sweeper, skips steps if too fast
unsigned char dir = SWEEPER_OFF; // direction of sweeper

void initSweeper(void) {
	stepper.setSpeed(speed);
} 

void updateSweeper(void) {
	if(dir == SWEEPER_IN) {
		stepper.step(STEPS_PER_UPDATE);
	} else if (dir == SWEEPER_OUT) {
		stepper.step(-STEPS_PER_UPDATE);
	}
}

void setSweepSpeed(int newSpeed) {
	speed = newSpeed;
	stepper.setSpeed(speed);
}

void setSweepDir(unsigned char newDir) {
	dir = newDir;
}
*/