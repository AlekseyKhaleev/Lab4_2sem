#include "lib_strings.h"
#include <iostream>


namespace lib_strings {
    void NewError() {
        throw std::bad_alloc();
    }
    /*****************************************************************************************************************/
    /*                                        TCharArray class                                                       */
    /*****************************************************************************************************************/
    // Constructor
    TCharArray::TCharArray() = default;

    TCharArray::TCharArray(const char *string) {
        size_of_str = strlen(string)+1;
        _str = new char[size_of_str];
        if (_str) {
            for (int i = 0; i < size_of_str; i++) {
                _str[i] = string[i];
            }
        }
    }
    TCharArray::TCharArray(int digit) {
        int len=0;
        int tmp = digit;
        do{
            len++;
            digit/=10;
        }while(digit != 0);
        size_of_str = len+1;
        _str = new char[size_of_str];
        if (_str) {
            for (int i = len-1; i >= 0; i--) {
                _str[i] = char((tmp % 10) + 48);
                tmp /= 10;
            }
        }
        _str[len] = '\0';
    }

    // Destructor
    TCharArray::~TCharArray() { delete[] _str; }
    // Methods

    // Overloads
    char *TCharArray::begin() { return _str; }

    char *TCharArray::end() { return _str + size_of_str; }

    char &TCharArray::at(unsigned long index) {
        if (index >= size_of_str) throw std::out_of_range("Invalid index");
        return _str[index];
    }

    char &TCharArray::operator[](unsigned long index) {
        if (index < 0 || index >= size_of_str) throw std::out_of_range("Invalid index");
        return _str[index];
    }

    /*****************************************************************************************************************/
    /*                                        String class                                                           */
    /*****************************************************************************************************************/

    // Constructor
    String::String() = default;

    String::String(const char *string) : TCharArray(string) {}

    String::String(int digit) : TCharArray(digit) {}

    // Getter/Setter

    const char* String::get() {
        return _str;
    }
    size_t String::get_size() {
        return size_of_str;
    }
    /*void String::set(const char *arg) {
        *_str = *arg;
    }*/


    //Overloads
    String& String::operator=(int digit){
        int len=0;
        int tmp = digit;
        do{
            len++;
            digit/=10;
        }while(digit != 0);
        size_of_str = len+1;
        _str = new char[size_of_str];
        if (_str) {
            for (int i = len-1; i >= 0; i--) {
                _str[i] = char((tmp % 10) + 48);
                tmp /= 10;
            }
        }
        _str[len] = '\0';
        return *this;
    }

    String& String::operator=(const char* string){
        size_of_str = strlen(string)+1;
        _str = new char[size_of_str];
        if (_str) {
            for (int i = 0; i < size_of_str; i++) {
                _str[i] = string[i];
            }
        }
        return *this;
    }

    String& String::operator=(char* string){
        size_of_str = strlen(string)+1;
        _str = new char[size_of_str];
        if (_str) {
            for (int i = 0; i < size_of_str; i++) {
                _str[i] = string[i];
            }
        }
        return *this;
    }

    std::istream &operator>>(std::istream &is, String &str) {
        str.size_of_str = 80;
        char *p = str._str;
        str._str = new char[str.size_of_str];
        delete[] p;
        is >> str._str;
        str.size_of_str = strlen(str._str) + 1;
        p = str._str;
        str._str = new char[str.size_of_str];
        for(int i= 0; i < str.size_of_str - 1; i++){
            str._str[i] = p[i];
        }
        str._str[str.size_of_str-1] = '\0';
        delete[] p;
        return is;
    }

    std::ostream &operator<<(std::ostream &os, String &str) {
        os << str._str;
        return os;
    }

    void operator+(String &left, String &right) {
        char *p = new char[left.size_of_str + right.size_of_str - 1];
        if (*p) {
            for (auto &c: left) {
                if (c != '\0') {
                    *p = c;
                    p++;
                }
            }
        }
        for (auto &c: right) {
            *p = c;
            p++;
        }
        left.size_of_str += right.size_of_str - 1;
        p -= left.size_of_str;
        char *q = left._str;
        left._str = p;
        delete[] q;
    }

    bool operator==(String &left, String &right) {
        return !strcmp(left.get(), right.get());
    }

    bool operator!=(String &left, String &right) {
        return strcmp(left.get(), right.get());
    }

    bool operator>(String &left, String &right) {
        return strcmp(left.get(), right.get()) > 0;
    }

    bool operator<(String &left, String &right) {
        return strcmp(left.get(), right.get()) < 0;
    }
    /*****************************************************************************************************************/

}