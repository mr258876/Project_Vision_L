#ifndef _HOYOVERSE_CONST_H_
#define _HOYOVERSE_CONST_H_

const PROGMEM char *Hoyoverse_hosts[] = {"https://api-takumi.mihoyo.com/", "https://api-os-takumi.mihoyo.com/"};
const PROGMEM char *Hoyoverse_hosts_record[] = {"https://api-takumi-record.mihoyo.com/", "https://bbs-api-os.mihoyo.com/"};
const PROGMEM char *Hoyoverse_salt[] = {"xV8v4Qu54lUKrEYFZkJhB8cuOh9Asafs", "okr4obncj8bw5a65hbnn5oo6ixjc3l9w"};

const PROGMEM char *Hoyoverse_App_version[] = {"2.38.1", "2.9.0"};
const PROGMEM char *Hoyoverse_App_UA[] = {
    "Mozilla/5.0 (FreeRTOS; The Vision L; Espressif ESP32) AppleWebKit/605.1.15 (KHTML, like Gecko) miHoYoBBS/2.40.1",
    "Mozilla/5.0 (FreeRTOS; The Vision L; Espressif ESP32) AppleWebKit/605.1.15 (KHTML, like Gecko) miHoYoBBSOversea/2.22.0"};
const PROGMEM char *Hoyoverse_App_client_type[] = {"5", "2"};
const PROGMEM char *Hoyoverse_App_origin[] = {
    "https://webstatic.mihoyo.com",
    "https://webstatic-sea.hoyolab.com"};
const PROGMEM char *Hoyoverse_App_x_requested_with[] = {
    "com.mihoyo.hyperion",
    "com.mihoyo.hoyolab"};
const PROGMEM char *Hoyoverse_App_referer[] = {
    "https://webstatic.mihoyo.com/bbs/event/signin-ys/index.html?bbs_auth_required=true&act_id=e202009291139501&utm_source=bbs&utm_medium=mys&utm_campaign=icon",
    "https://webstatic-sea.hoyolab.com"};

#endif