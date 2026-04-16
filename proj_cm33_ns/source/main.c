/*******************************************************************************
* File Name        : main.c
*
* Description      : This source file contains the main routine for non-secure
*                    application running on CM33 CPU.
*
* Related Document : See README.md
* 
********************************************************************************
 * (c) 2025-2026, Infineon Technologies AG, or an affiliate of Infineon
 * Technologies AG. All rights reserved.
 * This software, associated documentation and materials ("Software") is
 * owned by Infineon Technologies AG or one of its affiliates ("Infineon")
 * and is protected by and subject to worldwide patent protection, worldwide
 * copyright laws, and international treaty provisions. Therefore, you may use
 * this Software only as provided in the license agreement accompanying the
 * software package from which you obtained this Software. If no license
 * agreement applies, then any use, reproduction, modification, translation, or
 * compilation of this Software is prohibited without the express written
 * permission of Infineon.
 *
 * Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
 * IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
 * THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
 * SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
 * Infineon reserves the right to make changes to the Software without notice.
 * You are responsible for properly designing, programming, and testing the
 * functionality and safety of your intended application of the Software, as
 * well as complying with any legal requirements related to its use. Infineon
 * does not guarantee that the Software will be free from intrusion, data theft
 * or loss, or other breaches ("Security Breaches"), and Infineon shall have
 * no liability arising out of any Security Breaches. Unless otherwise
 * explicitly approved by Infineon, the Software may not be used in any
 * application where a failure of the Product or any consequences of the use
 * thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cybsp.h"
#include "retarget_io_init.h"
#include "cm33_ipc_receive.h"

/*******************************************************************************
* Macros
*******************************************************************************/
/* The timeout value in microseconds used to wait for CM55 core to be booted */
#define CM55_BOOT_WAIT_TIME_USEC            (10U)
#define CM33_APP_DELAY_MS                   (50U)

/* App boot address for CM55 project */
#define CM55_APP_BOOT_ADDR          (CYMEM_CM33_0_m55_nvm_START + \
                                        CYBSP_MCUBOOT_HEADER_SIZE)

volatile uint8_t msg_cmd;
ipc_msg_t *ipc_recv_msg;
/*******************************************************************************
* Function Name: cm33_msg_callback
********************************************************************************
* Summary:
*  Callback function called when endpoint-1 (CM33) has received a message
*
* Parameters:
*  msg_data: Message data received throuig IPC
*
* Return :
*  void
*
*******************************************************************************/
void cm33_msg_callback(uint32_t * msg_data)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    printf("\n[CM33] IPC callback triggered\r\n");
    if ((msg_data != NULL))
    {
        ipc_recv_msg = (ipc_msg_t *) msg_data;
        (void)xQueueSendFromISR(xUiRxQueue, ipc_recv_msg, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function of the CM33 non-secure application.
*
* It initializes the device and board peripherals. Post that the
* CM55 core is enabled and then the programs enters to deepsleep.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    cy_en_ipc_pipe_status_t pipeStatus;
    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board initialization failed. Stop program execution */
    if (CY_RSLT_SUCCESS != result)
    {
        /* Disable all interrupts. */
        __disable_irq();

        CY_ASSERT(0);

        /* Infinite loop */
        while(true);
    }

    /* Enable global interrupts */
    __enable_irq();
    init_retarget_io();
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "PSOC Edge MCU: Stream Dock "
           "****************** \r\n\n");
    
    cm33_ipc_communication_setup();
    Cy_SysLib_Delay(CM33_APP_DELAY_MS);
    pipeStatus = Cy_IPC_Pipe_RegisterCallback(CM33_IPC_PIPE_EP_ADDR, &cm33_msg_callback,
                                          (uint32_t)CM33_IPC_PIPE_CLIENT_ID);
    if(CY_IPC_PIPE_SUCCESS != pipeStatus)
    {
        printf("[ERROR] : cm33 Callback register failed");
    }
    Cy_SysEnableCM55(MXCM55, CY_CM55_APP_BOOT_ADDR, CM55_BOOT_WAIT_TIME_USEC);
    Cy_SysLib_Delay(CM33_APP_DELAY_MS);
    /* Put the CPU to Deep Sleep */
    result =xTaskCreate(scan_task, "Scan task", SCAN_TASK_STACK_SIZE, NULL, 
                                        SCAN_TASK_PRIORITY, &scan_task_handle);
    cm33_start_ipc_receive_task();
    if( pdPASS == result )
    {
        /* Start the RTOS Scheduler */
        vTaskStartScheduler();

        /* Should never get here. */
        handle_app_error();
    }
    else
    {
        handle_app_error();
    }
}


/* [] END OF FILE */
