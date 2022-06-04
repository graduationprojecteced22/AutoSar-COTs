#include "stdio.h"
void getRequiredDistance(int speedKM, int *distance);
int main()
{
    int distance = 0;
    getRequiredDistance(15, &distance);
    printf("current Distance  %d \n", distance);
    getRequiredDistance(25, &distance);
    printf("current Distance  %d \n", distance);
    getRequiredDistance(110, &distance);
    printf("current Distance  %d \n", distance);
    return 0;
}
void getRequiredDistance(int speedKM, int *distance)
{
    int disArr[8] = {2, 4, 6, 14, 24, 38, 55, 75};
    *distance = disArr[speedKM / 16 + (((speedKM % 16) / (float)16) >= .5)];
}