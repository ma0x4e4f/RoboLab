/*
 * AStarPathFinder.h
 *
 *  Created on: 17.11.2014
 *      Author: Manojkumar
 */

#ifndef ASTARPATHFINDER_H_
#define ASTARPATHFINDER_H_

#include "../types.h"
#include "Node.h"
#include "MazeArray.h"
#include "AStarNode.h"

aStarNode* getLowest(aStarList* f_aStarList_pst);

int32 heuristicEstimate(node* f_startNode_pst, node* f_inputNode_pst, node* f_endNode_pst);

neighbourList* reconstructPath(aStarNode* f_startAStarNode_pst, aStarNode* f_endAStarNode_pst);

neighbourList* aStarPathFinder(node* f_startNode_pst, node* f_endNode_pst);

int32 processAStarPath(neighbourList* f_aStarPathList_pst);

#endif /* ASTARPATHFINDER_H_ */
