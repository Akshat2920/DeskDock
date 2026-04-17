/*******************************************************************************
 *                              INCLUDES
 ******************************************************************************/
#include "ipc_receive.h"
#include "ipc_communication.h"
#include "lvgl.h"
#include <stdint.h>

/*******************************************************************************
 *                              CONSTANTS
 ******************************************************************************/
#define UI_RX_TASK_NAME                       ("UIRxTask")

/* stack size in words */
#define UI_RX_TASK_STACK_SIZE                   (1 * 1024)
#define UI_RX_TASK_PRIORITY                     (configMAX_PRIORITIES - 1)
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
static void ipc_receive_task(void *arg);

static void ipc_receive_task(void *arg)
{
    (void)arg;
    ipc_msg_t received_msg;
    extern volatile bool graphics_ready;
    
    /* Wait until graphics task is fully initialized before processing messages */
    while (!graphics_ready)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    printf("IPC receive task ready\r\n");
    
    for(;;)
    {
        /* Wait indefinitely for messages from the CM33 */
        if(xQueueReceive(xUiRxQueue, &received_msg, portMAX_DELAY) == pdPASS)
        {
            /* Process the received message */
            switch (received_msg.cmd)
            {
                case WIFI_SCAN_LIST:
                    store_wifi_security_for_ssid(&received_msg.wifi_scan_result);
                    lv_lock();
                    createWifiList(received_msg.wifi_scan_result.ssid, received_msg.msg);
                    lv_unlock();
                    break;
                case SCAN_COMPLETE:
                    lv_lock();
                    lv_obj_add_flag(ui_wifiRefresh, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_remove_flag(ui_wifiConnect, LV_OBJ_FLAG_HIDDEN);
                    lv_unlock();
                    //print_wifi_ssid_security_table();

                    break;
                default:
                    // Handle other message types or ignore
                    break;
            }
        }
    }
}

void start_ipc_receive_task()
{
    xUiRxQueue = xQueueCreate(UI_RX_QUEUE_LENGTH, sizeof(ipc_msg_t));
    if (NULL == xUiRxQueue)
    {
        return;
    }

    /* Create the IPC receive task */
    BaseType_t result = xTaskCreate(ipc_receive_task, UI_RX_TASK_NAME, UI_RX_TASK_STACK_SIZE, NULL, UI_RX_TASK_PRIORITY, &cm33_ui_rx_task_handle);
    if (result != pdPASS)
    {
        // Handle task creation failure (e.g., log error, retry, etc.)
    }
}