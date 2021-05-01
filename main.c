#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "config.h"

#ifdef _WIN32
#include <Windows.h>
#define green() SetConsoleTextAttribute(\
        GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define width(output) \
        CONSOLE_SCREEN_BUFFER_INFO csbi; \
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), \
                &csbi); \
        output = csbi.srWindow.Right - csbi.srWindow.Left
typedef SHORT width_t;
#else
#include <unistd.h>
#include <sys/ioctl.h>
#define green() fputs("\x1b[32m", stdout)
#define Sleep(ms) usleep(ms * 1000)
#define width(output) \
        struct winsize w; \
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); \
        output = w.ws_col
typedef unsigned short width_t;
#endif

int main(int argc, char **argv) {
        long sleep = SLEEP;
        width_t i, j;
        if(argc > 1) sleep = strtol(argv[1], NULL, 10);
        srand(time(0));
        green();
        while(1) {
                width(j);
                if(!j) puts("width = 0"), exit(1);
                for(i = 0; i < j; i++) putchar('0' + rand() % 10);
                putchar('\n');
                Sleep(sleep);
        }
}
