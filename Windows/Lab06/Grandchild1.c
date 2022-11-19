#include <stdio.h>
#include <windows.h>

#define RESET "\033[0m"
#define GREEN "\033[32m" /* Green */

int main(int argc, char* argv[]) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);

    DWORD outMode = 0;
    GetConsoleMode(console, &outMode);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, outMode);

    printf(GREEN "\x1b[3;33HP %s" RESET, argv[0]);
    printf(GREEN "\x1b[4;33HGP %s" RESET, argv[1]);
    printf(GREEN "\x1b[1;19HGC1" RESET);
    for (int i = 1; i < 29; i++) {
        // printf("Grandchild1 iterator: %d\n", i);
        printf(GREEN "\x1b[%d;19H%d" RESET, i + 1, i);
        sleep(1);
    }
}