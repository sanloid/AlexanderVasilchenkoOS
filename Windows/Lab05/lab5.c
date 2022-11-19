#include <stdio.h>
#include <wincon.h>
#include <windows.h>
#define RESET "\x1b[0m"
#define RED "\x1b[31m" /* Red */

void main() {
    int i, x, y;
    HANDLE fhand, hin, hout, hW, hR;
    DWORD cbw = 0, length, rc, cbRead;
    INPUT_RECORD infbuf;
    COORD pos1, pos2, pos3, outCoordPos, writePos;
    DWORD outMode = 0;
    char filename[30] = "lab5.txt", buf[255], buffer[4];
    char ch, newChar;

    short attr = BACKGROUND_GREEN;

    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    hin = GetStdHandle(STD_INPUT_HANDLE);
    if (hin == INVALID_HANDLE_VALUE || hout == INVALID_HANDLE_VALUE) {
        return;
    }

    fhand = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, 0,
                       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (fhand == INVALID_HANDLE_VALUE) {
        printf("File not found\n");
        ExitProcess(1);
    }

    do {
        rc = ReadFile(fhand, buffer, 4, &cbRead, NULL);
        WriteFile(hout, buffer, cbRead, &cbRead, NULL);
    } while (cbRead != 0);

    printf("\n");
    GetConsoleMode(hout, &outMode);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hout, outMode);
    SetConsoleMode(  // устанавливает режим ввода данных буфера ввода
                     // консоли или режима вывода экранного буфера
                     // консоли.
        hin,  // Дескриптор буфера ввода или экранного буфера консоли.
        ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT
        // Режим ввода или вывода
        // данных, который будет
        // установлен.ENABLE_MOUSE_INPUT
        // если курсор мыши - в пределах
        // границ консольного окна, и
        // окно имеет фокус клавиатуры,
        // события от нажатия мыши,
        // созданные перемещением мыши и
        // нажатием кнопки помещаются в
        // буфере ввода.
        // ENABLE_EXTENDED_FLAGS
        // запрещает пользователю
        // использовать мышь для выбора
        // и редактирования текста.
    );
    infbuf.EventType = MOUSE_EVENT;
    while (1) {
        if (ReadConsoleInput(hin, &infbuf, 1, &cbw)) {
            if (infbuf.Event.MouseEvent.dwButtonState ==
                RIGHTMOST_BUTTON_PRESSED) {
                return;
            }
            outCoordPos.Y = 24;
            outCoordPos.X = 1;
            pos3.Y = 25;
            pos3.X = 1;

            if (infbuf.Event.MouseEvent.dwButtonState ==
                FROM_LEFT_1ST_BUTTON_PRESSED) {
                pos1.X = infbuf.Event.MouseEvent.dwMousePosition.X;
                pos1.Y = infbuf.Event.MouseEvent.dwMousePosition.Y;
                writePos.X = infbuf.Event.MouseEvent.dwMousePosition.X;
                writePos.Y = infbuf.Event.MouseEvent.dwMousePosition.Y;
                ReadConsoleOutputCharacter(  //  копирует ряд символов
                                             //  из последовательных
                                             //  ячеек экранного буфера
                                             //  консоли, начинающихся в
                                             //  заданном месте.
                    hout,  //  Дескриптор экранного буфера консоли.
                    &ch,  // Указатель на буфер, который принимает
                          // прочитанные символы из экранного буфера
                          // консоли.
                    1,  // Число символьных знакомест экранного буфера
                        // для чтения.
                    pos1,  //  Координаты первой ячейки для чтения в
                           //  экранном буфере консоли.
                    &cbw  // Указатель на переменную, которая получает
                          // число фактически прочитанных символов.
                );
                ReadConsoleOutputCharacter(hout, &newChar, 1, pos1, &cbw);

                if (ch != ' ') {
                    FillConsoleOutputAttribute(  //  устанавливает
                                                 //  атрибуты символов
                                                 //  для заданного числа
                                                 //  символьных
                                                 //  знакомест,
                                                 //  начинающихся в
                                                 //  заданных
                                                 //  координатах в
                                                 //  экранном буфере.
                        hout,  // Дескриптор экранного буфера консоли.
                        0x00,  // Присваивает атрибуты, которые
                               // используются при записи в экранный
                               // буфер консоли.
                        80,  // Число символьных знакомест, в которые
                             // будут установлены заданные атрибуты
                             // цвета.
                        pos3,  // Структура COORD, которая устанавливает
                               // координаты экранного буфера консоли
                               // первой ячейки, атрибуты которой должны
                               // быть установлены.
                        &cbw  // Указатель на переменную, которая
                              // принимает число символьных знакомест,
                              // атрибуты которых были фактически
                              // установлены.
                    );

                    for (i = 0; i < cbw; i++) {
                        buf[i] = ' ';
                    }
                    WriteConsoleOutputCharacter(
                        hout,  // Дескриптор экранного буфера консоли.
                        buf,  // Указатель на буфер, который содержит
                              // символы, для записи в экранный буфер
                              // консоли.
                        strlen(buf),  // Число TCHARs, которые будут
                                      // записаны.
                        pos3,  // Структура COORD, которая устанавливает
                               // координаты первой ячейки в экранном
                               // буфере консоли в которые символы
                               // должны быть записаны.
                        &cbw  // Указатель на переменную, которая
                              // получает число фактически записанных
                              // TCHARs.
                    );
                    SetConsoleCursorPosition(hout, outCoordPos);
                    printf("      ");
                    SetConsoleCursorPosition(hout, outCoordPos);
                    printf("%d,%d", pos1.X, pos1.Y);
                    pos2 = pos1;
                    if (newChar <= 'Z' && newChar >= 'A') {
                        newChar += 32;
                        SetConsoleCursorPosition(hout, writePos);
                        printf(RED "%c" RESET, newChar);
                    } else if (newChar <= 'z' && newChar >= 'a') {
                        newChar -= 32;
                        SetConsoleCursorPosition(hout, writePos);
                        printf(RED "%c" RESET, newChar);
                    }

                    while ((ch != ' ') && (pos1.X > 0)) {
                        pos1.X--;
                        ReadConsoleOutputCharacter(hout, &ch, 1, pos1, &cbw);
                    }

                    if (ch == ' ') pos1.X++;

                    do {
                        pos2.X++;
                        ReadConsoleOutputCharacter(hout, &ch, 1, pos2, &cbw);
                    } while ((ch != ' ') && (pos2.X < 80));

                    if (ch == ' ') pos2.X--;

                    cbw = pos2.X - pos1.X + 1;

                    ReadConsoleOutputCharacter(hout, buf, cbw, pos1, &cbw);
                    WriteConsoleOutputCharacter(hout, buf, cbw, pos3, &cbw);
                    FillConsoleOutputAttribute(hout, attr, cbw, pos3, &cbw);
                }
            }
        }
    }
}