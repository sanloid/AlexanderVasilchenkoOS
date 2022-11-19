#include <stdio.h>
#include <string.h>
#include <windows.h>

#define RESET "\033[0m"
#define BLUE "\033[34m" /* Blue */

int main(int argc, char* argv[]) {
    DWORD rc;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    DWORD outMode = 0;
    GetConsoleMode(console, &outMode);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, outMode);

    char args[] = "Child1.exe ";
    strcat(args, argv[0]);

    rc = CreateProcess("Grandchild1.exe", args, NULL, NULL, FALSE,
                       NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    if (!rc) {
        printf("Error CreateProcess: %d", GetLastError());
        return 0;
    }
    printf(BLUE "\x1b[1;33HP %s" RESET, argv[0]);
    printf(BLUE "\x1b[1;9HC1" RESET);
    for (int i = 1; i < 16; i++) {
        printf(BLUE "\x1b[%d;9H%d" RESET, i + 1, i);
        sleep(2);
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}