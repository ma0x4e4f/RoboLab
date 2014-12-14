/*
 * AStarNode.c
 *
 *  Created on: 17.11.2014
 *      Author: Manojkumar
 */

#include "../../h/algo/AStarNode.h"

aStarNode* createEmptyAStarNode()
{
	aStarNode* AStarNode_pst = (aStarNode *) malloc(sizeof(aStarNode));

	if (AStarNode_pst)
	{
		AStarNode_pst ->informationNode_pst = NULL;
		AStarNode_pst ->cameFromNode_pst = NULL;
		AStarNode_pst ->gScore_i32 = 0;
		AStarNode_pst ->hScore_i32 = 0;
		AStarNode_pst ->fScore_i32 = 0;

		return AStarNode_pst;
	}
	else
	{
		return NULL;
	}

}

aStarNode* createAStarNode(node* f_inputInfoNode_pst)
{
	aStarNode* AStarNode_pst = (aStarNode *) malloc(sizeof(aStarNode));

	if (AStarNode_pst)
	{
		AStarNode_pst ->informationNode_pst = f_inputInfoNode_pst;
		AStarNode_pst ->cameFromNode_pst = NULL;
		AStarNode_pst ->gScore_i32 = 0;
		AStarNode_pst ->hScore_i32 = 0;
		AStarNode_pst ->fScore_i32 = 0;

		return AStarNode_pst;
	}
	else
	{
		return NULL;
	}

}

void setInformationPtr(aStarNode* f_inputAStarNode_pst, node* f_inputInfoNode_pst)
{
	if (NULL != f_inputInfoNode_pst)
	{
		f_inputAStarNode_pst ->informationNode_pst = f_inputInfoNode_pst;
	}
	else
	{
		// do nothing
	}
}

node* getInformationPtr(aStarNode* f_inputAStarNode_pst)
{
	return f_inputAStarNode_pst ->informationNode_pst;
}

void setCameFromPtr(aStarNode* f_inputAStarNode_pst, aStarNode* f_inputCameFromNode_pst)
{
	if (NULL != f_inputCameFromNode_pst)
	{
		f_inputAStarNode_pst ->cameFromNode_pst = f_inputCameFromNode_pst;
	}
	else
	{
		// do nothing
	}
}

aStarNode* getCameFromPtr(aStarNode* f_inputAStarNode_pst)
{
	return f_inputAStarNode_pst ->cameFromNode_pst;
}

void setGScore (aStarNode* f_inputAStarNode_pst, int32 f_inputGscore_i32)
{
	f_inputAStarNode_pst ->gScore_i32 = f_inputGscore_i32;
}

int32 getGScore (aStarNode* f_inputAStarNode_pst)
{
	return f_inputAStarNode_pst ->gScore_i32;
}

void setHScore (aStarNode* f_inputAStarNode_pst, int32 f_inputHscore_i32)
{
	f_inputAStarNode_pst ->hScore_i32 = f_inputHscore_i32;
}

int32 getHScore (aStarNode* f_inputAStarNode_pst)
{
	return f_inputAStarNode_pst ->hScore_i32;
}

void setFScore (aStarNode* f_inputAStarNode_pst, int32 f_inputGscore_i32, int32 f_inputHscore_i32)
{
	f_inputAStarNode_pst ->fScore_i32 = f_inputGscore_i32 + f_inputHscore_i32;
}

int32 getFScore (aStarNode* f_inputAStarNode_pst)
{
	return f_inputAStarNode_pst ->fScore_i32;
}

void setAllInfoAStarNode(aStarNode* f_inputAStarNode_pst, node* f_inputInfoNode_pst,
						 aStarNode* f_inputCameFromNode_pst, int32 f_inputGscore_i32,
						 int32 f_inputHscore_i32)
{
	setInformationPtr(f_inputAStarNode_pst, f_inputInfoNode_pst);
	setCameFromPtr(f_inputAStarNode_pst, f_inputCameFromNode_pst);
	setGScore(f_inputAStarNode_pst, f_inputGscore_i32);
	setHScore(f_inputAStarNode_pst, f_inputHscore_i32);
	setFScore(f_inputAStarNode_pst, f_inputGscore_i32, f_inputHscore_i32);
}

aStarListNode* createAStarListNode()
{
	aStarListNode* AStarListNode_pst = (aStarListNode *) malloc(sizeof(aStarListNode));

	if (AStarListNode_pst)
	{
		AStarListNode_pst ->aStarNode_pst = NULL;
		AStarListNode_pst ->prev = NULL;
		AStarListNode_pst ->next = NULL;

		return AStarListNode_pst;
	}
	else
	{
		return NULL;
	}

}

aStarList* createAStarList()
{
	aStarList* AStartList_pst = (aStarList *) malloc(sizeof(aStarList));

	if(AStartList_pst)
	{
		AStartList_pst ->head = NULL;
		AStartList_pst ->tail = NULL;
		AStartList_pst ->listSize = 0;
	}

	return AStartList_pst;
}

bool isAStarListEmpty(aStarList* f_aStarList_pst)
{
	if (0 == f_aStarList_pst ->listSize)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


aStarListNode* searchAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst)
{
	aStarListNode* current = f_aStarList_pst ->head;

	while (NULL != current)
	{
	    if (f_inputAStarNode_pst ->informationNode_pst == current ->aStarNode_pst ->informationNode_pst)
	    {
	    	return current;
	    }

		current = current->next;
	}

	return NULL;
}

aStarListNode* searchNeighbourInAStarList(aStarList* f_aStarList_pst, node* f_inputNode_pst)
{
	aStarListNode* current = f_aStarList_pst ->head;

	while (NULL != current)
	{
	    if (f_inputNode_pst == current ->aStarNode_pst ->informationNode_pst)
	    {
	    	return current;
	    }

		current = current->next;
	}

	return NULL;
}

bool isPresentInList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst)
{
	if(searchAStarList(f_aStarList_pst, f_inputAStarNode_pst))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool isNeighbourPresentInList(aStarList* f_aStarList_pst, node* f_inputNode_pst)
{
	if(searchNeighbourInAStarList(f_aStarList_pst, f_inputNode_pst))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool addToFrontAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst)
{
	if(isAStarListEmpty(f_aStarList_pst))
	{
		aStarListNode* AStarListNode_pst = createAStarListNode();

		if (AStarListNode_pst)
		{
			f_aStarList_pst ->head = AStarListNode_pst;
			f_aStarList_pst ->tail = AStarListNode_pst;
			AStarListNode_pst ->aStarNode_pst = f_inputAStarNode_pst;
			f_aStarList_pst ->listSize++;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		aStarListNode* aStarListHeadNode_pst = f_aStarList_pst ->head;

		aStarListNode* AStarListNode_pst = createAStarListNode();

		if (AStarListNode_pst)
		{
			aStarListHeadNode_pst ->prev = AStarListNode_pst;
			AStarListNode_pst ->next = aStarListHeadNode_pst;
			AStarListNode_pst ->aStarNode_pst = f_inputAStarNode_pst;
			f_aStarList_pst ->head = AStarListNode_pst;
			f_aStarList_pst ->listSize++;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

bool addToEndAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst)
{
	if(isAStarListEmpty(f_aStarList_pst))
	{
		aStarListNode* AStarListNode_pst = createAStarListNode();

		if (AStarListNode_pst)
		{
			f_aStarList_pst ->head = AStarListNode_pst;
			f_aStarList_pst ->tail = AStarListNode_pst;
			AStarListNode_pst ->aStarNode_pst = f_inputAStarNode_pst;
			f_aStarList_pst ->listSize++;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		aStarListNode* aStarListTailNode_pst = f_aStarList_pst ->tail;

		aStarListNode* AStarListNode_pst = createAStarListNode();

		if (AStarListNode_pst)
		{
			aStarListTailNode_pst ->next = AStarListNode_pst;
			AStarListNode_pst ->prev = aStarListTailNode_pst;
			AStarListNode_pst ->aStarNode_pst = f_inputAStarNode_pst;
			f_aStarList_pst ->tail = AStarListNode_pst;
			f_aStarList_pst ->listSize++;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

void removeAStarListEnd(aStarList* f_aStarList_pst)
{
	if(!isAStarListEmpty(f_aStarList_pst))
	{
		aStarListNode* aStarListTailNode_pst = f_aStarList_pst ->tail;

		if(f_aStarList_pst ->head == f_aStarList_pst ->tail)
		{
			f_aStarList_pst ->head = NULL;
			f_aStarList_pst ->tail = NULL;
		}
		else
		{
			f_aStarList_pst ->tail = aStarListTailNode_pst ->prev;
			f_aStarList_pst ->tail ->next = NULL;
		}

		free(aStarListTailNode_pst);
		f_aStarList_pst ->listSize--;
	}
}

void removeFromAStarList(aStarList* f_aStarList_pst, aStarNode* f_inputAStarNode_pst)
{
	aStarListNode* foundAStarListNode = searchAStarList(f_aStarList_pst, f_inputAStarNode_pst);

	aStarListNode* prevToFoundNode;
	aStarListNode* nextToFoundNode;

	if(foundAStarListNode)
	{
		prevToFoundNode = foundAStarListNode ->prev;
		nextToFoundNode = foundAStarListNode ->next;

		if(f_aStarList_pst ->head == f_aStarList_pst ->tail)
		{
			f_aStarList_pst ->head = NULL;
			f_aStarList_pst ->tail = NULL;
		}
		else if (f_aStarList_pst ->head == foundAStarListNode)
		{
			f_aStarList_pst ->head = nextToFoundNode;
			nextToFoundNode ->prev = NULL;
		}
		else if(f_aStarList_pst ->tail == foundAStarListNode)
		{
			f_aStarList_pst ->tail = prevToFoundNode;
			prevToFoundNode ->next = NULL;
		}
		else
		{
			prevToFoundNode ->next = nextToFoundNode;
			nextToFoundNode ->prev = prevToFoundNode;
		}

		free(foundAStarListNode);
		f_aStarList_pst ->listSize--;
	}
}

void destroyAStarList(aStarList* f_aStarList_pst)
{
	aStarListNode* nextAStarNode_pst;

    if(!isAStarListEmpty(f_aStarList_pst))
    {
    	aStarListNode* itNode_pst = f_aStarList_pst->head;

    	for (; itNode_pst != NULL; itNode_pst = nextAStarNode_pst)
    	{
    		nextAStarNode_pst = itNode_pst->next;
    		free(itNode_pst ->aStarNode_pst);
    		free(itNode_pst);
    	}
    }

    free(f_aStarList_pst);
}
