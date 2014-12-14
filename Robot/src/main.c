#include "../h/main.h"

#include "../h/algo/Node.h"
#include "../h/algo/Algo.h"

/// DO NOT DELETE THIS METHOD
/// It is called every 1ms and e.g. can be used for implementing a
/// real time counter / clock.
void user_1ms_isr_type2(void) {
}

void ecrobot_device_initialize(void) {
}

void ecrobot_device_terminate(void) {
}

int getCurrentOrientation()
{
	return curentOrientation;
}

void setCurrentOrientation(int orientation)
{
	curentOrientation = orientation;
}

int initRobot()
{
	// CAUTION: Robot has to be kept on Black in order to continue else the program will not work!!

	int originMoveResult_i32 = 0;

	ecrobot_set_light_sensor_active(NXT_PORT_S2);

	calibration(); // Do Calibration to find correct threshold value

	setCurrentOrientation(NORTH);

	originMoveResult_i32 = movenodetonode(); // Moving Robot to the Origin point and start the Algorithm

	return originMoveResult_i32;
}

void endRobot(int f_inputResult_i32)
{
	node* l_currentNode_pst = getCurretnNode();

	node* l_originNode_pst = getOriginNode();

	int l_moveResult_i32;

	if(l_originNode_pst == l_currentNode_pst)
	{
		l_moveResult_i32 = endHandler();
	}

}

TASK(OSEK_Main_Task)
{
//	for(int i = 0; i < 8; i++)
//	{
//		turnAndScan(45, 45, FALSE, FALSE);
//	}

//	while(1)
//	{
//		turnAndScan(90,90,FALSE, CLOCKWISE);
//		turnAndScan(180,180,FALSE, ANTICLOCKWISE);
//		turnAndScan(90,90,FALSE, CLOCKWISE);
//
////		systick_wait_ms(2000);
//	}

	int originMoveResult_i32 = initRobot();

	int startRobotAlgoResult_i32 = ALGO_FAIL;

	BOOL initResult_bl = initRobotAlgo(originMoveResult_i32);

	if(TRUE == initResult_bl)
	{
		startRobotAlgoResult_i32 = startRobotAlgo();
	}
	else
	{
		ecrobot_status_monitor("Init Error");
	}

	if(ALGO_FAIL != startRobotAlgoResult_i32 && ALGO_TIMEOUT != startRobotAlgoResult_i32)
	{
		endRobot(startRobotAlgoResult_i32);
	}
	else
	{
		node* l_currentNode_pst = getCurretnNode();
		ecrobot_status_monitor("Algo Error!");
		systick_wait_ms(20000);
		ecrobot_debug1(l_currentNode_pst->xy_st.x_Coordinate_i32, l_currentNode_pst->xy_st.y_Coordinate_i32,
				l_currentNode_pst->availableDirections_i32);
	}














//	while (1) {
//		     ecrobot_set_light_sensor_active(NXT_PORT_S2);
//		     nxt_motor_set_count(NXT_PORT_B, 0);
//		     nxt_motor_set_count(NXT_PORT_C, 0);
//
//     	     calibration();
//
//     	    threshold = getThreshold();

//     	    forward(135,135,30,30);

//     	     threshold=550;

//		     movenodetonode(threshold);//725 count for 29cm,movement untill threshold value chnages//
//		     stop();

//		     movingintersection(100,100,-20,-20);
//		     int validDir = Robot_GetIntersections();
//         	 north=straight(threshold);  // following functions are to check intersections are present or not //
//		  	 east=turneast(threshold);
//		  	 south=turnsouth(threshold);
//		  	 west=turnwest(threshold);
//		  	 validdirections=oring(north,south,east,west); // To know which directions are present //
//             robotmove (int x,int y,int u,int v, float threshold);

//	}

    TerminateTask();
}
