/*
 * DeadEndHandler.c
 *
 *  Created on: 18.11.2014
 *      Author: Manojkumar
 */

#include "../h/DeadEndHandler.h"

void setNeighbourNodes(node* f_inputNode_pst, node* f_neighbourNode_pst)
{
	directionsFlag availableDirectionsFlag_st = getAvailableDirectionsFlag(f_inputNode_pst);

	if (true == availableDirectionsFlag_st.isSouthAvailable_bl)
	{
		f_inputNode_pst ->south_pst = f_neighbourNode_pst;
	}
	else if (true == availableDirectionsFlag_st.isEastAvailable_bl)
	{
		f_inputNode_pst ->east_pst = f_neighbourNode_pst;
	}
	else if (true == availableDirectionsFlag_st.isNorthAvailable_bl)
	{
		f_inputNode_pst ->north_pst = f_neighbourNode_pst;
	}
	else if (true == availableDirectionsFlag_st.isWestAvailable_bl)
	{
		f_inputNode_pst ->west_pst = f_neighbourNode_pst;
	}
}

node* checkAndMoveFromDeadEnd(node* f_inputNode_pst,node* f_inputPrevNode_pst)
{
	int32 northIterator_i32 = 4;
	int32 eastIterator_i32 = 7;

	node* lastUncoveredNode_pst = NULL;

	int32 availablDirectionsNode_i32 = getAvailableDirections(f_inputNode_pst);

	int32 foundDeadEnd = 0;

	int32 deadEndChecker = 0x01;

	int32 it = northIterator_i32;

	for (; it <= eastIterator_i32; it++)
	{
		foundDeadEnd = ((availablDirectionsNode_i32 >> it) & deadEndChecker) + foundDeadEnd;
	}

	if (deadEndChecker == foundDeadEnd)
	{
		// set the previousNode to the current dead-end node's neighbour node!!!
		setNeighbourNodes(f_inputNode_pst, f_inputPrevNode_pst);

		// it is a dead end, find the last node with uncovered directions
		lastUncoveredNode_pst = getLastUncoveredNode();

		if (NULL == lastUncoveredNode_pst)
		{
			// go back to origin via A* Path
			// return origin Node ptr
			// but check out the cases for token!!
		}
		else
		{
			// go  to that node via a shortest path
			// needed a A* Algorithm

			neighbourList* AStarPathList_pst = aStarPathFinder(f_inputNode_pst, lastUncoveredNode_pst);

			processAStarPath(AStarPathList_pst);

			destroyNeighbourList(AStarPathList_pst);

			return lastUncoveredNode_pst;
		}

	}
	else
	{
		// not a dead end, return the input node
		return f_inputNode_pst;
	}
}
