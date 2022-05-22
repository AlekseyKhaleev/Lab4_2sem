/*********************************************************************************************************************
* Данный модуль содержит определения собственных классов
*********************************************************************************************************************/

#pragma once

/* Подключение модулей */
#include <string>
#include <stdexcept>
#include "definitions.h"
#include "lib_strings.h"

using namespace lib_strings;

class SyntaxException : public ::std::runtime_error {
    /*****************************************************************************************************************
    * Назначение: Создание исключения, связанного с аргументами командной строки
    * Исходные данные:
     *  std::runtime_error - базовый класс
    * Вызываемые модули: <string>, <stdexcept>
    * Описание класса:
    * Класс наследуется от std::runtime_error. Такое наследование необходимо для обеспечения возможности родительского
    * метода .what() получать строку типа string в качестве аргумента.
    * В классе определены две закрытые (private) целочисленные переменные:
    *   type - предназначена для хранения типа ошибки
    *   argc - предназначена для хранения количества пользовательских аргументов командной строки, полученных программой
    * Класс имеет один метод: description(), предназначенный для вывода сообщения о типе ошибки и минимальной справки
    * Класс имеет один конструктор, принимающий:
    *   message - описание ошибки
    *   type - тип ошибки
    *   argc - количество пользовательских аргументов главного модуля
    * Инициализация:
    *   Описание ошибки (тип string) передается в родительский метод what(), целочисленные значения типа ошибки
    *  и количества пользовательских аргументов присваиваются соответствующим закрытым переменным.
    * Дата: 15 / 05 / 2022 Версия 1.01
    * Автор: Студент НГТУ ИРИТ, Халеев А. А. гр. 21-ИВТз
    * Исправления: нет
    *****************************************************************************************************************/
public:
    explicit SyntaxException(const std::string& message, int type, int argc);

    void description();

private:
    int _type;
    int _argc;
};

class PC{
    /*****************************************************************************************************************
    * Назначение: Описание характеристик ПК
    * Исходные данные:
    * Вызываемые модули:
    * Описание класса:
    * Класс содержит 6 private(скрытых) переменных и 2 метода(функции).
    * Private:
    *   1) _id   - порядковый номер ПК
    *   2) _cpu_type - тип процессора
    *   3) _cpu_freq - тактовая частота процессора
    *   4) _memory   - объем оперативной памяти
    *   5) _storage  - объем дискового накопителя
    *   6) _display  - тип дисплея
    * Методы:
    *   1) set      - инициализация элементов структуры значениями, считанными из потока STDIN с перемещением
    * курсора во время ввода в соответствующие ячейки таблицы.
    *   2) print    - вывод элементов структуры с перемещением курсора во время вывода в соответствующие ячейки таблицы.
    * Дата: 19 / 05 / 2022 Версия 1.01
    * Автор: Студент НГТУ ИРИТ, Халеев А. А. гр. 21-ИВТз
    * Исправления: нет
    *****************************************************************************************************************/
public:
    void read(std::fstream &fd);
    void write(std::fstream &fd);
    void set(int row_to_print);
    void print(int row_to_print);
    explicit PC()= default;
private:
    String _id;
    String _cpu_type;
    String _cpu_freq;
    String _memory;
    String _storage;
    String _display;
    String* _attributes[6]{&_id, &_cpu_type, &_cpu_freq, &_memory, &_storage, &_display};
};

