/*******************************************************************************
* File Name: Wakeup_SW.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Wakeup_SW_ALIASES_H) /* Pins Wakeup_SW_ALIASES_H */
#define CY_PINS_Wakeup_SW_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Wakeup_SW_0			(Wakeup_SW__0__PC)
#define Wakeup_SW_0_PS		(Wakeup_SW__0__PS)
#define Wakeup_SW_0_PC		(Wakeup_SW__0__PC)
#define Wakeup_SW_0_DR		(Wakeup_SW__0__DR)
#define Wakeup_SW_0_SHIFT	(Wakeup_SW__0__SHIFT)
#define Wakeup_SW_0_INTR	((uint16)((uint16)0x0003u << (Wakeup_SW__0__SHIFT*2u)))

#define Wakeup_SW_INTR_ALL	 ((uint16)(Wakeup_SW_0_INTR))


#endif /* End Pins Wakeup_SW_ALIASES_H */


/* [] END OF FILE */
