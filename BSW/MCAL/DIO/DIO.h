/**
 * @file DIO.h
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief DIO file used for DIO types definitions and functions prototypes
 * @version 0.1
 * @date 2022-07-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DIO_H
#define DIO_H

/*
 * Module Version 1.0.0
 */
#define DIO_SW_MAJOR_VERSION           (1U)
#define DIO_SW_MINOR_VERSION           (0U)
#define DIO_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.6.0
 */
#define DIO_AR_RELEASE_MAJOR_VERSION   (4U)
#define DIO_AR_RELEASE_MINOR_VERSION   (0U)
#define DIO_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Dio Status
 */
#define DIO_INITIALIZED                (1U)
#define DIO_NOT_INITIALIZED            (0U)


/* Id for the company in the AUTOSAR */
#define DIO_VENDOR_ID    (1000U)

/* Dio Module Id */
#define DIO_MODULE_ID    (120U)

/* Dio Instance Id */
#define DIO_INSTANCE_ID  (0U)


#include "../Std_types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif




/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for DIO read Channel */
#define DIO_READ_CHANNEL_SID           (uint8)0x00

/* Service ID for DIO write Channel */
#define DIO_WRITE_CHANNEL_SID          (uint8)0x01

/* Service ID for DIO read Port */
#define DIO_READ_PORT_SID              (uint8)0x02

/* Service ID for DIO write Port */
#define DIO_WRITE_PORT_SID             (uint8)0x03

/* Service ID for DIO read Channel Group */
#define DIO_READ_CHANNEL_GROUP_SID     (uint8)0x04

/* Service ID for DIO write Channel Group */
#define DIO_WRITE_CHANNEL_GROUP_SID    (uint8)0x05

/* Service ID for DIO GetVersionInfo */
#define DIO_GET_VERSION_INFO_SID       (uint8)0x12

/* Service ID for DIO Init Channel */
#define DIO_INIT_SID                   (uint8)0x10

/* Service ID for DIO flip Channel */
#define DIO_FLIP_CHANNEL_SID           (uint8)0x11



/*
 *  PORT IDs
 */
#define PORTA       0
#define PORTB       1
#define PORTC       2
#define PORTD       3
#define PORTE       4
#define PORTF       5

typedef uint8  Dio_ChannelType;    /**< DIO Channel Type */
typedef uint8  Dio_PortType;       /**< DIO Port Type */
typedef uint8  Dio_LevelType;      /**< DIO Level Type Range [ 0x00 Physical state 0V, 0x01 Physical state 5V or 3.3V ] */
typedef uint8  Dio_PortLevelType;  /**< If the µC owns ports of different port widths (e.g. 4, 8,16...Bit) Dio_PortLevelType inherits the size of the largest port. */
typedef uint8  Dio_PortLevelType;  /**< DIO Port Level Type */

/**
 * @brief Type for the definition of a channel group, which consists of several adjoining channels within a port.
 * 
 */
typedef struct 
{
    uint8  mask;      // This element mask which defines the positions of the channel group.
    uint8  offset;     // This element shall be the position of the Channel Group on the port, counted from the LSB.
    Dio_PortType port;  // This shall be the port on which the Channel group is defined
}Dio_ChannelGroupType; 


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
Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId );


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
void Dio_WriteChannel (Dio_ChannelType ChannelId,   Dio_LevelType Level);


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
Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId );


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
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level);


/**
 * @brief Dio_ReadChannelGroup is a service that returns the value of the specified DIO channel group
 * 
 * @details Service ID [hex] 0x04
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 *          
 * @param [inout] ChannelGroupIdPtr  Pointer to the channel group ID of the DIO channel group to be read.
 * @return Dio_PortLevelType      The value of the specified DIO channel group.
 *                                  - STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 *                                  - STD_LOW The physical level of the corresponding Pin is STD_LOW
 */
Dio_PortLevelType Dio_ReadChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr);

/**
 * @brief Dio_WriteChannelGroup Service to set a level of a channel group.
 * 
 * @details Service ID [hex] 0x05
 *          Synchronous/Asynchronous: Synchronous
 *          Reentrancy: Reentrant
 * 
 * @param [inout] ChannelGroupIdPtr  Pointer to the channel group ID of the DIO channel group to be written.
 * @param [in] Level              The value to be written to the specified DIO channel group.
 */
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level);

/**
 * @brief DIO_GetVersionInfo is a service that returns the version information of the DIO module.
 * 
 * @details Service ID [hex] 0x12
 *         Synchronous/Asynchronous: Synchronous
 *        Reentrancy: Reentrant
 * 
 * @param [inout] versioninfo Pointer to where to store the version information of the DIO module.
 */
void Dio_GetVersionInfo (Std_VersionInfoType* versioninfo);

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
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId);


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
void Dio_MaskedWritePort (Dio_PortType PortId,Dio_PortLevelType Level,Dio_PortLevelType Mask);



#endif