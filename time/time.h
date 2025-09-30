#ifndef TIME_H
#define TIME_H

struct timeval {
        long tv_sec;
        long tv_usec;
};

void get_time(struct timeval *tp);

#endif
