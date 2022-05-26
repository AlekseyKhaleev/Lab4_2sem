#include "lib_strings.h"
#include <iostream>


namespace lib_strings {

    /*****************************************************************************************************************/
    /*                                        TCharArray class                                                       */
    /*****************************************************************************************************************/

    TCharArray::TCharArray() = default; // Конструктор по умолчанию, не принимает аргументов

    TCharArray::TCharArray(const char *string) { // Конструктор принимает аргумент типа const char*
        size_of_str = strlen(string) + 1;       // определение длины будущего массива (+1 для нуль-терминатора)
        _str = new char[size_of_str];            // выделение памяти
        if (_str) {
            /* Посимвольное копирование данных в новую память */
            for (int i = 0; i < size_of_str; i++) {
                _str[i] = string[i];
            }
        }
    }

    TCharArray::TCharArray(int digit) {     // Конструктор принимает аргумент типа int
        int len = 0; // счетчик - длина будущей строки (и количество символов в числе digit)
        int tmp = digit; // временная переменная для хранения исходного значения
        /* Определяем количество символов в полученном аргументе */
        do {
            len++; // увеличиваем значение счетчика
            digit /= 10; // делим нацело на 10
        } while (digit != 0); //пока аргумент не станет равным 0
        size_of_str = len + 1; // присваиваем значение соответствующему атрибуту (+1 для нуль-терминатора)
        _str = new char[size_of_str]; // выделяем память
        if (_str) {
            /* Посимвольно копируем цифры аргумента */
            for (int i = len - 1; i >= 0; i--) { // Присваиваем с конца
                // остаток от деления на 10 - есть последняя значащая цифра
                _str[i] = char((tmp % 10) + 48); // цифра (0-9) + 48 - есть код числа в соответствии с таблицей ASCII
                tmp /= 10; // для продвижения по числу отбрасываем последнюю цифру с помощью целочисленного деления
            }
        }
        _str[len] = '\0'; // дописываем в конец нуль-терминатор
    }

    // Деструктор
    TCharArray::~TCharArray() {
        delete[] _str;
        _str = nullptr;
    } // при уничтожении объекта освобождаем память выделенную под _str

    // Методы
    char *TCharArray::begin() { return _str; } // возвращает указатель на начало массива

    char *TCharArray::end() { return _str + size_of_str; } // возвращает указатель на конец массива

    char &TCharArray::at(unsigned long index) { // доступ к элементу массива по индексу
        /* Если индекс выходит за границу массива вызываем исключение*/
        if (index >= size_of_str) throw std::out_of_range("Invalid index");
        return _str[index];
    }

    char &TCharArray::operator[](unsigned long index) {// перегрузка оператора для доступа к элементу массива по индексу
        /* Если индекс выходит за границу массива вызываем исключение*/
        if (index < 0 || index >= size_of_str) throw std::out_of_range("Invalid index");
        return _str[index];
    }

    /**************************************************************************************************************
    *             "Правило 3/5/0" (деструктор с освобождением памяти в начале описания класса)                    *
    **************************************************************************************************************/

    // Конструктор копирования
    TCharArray::TCharArray(const TCharArray &other) : _str(new char[other.size_of_str]),
                                                      size_of_str(other.size_of_str) {
        std::strcpy(_str, other._str);
    }

    // Конструктор присваивания копии
    TCharArray &TCharArray::operator=(TCharArray const &other) {
        TCharArray copy(other);
        std::swap(*this, copy);
        return *this;
    }

    // Конструктор перемещения
    TCharArray::TCharArray(TCharArray &&that) noexcept: _str(nullptr), size_of_str(0) {
        std::swap(*this, that);
    }

    // Конструктор назначения перемещения
    TCharArray &TCharArray::operator=(TCharArray &&that) noexcept {
        std::swap(*this, that);
        return *this;
    }

    // Перегрузка функции перемещения
    void swap(TCharArray &lhs, TCharArray &rhs) noexcept {
        std::swap(lhs._str, rhs._str);
        std::swap(lhs.size_of_str, rhs.size_of_str);
    }

    /*****************************************************************************************************************/
    /*                                        String class                                                           */
    /*****************************************************************************************************************/

    //Конструкторы
    String::String() = default; // Конструктор по умолчанию, не принимает аргументов

    // Аргумент const char*, вызывает конструктор базового класса такого же типа
    String::String(const char *string) : TCharArray(string) {}

    // Аргумент int, вызывает конструктор базового класса такого же типа
    String::String(int digit) : TCharArray(digit) {}

    // Методы
    const char *String::get() {
        return _str; // возвращает указатель на начало массива _str
    }

    size_t String::get_size() {
        return size_of_str; // возвращает размер массива _str
    }

    //                                          Перегрузка операторов

    String &String::operator=(int digit) { // присваивание целого числа
        int len = 0; // Счетчик - длина будущей строки (и количество символов в числе digit)
        int tmp = digit; // временная переменная для хранения исходного значения
        /* Определяем количество символов в полученном аргументе */
        do {
            len++; // увеличиваем значение счетчика
            digit /= 10; // делим нацело на 10
        } while (digit != 0); //пока аргумент не станет равным 0
        size_of_str = len + 1; // присваиваем значение соответствующему атрибуту (+1 для нуль-терминатора)
        _str = new char[size_of_str]; // выделяем память
        if (_str) {
            /* Посимвольно копируем цифры аргумента */
            for (int i = len - 1; i >= 0; i--) { // Присваиваем с конца
                // остаток от деления на 10 - есть последняя значащая цифра
                _str[i] = char((tmp % 10) + 48); // цифра (0-9) + 48 - есть код числа в соответствии с таблицей ASCII
                tmp /= 10; // для продвижения по числу отбрасываем последнюю цифру с помощью целочисленного деления
            }
        }
        _str[len] = '\0'; // дописываем в конец нуль-терминатор
        return *this;
    }

    String &String::operator=(const char *string) { // Присваиваем аргумент типа const char*
        size_of_str = strlen(string) + 1; // определение длины будущего массива (+1 для нуль-терминатора)
        _str = new char[size_of_str]; // выделение памяти
        if (_str) {
            /* Посимвольное копирование данных в новую память */
            for (int i = 0; i < size_of_str; i++) {
                _str[i] = string[i];
            }
        }
        return *this;
    }

    String &String::operator=(char *string) { // Присваиваем аргумент типа char*
        size_of_str = strlen(string) + 1; // определение длины будущего массива (+1 для нуль-терминатора)
        _str = new char[size_of_str]; // выделение памяти
        if (_str) {
            /* Посимвольное копирование данных в новую память */
            for (int i = 0; i < size_of_str; i++) {
                _str[i] = string[i];
            }
        }
        return *this;
    }

    std::istream &operator>>(std::istream &input, String &str) { // перегрузка оператора ввода из потока
        char *old_str = str._str; // для избежания утечки памяти назначаем новый указатель на "старую" память
        str._str = new char[MAX_CHARS]; // выделяем новую память для чтения 80(максимум) символов из потока
        delete[] old_str; // освобождаем "старую" память
        input >> str._str; // осуществляем ввод из потока в массив _str
        str.size_of_str = strlen(str._str) + 1; // определяем количество введенных символов (+1 для нуль-терминатора)
        char *new_str = str._str; // определяем новый указатель на память для избежания потери введенных данных
        str._str = new char[str.size_of_str]; // выделяем новую память в точности необходимого размера
        /* Посимвольное копирование элементов в новую память */
        for (int i = 0; i < str.size_of_str - 1; i++) {
            str._str[i] = new_str[i];
        }
        str._str[str.size_of_str - 1] = '\0'; // добавляем нуль-терминатор в конец
        delete[] new_str; // освобождаем память размера MAX_CHARS
        return input;
    }

    std::ostream &operator<<(std::ostream &output, String &str) { // Перегрузка оператора вывода в потока
        output << str._str; // выводим в поток данные атрибута (указателя на массив) _str
        return output;
    }

    void operator+(String &left, String &right) { // перегрузка оператора конкатенации
        /* Выделяем память размером как 2 исходные нуль-терминированные строки (-1 нуль-терминатор) и присваиваем ей
         * временный указатель *tmp_ptr */
        char *tmp_ptr = new char[left.size_of_str + right.size_of_str - 1];
        /* В цикле копируем в новую память все символы из строки left кроме нуль-терминатора */
        if (*tmp_ptr) {
            for (auto &c: left) {
                if (c != '\0') {
                    *tmp_ptr = c; // присваиваем значение
                    tmp_ptr++;    // подвигаем указатель
                }
            }
            /* В цикле дописываем в новую память все символы из строки right включая нуль-терминатор */
            for (auto &c: right) {
                *tmp_ptr = c;
                tmp_ptr++;
            }
            left.size_of_str += right.size_of_str - 1; // присваиваем размер нового массива соответствующему атрибуту
            tmp_ptr -= left.size_of_str; // возвращаем указатель в начало выделенной памяти
            char *old_str = left._str; // во избежание утечки памяти присваиваем новый указатель "старой" памяти
            left._str = tmp_ptr; // присваиваем атрибуту (указателю на массив) адрес памяти новой строки
            delete[] old_str; // освобождаем "старую" память
        }
    }

    /*                                   Перегрузка операторов сравнения                                            */

    bool operator==(String &left, String &right) { // перегрузка оператора равенства
        return !strcmp(left.get(), right.get());   // лексикографическое сравнение средствами стандартной библиотеки
    }

    bool operator!=(String &left, String &right) { // перегрузка оператора неравенства
        return strcmp(left.get(), right.get());    // лексикографическое сравнение средствами стандартной библиотеки
    }

    bool operator>(String &left, String &right) {    // перегрузка оператора "больше"
        return strcmp(left.get(), right.get()) > 0;  // лексикографическое сравнение средствами стандартной библиотеки
    }

    bool operator<(String &left, String &right) {    // перегрузка оператора "меньше"
        return strcmp(left.get(), right.get()) < 0;  // лексикографическое сравнение средствами стандартной библиотеки
    }
}