#ifndef CALC_H
#define CALC_H


#include<iostream>
#include<QString>
#include<QDebug>
#include"program.h"



class calc
{

    enum Type{DATA,ADD,SUB,MULTI,DIV,OPAREN,CPAREN,EOL,VAR};
    struct node
    {
        Type type;
        int data;
        node *lchild,*rchild;
        QString Name;
        node(Type t, int d = 0,QString n = "", node *lc = NULL,node *rc = NULL)
        {type = t; data = d; Name=n; lchild = lc; rchild =rc;}
    };

    node *root;
    node *creat(QString &s);
    Type getToken(QString &s,int &value,QString &Name);
    int result(node *t);


public:
    calc (QString s){root = creat(s);}
    int result()
    {
        if(root == NULL) return 0;
        return result(root);
    }
    void Tree();
};

#endif // CALC_H
