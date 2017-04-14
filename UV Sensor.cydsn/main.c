/*******************************************************************************
NOW TRING TO IMPLEMENT THE WATCHDOG
*
********************************************************************************


/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  This is source code for the PSoC 4 BLE dynamic broadcaster example project.
*
* Note:
*
* Owner:
*  KRIS@CYPRESS.COM
*
* Related Document:
*
* Hardware Dependency:
*  1. PSoC 4 BLE device
*  2. CY8CKIT-042 BLE Pioneer Kit
*
* Code Tested With:
*  1. PSoC Creator 3.1 SP1
*  2. ARM GCC 4.8.4
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include <stdlib.h>
#include <Project.h>

/***************************************
*        API Constants
***************************************/
#define LED_ON                                      (0u)
#define LED_OFF                                     (1u)

/***************************************
*       ADC constants
***************************************/
#define ADC_VREF_MASK               (0x000000F0Lu)
#define ADC_CHANNEL         (0x00u)

/***************************************
* Extern and constants required for 
* dynamic ADV payload update
***************************************/
#define ENABLE_DYNAMIC_ADV                          (1u)

#if ENABLE_DYNAMIC_ADV
    
extern CYBLE_GAPP_DISC_MODE_INFO_T cyBle_discoveryModeInfo;
    
/* ADV payload dta structure */    
#define advPayload                                  (cyBle_discoveryModeInfo.advData->advData) 
    
#define OUT0                (23u) /* index of the dynamic data in the ADV packet */
#define OUT1                (24u) /* index of the dynamic data in the ADV packet */
#define LOOP_DELAY                                  (1u)  /* How often would you like to update the ADV payload */
    
#define MIN_PAYLOAD_VALUE                           (0u)
#define MAX_PAYLOAD_VALUE                           (200u)
    
#endif

/***************************************
*        Function Prototypes
***************************************/
void InitializeSystem(void);
void StackEventHandler(uint32 event, void* eventParam);
void EnterLowPowerMode(void);
void DynamicADVPayloadUpdate(void);
void ReadUVSensor(void);

/***************************************
*        Global variables
***************************************/
uint16 count = 0;
uint8 dynamicPayload = MIN_PAYLOAD_VALUE;

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{
    /* Setup the system initially */
    InitializeSystem();
     ADC_Start();
   
    char test_string[] = "\n\rHello World\n\r";
    UART_1_UartPutString(test_string); // print test_string
    /* Three simple APIs that showcases dynamic ADV payload update */ 
    while(1) 
    { 
        
     

        CyDelay(252);  
        ReadUVSensor();
  
        /* Single API call to service all the BLE stack events. Must be
         * called at least once in a BLE connection interval */
        CyBle_ProcessEvents();

        /* Configure the system in lowest possible power modes during and between BLE ADV events */
        EnterLowPowerMode();
        
        /* 
           LOW_POWER_NOTE - If you like to measure the current consumed by this project, following changes are to be 
           done to achieve lowest possible current number:
           1. Set the "Debug Select" option under Dynamic Broadcaster.cydwr -> System -> Programming/Debugging to GPIO 
           2. Comment out Advertising_LED_Write(LED_ON); line of code in StackEventHandler routine
        */

    }
}

/*******************************************************************************
* Function Name: InitializeSystem
********************************************************************************
*
* Summary:
*  This routine initializes all the componnets and firmware state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void InitializeSystem(void)
{
    CYBLE_API_RESULT_T apiResult;

    CyGlobalIntEnable;
    /* Service Solicitation data */
    cyBle_discoveryData.advData[3] = 0x03;      /* Length */
    cyBle_discoveryData.advData[4] = 0x03;      /* Complete List of Service UUIDs */
    cyBle_discoveryData.advData[5] = 0xAA;      /* LSB - Eddystone service */
    cyBle_discoveryData.advData[6] = 0xFE;      /* MSB - Eddystone service */
    
    /* Service Data */
        cyBle_discoveryData.advData[7] = 0x17;      /* Length */
        cyBle_discoveryData.advData[8] = 0x16;      /* Service Data */
        cyBle_discoveryData.advData[9] = 0xAA;      /* LSB - Eddystone Service */
        cyBle_discoveryData.advData[10] = 0xFE;     /* MSB - Eddystone Service */

        cyBle_discoveryData.advData[11] = 0x00;     /* Signifies Eddystone UID */

        cyBle_discoveryData.advData[12] = 0xF2;     /* Ranging data: -14dB*/

        /* SHA-1 hash of the FQDN (bless this mess!) is calculated and its 
         * first 10 bytes are placed here as the Namespace ID, MSB first.
         */
        cyBle_discoveryData.advData[13] = 0x6B;     /* NID[0] */
        cyBle_discoveryData.advData[14] = 0xE6;     /* NID[1] */
        cyBle_discoveryData.advData[15] = 0x10;     /* NID[2] */
        cyBle_discoveryData.advData[16] = 0xD6;     /* NID[3] */
        cyBle_discoveryData.advData[17] = 0x1B;     /* NID[4] */
        cyBle_discoveryData.advData[18] = 0xCA;     /* NID[5] */
        cyBle_discoveryData.advData[19] = 0x0B;     /* NID[6] */
        cyBle_discoveryData.advData[20] = 0x2F;     /* NID[7] */
        cyBle_discoveryData.advData[21] = 0x9D;     /* NID[8] */
        cyBle_discoveryData.advData[22] = 0xDF;     /* NID[9] */

        /* Instance ID - randomly created */
        cyBle_discoveryData.advData[23] = 0x77;     /* BID[0] */
        cyBle_discoveryData.advData[24] = 0x66;     /* BID[1] */
        cyBle_discoveryData.advData[25] = 0x00;     /* BID[2] */
        cyBle_discoveryData.advData[26] = 0x00;     /* BID[3] */
        cyBle_discoveryData.advData[27] = 0x00;     /* BID[4] */
        cyBle_discoveryData.advData[28] = 0x00;     /* BID[5] */
        
        cyBle_discoveryData.advData[29] = 0x00;     /* Reserved */
        cyBle_discoveryData.advData[30] = 0x00;     /* Reserved */
        
        /* ADV packet length */
        cyBle_discoveryData.advDataLen = 31;
    
    
    

    apiResult = CyBle_Start(StackEventHandler); /* Init the BLE stack and register an applicaiton callback */

    if(apiResult != CYBLE_ERROR_OK)
    {
        /* BLE stack initialization failed, check your configuration */
        CYASSERT(0);
    }
    
    /* Set XTAL divider to 3MHz mode */
    CySysClkWriteEcoDiv(CY_SYS_CLK_ECO_DIV8); 
    
    /* ILO is no longer required, shut it down */
    CySysClkIloStop();
    
    
    UART_1_Start();
    
    
    
    
    
}

/*******************************************************************************
* Function Name: EnterLowPowerMode
********************************************************************************
*
* Summary:
*  This configures the BLESS and system in low power mode whenever possible.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EnterLowPowerMode(void)
{
    CYBLE_BLESS_STATE_T blessState;
    uint8 intrStatus;
    
    /* Configure BLESS in Deep-Sleep mode */
    CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
    
    /* Prevent interrupts while entering system low power modes */
    intrStatus = CyEnterCriticalSection();
    
    /* Get the current state of BLESS block */
    blessState = CyBle_GetBleSsState();
    
    /* If BLESS is in Deep-Sleep mode or the XTAL oscillator is turning on, 
     * then PSoC 4 BLE can enter Deep-Sleep mode (1.3uA current consumption) */
    if(blessState == CYBLE_BLESS_STATE_ECO_ON || 
        blessState == CYBLE_BLESS_STATE_DEEPSLEEP)
    {
        CySysPmDeepSleep();
    }
    else if(blessState != CYBLE_BLESS_STATE_EVENT_CLOSE)
    {
        /* If BLESS is active, then configure PSoC 4 BLE system in 
         * Sleep mode (~1.6mA current consumption) */
        CySysClkWriteHfclkDirect(CY_SYS_CLK_HFCLK_ECO);
        CySysClkImoStop();
        CySysPmSleep();
        CySysClkImoStart();
        CySysClkWriteHfclkDirect(CY_SYS_CLK_HFCLK_IMO);
    }
    else
    {
        /* Keep trying to enter either Sleep or Deep-Sleep mode */    
    }
    
    CyExitCriticalSection(intrStatus);
}
   
/*******************************************************************************
* Function Name: DynamicADVPayloadUpdate
********************************************************************************
*
* Summary:
*  This routine dynamically updates the BLE advertisement packet
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DynamicADVPayloadUpdate(void)
{
    if(CyBle_GetBleSsState() == CYBLE_BLESS_STATE_EVENT_CLOSE)
    {
        count++; /* Loop counter */
        
        /* Once the system enters Sleep/Deepsleep mode during advertisement, the source of wake-up is the next  
         * advertisement interval which has a wakeup interval of 1 advertisement (ADV) interval (100ms). 
         * LOOP_DELAY * ADV interval is the interval after which ADV data is updated in this firmware.*/
        
        if(count >= LOOP_DELAY)
        {
            /* Dynamic payload will be continuously updated */
            advPayload[OUT0] = dynamicPayload++;
            
            //advPayload[OUT0] = readValue;
            
            if(dynamicPayload == MAX_PAYLOAD_VALUE)
            {
                dynamicPayload = MIN_PAYLOAD_VALUE;
            }
            
            count = 0;
            
            CyBle_GapUpdateAdvData(cyBle_discoveryModeInfo.advData, cyBle_discoveryModeInfo.scanRspData);
        }
    }
}

/*******************************************************************************
* Function Name: StackEventHandler
********************************************************************************
*
* Summary:
*  This is an event callback function to receive events from the BLE Component.
*
* Parameters:
*  uint8 event:       Event from the CYBLE component
*  void* eventParams: A structure instance for corresponding event type. The
*                     list of event structure is described in the component
*                     datasheet.
*
* Return:
*  None
*
*******************************************************************************/
void StackEventHandler(uint32 event, void *eventParam)
{
    switch(event)
    {
        /* Mandatory events to be handled by Find Me Target design */
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            /* Start BLE advertisement for 30 seconds and update link
             * status on LEDs */
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            Advertising_LED_Write(LED_ON);
          break;

        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
            {
                /* Advertisement event timed out, go to low power
                 * mode (Hibernate mode) and wait for an external
                 * user event to wake up the device again */
                Advertising_LED_Write(LED_OFF);
                Hibernate_LED_Write(LED_ON);
                Wakeup_SW_ClearInterrupt();
                Wakeup_Interrupt_ClearPending();
                Wakeup_Interrupt_Start();
                CySysPmHibernate();
            }
            break;

        default:
        break;
    }
}

/*******************************************************************************
* Function Name: ReadUVSensor()
********************************************************************************
*
* Summary:
*   This function measures the adc value
*
*******************************************************************************/
void ReadUVSensor(void)
{
	int16 adcResult;
    int16 temp;
	uint32 sarControlReg;
    char str[5];
    int8 scoop;
    int8 froop;

    //batteryTimer = BATTERY_TIMEOUT;
        
    	/* Set the reference to VBG and enable reference bypass */
    	sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
    	ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_INTERNAL1024BYPASSED;
    	
    	/* 25 ms delay for reference capacitor to charge */
    	CyDelay(25);             
    	
    	/* Set the reference to VDD and disable reference bypass */
    	sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
    	ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_VDDA;

    	/* Perform a measurement. Store this value in Vref. */
    	CyDelay(1);
    	ADC_StartConvert();
        
    	ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);

        adcResult = ADC_GetResult16(ADC_CHANNEL);
        //temp = adcResult/8;
        temp = adcResult;
        
        
        
        //scoop = ((temp - 0.99) * (15.0 - 0) / (2.8 - 0.99)) + 0;
        scoop = temp;
        froop = temp >> 8 ;
        
    //    itoa(adcResult, str, 10);
        //itoa(scoop, str, 10);
   //     UART_1_UartPutString(str);
  //      CyDelay(5);  
  //      UART_1_UartPutChar('\n');
  //      CyDelay(5);  
  //      UART_1_UartPutChar('\r');
  //      CyDelay(5);  
        
        
        
        advPayload[OUT1] = scoop;
        //advPayload[OUT0] = (scoop)&(0x000F);
        advPayload[OUT0] = froop;
        CyBle_GapUpdateAdvData(cyBle_discoveryModeInfo.advData, cyBle_discoveryModeInfo.scanRspData);
        
        
}
/* [] END OF FILE */
