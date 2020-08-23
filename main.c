#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"

#ifdef _WIN32
#include <Windows.h>
#define green() SetConsoleTextAttribute(\
	GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define ms_sleep(ms) Sleep(ms)
#define width(output) \
	CONSOLE_SCREEN_BUFFER_INFO csbi; \
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), \
		&csbi); \
	output = csbi.srWindow.Right - csbi.srWindow.Left
#define WIDTH_TYPE SHORT
#else
#include <unistd.h>
#ifndef usleep
/* this is a workaround for glibc's unistd.h (it is way too stupid) */
extern int usleep (__useconds_t);
#endif
#include <sys/ioctl.h>
#define green() fputs("\x1b[32m", stdout)
#define ms_sleep(ms) usleep(ms * 1000)
#define width(output) \
	struct winsize w; \
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); \
	output = w.ws_col
#define WIDTH_TYPE unsigned short
#endif

int main(int argc, char **argv)
{
        long sleep = SLEEP;
        if(argc > 1) sleep = strtol(argv[1], NULL, 10);
	srand(time(0));
	green();
	while(1)
	{
                WIDTH_TYPE i, j;
		width(j);
                if(!j) puts("width = 0"), exit(1);
		for(i = 0; i < j; i++) putchar(rand() % 10 | 0x30);
		putchar('\n');
		ms_sleep(sleep);
	}
}
