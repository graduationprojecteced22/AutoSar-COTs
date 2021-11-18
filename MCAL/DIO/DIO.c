#include "../../LIB/stm32f103C8.h"
#include "DIO.h"

extern u16 PortA_DIO_OutputPins;
extern u16 PortB_DIO_OutputPins;
extern u16 PortC_DIO_OutputPins;

extern u16 PortA_DIO_InputPins;
extern u16 PortB_DIO_InputPins;
extern u16 PortC_DIO_InputPins;

static GPIO_RegDef_t *GPIO_AStrPtr[3] = {GPIOA, GPIOB, GPIOC};
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    switch (ChannelId / 16)
    {
    case DIO_PORTA:
        return GET_BIT(((GPIO_AStrPtr[DIO_PORTA]->IDR) & (PortA_DIO_InputPins | PortA_DIO_OutputPins)), (ChannelId % 16));
        break;
    case DIO_PORTB:
        return GET_BIT((GPIO_AStrPtr[DIO_PORTB]->IDR & (PortB_DIO_InputPins | PortB_DIO_OutputPins)), (ChannelId % 16));
        break;
    case DIO_PORTC:
        if ((ChannelId % 16) > 12)
        {
            return GET_BIT((GPIO_AStrPtr[DIO_PORTC]->IDR & (PortC_DIO_InputPins | PortC_DIO_OutputPins)), (ChannelId % 16));
        }
        else
        {
            /* call DET with error code DIO_E_PARAM_INVALID_CHANNEL_ID */
            return 0;
        }
        break;
    default: /* call DET with error code DIO_E_PARAM_INVALID_CHANNEL_ID */
        return 0;
        break;
    }
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    switch (Level)
    {
    case STD_HIGH:
        if (ChannelId <= PORT_A_End_Channel_ID && ChannelId >= PORT_A_Start_Channel_ID)
            GPIO_AStrPtr[DIO_PORTA]->BSRR = (1 << (ChannelId) & (PortB_DIO_OutputPins));
        if (ChannelId <= PORT_B_End_Channel_ID && ChannelId >= PORT_B_Start_Channel_ID)
            GPIO_AStrPtr[DIO_PORTB]->BSRR = (1 << (ChannelId % 0xF) & (PortB_DIO_OutputPins));
        if (ChannelId <= PORT_C_End_Channel_ID && ChannelId >= PORT_C_Start_Channel_ID)
            GPIO_AStrPtr[DIO_PORTC]->BSRR = (1 << (ChannelId % 0xF) & (PortB_DIO_OutputPins));
        break;
    case STD_LOW:
        if (ChannelId <= PORT_A_End_Channel_ID && ChannelId >= PORT_A_Start_Channel_ID)
            GPIO_AStrPtr[DIO_PORTA]->BSRR = (1 << (ChannelId) & (PortB_DIO_OutputPins));
        if (ChannelId <= PORT_B_End_Channel_ID && ChannelId >= PORT_B_Start_Channel_ID)
            GPIO_AStrPtr[DIO_PORTB]->BSRR = (1 << (ChannelId % 0xF) & (PortB_DIO_OutputPins));
        if (ChannelId <= PORT_C_End_Channel_ID && ChannelId >= PORT_C_Start_Channel_ID)
            GPIO_AStrPtr[DIO_PORTC]->BSRR = (1 << (ChannelId % 0xF) & (PortB_DIO_OutputPins));
        break;
    default:
        // throw Error
        break;
    }
}
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    Dio_PortLevelType LOC_PortValue;
    if (PortId <= DIO_PORTC && PortId >= DIO_PORTA)
    {
        LOC_PortValue = 0xFFFF & GPIO_AStrPtr[PortId]->IDR & (PortA_DIO_InputPins | PortA_DIO_OutputPins);
    }
    else
    {
        // throw error
    }
    return LOC_PortValue;
}
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    if (PortId == DIO_PORTC && PortId >= DIO_PORTA)
    {
        GPIO_AStrPtr[PortId]->ODR = 0xE000 & (Level & (PortA_DIO_OutputPins));
    }
    else if (PortId == DIO_PORTA || PortId == DIO_PORTB)
    {
        GPIO_AStrPtr[PortId]->ODR = (Level & (PortA_DIO_OutputPins));
    }
    else
    {
        // throw error
    }
}
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
    if (ChannelGroupIdPtr->port == DIO_PORTC)
    {
        if (ChannelGroupIdPtr->mask >= 0xE000)
            return ((GPIO_AStrPtr[ChannelGroupIdPtr->port]->IDR & (PortA_DIO_InputPins | PortA_DIO_OutputPins)) >> ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask;
        else
        {
            //throw error
        }
    }
    else
    {
        return ((GPIO_AStrPtr[ChannelGroupIdPtr->port]->IDR & (PortA_DIO_InputPins | PortA_DIO_OutputPins)) >> ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask;
    }
}
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level)
{
    Level &= ChannelGroupIdPtr->mask;
    if (ChannelGroupIdPtr->port == DIO_PORTC)
    {
        *GPIO_AStrPtr[DIO_PORTC]->BRR->BRR = (ChannelGroupIdPtr->mask & 0xE000);
        *GPIO_AStrPtr[DIO_PORTC]->BRR->BSRR = ((Level & (PortC_DIO_OutputPins)) & 0xE000);
    }
    else
    {
        *GPIO_AStrPtr[ChannelGroupIdPtr->port]->BRR = ChannelGroupIdPtr->mask;
        *GPIO_AStrPtr[ChannelGroupIdPtr->port]->BSRR = (Level & (PortA_DIO_OutputPins));
    }
}

/*
 * Service name: Dio_GetVersionInfo
 * Parameters (out): VersionInfo -> Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Service to get the version information of this module.
 */
void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{
    VersionInfo->moduleID = DIO_MODULE_ID;
    VersionInfo->vendorID = DIO_VENDOR_ID;
    VersionInfo->sw_major_version = DIO_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = DIO_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = DIO_SW_PATCH_VERSION;
}

/*
 * Service name: Dio_FlipChannel
 * Parameters (in): ChannelId -> ID of DIO channel
 * Return value: Dio_LevelType -> STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
 * 								  STD_LOW: The physical level of the corresponding Pin is STD_LOW.
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return the level of the channel after flip.
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType TempPinState = Dio_ReadChannel(ChannelId);
    Dio_WriteChannel(ChannelId, (0x01 ^ TempPinState));
    return Dio_ReadChannel(ChannelId);
}

void Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask)
{
    Level &= Mask;
    if (PortId == DIO_PORTC)
    {
        *GPIO_AStrPtr[DIO_PORTC]->BRR->BRR = (Mask & 0xE000);
        *GPIO_AStrPtr[DIO_PORTC]->BRR->BSRR = ((Level & (PortC_DIO_OutputPins)) & 0xE000);
    }
    else
    {
        *GPIO_AStrPtr[PortId]->BRR = Mask;
        *GPIO_AStrPtr[PortId]->BSRR = (Level & (PortA_DIO_OutputPins));
    }
}
