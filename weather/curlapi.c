#include "curlapi.h"

#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"
#include "asciiarttable.h"

//当天天气链接
char *wearurlhead = "http://api.k780.com/?app=weather.today&weaid=";
char *wearurltail = "&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json";

//生活指标
char *indexhead = "http://api.k780.com/?app=weather.lifeindex&weaid=";
char *indextail = "&&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json";

//天气预报
char *forcasthead = "http://api.k780.com/?app=weather.future&weaid=1";
char *forcasttail = "&&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json";

char *WearUrl(char *id,const char *urlhead, const char *urltail){
    char *res = malloc(strlen(urlhead)+strlen(id)+strlen(urltail));
    sprintf(res,"%s%s%s",urlhead,id,urltail);
    return res;
    //printf("%s", res);
}

size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp)
 {
    strcat( (char*)userp, (char*)ptr);
    return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何.
 }

CURLcode curl_get_req(const char *url, char *response)
{
    // init curl
    CURL *curl = curl_easy_init();
    // res code
    CURLcode res;
    struct curl_slist *head = NULL;
    head = curl_slist_append(head, "Content-Type:application/x-www-form-urlencoded;charset=UTF-8");

    if (curl)
    {
        // set params

        curl_easy_setopt(curl, CURLOPT_URL, url); // url
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, head);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // if want to use https
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); // set peer and host verify false
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        //curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl,CURLOPT_ENCODING,"");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30); // set transport and time out time
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
        // start req
        res = curl_easy_perform(curl);
    }
    // release curl
    curl_easy_cleanup(curl);
    return res;

}

char *getJson(const char *url)
{
    char * buf = (char *)malloc(1024*1000);
    memset(buf,0,1024*1000);
    curl_get_req(url,buf);
    //printf("%s\n", buf);
    return buf;
    //printf("%s\n", weather_city);
    //getchar();
}

char *getWeaid(const char *url,const char *city)
{
    char *json = getJson(url);
    cJSON *root = cJSON_Parse(json);
    cJSON *result = cJSON_GetObjectItem(root,"result");
    cJSON *data = cJSON_GetObjectItem(result,"1");
    cJSON *p,*s;
    p = data;
    while(p){
        char *cityname  = cJSON_GetObjectItem(p,"citynm")->valuestring;
        char  *weatid = cJSON_GetObjectItem(p,"weaid")->valuestring;
        if(!strcmp(cityname,city))
            return weatid;
        //printf("Weatid: %s,city: %s \n",weatid,cityname);
        s = p;
        p = p->next;
    }
}

char *getCity(const char *url, const char *Weaid)
{
    char *json = getJson(url);
    cJSON *root = cJSON_Parse(json);
    cJSON *result = cJSON_GetObjectItem(root,"result");
    cJSON *data = cJSON_GetObjectItem(result,"1");
    cJSON *p,*s;
    p = data;
    while(p){
        char *cityname  = cJSON_GetObjectItem(p,"citynm")->valuestring;
        char  *weatid = cJSON_GetObjectItem(p,"weaid")->valuestring;
        if(!strcmp(weatid,Weaid))
            return cityname;
        //printf("Weatid: %s,city: %s \n",weatid,cityname);
        s = p;
        p = p->next;
    }
}




void getWearData(const char *wearid,char *weardata[5])
{
    char *url = WearUrl(wearid,wearurlhead,wearurltail);
    //printf("%s",url);
    char *json = getJson(url);

    cJSON *root = cJSON_Parse(json);
    cJSON *result = cJSON_GetObjectItem(root,"result");
    cJSON *weather = cJSON_GetObjectItem(result,"weather");
    cJSON *temperature = cJSON_GetObjectItem(result,"temperature");
    cJSON *wind = cJSON_GetObjectItem(result,"wind");
    cJSON *winp = cJSON_GetObjectItem(result,"winp");
    cJSON *temperature_curr = cJSON_GetObjectItem(result,"temperature_curr");

    weardata[0] = weather->valuestring;
    weardata[1] = temperature->valuestring;
    weardata[2] = temperature_curr->valuestring;
    weardata[3] = wind->valuestring;
    weardata[4] = winp->valuestring;

    //printf("%s",data->valuestring);
}


void getLifeIndex(const char *wearid, char *index[18])
{
    char *url = WearUrl(wearid,indexhead,indextail);
    //printf("%s",url);
    char *json = getJson(url);

    cJSON *root = cJSON_Parse(json);
    cJSON *result = cJSON_GetObjectItem(root,"result");
    cJSON *s,*p;
    p = result->child;
    int i=0;
    int k=0;
    while(p &&i<3){
        //printf("日期 %s\n",p->string);
        cJSON *lifeindex_uv_typenm = cJSON_GetObjectItem(p,"lifeindex_uv_attr");
        cJSON *lifeindex_gm_attr = cJSON_GetObjectItem(p,"lifeindex_gm_attr");
        cJSON *lifeindex_ct_dese = cJSON_GetObjectItem(p,"lifeindex_ct_dese");
        cJSON *lifeindex_yd_dese = cJSON_GetObjectItem(p,"lifeindex_yd_dese");
        cJSON *lifeindex_kq_dese = cJSON_GetObjectItem(p,"lifeindex_kq_dese");
        index[0+k] = p->string;
        index[1+k] = lifeindex_uv_typenm->valuestring;
        index[2+k] = lifeindex_gm_attr->valuestring;
        index[3+k] = lifeindex_ct_dese->valuestring;
        index[4+k] = lifeindex_yd_dese->valuestring;
        index[5+k] = lifeindex_kq_dese->valuestring;
//        printf("紫外线 %s\n",lifeindex_uv_typenm->valuestring);
//        printf("感冒 %s\n",lifeindex_gm_attr->valuestring);
//        printf("穿衣 %s\n",lifeindex_ct_dese->valuestring);
//        printf("运动 %s\n",lifeindex_yd_typenm->valuestring);
//        printf("空气污染 %s\n\n",lifeindex_kq_dese->valuestring);
        s = p;
        p = p->next;
        i++;
        k+=6;
    }

}



void getForcast(const char *wearid, char *focast[32])
{
    char *url = WearUrl(wearid,forcasthead,forcasttail);
    //printf("%s",url);
    char *json = getJson(url);
    cJSON *root = cJSON_Parse(json);
    cJSON *result = cJSON_GetObjectItem(root,"result");

    cJSON *s,*p;
    p = result->child;
    int i=0;
    int k=0;
    while(p &&i<3){
        //printf("日期 %s\n",p->string);
        cJSON *temperature = cJSON_GetObjectItem(p,"temperature");
        cJSON *humidity = cJSON_GetObjectItem(p,"humidity");
        cJSON *weather = cJSON_GetObjectItem(p,"weather");
        cJSON *wind = cJSON_GetObjectItem(p,"wind");
        cJSON *winp = cJSON_GetObjectItem(p,"winp");
        focast[0+k] = " ";
        focast[1+k] = temperature->valuestring;
        focast[2+k] = humidity->valuestring;
        focast[3+k] = weather->valuestring;
        focast[4+k] = wind->valuestring;
        focast[5+k] = winp->valuestring;
//        printf("温差 %s\n",temperature->valuestring);
//        printf("湿度 %s\n",humidity->valuestring);
//        printf("天气 %s\n",weather->valuestring);
//        printf("风向 %s\n",wind->valuestring);
//        printf("风力 %s\n\n",winp->valuestring);
        s = p;
        p = p->next;
        i++;
        k+=6;
    }
}


cJSON *dofile(char *filename)
{
    FILE *f;
    long len;
    char *data;
    cJSON *json, *ret;

    f = fopen(filename, "rb");
    if (f == NULL) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    data = (char*)malloc(len + 1);
    fread(data, 1, len, f);
    data[len] = '\0';
    json = cJSON_Parse(data);
    if (!json)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        ret = NULL;
        free(data);
        fclose(f);
        return ret;
    }
    else
    {
        //printf("%s\n",data);
        ret = json;
    }

    free(data);
    fclose(f);
    return ret;
}

char *getcityName(const char *cityId)
{
    cJSON *A = dofile("city.json");
    cJSON *result = cJSON_GetObjectItem(A, "result");
    cJSON *id = cJSON_GetObjectItem(result, cityId);
    cJSON *citynm = cJSON_GetObjectItem(id, "cityno");
    return citynm->valuestring;
    //printf("%s", citynm->valuestring);
}
int getcityid(const char *cityname)
{
    cJSON *A = dofile("city.json");
    cJSON *result = cJSON_GetObjectItem(A, "result");
    cJSON *s,*p;
    p = result->child;
    while(p){
        cJSON *citynm = cJSON_GetObjectItem(p,"cityno");
        cJSON *cityid = cJSON_GetObjectItem(p,"weaid");
        if(!strcmp(citynm->valuestring,cityname))
            return strtol(cityid->valuestring,NULL,10);
        s = p;
        p = p->next;
    }
    return -1;
}

int getWeatid(const char *wearid)
{
    char *url = WearUrl(wearid,wearurlhead,wearurltail);
    //printf("%s",url);
    char *json = getJson(url);

    cJSON *root = cJSON_Parse(json);
    cJSON *result = cJSON_GetObjectItem(root,"result");
    cJSON *weatid = cJSON_GetObjectItem(result,"weatid");
    int id = strtol(weatid->valuestring,NULL,10);
    //printf("%d",id);
    return id;
}

int getWearIcoId(const char *wearid)
{
    int id = getWeatid(wearid);

    switch (id) {
    case 1:
        return WEATHER_SUNNY;break;
    case 2:
        return WEATHER_CLOUDY;break;
    case 3:
        return WEATHER_OVERCAST;break;
    case 4:
        return WEATHER_SHOWERRAIN;break;
    case 5:
        return WEATHER_THUNDERSHOWER;break;
    case 6:
        return WEATHER_THUNDERSHOWERHAILY;break;
    case 7:
        return WEATHER_RAINSNOW;break;
    case 8:
        return WEATHER_LIGHTRAIN;break;
    case 9:
        return WEATHER_MODERATERAIN;break;
    case 10:
        return WEATHER_HEAVYRAIN;break;
    case 11:
        return WEATHER_RAINSTORM;break;
    case 12:
        return WEATHER_BIGRAINSTORM;break;
    case 13:
        return WEATHER_SUPERRAINSTORM;break;
    case 14:
        return WEATHER_SNOWSHOWER;break;
    case 15:
        return WEATHER_LIGHTSNOW;break;
    case 16:
        return WEATHER_MODERATESNOW;break;
    case 17:
        return WEATHER_HEAVYSNOW;break;
    case 18:
        return WEATHER_SNOWSTORM;break;
    case 19:
        return WEATHER_FOG;break;
    case 20:
        return WEATHER_ICERAIN;break;
    case 21:
        return WEATHER_SANDSTORM;break;
    case 22:
        return WEATHER_LIGHTTOMODERATERAIN;break;
    case 23:
        return WEATHER_MODERARETOBIGRAIN;break;
    case 24:
        return WEATHER_BIGTOSTORMRAIN;break;
    case 25:
        return WEATHER_STORMTOSUPERRAIN;break;
    case 26:
        return WEATHER_STORMTOMOSTRAIN;break;
    case 27:
        return WEATHER_LIGHTTOMODERATESNOW;break;
    case 28:
        return WEATHER_MODERATETOBIG;break;
    case 29:
        return WEATHER_BIGTOSTORMSNOW;break;
    case 30:
        return WEATHER_DRIFTSNOW;break;
    case 31:
        return WEATHER_DRIFTSNOW;break;
    case 32:
        return WEATHER_DRIFTSNOW;break;
    case 33:
        return WEATHER_DRIFTSNOW;break;
    default:
        break;
    }
}


