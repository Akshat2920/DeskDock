enum cm33_cm55_cmd{
    WIFI_SCAN_LIST = 0,
    REFRESH_WIFI,
    SCAN_COMPLETE
};

typedef struct {
    char ssid[33];
    char password[65];
    uint32_t security;
} wifi_credentials_t;