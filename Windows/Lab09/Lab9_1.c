#include "stdio.h"
#include "windows.h"

HANDLE map, sema;

int main() {
    system("cls");
    sema = CreateSemaphore(  // создает семафор
        NULL,                // атрибут доступа
        0,  // начальное состояние счетчика
        1,  // максимальное количество обращений
        "sema1"  // имя
    );
    map = CreateFileMapping(  // создает или открывает объект в памяти
        (HANDLE)-1,              // дескриптор файла
        NULL,                    // защита
        PAGE_EXECUTE_READWRITE,  // Дает доступ для чтения, записи и исполнения
        0,     // размер слова младшего порядка
        1000,  // старшего
        "map"  // имя объекта
    );
    char* buf = (char*)MapViewOfFile(  // отображает представление проецируемого
                                       // файла в адресное пространство
        map,             // дескр. объекта
        FILE_MAP_WRITE,  // Доступ к операциям чтения-записи
        0,               // старшего
        0,               // смещение младшего порядка
        0                // сколько байтов отображать
    );
    Sleep(2000);
    sprintf(buf, "Secret message");
    printf("WROTE IN:%08X - %s\n", &buf, buf);
    ReleaseSemaphore(  // меняет счётчик
        sema,          // хенд семафора
        1,             // на сколько изменить счётчик
        NULL           // предыдущее значение
    );

    char* buf1 = (char*)VirtualAlloc(NULL,        // адрес
                                     1000,        // размер
                                     MEM_COMMIT,  // способ получения
                                     PAGE_READWRITE  // типа доступа
    );
    for (int i = 0; i < 15; i++) {
        *(buf1 + 399 * i) = 'a' + i;
        printf("%08X = %c\n", buf1 + 399 * i, *(buf1 + 399 * i));
    }
    CloseHandle(sema);
    UnmapViewOfFile(  //  отменяет отображение
        buf           // адрес
    );
    CloseHandle(map);
    getchar();
    return 0;
}