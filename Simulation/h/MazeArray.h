/*
 * MazeArray.h
 *
 *  Created on: 06.11.2014
 *      Author: Manojkumar
 */

#ifndef MAZEARRAY_H_
#define MAZEARRAY_H_

#include "types.h"
#include "Node.h"

#define MAZEARRAYMAXSIZE 100

node mazeArray[MAZEARRAYMAXSIZE];

void initMazeArray();

node* getOriginNode();

uint32 getValidNumElements();

node* setMazeArrayElement(int32 f_xCord_i32, int32 f_yCord_i32, int32 f_availableDirections_i32);

node* searchMazeArray(int32 f_xCord_i32, int32 f_yCord_i32);

#endif /* MAZEARRAY_H_ */
