/*#include <rtc.h>

DS1302 rtc;

void rtc_setup()
{
    Wire.begin();
    rtc.begin();

    if (! rtc.isrunning()) {
        Serial.println("RTC is NOT running!");

        rtc.adjust(DateTime(__DATE__, __TIME__));
    }
}

void rtc_read()
{
    now = rtc.now();
}*/