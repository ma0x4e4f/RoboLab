#include "../h/main.h"

/// DO NOT DELETE THIS METHOD
/// It is called every 1ms and e.g. can be used for implementing a
/// real time counter / clock.
void user_1ms_isr_type2(void) {
}

void ecrobot_device_initialize(void) {
}

void ecrobot_device_terminate(void) {
}

void hello_world() {
	ecrobot_status_monitor("Hello, World!");

}

TASK(OSEK_Main_Task) {

	int n = 0;

//	while (n < 5) {
//			nxt_motor_set_speed(NXT_PORT_A,75,0);
//			systick_wait_ms(2000);
//			nxt_motor_set_speed(NXT_PORT_A,0,1);

//			hello_world();

		int RN = 50;

		int currentRev = ecrobot_get_motor_rev(NXT_PORT_B);
		int oldRev = ecrobot_get_motor_rev(NXT_PORT_B);


//		nxt_motor_set_count(NXT_PORT_B, 180);
//		nxt_motor_set_count(NXT_PORT_C, 90);

		nxt_motor_set_speed(NXT_PORT_B, RN, 1); 			/* Set motor speed for B and C to RN */
		nxt_motor_set_speed(NXT_PORT_C, RN, 1);


		/* 500msec wait */
//		systick_wait_ms(5000);

		while(n < 180)
		{
			currentRev = ecrobot_get_motor_rev(NXT_PORT_B);
			n = currentRev-oldRev;
		}

		oldRev = currentRev;

		nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		nxt_motor_set_speed(NXT_PORT_C, 0, 1);

//		systick_wait_ms(2000);
//
//		nxt_motor_set_speed(NXT_PORT_B, 50, 1);
//		nxt_motor_set_speed(NXT_PORT_C, -50, 1);

		systick_wait_ms(15000);

		nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		nxt_motor_set_speed(NXT_PORT_C, 0, 1);


//		n++;


//	}

	TerminateTask();
}
