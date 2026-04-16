/*******************************************************************************
 *                              INCLUDES
 ******************************************************************************/
#include "cm33_ipc_receive.h"
#include "ipc_communication.h"
#include <stdint.h>

/*******************************************************************************
 *                              CONSTANTS
 ******************************************************************************/
#define UI_RX_TASK_NAME                       ("UIRxTask")

/* stack size in words */
#define UI_RX_TASK_STACK_SIZE                   (2 * 1024)
#define UI_RX_TASK_PRIORITY                     (3)
#define UI_RX_QUEUE_LENGTH                      20U   

/*******************************************************************************
 *                              GLOBAL VARIABLES
 ******************************************************************************/
/* Task handler for communication with the UI_RX task */
TaskHandle_t cm33_ui_rx_task_handle = NULL;
QueueHandle_t xUiRxQueue = NULL;
extern ipc_msg_t *ipc_recv_msg;

/****************************************************************************
 *                              FUNCTION DECLARATIONS
 ***************************************************************************/
static void cm33_ipc_receive_task(void *arg);

static void cm33_ipc_receive_task(void *arg)
{
    (void)arg;
    ipc_msg_t received_msg;
    
    for(;;)
    {
        /* Wait indefinitely for messages from the CM33 */
        printf("\nIPC receive task waiting for messages...\r\n");
        if(xQueueReceive(xUiRxQueue, &received_msg, portMAX_DELAY) == pdPASS)
        {
            /* Process the received message */
            printf("\n[CM33 IPC] Received message with cmd: %lu\r\n", (unsigned long)received_msg.cmd);
            switch (received_msg.cmd)
            {
                case REFRESH_WIFI:
                    xTaskNotify(scan_task_handle, 0, eNoAction);
                    scanned = false;
                    break;
                default:
                    // Handle other message types or ignore
                    break;
            }
        }
       // CyDelay(100);
    }
}

void cm33_start_ipc_receive_task()
{
    xUiRxQueue = xQueueCreate(UI_RX_QUEUE_LENGTH, sizeof(ipc_msg_t));
    if (NULL == xUiRxQueue)
    {
        return;
    }

    /* Create the IPC receive task */
    BaseType_t result = xTaskCreate(cm33_ipc_receive_task, UI_RX_TASK_NAME, UI_RX_TASK_STACK_SIZE, NULL, UI_RX_TASK_PRIORITY, &cm33_ui_rx_task_handle);
    if (result != pdPASS)
    {
        // Handle task creation failure (e.g., log error, retry, etc.)
    }
}