#include <stdio.h>
#include <windows.h>

void main() {
    char buffer[100];
    DWORD actlen, error;
    HANDLE hstdout, fhandle;
    char fname[] = "file";
    BOOL rc;

    COORD coord;
    coord.X = 50;
    coord.Y = 13;

    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hstdout, coord);
    SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_BLUE);

    fhandle = CreateFile(  // создает или открывает каталог, физический диск,
                           // том, буфер консоли (CONIN$ или CONOUT$),
                           // устройство на магнитной ленте, коммуникационный
                           // ресурс, почтовый слот или именованный канал.
                           // Функция возвращает дескриптор, который может быть
                           // использован для доступа к объекту.
        fname,  // Указатель на символьную строку с нулем в
                // конце, устанавливающую имя объекта, который
                // создается или открываться.
        GENERIC_READ,  // Тип доступа к объекту (чтение, запись
                       // или то и другое).
                       // GENERIC_READ это флаги FILE_READ_ATTRIBUTES
                       // FILE_READ_DATA FILE_READ_EA
                       // STANDARD_RIGHTS_READ SYNCHRONIZE
        0,  // Режим совместного доступа (чтение, запись, оба
            // или никакого действия).
        0,  // Указатель на структуру SECURITY_ATTRIBUTES, которая
            // устанавливает может ли возвращенный дескриптор быть
            // унаследован дочерними процессами.
        OPEN_EXISTING,  // Выполняемые действия с файлами, которые
                        // существуют и выполняемые действия с
                        // файлами, которые не существуют.
        FILE_ATTRIBUTE_NORMAL,  // Атрибуты и флажки файла. У файла нет других
                                // установленных атрибутов. Этот атрибут
                                // допустим только в том случае, если он
                                // используется один.
        0  // Дескриптор файла шаблона с правом доступа GENERIC_READ. Файл
           // шаблона предоставляет атрибуты файла и дополнительные атрибуты для
           // создающегося файла. Этот параметр должен быть ПУСТО (NULL).
    );
    if (fhandle == INVALID_HANDLE_VALUE) {
        error = GetLastError();
        if (error == 32) {
            printf("Error! ");
            while (fhandle == INVALID_HANDLE_VALUE) {
                fhandle = CreateFile(fname, GENERIC_READ, 0, 0, OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL, 0);
            }
        }
    }
    rc = ReadFile(fhandle, buffer, 80, &actlen, NULL);
    WriteFile(hstdout, buffer, actlen, &actlen, NULL);
    sleep(10);
    CloseHandle(fhandle);
}