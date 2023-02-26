#include "calc.h"
//#include "mainwindow.h"
#include <queue>

list<variable> var;
extern list<QString> tree;

calc::node *calc::creat(QString &s)
{
    s.remove(QRegExp("\\s"));
    calc::node *p, *root = NULL;
    Type returnType;
    int value;
    QString Name;
    while(!s.isEmpty())
    {
        returnType = calc::getToken(s,value,Name);
        switch (returnType)
        {

            case DATA: case OPAREN:case VAR:
                if(returnType == DATA) p = new calc::node(DATA,value);
                else if(returnType == VAR) p =new calc::node(VAR,value,Name);
                else p = creat(s);
                if(root!=NULL)
                {
                    if(root->rchild == NULL) root->rchild = p;
                    else root->rchild->rchild = p;
                }
            break;
            case CPAREN: case EOL: return root;
            case ADD: case SUB:
                 if(root == NULL) root = new node(returnType,0,"",p);
                 else root = new node(returnType,0,"",root);
            break;
            case MULTI: case DIV:
                if(root == NULL) root = new node(returnType,0,"",p);
                else if(root->type == MULTI || root->type == DIV) root = new node(returnType,0,"",root);
            else root->rchild = new node(returnType,0,"",root->rchild);
        }
    }
    return root;
}

calc::Type calc::getToken(QString &s, int &data,QString &Name)
{
    QString type;
    if(s.isEmpty()) return EOL;
    while(s.left(1) == ' ') s.remove(0,1);
    if((s.left(1)>='a'&&s.left(1)<='z')||(s.left(1)>='A'&&s.left(1)<='Z'))
    {
        QString ID;
        ID.clear();
        data = 0;
        while((s.left(1)>='a'&&s.left(1)<='z')||(s.left(1)>='A'&&s.left(1)<='Z')||(s.left(1) >= '0' && s.left(1) <= '9'))
        {
            ID = ID + s.left(1);
            s.remove(0,1);
        }

        list<variable>::iterator itr1 = var.begin();
        list<variable>::iterator itr2 = var.end();
        while(itr1 != itr2)
        {

            if((*itr1).id == ID)
            {
                data = (*itr1).value;
                break;
            }
             else ++itr1;
        }
            Name = ID;
            return VAR;
    }
    if(s.left(1) >= '0' && s.left(1) <= '9')
    {
        data = 0;
        while(s.left(1) >= '0' && s.left(1) <= '9')
        {
            data = data * 10 + s.left(1).toInt();
            s.remove(0,1);
        }
        return DATA;
    }
    type = s.left(1);
    s.remove(0,1);
    if(type == '+') return ADD;
    else if(type == '-') return SUB;
    else if(type == '*') return MULTI;
    else if(type == '/') return DIV;
    else if(type == '(') return OPAREN;
    else if(type == ')') return CPAREN;
    else return EOL;
}

int calc::result(node *t)
{
    if(t->type == DATA || t->type == VAR) return t->data;
    int n1,n2;
    n1 = result(t->lchild);
    n2 = result(t->rchild);
    if(t->type == ADD) t->data = n1 + n2;
    else if(t->type == SUB) t->data = n1 - n2;
    else if(t->type == MULTI) t->data = n1 * n2;
    else if(t->type == DIV) t->data = n1 / n2;
    return t->data;
}

void calc::Tree()
{
    queue<node *>que;
    node *tmp;
    QString Temp;
    QString blank = "    ";
    int i = 0;
    que.push(root);
    while(!que.empty())
    {
        tmp = que.front();
        if(tmp->type == ADD) Temp = "+";
        else if(tmp->type == VAR) Temp = tmp->Name;
        else if(tmp->type == SUB) Temp = "-";
        else if(tmp->type == MULTI) Temp = "*";
        else if(tmp->type == DIV) Temp = "/";
        else if(tmp->type == DATA) Temp = QString::number(tmp->data);
        que.pop();
        tree.push_back(blank + Temp);
        ++i;
        if( i%2 == 1 ) blank += "    ";
        Temp.clear();
        if(tmp->lchild) que.push(tmp->lchild);
        if(tmp->rchild) que.push(tmp->rchild);
    }
}
