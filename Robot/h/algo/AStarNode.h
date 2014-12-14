/*
 * AStarNode.h
 *
 *  Created on: 17.11.2014
 *      Author: Manojkumar
 */

#ifndef ASTARNODE_H_
#define ASTARNODE_H_

#include "../types.h"
#include "Node.h"
#include "MazeArray.h"
#include "../RobotHandler.h"

typedef struct AStarNode_st
{
	node* informationNode_pst;
	struct AStarNode_st* cameFromNode_pst;

	int32 gScore_i32;
	int32 hScore_i32;
	int32 fScore_i32;

} aStarNode;

aStarNode* createEmptyAStarNode();

aStarNode* createAStarNode(node* f_inputInfoNode_pst);

void setInformationPtr(aStarNode* f_inputAStarNode_pst, node* f_inputInfoNode_pst);

node* getInformationPtr(aStarNode* f_inputAStarNode_pst);

void setCameFromPtr(aStarNode* f_inputAStarNode_pst, aStarNode* f_inputCameFromNode_pst);

aStarNode* getCameFromPtr(aStarNode* f_inputAStarNode_pst);

void setGScore (aStarNode* f_inputAStarNode_pst, int32 f_inputscore_i32);

int32 getGScore (aStarNode* f_inputAStarNode_pst);

void setHScore (aStarNode* f_inputAStarNode_pst, int32 f_inputscore_i32);

int32 getHScore (aStarNode* f_inputAStarNode_pst);

void setFScore (aStarNode* f_inputAStarNode_pst, int32 f_inputGscore_i32, int32 f_inputHscore_i32);

int32 getFScore (aStarNode* f_inputAStarNode_pst);

void setAllInfoAStarNode(aStarNode* f_inputAStarNode_pst, node* f_inputInfoNode_pst,
						 aStarNode* f_inputCameFromNode_pst, int32 f_inputGscore_i32,
						 int32 f_inputHscore_i32);

typedef struct AStarListNode_st
{
	aStarNode* aStarNode_pst;

	struct AStarListNode_st* prev;
	struct AStarListNode_st* next;

} aStarListNode;

typedef struct AStarList_st
{
	aStarListNode* head;
	aStarListNode* tail;
	int32 listSize;
} aStarList;

// Functions

aStarListNode* createAStarListNode();

aStarList* createAStarList();

bool isAStarListEmpty(aStarList* f_aStarList_pst);

aStarListNode* searchAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst);

aStarListNode* searchNeighbourInAStarList(aStarList* f_aStarList_pst, node* f_inputNode_pst);

bool isPresentInList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst);

bool isNeighbourPresentInList(aStarList* f_aStarList_pst, node* f_inputNode_pst);

bool addToFrontAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst);

bool addToEndAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst);

void removeAStarListEnd(aStarList* f_aStarList_pst);

void removeFromAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst);

void destroyAStarList(aStarList* f_aStarList_pst);

#endif /* ASTARNODE_H_ */
