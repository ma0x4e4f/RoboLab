/*
 * Node.c
 *
 *  Created on: 02.11.2014
 *      Author: Manojkumar
 */

#include "../h/Node.h"

void initNode(node* f_inputNode_pst)
{
	f_inputNode_pst -> xy_st.x_Coordinate_i32 = 0;
	f_inputNode_pst -> xy_st.y_Coordinate_i32 = 0;

	f_inputNode_pst -> availableDirections_i32 = NULLDIRECTION;
	f_inputNode_pst -> unCoveredDirections_i32 = NULLDIRECTION;

	f_inputNode_pst -> north_pst = NULL;
	f_inputNode_pst -> south_pst = NULL;
	f_inputNode_pst -> east_pst = NULL;
	f_inputNode_pst -> west_pst = NULL;

	//	f_inputNode_pst -> origin_bl = false;
}


bool setNodeCoordinates(node* f_inputNode_pst, int32 f_xCord_i32, int32 f_yCord_i32)
{
	f_inputNode_pst -> xy_st.x_Coordinate_i32 = f_xCord_i32;
	f_inputNode_pst -> xy_st.y_Coordinate_i32 = f_yCord_i32;

	return true;
}

coordinates getNodeCoordinates(node* f_inputNode_pst)
{
	return f_inputNode_pst -> xy_st;
}

void setAvailableDirections(node* f_inputNode_pst, int32 f_availableDirections_i32)
{
	f_inputNode_pst -> availableDirections_i32 = f_availableDirections_i32;
	f_inputNode_pst -> unCoveredDirections_i32 = f_availableDirections_i32;
}

int32 getAvailableDirections(node* f_inputNode_pst)
{
	return f_inputNode_pst -> availableDirections_i32;
}

void setCoveredDirection(node* f_inputNode_pst, int32 f_direction_i32)
{
	int32 uncoveredDir_i32 = 0x00;

	if (NORTH == f_direction_i32)
	{
		uncoveredDir_i32 = f_inputNode_pst ->unCoveredDirections_i32 & NORTHCOVERED;
		setUnCoveredDirections(f_inputNode_pst, uncoveredDir_i32);
	}

	if (SOUTH == f_direction_i32)
	{
		uncoveredDir_i32 = f_inputNode_pst ->unCoveredDirections_i32 & SOUTHCOVERED;
		setUnCoveredDirections(f_inputNode_pst, uncoveredDir_i32);
	}

	if (EAST == f_direction_i32)
	{
		uncoveredDir_i32 = f_inputNode_pst ->unCoveredDirections_i32 & EASTCOVERED;
		setUnCoveredDirections(f_inputNode_pst, uncoveredDir_i32);
	}

	if (WEST == f_direction_i32)
	{
		uncoveredDir_i32 = f_inputNode_pst ->unCoveredDirections_i32 & WESTCOVERED;
		setUnCoveredDirections(f_inputNode_pst, uncoveredDir_i32);
	}


}

void setUnCoveredDirections(node* f_inputNode_pst, int32 f_unCoveredDirections_i32)
{
	f_inputNode_pst -> unCoveredDirections_i32 = f_unCoveredDirections_i32;
}

int32 getUnCoveredDirections(node* f_inputNode_pst)
{
	return f_inputNode_pst -> unCoveredDirections_i32;
}
