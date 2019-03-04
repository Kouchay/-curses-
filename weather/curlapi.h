#ifndef CURLAPI_H
#define CURLAPI_H
#include <curl/curl.h>
#include "cJSON.h"
#include <stdlib.h>

//typedef struct wearthdata{
//    char *temperature_curr[16];
//    char *temperature[16];
//    char *weather_curr[16];
//    char *wind[16];
//    char *winp[16];
//}wear;



void T();

CURLcode curl_get_req(const char *url, char *response);

char *getJson(const char *url);

char *getWeaid(const char *url,const char *city);
char *getCity(const char *url, const char *Weaid);
void getWearData(const char *wearid, char *weardata[5]);
void getLifeIndex(const char *wearid,char *index[18]);
void getForcast(const char *wearid, char *focast[32]);
int getWeatid(const char *wearid);

int getcityid(const char *cityname);

int getWearIcoId(const char *wearid);
char *getcityName(const char *cityId);
#endif // CURLAPI_H
