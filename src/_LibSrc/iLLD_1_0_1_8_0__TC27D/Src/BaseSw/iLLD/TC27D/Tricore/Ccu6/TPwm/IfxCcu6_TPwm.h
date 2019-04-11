/**
 * \file IfxCcu6_TPwm.h
 * \brief CCU6 TPWM details
 * \ingroup IfxLld_Ccu6
 *
 * \version iLLD_1_0_1_8_0
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * \defgroup IfxLld_Ccu6_TPwm_Usage How to use the CCU6 TPWM Interface driver?
 * \ingroup IfxLld_Ccu6_TPwm
 *
 * The TPWM interface driver provides a default CCU6 configuration for PWM modulation output through the selected timer block.
 *
 * User can select the various configuration options that hardware allows
 *
 * In the following sections it will be described, how to integrate the driver into the application framework.
 *
 *
 * \section IfxLld_Ccu6_TPwm_Preparation Preparation
 *
 *
 * \subsection IfxLld_Ccu6_TPwm_Include Include Files
 *
 * Include following header file into your C code:
 * \code
 *     #include <Ccu6/TPwm/IfxCcu6_TPwm.h>
 * \endcode
 *
 * \subsection IfxLld_Ccu6_TPwm_Variables Variables
 *
 * Declare the TPWM handle as global variable in your C code:
 *
 * \code
 *     // used globally
 *     static IfxCcu6_TPwm tPwm;
 * \endcode
 *
 * \subsection IfxLld_Ccu6_TPwm_Interrupt Interrupt Handler Installation
 *
 * See also \ref IfxLld_Cpu_Irq_Usage
 *
 * Define priority for the Interrrupt handler. This is normally done in the Ifx_IntPrioDef.h file:
 * \code
 *     // priorities are normally defined in Ifx_IntPrioDef.h
 *     #define IFX_INTPRIO_CCU6 1
 * \endcode
 *
 * Add the interrupt service routine to your C code.
 * \code
 *     IFX_INTERRUPT(ccu60ISR_TPwm, 0, IFX_INTPRIO_CCU6)
 *     {
 *         //user code
 *     }
 * \endcode
 *
 * Finally install the interrupt handlers in your initialisation function:
 * \code
 *     // install interrupt handlers
 *     IfxCpu_Irq_installInterruptHandler(&ccu60ISR_TPwm, IFX_INTPRIO_CCU6);
 *     IfxCpu_enableInterrupts();
 * \endcode
 *
 * \subsection IfxLld_Ccu6_TPwm_Init Module Initialisation
 *
 * The module initialisation can be done in the same function. Here an example:
 * \code
 *     // create configuration
 *     IfxCcu6_TPwm_Config tPwmConfig;
 *     IfxCcu6_TPwm_initModuleConfig(&tPwmConfig, &MODULE_CCU60);
 *
 *     // configure the frequency of the timer in case of internal start
 *     // this frequency will be set for the timer block selected later
 *     tPwmConfig.base.frequency = 400000;
 *
 *     // configure the period of the timer
 *     tPwmConfig.base.period = 100;
 *
 *     // configure the waiting time in case of delayed T13 start in sync with T12
 *     tPwmConfig.base.waitingTime = 20;
 *
 *     // select the active state of the output
 *     tPwmConfig.base.activeState = Ifx_ActiveState_high;
 *
 *     // select the timer through which PWM is to be generated
 *     tPwmConfig.timer = IfxCcu6_TimerId_t13;
 *
 *     // configure the clock for internal mode
 *     tPwmConfig.clock.t13ExtClockEnabled   = FALSE;
 *     tPwmConfig.clock.t13ExtClockInput     = NULL_PTR;
 *     tPwmConfig.clock.t13countingInputMode = IfxCcu6_CountingInputMode_internal;
 *
 *     // configure the selcted timer block
 *     tPwmConfig.timer13.counterValue     = 0;
 *     tPwmConfig.timer13.compareValue     = 100;
 *     // configure the syncronisation, in case of sync start with T12
 *     tPwmConfig.timer13.t12SyncEvent     = IfxCcu6_T13TriggerEvent_onCC60RCompare;
 *     tPwmConfig.timer13.t12SyncDirection = IfxCcu6_T13TriggerDirection_onT12CountingUp;
 *
 *     //select the channel out for modulation
 *     tPwmConfig.channelOut = IfxCcu6_ChannelOut_cout3;
 *
 *     // pin configuration
 *     const IfxCcu6_TPwm_Pins pins = {
 *         NULL,	// CC60Out pin not used
 *         NULL,	// CC61Out pin not used
 *         NULL,	// CC62Out pin not used
 *         NULL,	// COUT60 pin not used
 *         NULL,	// COUT61 pin not used
 *         NULL,	// COUT62 pin not used
 *         IfxCcu60_COUT63_P00_0_OUT,	// COUT63 pin
 *         IfxPort_OutputMode_pushPull,
 *         IfxPort_PadDriver_cmosAutomotiveSpeed1
 *     };
 *     tPwmConfig.pins = &pins;
 *
 *     // configure the interrupts
 *     tPwmConfig.interrupt1.interruptSource = IfxCcu6_InterruptSource_t13CompareMatch;
 *     tPwmConfig.interrupt1.serviceRequest  = IfxCcu6_ServiceRequest_2;
 *     tPwmConfig.interrupt1.priority        = IFX_INTPRIO_CCU6;
 *     tPwmConfig.interrupt1.typeOfService   = IfxSrc_Tos_cpu0;
 *
 *     // configure input and output triggers
 *     tPwmConfig.trigger.t12ExtInputTrigger   = IfxCcu60_T12HRB_P00_7_IN;
 *     tPwmConfig.trigger.t13ExtInputTrigger   = NULL_PTR;
 *     tPwmConfig.trigger.extInputTriggerMode  = IfxCcu6_ExternalTriggerMode_risingEdge;
 *     tPwmConfig.trigger.t13InSyncWithT12     = TRUE;
 *
 *     tPwmConfig.trigger.outputTriggerEnabled = TRUE;
 *     tPwmConfig.trigger.outputLine           = IfxCcu6_TrigOut_0;
 *     tPwmConfig.trigger.outputTrigger      = IfxCcu6_TrigSel_cout63;
 *
 *
 *     // initialize the module
 *     IfxCcu6_TPwm_initModule(&tPwm, &tPwmConfig);
 * \endcode
 *
 *
 * The TPWM is ready for use now!
 *
 *
 * \section IfxLld_Ccu6_TPwm_ModulationControl Modulation Control
 *
 *
 * The TPWM driver provides simple to use Modulation Control functions
 *
 * This means: you can start, stop, pause and resume the modulation once the module is initialised with the appropriate configuration
 *
 * Start the modulation
 * \code
 *     IfxCcu6_TPwm_start(&tPwm);
 * \endcode
 *
 * Stop the modulation
 * \code
 *     IfxCcu6_TPwm_stop(&tPwm);
 * \endcode
 *
 * Pause the modulation
 * \code
 *     IfxCcu6_TPwm_pause(&tPwm);
 * \endcode
 *
 * Resume the modulation
 * \code
 *     IfxCcu6_TPwm_resume(&tPwm);
 * \endcode
 *
 * \defgroup IfxLld_Ccu6_TPwm TPWM Interface driver
 * \ingroup IfxLld_Ccu6
 * \defgroup IfxLld_Ccu6_TPwm_DataStructures Data Structures
 * \ingroup IfxLld_Ccu6_TPwm
 * \defgroup IfxLld_Ccu6_TPwm_Module_Initialize_Functions Module Initialize Functions
 * \ingroup IfxLld_Ccu6_TPwm
 * \defgroup IfxLld_Ccu6_TPwm_Modultion_Control_Functions Modultion Control Functions
 * \ingroup IfxLld_Ccu6_TPwm
 */

#ifndef IFXCCU6_TPWM_H
#define IFXCCU6_TPWM_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "Ccu6/Std/IfxCcu6.h"
#include "If/Ccu6If/TPwm.h"

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Ccu6_TPwm_DataStructures
 * \{ */
/** \brief Structure for clock configuration
 */
typedef struct
{
    boolean                   t12ExtClockEnabled;         /**< \brief Timer 12 external clock enable / disable selection */
    IfxCcu6_T12hr_In         *t12ExtClockInput;           /**< \brief External input signal selection for timer 12 */
    IfxCcu6_CountingInputMode t12countingInputMode;       /**< \brief Input event leading to a counting action of the timer T12 */
    boolean                   t13ExtClockEnabled;         /**< \brief Timer 13 external clock enable / disable selection */
    IfxCcu6_T13hr_In         *t13ExtClockInput;           /**< \brief External input signal selection for timer 13 */
    IfxCcu6_CountingInputMode t13countingInputMode;       /**< \brief Input event leading to a counting action of the timer T13 */
} IfxCcu6_TPwm_Clock;

/** \brief Structure for interrupt configuration
 */
typedef struct
{
    IfxCcu6_InterruptSource source;               /**< \brief Interrupt source selection */
    IfxCcu6_ServiceRequest  serviceRequest;       /**< \brief Selection of service request outputs */
    uint16                  priority;             /**< \brief Interrupt priority */
    IfxSrc_Tos              typeOfService;        /**< \brief type of interrupt service */
} IfxCcu6_TPwm_InterruptConfig;

/** \brief Structure for CCU6 output pin configuration
 */
typedef struct
{
    IFX_CONST IfxCcu6_Cc60_Out   *cc60Out;              /**< \brief CC60 compare output CC0 */
    IFX_CONST IfxCcu6_Cc61_Out   *cc61Out;              /**< \brief CC61 compare output CC1 */
    IFX_CONST IfxCcu6_Cc62_Out   *cc62Out;              /**< \brief CC62 compare output CC2 */
    IFX_CONST IfxCcu6_Cout60_Out *cout60;               /**< \brief CC60 compare output COUT0 */
    IFX_CONST IfxCcu6_Cout61_Out *cout61;               /**< \brief CC61 compare output COUT1 */
    IFX_CONST IfxCcu6_Cout62_Out *cout62;               /**< \brief CC62 compare output COUT2 */
    IFX_CONST IfxCcu6_Cout63_Out *cout63;               /**< \brief CC63 compare output COUT3 */
    IfxPort_OutputMode            outputMode;           /**< \brief The pin output mode which should be configured */
    IfxPort_PadDriver             pinDriver;            /**< \brief pad driver */
    IFX_CONST IfxCcu6_T12hr_In   *t12hr;                /**< \brief T12HR input signal */
    IFX_CONST IfxCcu6_T13hr_In   *t13hr;                /**< \brief T13HR input signal */
    IfxPort_InputMode             t1xhrInputMode;       /**< \brief The T1xHR pin input mode which should be configured */
} IfxCcu6_TPwm_Pins;

/** \brief Structure for Timer 12
 */
typedef struct
{
    IfxCcu6_TimerInputClock clockInput;          /**< \brief Input clock selection (prescaler) */
    IfxCcu6_T12Channel      channelId;           /**< \brief Capture compare channel of the Timer12 */
    IfxCcu6_T12ChannelMode  channelMode;         /**< \brief The operating mode for the T12 channel */
    IfxCcu6_T12CountMode    countMode;           /**< \brief Operating mode of Timer 12 */
    uint16                  counterValue;        /**< \brief 16-bit counter value of Timer12 */
    uint8                   deadTimeValue;       /**< \brief Value of the dead time to be induced */
    uint16                  compareValue;        /**< \brief 16-bit comapre value of Timer12 */
} IfxCcu6_TPwm_Timer12;

/** \brief Structure for Timer 13
 */
typedef struct
{
    IfxCcu6_TimerInputClock     clockInput;             /**< \brief Input clock selection (prescaler) */
    uint16                      counterValue;           /**< \brief 16-bit counter value of Timer13 */
    uint16                      compareValue;           /**< \brief 16-bit comapre value of Timer12 */
    IfxCcu6_T13TriggerEvent     t12SyncEvent;           /**< \brief T12 sync trigger event to start T13 */
    IfxCcu6_T13TriggerDirection t12SyncDirection;       /**< \brief Additional information to control trigger event selection */
} IfxCcu6_TPwm_Timer13;

/** \brief Configuration structure for external triggers
 */
typedef struct
{
    IfxCcu6_T12hr_In           *t12ExtInputTrigger;         /**< \brief External trigger input signal selection to start the timer 12 */
    IfxCcu6_T13hr_In           *t13ExtInputTrigger;         /**< \brief External trigger input signal selection to start the timer 13 */
    IfxCcu6_ExternalTriggerMode extInputTriggerMode;        /**< \brief Event of signal T1xHR that can set the run bit T1xR by HW */
    boolean                     t13InSyncWithT12;           /**< \brief Selection of Timer 13 start in sync with T12 */
    boolean                     outputTriggerEnabled;       /**< \brief Output trigger connection to VADC enable / disable choice */
    IfxCcu6_TrigOut             outputLine;                 /**< \brief Trigger out selection */
    IfxCcu6_TrigSel             outputTrigger;              /**< \brief Output Trigger selection */
} IfxCcu6_TPwm_TriggerConfig;

/** \} */

/** \addtogroup IfxLld_Ccu6_TPwm_DataStructures
 * \{ */
/** \brief Module handle
 */
typedef struct
{
    TPwm                       base;             /**< \brief Base TPWM object */
    Ifx_CCU6                  *ccu6;             /**< \brief Pointer to the base of CCU6 registers */
    IfxCcu6_TimerId            timer;            /**< \brief Timer number (T12 / T13) */
    IfxCcu6_ChannelOut         channelOut;       /**< \brief Capture compare output pin selection */
    IfxCcu6_TPwm_TriggerConfig trigger;          /**< \brief Structure for trigger configuration */
} IfxCcu6_TPwm;

/** \brief Configuration structure of the module
 */
typedef struct
{
    TPwm_Config                  base;             /**< \brief Base configuration */
    Ifx_CCU6                    *ccu6;             /**< \brief Pointer to the base of CCU6 registers */
    IfxCcu6_TimerId              timer;            /**< \brief Timer number (T12 / T13) */
    IfxCcu6_TPwm_Clock           clock;            /**< \brief Structure for clock configuration */
    IfxCcu6_TPwm_Timer12         timer12;          /**< \brief Structure for Timer 12 */
    IfxCcu6_TPwm_Timer13         timer13;          /**< \brief Structure for Timer 13 */
    IfxCcu6_ChannelOut           channelOut;       /**< \brief Capture compare output pin selection */
    IfxCcu6_TPwm_Pins           *pins;             /**< \brief Structure for CCU6 output pin configuration */
    IfxCcu6_TPwm_InterruptConfig interrupt1;       /**< \brief Structure for first interrupt configuration */
    IfxCcu6_TPwm_InterruptConfig interrupt2;       /**< \brief Structure for second interrupt configuration */
    IfxCcu6_TPwm_InterruptConfig interrupt3;       /**< \brief Structure for third interrupt configuration */
    IfxCcu6_TPwm_InterruptConfig interrupt4;       /**< \brief Structure for fourth interrupt configuration */
    IfxCcu6_TPwm_TriggerConfig   trigger;          /**< \brief Structure for trigger configuration */
} IfxCcu6_TPwm_Config;

/** \} */

/** \addtogroup IfxLld_Ccu6_TPwm_Module_Initialize_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Fills the config structure with default values
 * \param config Configuration structure of the module
 * \param ccu6 Pointer to the base of CCU6 registers
 * \return None
 *
 * A coding example can be found in \ref IfxLld_Ccu6_TPwm_Usage
 *
 */
IFX_EXTERN void IfxCcu6_TPwm_initModuleConfig(IfxCcu6_TPwm_Config *config, Ifx_CCU6 *ccu6);

/** \} */

/** \addtogroup IfxLld_Ccu6_TPwm_Modultion_Control_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Initialises the module with default configuration
 * \param tPwm Module handle
 * \param config Configuration structure of the module
 * \return None
 *
 * A coding example can be found in \ref IfxLld_Ccu6_TPwm_Usage
 *
 */
IFX_EXTERN void IfxCcu6_TPwm_initModule(IfxCcu6_TPwm *tPwm, const IfxCcu6_TPwm_Config *config);

/** \brief Pauses the triggered PWM
 * \param tPwm Module handle
 * \return None
 *
 * A coding example can be found in \ref IfxLld_Ccu6_TPwm_Usage
 *
 */
IFX_EXTERN void IfxCcu6_TPwm_pause(IfxCcu6_TPwm *tPwm);

/** \brief Resumes the triggered PWM
 * \param tPwm Module handle
 * \return None
 *
 * A coding example can be found in \ref IfxLld_Ccu6_TPwm_Usage
 *
 */
IFX_EXTERN void IfxCcu6_TPwm_resume(IfxCcu6_TPwm *tPwm);

/** \brief Starts the triggered PWM
 * \param tPwm Module handle
 * \return None
 *
 * A coding example can be found in \ref IfxLld_Ccu6_TPwm_Usage
 *
 */
IFX_EXTERN void IfxCcu6_TPwm_start(IfxCcu6_TPwm *tPwm);

/** \brief Stops the triggered PWM
 * \param tPwm Module handle
 * \return None
 *
 * A coding example can be found in \ref IfxLld_Ccu6_TPwm_Usage
 *
 */
IFX_EXTERN void IfxCcu6_TPwm_stop(IfxCcu6_TPwm *tPwm);

/** \} */

#endif /* IFXCCU6_TPWM_H */
