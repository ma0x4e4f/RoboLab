/*
 * lightsensor.h
 *
 *  Created on: 23-Nov-2014
 *      Author: ACHU
 */

#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#include "main.h"
#include "movements.h"

void calibration();
BOOL lightsensor();
int calculatethreshold(int black ,int white);
int getThreshold();

#endif /* LIGHTSENSOR_H_ */
