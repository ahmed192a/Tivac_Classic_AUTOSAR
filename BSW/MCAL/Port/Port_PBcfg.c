/**
 * @file Port_PBcfg.c
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (6U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (0U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/*Configuration structure that will be used by the port driver to initialize all the pins
  using default settings of DIO,INPUT,RESISTANCE OFF,DIRECTION AND MODE NOT CHANGABLE.

  The configuration structure configures the Button in PF4 and LED in PF1 with the needed
  configurations by the project*/

const Port_ConfigType Port_Configuration= 
{
	PORTA,PIN0,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTA,PIN1,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTA,PIN2,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTA,PIN3,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTA,PIN4,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTA,PIN5,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTA,PIN6,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTA,PIN7,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,

	PORTB,PIN0,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTB,PIN1,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTB,PIN2,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTB,PIN3,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTB,PIN4,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTB,PIN5,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTB,PIN6,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTB,PIN7,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,


	PORTC,PIN4,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTC,PIN5,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTC,PIN6,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTC,PIN7,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,

	PORTD,PIN0,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTD,PIN1,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTD,PIN2,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTD,PIN3,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTD,PIN4,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTD,PIN5,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTD,PIN6,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTD,PIN7,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,

	PORTE,PIN0,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTE,PIN1,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTE,PIN2,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTE,PIN3,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTE,PIN4,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTE,PIN5,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,

	PORTF,PIN0,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTF,PIN1,PORT_PIN_OUT,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTF,PIN2,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTF,PIN3,PORT_PIN_IN,DIO,OFF,STD_LOW,STD_OFF,STD_OFF,
	PORTF,PIN4,PORT_PIN_IN,DIO,PULL_UP,STD_LOW,STD_OFF,STD_OFF
};
