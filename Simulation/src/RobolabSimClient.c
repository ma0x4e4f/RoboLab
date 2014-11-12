
#include "../h/RobolabSimClient.h"


int main(void) {

	printf("size of: %d\n", sizeof(node));

	initMazeArray(); //This function has to be called in the init task

	int32 algoResult_i32 = 0;

	bool algoInitResult_bl = initRobotAlgo(); // This function has to be called once in the main task

	if(true == algoInitResult_bl)
	{
		printf("Starting Algo from co-ordinate (0,0)\n");
		algoResult_i32 = startRobotAlgo();
	}

	node* node_pst = NULL;

//	node_pst = searchMazeArray(0,0);
	node_pst = getOriginNode();

	printf("origin node ptr: %x\n", node_pst);

	// This function has to be called in main task and
	// will be returned only when all the nodes are covered and all tokens are found or
	// when error happened in maze exploration

	printf("AlgoResult = %d\n", algoResult_i32);

	printf("number of valid elements = %d\n",getValidNumElements());
//
//	node* mazeElement = searchMazeArray(0,0);
//
//	if (NULL != mazeElement)
//	{
//		printf("Available directions of (0,0) = %x\n", getAvailableDirections(mazeElement));
//	}


//	printf("output: %d\n", Robot_Move(1, 0));
//	printf("Intersections: %X\n", Robot_GetIntersections());
//	printf("output: %d\n", Robot_Move(1, 1));
	return EXIT_SUCCESS;
}
