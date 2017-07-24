//
// Created by liu on 16-7-19.
//

#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Complex
{
private:
    long re, im;
    bool flag = true;
public:
    Complex(const char *str)
    {
        if (str[0] == '+')flag = false;
        char *end;
        re = strtol(str, &end, 10);
        if (errno || !(*end == '+' || *end == '-'))flag = false;
        im = strtol(end, &end, 10);
        if (errno || *end != 'i' || *(end+1) != '\0')flag = false;
    }

    Complex(const long &r, const long &i) : re(r), im(i)
    {}

    Complex operator+(const Complex &that) const
    {
        return Complex(this->re + that.re, this->im + that.im);
    }

    Complex operator-(const Complex &that) const
    {
        return Complex(this->re - that.re, this->im - that.im);
    }

    Complex operator-() const
    {
        return Complex(-this->re, -this->im);
    }

    Complex operator*(const Complex &that) const
    {
        return Complex(this->re * that.re - this->im * that.im, this->re * that.im + this->im * that.re);
    }

    explicit operator bool() const
    {
        return this->flag;
    }

    friend inline ostream &operator<<(ostream &out, const Complex &complex)
    {
        out << complex.re;
        if (complex.im >= 0)out << "+";
        out << complex.im << "i";
    }
};

template<typename T>
void two(char c, Dlist<T> &stack)
{
    T *a, *b;
    try
    {
        a = stack.removeBack();
    }
    catch (emptyList)
    {
        throw;
    }
    try
    {
        b = stack.removeBack();
    }
    catch (emptyList)
    {
        stack.insertBack(a);
        throw;
    }
    switch (c)
    {
        case '+':
            *b = *b + *a;
            delete a;
            break;
        case '-':
            *b = *b - *a;
            delete a;
            break;
        case '*':
            *b = *b * *a;
            delete a;
            break;
        case 'r':
            stack.insertBack(a);
            break;
        default:
            break;
    }
    stack.insertBack(b);
}

template<typename T>
void one(char c, Dlist<T> &stack)
{
    T *a;
    try
    {
        a = stack.removeBack();
    }
    catch (emptyList)
    {
        throw;
    }
    switch (c)
    {
        case 'n':
            *a = -(*a);
            break;
        case 'd':
        {
            auto b = new T(*a);
            stack.insertBack(b);
            break;
        }
        case 'p':
            cout << *a << endl;
            break;
        default:
            break;
    }
    stack.insertBack(a);
}

template<typename T>
void clear(Dlist<T> &stack)
{
    while (!stack.isEmpty())
    {
        auto back = stack.removeBack();
        delete back;
    }
}

template<typename T>
void print(const Dlist<T> &stack)
{
    Dlist<T> temp;
    temp = stack;
    while (!temp.isEmpty())
    {
        auto back = temp.removeBack();
        cout << *back << " ";
        delete back;
    }
    cout << endl;
}

bool input(string cmd, Dlist<Complex> &stack)
{
    if (cmd.length() == 1)
    {
        try
        {
            switch (cmd[0])
            {
                case 'q':
                    return false;
                case '+':
                case '-':
                case '*':
                case 'r':
                    two<Complex>(cmd[0], stack);
                    return true;
                case 'n':
                case 'd':
                case 'p':
                    one<Complex>(cmd[0], stack);
                    return true;
                case 'c':
                    clear<Complex>(stack);
                    return true;
                case 'a':
                    print<Complex>(stack);
                    return true;
                default:
                    if (cmd[0] < '0' || cmd[0] > '9')
                    {
                        cout << "Bad input\n";
                        return true;
                    }
            }
        }
        catch (emptyList)
        {
            cout << "Not enough operands\n";
            return true;
        }
    }
    auto temp = new Complex(cmd.c_str());
    if (*temp)
    {
        stack.insertBack(temp);
    }
    else cout << "Bad input\n";
    return true;
}

int main()
{
    string str;
    Dlist<Complex> stack;
    do
    {
        cin >> str;
    } while (input(str, stack));
    return 0;
}