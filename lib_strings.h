# pragma once

#include <exception>
#include <iostream>
#include <cstring>

namespace lib_strings {

    typedef unsigned long size_t;

    class TCharArray {
    protected:
        size_t size_of_str = 0; // array max_len
        char *_str = nullptr;   // array pointer
    public:
        // Constructor
        TCharArray();
        explicit TCharArray(const char *string);
        explicit TCharArray(int digit);
        // Destructor
        virtual ~TCharArray();

        // Overloads
        char *begin();

        char *end();

        char &at(size_t index);

        virtual char &operator[](size_t index);
    };

    class String : public TCharArray {
    private:
    public:
        // Constructor
        String();
        String(const char *string);
        explicit String(int digit);

        // Getter/Setter

        const char* get();

        size_t get_size();

        //void set(const char *arg);

        // Overloads
        String& operator=(int digit);
        String& operator=(const char* string);
        String& operator=(char* string);
        friend std::istream &operator>>(std::istream &is, String &str);

        friend std::ostream &operator<<(std::ostream &os, String &str);

        friend void operator+(String &left, String &right);

        friend bool operator==(String &left, String &right);

        friend bool operator!=(String &left, String &right);

        friend bool operator>(String &left, String &right);

        friend bool operator<(String &left, String &right);
    };
}
