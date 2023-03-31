#ifndef _HOYOVERSE_H_
#define _HOYOVERSE_H_

#include <ArduinoJSON.h>
#include <MD5Builder.h>
#include <esp_http_client.h>
#include <esp_crt_bundle.h>

struct Notedata
{
    int respCode;
    String respMsg;
    int resinRemain = 160;
    int resinMax = 160;
    time_t resinRecoverTime = 0;
    int homecoinRemain = 2400;
    int homecoinMax = 2400;
    time_t homecoinRecoverTime = 0;
    int expeditionOngoing = 5;
    int expeditionFinished = 5;
    int expeditionMax = 5;
    time_t expeditionRecoverTime[5] = {0, 0, 0, 0, 0};
    bool hasTransformer = false;
    time_t transformerRecoverTime = 0;
    time_t _last_calc_time = 0;
    time_t _last_update_time = 0;
};

typedef enum
{
    HOYO_CLI_HTTP_OPEN_FAIL = -6,
    HOYO_CLI_HTTP_READ_FAIL,
    HOYO_CLI_JSON_DESER_FAIL,
    HOYO_CLI_RESP_ERR,
    HOYO_CLI_OUT_OF_MEM,
    HOYO_CLI_CONFIG_ERR = 0,
    HOYO_CLI_OK = 1
} HoyoverseClient_result_t;

class HoyoverseClient
{
public:
    HoyoverseClient();
    ~HoyoverseClient();

    void begin(const char *cookie, const char *uid);

    HoyoverseClient_result_t syncDailyNote(Notedata *data); // Sync resin data from server
    static void updateDailyNote(Notedata *data);            // Calculate resin locally

    String getCookie();
    String getUid();
    void setCookie(const char *guid);
    void setUid(const char *guid);
    String getDeviceGuid();
    void setDeviceGuid(const char *guid);
    static String generateGuid();

private:
    String _uid;
    String _cookie;
    String _device_guid;

    static uint8_t getForumType(const char *uid);
    static const char *getServer(const char *uid);

    String getDynamicSalt(const char *body = "", const char *param = "");

    static String genGuid4Byte();
};

#endif