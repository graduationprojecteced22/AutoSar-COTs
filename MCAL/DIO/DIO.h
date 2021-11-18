/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ //
// name: MOHAMED KHAELD
// date: 23/10/2021
// File: Dio
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

typedef u8 Dio_ChannelType;
typedef u8 Dio_PortType;

typedef struct
{
    u16 mask;
    u8 offset;
    Dio_PortType port;
} Dio_ChannelGroupType;

typedef u8 Dio_LevelType;
typedef u16 Dio_PortLevelType;

/* Id for the company in the AUTOSAR for example 1999 */
#define DIO_VENDOR_ID (1999U)

/* Dio Module Id */
#define DIO_MODULE_ID (120U)

/* Module Version 1.0.0  */
#define DIO_SW_MAJOR_VERSION (1U)
#define DIO_SW_MINOR_VERSION (0U)
#define DIO_SW_PATCH_VERSION (0U)

/* AUTOSAR Version 2.5.0 */
#define DIO_AR_RELEASE_MAJOR_VERSION (4U)
#define DIO_AR_RELEASE_MINOR_VERSION (4U)
#define DIO_AR_RELEASE_PATCH_VERSION (0U)

/************************ Dio_Port ID ******************************/
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
/********************************************************************/

/************************ Dio_Pin Numbers **************************/
#define DIO_A_PIN0 0x00
#define DIO_A_PIN1 0x01
#define DIO_A_PIN2 0x02
#define DIO_A_PIN3 0x03
#define DIO_A_PIN4 0x04
#define DIO_A_PIN5 0x05
#define DIO_A_PIN6 0x06
#define DIO_A_PIN7 0x07
#define DIO_A_PIN8 0x08
#define DIO_A_PIN9 0x0B
#define DIO_A_PIN12 0x0C
#define DIO_A_PIN13 0x0D
#define DIO_A_PIN14 0x0E
#define DIO_A_PIN15 0x0F
#define DIO_B_PIN0 0x10
#define DIO_B_PIN1 0x11
#define DIO_B_PIN2 0x12
#define DIO_B_PIN3 0x13
#define DIO_B_PIN4 0x14
#define DIO_B_PIN5 0x15
#define DIO_B_PIN6 0x16
#define DIO_B_PIN7 0x17
#define DIO_B_PIN8 0x18
#define DIO_B_PIN9 0x19
#define DIO_B_PIN10 0x1A
#define DIO_B_PIN11 0x1B
#define DIO_B_PIN12 0x1C
#define DIO_B_PIN13 0x1D
#define DIO_B_PIN14 0x1E
#define DIO_B_PIN15 0x1F
#define DIO_C_PIN0 0x20
#define DIO_C_PIN1 0x21
#define DIO_C_PIN2 0x22

#define Max_Channel_ID 0x22
#define Min_Channel_ID 0x00

#define PORT_A_Start_Channel_ID 0x00
#define PORT_A_End_Channel_ID 0x0f
#define PORT_B_Start_Channel_ID 0x10
#define PORT_B_End_Channel_ID 0x1f
#define PORT_C_Start_Channel_ID 0x20
#define PORT_C_End_Channel_ID 0x2f

#define STD_LOW 0
#define STD_HIGH 1

/***********************************************************************/

/************************************** Function *********************************************************************/

// Service Name      : Dio_ReadChannel
/// Syntax            : Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
/// Sync/Async        : Synchronous
/// Reentrancy        : Reentrant
/// Parameters(in)    : ChannelId --> ID of DIO channel
/// Parameters(inout) : None
/// Parameters(out)   : None
/// Return value      : Dio_LevelType STD_HIGH The physical level of the corresponding Pin is//                                   STD_HIGH//                                   STD_LOW The physical level of the corresponding Pin is//                                   STD_LOW
/// Description       : Returns the value of the specified DIO channel.

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Service Name      : Dio_WriteChannel
 * Syntax            : void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level)
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters(in)    : ChannelId --> ID of DIO channel
                       Level     --> Level
 * Parameters(inout) : None
 * Parameters(out)   : None
 * Return value      : None
 * Description       : Service to set a level of a channel. */

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/* Service Name      : Dio_ReadPort
 * Syntax            : Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters(in)    : PortId --> ID of DIO Port
 * Parameters(inout) : None
 * Parameters(out)   : None
 * Return value      : Dio_PortLevelType --> Level of all channels of that port
 * Description       : Returns the level of all channels of that port. */

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/* Service Name      : Dio_WritePort
 * Syntax            : void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters(in)    : PortId --> ID of DIO Port
                       Level  --> Value to be written
 * Parameters(inout) : None
 * Parameters(out)   : None
 * Return value      : None
 * Description       : Service to set a value of the port. */

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/* Service Name      : Dio_ReadChannelGroup
 * Syntax            : void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level)
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters(in)    : ChannelGroupIdPtr --> Pointer to ChannelGroup
 * Parameters(inout) : None
 * Parameters(out)   : None
 * Return value      : Dio_PortLevelType --> Dio_PortLevelType
 * Description       : This Service reads a subset of the adjoining bits of a port. */

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr);

/* Service Name      : Dio_WriteChannelGroup
 * Syntax            : void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level)
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters(in)    : ChannelGroupIdPtr --> Pointer to ChannelGroup
                       Level             --> Value to be written
 * Parameters(inout) : None
 * Parameters(out)   : None
 * Return value      : None
 * Description       :  Service to set a subset of the adjoining bits of a port to a specified level. */

void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level);
/*
 * Service name: Dio_GetVersionInfo
 * Parameters (out): VersionInfo -> Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Service to get the version information of this module.
 */
void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo);
/*
 * Service name: Dio_FlipChannel
 * Parameters (in): ChannelId -> ID of DIO channel
 * Return value: Dio_LevelType -> STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
 * 								  STD_LOW: The physical level of the corresponding Pin is STD_LOW.
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return the level of the channel after flip.
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

/*
Service Name      : Dio_MaskedWritePort
Syntax: void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
Service ID[hex]: 0x13 Sync/Async:
Synchronous Reentrancy: Reentrant
Parameters (in):PortId ID of DIO Port
                Level  Value to be written
                Mask   Channels to be masked in the port Parameters (inout):
None Parameters (out):NONE 
None Return value: NONE 
None Description: Service to set the value of a given port with required mask.
*/

void Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask);
#endif
