/**
 * @file    Compiler.h
 * @author Ahmed Moahmed (ahmed.moahmed.eng.25@gmail.com)
 * @brief This file contains the definitions and macros specified by
 *          AUTOSAR for the abstraction of compiler specific keywords.
 * 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef COMPILER_H
#define COMPILER_H

/* Id for the company in the AUTOSAR (for example our ID = 1000 :) */
#define COMPILER_VENDOR_ID                                  (1000U)

/* The memory class is used for the declaration of local pointers */
#define AUTOMATIC

/* The memory class is used within type definitions, where no memory qualifier can be specified */
#define TYPEDEF

/* This is used to define the void pointer to zero definition */
#define NULL_PTR                                            ((void *)0)

/* This is used to define the abstraction of compiler keyword inline */
#define INLINE                                              inline

/* This is used to define the local inline function */
#define LOCAL_INLINE                                        static inline

/* This is used to define the abstraction of compiler keyword static */
#define STATIC                                              static

#endif
