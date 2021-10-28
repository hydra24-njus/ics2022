#include <am.h>
#include <nemu.h>

static uint32_t bootime_hi,bootime_lo;
void __am_timer_init() {
  bootime_hi=inl(RTC_ADDR+4);
  bootime_lo=inl(RTC_ADDR);
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = (inl(RTC_ADDR+4)-bootime_hi)*1000000+(inl(RTC_ADDR)-bootime_lo)/2;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
