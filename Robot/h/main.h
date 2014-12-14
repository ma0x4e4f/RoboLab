#ifndef MAIN_H_
#define MAIN_H_

#include "types.h"

#include "movements.h"
#include "directions.h"
#include "lightsensor.h"
/* add user headers here: */

static int curentOrientation;

int getCurrentOrientation();
void setCurrentOrientation(int orientation);

int initRobot();
void endRobot(int f_inputResult_i32);

#endif /* MAIN_H_ */
