/*******************************************************************************
 *                              INCLUDES
 *******************************************************************************/
#include "cybsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cyabs_rtos.h"
#include "cyabs_rtos_impl.h"
#include "ipc_communication.h"
#include "wifiTask.h"

/*******************************************************************************
 *                              GLOBAL VARIABLES
 *******************************************************************************/
extern QueueHandle_t xUiRxQueue;
extern TaskHandle_t cm55_ui_rx_task_handle;
extern bool scanned;
/*******************************************************************************
 *                              FUNCTION PROTOTYPES
 *******************************************************************************/
/**
 * @brief Initializes and starts the UI receiver thread.
 *
 * This function creates the FreeRTOS task responsible for handling events and
 * messages for the user interface.
 */
void cm33_start_ipc_receive_task();
 