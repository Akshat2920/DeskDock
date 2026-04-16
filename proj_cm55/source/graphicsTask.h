#if defined(MTB_DISPLAY_WS7P0DSI_RPI)
#include "mtb_disp_ws7p0dsi_drv.h"
#elif defined(MTB_DISPLAY_EK79007AD3)
#include "mtb_display_ek79007ad3.h"
#elif defined(MTB_DISPLAY_W4P3INCH_RPI)
#include "mtb_disp_dsi_waveshare_4p3.h"
#endif

#include "retarget_io_init.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "demos/lv_demos.h"
#include "display_i2c_config.h"

#include "vg_lite.h"
#include "vg_lite_platform.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lvgl.h"
#include "ipc_receive.h"
#include "ui.h"

extern TaskHandle_t rtos_cm55_gfx_task_handle;
BaseType_t createGraphicsTask(void);
