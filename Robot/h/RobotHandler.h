/*
 * RobotHandler.h
 *
 *  Created on: 02-Dec-2014
 *      Author: ACHU
 */

#ifndef ROBOTHANDLER_H_
#define ROBOTHANDLER_H_

#include "types.h"
#include "directions.h"
#include "movements.h"

#define INVALID -1


// Helper Functions

int calcTurnOrientation(int f_startCoordX_i32, int f_startCoordY_i32,
						int f_moveCoordX_i32,  int f_moveCoordY_i32 );

int unitShiftCounter(int f_orientation_i32);

BOOL findTurnFlag(int f_currentShiftCount_i32, int f_turnShiftCount_i32);

// Helper Functions End

int Robot_GetIntersections();

int Robot_Move(int f_moveCoordX_i32, int f_moveCoordY_i32);

int endHandler();

#endif /* ROBOTHANDLER_H_ */
