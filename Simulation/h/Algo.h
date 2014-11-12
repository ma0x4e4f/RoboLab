/*
 * Algo.h
 *
 *  Created on: 07.11.2014
 *      Author: Manojkumar
 */

#ifndef ALGO_H_
#define ALGO_H_

#include "types.h"
#include "RobotProxy.h"
#include "Node.h"
#include "MazeArray.h"

#define MAX_TOKENS 3
#define ALGO_FAIL -1
#define ALGO_TIMEOUT -2
#define ALGO_EXPLORED 0
#define ALGO_TOKENS_COLLECTED 1
#define ALGO_CONFUSED 3

#define CHECK_NOT_OK 0
#define CHECK_OK 1


bool isMazeExplored_bl = false;
bool isTokensCollected_bl = false;
bool isBorderCCovered_bl;

node* originNode_pst = NULL;
static node* currentNode_pst = NULL;
static node* previousNode_pst = NULL;

static uint32 timeout_ui32 = 0;
int32 tokenCount_i32 = 0;

typedef struct
{
	bool isNorthAvailable_bl;
	bool isSouthAvailable_bl;
	bool isWestAvailable_bl;
	bool isEastAvailable_bl;
}directionsFlag;

directionsFlag getAvailableDirectionsFlag(node* f_inputNode_pst);

directionsFlag getUncoveredDirectionsFlag(node* f_inputNode_pst);

void checkToken(int32 f_moveResult_i32);

bool initRobotAlgo();

int32 robotAlgoMove(int32 f_moveCord_x_i32, int32 f_moveCord_y_i32);

int32 checkAndMoveWest(node* f_inputNode_pst);

int32 checkAndMoveNorth(node* f_inputNode_pst);

int32 checkAndMoveEast(node* f_inputNode_pst);

int32 checkAndMoveSouth(node* f_inputNode_pst);

void reviewWest(node* f_inputNode_pst);

void reviewNorth(node* f_inputNode_pst);

void reviewEast(node* f_inputNode_pst);

void reviewSouth(node* f_inputNode_pst);

void reviewNeighbours(node* f_inputNode_pst);

// InitAlgo() needs to be called before calling this function
int32 startRobotAlgo();


#endif /* ALGO_H_ */
