/**
 * @file Platform_Types.h
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief  general type definitions
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H


/*
 * CPU register type width
 */
#define CPU_TYPE_8                  (8U)
#define CPU_TYPE_16                 (16U)
#define CPU_TYPE_32                 (32U)

/*
 * Bit order definition
 */
#define MSB_FIRST                   (0u)        /* Big endian bit ordering        */
#define LSB_FIRST                   (1u)        /* Little endian bit ordering     */

/*
 * Byte order definition
 */
#define HIGH_BYTE_FIRST             (0u)        /* Big endian byte ordering       */
#define LOW_BYTE_FIRST              (1u)        /* Little endian byte ordering    */

/*
 * Platform type and endianess definitions, specific for ARM Cortex-M4F
 */
#define CPU_TYPE                CPU_TYPE_32

#define CPU_BIT_ORDER           LSB_FIRST
#define CPU_BYTE_ORDER          LOW_BYTE_FIRST

/*
 * Boolean Values
 */
#ifndef FALSE
#define FALSE                   (0u)
#endif

#ifndef TRUE
#define TRUE                    (1u)
#endif

typedef unsigned char           boolean;    /*           0 .. 255             */

typedef unsigned char           uint8;      /*           0 .. 255             */
typedef signed char             sint8;      /*        -128 .. +127            */
typedef unsigned short          uint16;     /*           0 .. 65535           */
typedef signed short            sint16;     /*      -32768 .. +32767          */
typedef unsigned long           uint32;     /*           0 .. 4294967295      */
typedef signed long             sint32;     /* -2147483648 .. +2147483647     */
typedef unsigned long long      uint64;     /*       0..18446744073709551615  */
typedef signed long long        sint64;     /* -9223372036854775808..9223372036854775807 */

typedef float                   float32;    /* 1.2E-38 .. 3.4E+38            */
typedef double                  float64;    /* 2.3E-308 .. 1.7E+308          */




#endif /* PLATFORM_TYPES_H */
