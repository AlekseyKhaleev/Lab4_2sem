// Lab3_2.cpp: Листинг программы для Задания 1, 3-й лабораторной работы 2-го семестра
// Вариант 8
//*********************************************************************************
// Имя файла: Lab3_2.cpp
// Резюме: Пример программы написанной на языке программирования С++
// Описание:
// Программа позволяет создавать и просматривать таблицы парка ПК,
// получать справку и прокручивать экран. Таблица сохраняется в бинарном файле.
// Каждый бинарный файл содержит:
// 1) уникальный числовой идентификатор программы
// 2) количество записей в таблице
// 3) непосредственно записи таблице, организованные с помощью структур.
// - для корректного вызова программы требуется указать серию аргументов:
// --help или -h      : режим справки
// -с [N] [file_name] : режим создания таблицы
// -r [N] [file_name] : режим чтения таблицы
// где:
//    N – число записей для ввода/вывода;
//    file_name – асболютный или относительный путь к файлу;
// В программе организована обработка аргументов командной строки,
// при некорректных параметрах выводятся соответствующие сообщения
//  Программа поддерживает некоторые горячие клавиши:
// - Up, Down - прокрутка текста;
// - h - вызов справки;
// - r - возврат к текстовому файлу;
// - ESC - завершение программы;
// Дата создания: 19 / 05 / 2022
// Автор : Студент НГТУ ИРИТ, Халеев А.А., гр. 21-ИВТз
// Платформа : OS Ubuntu 22.04, Jet Brains Clion IDE (Study)
// *********************************************************************************

/* Подключение модулей */

#include "print_func.h"
#include "draw_func.h"
#include "table_func.h"
#include <iostream>
#include <string>
#include <map>
#include "lib_classes.h"
#include "lib_strings.h"

using namespace lib_strings;
/* Для корректной работы программы необходимо передать путь к текстовому файлу в качестве аргумента командной строки */
int main(int argc, char **argv) {

/**********************************************************************************************************************/
    /* В процессе работы программы будут изменены размеры окна терминала
     * для того, чтобы восстановить их по завершению работы программы, следует сохранить исходные параметры
     * с помощью функции GetWinSize в соответствующих переменных*/
    int win_width;
    int win_height;
    GetWinSize(win_width, win_height);
/**********************************************************************************************************************/
    /* Блок Try-except отлавливает исключения, генерируемые при обнаружении некорректных аргументов командной строки */
    try {
        switch (argc) { // ветвление в зависимости от количества полученных аргументов
            case 2: {   // получен 1 пользовательский аргумент + argc (помним, что argc всегда получаем первым)
                /* Если полученный аргумент соответствует запуску в режиме справки*/
                if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
                    CustomizeTerminal(F_BLACK, B_WHITE); // применяем новые параметры терминала
                    PrintHelpScreen("help_arg");             // выводим справочную страницу
                    /**************************************************************************************************/
                    /* Блок управления, поддерживает только выход из программы*/
                    bool mark = true;
                    while (mark) {
                        switch (UserKey()) {
                            case Escape:
                                mark = false;
                                break;
                            default:
                                break;
                        }
                    }
                    /**************************************************************************************************/
                } else
                    throw SyntaxException("First argument is wrong. Among other things, check your keyboard layout", 1,
                                          argc);
                break;
            }
            case 4: { // получено 3 пользовательских аргумент + argc (помним, что argc всегда получаем первым)
                int rows_request; // переменная для хранения желаемого количество строк в таблице
                try {
                    rows_request = std::stoi(argv[2]); // попытка привести к целому типу полученного аргумента
                } catch (std::exception &stoi_err) {
                    throw SyntaxException("The specified number of lines must be an integer", 2, argc);
                }
                if (rows_request <= 0) {       // Если пользователь захотел ввести/прочитать 0 или меньше строк
                    throw SyntaxException(
                            "The specified number of lines can't be less than or equal to zero", 3, argc);
                }
                /* Функция std::stoi() выше приведет к целому первую цифру из массива char* полученного
                 * в качестве аргумента, поэтому стоит сделать обратную проверку - она укажет на наличие не цифровых
                 * символов в полученном аргументе, например при попытке передать число с плавающей точкой*/
                if (argv[2] != std::to_string(rows_request)) {
                    throw SyntaxException(
                            "It is not possible to use a floating point number to specify the number of lines\n"
                            "You should also use only digits for an integer", 4, argc);
                } else
                    /* Если количество строк целое и больше нуля */
                {
                    /* карта аргументов для блока switch */
                    std::map<std::string, int> choice_map{
                            /* Строка справки для экрана, формируемого в случае некорректного запуска программы */
                            {"-r", 1},
                            /* Строка справки для экрана, формируемого в режиме прокрутки содержимого файла */
                            {"-c", 2}
                    };
                    switch (choice_map[argv[1]]) {
                        case 1: { // если получен аргумент -r, соответствующий режиму чтения таблицы
                            /* Открываем бинарный файл в режиме чтения*/
                            std::fstream table_in(argv[3], std::ios::in | std::ios::binary);
                            /* Проверка открытия */
                            if (!table_in.is_open()) { // Не удалось открыть файл
                                throw SyntaxException(
                                        "Unable to open or create specified file. Check that the specified file exists",
                                        5, argc);
                            } else
                                /* Если файл открыт успешно, продолжаем работу с его содержимым */
                            {
                                unsigned long file_bit; // переменная для хранения специального кода программы
                                table_in.seekg(0, std::ios::end);  // перемещаем курсор из начала в конец файла
                                long file_size = table_in.tellg(); // сохраняем размер фала
                                if (file_size == 0) {  // если файл пустой
                                    throw SyntaxException("The specified file is empty", 6, argc);
                                } else
                                    /* Если файл не пустой */
                                {
                                    table_in.seekg(std::ios::beg); // перемещаем курсор в начало
                                    /* считываем специальный код программы */
                                    table_in.read((char *) &file_bit, sizeof(CORRECT_BIT));
                                    if (file_bit == CORRECT_BIT)
                                        /* Если получен корректный код, значит файл был создан в этом приложении */
                                    {
                                        /* Вывод содержимого файла в виде таблицы, с поддержкой управляющих клавиш */
                                        ViewTable(argv, table_in, rows_request);
                                    } else
                                        /* Если получен считан некорректный специальный код */
                                    {
                                        throw SyntaxException(
                                                "The specified file was not created in this program", 7, argc);
                                    }
                                }
                                table_in.close(); // по завершению работы ViewTable закрываем файл
                                /* Проверка закрытия файла */
                                if (table_in.is_open()) {
                                    throw SyntaxException("Unable to close specified file", 8, argc);
                                }
                            }
                            break;
                        }
                        case 2: { // если получен аргумент -c, соответствующий режиму создания таблицы
                            /* Открываем бинарный файл в режиме чтения и записи:
                             * - если файл не существует, он будет создан */
                            std::fstream table_out(argv[3],
                                                   std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
                            /* Проверка открытия файла */
                            if (!table_out.is_open()) { // Если не удалось открыть файл
                                throw SyntaxException(
                                        "Unable to open or create specified file. Check that the specified file exists",
                                        5, argc);
                            } else
                                /* Если файл открыт успешно, продолжаем работу с его содержимым */
                            {
                                /* Создаем файл-таблицу с помощью функции CreateTable
                                 * После завершения функция вернет номер первой строки, отображенной на экране*/
                                int row_number = CreateTable(argv, table_out, rows_request);
                                /* Для того чтобы пользователь мог посмотреть введенные данные, а также справку,
                                 * выводим содержимое файла в виде таблицы, с поддержкой управляющих клавиш.
                                 * Вывод начинается со строки, возвращенной CreateTable */
                                ViewTable(argv, table_out, rows_request, row_number);
                                table_out.close(); // по завершению работы ViewTable закрываем файл
                                /* Проверка закрытия файла */
                                if (table_out.is_open()) {
                                    throw SyntaxException("Unable to close specified file", 8, argc);

                                }
                                break; // конец блока создания таблицы
                            }
                        }
                        default:
                            /* Если количество пользовательских аргументов равно 3, аргумент [N] целое и больше нуля,
                             * но получен неизвестный первый пользовательский аргумент*/
                        {
                            throw SyntaxException(
                                    "First argument is wrong. Among other things, check your keyboard layout", 1,
                                    argc);
                        }
                    }
                    break; // конец обработки режима запуска (первый аргумент)
                }
                default:
                    /* Если полученное количество пользовательских аргументов больше 3 или равно 0 */
                {
                    throw SyntaxException(
                            "Wrong number of arguments", 9, argc);
                    break; // конец обработки количества полученных аргументов
                }
            }
        }
    } catch (SyntaxException &ex)
    /* Если поймали собственное исключение (переданы некорректные аргументы командной строки) */
    {
        ex.description(); // Вызываем сообщение, соответствующее ошибке с помощью метода .description()
        return 1; // Завершение программы с кодом 1
    }
    /* Перед завершением работы программы восстанавливаем исходные настройки терминала */
    ResetTerminal(win_width, win_height);
    return 0; // Завершение программы с кодом 0.
}
