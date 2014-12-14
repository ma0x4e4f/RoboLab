/*
 * lightsensor.c
 *
 *  Created on: 23-Nov-2014
 *      Author: ACHU
 */

#ifndef LIGHTSENSOR_C_
#define LIGHTSENSOR_C_

#include "../h/main.h"
#include "../h/lightsensor.h"

static int thresholdvalue;

void calibration()
{
     int white;
     int black;

     int calibrationAngle = 70;

     forward(10);

//     black = lightsensor();
     black = ecrobot_get_light_sensor(NXT_PORT_S2);

	 nxt_motor_set_count(NXT_PORT_B, 0);
	 nxt_motor_set_count(NXT_PORT_C, 0);

	 halfClockwise(calibrationAngle);

//	 white = lightsensor();
	 white = ecrobot_get_light_sensor(NXT_PORT_S2);

	 thresholdvalue = calculatethreshold(black,white);

	 ecrobot_show_int(thresholdvalue);

	 halfAntiClockwise(calibrationAngle);
}


BOOL lightsensor()
{
	int sensorvalue = 0;

	sensorvalue = ecrobot_get_light_sensor(NXT_PORT_S2);

	int threshold = getThreshold();

	if(thresholdvalue < sensorvalue)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

//	return sensorvalue;
}

int calculatethreshold(int black ,int white )
{

	int threshold;
	threshold = (black+white)/2;
	return threshold;
}

int getThreshold()
{
	return thresholdvalue;
}

#endif /* LIGHTSENSOR_C_ */
