#include <stdio.h>
#include <windows.h>

#define RESET "\033[0m"
#define RED "\033[31m" /* Red */

int main() {
    DWORD rc, rc1;
    STARTUPINFO si;
    PROCESS_INFORMATION pi, ch1, ch2;
    HANDLE sproc;
    int i = 1;

    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD outMode = 0;
    GetConsoleMode(console, &outMode);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, outMode);
    printf(RED "\x1b[1;1HParent" RESET);
    for (int i = 1; i < 16; i++) {
        printf(RED "\x1b[%d;1H%d" RESET, i + 1, i);
        if (i == 2) {
            rc = CreateProcess(  // создает новый процесс.
                "Child1.exe",    // имя исполняемого модуля
                "Parent.exe",  // Командная строка. Здесь передаются
                               // параметры. Она может быть NULL. Здесь
                               // можно указать и путь и имя модуля.
                NULL,  // Здесь определяются атрибуты защиты для
                       // нового приложения. Если указать NULL то
                       // система сделает это по умолчанию.
                NULL,  //  Здесь определяются атрибуты защиты для первого потока
                       //  созданного приложением. NULL опять приводит к
                       //  установке по умолчанию.
                FALSE,  // Флаг наследования от процесса производящего запуск.
                        // Здесь наследуются дескрипторы. Унаследованные
                        // дескрипторы имеют те же значения и права доступа, что
                        // и оригиналы.
                NORMAL_PRIORITY_CLASS,  // Флаг способа создание процесса и его
                                        // приоритет. NORMAL_PRIORITY_CLASS
                                        // указывает на процесс, без каких либо
                                        // специальных требований к выполнению.
                NULL,  // Указывает на блок среды. Если NULL, то будет
                       // использован блок среды родительского процесса. Блок
                       // среды это список переменных имя=значение в виде строк
                       // с нулевым окончанием.
                NULL,  // Указывает текущий диск и каталог. Если NULL то будет
                       // использован диск и каталог процесса родителя.
                &si,  //  Используется для настройки свойств процесса, например
                      //  расположения окон и заголовок. Структура должна быть
                      //  правильно инициализирована
                &ch1  // Структура PROCESS_INFORMATION с информацией о процессе.
                      // Будет заполнена Windows.
            );
            if (!rc) {
                printf("Error CreateProcess: ", GetLastError());
                getchar();
                return 0;
            }
        }

        if (i == 4) {
            sproc = CreateJobObject(  // создает или открывает объект задания.
                NULL,  // Указатель на структуру SECURITY_ATTRIBUTES, которая
                       // устанавливает дескриптор безопасности для объекта
                       // задания и обуславливает могут ли дочерние процессы
                       // наследовать возвращенный дескриптор. Если
                       // lpJobAttributes имеет значение ПУСТО (NULL), объект
                       // задания получает заданный по умолчанию дескриптор
                       // безопасности, и он не может быть унаследован. Списки
                       // контроля доступа (ACL) в заданном по умолчанию
                       // дескрипторе безопасности для объекта задания
                       // происходят от первичного маркера или маркера
                       // заимствования прав создателя.
                NULL  // Указатель на символьную строку с нулем в конце,
                      // определяющую имя задания. Имя ограничивается символами
                      // MAX_PATH. Имя сравнивается с учетом регистра. Если
                      // lpName имеет значение ПУСТО (NULL), задание создано без
                      // имени(названия). Если lpName соответствует имени
                      // существующего события, семафора, мьютекса, ждущего
                      // таймера или отображаемого в памяти объекта, функция
                      // завершается ошибкой, а функция GetLastError возвращает
                      // значение ERROR_INVALID_HANDLE. Это происходит потому,
                      // что эти объекты совместно используют одно и то же
                      // пространство имен.
            );
            rc1 = CreateProcess("Child2.exe", "Parent.exe", NULL, NULL, FALSE,
                                NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &ch2);
            AssignProcessToJobObject(  // связывает процесс с существующим
                                       // объектом задания.
                sproc,  // Дескриптор объекта задания, с которым процесс должен
                        // быть связан. Функция CreateJobObject или
                        // OpenJobObject возвращает этот дескриптор.
                ch2.hProcess  // Дескриптор процесса, который связан с объектом
                              // задания. Процесс ранее не должен быть назначен
                              // заданию. Дескриптор должен иметь права доступа
                              // PROCESS_SET_QUOTA и PROCESS_TERMINATE.
            );
            if (!rc1) {
                printf("Error CreateProcess: ", GetLastError());
                getchar();
                return 0;
            }
        }
        if (i == 7) {
            printf("\x1b[1;49H\033[1m\033[30mChild1 was killed\n" RESET);
            TerminateProcess(  // завершает работу заданного процесса и всех его
                               // потоков.
                ch1.hProcess,  // Дескриптор процесса, который завершает
                               // работу.
                0  // Код выхода, который использует процесс и потоки, чтобы
                   // завершить работу в результате этого вызова
            );
        }
        if (i == 11) {
            printf("\x1b[2;49H\033[1m\033[30mChild2 was killed\n" RESET);
            TerminateJobObject(  // завершает работу всех процессов, в настоящее
                                 // время связанных с заданием.
                sproc,  // Дескриптор задания, процессы которого должен быть
                        // завершены. Функция CreateJobObject или OpenJobObject
                        // возвращает этот дескриптор.
                0  // Код выхода, который будет использоваться процессами и
                   // потоками, завершающими свою работу в результате этого
                   // вызова.
            );
        }
        sleep(3);
    }
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(
        console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}