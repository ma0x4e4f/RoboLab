/*
 * directions.c
 *
 *  Created on: 23-Nov-2014
 *      Author: ACHU
 */


#include "../h/main.h"
#include "../h/directions.h"

int oring(int f_sideOne,int f_sideTwo,int f_sideThree,int f_sideFour)
{
	int validDirection;

	int currentOrientation = getCurrentOrientation();

	int northShift = 4;
	int southShift = 5;
	int westShift = 6;
	int eastShift = 7;

	if(NORTH == currentOrientation)
	{
		f_sideOne = f_sideOne << northShift;
		f_sideTwo = f_sideTwo << westShift;
		f_sideThree = f_sideThree << southShift;
		f_sideFour = f_sideFour << eastShift;
	}
	else if(SOUTH == currentOrientation)
	{
		f_sideOne = f_sideOne << southShift;
		f_sideTwo = f_sideTwo << eastShift;
		f_sideThree = f_sideThree << northShift;
		f_sideFour = f_sideFour << westShift;
	}
	else if(EAST == currentOrientation)
	{
		f_sideOne = f_sideOne << eastShift;
		f_sideTwo = f_sideTwo << northShift;
		f_sideThree = f_sideThree << westShift;
		f_sideFour = f_sideFour << southShift;
	}
	else if(WEST == currentOrientation)
	{
		f_sideOne = f_sideOne << westShift;
		f_sideTwo = f_sideTwo << southShift;
		f_sideThree = f_sideThree << eastShift;
		f_sideFour = f_sideFour << northShift;
	}

	validDirection = (f_sideOne | f_sideTwo | f_sideThree | f_sideFour);

	ecrobot_show_int(validDirection);

	return validDirection;
}

int getOppositeOrientation(int f_currentOrientation_i32)
{
	int l_oppositeOrintation_i32 = 0x00;

	if(NORTH == f_currentOrientation_i32 || WEST == f_currentOrientation_i32)
	{
		l_oppositeOrintation_i32 = f_currentOrientation_i32 << 1;
	}
	else if(SOUTH == f_currentOrientation_i32 || EAST == f_currentOrientation_i32)
	{
		l_oppositeOrintation_i32 = f_currentOrientation_i32 >> 1;
	}

	if(0x00 != l_oppositeOrintation_i32)
	{
		return l_oppositeOrintation_i32;
	}
	else
	{
		// print error

	}

}

int faultTolerant()
{
//	Two scenarios,
//	either we are on the left side but near to black line
//	or on the right side but far away from black line
//	so we have to search the path we came and turn our current orientation to oppsite side
//	and do a 360 from here
	int l_validDirection_i32 = 0x00;

	BOOL returnOceBlackFound_bl = TRUE;
	BOOL dontReturnOceBlackFound_bl = FALSE;

	int l_turningSpeed_i32 = TURNSPEED;

	int sideOne = 0;
	int sideTwo = 0;
	int sideThree = 0;
	int sideFour = 0;

	int startingTurnAngle_i32 = 25;
	int startingScanAngle_i32 = 0;

	int intermediateTurnAngle_i32 = 90;
	int intermediateScanAngle_i32 = 40;

	int finishTurnAngle_i32 = 80;
	int finishScanAngle_i32 = 40;

	int l_clockWiseSearchANgle_i32 = 75;
	int l_antiClockwiseSearchAngle_i32 = 10;

	BOOL l_foundBlack_bl = turnAndScan(l_antiClockwiseSearchAngle_i32 , startingScanAngle_i32,
				returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);

	if(!l_foundBlack_bl)
	{
		l_foundBlack_bl = turnAndScan(l_clockWiseSearchANgle_i32 , startingScanAngle_i32,
						returnOceBlackFound_bl, CLOCKWISE, l_turningSpeed_i32, FALSE);

		if(!l_foundBlack_bl)
		{
			return 0x00;
		}
	}

	int l_currentOrientation_i32 = getCurrentOrientation();

	int l_oppositeOrientation_i32 = 0x00;

	l_oppositeOrientation_i32 = getOppositeOrientation(l_currentOrientation_i32);

	setCurrentOrientation(l_oppositeOrientation_i32);

	sideOne = turnAndScan(startingTurnAngle_i32 , startingScanAngle_i32,
			dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
	sideTwo = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
			dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
	sideThree = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
			dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
	sideFour = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
			dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
	if(!sideOne)
	{
		sideOne = turnAndScan(finishTurnAngle_i32, finishScanAngle_i32,
					dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
	}
	else
	{
		turnAndScan(finishTurnAngle_i32, finishScanAngle_i32,
				returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
	}


	l_validDirection_i32 = oring(sideOne, sideTwo, sideThree, sideFour);

	return l_validDirection_i32;

}

int scan360()
{
	int foundDirections_i32 = 0x00;

	BOOL returnOceBlackFound_bl = TRUE;
	BOOL dontReturnOceBlackFound_bl = FALSE;

	int l_turningSpeed_i32 = TURNSPEED;

	int startingTurnAngle_i32 = 30;
	int startingScanAngle_i32 = 0;

	int intermediateTurnAngle_i32 = 90;
	int intermediateScanAngle_i32 = 30;

	int finishTurnAngle_i32 = 75;
	int finishScanAngle_i32 = 40;

	int sideOne = 0;

	int sideTwo = 0;

	int sideThree = 0;

	int sideFour = 0;

	sideOne = turnAndScan(startingTurnAngle_i32, startingScanAngle_i32,
			returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);

	if(sideOne) // Found side one start a 360 degree from here
	{
		sideOne = turnAndScan(startingTurnAngle_i32 , startingScanAngle_i32,
				dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
		sideTwo = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
				dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
		sideThree = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
				dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
		sideFour = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
				dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
		int tempSideOne = turnAndScan(finishTurnAngle_i32, finishScanAngle_i32,
				returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);

		if(sideOne == tempSideOne)
		{
			// do nothing
		}
		else if(tempSideOne)
		{
			sideOne = tempSideOne;
			// Somehow if we have missed the sideOne update now
		}
	}
	else
	{
		sideTwo = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32, returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);

		if(sideTwo) // Found side two, start a 270 degree turn from here
		{
			sideTwo = turnAndScan(startingTurnAngle_i32, startingScanAngle_i32,
					dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
			sideThree = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
					dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
			sideFour = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
					dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
			sideOne = turnAndScan(finishTurnAngle_i32, finishScanAngle_i32,
					returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
		}
		else
		{
			sideThree = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
					returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE); // This has to return true,
			// because through this line only we came here

			if(sideThree) // Found side three, start a 180 degree turn from here
			{
				sideThree = turnAndScan(startingTurnAngle_i32, startingScanAngle_i32,
						dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
				sideFour = turnAndScan(intermediateTurnAngle_i32, intermediateScanAngle_i32,
						dontReturnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
				sideOne = turnAndScan(finishTurnAngle_i32, finishScanAngle_i32,
						returnOceBlackFound_bl, ANTICLOCKWISE, l_turningSpeed_i32, FALSE);
			}
			else // Really a bad thing, we missed our path, do retry!
			{
				foundDirections_i32 = faultTolerant();

				if(0x00 == foundDirections_i32)
				{
					return 0x00;
				}
			}
		}
	}

	if(0x00 == foundDirections_i32)
	{
		foundDirections_i32 = oring(sideOne, sideTwo, sideThree, sideFour);
	}

	//	ecrobot_show_int(foundDirections_i32);

	return foundDirections_i32;
}

BOOL scanBlack(int testAngle)
{
	int currentCountB = 0;
	int currentCountC = 0;

	int turnSpeed = 20;

	int halfCircleDiameter_mm = 166;

	int countPerMm = 2;

	float sensorThreshold = getThreshold();

	int turnCount = ((3.14 * halfCircleDiameter_mm * testAngle * countPerMm)/360) + 10;

	int doubleTurnCount = (2 * turnCount);

	int initialCountB = nxt_motor_get_count(NXT_PORT_B);
	int initialCountC = nxt_motor_get_count(NXT_PORT_C);

	int sensorValue = lightsensor();

	BOOL foundBlack = FALSE;
	BOOL ClockwiseFinished = FALSE;
	BOOL AntiClockwiseFinished = FALSE;

	if(sensorThreshold < sensorValue)
	{
		foundBlack = TRUE;
		return foundBlack;
	}
	else
	{
		while(currentCountB < turnCount && currentCountC < turnCount)
		{
			nxt_motor_set_speed(NXT_PORT_B, -turnSpeed, 1); /* Set motor speed for B and C to RN */
		    nxt_motor_set_speed(NXT_PORT_C,  turnSpeed, 1);

		    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
		    currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);

		    sensorValue = lightsensor();

		    if (sensorThreshold < sensorValue)
		    {
		    	foundBlack = TRUE;
		    }

		}

		stop();

		ClockwiseFinished = TRUE;

		initialCountB = nxt_motor_get_count(NXT_PORT_B);
		initialCountC = nxt_motor_get_count(NXT_PORT_C);
		currentCountB = 0;
		currentCountC = 0;

		if(FALSE == foundBlack)
		{
			while(currentCountB < doubleTurnCount && currentCountC < doubleTurnCount)
			{
				nxt_motor_set_speed(NXT_PORT_B,  turnSpeed, 1); /* Set motor speed for B and C to RN */
			    nxt_motor_set_speed(NXT_PORT_C, -turnSpeed, 1);

			    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
			    currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);

			    sensorValue = lightsensor();

			    if (sensorThreshold < sensorValue)
			    {
			    	foundBlack = TRUE;
			    }
			}

			AntiClockwiseFinished = TRUE;
		}

		stop();

		initialCountB = nxt_motor_get_count(NXT_PORT_B);
		initialCountC = nxt_motor_get_count(NXT_PORT_C);
		currentCountB = 0;
		currentCountC = 0;

		while(currentCountB < turnCount && currentCountC < turnCount)
		{
			if (TRUE == AntiClockwiseFinished)
			{
				nxt_motor_set_speed(NXT_PORT_B, -turnSpeed, 1);
				nxt_motor_set_speed(NXT_PORT_C,  turnSpeed, 1);
			}
			else
			{
				nxt_motor_set_speed(NXT_PORT_B,  turnSpeed, 1);
				nxt_motor_set_speed(NXT_PORT_C, -turnSpeed, 1);
			}

			currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
			currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);
		}

		stop();

		return foundBlack;
	}
}

int getNorthDirections()
{
	int foundDirection = 0x00;

	int north = 0;
	int south = 0; // set south 1 before oring
	int east = 0;
	int west = 0;

	int moveDistance_mm = 90;

	int turnAngle = 90;
	int scanAngle = 30;

	int movementForwardFlag = TRUE;
	int movementReverseFlag = FALSE;

//	systick_wait_ms(5000);

	forward(moveDistance_mm);
	north = scanBlack(scanAngle);
	reverse(moveDistance_mm);

	FullAntiClockwise(turnAngle, movementForwardFlag);
	west = scanBlack(scanAngle);
	FullAntiClockwise(turnAngle, movementReverseFlag);

	errorCorrection();

	FullClockwise(turnAngle, movementForwardFlag);
	east = scanBlack(scanAngle);
	FullClockwise(turnAngle, movementReverseFlag);

	south = 1; // The direction we came from

	foundDirection = oring(north, south, east, west);

	return foundDirection;
}

int getSouthDirections()
{
	int foundDirection = 0x00;

	int north = 0; // set North 1 before oring
	int south = 0;
	int east = 0;
	int west = 0;

	int moveDistance_mm = 90;

	int turnAngle = 90;
	int scanAngle = 30;

	int movementForwardFlag = TRUE;
	int movementReverseFlag = FALSE;

//	systick_wait_ms(5000);

	forward(moveDistance_mm);
	south = scanBlack(scanAngle);
	reverse(moveDistance_mm);

	FullAntiClockwise(turnAngle, movementForwardFlag);
	east = scanBlack(scanAngle);
	FullAntiClockwise(turnAngle, movementReverseFlag);

	errorCorrection();

	FullClockwise(turnAngle, movementForwardFlag);
	west = scanBlack(scanAngle);
	FullClockwise(turnAngle, movementReverseFlag);

	north = 1; // The direction we came from

	foundDirection = oring(north, south, east, west);

	return foundDirection;
}


int getWestDirections()
{
	int foundDirection = 0x00;

	int north = 0;
	int south = 0;
	int east = 0;
	int west = 0;

	int moveDistance_mm = 90;

	int turnAngle = 90;
	int scanAngle = 30;

	int movementForwardFlag = TRUE;
	int movementReverseFlag = FALSE;

//	systick_wait_ms(5000);

	forward(moveDistance_mm);
	west = scanBlack(scanAngle);
	reverse(moveDistance_mm);

	FullAntiClockwise(turnAngle, movementForwardFlag);
	south = scanBlack(scanAngle);
	FullAntiClockwise(turnAngle, movementReverseFlag);

	errorCorrection();

	FullClockwise(turnAngle, movementForwardFlag);
	north = scanBlack(scanAngle);
	FullClockwise(turnAngle, movementReverseFlag);

	east = 1; // The direction we came from

	foundDirection = oring(north, south, east, west);

	return foundDirection;
}

int getEastDirections()
{
	int foundDirection = 0x00;

	int north = 0;
	int south = 0;
	int east = 0;
	int west = 0;

	int moveDistance_mm = 90;

	int turnAngle = 90;
	int scanAngle = 30;

	int movementForwardFlag = TRUE;
	int movementReverseFlag = FALSE;

//	systick_wait_ms(5000);

	forward(moveDistance_mm);
	east = scanBlack(scanAngle);
	reverse(moveDistance_mm);

	FullAntiClockwise(turnAngle, movementForwardFlag);
	north = scanBlack(scanAngle);
	FullAntiClockwise(turnAngle, movementReverseFlag);

	errorCorrection();

	FullClockwise(turnAngle, movementForwardFlag);
	south= scanBlack(scanAngle);
	FullClockwise(turnAngle, movementReverseFlag);

	west = 1; // The direction we came from

	foundDirection = oring(north, south, east, west);

	return foundDirection;
}
