/*
 * types.h
 *
 *  Created on: 07.11.2014
 *      Author: Manojkumar
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "Configuration.h"

#define SIMULATION 1
#define ROBOT 0

typedef char int8;

typedef int int32;
typedef unsigned int uint32;
typedef signed int sint32;

typedef float float32;

#define NORTHCOVERED 0xE0;
#define SOUTHCOVERED 0xD0;
#define WESTCOVERED 0xB0;
#define EASTCOVERED 0x70;

#endif /* TYPES_H_ */
