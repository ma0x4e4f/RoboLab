/*
 * RobotHandler.c
 *
 *  Created on: 02-Dec-2014
 *      Author: ACHU
 */

#include "../h/RobotHandler.h"
#include "../h/algo/Node.h"
#include "../h/algo/Algo.h"

int calcTurnOrientation(int f_startCoordX_i32, int f_startCoordY_i32,
						int f_moveCoordX_i32,  int f_moveCoordY_i32 )
{
	int turnOrientation_i32 = NULLDIRECTION;

	int offsetX_i32 = f_moveCoordX_i32 - f_startCoordX_i32;
	int offsetY_i32 = f_moveCoordY_i32 - f_startCoordY_i32;

	int postiveChecker_i32 = 1;
	int negativeChecker_i32 = -1;

	if(postiveChecker_i32 == offsetY_i32)
	{
		turnOrientation_i32 = NORTH;
	}
	else if (negativeChecker_i32 == offsetY_i32)
	{
		turnOrientation_i32 = SOUTH;
	}
	else if (postiveChecker_i32 == offsetX_i32)
	{
		turnOrientation_i32 = EAST;
	}
	else if (negativeChecker_i32 == offsetX_i32)
	{
		turnOrientation_i32 = WEST;
	}

	return turnOrientation_i32;
}

int unitShiftCounter(int f_orientation_i32)
{
	int shiftCount = 0;

	int unitValue = 0x01;

	while(unitValue != f_orientation_i32)
	{
		f_orientation_i32 = f_orientation_i32 >> unitValue;

		shiftCount++;
	}

	return shiftCount;
}

BOOL findTurnFlag(int f_currentShiftCount_i32, int f_turnShiftCount_i32)
{
	BOOL turnFlag_bl = INVALID;

	int shiftCountDiff_i32 = f_currentShiftCount_i32 - f_turnShiftCount_i32;

	if(((abs(shiftCountDiff_i32) % 2 == 0) && (shiftCountDiff_i32 > 0)) ||
		((abs(shiftCountDiff_i32) % 2 == 1) && (shiftCountDiff_i32 < 0)))
	{
		turnFlag_bl = TRUE;
	}
	else if(((abs(shiftCountDiff_i32) % 2 == 0) && (shiftCountDiff_i32 < 0)) ||
			((abs(shiftCountDiff_i32) % 2 == 1) && (shiftCountDiff_i32 > 0)))
	{
		turnFlag_bl = FALSE;
	}

	return turnFlag_bl;

}

int Robot_GetIntersections()
{
//	printString("entering getIntersection");

	int validDirection = 0x00;

	validDirection = scan360();

//	printString("exiting getIntersection");

	return validDirection;
}

int Robot_Move(int f_moveCoordX_i32, int f_moveCoordY_i32)
{
//	printString("entering robot_move");

	node* f_currentNode_pst = getCurretnNode();

	int f_currentOrientation_i32 = getCurrentOrientation();

	int l_moveResult_i32 = ROBOT_FAIL;

	int l_turnSpeedd_i32 = TURNSPEED;

	int normalTurnAngle = 100;
	int normalTurnScanAngle = 60;
	int uTurnAngle = 180;
	int uTurnScanAngle = 150;

	BOOL returnBlackFound_bl =TRUE;

	int turnOrientation_i32 = NULLDIRECTION;

	turnOrientation_i32 = calcTurnOrientation(f_currentNode_pst->xy_st.x_Coordinate_i32,
											  f_currentNode_pst->xy_st.y_Coordinate_i32,
											  f_moveCoordX_i32,
											  f_moveCoordY_i32);

	if(NULLDIRECTION != turnOrientation_i32)
	{
		int OR_result_i32 = f_currentOrientation_i32 | turnOrientation_i32;

		if (f_currentOrientation_i32 == turnOrientation_i32)
		{
//			forward(moveDistance_mm);
			// No change in current orientation
		}
		else if((0x30 == OR_result_i32) || (0xC0 == OR_result_i32))
		{
			turnAndScan(uTurnAngle, uTurnScanAngle, returnBlackFound_bl, CLOCKWISE, l_turnSpeedd_i32, FALSE);
		}
		else
		{
			int currentOrintShiftCount_i32 = unitShiftCounter(f_currentOrientation_i32);
			int turnOrientShiftCount_i32 = unitShiftCounter(turnOrientation_i32);

			int turnFlag_bl = findTurnFlag(currentOrintShiftCount_i32, turnOrientShiftCount_i32);

			if(TRUE == turnFlag_bl)
			{
				turnAndScan(normalTurnAngle, normalTurnScanAngle, returnBlackFound_bl, CLOCKWISE, l_turnSpeedd_i32, FALSE);
			}
			else
			{
				turnAndScan(normalTurnAngle, normalTurnScanAngle, returnBlackFound_bl, ANTICLOCKWISE, l_turnSpeedd_i32, FALSE);
			}

		}

		setCurrentOrientation(turnOrientation_i32);
	}

	if(getBlack())
	{
		l_moveResult_i32 = movenodetonode();
	}

	return l_moveResult_i32;
}

int endHandler()
{
	int l_currentOrientation_i32 = getCurrentOrientation();

	int l_turnOrientation_i32 = SOUTH;

	int l_moveResult_i32 = ROBOT_FAIL;

	int l_turnSpeedd_i32 = TURNSPEED;

	int normalTurnAngle = 100;
	int normalTurnScanAngle = 60;
	BOOL returnBlackFound_bl = TRUE;

	if (l_currentOrientation_i32 == l_turnOrientation_i32)
	{
		// No change in current orientation
		// Do nothing
	}
	else
	{
		int currentOrintShiftCount_i32 = unitShiftCounter(l_currentOrientation_i32);
		int turnOrientShiftCount_i32 = unitShiftCounter(l_turnOrientation_i32);

		int turnFlag_bl = findTurnFlag(currentOrintShiftCount_i32, turnOrientShiftCount_i32);

		if(TRUE == turnFlag_bl)
		{
			turnAndScan(normalTurnAngle, normalTurnScanAngle, returnBlackFound_bl, CLOCKWISE, l_turnSpeedd_i32, FALSE);
		}
		else
		{
			turnAndScan(normalTurnAngle, normalTurnScanAngle, returnBlackFound_bl, ANTICLOCKWISE, l_turnSpeedd_i32, FALSE);
		}

	}

	setCurrentOrientation(l_turnOrientation_i32);

	if(getBlack())
	{
		l_moveResult_i32 = movenodetonode();
	}

	sound_freq(500, 2000);
	systick_wait_ms(2000);

	return l_moveResult_i32;

}


