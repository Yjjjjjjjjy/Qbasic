#ifndef PROGRAM_H
#define PROGRAM_H

#include<list>
#include<QString>
#include<QDebug>
#include<calc.h>

using namespace std;


struct variable
{
    int value = 0;
    QString id = "";
};

struct NumState
{
    int num = 0;
    QString statement = "";
    bool flag = true;
};

class program
{
public:
    program();
    void parse(list<NumState>::iterator &itr);
    void gettree(list<NumState>::iterator &itr);
    void pro_clear();
    void pro_run();
    void push(QString s);
    bool getvalue(QString s);
    int answer;
    list<NumState> str;

    list<QString> print;
};

#endif // PROGRAM_H
