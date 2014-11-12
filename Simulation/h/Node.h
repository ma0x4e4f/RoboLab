/*
 * Node.h
 *
 *  Created on: 02.11.2014
 *      Author: Manojkumar
 * Description: This file declares the node structure and the operation on each node
 */

#ifndef NODE_H_
#define NODE_H_

#include "Configuration.h"
#include "types.h"

#define NULLDIRECTION 0x00

typedef struct {

	int32 x_Coordinate_i32; // X-Coordinate of the node in the maze
	int32 y_Coordinate_i32; // Y-Coordinate of the node in the maze

}coordinates;

typedef struct node_st
{
	coordinates xy_st;

	int32 availableDirections_i32; // Available directions for a particular node
	int32 unCoveredDirections_i32; // Directions yet to be covered for a particular node

	struct node_st* north_pst;
	struct node_st* south_pst;
	struct node_st* east_pst;
	struct node_st* west_pst;

	// The above four pointer stores the pointer to neighboring nodes

//	bool origin_bl; // Is the node an origin? This flag is needed as we are initializing
					// every node with (0,0) but this flag will be set to true for
					// the real origin through which we enter the maze

} node;

void initNode(node* f_inputNode_pst);



bool setNodeCoordinates(node* f_inputNode_pst, int32 f_xCord_i32, int32 f_yCord_i32);

coordinates getNodeCoordinates(node* f_inputNode_pst);

void setAvailableDirections(node* f_inputNode_pst, int32 f_availableDirections_i32);

int32 getAvailableDirections(node* f_inputNode_pst);

void setCoveredDirection(node* f_inputNode_pst, int32 f_direction_i32);

void setUnCoveredDirections(node* f_inputNode_pst, int32 f_unCoveredDirections_i32);

int32 getUnCoveredDirections(node* f_inputNode_pst);

void setNorthNode(node* f_inputNode_pst, node* f_neighbourNode_pst);

node* getNorthNode(node* f_inputNode_pst);

void setSouthNode(node* f_inputNode_pst, node* f_neighbourNode_pst);

node* getSouthNode(node* f_inputNode_pst);

void setEastNode(node* f_inputNode_pst, node* f_neighbourNode_pst);

node* getEastNode(node* f_inputNode_pst);

void setWestNode(node* f_inputNode_pst, node* f_neighbourNode_pst);

node* getWestNode(node* f_inputNode_pst);
//bool isNodeOrigin (node* f_inputNode_p);

#endif /* NODE_H_ */
