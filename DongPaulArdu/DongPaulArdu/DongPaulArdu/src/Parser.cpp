/*
 * Parser.cpp
 *
 * Created: 8/7/2017 3:06:43 PM
 *  Author: Andrew_2
 */ 

#include "Message.h"
#include "Control.h"

extern void kill(void);
extern void parseControlMessage(unsigned char *data, unsigned char len);

void parseMessage(unsigned char *data, int len) {
	
	unsigned char command = data[0];
	switch(command) {
		case 's': 
		case 'c': {
			parseControlMessage(data, len);
			break;
		} case 'i': {
			//send info
			break;
		} case 'k': {
			kill();
			break;
		} case 'e': {
			enableControl(true);
			break;
		} case 'd': {
			enableControl(false);
			break;
		}
		
	}

}
