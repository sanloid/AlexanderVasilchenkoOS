#include <stdio.h>
#include <string.h>
#include <windows.h>

#define RESET "\033[0m"
#define CYAN "\033[36m" /* Cyan */

int main(int argc, char* argv[]) {
    DWORD rc1;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    DWORD outMode = 0;
    GetConsoleMode(console, &outMode);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, outMode);

    char args[] = "Child2.exe ";
    strcat(args, argv[0]);

    rc1 = CreateProcess("Grandchild2.exe", args, NULL, NULL, FALSE,
                        NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
    if (!rc1) {
        printf("Error CreateProcess: ", GetLastError());
        return 0;
    }
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    printf(CYAN "\x1b[2;33HP %s" RESET, argv[0]);
    printf(CYAN "\x1b[1;13HC2" RESET);
    for (int i = 1; i < 16; i++) {
        printf(CYAN "\x1b[%d;13H%d" RESET, i + 1, i);
        sleep(2);
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}