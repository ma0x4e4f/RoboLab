/*
 * movements.c
 *
 *  Created on: 23-Nov-2014
 *      Author: ACHU
 */

#include "../h/main.h"
#include "../h/movements.h"


void  stop()
{
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
}

void forward(int distance_mm)
{
//	printString("entering forward");
	int currentCountB = 0;
	int currentCountC = 0;

	int wheelDiameter_mm = 56;

	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	int speed = 50;

	int countPerMm = (360 * 7)/(22 * wheelDiameter_mm);

	int countForDistance = distance_mm * countPerMm;

    while(currentCountB < countForDistance && currentCountC < countForDistance)
    {
		nxt_motor_set_speed(NXT_PORT_B, speed, 1);
		nxt_motor_set_speed(NXT_PORT_C, speed, 1);

		currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B));
		currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C));
    }

    stop();

//    printString("exiting forward");
}

void reverse(int distance_mm)
{
	int currentCountB = 0;
	int currentCountC = 0;

	int wheelDiameter_mm = 56;

	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	int speed = 30;

	float countPerMm = (360 * 7)/(22 * wheelDiameter_mm);

	int countForDistance = distance_mm * countPerMm;

    while(currentCountB < countForDistance && currentCountC < countForDistance)
    {
		nxt_motor_set_speed(NXT_PORT_B, -speed, 1);
		nxt_motor_set_speed(NXT_PORT_C, -speed, 1);

		currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B));
		currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C));
    }

    stop();
}

int getCount(int f_angle_i32)
{
	printString("entering getcount");

	float robotWheel2WheelDistance = 163;

	float pi = 3.14 ;

//	float wheelDiameter = 56;

	int totalAngle = 360;

//	float countPerMM = totalAngle/ (pi * wheelDiameter);

	int countPerMM = 2;

	int count = (int) (robotWheel2WheelDistance * pi * f_angle_i32 * countPerMM/ totalAngle);

	return count;

	printString("exiting getcount");
}

BOOL turnAndScan(int f_turnAngle_i32, int f_scanOffsetAngle_i32,
				BOOL f_returnOceBlackFound_bl, BOOL f_directionFlag_bl,
				int f_turnSpeed_i32, BOOL f_correctionFlag_bl)
{
//	printString("entering turnandscan");

	BOOL foundBlack_bl = FALSE;
	BOOL sensorFlag_bl = FALSE;

	int turnSpeed_i32 = TURNSPEED;

	int correctionOffsetLeft_i32 = 12;
	int correctionOffsetRight_i32 = 12;

	int turnspeedMotorLeft;
	int turnSpeedMotorRight;

	int correctionSpeedLeft;
	int correctionSpeedRight;

	int leftOffset_i32 = 0;
	int rightOffset_i32 = 0;

	if(f_directionFlag_bl)
	{
		turnspeedMotorLeft = turnSpeed_i32;
		correctionSpeedLeft = -turnSpeed_i32 + 15;

		turnSpeedMotorRight = -turnSpeed_i32;
		correctionSpeedRight = turnSpeed_i32 - 15;
	}
	else
	{
		turnspeedMotorLeft = -turnSpeed_i32;
		correctionSpeedLeft = turnSpeed_i32 - 15;

		turnSpeedMotorRight = turnSpeed_i32;
		correctionSpeedRight = -turnSpeed_i32 + 15;
	}

	int turnCount = getCount(f_turnAngle_i32);

	int scanCountOffset_i32 = getCount(f_scanOffsetAngle_i32);

	int startRevMotorLeft_i32 = ecrobot_get_motor_rev(LEFT_MOTOR);
	int startRevMotorRight_i32 = ecrobot_get_motor_rev(RIGHT_MOTOR);

	int currentRevMotorLeft_i32 = 0;
	int currentRevMotorRight_i32 = 0;

	while(currentRevMotorLeft_i32 < turnCount || currentRevMotorRight_i32 < turnCount)
	{
		ecrobot_set_motor_speed(LEFT_MOTOR, turnspeedMotorLeft);
		ecrobot_set_motor_speed(RIGHT_MOTOR, turnSpeedMotorRight);

		if(scanCountOffset_i32 < currentRevMotorLeft_i32 && !foundBlack_bl)
		{
			sensorFlag_bl = lightsensor(); // call the lightsensor function to check white or black

			if(sensorFlag_bl)
			{
				foundBlack_bl = TRUE;

				if(f_returnOceBlackFound_bl)
				{
//					systick_wait_ms(8);
					break;
				}
			}
		}

		currentRevMotorLeft_i32 = abs(ecrobot_get_motor_rev(LEFT_MOTOR) - startRevMotorLeft_i32);
		currentRevMotorRight_i32 = abs(ecrobot_get_motor_rev(RIGHT_MOTOR) - startRevMotorRight_i32);
	}

	stop();

	if(f_correctionFlag_bl)
	{

		leftOffset_i32 = abs(currentRevMotorLeft_i32 - turnCount);
		rightOffset_i32 = abs(currentRevMotorRight_i32 - turnCount);

		startRevMotorLeft_i32 = ecrobot_get_motor_rev(LEFT_MOTOR);
		startRevMotorRight_i32 = ecrobot_get_motor_rev(RIGHT_MOTOR);

		if(correctionOffsetLeft_i32 < leftOffset_i32)
		{
			currentRevMotorLeft_i32 = 0;
			leftOffset_i32 = leftOffset_i32 - correctionOffsetLeft_i32;

			while(currentRevMotorLeft_i32 < leftOffset_i32)
			{
				ecrobot_set_motor_speed(LEFT_MOTOR, correctionSpeedLeft);

				currentRevMotorLeft_i32 = abs(ecrobot_get_motor_rev(LEFT_MOTOR) - startRevMotorLeft_i32);
			}

//			systick_wait_ms(50);

			stop();
		}
		if(correctionOffsetRight_i32 < rightOffset_i32)
		{
			currentRevMotorRight_i32 = 0;

			rightOffset_i32 = rightOffset_i32 - correctionOffsetRight_i32;

			while(currentRevMotorRight_i32 < rightOffset_i32)
			{
				ecrobot_set_motor_speed(RIGHT_MOTOR, correctionSpeedRight);

				currentRevMotorRight_i32 = abs(ecrobot_get_motor_rev(RIGHT_MOTOR) - startRevMotorRight_i32);
			}

//			systick_wait_ms(50);

			stop();
		}
	}
//	stop();

//	ecrobot_debug1(turnCount, leftOffset_i32, rightOffset_i32);

//	systick_wait_ms(2000);

//	printString("exiting turnandscan");

	return foundBlack_bl;
}

int findToken()
{
	int touchResult = 0;

	touchResult = ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S4);

	if(1 == touchResult)
	{
		stop();
		ecrobot_status_monitor("Token found");
		sound_freq(100, 600);
		systick_wait_ms(5000);
		return ROBOT_TOKENFOUND;
	}
	else
	{
		// Do nothing
	}
}

BOOL getBlack()
{
	int currentCountB = 0;
	int currentCountC = 0;

	int testAngle = 30;

	int turnSpeed = TURNSPEED;

	int turnCount = getCount(testAngle);

	int doubleTurnCount = (2 * turnCount);

	int initialCountB = nxt_motor_get_count(NXT_PORT_B);
	int initialCountC = nxt_motor_get_count(NXT_PORT_C);

	BOOL sensorFlag_bl = lightsensor();

	BOOL foundBlack = FALSE;
	BOOL ClockwiseFinished = FALSE;
	BOOL AntiClockwiseFinished = FALSE;

	if(sensorFlag_bl)
	{
		foundBlack = TRUE;
		return foundBlack;
	}
	else
	{
		while(currentCountB < turnCount && currentCountC < turnCount)
		{
			nxt_motor_set_speed(NXT_PORT_B, turnSpeed, 1); /* Set motor speed for B and C to RN */
		    nxt_motor_set_speed(NXT_PORT_C, -turnSpeed, 1);

		    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
		    currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);

		    sensorFlag_bl = lightsensor();

		    if (sensorFlag_bl)
		    {
		    	foundBlack = TRUE;
		    	stop();
		    	return foundBlack;
		    }

		}

		stop();

		AntiClockwiseFinished = TRUE;

		initialCountB = nxt_motor_get_count(NXT_PORT_B);
		initialCountC = nxt_motor_get_count(NXT_PORT_C);
		currentCountB = 0;
		currentCountC = 0;

		if(FALSE == foundBlack)
		{
			while(currentCountB < doubleTurnCount && currentCountC < doubleTurnCount)
			{
				nxt_motor_set_speed(NXT_PORT_B, -turnSpeed, 1); /* Set motor speed for B and C to RN */
			    nxt_motor_set_speed(NXT_PORT_C, turnSpeed, 1);

			    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
			    currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);

			    sensorFlag_bl = lightsensor();

			    if (sensorFlag_bl)
			    {
			    	foundBlack = TRUE;
			    	stop();
			    	return foundBlack;
			    }
			}

			ClockwiseFinished = TRUE;
		}

		stop();

		initialCountB = nxt_motor_get_count(NXT_PORT_B);
		initialCountC = nxt_motor_get_count(NXT_PORT_C);
		currentCountB = 0;
		currentCountC = 0;

		while(currentCountB < turnCount && currentCountC < turnCount)
		{
			if (TRUE == ClockwiseFinished)
			{
				nxt_motor_set_speed(NXT_PORT_B, turnSpeed, 1);
				nxt_motor_set_speed(NXT_PORT_C, -turnSpeed, 1);
			}
			else
			{
				nxt_motor_set_speed(NXT_PORT_B, -turnSpeed, 1);
				nxt_motor_set_speed(NXT_PORT_C, turnSpeed, 1);
			}

			currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
			currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);
		}

		stop();

		return foundBlack;
	}
}

BOOL oldlinescan(int threshold)
{
	int currentrevB = 0;
	int currentrevC = 0;

	BOOL blackFlag_bl = FALSE;

	BOOL tempBlackFlag_bl = FALSE;

	int black=0;
	int white=0;

	int checkrevB;
	int checkrevC;

	BOOL lineScanResult_bl = FALSE;

	checkrevB = ecrobot_get_motor_rev(NXT_PORT_B);  // contains the current revolution degree of movenodetonode function//
	checkrevC = ecrobot_get_motor_rev(NXT_PORT_C);

	currentrevB = 0;
	currentrevC = 0;

	blackFlag_bl = lightsensor();

	if(!blackFlag_bl)
	{
		while(currentrevB < 60 && currentrevC < 60)
		{
			nxt_motor_set_speed(NXT_PORT_B, -20, 1); /* Set motor speed for B and C to RN */
			nxt_motor_set_speed(NXT_PORT_C,  20, 1);
			currentrevB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - checkrevB);
			currentrevC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - checkrevC);
			tempBlackFlag_bl = lightsensor();
			if(tempBlackFlag_bl)
			{
				black++;

				if(black == 8)//one degree 0.04cm so using 4 degree and also this number decides where the robot be at the midpoint  //
				{
					stop();
					lineScanResult_bl = TRUE;
					return lineScanResult_bl;
				}
			}
			else
			{
				white++;
			}
		}      //ending of while loop//

		if(black == 8)
		{
//			ecrobot_status_monitor("Path  found");
			stop();
			lineScanResult_bl = TRUE;
			return lineScanResult_bl;
		}
		else
		{
			checkrevB = ecrobot_get_motor_rev(NXT_PORT_B);
			checkrevC = ecrobot_get_motor_rev(NXT_PORT_C);
			currentrevB = 0;
			currentrevC = 0;
			while(currentrevB < 120 && currentrevC < 120)
			{
				nxt_motor_set_speed(NXT_PORT_B,  20, 1); /* Set motor speed for B and C to RN */
				nxt_motor_set_speed(NXT_PORT_C, -20, 1);
				currentrevB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - checkrevB);
				currentrevC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - checkrevC);
				tempBlackFlag_bl = lightsensor();
				if(tempBlackFlag_bl)
				{
					black++;
				}
				else
				{
					white++;
				}
				if(black == 8)//one degree is  0.04cm so using 13 degree//
				{
					stop();
					lineScanResult_bl = TRUE;
					return lineScanResult_bl;
//					nxt_motor_set_count(NXT_PORT_B, checkrevB);
//					nxt_motor_set_count(NXT_PORT_C, checkrevC);
				}
				else
				{
					white++;
				}
			}      //ending of while loop//
			stop();
		}

		if(FALSE == lineScanResult_bl)
		{
			checkrevB = ecrobot_get_motor_rev(NXT_PORT_B);
			checkrevC = ecrobot_get_motor_rev(NXT_PORT_C);
			currentrevB = 0;
			currentrevC = 0;

			while(currentrevB < 60 && currentrevC < 60)
			{
				nxt_motor_set_speed(NXT_PORT_B, -20, 1); /* Set motor speed for B and C to RN */
				nxt_motor_set_speed(NXT_PORT_C,  20, 1);
				currentrevB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - checkrevB);
				currentrevC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - checkrevC);
			}

			stop();
			return FALSE;
		}
	}
	else
	{
//		ecrobot_status_monitor("Path  found");
		stop();
		return TRUE;
	}
}

BOOL linescan(int threshold, BOOL f_correctionFlag_bl)
{
//	printString("entered line scan");

	int currentrevB = 0;
	int currentrevC = 0;

	BOOL blackFlag_bl = FALSE;

	int checkrevB;
	int checkrevC;

	int l_turnSpeed_i32 = TURNSPEED - 25;

	BOOL lineScanResult_bl = FALSE;

	checkrevB = ecrobot_get_motor_rev(NXT_PORT_B);  // contains the current revolution degree of movenodetonode function//
	checkrevC = ecrobot_get_motor_rev(NXT_PORT_C);

	currentrevB = 0;
	currentrevC = 0;

	blackFlag_bl = lightsensor();

	if(!blackFlag_bl)
	{
		if(!f_correctionFlag_bl)
		{
			lineScanResult_bl = turnAndScan(15,0,TRUE,CLOCKWISE, l_turnSpeed_i32, f_correctionFlag_bl);
		}
		else
		{
			lineScanResult_bl = turnAndScan(25,0,TRUE,CLOCKWISE, l_turnSpeed_i32, !f_correctionFlag_bl);
		}

		if(lineScanResult_bl)
		{
//			ecrobot_status_monitor("Path  found");
			stop();
//			lineScanResult_bl = TRUE;
			return lineScanResult_bl;
//			printString("exiting linescan1");
		}
		else
		{
//			turnAndScan(20,0,FALSE,ANTICLOCKWISE);

			if(!f_correctionFlag_bl)
			{
				lineScanResult_bl = turnAndScan(40,0,TRUE,ANTICLOCKWISE, l_turnSpeed_i32, f_correctionFlag_bl);
			}
			else
			{
				lineScanResult_bl = turnAndScan(60,0,TRUE,ANTICLOCKWISE, l_turnSpeed_i32, !f_correctionFlag_bl);
			}

			if(lineScanResult_bl)
			{
//				ecrobot_status_monitor("Path  found");
				stop();
//				lineScanResult_bl = TRUE;
				return lineScanResult_bl;

//				printString("exiting linescan2");
			}
		}

		if(!lineScanResult_bl)
		{
			if(!f_correctionFlag_bl)
			{
				turnAndScan(20,20,FALSE,CLOCKWISE, l_turnSpeed_i32, f_correctionFlag_bl);
			}
			else
			{
				turnAndScan(30,30,FALSE,CLOCKWISE, l_turnSpeed_i32, !f_correctionFlag_bl);
			}
			stop();
			return FALSE;
//			printString("exiting linescan3");
		}
	}
	else
	{
//		ecrobot_status_monitor("Path  found");
//		stop();
		return TRUE;
//		printString("exiting linescan4");
	}
}

int movenodetonode()
{

//	printString("entered move node2node");

	int currentCountB=0;
	int currentCountC=0;

	int moveResult_i32 = ROBOT_FAIL;

	int sensorThreshold = getThreshold();

	BOOL blackFlag_bl = FALSE;

	int countBThreshold = 600;
	int countCThreshold = 600;

	int speed = RIDESPEED;

	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	blackFlag_bl = lightsensor();

	BOOL lineScanResult_bl = FALSE;

    while((blackFlag_bl) || (currentCountB < countBThreshold)
    		|| (currentCountC < countCThreshold))
	{
    	if(ROBOT_FAIL == moveResult_i32)
    	{
    		moveResult_i32 = findToken();
    	}

		currentCountB = ecrobot_get_motor_rev(NXT_PORT_B);
		currentCountC = ecrobot_get_motor_rev(NXT_PORT_C);

		lineScanResult_bl = linescan(sensorThreshold, FALSE);

		blackFlag_bl = lightsensor();

		nxt_motor_set_count(NXT_PORT_B, currentCountB);
		nxt_motor_set_count(NXT_PORT_C, currentCountB);

		if(TRUE == lineScanResult_bl)
		{
//			lineEndCount = 0;
			nxt_motor_set_speed(NXT_PORT_B, speed, 1);
			nxt_motor_set_speed(NXT_PORT_C, speed, 1);

			systick_wait_ms(50);
		}
		else
		{
			stop();
//			lineEndCount++;

			if(ROBOT_FAIL == moveResult_i32)
			{
				moveResult_i32 = findToken();
			}

			forward(5);

			lineScanResult_bl = linescan(sensorThreshold, TRUE);

			if(!lineScanResult_bl)
			{
				blackFlag_bl = FALSE;

//				ecrobot_status_monitor("Stopped due to line break!");

				if(ROBOT_FAIL == moveResult_i32)
				{
					moveResult_i32 = ROBOT_SUCCESS;
				}
				break;
			}
		}
	}

//    errorCorrection();

    systick_wait_ms(100);

    forward(110);

    stop();

    return moveResult_i32;
}

void halfAntiClockwise(int turnAngle)
{
	int currentCountB = 0;
	int currentCountC = 0;

	int speed = TURNSPEED;

	int halfCircleDiameter_mm = 166;

	int countPerMm = 2;

	int turnCount = (3.14 * halfCircleDiameter_mm * turnAngle * countPerMm)/360;

	int initialCountB = nxt_motor_get_count(NXT_PORT_B);
	int initialCountC = nxt_motor_get_count(NXT_PORT_C);

	while(currentCountB < turnCount && currentCountC < turnCount)
	{
		nxt_motor_set_speed(NXT_PORT_B,  speed, 1); /* Set motor speed for B and C to RN */
	    nxt_motor_set_speed(NXT_PORT_C, -speed, 1);

	    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
	    currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);
	}

	stop();
}

void FullAntiClockwise(int turnAngle, BOOL forwardFlag)
{
	int currentCountB = 0;

	int fullCircleDiameter_mm = 166 * 2;

	int speed = TURNSPEED;

	int countPerMm = 2;

	int turnCount = 0; // ((3.14 * fullCircleDiameter_mm * turnAngle * countPerMm)/360) + 10;

	if(TRUE == forwardFlag)
	{
		turnCount = ((3.14 * fullCircleDiameter_mm * turnAngle * countPerMm)/360) + 10;
	}
	else if (FALSE == forwardFlag)
	{
		turnCount = ((3.14 * fullCircleDiameter_mm * turnAngle * countPerMm)/360) + 10;
	}

	int initialCountB = nxt_motor_get_count(NXT_PORT_B);

	while(currentCountB < turnCount)
	{
		if(TRUE == forwardFlag)
		{
			nxt_motor_set_speed(NXT_PORT_B, speed, 1); /* Set motor speed for B and C to RN */
		}
		else if (FALSE == forwardFlag)
		{
			nxt_motor_set_speed(NXT_PORT_B, -speed, 1);
		}

	    nxt_motor_set_speed(NXT_PORT_C,  0, 1);

	    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
	}

	stop();
}

void halfClockwise(int turnAngle)
{
	int currentCountB = 0;
	int currentCountC = 0;

	int halfCircleDiameter_mm = 166;

	int countPerMm = 2;

	int speed = TURNSPEED;

	int turnCount = (3.14 * halfCircleDiameter_mm * turnAngle * countPerMm)/360;

	int initialCountB = nxt_motor_get_count(NXT_PORT_B);
	int initialCountC = nxt_motor_get_count(NXT_PORT_C);

	while(currentCountB < turnCount && currentCountC < turnCount)
	{
		nxt_motor_set_speed(NXT_PORT_B, -speed, 1); /* Set motor speed for B and C to RN */
	    nxt_motor_set_speed(NXT_PORT_C,  speed, 1);

	    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
	    currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);
	}

	stop();
}

void FullClockwise(int turnAngle, BOOL forwardFlag)
{
	int currentCountC = 0;

	int fullCircleDiameter_mm = 166 * 2;

	int countPerMm = 2;

	int speed = TURNSPEED;

	int turnCount = ((3.14 * fullCircleDiameter_mm * turnAngle * countPerMm)/360);

	int initialCountC = nxt_motor_get_count(NXT_PORT_C);

	while(currentCountC < turnCount)
	{
		nxt_motor_set_speed(NXT_PORT_B,  0, 1);

		if (TRUE == forwardFlag)
		{
			nxt_motor_set_speed(NXT_PORT_C, speed, 1);
		}
		else if (FALSE == forwardFlag)
		{
			nxt_motor_set_speed(NXT_PORT_C, -speed, 1);
		}

	    currentCountC = abs(ecrobot_get_motor_rev(NXT_PORT_C) - initialCountC);
	}

	stop();
}

void errorCorrection()
{
	int initialCountB = nxt_motor_get_count(NXT_PORT_B);

	int errorTurnCount = 20;

	int turnSpeed = TURNSPEED;

	int currentCountB = 0;

	while(currentCountB < errorTurnCount)
	{
		nxt_motor_set_speed(NXT_PORT_B, -turnSpeed, 1);

	    currentCountB = abs(ecrobot_get_motor_rev(NXT_PORT_B) - initialCountB);
	}

	stop();
}



