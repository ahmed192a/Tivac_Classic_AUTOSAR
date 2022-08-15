/**
 * @file Port.h
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PORT_H_
#define PORT_H_


#include "../Common_Macros.h"
#include "../Std_types.h"
#include "Port_Cfg.h"


/* Port for the company in the AUTOSAR*/
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (130U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.6.0
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (6U)
#define PORT_AR_RELEASE_PATCH_VERSION   (0U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)


/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

// /* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
// #if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
//  ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
//  ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
//   #error "The AR version of Port_Cfg.h does not match the expected version"
// #endif

// /* Software Version checking between Port_Cfg.h and Port.h files */
// #if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
//  ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
//  ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
//   #error "The SW version of Port_Cfg.h does not match the expected version"
// #endif

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID           (uint8)0x00

/* Service ID for Port_Init */
#define PORT_INIT_SID                		 (uint8)0x01

/* Service ID for Port_SetPinMode*/
#define PORT_SET_PIN_MODE_SID                (uint8)0x02

/* Service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID            (uint8)0x03

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIRECTION_SID      (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN 							(uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE         	    (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter*/
#define PORT_E_PARAM_CONFIG 					    (uint8)0x0C

/* DET code to report API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE				    (uint8)0x0D

/*
 *API Port_SetPinMode service called when mode is unchangeable.
 */
#define PORT_E_MODE_UNCHANGEABLE    		        (uint8)0x0E

/*
 *API service called without module initialization
 */
#define PORT_E_UNINIT                 			    (uint8)0x0F

/* DET code to report APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER 					    (uint8)0x10

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/



/*Clock Gating Register*/
// #define RCGC2_REGISTER_ADDRESS			  SYSCTL_RCGC2_R


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*Symbolic name of a Port Pin number (43 pins)*/
typedef uint8 Port_PinType;

/* Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,            //!< 0x00 Sets port pin as input.
    PORT_PIN_OUT            //!< 0x01 Sets port pin as output.
}Port_PinDirectionType;

/* Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,        //!< 0x00 disable internal resistor.
    PULL_UP,    //!< 0x01 enable internal pull-up resistor.
    PULL_DOWN   //!< 0x02 enable internal pull-down resistor.
}Port_InternalResistor;

typedef uint8 Port_PinModeType; // Different port pin modes.

/* Definition of the Configuration Structure which will configure each individual PIN.
 * Member port_num will determine the port of the pin.
 * Member pin num will determine the pin number in the port.
 * Member direction will determine the direction of the pin (input or output).
 * Member resistor will determine the resistor type of the pin (pull up - pull down - off).
 * Member initial_value will determine the initial value of the pin in case of output pin.
 * Member pin_mode_changeable will determine if the pin mode can be changed after initialization.
 * Member pin_direction_changeable will determine if the pin direction can be changed after initialization.
 */
typedef struct 
{
    uint8 port_num; 
    uint8 pin_num; 
    Port_PinDirectionType direction;
    Port_PinModeType pin_mode;
    Port_InternalResistor resistor;
    uint8 initial_value;
    uint8 pin_mode_changeable; //STD_ON OR STD_OFF
    uint8 pin_direction_changeable; //STD_ON OR STD_OFF
}Port_ConfigChannel;

typedef struct
{
	Port_ConfigChannel Channels[PINS_NUMBER_EXCEPT_JTAG];
}Port_ConfigType;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/


/**
 * @brief Initializes the Port Driver module.
 * @details This function shall initialize all pins configured in the configuration set referenced by ConfigPtr.
 *          Reentrant: Non Reentrant
 *          Synchronous: Synchronous
 *          
 * @param [in] ConfigPtr Pointer to configuration set.
 * @return None
 *
 * @note This function shall initialize all pins configured in the configuration set.  
 */
void Port_Init(
	const Port_ConfigType* ConfigPtr );



#if (PORT_SET_PIN_DIRECTION_API == TRUE) 
/**
 * @brief Port_SetPinDirection
 * @details This function shall set the port pin direction.
 *          Reentrant: Reentrant
 *          Synchronous: Synchronous
 * 
 * @param [in] Pin          Port Pin ID number
 * @param [in] Direction    Port Pin Direction
 * @return None
 */
void Port_SetPinDirection( 
	Port_PinType Pin,
	Port_PinDirectionType Direction );
#endif



/**
 * @brief Refreshes port direction.
 * @details This function shall refresh port direction.
 *          Reentrant: Non-Reentrant
 *          Synchronous: Synchronous
 *          
 * @param None
 * @return None
 *
 * @note This function shall refresh port direction.  
 */
void Port_RefreshPortDirection(void);


#if (PORT_VERSION_INFO_API == STD_ON)
/**
 * @brief Returns the version information of this module.
 * @details This function shall return the version information of this module.
 *          Reentrant: Non-Reentrant
 *          Synchronous: Synchronous
 *          
 * @param [in] versioninfo Pointer to where to store the version information of this module.
 * @return None
 *
 * @note This function shall return the version information of this module.  
 */
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif


/**
 * @brief Sets the port pin mode.
 * @details This function shall set the port pin mode.
 *          Reentrant: Reentrant
 *          Synchronous: Synchronous
 *          
 * @param [in] Pin  Port Pin ID number
 * @param [in] Mode Port Pin Mode to be set on port pin
 * @return None
 *
 * @note This function shall set the port pin mode.  
 */
void Port_SetPinMode( 
	Port_PinType Pin, 
	Port_PinModeType Mode );


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

/* Extern Port_Status to be used by button_init and led_init functions
   This will help in following the layering system of AUTOSAR by not including
   port.h and dio.h in the app*/
extern uint8 Port_Status;

#endif /* PORT_H */
