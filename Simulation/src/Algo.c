/*
 * Algo.c
 *
 *  Created on: 07.11.2014
 *      Author: Manojkumar
 */

#include "../h/Algo.h"

directionsFlag getAvailableDirectionsFlag(node* f_inputNode_pst)
{
	directionsFlag directionsFlag_st;

	int32 availableDirections_i32 = getAvailableDirections(f_inputNode_pst);

	directionsFlag_st.isNorthAvailable_bl =  (availableDirections_i32 & NORTH) == (NORTH);
	directionsFlag_st.isSouthAvailable_bl =  (availableDirections_i32 & SOUTH) == (SOUTH);
	directionsFlag_st.isWestAvailable_bl =  (availableDirections_i32 & WEST) == (WEST);
	directionsFlag_st.isEastAvailable_bl =  (availableDirections_i32 & EAST) == (EAST);

	return directionsFlag_st;
}

directionsFlag getUncoveredDirectionsFlag(node* f_inputNode_pst)
{
	directionsFlag directionsFlag_st;

	int32 uncoveredDirections_i32 = getUnCoveredDirections(f_inputNode_pst);

	directionsFlag_st.isNorthAvailable_bl =  (uncoveredDirections_i32 & NORTH) == (NORTH);
	directionsFlag_st.isSouthAvailable_bl =  (uncoveredDirections_i32 & SOUTH) == (SOUTH);
	directionsFlag_st.isWestAvailable_bl =  (uncoveredDirections_i32 & WEST) == (WEST);
	directionsFlag_st.isEastAvailable_bl =  (uncoveredDirections_i32 & EAST) == (EAST);

	return directionsFlag_st;
}

void checkToken(int32 f_moveResult_i32)
{
	if (ROBOT_TOKENFOUND == f_moveResult_i32)
	{
		tokenCount_i32++;

		if (MAX_TOKENS == tokenCount_i32)
		{
			isTokensCollected_bl = true;
		}
	}
}

bool initRobotAlgo()
{
	int32 origin_x_i32 = 0;
	int32 origin_y_i32 = 0;

	int32 availableDirections_i32 = Robot_GetIntersections();

	printf("Initial Available dir: %x\n", availableDirections_i32);

	if(NULLDIRECTION != availableDirections_i32)
	{
		node* node_pst = setMazeArrayElement(origin_x_i32, origin_y_i32, availableDirections_i32);

		if (NULL != node_pst)
		{
			currentNode_pst = node_pst;
			originNode_pst = node_pst;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}


//	call  the below command only in ROBOT, but not sure
//	setCoveredDirection(currentNode_pst, SOUTH);
//	currentOrientation_i32 = NORTH;

//	currentNode_pst = getOriginNode();

}

int32 robotAlgoMove(int32 f_moveCord_x_i32, int32 f_moveCord_y_i32)
{
	printf("Moving to coordinate (%d,%d)\n", f_moveCord_x_i32, f_moveCord_y_i32);
	return Robot_Move(f_moveCord_x_i32, f_moveCord_y_i32);
}

int32 checkAndMoveWest(node* f_inputNode_pst)
{
	coordinates nodeCord_st;
	node* moveNode_pst = NULL;

	int moveResult_i32 = ALGO_FAIL;

	nodeCord_st = getNodeCoordinates(f_inputNode_pst);
	// Un-comment the below line if needed
	directionsFlag uncoveredDirectionsFlag_st = getUncoveredDirectionsFlag(f_inputNode_pst);

	int32 moveCord_x_i32 = nodeCord_st.x_Coordinate_i32 - 1;
	int32 moveCord_y_i32 = nodeCord_st.y_Coordinate_i32;

	moveNode_pst = searchMazeArray(moveCord_x_i32, moveCord_y_i32);

	if (NULL != moveNode_pst)
	{
		int32 unCoveredDirMoveNode_i32 = getUnCoveredDirections(moveNode_pst);

		if (EAST == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(currentNode_pst, WEST);
			setCoveredDirection(moveNode_pst, EAST);

			// consideration No.7: call a specific function in the confused state (state where no
			// valid uncovered direction available for current node
			return ALGO_CONFUSED;
		}
		else // unCoveredDirMoveNode_i32 contains more than EAST
		{
			moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{
				previousNode_pst = currentNode_pst;
				currentNode_pst = moveNode_pst;
				checkToken(moveResult_i32);

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
	else // false == searchResult_bl
	{
		moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = currentNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();
			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst)
			{
				currentNode_pst = moveNode_pst;
			}
			else
			{
				return CHECK_NOT_OK;
			}
			setCoveredDirection(previousNode_pst, WEST);
			setCoveredDirection(currentNode_pst, EAST);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}

	return ALGO_CONFUSED;
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

		if (SOUTH == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, NORTH);
			setCoveredDirection(moveNode_pst, SOUTH);
			
			if (true == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(f_inputNode_pst);
			}
			
			return moveResult_i32;

			// check other remaining direction here and if nothing available, do the below command
			// consideration No.7: call a specific function in the confused state
		}
		else // unCoveredDirMoveNode_i32 contains more than SOUTH
		{
			moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{
				previousNode_pst = f_inputNode_pst;
				currentNode_pst = moveNode_pst;
				checkToken(moveResult_i32);

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
	else // false == searchResult_bl
	{
		moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = f_inputNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();
			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst)
			{
				currentNode_pst = moveNode_pst;
			}
			else
			{
				return CHECK_NOT_OK;
			}

			setCoveredDirection(previousNode_pst, NORTH);
			setCoveredDirection(currentNode_pst, SOUTH);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}

	return ALGO_CONFUSED;
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

		if (WEST == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, EAST);
			setCoveredDirection(moveNode_pst, WEST);

			if (true == uncoveredDirectionsFlag_st.isNorthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveNorth(f_inputNode_pst);
			}
			else if (true == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(f_inputNode_pst);
			}

			return moveResult_i32;

			// check other remaining direction here and if nothing available, do the below command
			// consideration No.7: call a specific function in the confused state
		}
		else // unCoveredDirMoveNode_i32 contains more than WEST
		{
			moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{
				previousNode_pst = f_inputNode_pst;
				currentNode_pst = moveNode_pst;
				checkToken(moveResult_i32);

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
	else // false == searchResult_bl
	{
		moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = f_inputNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();
			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst)
			{
				currentNode_pst = moveNode_pst;
			}
			else
			{
				return CHECK_NOT_OK;
			}

			setCoveredDirection(previousNode_pst, EAST);
			setCoveredDirection(currentNode_pst, WEST);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}

	return ALGO_CONFUSED;
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

		if (NORTH == unCoveredDirMoveNode_i32)
		{
			setCoveredDirection(f_inputNode_pst, SOUTH);
			setCoveredDirection(moveNode_pst, NORTH);

			if (true == uncoveredDirectionsFlag_st.isEastAvailable_bl)
			{
				moveResult_i32 = checkAndMoveEast(f_inputNode_pst);
			}
			else if (true == uncoveredDirectionsFlag_st.isNorthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveNorth(f_inputNode_pst);
			}
			else if (true == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(f_inputNode_pst);
			}

			return moveResult_i32;

			// check other remaining direction here and if nothing available, do the below command
			// consideration No.7: call a specific function in the confused state
		}
		else // unCoveredDirMoveNode_i32 contains more than NORTH
		{
			moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
			if (ROBOT_FAIL != moveResult_i32)
			{
				previousNode_pst = f_inputNode_pst;
				currentNode_pst = moveNode_pst;
				checkToken(moveResult_i32);

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
	else // Unsuccessful search
	{
		moveResult_i32 = robotAlgoMove(moveCord_x_i32, moveCord_y_i32);
		if (ROBOT_FAIL != moveResult_i32)
		{
			previousNode_pst = f_inputNode_pst;
			checkToken(moveResult_i32);
			int32 availableDirMoveNode_i32 = Robot_GetIntersections();
			moveNode_pst = setMazeArrayElement(moveCord_x_i32, moveCord_y_i32, availableDirMoveNode_i32);

			if (NULL != moveNode_pst)
			{
				currentNode_pst = moveNode_pst;
			}
			else
			{
				return CHECK_NOT_OK;
			}

			setCoveredDirection(previousNode_pst, SOUTH);
			setCoveredDirection(currentNode_pst, NORTH);

			return CHECK_OK;
		}
		else
		{
			return CHECK_NOT_OK;
		}
	}

	return ALGO_CONFUSED;
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
		f_inputNode_pst->east_pst = westNode_pst;
		westNode_pst->east_pst = f_inputNode_pst;

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
		f_inputNode_pst->north_pst = northNode_pst;
		northNode_pst->south_pst = f_inputNode_pst;

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
		f_inputNode_pst->east_pst = eastNode_pst;
		eastNode_pst->west_pst = f_inputNode_pst;

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
		f_inputNode_pst->south_pst = southNode_pst;
		southNode_pst->north_pst = f_inputNode_pst;

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

	if (true == availableDirFlag_st.isSouthAvailable_bl)
	{
		reviewSouth(f_inputNode_pst);
	}

	if (true == availableDirFlag_st.isEastAvailable_bl)
	{
		reviewEast(f_inputNode_pst);
	}

	if (true == availableDirFlag_st.isNorthAvailable_bl)
	{
		reviewNorth(f_inputNode_pst);
	}

	if (true == availableDirFlag_st.isWestAvailable_bl)
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
//	bool searchResult_bl = false;

	while( (!isMazeExplored_bl || !isTokensCollected_bl) && (100 > timeout_ui32) )
	{
		if(NULL != currentNode_pst)
		{
			moveResult_i32 = 0;

			timeout_ui32 = 0;

			reviewNeighbours(currentNode_pst);

			directionsFlag uncoveredDirectionsFlag_st = getUncoveredDirectionsFlag(currentNode_pst);

			if (true == uncoveredDirectionsFlag_st.isSouthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveSouth(currentNode_pst);
			}
			else if (true == uncoveredDirectionsFlag_st.isEastAvailable_bl)
			{
				moveResult_i32 = checkAndMoveEast(currentNode_pst);
			}
			else if (true == uncoveredDirectionsFlag_st.isNorthAvailable_bl)
			{
				moveResult_i32 = checkAndMoveNorth(currentNode_pst);
			}
			else if (true == uncoveredDirectionsFlag_st.isWestAvailable_bl)
			{
				moveResult_i32 = checkAndMoveWest(currentNode_pst);
			}

			if (ALGO_CONFUSED == moveResult_i32)
			{
				return ALGO_CONFUSED;
			}

			if (CHECK_OK != moveResult_i32)
			{
				return ALGO_FAIL;
			}
		}
		else
		{
			timeout_ui32++;
		}
	}

	if (100 == timeout_ui32)
	{
		return ALGO_TIMEOUT;
	}

	if (true == isTokensCollected_bl)
	{
		return ALGO_TOKENS_COLLECTED;
	}
	else
	{
		return ALGO_EXPLORED;
	}
}

