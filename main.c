#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#define GREEN() SetConsoleTextAttribute(\
	GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define OS_SLEEP(ms) Sleep(ms)
#define width() \
	CONSOLE_SCREEN_BUFFER_INFO csbi; \
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), \
		&csbi); \
	j = csbi.srWindow.Right - csbi.srWindow.Left
#else
#include <unistd.h>
#include <sys/ioctl.h>
#define GREEN() fputs("\e[32m", stdout)
#define OS_SLEEP(ms) usleep(ms * 1000)
#define width() \
	struct winsize w; \
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); \
	j = w.ws_col
#endif

#define assert(condition, msg) if(!condition) { puts(msg); return 1; }

int main(int argc, char **argv)
{
	char str[2000]; //buffer
	srand(time(0));
	GREEN();
	int j;
	while(1)
	{
		width();
		assert(j, "width = 0");
		for(int i = 0; i < j; i++)
			str[i] = rand() % 10 + 0x30;
		str[j] = '\0';
		puts(str);
		OS_SLEEP(SLEEP);
	}
}
