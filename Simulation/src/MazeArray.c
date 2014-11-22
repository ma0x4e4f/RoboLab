/*
 * MazeArray.c
 *
 *  Created on: 06.11.2014
 *      Author: Manojkumar
 */

#include "../h/MazeArray.h"

static uint32 mazeArrayElements_ui32 = 0;
int32 originNodePos_i32 = 0;

void initMazeArray()
{
	uint32 it = 0;

	for(; it < MAZEARRAYMAXSIZE; it++)
	{
		node* mazeElement_pst = &mazeArray[it];

		initNode(mazeElement_pst);

//		static uint32 n = 1;
//		printf("came here = %d\n", n);
//		n++;
	}
}

node* getOriginNode()
{
	node* mazeArrayElement_pst = &mazeArray[originNodePos_i32];

	if(NULLDIRECTION == getAvailableDirections(mazeArrayElement_pst))
	{
		return NULL;
	}
	else
	{
		return mazeArrayElement_pst;
	}
}

uint32 getValidNumElements()
{
	return mazeArrayElements_ui32;
}

node* setMazeArrayElement(int32 f_xCord_i32, int32 f_yCord_i32, int32 f_availableDirections_i32)
{
	node* mazeArrayElement_pst = NULL;

	mazeArrayElement_pst = searchMazeArray(f_xCord_i32, f_yCord_i32);

	if (NULL == mazeArrayElement_pst)
	{
		if (MAZEARRAYMAXSIZE > mazeArrayElements_ui32)
		{
			mazeArrayElement_pst = &mazeArray[mazeArrayElements_ui32];

			setNodeCoordinates(mazeArrayElement_pst, f_xCord_i32, f_yCord_i32);

			setAvailableDirections(mazeArrayElement_pst, f_availableDirections_i32);

			mazeArrayElements_ui32++; // Increase the number of valid elements in Maze array by 1
		}
		else
		{
			return mazeArrayElement_pst;
		}
	}
	else
	{

	}

	return mazeArrayElement_pst;
}

node* searchMazeArray(int32 f_xCord_i32, int32 f_yCord_i32)
{
	node* mazeArrayElement_pst = NULL;

	uint32 it = 0;

	for(; it < mazeArrayElements_ui32; it++)
	{
		mazeArrayElement_pst = &mazeArray[it];

		if (NULL != mazeArrayElement_pst)
		{
			coordinates mazeElementCoordinate_st = getNodeCoordinates(mazeArrayElement_pst);

			if((f_xCord_i32 == mazeElementCoordinate_st.x_Coordinate_i32) &&
				(f_yCord_i32 == mazeElementCoordinate_st.y_Coordinate_i32))
			{
				if(NULLDIRECTION == getAvailableDirections(mazeArrayElement_pst))
				{
					return NULL;
				}

				break;
			}
			else
			{
				// Left Intentionally blank
			}
		}

	}

	if((NULL == mazeArrayElement_pst) || (mazeArrayElements_ui32 == it))
	{
		return NULL;
	}
	else
	{
		return mazeArrayElement_pst;
	}
}

node* getLastUncoveredNode()
{
	node* mazeArrayElement_pst = NULL;

	int32 uncoveredDirtections_i32 = 0x00;

	uint32 it = 0;

	if (0 < mazeArrayElements_ui32)
	{
		it = mazeArrayElements_ui32;

		for (; it > 0; it--)
		{
			int32 arrayIndex_i32 = it - 1;

			mazeArrayElement_pst = &mazeArray[arrayIndex_i32];
			uncoveredDirtections_i32 = getUnCoveredDirections(mazeArrayElement_pst);

			if(NULLDIRECTION != uncoveredDirtections_i32)
			{
				return mazeArrayElement_pst;
			}
			else
			{
				// do nothing
				// check the next element
			}
		}
	}
	else
	{
		return NULL;
	}

	if ((NULL == mazeArrayElement_pst) || (0 == it))
	{
		return NULL;
	}
	else
	{
		// Intentionally left blank
	}

}
