#include "stdio.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../HAL/hall/hall.c"
#include "../HAL/sonar/sonar.h"
#include "get_distance/get_distance.c"
#define MOTOR 1
#define BRAKE 2
#define UserSpeed 80

u8 motorStatus = 1; // 1 >> for run , 0 >> for stop
u8 brakeStatus = 0;
u8 userSpeedSafeDistance = 0;
u8 currentDistance = 0;

u8 currentSafeSpeed = 0;

SpeedData currentSpeedData;

void stopAcu(u8 PinNumber);
void brake(u8 currentSafeSpeed);
u8 getRequiredDistance(u8 speedKM, u8 *distance);
void getRequiredSpeed(u8 distance, u8 *currentSafeSpeed);
void accelerate(u8 currentSafeSpeed);
void ACC();

u16 LOC_u16SonarDistance[4] = {0, 0, 0, 0};
int main()
{
    ACC();
    return 0;
}

void ACC()
{
    // Mode 1
    //* init data
    //! get car data
    GetDistance_u16GetForwardDistance(LOC_u16SonarDistance);
    currentDistance = LOC_u16SonarDistance[LOC_u16SonarDistance[1] > LOC_u16SonarDistance[0]];
    HALL_GetSpeed(&currentSpeedData);
    printf("current Distance  %d \n", LOC_u16SonarDistance[0]);
    printf("current Speed  %d \n", currentSpeedData.speedPerKm);
    //! Safe data for user
    getRequiredDistance(UserSpeed, &userSpeedSafeDistance);
    printf("Safe Distance for user speed %d \n", userSpeedSafeDistance);
    //!
    getRequiredSpeed(currentDistance, &currentSafeSpeed);
    printf("current Safe Speed  %d \n", currentSafeSpeed);
    //
    if (currentSpeedData.speedPerKm > UserSpeed)
    {
        printf("if currentSpeedData.speedPerKm > UserSpeed \n");
        brake(UserSpeed);

        //! sim for speed dawn

        LOC_u16SonarDistance[0] = LOC_u16SonarDistance[0] + 10;
        LOC_u16SonarDistance[1] = LOC_u16SonarDistance[1] + 10;
        getRequiredSpeed(LOC_u16SonarDistance[LOC_u16SonarDistance[1] > LOC_u16SonarDistance[0]], &currentSafeSpeed);
        printf("current Safe Speed  %d \n", currentSafeSpeed);
        printf("end if \n");
    }
    // //! case 1 userSpeedSafeDistance > currentDistance
    if (userSpeedSafeDistance > currentDistance)
    {
        printf("user Speed Safe Distance bigger currentDistance \n");
        brake(currentSafeSpeed);
        accelerate(currentSafeSpeed);
    }
    //! case 2 userSpeedSafeDistance < currentDistance
    else if (userSpeedSafeDistance <= currentDistance)
    {
        printf("Safe Distance lower current Distance \n");
        accelerate(UserSpeed);
    }
}

//* tested
u8 getRequiredDistance(u8 speedKM, u8 *distance)
{
    u8 disArr[8] = {2, 4, 6, 14, 24, 38, 55, 75};
    *distance = disArr[(speedKM / 16)];
}

//* tested
void getRequiredSpeed(u8 distance, u8 *currentSafeSpeed)
{
    u8 SpeedArr[8] = {0, 16, 32, 48, 64, 80, 96, 112};
    u8 disArr[8] = {2, 4, 6, 14, 24, 38, 55, 75};
    u8 i;
    if (distance > disArr[7])
    {
        *currentSafeSpeed = SpeedArr[7];
    }
    else if (distance == 0)
    {
        *currentSafeSpeed = SpeedArr[0];
    }
    else
    {
        for (i = 0; i < 0b1000; i++)
        {
            if (distance < disArr[i])
            {
                i--;
                break;
            }
        }
        *currentSafeSpeed = SpeedArr[i];
    }
}

void brake(u8 currentSafeSpeed)
{
    stopAcu(MOTOR);
    while (currentSpeedData.speedPerKm > currentSafeSpeed)
    {
        HALL_GetSpeed(&currentSpeedData);
        for (u32 i = 0; i < 100000; i++)
            ;
    };
    printf("brake current safe speed = %d \n", currentSafeSpeed);
    printf("speedPerKm = %d \n", currentSpeedData.speedPerKm);
    stopAcu(BRAKE);
}

void stopAcu(u8 PinNumber)
{
    switch (PinNumber)
    {
    case MOTOR:
        motorStatus = 0;
        printf("Motor Status  %d \n", motorStatus);
        break;
    case BRAKE:
        brakeStatus = 0;
        printf("Brake Status  %d \n", motorStatus);
        break;
    }
}
void accelerate(u8 currentSafeSpeed)
{
    currentSpeedData.speedPerKm = currentSafeSpeed;
    printf("motor  Speed %d \n", currentSpeedData.speedPerKm);
}
