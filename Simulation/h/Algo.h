/*
 * Algo.h
 *
 *  Created on: 07.11.2014
 *      Author: Manojkumar
 */

#ifndef ALGO_H_
#define ALGO_H_

#include "types.h"
#include "Node.h"
#include "MazeArray.h"
#include "DeadEndHandler.h"

#define ALGO_FAIL -1
#define ALGO_TIMEOUT -2
#define ALGO_EXPLORED 0
#define ALGO_TOKENS_COLLECTED 1
#define ALGO_CONFUSED 3

#define CHECK_NOT_OK -1
#define CHECK_OK 1

static node* currentNode_pst = NULL;
static node* previousNode_pst = NULL;

void checkToken(int32 f_moveResult_i32);

int32 checkAndMoveWest(node* f_inputNode_pst);

int32 checkAndMoveNorth(node* f_inputNode_pst);

int32 checkAndMoveEast(node* f_inputNode_pst);

int32 checkAndMoveSouth(node* f_inputNode_pst);

void reviewWest(node* f_inputNode_pst);

void reviewNorth(node* f_inputNode_pst);

void reviewEast(node* f_inputNode_pst);

void reviewSouth(node* f_inputNode_pst);

void reviewNeighbours(node* f_inputNode_pst);

bool initRobotAlgo();

// InitAlgo() needs to be called before calling this function
int32 startRobotAlgo();


#endif /* ALGO_H_ */
