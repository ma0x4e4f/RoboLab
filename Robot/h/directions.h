/*
 * directions.h
 *
 *  Created on: 23-Nov-2014
 *      Author: ACHU
 */

#ifndef DIRECTIONS_H_
#define DIRECTIONS_H_


#include "types.h"
#include "movements.h"
#include "lightsensor.h"

int oring(int f_sideOne,int f_sideTwo,int f_sideThree,int f_sideFour);

int getOppositeOrientation(int f_currentOrientation_i32);

int faultTolerant();

int scan360();

BOOL scanBlack(int testAngle);

int getNorthDirections();
int getSouthDirections();
int getWestDirections();
int getEastDirections();

#endif /* DIRECTIONS_H_ */
