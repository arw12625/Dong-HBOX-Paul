/*
 * Sweeper.h
 *
 * Created: 10/25/2017 11:15:22 AM
 *  Author: Andrew_2
 */ 


#ifndef SWEEPER_H_
#define SWEEPER_H_


#define SWEEPER_OFF 0
#define SWEEPER_IN 1
#define SWEEPER_OUT 2

void initSweeper(void);
void updateSweeper(void);

//void setSweepSpeed(int newSpeed);
void setSweepDir(unsigned char newDir);



#endif /* SWEEPER_H_ */