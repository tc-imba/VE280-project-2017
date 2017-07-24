//
// Created by liu on 2016/7/19.
//

#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum STATUS
{
    PLATINUM, GOLD, SILVER, REGULAR,
};

const char *STATUS_STR[] = {"platinum", "gold", "silver", "regular"};

struct Customer
{
    string name;
    int hangup;
    int duration;
};

STATUS getStatus(const string &str)
{
    for (int i = 0; i < 4; i++)
    {
        if (str == STATUS_STR[i])
        {
            return STATUS(i);
        }
    }
}

int main()
{
    int num, time_next = 0;
    Dlist<Customer> *customer[4] = {};
    for (int i = 0; i < 4; i++)customer[i] = new Dlist<Customer>;
    cin >> num;
    if (num > 0)
    {
        num--;
        cin >> time_next;
    } else
    {
        time_next = -1;
    }
    int time = 0, end = 0;
    while (true)
    {
        cout << "Starting tick #" << time << endl;

        for (int i = 0; i < 4; i++)
        {
            auto temp = new Dlist<Customer>;
            while (!customer[i]->isEmpty())
            {
                auto c = customer[i]->removeFront();
                if (c->hangup == time)
                {
                    cout << c->name << " hangs up\n";
                    delete c;
                } else
                {
                    temp->insertFront(c);
                }
            }
            delete customer[i];
            customer[i] = temp;
        }

        while (time == time_next && num >= 0)
        {
            auto temp = new Customer;
            cin >> temp->name;
            string str;
            cin >> str;
            auto status = getStatus(str);
            cin >> temp->hangup >> temp->duration;
            temp->hangup += time;
            customer[status]->insertBack(temp);
            cout << "Call from " << temp->name << " a " << STATUS_STR[status] << " member" << endl;
            num--;
            if (num >= 0)
            {
                cin >> time_next;
            }
        }
        if (end > time)
        {
            time++;
            continue;
        }
        Customer *temp = NULL;
        for (int i = 0; i < 4; i++)
        {
            if (!customer[i]->isEmpty())
            {
                temp = customer[i]->removeFront();
                break;
            }
        }
        if (temp)
        {
            cout << "Answering call from " << temp->name << endl;
            end += temp->duration;
            delete temp;
        } else if (time == end)
        {
            break;
        }
        time++;
    }
    for (int i = 0; i < 4; i++)delete customer[i];
    return 0;
}