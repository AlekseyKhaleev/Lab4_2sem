/**********************************************************************************************************************
* Данный модуль содержит определения методов собственных классов, определенных в "classes.h"
**********************************************************************************************************************/

/* Подключение модулей */
#include <string>
#include <iostream>
#include <fstream>
#include "lib_classes.h"

SyntaxException::SyntaxException(const std::string &message, int type, int argc) : runtime_error{message} {
    _type=type;
    _argc=argc;
}

void SyntaxException::description(){
    /*****************************************************************************************************************
    * Цель: Вывести в STDOUT сообщение с описанием полученной ошибки аргументов и краткую справку.
    * Исходные данные:
     *  type - закрытая переменная класса SyntaxException
     *  argc - закрытая переменная класса SyntaxException
    * Результат: В поток вывода выведено сообщение об ошибке.
    * Вызываемые модули: <string>, "classes.h"
    * Описание алгоритма:
    * 1) Определяется массив string[], содержащий общую информацию о корректных аргументах
    * 2) Выводится сообщение, в котором:
     * type - тип ошибки
     * argc - количество полученных аргументов
     * what() - возвращенное описание ошибки
    * 3) В цикле по строчно выводится базовое сообщение
    * Дата: 15 / 05 / 2022 Версия 1.01
    * Автор: Студент НГТУ ИРИТ, Халеев А. А. гр. 21-ИВТз
    * Исправления: нет
    *****************************************************************************************************************/
    std::string error_msg[] = {
            "Correct arguments for run this app:\n\n",
            "--help or -h : help mode\n",
            "-с [N] [file_name] : create spreadsheet mode\n",
            "-r [N] [file_name] : read spreadsheet mode\n\n",
            "N – the number of records;\n",
            "file_name – file name or full path to save/read the table;\n\n"
    };
    std::cout << "\nSyntax Exception Type " << _type << " : " << _argc - 1 << " arguments given.\n" << what() << "\n\n";
    for (auto &i: error_msg) {
        std::cout << i;
    }
}
/*********************************************************************************************************************/
/*                                            PC class                                                               */
/*********************************************************************************************************************/

void PC::set(int row_to_print){
    /*****************************************************************************************************************
    * Цель: Инициализация элементов структуры значениями, считанными из потока STDIN с перемещением
    * курсора во время ввода в соответствующие ячейки таблицы.
    * Исходные данные:
    *   row_number   - порядковый номер строки таблицы
    *   row_to_print - строка таблицы, в которой должен осуществляться ввод
    * Результат: Элементы структуры инициализированы соответствующими значениями.
    * Вызываемые модули: <iostream>, "structs.h", "definitions.h"
    * Описание алгоритма:
    * 1) Переменная current_col, соответствующая позиции текущего столбца для ввода, инициализируется
    * начальным значением START_COL
    * 2) Для каждого элемента структуры:
    *   - курсор перемещается в очередную позицию (используются шаги сдвига курсора, определенные в definitions.h)
    *   - производится пользовательский ввод с клавиатуры очередного значения элемента структуры
    * Дата: 15 / 05 / 2022 Версия 1.01
    * Автор: Студент НГТУ ИРИТ, Халеев А. А. гр. 21-ИВТз
    * Исправления: нет
    *****************************************************************************************************************/

    int current_col = START_COL;
    move_cursor(START_ROW + row_to_print * STEP_ROW, START_COL);
    for(auto & _attribute : _attributes){
        std::cin >> *_attribute;
        move_cursor(START_ROW + row_to_print * STEP_ROW, current_col += STEP_COL);
    }
}
void PC::print(int row_to_print){
    /*****************************************************************************************************************
    * Цель: Вывод элементов структуры с перемещением курсора во время вывода в соответствующие ячейки таблицы.
    * Исходные данные:
    *   row_to_print - строка таблицы, в которой должен осуществляться вывод
    * Результат: Элементы структуры выведены в соответствующих ячейках таблицы.
    * Вызываемые модули: <iostream>, "structs.h", "definitions.h"
    * Описание алгоритма:
    * 1) Переменная current_col, соответствующая позиции текущего столбца для вывода, инициализируется
    * начальным значением START_COL
    * 2) Для каждого элемента структуры:
    *   - курсор перемещается в очередную позицию (используются шаги сдвига курсора, определенные в definitions.h)
    *   - производится вывод очередного значения элемента структуры
    * Дата: 15 / 05 / 2022 Версия 1.01
    * Автор: Студент НГТУ ИРИТ, Халеев А. А. гр. 21-ИВТз
    * Исправления: нет
    *****************************************************************************************************************/

    int current_col = START_COL;
    move_cursor(START_ROW + row_to_print * STEP_ROW, START_COL);
    for(auto &_attribute:_attributes){
        std::cout << *_attribute;
        move_cursor(START_ROW + row_to_print * STEP_ROW, current_col += STEP_COL);
    }
}
void PC::write(std::fstream &fd){
    for(auto &_attribute:_attributes){
        lib_strings::size_t attr_size = _attribute->get_size();
        fd.write((char *) &attr_size, sizeof(lib_strings::size_t));
        fd.write((char *) &*_attribute->get(), long(attr_size));
    }
}
void PC::read(std::fstream &fd) {
        for(auto &_attribute:_attributes){
            lib_strings::size_t attr_size{0};
            fd.read((char *) &attr_size, sizeof(lib_strings::size_t));
            char content[attr_size];
            fd.read((char *) &content, long(attr_size));
            *_attribute = content;
    }
}

