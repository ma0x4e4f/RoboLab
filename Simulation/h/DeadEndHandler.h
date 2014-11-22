/*
 * DeadEndHandler.h
 *
 *  Created on: 18.11.2014
 *      Author: Manojkumar
 */

#ifndef DEADENDHANDLER_H_
#define DEADENDHANDLER_H_

#include "types.h"
#include "Node.h"
#include "MazeArray.h"
#include "AStarNode.h"
#include "AStarPathFinder.h"

void setNeighbourNodes(node* f_inputNode_pst, node* f_neighbourNode_pst);

node* checkAndMoveFromDeadEnd(node* f_inputNode_pst, node* f_inputPrevNode_pst);

#endif /* DEADENDHANDLER_H_ */
