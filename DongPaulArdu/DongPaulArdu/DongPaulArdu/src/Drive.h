/*
 * drive.h
 *
 * Created: 10/5/2017 5:42:54 PM
 *  Author: Andrew_2
 */ 

#ifndef DRIVE_H_
#define DRIVE_H_

#define DRIVE_MOTOR_LEFT 0
#define DRIVE_MOTOR_RIGHT 1

#define DRIVE_BRAKEVCC 0
#define DRIVE_CW   1
#define DRIVE_CCW  2
#define DRIVE_BRAKEGND 3

#define DRIVE_MAX 1023

void initDrive(void);
void updateDrive(void);

void setDriveMotor(unsigned int motor, unsigned int direct, unsigned int pwm);
void brakeDrive();

void enableDrive(bool ena);

#endif /* DRIVE_H_ */