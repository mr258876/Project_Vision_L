#ifndef _HOYOVERSE_CONST_H_
#define _HOYOVERSE_CONST_H_

const PROGMEM char *Hoyoverse_hosts[] = {"https://api-takumi.mihoyo.com/", "https://api-os-takumi.mihoyo.com/"};
const PROGMEM char *Hoyoverse_hosts_record[] = {"https://api-takumi-record.mihoyo.com/", "https://bbs-api-os.mihoyo.com/"};
const PROGMEM char *Hoyoverse_salt[] = {"xV8v4Qu54lUKrEYFZkJhB8cuOh9Asafs", "okr4obncj8bw5a65hbnn5oo6ixjc3l9w"};

const PROGMEM char *Hoyoverse_App_version[] = {"2.63.1", "2.49.0"};
const PROGMEM char *Hoyoverse_App_UA[] = {
    "Mozilla/5.0 (Linux; Android 14; GO3Z5 Build/AP1A.240405.002) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.5672.136 Mobile Safari/537.36 miHoYoBBS/2.63.1",
    "Mozilla/5.0 (Linux; Android 14; GO3Z5 Build/AP1A.240405.002) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.5672.136 Mobile Safari/537.36 miHoYoBBSOversea/2.49.0"};
const PROGMEM char *Hoyoverse_App_client_type[] = {"5", "2"};
const PROGMEM char *Hoyoverse_App_origin[] = {
    "https://webstatic.mihoyo.com",
    "https://webstatic-sea.hoyolab.com"};
const PROGMEM char *Hoyoverse_App_x_requested_with[] = {
    "com.mihoyo.hyperion",
    "com.mihoyo.hoyolab"};
const PROGMEM char *Hoyoverse_App_referer[] = {
    "https://webstatic.mihoyo.com",
    "https://webstatic-sea.hoyolab.com"};

// shared
const PROGMEM char *Hoyoverse_App_rpc_sys_version = "14";
const PROGMEM char *Hoyoverse_App_rpc_device_model = "GO3Z5";
const PROGMEM char *Hoyoverse_App_rpc_device_name = "Pixel 7";

// Miyoushe ONLY
const PROGMEM char *Hoyoverse_App_rpc_page[] = {"v4.2.2-ys_#/ys/daily"};
const PROGMEM char *Hoyoverse_App_rpc_tool_version[] = {"v4.2.2"};
const PROGMEM char *Hoyoverse_App_rpc_verify_key[] = {"bll8iq97cem8"};
const PROGMEM char *Hoyoverse_App_rpc_channel[] = {"miyousheluodi"};
const PROGMEM char *Hoyoverse_App_sec_fetch_site[] = {"same-site"};
const PROGMEM char *Hoyoverse_App_sec_fetch_mode[] = {"cors"};
const PROGMEM char *Hoyoverse_App_sec_fetch_dest[] = {"empty"};

#endif