#include "ui.h"
#include "ipc_communication.h"

#define MAX_STORED_WIFI_SSIDS               (64U)

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