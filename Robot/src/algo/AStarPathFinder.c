/*
 * AStarPathFinder.c
 *
 *  Created on: 17.11.2014
 *      Author: Manojkumar
 */

#include "../../h/algo/AStarPathFinder.h"

#include "../../h/algo/Algo.h"

aStarNode* getLowest(aStarList* f_aStarList_pst)
{
	aStarNode* lowestFscoreNode_pst = NULL;
	int32 lowestFscore_i32;

	aStarListNode* current = f_aStarList_pst ->head;

	lowestFscoreNode_pst = current ->aStarNode_pst;
	lowestFscore_i32 = lowestFscoreNode_pst ->fScore_i32;

	while (NULL != current ->next)
	{
		if (current ->aStarNode_pst ->fScore_i32 < lowestFscore_i32)
		{
			lowestFscore_i32 = current ->aStarNode_pst ->fScore_i32;
			lowestFscoreNode_pst = current ->aStarNode_pst;
		}

		current = current ->next;
	}

	return lowestFscoreNode_pst;
}

int32 heuristicEstimate(node* f_startNode_pst, node* f_inputNode_pst, node* f_endNode_pst)
{
	coordinates startNodeCoord_st =  getNodeCoordinates(f_startNode_pst);
	coordinates inputNodeCoord_st =  getNodeCoordinates(f_inputNode_pst);
	coordinates endNodeCoord_st =  getNodeCoordinates(f_endNode_pst);

	// Manhattan heuristic with cross-product tie breaker
	int32 diff_x1 = inputNodeCoord_st.x_Coordinate_i32 - endNodeCoord_st.x_Coordinate_i32;
	int32 diff_y1 = inputNodeCoord_st.y_Coordinate_i32 - endNodeCoord_st.y_Coordinate_i32;

	int32 diff_x2 = startNodeCoord_st.x_Coordinate_i32 - endNodeCoord_st.x_Coordinate_i32;
	int32 diff_y2 = startNodeCoord_st.y_Coordinate_i32 - endNodeCoord_st.y_Coordinate_i32;

	int32 heuristic_i32  = abs(diff_x1) + abs(diff_y1);

	int32 crossProduct_i32 = abs((diff_x1 * diff_y2) - (diff_x2 * diff_y1));

	heuristic_i32 += crossProduct_i32;

	return heuristic_i32;
}

neighbourList* reconstructPath(aStarNode* f_startAStarNode_pst, aStarNode* f_endAStarNode_pst)
{
	neighbourList* NeighbourList_pst = createNeghbourList();

	bool neighbourListUpdateflag_bl = FALSE;

	aStarNode* currentAstarNode_pst = f_endAStarNode_pst;

	while(NULL != currentAstarNode_pst ->cameFromNode_pst)
	{
		neighbourListUpdateflag_bl &= addToFrontNeighbourList(NeighbourList_pst, currentAstarNode_pst ->informationNode_pst);

		currentAstarNode_pst = currentAstarNode_pst ->cameFromNode_pst;
	}

	return NeighbourList_pst;
}

neighbourList* aStarPathFinder(node* f_startNode_pst, node* f_endNode_pst)
{
	int32 unitGscore_i32 = 1;
	int32 gScoreStart_i32 = 0;
	int32 hScoreStart_i32;

	aStarNode* startAStarNode = createAStarNode(f_startNode_pst);
	aStarNode* startCameFrom_pst = NULL;

	aStarList* openAStarList_pst = createAStarList();
	aStarList* closedAStarList_pst = createAStarList();

	if(startAStarNode && openAStarList_pst && closedAStarList_pst)
	{
		hScoreStart_i32 = heuristicEstimate(f_startNode_pst, f_startNode_pst, f_endNode_pst);

		setAllInfoAStarNode(startAStarNode, f_startNode_pst, startCameFrom_pst, gScoreStart_i32, hScoreStart_i32);

		addToEndAStarList(openAStarList_pst, startAStarNode);

		while(!isAStarListEmpty(openAStarList_pst))
		{
			aStarNode* LowestFscoreNode_pst = getLowest(openAStarList_pst);

			if (f_endNode_pst == LowestFscoreNode_pst ->informationNode_pst)
			{
				// Reconstruct path, destroy the AStarlists created above
				// and return the node list to process

				neighbourList* AstarPath_pst = reconstructPath(startAStarNode, LowestFscoreNode_pst);

				destroyAStarList(openAStarList_pst);
				destroyAStarList(closedAStarList_pst);

				return AstarPath_pst;

			}

			removeFromAStarList(openAStarList_pst, LowestFscoreNode_pst);
			addToEndAStarList(closedAStarList_pst, LowestFscoreNode_pst);

			node* currentNode_pst = LowestFscoreNode_pst ->informationNode_pst;

			neighbourList* NeighbourList_pst = getNeighbourList(currentNode_pst);

			if(!isNeighbourListEmpty(NeighbourList_pst))
			{
				neighbourListNode* nextNeighbour_pst = NULL;

				neighbourListNode* neighbour_pst = NeighbourList_pst->head;

				for (; neighbour_pst != NULL; neighbour_pst = nextNeighbour_pst)
			   	{
			   		nextNeighbour_pst = neighbour_pst->next;

			   		node* neighbourNode_pst = neighbour_pst ->neighbourNode_pst;

			   		if(searchNeighbourInAStarList(closedAStarList_pst, neighbourNode_pst))
			   		{
			   			continue;
			   		}

			   		int32 neighbourGscore_i32 = LowestFscoreNode_pst ->gScore_i32 + unitGscore_i32;

			   		aStarListNode* searchResult_pst = searchNeighbourInAStarList(openAStarList_pst, neighbourNode_pst);

			   		if (!searchResult_pst)
			   		{
			   			aStarNode* neighbourAStarNode = createAStarNode(neighbourNode_pst);

			   			int32 neighbourHscore_i32 = heuristicEstimate(f_startNode_pst, neighbourNode_pst, f_endNode_pst);

			   			setAllInfoAStarNode(neighbourAStarNode, neighbourNode_pst, LowestFscoreNode_pst,
			   								neighbourGscore_i32, neighbourHscore_i32);

			   			addToEndAStarList(openAStarList_pst, neighbourAStarNode);
			   		}
			   		else if (neighbourGscore_i32 < searchResult_pst ->aStarNode_pst ->gScore_i32)
			   		{
			   			aStarNode* neighbourAStarNode = searchResult_pst ->aStarNode_pst;

			   			setCameFromPtr(neighbourAStarNode, LowestFscoreNode_pst);
			   			setGScore(neighbourAStarNode, neighbourGscore_i32);
			   			setFScore(neighbourAStarNode, neighbourGscore_i32, neighbourAStarNode ->hScore_i32);
			   		}
			   	}
			}

			destroyNeighbourList(NeighbourList_pst);
		}

		return NULL;
	}

	return NULL;
}

int32 processAStarPath(neighbourList* f_aStarPathList_pst)
{
	int32 moveResult_i32 = 0x00;

	if(!isNeighbourListEmpty(f_aStarPathList_pst))
	{
		neighbourListNode* nextMove_pst = NULL;

		neighbourListNode* neighbour_pst = f_aStarPathList_pst->head;

		for (; neighbour_pst != NULL; neighbour_pst = nextMove_pst)
		{
			nextMove_pst = neighbour_pst->next;

			node* moveNode_pst = neighbour_pst ->neighbourNode_pst;

			coordinates moveNodeCoord_st =  getNodeCoordinates(moveNode_pst);

			moveResult_i32 = Robot_Move(moveNodeCoord_st.x_Coordinate_i32, moveNodeCoord_st.y_Coordinate_i32);

			if (ROBOT_FAIL == moveResult_i32)
			{
				return moveResult_i32;
			}
			else
			{
				setCurrentNode(moveNode_pst);
			}
		}
	}

	return moveResult_i32;
}




