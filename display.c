#include <errno.h>
#include <stdio.h>
#include <time.h>

void clear_term() { printf("\033[H\033[J"); }

void pretty_print(int val) {
  int color_code = (val % 7) + 31;
  printf("\033[1;%dm%1d\033[0m", color_code, val);
}

void sleep_mili(long t) {
  struct timespec ts;
  int res;

  ts.tv_sec = t / 1000;
  ts.tv_nsec = (t % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);
}
