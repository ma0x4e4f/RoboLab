/*
 * movements.h
 *
 *  Created on: 23-Nov-2014
 *      Author: ACHU
 */

#ifndef MOVEMENTS_H_
#define MOVEMENTS_H_

#include "main.h"

#define TURNSPEED 45
#define RIDESPEED 75

#define LEFT_MOTOR NXT_PORT_C
#define RIGHT_MOTOR NXT_PORT_B

void stop();
void forward(int distance_mm);
void reverse(int distance_mm);

int getCount(int f_angle_i32);

BOOL turnAndScan(int f_turnAngle_i32, int f_scanOffsetAngle_i32,
				BOOL f_returnOceBlackFound_bl, BOOL f_directionFlag_bl,
				int f_turnSpeed_i32, BOOL f_correctionFlag_bl);

int findToken();

BOOL getBlack();
BOOL oldlinescan(int threshold);
BOOL linescan(int threshold, BOOL f_correctionFlag_bl);
int movenodetonode();

void halfAntiClockwise(int turnAngle);
void FullAntiClockwise(int turnAngle, BOOL forwardFlag);
void halfClockwise(int turnAngle);
void FullClockwise(int turnAngle, BOOL forwardFlag);

void errorCorrection();

#endif /* MOVEMENTS_H_ */
