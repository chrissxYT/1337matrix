#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#define green() SetConsoleTextAttribute(\
	GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define os_sleep(ms) Sleep(ms)
#define width() \
	CONSOLE_SCREEN_BUFFER_INFO csbi; \
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), \
		&csbi); \
	unsigned int j = csbi.srWindow.Right - csbi.srWindow.Left
#else
#include <unistd.h>
#include <sys/ioctl.h>
#define green() fputs("\e[32m", stdout)
#define os_sleep(ms) usleep(ms * 1000)
#define width() \
	struct winsize w; \
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); \
	unsigned short j = w.ws_col
#endif

#define assert(condition, msg) if(!condition) { puts(msg); return 1; }

int main(int argc, char **argv)
{
        long sleep = SLEEP;
        if(argc > 1) sleep = strtol(argv[1], NULL, 10);
	srand(time(0));
	green();
	while(1)
	{
		width();
		assert(j, "width = 0");
		for(int i = 0; i < j; i++) putchar(rand()%10 | 0x30);
		putchar('\n');
		os_sleep(sleep);
	}
}
