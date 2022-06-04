#include "stdio.h"

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "hall.h"
#include "hall_private.h"
#include "hall_config.h"

u32 oldCounter = 0x0;
u8 rps = 4;
u32 Get_Timer_Counter();
u32 Get_Timer_Counter()
{
    rps = rps - 1;
    return rps;
}
void HALL_GetSpeed(SpeedData *ptr_SpeedData)
{
    u32 snapshot = Get_Timer_Counter();
    // TODO: need #define for each case 1) car moving 2) car stoped 3)Exception
    if (snapshot == 0)
    {
        ptr_SpeedData->statusCode = CAR_NOT_MOVING;
    }
    else if (snapshot > 0)
    {
        ptr_SpeedData->statusCode = CAR_MOVING;
    }
    else
    {
        ptr_SpeedData->statusCode = CAR_SPEED_EXCEPTION;
    }
    ptr_SpeedData->RPM = snapshot * 60;
    ptr_SpeedData->speedPerKm = (ptr_SpeedData->RPM * 3.14 * wheelRaduis * 3) / (u32)25;
}

void HALL_Init()
{
    // GPIO init input pin as ETXI with rising edge
    // init ISR with cont up function
}
