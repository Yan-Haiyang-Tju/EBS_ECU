/*
 * user_AS_State.c
 *
 *  Created on: Apr 26, 2025
 *      Author: 24116
 */

#include "user_AS_State.h"

void AS_State_Detect(void)
{
 switch(AS_State)
 {
 case AS_Off:
	 AS_Off_Solve();
	 break;
 case AS_Ready:
     AS_Ready_Solve();
     break;
 case AS_Driving:
     AS_Driving_Solve();
	 break;
 case AS_Emergency:
	 AS_Emergency_Solve();
	 break;
 case AS_Finished:
	 AS_Finished_Solve();
	 break;
 case Manu_Driving:
	 Manu_Driving_Solve();
	 break;
 }
}

void AS_Off_Solve()
{
 ASSI_OFF();
}
void AS_Ready_Solve()
{
	ASSI_Yellow_Stable();
}
void AS_Driving_Solve()
{
	ASSI_Yellow_Blink();
}
void AS_Emergency_Solve()
{
	EBS_Trigger();

}
void AS_Finished_Solve()
{
	DCF_Activate();
	ASSI_Blue_Stable();
}
void Manu_Driving_Solve()
{

}
