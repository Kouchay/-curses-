#ifndef ASCIIARTTABLE_H
#define ASCIIARTTABLE_H

#define WEATHER_SUNNY               0//晴 1
#define WEATHER_CLOUDY              1//多云 2
#define WEATHER_OVERCAST            2//阴 3
#define WEATHER_SHOWERRAIN          3//阵雨 4
#define WEATHER_THUNDERSHOWER       4//雷阵雨 5
#define WEATHER_THUNDERSHOWERHAILY  5//雷阵雨有冰雹 6
#define WEATHER_RAINSNOW            6//雨夹雪 7
#define WEATHER_LIGHTRAIN           7//小雨 8
#define WEATHER_MODERATERAIN        8//中雨 9
#define WEATHER_HEAVYRAIN           9//大雨 10
#define WEATHER_RAINSTORM           10//暴雨 11
#define WEATHER_BIGRAINSTORM        10//大暴雨 12
#define WEATHER_SUPERRAINSTORM      10//特大暴雨 13
#define WEATHER_SNOWSHOWER          11//阵雪 14
#define WEATHER_LIGHTSNOW           12//小雪 15
#define WEATHER_MODERATESNOW        13//中雪 16
#define WEATHER_HEAVYSNOW           14//大雪 17
#define WEATHER_SNOWSTORM           15//暴雪 18
#define WEATHER_FOG                 16//雾 19
#define WEATHER_ICERAIN             17//冻雨 20
#define WEATHER_SANDSTORM           18 //沙尘暴 21
#define WEATHER_LIGHTTOMODERATERAIN 19//小雨-中雨 22
#define WEATHER_MODERARETOBIGRAIN   20//中雨-大雨 23
#define WEATHER_BIGTOSTORMRAIN      21//大雨-暴雨 24
#define WEATHER_STORMTOSUPERRAIN    22//暴雨-大暴雨 25
#define WEATHER_STORMTOMOSTRAIN     23//大暴雨-特大暴雨 26
#define WEATHER_LIGHTTOMODERATESNOW 24//小雪-中雪 27
#define WEATHER_MODERATETOBIG       25//中雪-大雪 28
#define WEATHER_BIGTOSTORMSNOW      26//大雪-暴雪 29
#define WEATHER_DRIFTSNOW           27//浮尘 扬沙 强沙尘暴 霾 30

extern const char *weather[][12];


#endif // ASCIIARTTABLE_H
