#include "stdio.h"
#include "windows.h"

HANDLE map, sema;

int main() {
    system("cls");
    sema = OpenSemaphore(  //  открывает  семафор
        SYNCHRONIZE,       // Доступ к объекту семафора
        FALSE,  // процессы не наследуют дескриптор
        "sema1"  // имя семафора
    );
    WaitForSingleObject(  //  ожидает сигнал
        sema,             // дескриптор
        INFINITE  // вернется только тогда, когда получит сигнал
    );
    map = OpenFileMapping(  // открывает именованный объект файла
        FILE_MAP_READ,  // Доступ для чтения
        FALSE,          // не налседовать дексриптор
        "map"           // имя файла
    );
    char* buf = (char*)MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
    printf("READ FROM:%08X - %s", &buf, buf);
    getchar();
    return 0;
}