enum cm33_cm55_cmd{
    WIFI_SCAN_LIST = 0,
    REFRESH_WIFI,
    SCAN_COMPLETE,
    CONNECT_WIFI,
    DISCONNECT_WIFI
};

typedef struct {
    char ssid[33];
    char password[65];
    uint32_t security;
} wifi_credentials_t;

typedef enum  {
    CONNECTED=0,
    NOT_CONNECTED
} connect_status;

typedef struct {
    connect_status WiFi;
    connect_status Client;
}connection_state_t;