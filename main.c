#define SLEEP 100

#include <stdio.h>
#include <time.h>
#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64)
#define WIN 1
#include <Windows.h>
#define GREEN() SetConsoleTextAttribute(\
	GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define OS_SLEEP(ms) Sleep(ms)
inline int width()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left;
}
#else
#define WIN 0
#include <unistd.h>
#include <sys/ioctl.h>
#define GREEN() puts("\e[32m")
#define OS_SLEEP(ms) usleep(ms * 1000)
inline int width()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}
#endif

int main(int argc, char **argv)
{
	char *str = malloc(2000); //buffer
	if (!str) { puts("WTF, MALLOC FAILS"); return 1; }
	srand(time(0));
	GREEN();
	int j;
	while (1)
	{
		j = width();
		for (int i = 0; i < j; i++)
			str[i] = rand() % 10 + 48;
		str[j] = '\0';
		puts(str);
#if SLEEP
		OS_SLEEP(SLEEP);
#endif
	}
}