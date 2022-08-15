/**
 * @file DIO.c
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief Dio.c is the source file for DIO.h file which contains the implementation of the functions.
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "DIO.h"
#include "DIO_Private.h"

/**
 * @brief Dio_ReadChannel is a service that returns the value of the specified DIO channel
 * 
 * @details Service ID [hex] 0x00
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 *          
 * @param [in] ChannelId         The channel ID of the DIO channel to be read.
 * @return Dio_LevelType    The value of the specified DIO channel.
 *                             - STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 *                             - STD_LOW The physical level of the corresponding Pin is STD_LOW
 */
Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId ){
    Dio_LevelType Level;
    if (ChannelId < 8)
    {
        Level = (Dio_LevelType)GET_BIT(GPIO_PORTA_DATA_R,ChannelId);
    }
    else if (ChannelId < 16)
    {
        Level = (Dio_LevelType)GET_BIT(GPIO_PORTB_DATA_R,ChannelId-8);
    }
    else if (ChannelId < 24)
    {
        Level = (Dio_LevelType)GET_BIT(GPIO_PORTC_DATA_R,ChannelId-16);
    }
    else if (ChannelId < 32)
    {
        Level = (Dio_LevelType)GET_BIT(GPIO_PORTD_DATA_R,ChannelId-24);
    }
    else if (ChannelId < 40)
    {
        Level = (Dio_LevelType)GET_BIT(GPIO_PORTE_DATA_R,ChannelId-32);
    }
    else if (ChannelId < 48)
    {
        Level = (Dio_LevelType)GET_BIT(GPIO_PORTF_DATA_R,ChannelId-40);
    }
    return Level;
}

/**
 * @brief Dio_WriteChannel Service to set a level of a channel.
 * 
 * @details Service ID [hex] 0x01
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 * 
 * @param [in] ChannelId     The channel ID of the DIO channel to be written.
 * @param [in] Level         The value to be written to the specified DIO channel.
 */
void Dio_WriteChannel (Dio_ChannelType ChannelId,   Dio_LevelType Level){
    if (ChannelId < 8)
    {
        if (Level == STD_HIGH)
        {
            SET_BIT(GPIO_PORTA_DATA_R,ChannelId);
        }
        else
        {
            CLR_BIT(GPIO_PORTA_DATA_R,ChannelId);
        }
    }
    else if (ChannelId < 16)
    {
        if (Level == STD_HIGH)
        {
            SET_BIT(GPIO_PORTB_DATA_R,ChannelId-8);
        }
        else
        {
            CLR_BIT(GPIO_PORTB_DATA_R,ChannelId-8);
        }
    }
    else if (ChannelId < 24)
    {
        if (Level == STD_HIGH)
        {
            SET_BIT(GPIO_PORTC_DATA_R,ChannelId-16);
        }
        else
        {
            CLR_BIT(GPIO_PORTC_DATA_R,ChannelId-16);
        }
    }
    else if (ChannelId < 32)
    {
        if (Level == STD_HIGH)
        {
            SET_BIT(GPIO_PORTD_DATA_R,ChannelId-24);
        }
        else
        {
            CLR_BIT(GPIO_PORTD_DATA_R,ChannelId-24);
        }
    }
    else if (ChannelId < 40)
    {
        if (Level == STD_HIGH)
        {
            SET_BIT(GPIO_PORTE_DATA_R,ChannelId-32);
        }
        else
        {
            CLR_BIT(GPIO_PORTE_DATA_R,ChannelId-32);
        }
    }
    else if (ChannelId < 48)
    {
        if (Level == STD_HIGH)
        {
            SET_BIT(GPIO_PORTF_DATA_R,ChannelId-40);
        }
        else
        {
            CLR_BIT(GPIO_PORTF_DATA_R,ChannelId-40);
        }
    }
}

/**
 * @brief Dio_ReadPort is a service that returns the level of all channels of that port
 * 
 * @details Service ID [hex] 0x02
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 *          
 * @param [in] PortId         The port ID of the DIO port to be read.
 * @return Dio_PortLevelType    The value of the specified DIO port.
 *                             - STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 *                             - STD_LOW The physical level of the corresponding Pin is STD_LOW
 */
Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId ){
    Dio_PortLevelType PortLevel;
    if (PortId == PORTA)
    {
        PortLevel = GPIO_PORTA_DATA_R;
    }
    else if (PortId == PORTB)
    {
        PortLevel = GPIO_PORTB_DATA_R;
    }
    else if (PortId == PORTC)
    {
        PortLevel = GPIO_PORTC_DATA_R;
    }
    else if (PortId == PORTD)
    {
        PortLevel = GPIO_PORTD_DATA_R;
    }
    else if (PortId == PORTE)
    {
        PortLevel = GPIO_PORTE_DATA_R;
    }
    else if (PortId == PORTF)
    {
        PortLevel = GPIO_PORTF_DATA_R;
    }
    return PortLevel;
}

/**
 * @brief Dio_WritePort Service to set a level of a port.
 * 
 * @details Service ID [hex] 0x03
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 * 
 * @param [in] PortId     The port ID of the DIO port to be written.
 * @param [in] Level         The value to be written to the specified DIO port.
 */
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level){
    if (PortId == PORTA)
    {
        GPIO_PORTA_DATA_R = Level;
    }
    else if (PortId == PORTB)
    {
        GPIO_PORTB_DATA_R = Level;
    }
    else if (PortId == PORTC)
    {
        GPIO_PORTC_DATA_R = Level;
    }
    else if (PortId == PORTD)
    {
        GPIO_PORTD_DATA_R = Level;
    }
    else if (PortId == PORTE)
    {
        GPIO_PORTE_DATA_R = Level;
    }
    else if (PortId == PORTF)
    {
        GPIO_PORTF_DATA_R = Level;
    }
}

/**
 * @brief Dio_ReadChannelGroup is a service that returns the value of the specified DIO channel group
 * 
 * @details Service ID [hex] 0x04
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 *          
 * @param [in] ChannelGroupIdPtr  Pointer to the channel group ID of the DIO channel group to be read.
 * @return Dio_PortLevelType      The value of the specified DIO channel group.
 *                                  - STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 *                                  - STD_LOW The physical level of the corresponding Pin is STD_LOW
 */
Dio_PortLevelType Dio_ReadChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr){
    Dio_PortLevelType PortLevel;
    if (ChannelGroupIdPtr->port == PORTA)
    {
        PortLevel = GPIO_PORTA_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTB)
    {
        PortLevel = GPIO_PORTB_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTC)
    {
        PortLevel = GPIO_PORTC_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTD)
    {
        PortLevel = GPIO_PORTD_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTE)
    {
        PortLevel = GPIO_PORTE_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTF)
    {
        PortLevel = GPIO_PORTF_DATA_R;
    }
    PortLevel = PortLevel & ChannelGroupIdPtr->mask;
    PortLevel = PortLevel >> ChannelGroupIdPtr->offset;
    return PortLevel;
}

/**
 * @brief Dio_WriteChannelGroup Service to set a level of a channel group.
 * 
 * @details Service ID [hex] 0x05
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 * 
 * @param [in] ChannelGroupIdPtr  Pointer to the channel group ID of the DIO channel group to be written.
 * @param [in] Level              The value to be written to the specified DIO channel group.
 */
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level){
    Dio_PortLevelType PortLevel;
    if (ChannelGroupIdPtr->port == PORTA)
    {
        PortLevel = GPIO_PORTA_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTB)
    {
        PortLevel = GPIO_PORTB_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTC)
    {
        PortLevel = GPIO_PORTC_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTD)
    {
        PortLevel = GPIO_PORTD_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTE)
    {
        PortLevel = GPIO_PORTE_DATA_R;
    }
    else if (ChannelGroupIdPtr->port == PORTF)
    {
        PortLevel = GPIO_PORTF_DATA_R;
    }
    PortLevel = PortLevel & (~ChannelGroupIdPtr->mask);
    PortLevel = PortLevel | (Level << ChannelGroupIdPtr->offset);
    if (ChannelGroupIdPtr->port == PORTA)
    {
        GPIO_PORTA_DATA_R = PortLevel;
    }
    else if (ChannelGroupIdPtr->port == PORTB)
    {
        GPIO_PORTB_DATA_R = PortLevel;
    }
    else if (ChannelGroupIdPtr->port == PORTC)
    {
        GPIO_PORTC_DATA_R = PortLevel;
    }
    else if (ChannelGroupIdPtr->port == PORTD)
    {
        GPIO_PORTD_DATA_R = PortLevel;
    }
    else if (ChannelGroupIdPtr->port == PORTE)
    {
        GPIO_PORTE_DATA_R = PortLevel;
    }
    else if (ChannelGroupIdPtr->port == PORTF)
    {
        GPIO_PORTF_DATA_R = PortLevel;
    }
}

/**
 * @brief DIO_GetVersionInfo is a service that returns the version information of the DIO module.
 * 
 * @details Service ID [hex] 0x12
 *         Synchronous/Asynchronous: Synchronous
 *        Reentrancy: Reentrant
 * 
 * @param [out] versioninfo Pointer to where to store the version information of the DIO module.
 */
void Dio_GetVersionInfo (Std_VersionInfoType* versioninfo){
    versioninfo->vendorID = DIO_VENDOR_ID;
    versioninfo->moduleID = DIO_MODULE_ID;
    versioninfo->sw_major_version = DIO_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DIO_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DIO_SW_PATCH_VERSION;
}

/**
 * @brief Dio_FlipChannel is a service that flips the level of the specified DIO channel.
 * 
 * @details Service ID [hex] 0x11
 *         Synchronous/Asynchronous: Synchronous
 *       Reentrancy: Reentrant
 * 
 * @param [in] ChannelId         The channel ID of the DIO channel to be flipped.
 * @return Dio_LevelType    The value of the specified DIO channel.
 *                            - STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 *                            - STD_LOW The physical level of the corresponding Pin is STD_LOW
 */
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId){
    Dio_LevelType Level;
    if (ChannelId < 8)
    {
        Level = GPIO_PORTA_DATA_R;
    }
    else if (ChannelId < 16)
    {
        Level = GPIO_PORTB_DATA_R;
    }
    else if (ChannelId < 24)
    {
        Level = GPIO_PORTC_DATA_R;
    }
    else if (ChannelId < 32)
    {
        Level = GPIO_PORTD_DATA_R;
    }
    else if (ChannelId < 40)
    {
        Level = GPIO_PORTE_DATA_R;
    }
    else if (ChannelId < 44)
    {
        Level = GPIO_PORTF_DATA_R;
    }
    Level = Level & (1 << (ChannelId % 8));
    if (Level == 0)
    {
        Level = 1;
    }
    else
    {
        Level = 0;
    }
    if (ChannelId < 8)
    {
        GPIO_PORTA_DATA_R = Level;
    }
    else if (ChannelId < 16)
    {
        GPIO_PORTB_DATA_R = Level;
    }
    else if (ChannelId < 24)
    {
        GPIO_PORTC_DATA_R = Level;
    }
    else if (ChannelId < 32)
    {
        GPIO_PORTD_DATA_R = Level;
    }
    else if (ChannelId < 40)
    {
        GPIO_PORTE_DATA_R = Level;
    }
    else if (ChannelId < 44)
    {
        GPIO_PORTF_DATA_R = Level;
    }
    return Level;
}

/**
 * @brief Dio_MaskedReadChannel is a service that returns the value of the specified DIO channel
 * 
 * @details Service ID [hex] 0x13
 *         Synchronous/Asynchronous: Synchronous
 *      Reentrancy: Reentrant
 * 
 * @param [in] PortId        The port ID of the DIO port to be read.
 * @param [in] Level         The value of the specified DIO port.
 * @param [in] Mask          The value of the specified DIO port.
 */
void Dio_MaskedWritePort (Dio_PortType PortId,Dio_PortLevelType Level,Dio_PortLevelType Mask){
    Dio_PortLevelType PortLevel;
    if (PortId == PORTA)
    {
        PortLevel = GPIO_PORTA_DATA_R;
    }
    else if (PortId == PORTB)
    {
        PortLevel = GPIO_PORTB_DATA_R;
    }
    else if (PortId == PORTC)
    {
        PortLevel = GPIO_PORTC_DATA_R;
    }
    else if (PortId == PORTD)
    {
        PortLevel = GPIO_PORTD_DATA_R;
    }
    else if (PortId == PORTE)
    {
        PortLevel = GPIO_PORTE_DATA_R;
    }
    else if (PortId == PORTF)
    {
        PortLevel = GPIO_PORTF_DATA_R;
    }
    PortLevel = PortLevel & (~Mask);
    PortLevel = PortLevel | (Level & Mask);
    if (PortId == PORTA)
    {
        GPIO_PORTA_DATA_R = PortLevel;
    }
    else if (PortId == PORTB)
    {
        GPIO_PORTB_DATA_R = PortLevel;
    }
    else if (PortId == PORTC)
    {
        GPIO_PORTC_DATA_R = PortLevel;
    }
    else if (PortId == PORTD)
    {
        GPIO_PORTD_DATA_R = PortLevel;
    }
    else if (PortId == PORTE)
    {
        GPIO_PORTE_DATA_R = PortLevel;
    }
    else if (PortId == PORTF)
    {
        GPIO_PORTF_DATA_R = PortLevel;
    }
}



