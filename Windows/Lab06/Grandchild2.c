#include <stdio.h>
#include <windows.h>

#define RESET "\033[0m"
#define YELLOW "\033[33m" /* Yellow */

int main(int argc, char* argv[]) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN);

    DWORD outMode = 0;
    GetConsoleMode(console, &outMode);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, outMode);
    printf(YELLOW "\x1b[5;33HP %s" RESET, argv[0]);
    printf(YELLOW "\x1b[6;33HGP %s" RESET, argv[1]);
    printf(YELLOW "\x1b[1;27HGC2" RESET);
    for (int i = 1; i < 31; i++) {
        // printf("Grandchild2 iterator: %d\n", i);
        printf(YELLOW "\x1b[%d;27H%d" RESET, i + 1, i);
        sleep(1);
    }
}