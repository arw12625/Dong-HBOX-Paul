#include <Arduino.h>

#include "Config.h"
#include "TimeUtil.h"
#include "Comm.h"
#include "Message.h"
#include "Control.h"
#include "Drive.h"
#include "Sweeper.h"

void setup() {
	initTime();
	initComm();
	initMessage();
	initControl();
	initDrive();
	initSweeper();
}

void loop() {
	if((millis()-timer) >= MAIN_LOOP_TIME) {
		updateTime();
		updateComm();
		updateMessage();
		updateControl();
		updateDrive();
		updateSweeper();
	}
}

void kill() {
	enableDrive(false);
	enableControl(false);
}

