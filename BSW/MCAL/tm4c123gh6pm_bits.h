/**
 * @file tm4c123gh6pm_bits.h
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief  definitions of bits in Tiva C registers 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TM4C123GH6PM_BITS_H_
#define TM4C123GH6PM_BITS_H_

/* in register CANCTL */
#define INIT        0
#define IE          1
#define SIE         2
#define EIE         3
#define DAR         5
#define CCE         6
#define TEST        7


/* in register CAN0_IFnCRQ_R*/
#define BUSY        15

/* in register CAN0_BIT_R */
#define TSEG2       0xFFFF8FFF
#define TSEG1       0xFFFFF0FF
#define SJW         0xFFFFFF3F
#define BRP         0xFFFFFFC0

/* in register CAN0_BIT_R */
#define TSEG2       0xFFFF8FFF
#define TSEG1       0xFFFFF0FF
#define SJW         0xFFFFFF3F
#define BRP         0xFFFFFFC0

/* in register CANIFnCMSK */
#define WRNRD          7
#define MASK           6
#define ARB            5
#define CONTROL        4
#define CLRINTPND      3
#define NEWDAT_CMSK    2
#define TXRQST         2
#define DATAA          1
#define DATAB          0

/* in register CANIFnARB2*/
#define MSGVAL         15
#define XTD            14
#define DIR            13

/* in register CANIFnMCTL */

#define NEWDAT_MCTL    15
#define MSGLST         14
#define INTPND         13
#define UMASK          12
#define TXIE           11
#define RXIE           10
//#define TXRQST         8

/*in register CANIFnMSK2*/
#define MXTD           15
#define MDIR           14

/* PORT A PINS */
#define PA_Pin0_Id     0
#define PA_Pin1_Id     1
#define PA_Pin2_Id     2
#define PA_Pin3_Id     3
#define PA_Pin4_Id     4
#define PA_Pin5_Id     5
#define PA_Pin6_Id     6
#define PA_Pin7_Id     7

/*PORT B PINS */
#define PB_Pin0_Id      0
#define PB_Pin1_Id      1
#define PB_Pin2_Id      2
#define PB_Pin3_Id      3
#define PB_Pin4_Id      4
#define PB_Pin5_Id      5
#define PB_Pin6_Id      6
#define PB_Pin7_Id      7

/*PORT C PINS */
#define PC_Pin0_Id      0
#define PC_Pin1_Id      1
#define PC_Pin2_Id      2
#define PC_Pin3_Id      3
#define PC_Pin4_Id      4
#define PC_Pin5_Id      5
#define PC_Pin6_Id      6
#define PC_Pin7_Id      7

/*PORT D PINS */
#define PD_Pin0_Id      0
#define PD_Pin1_Id      1
#define PD_Pin2_Id      2
#define PD_Pin3_Id      3
#define PD_Pin4_Id      4
#define PD_Pin5_Id      5
#define PD_Pin6_Id      6
#define PD_Pin7_Id      7

/*PORT E PINS */
#define PE_Pin0_Id      0
#define PE_Pin1_Id      1
#define PE_Pin2_Id      2
#define PE_Pin3_Id      3
#define PE_Pin4_Id      4
#define PE_Pin5_Id      5

/*PORT F PINS */
#define PF_Pin0_Id      0
#define PF_Pin1_Id      1
#define PF_Pin2_Id      2
#define PF_Pin3_Id      3
#define PF_Pin4_Id      4
#define PF_Pin5_Id      5
#define PF_Pin6_Id      6
#define PF_Pin7_Id      7

/* in register RCGCCAN which enables clock to CAN module*/
#define CAN0_CLOCK           0
#define CAN1_CLOCK           1

/* in register PRCAN which check that CAN module is ready*/
#define CAN0_CLOCKCHECK      0
#define CAN1_CLOCKCHECK      1

/* in register RCGCGPIO which enables clock to GPIO Ports*/
#define PORT_A_CLOCK         0
#define PORT_B_CLOCK         1
#define PORT_C_CLOCK         2
#define PORT_D_CLOCK         3
#define PORT_E_CLOCK         4
#define PORT_F_CLOCK         5

/*in register PRGPIO which checks that GPIO Ports are ready*/
#define PORT_A_CLOCKCHECK    0
#define PORT_B_CLOCKCHECK    1
#define PORT_C_CLOCKCHECK    2
#define PORT_D_CLOCKCHECK    3
#define PORT_E_CLOCKCHECK    4
#define PORT_F_CLOCKCHECK    5

/*******************************************************************************
 *                              CAN Bit Fields                                 *
 *******************************************************************************/
/*in CANCTL register that enables the Interrupts*/
#define ERROR_INT_ENABLE                3
#define STATUS_INT_ENABLE               2
#define CAN_INT_ENABLE                  1

/* in CANSTS register contains information for interrupt servicing */
#define BUS_OFF_STATUS                  7
#define RECIEVED_MSG_OK                 4
#define TRANSMITTED_MSG_OK              3

/* in CANIFnCMSK register contains information for interrupt servicing */
#define CLR_INT_PND                     3

/* in CANIFnMCTL register contains information for interrupt servicing */
#define INT_PND                         13


/*******************************************************************************
 *                       CANINT Register possible values                       *
 *******************************************************************************/

#define CAN_NO_INT                      0x00000000  // No interrupt pending
#define CAN_INT_INTID_STATUS            0x00008000  // Status Interrupt


/*******************************************************************************
 *                              Base Addresses                                 *
 *******************************************************************************/

#define CAN0_BASE_ADDRESS              (volatile unsigned long *)0x40040000
#define CAN1_BASE_ADDRESS              (volatile unsigned long *)0x40041000   
/*******************************************************************************
 *                              Registers Offset                              *
 *******************************************************************************/
#define CANCTL_OFFSET                   0x00
#define CANSTS_OFFSET                   0x04
#define CANINT_OFFSET                   0x10
#define CANIF1CMSK_OFFSET               0x24
#define CANIF2CMSK_OFFSET               0x84
#define CANIF1MCTL_OFFSET               0x38
#define CANIF2MCTL_OFFSET               0x98


/*******************************************************************************
 *                        Priority registers Addresses                         *
 *******************************************************************************/
#define CAN0_PR_ADDRESS             (*((volatile unsigned long *)0xE000E424))
#define CAN1_PR_ADDRESS             (*((volatile unsigned long *)0xE000E428))


/*******************************************************************************
 *                       CAN Priority Masks                                    *
 *******************************************************************************/

#define CAN0_PRIORITY_MASK          0x1FFFFFFF
#define CAN1_PRIORITY_MASK          0xFFFFFF1F
   
/*******************************************************************************
 *                    CAN Priority and priority pos                            *
 *******************************************************************************/
#define CAN0_INTERRUPT_PRIORITY       0      /* Highest Priority Level */
#define CAN0_PRIORITY_BITS_POS        29
#define CAN1_INTERRUPT_PRIORITY       0      /* Highest Priority Level */
#define CAN1_PRIORITY_BITS_POS        5


#endif /* TM4C123GH6PM_BITS_H_ */
