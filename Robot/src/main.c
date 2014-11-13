#include "../h/main.h"
//systick_wait_ms(1500);
//nxt_motor_set_speed(NXT_PORT_B, -50, 1);
//nxt_motor_set_speed(NXT_PORT_C, -50, 1);

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
     int n=0,b,w,north,south,west,east;
     ecrobot_set_light_sensor_active(NXT_PORT_S2);

	 while (ecrobot_get_motor_rev(NXT_PORT_B) <720)
	 {
		 nxt_motor_set_speed(NXT_PORT_B, 50, 1); /* Set motor speed for B and C to RN */
		 nxt_motor_set_speed(NXT_PORT_C, 50, 1);

	 }  n++;


	 nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	 nxt_motor_set_speed(NXT_PORT_C, 0, 1);

	 systick_wait_ms(2000);

	 b=ecrobot_get_light_sensor(NXT_PORT_S2) ;

	 nxt_motor_set_count(NXT_PORT_B, 0);

	 while (ecrobot_get_motor_rev(NXT_PORT_B) ==320)
		 {
			 nxt_motor_set_speed(NXT_PORT_B, -50, 1); /* Set motor speed for B and C to RN */
			 nxt_motor_set_speed(NXT_PORT_C,  50, 1);

		 } n++ ;


		 nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		 nxt_motor_set_speed(NXT_PORT_C, 0, 1);

		 systick_wait_ms(2000);

     w=ecrobot_get_light_sensor(NXT_PORT_S2) ;

     nxt_motor_set_count(NXT_PORT_B, 320);


     while (ecrobot_get_motor_rev(NXT_PORT_B) <320)
			 {
				 nxt_motor_set_speed(NXT_PORT_B, 50, 1); /* Set motor speed for B and C to RN */
				 nxt_motor_set_speed(NXT_PORT_C,-50, 1);

			 } n++ ;

			 nxt_motor_set_speed(NXT_PORT_B, 0, 1);
			 nxt_motor_set_speed(NXT_PORT_C, 0, 1);

			 systick_wait_ms(2000);

	 while (ecrobot_get_light_sensor(NXT_PORT_S2) ==b)
	 {
		         nxt_motor_set_speed(NXT_PORT_B, 50, 1); /* Set motor speed for B and C to RN */
                 nxt_motor_set_speed(NXT_PORT_C, 50, 1);
	 } n++;


	 nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	 nxt_motor_set_speed(NXT_PORT_C, 0, 1);

	 systick_wait_ms(2000);

	 nxt_motor_set_count(NXT_PORT_B, 0);

        while (ecrobot_get_motor_rev(NXT_PORT_B) < 162.5)
     {
                  nxt_motor_set_speed(NXT_PORT_B, 50, 1); /* Set motor speed for B and C to RN */
     			  nxt_motor_set_speed(NXT_PORT_C,50, 1);

     } ;

        nxt_motor_set_speed(NXT_PORT_B, 0, 1);
        	 nxt_motor_set_speed(NXT_PORT_C, 0, 1);

//       if( ecrobot_get_light_sensor(NXT_PORT_S2)== b )
//       {
//    	   south =1;
//    	   north =1;
//       }
//       else
//       {
//    	   north =0;
//    	   south =0;
//
//	   }
//       nxt_motor_set_count(NXT_PORT_B, 0);
//       while (ecrobot_get_motor_rev(NXT_PORT_B) < 316)
//          {
//                      nxt_motor_set_speed(NXT_PORT_B,-50, 1); /* Set motor speed for B and C to RN */
//          			  nxt_motor_set_speed(NXT_PORT_C,50, 1);
//
//          } ;
//
//       if( ecrobot_get_light_sensor(NXT_PORT_S2)== b )
//             {
//          	   east =1;
//          	   south =1;
//             }
//             else
//             {
//          	   east =0;
//          	   south =1;
//
//      	   }
//       nxt_motor_set_count(NXT_PORT_B, 0);
//
//       while (ecrobot_get_motor_rev(NXT_PORT_B) < 639)
//                {
//                        nxt_motor_set_speed(NXT_PORT_B,50, 1); /* Set motor speed for B and C to RN */
//                		nxt_motor_set_speed(NXT_PORT_C,-50, 1);
//
//                } ;
//
//             if( ecrobot_get_light_sensor(NXT_PORT_S2)== b )
//                   {
//                	   west =1;
//                	   south =1;
//                   }
//                   else
//                   {
//                	   west =0;
//                	   south =1;
//
//            	   }
//             nxt_motor_set_count(NXT_PORT_B, 0);
//             while (ecrobot_get_motor_rev(NXT_PORT_B) < 316)
//                    {
//                        nxt_motor_set_speed(NXT_PORT_B,-50, 1); /* Set motor speed for B and C to RN */
//                        nxt_motor_set_speed(NXT_PORT_C,50, 1);
//
//                     } n++ ;
//
//             nxt_motor_set_count(NXT_PORT_B, 0);
//             while (ecrobot_get_motor_rev(NXT_PORT_B) < 162.5)
//                               {
//                                   nxt_motor_set_speed(NXT_PORT_B,-50, 1); /* Set motor speed for B and C to RN */
//                                   nxt_motor_set_speed(NXT_PORT_C,-50, 1);
//
//                                } n++ ;
                                TerminateTask();
}
