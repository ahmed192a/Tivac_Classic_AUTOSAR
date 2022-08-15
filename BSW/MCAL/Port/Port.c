/**
 * @file Port.c
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief  Port file used for Port types definitions and functions prototypes
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Port.h"
#include "Port_Private.h"



STATIC const Port_ConfigChannel * Port_Channels = NULL_PTR; /* Pointer to the first element in the Port_ConfigChannel array */
uint8 Port_Status = PORT_NOT_INITIALIZED;                   /* Port Status */

void Port_Init(const Port_ConfigType* ConfigPtr ){
    #if (DEV_ERROR_DETECT == STD_ON)
        /* Check if the input configuration pointer is not a NULL_PTR */
        if (NULL_PTR == ConfigPtr)
        {
            /* Report to DET  */
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
            return;
        }
    #endif

    Port_Channels = ConfigPtr->Channels; /* Set the Port_Channels to point to the first element in the Port_ConfigChannel array */
    Port_Status = PORT_INITIALIZED;      /* Set the Port_Status to PORT_INITIALIZED */


    volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 * PCTRreg_Ptr = NULL_PTR; /*Pointer to hold the Current Control Register Address*/

    #if (PORT_SET_PIN_DIRECTION_API == STD_ON)
        uint8 PinIndex = 0; /* Loop index for the channels in the Port_ConfigChannel array */
        for (PinIndex = 0; PinIndex < PORT_CONFIGURED_PINS; PinIndex++)
        {
            switch(Port_Channels[PinIndex].port_num)
            {
                case PORTA:
                    Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
                    break;
                case PORTB:
                    Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
                    break;
                case PORTC:
                    Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
                    break;
                case PORTD:
                    Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                    break;
                case PORTE:
                    Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
                    break;
                case PORTF:
                    Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                    break;
                default:
                    /* No Action Required */
                    break;
            }

            // if clock is not enabled for port then enable it
            if (0 == (SYSCTL_RCGC2_R & (1 << Port_Channels[PinIndex].port_num)))
            {
                SYSCTL_RCGC2_R |= (1 << Port_Channels[PinIndex].port_num);
                // wait until clock is enabled
                while (0 == (SYSCTL_PRGPIO_R & (1 << Port_Channels[PinIndex].port_num)));
            }
            /*use the unlock and commit register incase of PD7 & PF0*/
            if (Port_Channels[PinIndex].port_num == PORTD && Port_Channels[PinIndex].pin_num == PIN7)
            {
                GPIO_PORTD_LOCK_R = 0x4C4F434B;
                GPIO_PORTD_CR_R |= (1 << Port_Channels[PinIndex].pin_num);
            }
            else if (Port_Channels[PinIndex].port_num == PORTF && Port_Channels[PinIndex].pin_num == PIN0)
            {
                GPIO_PORTF_LOCK_R = 0x4C4F434B;
                GPIO_PORTF_CR_R |= (1 << Port_Channels[PinIndex].pin_num);
            }

            /*switch case to set the direction of the pin (input or output)*/
            switch (Port_Channels[PinIndex].direction)
            {
                case PORT_PIN_IN:
                    CLEAR_BIT(*(Port_Ptr + PORT_DIR_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    break;
                case PORT_PIN_OUT:
                    SET_BIT(*(Port_Ptr + PORT_DIR_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    break;
                default:
                    /* No Action Required */
                    break;
            }

            /*switch case to set resistor type of the pin (pull up or pull down)*/
            switch (Port_Channels[PinIndex].resistor)
            {
                case PULL_UP:
                    SET_BIT(*(Port_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    break;
                case PULL_DOWN:
                    SET_BIT(*(Port_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    break;
                case OFF:
                    CLEAR_BIT(*(Port_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    CLEAR_BIT(*(Port_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    break;
                default:
                    /* No Action Required */
                    break;
            }

            // save the current control register address
            PCTRreg_Ptr = Port_Ptr + PORT_CTL_REG_OFFSET;
            // set the current control register

            switch(Port_Channels[PinIndex].pin_mode)
            {
                case DIO:
                    // clearing the corresponding bit in the analog register
                    CLEAR_BIT(*(Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    //clear control register
                    *PCTRreg_Ptr &= ~(BYTE_MASK << (Port_Channels[PinIndex].pin_num * 4));
                    //clear alternate function register
                    CLEAR_BIT(*(Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    //set the corresponding bit in the digital register
                    SET_BIT(*(Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    // if the pin is output then set the corresponding bit in the data register
                    if (Port_Channels[PinIndex].direction == PORT_PIN_OUT)
                    {
                        if ((Port_Channels[PinIndex].initial_value & BIT_MASK)  == STD_HIGH)
                        {
                            SET_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                        }
                        else
                        {
                            CLEAR_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                        }
                    }
                    break;
                case ADC:
                    // clearing the corresponding bit in the digital register
                    CLEAR_BIT(*(Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    //clear control register
                    *PCTRreg_Ptr &= ~(BYTE_MASK << (Port_Channels[PinIndex].pin_num * 4));
                    //clear alternate function register
                    CLEAR_BIT(*(Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    //set the corresponding bit in the analog register
                    SET_BIT(*(Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    // if the pin is output then set the corresponding bit in the data register
                    if (Port_Channels[PinIndex].direction == PORT_PIN_OUT)
                    {
                        if ((Port_Channels[PinIndex].initial_value & BIT_MASK)  == STD_HIGH)
                        {
                            SET_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                        }
                        else
                        {
                            CLEAR_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                        }
                    }
                    break;
                default:
                    // clearing the corresponding bit in the analog register
                    CLEAR_BIT(*(Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    // setting the corresponding bits in the digital register
                    SET_BIT(*(Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    // setting the corresponding bits in the alternate function register
                    SET_BIT(*(Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    /*Masking and setting the mode of the current pin in the right bits in the control register*/
                    *PCTRreg_Ptr = (*PCTRreg_Ptr & ~(BYTE_MASK << (Port_Channels[PinIndex].pin_num * 4))) | (Port_Channels[PinIndex].pin_mode << (Port_Channels[PinIndex].pin_num * 4));
                    // if the pin is output then set the corresponding bit in the data register
                    if (Port_Channels[PinIndex].direction == PORT_PIN_OUT)
                    {
                        if ((Port_Channels[PinIndex].initial_value & BIT_MASK)  == STD_HIGH)
                        {
                            SET_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                        }
                        else
                        {
                            CLEAR_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                        }
                    }
                    break;
            }     
                    
        }
    #endif

}


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
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){
#if (DET_DEV_ERROR_DETECT == STD_ON)
    /* Check if the driver is initialized */
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        return;
    }
    /* Check if the input port pin ID is valid */
    else if (Pin >= PORT_CONFIGURED_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        return;
    }
    /* Check if the input port pin direction is valid */
    else if ((Direction != PORT_PIN_IN) && (Direction != PORT_PIN_OUT))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_DIRECTION);
        return;
    }
#endif    


    volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    switch (Port_Channels[Pin].port_num)
    {
        case PORTA:
            Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
        case PORTB:
            Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
        case PORTC:
            Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
        case PORTD:
            Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
        case PORTE:
            Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
        case PORTF:
            Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
        default:
            /* No Action Required */
            break;
    }
    if (Direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(Port_Ptr + PORT_DIR_REG_OFFSET), Port_Channels[Pin].pin_num);
    }
    else
    {
        SET_BIT(*(Port_Ptr + PORT_DIR_REG_OFFSET), Port_Channels[Pin].pin_num);
    }
            
}
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
void Port_RefreshPortDirection(void){
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(Port_Status  == PORT_NOT_INITIALIZED)
    {
        /*Report DET error*/
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
        return;
    }
    #endif

    volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */

    int PinIndex=0;
    for(PinIndex=0 ; PinIndex < PORT_CONFIGURED_PINS ; PinIndex++)
    {
        if(Port_Channels[PinIndex].pin_direction_changeable == STD_OFF) /*Refreshes pins with pin_direction_changeable set to OFF only*/
        {
            switch(Port_Channels[PinIndex].port_num)
            {
                case  PORTA: 
                    Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                    break;

                case  PORTB: 
                    Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                    break;

                case  PORTC: 
                    Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                    break;

                case  PORTD: 
                    Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                    break;
        
                case  PORTE: 
                    Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                    break;
                case PORTF:
                    Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                    break;
                default:
                    /* No Action Required */
                    break;
            }


            /*use the unlock and commit register incase of PD7 & PF0*/
            if (Port_Channels[PinIndex].port_num == PORTD && Port_Channels[PinIndex].pin_num == PIN7)
            {
                GPIO_PORTD_LOCK_R = 0x4C4F434B;
                GPIO_PORTD_CR_R |= (1 << Port_Channels[PinIndex].pin_num);
            }
            else if (Port_Channels[PinIndex].port_num == PORTF && Port_Channels[PinIndex].pin_num == PIN0)
            {
                GPIO_PORTF_LOCK_R = 0x4C4F434B;
                GPIO_PORTF_CR_R |= (1 << Port_Channels[PinIndex].pin_num);
            }

            /*switch case to set the direction of the pin (input or output)*/
            switch(Port_Channels[PinIndex].direction)
            {
                case PORT_PIN_IN:
                    CLEAR_BIT(*(Port_Ptr + PORT_DIR_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    break;
                case PORT_PIN_OUT:
                    SET_BIT(*(Port_Ptr + PORT_DIR_REG_OFFSET), Port_Channels[PinIndex].pin_num);
                    break;
                default:
                    /* No Action Required */
                    break;
            }
        }
    }
}



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
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo){
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(Port_Status  == PORT_NOT_INITIALIZED)
    {
        /*Report DET error*/
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
        return;
    }
    #endif

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(versioninfo == NULL_PTR)
    {
        /*Report DET error*/
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
        return;
    }
    #endif

    versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
    versioninfo->moduleID = (uint16)PORT_MODULE_ID;
    versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
}
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
void Port_SetPinMode(  Port_PinType Pin, Port_PinModeType Mode ){
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(Port_Status  == PORT_NOT_INITIALIZED)
    {
        /*Report DET error*/
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
        return;
    }
    #endif

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(Pin >= PORT_CONFIGURED_PINS)
    {
        /*Report DET error*/
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        return;
    }
    #endif

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(Mode >= PORT_CONFIGURED_MODES)
    {
        /*Report DET error*/
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
        return;
    }
    #endif

    if(Port_Channels[Pin].pin_mode_changeable == STD_ON ) /*Checking if the pin mode is changable before changing it*/
    {

        volatile uint32 * Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        switch(Port_Channels[Pin].port_num) /*Checking the current port number and saving its address to Port_Ptr*/
        {
            case  PORTA: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                        break;

            case  PORTB: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                        break;

            case  PORTC: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                        break;

            case  PORTD: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                        break;

            case  PORTE: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                        break;

            case  PORTF: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                        break;
            default:        break; /*default case to obey MISRA rules*/
        }




        /*use the unlock and commit register incase of PD7 & PF0*/
        if (Port_Channels[Pin].port_num == PORTD && Port_Channels[Pin].pin_num == PIN7)
        {
            GPIO_PORTD_LOCK_R = 0x4C4F434B;
            GPIO_PORTD_CR_R |= (1 << Port_Channels[Pin].pin_num);
        }
        else if (Port_Channels[Pin].port_num == PORTF && Port_Channels[Pin].pin_num == PIN0)
        {
            GPIO_PORTF_LOCK_R = 0x4C4F434B;
            GPIO_PORTF_CR_R |= (1 << Port_Channels[Pin].pin_num);
        }

        volatile uint32 * PCTRreg_Ptr = NULL_PTR; /*Pointer to hold the Current Control Register Address*/

        /*Saving the Current Control Register Address in the PCTR_Ptr*/
        PCTRreg_Ptr = Port_Ptr + PORT_CTL_REG_OFFSET ;

        switch(Port_Channels[Pin].pin_mode)
            {
                case DIO:
                    // clearing the corresponding bit in the analog register
                    CLEAR_BIT(*(Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[Pin].pin_num);
                    //clear control register
                    *PCTRreg_Ptr &= ~(BYTE_MASK << (Port_Channels[Pin].pin_num * 4));
                    //clear alternate function register
                    CLEAR_BIT(*(Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[Pin].pin_num);
                    //set the corresponding bit in the digital register
                    SET_BIT(*(Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[Pin].pin_num);
                    // if the pin is output then set the corresponding bit in the data register
                    if (Port_Channels[Pin].direction == PORT_PIN_OUT)
                    {
                        if ((Port_Channels[Pin].initial_value & BIT_MASK)  == STD_HIGH)
                        {
                            SET_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[Pin].pin_num);
                        }
                        else
                        {
                            CLEAR_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[Pin].pin_num);
                        }
                    }
                    break;
                case ADC:
                    // clearing the corresponding bit in the digital register
                    CLEAR_BIT(*(Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[Pin].pin_num);
                    //clear control register
                    *PCTRreg_Ptr &= ~(BYTE_MASK << (Port_Channels[Pin].pin_num * 4));
                    //clear alternate function register
                    CLEAR_BIT(*(Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[Pin].pin_num);
                    //set the corresponding bit in the analog register
                    SET_BIT(*(Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[Pin].pin_num);
                    // if the pin is output then set the corresponding bit in the data register
                    if (Port_Channels[Pin].direction == PORT_PIN_OUT)
                    {
                        if ((Port_Channels[Pin].initial_value & BIT_MASK)  == STD_HIGH)
                        {
                            SET_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[Pin].pin_num);
                        }
                        else
                        {
                            CLEAR_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[Pin].pin_num);
                        }
                    }
                    break;
                default:
                    // clearing the corresponding bit in the analog register
                    CLEAR_BIT(*(Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[Pin].pin_num);
                    // setting the corresponding bits in the digital register
                    SET_BIT(*(Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[Pin].pin_num);
                    // setting the corresponding bits in the alternate function register
                    SET_BIT(*(Port_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[Pin].pin_num);
                    /*Masking and setting the mode of the current pin in the right bits in the control register*/
                    *PCTRreg_Ptr = (*PCTRreg_Ptr & ~(BYTE_MASK << (Port_Channels[Pin].pin_num * 4))) | (Port_Channels[Pin].pin_mode << (Port_Channels[Pin].pin_num * 4));
                    // if the pin is output then set the corresponding bit in the data register
                    if (Port_Channels[Pin].direction == PORT_PIN_OUT)
                    {
                        if ((Port_Channels[Pin].initial_value & BIT_MASK)  == STD_HIGH)
                        {
                            SET_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[Pin].pin_num);
                        }
                        else
                        {
                            CLEAR_BIT(*(Port_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[Pin].pin_num);
                        }
                    }
                    break;
            }   
    }
    
}


