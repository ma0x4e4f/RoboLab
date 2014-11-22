/*
 * Node.c
 *
 *  Created on: 02.11.2014
 *      Author: Manojkumar
 */

#include "../h/Node.h"

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

void setNorthNode(node* f_inputNode_pst, node* f_neighbourNode_pst)
{
	if ((NULL != f_neighbourNode_pst) && (NULL == f_inputNode_pst ->north_pst))
	{
		f_inputNode_pst ->north_pst = f_neighbourNode_pst;
	}
}

node* getNorthNode(node* f_inputNode_pst)
{
	return f_inputNode_pst ->north_pst;
}

void setSouthNode(node* f_inputNode_pst, node* f_neighbourNode_pst)
{
	if ((NULL != f_neighbourNode_pst) && (NULL == f_inputNode_pst ->south_pst))
	{
		f_inputNode_pst ->south_pst = f_neighbourNode_pst;
	}
}

node* getSouthNode(node* f_inputNode_pst)
{
	return f_inputNode_pst ->south_pst;
}

void setEastNode(node* f_inputNode_pst, node* f_neighbourNode_pst)
{
	if ((NULL != f_neighbourNode_pst) && (NULL == f_inputNode_pst ->east_pst))
	{
		f_inputNode_pst ->east_pst = f_neighbourNode_pst;
	}
}

node* getEastNode(node* f_inputNode_pst)
{
	return f_inputNode_pst ->east_pst;
}

void setWestNode(node* f_inputNode_pst, node* f_neighbourNode_pst)
{
	if ((NULL != f_neighbourNode_pst) && (NULL == f_inputNode_pst ->west_pst))
	{
		f_inputNode_pst ->west_pst = f_neighbourNode_pst;
	}
}

node* getWestNode(node* f_inputNode_pst)
{
	return f_inputNode_pst ->west_pst;
}


neighbourListNode* createNeighbourListNode()
{
	neighbourListNode* NeighbourListNode_pst = (neighbourListNode *) malloc(sizeof(neighbourListNode));

	if (NeighbourListNode_pst)
	{
		NeighbourListNode_pst ->neighbourNode_pst = NULL;
		NeighbourListNode_pst ->prev = NULL;
		NeighbourListNode_pst ->next = NULL;

		return NeighbourListNode_pst;
	}
	else
	{
		return NULL;
	}

}

neighbourList* createNeghbourList()
{
	neighbourList* NeighbourList_pst = (neighbourList *) malloc(sizeof(neighbourList));

	if(NeighbourList_pst)
	{
		NeighbourList_pst ->head = NULL;
		NeighbourList_pst ->tail = NULL;
		NeighbourList_pst ->listSize = 0;
	}

	return NeighbourList_pst;
}

bool isNeighbourListEmpty(neighbourList* f_neighbourList_pst)
{
	if (0 == f_neighbourList_pst ->listSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool addToFrontNeighbourList(neighbourList* f_neighbourList_pst, node* f_inputNode_pst)
{
	if(isNeighbourListEmpty(f_neighbourList_pst))
	{
		neighbourListNode* NeighbourListNode_pst = createNeighbourListNode();

		if (NeighbourListNode_pst)
		{
			f_neighbourList_pst ->head = NeighbourListNode_pst;
			f_neighbourList_pst ->tail = NeighbourListNode_pst;
			NeighbourListNode_pst ->neighbourNode_pst = f_inputNode_pst;
			f_neighbourList_pst ->listSize++;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		neighbourListNode* neighbourListHeadNode_pst = f_neighbourList_pst ->head;

		neighbourListNode* NeighbourListNode_pst = createNeighbourListNode();

		if (NeighbourListNode_pst)
		{
			neighbourListHeadNode_pst ->prev = NeighbourListNode_pst;
			NeighbourListNode_pst ->next = neighbourListHeadNode_pst;
			NeighbourListNode_pst ->neighbourNode_pst = f_inputNode_pst;
			f_neighbourList_pst ->head = NeighbourListNode_pst;
			f_neighbourList_pst ->listSize++;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool addToEndNeighbourList(neighbourList* f_neighbourList_pst, node* f_inputNode_pst)
{

	if(isNeighbourListEmpty(f_neighbourList_pst))
	{
		neighbourListNode* NeighbourListNode_pst = createNeighbourListNode();

		if (NeighbourListNode_pst)
		{
			f_neighbourList_pst ->head = NeighbourListNode_pst;
			f_neighbourList_pst ->tail = NeighbourListNode_pst;
			NeighbourListNode_pst ->neighbourNode_pst = f_inputNode_pst;
			f_neighbourList_pst ->listSize++;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		neighbourListNode* neighbourListTailNode_pst = f_neighbourList_pst ->tail;

		neighbourListNode* NeighbourListNode_pst = createNeighbourListNode();

		if (NeighbourListNode_pst)
		{
			neighbourListTailNode_pst ->next = NeighbourListNode_pst;
			NeighbourListNode_pst ->prev = neighbourListTailNode_pst;
			NeighbourListNode_pst ->neighbourNode_pst = f_inputNode_pst;
			f_neighbourList_pst ->tail = NeighbourListNode_pst;
			f_neighbourList_pst ->listSize++;
			return true;
		}
		else
		{
			return false;
		}
	}
}

void removeNeighbourListEnd(neighbourList* f_neighbourList_pst)
{
	if(!isNeighbourListEmpty(f_neighbourList_pst))
	{
		neighbourListNode* neighbourListTailNode_pst = f_neighbourList_pst ->tail;

		if(f_neighbourList_pst ->head == f_neighbourList_pst ->tail)
		{
			f_neighbourList_pst ->head = NULL;
			f_neighbourList_pst ->tail = NULL;
		}
		else
		{
			f_neighbourList_pst ->tail = neighbourListTailNode_pst ->prev;
			f_neighbourList_pst ->tail ->next = NULL;
		}

		free(neighbourListTailNode_pst);
		f_neighbourList_pst ->listSize--;
	}
}

void destroyNeighbourList(neighbourList* f_neighbourList_pst)
{
	neighbourListNode* nextNeighbourNode_pst;

    if(!isNeighbourListEmpty(f_neighbourList_pst))
    {
    	neighbourListNode* itNode_pst = f_neighbourList_pst->head;

    	for (; itNode_pst != NULL; itNode_pst = nextNeighbourNode_pst)
    	{
    		nextNeighbourNode_pst = itNode_pst->next;
    		free(itNode_pst);
    	}
    }

    free(f_neighbourList_pst);
}

neighbourList* getNeighbourList(node* f_inputNode_pst)
{
	neighbourList* NeighbourList_pst = createNeghbourList();

	bool neighbourListUpdateflag_bl = true;

	if(NULL != f_inputNode_pst ->south_pst)
	{
		neighbourListUpdateflag_bl &= addToEndNeighbourList(NeighbourList_pst, f_inputNode_pst ->south_pst);
	}

	if(NULL != f_inputNode_pst ->east_pst)
	{
		neighbourListUpdateflag_bl &= addToEndNeighbourList(NeighbourList_pst, f_inputNode_pst ->east_pst);
	}

	if(NULL != f_inputNode_pst ->north_pst)
	{
		neighbourListUpdateflag_bl &= addToEndNeighbourList(NeighbourList_pst, f_inputNode_pst ->north_pst);
	}

	if(NULL != f_inputNode_pst ->west_pst)
	{
		neighbourListUpdateflag_bl &= addToEndNeighbourList(NeighbourList_pst, f_inputNode_pst ->west_pst);
	}

	if(!isNeighbourListEmpty(NeighbourList_pst) && neighbourListUpdateflag_bl)
	{
		return NeighbourList_pst;
	}
	else
	{
		destroyNeighbourList(NeighbourList_pst);
		return NULL;
	}
}
