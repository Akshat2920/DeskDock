#include "dock.h"

wifi_ssid_security_entry_t wifi_ssid_security_table[MAX_STORED_WIFI_SSIDS];
buttons buttonPressed;
CY_SECTION_SHAREDMEM static ipc_msg_t cm55_msg;
static volatile bool cm55_ipc_tx_in_flight = false;
int idx = 0;

static void cm55_ipc_release_callback(void)
{
    cm55_ipc_tx_in_flight = false;
}

void setStateX_open(){
    buttonPressed = X;
    lv_obj_set_style_shadow_color(ui_apps, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_apps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_apps, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_apps, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_apps, lv_color_hex(0x47F6BF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_apps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_apps, lv_color_hex(0xBDFCE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_apps, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_apps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_apps, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_y(ui_buttonOverlay, -24);
    lv_obj_clear_flag(ui_appsContainer, LV_OBJ_FLAG_HIDDEN);
}

void setStateO_open(){
    buttonPressed = O;
    lv_obj_set_style_shadow_color(ui_edge, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_edge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_edge, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_edge, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_edge, lv_color_hex(0x47F6BF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_edge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_edge, lv_color_hex(0xBDFCE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_edge, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_edge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_edge, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_y(ui_buttonOverlay, 135);
    lv_obj_clear_flag(ui_edgeContainer, LV_OBJ_FLAG_HIDDEN);
}

void setStateX_closed(){
    lv_obj_set_style_shadow_opa(ui_apps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_apps, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_apps, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui_apps, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui_apps, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_apps, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_appsContainer, LV_OBJ_FLAG_HIDDEN);
}

void setStateO_closed(){
    lv_obj_set_style_shadow_opa(ui_edge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_edge, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_edge, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui_edge, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui_edge, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_edge, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_edgeContainer, LV_OBJ_FLAG_HIDDEN);
}

void buttonPressed_X(lv_event_t * e){
    if(buttonPressed != X){
        setStateX_open();
        setStateO_closed();
    }
}

void buttonPressed_O(lv_event_t * e){
    if(buttonPressed != O){
        setStateO_open();
        setStateX_closed();
    }
}

void initialState(){
    buttonPressed = X;
    setStateX_open();
    setStateO_closed();
}

void openYoutube(lv_event_t * e){
    // Code to open YouTube
}
void openDiscord(lv_event_t * e){
    // Code to open Discord
}
void openSpotify(lv_event_t * e){
    // Code to open Spotify
}
void openTerminal(lv_event_t * e){
    // Code to open Terminal
}
void openFiles(lv_event_t * e){
    // Code to open Files
}

void openSettings(lv_event_t * e){
    // Code to open Settings
}
void openNetflix(lv_event_t * e){
    // Code to open Netflix
}
void openCustom1(lv_event_t * e){
    // Code to open Custom-1
}
void openCustom2(lv_event_t * e){
    // Code to open Custom-2
}
void openCustom3(lv_event_t * e){
    // Code to open Custom-3
}
void refreshWifiList(lv_event_t *e){
    if (cm55_ipc_tx_in_flight)
    {
        printf("\n[CM55] IPC pipe busy, refresh request dropped\n");
        return;
    }
    lv_dropdown_clear_options(ui_wifiList);
    lv_dropdown_set_options(ui_wifiList, "Select Network");
    clear_wifi_ssid_security_table();
    cm55_msg.client_id = CM33_IPC_PIPE_CLIENT_ID;
    cm55_msg.intr_mask = CY_IPC_CYPIPE_INTR_MASK_EP2;
    cm55_msg.cmd = REFRESH_WIFI;

    cm55_ipc_tx_in_flight = true;

    lv_obj_add_flag(ui_wifiConnect, LV_OBJ_FLAG_HIDDEN);
    //lv_label_set_text(ui_wifiLabel, "Scanning for Wi-Fi...");
    lv_obj_remove_flag(ui_wifiRefresh, LV_OBJ_FLAG_HIDDEN);

    cy_en_ipc_pipe_status_t status = Cy_IPC_Pipe_SendMessage(CM33_IPC_PIPE_EP_ADDR,
                                                              CM55_IPC_PIPE_EP_ADDR,
                                                              &cm55_msg,
                                                              cm55_ipc_release_callback);
    if (CY_IPC_PIPE_SUCCESS != status)
    {
        cm55_ipc_tx_in_flight = false;
        printf("\n[CM55] IPC send failed: %d\n", (int)status);
    }
    else
    {
        printf("\n[CM55] IPC REFRESH_WIFI sent\n");
    }

    lv_dropdown_clear_options(ui_wifiList);
    lv_dropdown_add_option(ui_wifiList, "Select Network", 0);
}

void createWifiList(char * ssid, uint32_t ind){
    lv_dropdown_add_option(ui_wifiList, ssid, ind);
}

void store_wifi_security_for_ssid(wifi_credentials_t *wifi_scan_result)
{
    uint32_t index;
    size_t ssid_len;

    if (NULL == wifi_scan_result)
    {
        return;
    }

    ssid_len = strnlen(wifi_scan_result->ssid, sizeof(wifi_scan_result->ssid));
    if (ssid_len == 0U)
    {
        return;
    }
    if(idx >= MAX_STORED_WIFI_SSIDS){
        printf("\nMax stored Wi-Fi SSIDs reached. Cannot store more SSIDs.\n");
        return;
    }
    // for (index = 0U; index < MAX_STORED_WIFI_SSIDS; index++)
    // {
    //     if ((wifi_ssid_security_table[index].in_use == true) &&
    //         (0 == strcmp(wifi_ssid_security_table[index].ssid, wifi_scan_result->ssid)))
    //     {
    //         wifi_ssid_security_table[index].security = wifi_scan_result->security;
    //         return;
    //     }
    // }
    for (index = 0U; index < MAX_STORED_WIFI_SSIDS; index++)
    {
        if (wifi_ssid_security_table[index].in_use == false)
        {
            memcpy(wifi_ssid_security_table[index].ssid, wifi_scan_result->ssid, sizeof(wifi_ssid_security_table[index].ssid));
            wifi_ssid_security_table[index].ssid[sizeof(wifi_ssid_security_table[index].ssid) - 1U] = '\0';
            wifi_ssid_security_table[index].security = wifi_scan_result->security;
            wifi_ssid_security_table[index].in_use = true;
            return;
        }
    }
}

void clear_wifi_ssid_security_table(void)
{
    for (uint32_t index = 0U; index < MAX_STORED_WIFI_SSIDS; index++)
    {
        wifi_ssid_security_table[index].in_use = false;
        memset(wifi_ssid_security_table[index].ssid, 0, sizeof(wifi_ssid_security_table[index].ssid));
        wifi_ssid_security_table[index].security = 0U;
    }
}

void print_wifi_ssid_security_table(void)
{
    printf("\nStored Wi-Fi SSIDs and Security Types:\n");
    for (uint32_t index = 0U; index < MAX_STORED_WIFI_SSIDS; index++)
    {
        if (wifi_ssid_security_table[index].in_use)
        {
            printf("SSID: %s, Security: %u\n", wifi_ssid_security_table[index].ssid, wifi_ssid_security_table[index].security);
        }
    }
}