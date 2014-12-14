/*
 * types.h
 *
 *  Created on: 07.11.2014
 *      Author: Manojkumar
 */

#ifndef TYPES_H_
#define TYPES_H_

#define SIMULATION 1
#define ROBOT 0

//#include "Configuration.h"
//#include "RobotProxy.h"

#include <stdlib.h>
#include "kernel.h"
/* Will be generated: */
#include "kernel_id.h"
#include "ecrobot_interface.h"

typedef char int8;

typedef int int32;
typedef unsigned int uint32;
typedef signed int sint32;

typedef float float32;

typedef BOOL bool;

//#define false 0
//#define true 1

#define NORTH 0x10
#define SOUTH 0x20
#define WEST 0x40
#define EAST 0x80

#define ROBOT_FAIL        0x00
#define ROBOT_SUCCESS     0x01
#define ROBOT_TOKENFOUND  0x02

#define NORTHCOVERED 0xE0;
#define SOUTHCOVERED 0xD0;
#define WESTCOVERED 0xB0;
#define EASTCOVERED 0x70;

#define CLOCKWISE 1
#define ANTICLOCKWISE 0

#define MAX_TOKENS 3

void printString(const char* f_inputString);

#endif /* TYPES_H_ */
