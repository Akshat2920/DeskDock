#include "ui.h"
#include "ipc_communication.h"

#define MAX_STORED_WIFI_SSIDS               (64U)

#define CY_WCM_SECURITY_OPEN                    0 
#define CY_WCM_SECURITY_WEP_PSK                 1
#define CY_WCM_SECURITY_WEP_SHARED              32769
#define CY_WCM_SECURITY_WPA_TKIP_PSK            2097154
#define CY_WCM_SECURITY_WPA_AES_PSK             2097156
#define CY_WCM_SECURITY_WPA_MIXED_PSK           2097158
#define CY_WCM_SECURITY_WPA2_AES_PSK            4194308
#define CY_WCM_SECURITY_WPA2_TKIP_PSK           4194306
#define CY_WCM_SECURITY_WPA2_MIXED_PSK          4194310
#define CY_WCM_SECURITY_WPA2_FBT_PSK            1077936132
#define CY_WCM_SECURITY_WPA3_SAE                16777220
#define CY_WCM_SECURITY_WPA3_WPA2_PSK           20971524
#define CY_WCM_SECURITY_IBSS_OPEN               536870912
#define CY_WCM_SECURITY_WPS_SECURE              268435460
#define CY_WCM_SECURITY_UNKNOWN                 4294967295
#define CY_WCM_SECURITY_WPA2_WPA_AES_PSK        6291460
#define CY_WCM_SECURITY_WPA2_WPA_MIXED_PSK      6291462
#define CY_WCM_SECURITY_WPA_TKIP_ENT            35651586
#define CY_WCM_SECURITY_WPA_AES_ENT             35651588
#define CY_WCM_SECURITY_WPA_MIXED_ENT           35651590
#define CY_WCM_SECURITY_WPA2_TKIP_ENT           37748738
#define CY_WCM_SECURITY_WPA2_AES_ENT            37748740
#define CY_WCM_SECURITY_WPA2_MIXED_ENT          37748742
#define CY_WCM_SECURITY_WPA2_FBT_ENT            1111490564

#define SECURITY_OPEN                        "OPEN"
#define SECURITY_WEP_PSK                     "WEP-PSK"
#define SECURITY_WEP_SHARED                  "WEP-SHARED"
#define SECURITY_WEP_TKIP_PSK                "WEP-TKIP-PSK"
#define SECURITY_WPA_TKIP_PSK                "WPA-TKIP-PSK"
#define SECURITY_WPA_AES_PSK                 "WPA-AES-PSK"
#define SECURITY_WPA_MIXED_PSK               "WPA-MIXED-PSK"
#define SECURITY_WPA2_AES_PSK                "WPA2-AES-PSK"
#define SECURITY_WPA2_TKIP_PSK               "WPA2-TKIP-PSK"
#define SECURITY_WPA2_MIXED_PSK              "WPA2-MIXED-PSK"
#define SECURITY_WPA2_FBT_PSK                "WPA2-FBT-PSK"
#define SECURITY_WPA3_SAE                    "WPA3-SAE"
#define SECURITY_WPA2_WPA_AES_PSK            "WPA2-WPA-AES-PSK"
#define SECURITY_WPA2_WPA_MIXED_PSK          "WPA2-WPA-MIXED-PSK"
#define SECURITY_WPA3_WPA2_PSK               "WPA3-WPA2-PSK"
#define SECURITY_WPA_TKIP_ENT                "WPA-TKIP-ENT"
#define SECURITY_WPA_AES_ENT                 "WPA-AES-ENT"
#define SECURITY_WPA_MIXED_ENT               "WPA-MIXED-ENT"
#define SECURITY_WPA2_TKIP_ENT               "WPA2-TKIP-ENT"
#define SECURITY_WPA2_AES_ENT                "WPA2-AES-ENT"
#define SECURITY_WPA2_MIXED_ENT              "WPA2-MIXED-ENT"
#define SECURITY_WPA2_FBT_ENT                "WPA2-FBT-ENT"
#define SECURITY_IBSS_OPEN                   "IBSS-OPEN"
#define SECURITY_WPS_SECURE                  "WPS-SECURE"
#define SECURITY_UNKNOWN                     "UNKNOWN"

typedef enum{
    X = 1,
    O = 2
} buttons;

typedef enum{
    youTube = 1,
    discord = 2,
    spotify = 3,
    terminal = 4,
    fileExplorer = 5,
    settings = 6,
    netflix = 7,
    custom_1 = 8,
    custom_2 = 9,
    custom_3 = 10
} applications;

typedef struct
{
    char ssid[sizeof(((wifi_credentials_t *)0)->ssid)];
    uint32_t security;
    bool in_use;
} wifi_ssid_security_entry_t;
extern wifi_ssid_security_entry_t wifi_ssid_security_table[MAX_STORED_WIFI_SSIDS];

void initialState();
extern void buttonPressed_X(lv_event_t * e);
extern void buttonPressed_O(lv_event_t * e);
void createWifiList(char * ssid, uint32_t ind);
void store_wifi_security_for_ssid(wifi_credentials_t *wifi_scan_result);
void clear_wifi_ssid_security_table(void);
void print_wifi_ssid_security_table(void);
void setDefaultStatus();
void connectWifi(lv_event_t *e);
void disconnectWifi(lv_event_t *e);
void enablePassword();
void disablePassword();
void enableButton();
void disableButton();
void updateWifiCredential(lv_event_t *e);