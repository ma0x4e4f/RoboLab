/*
 * Algo.c
 *
 *  Created on: 07.11.2014
 *      Author: Manojkumar
 */

#include "../../h/algo/Algo.h"

bool isMazeExplored_bl = FALSE;
static uint32 timeout_ui32 = 0;
node* originNode_pst = NULL;

bool isTokensCollected_bl = FALSE;
int32 tokenCount_i32 = 0;

bool initRobotAlgo(int originMoveResult_i32)
{
	int32 origin_x_i32 = 0;
	int32 origin_y_i32 = 0;

	int32 availableDirections_i32 = Robot_GetIntersections();

//	printf("Initial Available dir: %x\n", availableDirections_i32);

	if(NULLDIRECTION != availableDirections_i32)
	{
		checkToken(originMoveResult_i32);

		node* node_pst = setMazeArrayElement(origin_x_i32, origin_y_i32, availableDirections_i32);

		if (NULL != node_pst)
		{
			currentNode_pst = node_pst;
			originNode_pst = node_pst;

			setCoveredDirection(currentNode_pst, SOUTH);

			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}


//	call  the below command only in ROBOT, but not sure
//	setCoveredDirection(currentNode_pst, SOUTH);
//	currentOrientation_i32 = NORTH;

//	currentNode_pst = getOriginNode();

}

void checkToken(int32 f_moveResult_i32)
{
	if (ROBOT_TOKENFOUND == f_moveResult_i32)
	{
		tokenCount_i32++;

		if (MAX_TOKENS == tokenCount_i32)
		{
			isTokensCollected_bl = TRUE;
		}
	}
}

node* getCurretnNode()
{
	return currentNode_pst;
}

void setCurrentNode(node* f_inputCurrentNode_pst)
{
	currentNode_pst = f_inputCurrentNode_pst;
}

int32 checkAndMoveWest(node* f_inputNode_pst)
{
//	printString("enter cmwest");

	coordinates nodeCord_st;
	node* moveNode_pst = NULL;

	int moveResult_i32 = ALGO_FAIL;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);
	// Un-comment the below line if needed
//	directionsFlag uncoveredDirectionsFlag_st = getUncoveredDirectionsFlag(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32 - 1;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32;

	moveNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != moveNode_pst)
	{
		int32 unCoveredDirMoveNode_i32 = getUnCoveredDirections(moveNode_pst);

		setWestNode(f_inputNode_pst, moveNode_pst);
		setEastNode(moveNode_pst, f_inputNode_pst);

		if (EAST == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, WEST);
			setCoveredDirection(moveNode_pst, EAST);

			// As per design it should not come here
			return CHECK_NOT_OK;
		}
		else if (NULLDIRECTION != unCoveredDirMoveNode_i32) // unCoveredDirMoveNode_i32 contains more than EAST
		{
			moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{
				previousNode_pst = f_inputNode_pst;
				currentNode_pst = moveNode_pst;
//				checkToken(moveResult_i32); // Don't check token for already visited Node

				setCoveredDirection(previousNode_pst, WEST);
				setCoveredDirection(currentNode_pst, EAST);

				return CHECK_OK;
			}
			else
			{
				return CHECK_NOT_OK;
			}
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
	else // FALSE == searchResult_bl
	{
		moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = f_inputNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();
			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst && NULLDIRECTION != availableDirMoveNode_i32)
			{
				currentNode_pst = moveNode_pst;
//				ecrobot_status_monitor("correctW exec");
			}
			else
			{
				return CHECK_NOT_OK;
			}

			setWestNode(f_inputNode_pst, moveNode_pst);
			setEastNode(moveNode_pst, f_inputNode_pst);

			setCoveredDirection(previousNode_pst, WEST);
			setCoveredDirection(currentNode_pst, EAST);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
}

int32 checkAndMoveNorth(node* f_inputNode_pst)
{
	coordinates nodeCord_st;
	node* moveNode_pst = NULL;

	int moveResult_i32 = CHECK_NOT_OK;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);
	directionsFlag uncoveredDirectionsFlag_st = getUncoveredDirectionsFlag(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32 + 1;

	moveNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != moveNode_pst)
	{
		int32 unCoveredDirMoveNode_i32 = getUnCoveredDirections(moveNode_pst);

		setNorthNode(f_inputNode_pst, moveNode_pst);
		setSouthNode(moveNode_pst, f_inputNode_pst);

		if (SOUTH == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, NORTH);
			setCoveredDirection(moveNode_pst, SOUTH);

			if (TRUE == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(f_inputNode_pst);
			}
			else
			{
				// As per design it should not come here
				return CHECK_NOT_OK;
			}
		}
		else if (NULLDIRECTION != unCoveredDirMoveNode_i32) // unCoveredDirMoveNode_i32 contains more than SOUTH
		{
			moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{


				previousNode_pst = f_inputNode_pst;
				currentNode_pst = moveNode_pst;
//				checkToken(moveResult_i32); // Don't check token for already visited Node

				setCoveredDirection(previousNode_pst, NORTH);
				setCoveredDirection(currentNode_pst, SOUTH);

				return CHECK_OK;
			}
			else
			{
				return CHECK_NOT_OK;
			}
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
	else // FALSE == searchResult_bl
	{
		moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = f_inputNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();
			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst && NULLDIRECTION != availableDirMoveNode_i32)
			{
				currentNode_pst = moveNode_pst;
//				ecrobot_status_monitor("correctN exec");
			}
			else
			{
				return CHECK_NOT_OK;
			}

			setNorthNode(f_inputNode_pst, moveNode_pst);
			setSouthNode(moveNode_pst, f_inputNode_pst);

			setCoveredDirection(previousNode_pst, NORTH);
			setCoveredDirection(currentNode_pst, SOUTH);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
}

int32 checkAndMoveEast(node* f_inputNode_pst)
{
	coordinates nodeCord_st;
	node* moveNode_pst = NULL;

	int moveResult_i32 = CHECK_NOT_OK;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);
	directionsFlag uncoveredDirectionsFlag_st = getUncoveredDirectionsFlag(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32 + 1;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32;

	moveNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != moveNode_pst)
	{
		int32 unCoveredDirMoveNode_i32 = getUnCoveredDirections(moveNode_pst);

		setEastNode(f_inputNode_pst, moveNode_pst);
		setWestNode(moveNode_pst, f_inputNode_pst);

		if (WEST == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, EAST);
			setCoveredDirection(moveNode_pst, WEST);

			if (TRUE == uncoveredDirectionsFlag_st.isNorthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveNorth(f_inputNode_pst);
			}
			else if (TRUE == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(f_inputNode_pst);
			}
			else
			{
				// As per design it should not come here
				return CHECK_NOT_OK;
			}
		}
		else if (NULLDIRECTION != unCoveredDirMoveNode_i32) // unCoveredDirMoveNode_i32 contains more than WEST
		{
			moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{
				previousNode_pst = f_inputNode_pst;
				currentNode_pst = moveNode_pst;
//				checkToken(moveResult_i32); // Don't check token for already visited Node

				setCoveredDirection(previousNode_pst, EAST);
				setCoveredDirection(currentNode_pst, WEST);

				return CHECK_OK;
			}
			else
			{
				return CHECK_NOT_OK;
			}
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
	else // FALSE == searchResult_bl
	{
		moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = f_inputNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();
			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst && NULLDIRECTION != availableDirMoveNode_i32)
			{
				currentNode_pst = moveNode_pst;
//				ecrobot_status_monitor("correctE exec");
			}
			else
			{
				return CHECK_NOT_OK;
			}

			setEastNode(f_inputNode_pst, moveNode_pst);
			setWestNode(moveNode_pst, f_inputNode_pst);

			setCoveredDirection(previousNode_pst, EAST);
			setCoveredDirection(currentNode_pst, WEST);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
}

int32 checkAndMoveSouth(node* f_inputNode_pst)
{


	coordinates nodeCord_st;
	node* moveNode_pst = NULL;

	int moveResult_i32 = ALGO_FAIL;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);
	directionsFlag uncoveredDirectionsFlag_st = getUncoveredDirectionsFlag(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32 - 1;

	moveNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != moveNode_pst)
	{
		int32 unCoveredDirMoveNode_i32 = getUnCoveredDirections(moveNode_pst);

		setSouthNode(f_inputNode_pst, moveNode_pst);
		setNorthNode(moveNode_pst, f_inputNode_pst);

		if (NORTH == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, SOUTH);
			setCoveredDirection(moveNode_pst, NORTH);

			if (TRUE == uncoveredDirectionsFlag_st.isEastAvailable_bl)
			{
				moveResult_i32 = checkAndMoveEast(f_inputNode_pst);
			}
			else if (TRUE == uncoveredDirectionsFlag_st.isNorthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveNorth(f_inputNode_pst);
			}
			else if (TRUE == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(f_inputNode_pst);
			}
			else
			{
				// As per design it should not come here
				return CHECK_NOT_OK;
			}
		}
		else if (NULLDIRECTION != unCoveredDirMoveNode_i32) // unCoveredDirMoveNode_i32 contains more than NORTH
		{
			moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{
				previousNode_pst = f_inputNode_pst;
				currentNode_pst = moveNode_pst;
//				checkToken(moveResult_i32); // Don't check token for already visited Node

				setCoveredDirection(previousNode_pst, SOUTH);
				setCoveredDirection(currentNode_pst, NORTH);

				return CHECK_OK;
			}
			else
			{
				return CHECK_NOT_OK;
			}
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
	else // Unsuccessful search
	{
		moveResult_i32 = Robot_Move(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = f_inputNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();

			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst && NULLDIRECTION != availableDirMoveNode_i32)
			{
				currentNode_pst = moveNode_pst;
//				ecrobot_status_monitor("correctW exec");
			}
			else
			{
				return CHECK_NOT_OK;
			}

			setSouthNode(f_inputNode_pst, moveNode_pst);
			setNorthNode(moveNode_pst, f_inputNode_pst);

			setCoveredDirection(previousNode_pst, SOUTH);
			setCoveredDirection(currentNode_pst, NORTH);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}
}

void reviewWest(node* f_inputNode_pst)
{
	coordinates nodeCord_st;
	node* westNode_pst = NULL;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32 - 1;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32;

	westNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != westNode_pst)
	{
		setWestNode(f_inputNode_pst, westNode_pst);
		setEastNode(westNode_pst, f_inputNode_pst);

		int32 unCoveredDirWestNode_i32 = getUnCoveredDirections(westNode_pst);
		if (EAST == unCoveredDirWestNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, WEST);
			setCoveredDirection(westNode_pst, EAST);
		}
		else
		{
			// Directions other than east is available, We might need to move there
			// So don't clear the directions
		}
	}
	else
	{
		// Still not visited the south node of the input node
	}

}

void reviewNorth(node* f_inputNode_pst)
{
	coordinates nodeCord_st;
	node* northNode_pst = NULL;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32 + 1;

	northNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != northNode_pst)
	{
		setNorthNode(f_inputNode_pst, northNode_pst);
		setSouthNode(northNode_pst, f_inputNode_pst);

		int32 unCoveredDirNorthNode_i32 = getUnCoveredDirections(northNode_pst);
		if (SOUTH == unCoveredDirNorthNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, NORTH);
			setCoveredDirection(northNode_pst, SOUTH);
		}
		else
		{
			// Directions other than south is available, We might need to move there
			// So don't clear the directions
		}
	}
	else
	{
		// Still not visited the south node of the input node
	}

}

void reviewEast(node* f_inputNode_pst)
{
	coordinates nodeCord_st;
	node* eastNode_pst = NULL;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32 + 1;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32;

	eastNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != eastNode_pst)
	{
		setEastNode(f_inputNode_pst, eastNode_pst);
		setWestNode(eastNode_pst, f_inputNode_pst);

		int32 unCoveredDirEastNode_i32 = getUnCoveredDirections(eastNode_pst);
		if (WEST == unCoveredDirEastNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, EAST);
			setCoveredDirection(eastNode_pst, WEST);
		}
		else
		{
			// Directions other than West is available, We might need to move there
			// So don't clear the directions
		}
	}
	else
	{
		// Still not visited the south node of the input node
	}

}

void reviewSouth(node* f_inputNode_pst)
{
	coordinates nodeCord_st;
	node* southNode_pst = NULL;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32 - 1;

	southNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != southNode_pst)
	{
		setSouthNode(f_inputNode_pst, southNode_pst);
		setNorthNode(southNode_pst, f_inputNode_pst);

		int32 unCoveredDirSouthNode_i32 = getUnCoveredDirections(southNode_pst);
		if (NORTH == unCoveredDirSouthNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, SOUTH);
			setCoveredDirection(southNode_pst, NORTH);
		}
		else
		{
			// Directions other than North is available, We might need to move there
			// So don't clear the directions
		}
	}
	else
	{
		// Still not visited the south node of the input node
	}

}

void reviewNeighbours(node* f_inputNode_pst)
{
	directionsFlag availableDirFlag_st;

	availableDirFlag_st = getAvailableDirectionsFlag(f_inputNode_pst);

	if (TRUE == availableDirFlag_st.isSouthAvailable_bl)
	{
		reviewSouth(f_inputNode_pst);
	}

	if (TRUE == availableDirFlag_st.isEastAvailable_bl)
	{
		reviewEast(f_inputNode_pst);
	}

	if (TRUE == availableDirFlag_st.isNorthAvailable_bl)
	{
		reviewNorth(f_inputNode_pst);
	}

	if (TRUE == availableDirFlag_st.isWestAvailable_bl)
	{
		reviewWest(f_inputNode_pst);
	}
}


int32 startRobotAlgo()
{
	int32 moveResult_i32 = 0;
//	coordinates* nodeCord_pst;
//
//	int32 moveCord_x_i32 = 0;
//	int32 moveCord_y_i32 = 0;
//
//	node* moveNode_pst = NULL;
//	bool searchResult_bl = FALSE;

	while((!isMazeExplored_bl) && (!isTokensCollected_bl) && (100 > timeout_ui32))
	{
		if(NULL != currentNode_pst)
		{
			moveResult_i32 = ALGO_FAIL;

			timeout_ui32 = 0;

			node* movedIfDeadEndNode_pst = checkAndMoveFromDeadEnd(currentNode_pst, previousNode_pst);

			if (NULL != movedIfDeadEndNode_pst)
			{
				currentNode_pst = movedIfDeadEndNode_pst;
			}

			reviewNeighbours(currentNode_pst);

			directionsFlag uncoveredDirectionsFlag_st = getUncoveredDirectionsFlag(currentNode_pst);

			if (TRUE == uncoveredDirectionsFlag_st.isSouthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveSouth(currentNode_pst);
			}
			else if (TRUE == uncoveredDirectionsFlag_st.isEastAvailable_bl)
			{
				moveResult_i32 = checkAndMoveEast(currentNode_pst);
			}
			else if (TRUE == uncoveredDirectionsFlag_st.isNorthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveNorth(currentNode_pst);
			}
			else if (TRUE == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(currentNode_pst);
			}
			else
			{
				node* lastUncoveredNode_pst = NULL;

				// Confused state don't know where to go, check the last uncovered node
				lastUncoveredNode_pst = getLastUncoveredNode();

				// If nothing available exit the function, HURRAY! we explored the whole Maze!
				if (NULL == lastUncoveredNode_pst)
				{
					// go back to origin via A* Path
					// return origin Node ptr
					// but check out the cases for token!!
//					neighbourList* AStarPathList_pst = aStarPathFinder(currentNode_pst, originNode_pst);
//					moveResult_i32 = processAStarPath(AStarPathList_pst);
//					destroyNeighbourList(AStarPathList_pst);
//					currentNode_pst = originNode_pst;
					isMazeExplored_bl = TRUE;
					break;
				}
				else
				{
					// go  to that node via a shortest path
					// needed a A* Algorithm
					neighbourList* AStarPathList_pst = aStarPathFinder(currentNode_pst, lastUncoveredNode_pst);
					moveResult_i32 = processAStarPath(AStarPathList_pst);
					destroyNeighbourList(AStarPathList_pst);
					currentNode_pst = lastUncoveredNode_pst;
				}
			}

			if (ALGO_FAIL == moveResult_i32)
			{
				return ALGO_FAIL;
				ecrobot_status_monitor("Algo Error!");
			}

			if (TRUE == isTokensCollected_bl)
			{
				ecrobot_status_monitor("Returning to Origin");

				reviewNeighbours(currentNode_pst);
				neighbourList* AStarPathList_pst = aStarPathFinder(currentNode_pst, originNode_pst);
				processAStarPath(AStarPathList_pst);
				destroyNeighbourList(AStarPathList_pst);
				currentNode_pst = originNode_pst;
				return ALGO_TOKENS_COLLECTED;
			}
		}
		else
		{
			timeout_ui32++;
		}
	}

	if(isMazeExplored_bl)
	{
		ecrobot_status_monitor("Algo Explored!");
		sound_freq(500, 2000);
		systick_wait_ms(2000);
		return ALGO_EXPLORED;
	}

//	if (100 == timeout_ui32)
//	{
//		return ALGO_TIMEOUT;
//	}

	if (TRUE == isTokensCollected_bl)
	{
		return ALGO_TOKENS_COLLECTED;
	}
	else
	{
		return ALGO_EXPLORED;
	}
}

