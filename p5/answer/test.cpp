#include <iostream>
#include <cstdlib>
#include "dlist.h"

using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);

    ip = ilist.removeFront();
    if (*ip != 1)
        result = -1;
    delete ip;

    if (!ilist.isEmpty())
        result = -1;

    long re, im;
    bool flag = true;

    const char *str = "-3568+-6i";
    if (str[0] == '+')flag = false;
    char *end;
    re = strtol(str, &end, 10);
    if (errno || !(isdigit(*end) || *end == '+' || *end == '-'))flag = false;
    im = strtol(end, &end, 10);
    if (errno || *end != 'i' || *(end+1) != '\0')flag = false;


    cout << re << "\t" << im << "\t" << flag;

    return result;
}
