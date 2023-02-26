#include "program.h"

extern list<variable> var;
extern list<QString> tree;


program::program()
{
    answer = 0;
}

void program::pro_run()
{
    list<NumState>::iterator itr3 = str.begin();
    list<NumState>::iterator itr4 = str.end();
    while(itr3!=itr4)
    {
        gettree(itr3);
    }
    list<NumState>::iterator itr1 = str.begin();
    list<NumState>::iterator itr2 = str.end();
    while(itr1!=itr2)
    {
        if(!(*itr1).flag) return;
        parse(itr1);
    }
}

void program::pro_clear()
{
    str.clear();
    tree.clear();
    var.clear();
    print.clear();
}

void program::push(QString s)
{
    int number = 0;
    int i = 0;
    while(true)
    {
        if(s.mid(i,1) == ' ' ) ++i;
        else break;
    }
    do{
        if(s.mid(i,1) >=  '0' && s.mid(i,1) <= '9') ++i;
        else break;
    }while(true);
    number = s.left(i).toInt();
    if(s.mid(i,1) == ' ') ++i;
    else return;
    do{
        if(s.mid(i,1) == ' ') ++i;
        else break;
    }while(true);
    s.remove(0,i);
    NumState temp;
    temp.num = number;
    temp.statement = s;

    list<NumState>::iterator itre = str.end();
    itre--;
    if(str.empty() || (*itre).num < number)
    {
        str.push_back(temp);
    }
    else
    {
        list<NumState>::iterator itr1 = str.begin();
        if((*itr1).num > number)
        {
            str.insert(itr1,temp);

        }
        list<NumState>::iterator itr2 = str.begin();
        ++itr2;
        list<NumState>::iterator itre = str.end();
        do
        {
         if((*itr1).num < number && (*itr2).num >number)
         {
             str.insert(itr2,temp);
             break;
         }
         else if((*itr1).num == number)
         {
             str.insert(itr2,temp);
             --itr2;
             --itr2;
             str.erase(itr2);
             break;
         }
         else
         {
             ++itr1;
             ++itr2;
         }
        }while (itr1 != itre);
    }
}

void program::parse(list<NumState>::iterator &itr)
{
    QString current = (*itr).statement;
    bool istrue = true;
    if( current.left(4)  == "REM " )
    {
        ++itr;
        return;
    }
    else if( current.left(4)  == "LET " )
    {
        int i = 4;
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        QString temp;
        do
        {
            if(current.mid(i,1) != ' ' && current.mid(i,1) != '=') temp += current.mid(i,1);
            else break;
            ++i;
        }while(true);
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        if(current.mid(i,1) == "=")
        {
            ++i;
            current.remove(0,i);
            istrue = getvalue(current);
            if(istrue)
            {
                variable TEMP;
                TEMP.id = temp;
                TEMP.value = answer;
                if(var.empty()) var.push_back(TEMP);
                else
                {
                    list<variable>::iterator itr1 = var.begin();
                    list<variable>::iterator itr2 = var.end();
                    while(itr1 != itr2)
                    {
                        if((*itr1).id == temp) break;
                        else ++itr1;
                    }
                    if(itr1 == itr2)
                    {
                        var.push_back(TEMP);
                    }
                    else
                    {
                        (*itr1).value = TEMP.value;
                    }
                }
                ++itr;
                return;
            }
        }
        else istrue = false;
    }
    else if( current.left(5)  == "GOTO " )
    {
        current.remove(0,5);
        current = current.simplified();
        int number = current.toInt(&istrue);
        if(istrue)
        {
            list<NumState>::iterator itr1 = str.begin();
            list<NumState>::iterator itr2 = str.end();
            while(itr1!=itr2)
            {
                if((*itr1).num != number) ++itr1;
                else break;
            }
            if((*itr1).num == number)
            {
                itr = itr1;
                return;
            }
            else istrue =false;
        }
    }
    else if( current.left(6)  == "PRINT " )
    {
        int i = 6;
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        current.remove(0,i);
        istrue = getvalue(current);
        if(istrue)
        {
            print.push_back(QString::number(answer));
            ++itr;
            return;
        }
    }
    else if( current.left(3) == "IF ")
    {
        QString Number = QString::number((*itr).num);
        bool flag = true;
        int Exp1;
        int Exp2;
        int i = 3;
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        QString exp1;
        QString exp2;
        QString Operator;
        do
        {
            if(current.mid(i,1) != ' ' && current.mid(i,1) != '=' && current.mid(i,1) != '>' && current.mid(i,1) != '<')
                exp1 += current.mid(i,1);
            else break;
            ++i;
        }while(true);
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        Operator = current.mid(i,1);
        ++i;
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        do
        {
            if(current.mid(i,1) != ' ' )
                exp2 += current.mid(i,1);
            else break;
            ++i;
        }while(true);
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        istrue = getvalue(exp1);
        if(istrue)
        {
            Exp1 = answer;
            istrue = getvalue(exp2);
            if(istrue)
            {
                Exp2 = answer;
                if((Operator == ">" && Exp1 > Exp2)||(Operator == "<" && Exp1 < Exp2)||(Operator == "=" && Exp1 == Exp2))
                    flag = true;
                else flag = false;
            }
        }
        if(istrue && flag)
        {
            if(current.mid(i,4) == "THEN")
            {
                i += 4;
                current.remove(0,i);
                int number = (current).toInt(&istrue);
                list<NumState>::iterator itr1 = str.begin();
                list<NumState>::iterator itr2 = str.end();
                while(itr1!=itr2)
                {
                    if((*itr1).num != number) ++itr1;
                    else break;
                }
                if((*itr1).num == number)
                {
                    itr = itr1;
                    return;
                }
                else istrue = false;
            }
            else istrue = false;
        }
        else if(istrue && (!flag))
        {
            ++itr;
            return;
        }
    }
    else if( current.left(6)  == "INPUT " )
    {

        int i = 6;
        while(true)
        {
            if(current.mid(i,1) == ' ' ) ++i;
            else break;
        }
        QString temp = current.remove(0,i);
        variable TEMP;
        TEMP.id = temp;


        TEMP.value = answer;


        list<variable>::iterator itr1 = var.begin();
        list<variable>::iterator itr2 = var.end();
        while(itr1 != itr2)
        {
            if((*itr1).id == temp) break;
            else ++itr1;
        }
        if( itr1 != itr2 )
        {
            var.push_back(TEMP);
        }
        else
        {
            (*itr1).value = answer;
        }
    }
    else if( current == "END")
    {
        itr = str.end();
        return;
    }
    else istrue =false;
    if(!istrue)
    {
        itr = str.end();
    }
}

bool program::getvalue(QString s)
{
    s=s.simplified();
    bool flag;
    answer = s.toInt(&flag);
    if(flag) return true;
    if(!var.empty())
    {
        list<variable>::iterator itr1 = var.begin();
        list<variable>::iterator itr2 = var.end();
        while(itr1 != itr2)
        {

            if((*itr1).id == s)
            {
                answer = (*itr1).value;
                return true;
            }
            else ++itr1;
        }
    }

    QString temp = s;
    calc exp(temp);
    answer = exp.result();
    return true;
}

void program::gettree(list<NumState>::iterator &itr)
{
    QString current = (*itr).statement;
    bool istrue = true;
    if( current.left(4)  == "REM " )
    {
        tree.push_back(QString::number((*itr).num) + " REM");
        current.remove(0,4);
        current = current.simplified();
        tree.push_back("    " + current);
        ++itr;
        return;
    }
    else if( current.left(4)  == "LET " )
    {
        current.remove(0,4);
        current = current.simplified();     
        QString temp;
        do
        {
            if(current.left(1) != ' ' && current.left(1) != '=')
            {
                temp += current.left(1);
                current.remove(0,1);
            }
            else break;
        }while(true);
        current = current.simplified();
        if(current.left(1) == '=')
        {
            current.remove(0,1);
            current = current.simplified();
            tree.push_back(QString::number((*itr).num) + " LET =");
            tree.push_back("    " + temp);
            int number = current.toInt(&istrue);
            if(istrue)
            {
                tree.push_back("    " + current);
            }
            else
            {
                if(!current.contains("+") && !current.contains("-") && !current.contains("*") && !current.contains("/") && !current.contains("**"))
                {
                    tree.push_back("    " + current);
                }
                else
                {
                    calc s(current);
                    s.Tree();
                }
            }
            ++itr;
            return;
        }
        else istrue = false;
    }
    else if( current.left(5)  == "GOTO " )
    {
        current.remove(0,5);
        current = current.simplified();
        int number = current.toInt(&istrue);
        if(istrue)
        {
            tree.push_back(QString::number((*itr).num)+ " GOTO");
            tree.push_back("     " + QString::number(number));
            ++itr;
            return;
        }
    }
    else if( current.left(6)  == "PRINT " )
    {
        current.remove(0,6);
        current = current.simplified();
        tree.push_back(QString::number((*itr).num) + " PRINT");
        int number = current.toInt(&istrue);
        if(istrue)
        {
            tree.push_back("    " + current);
        }
        else
        {
            if(!current.contains("+") && !current.contains("-") && !current.contains("*") && !current.contains("/") && !current.contains("**"))
            {
                tree.push_back("    " + current);
            }
            else
            {
                calc s(current);
                s.Tree();
            }
        }
        ++itr;
        return;
    }
    else if( current.left(3) == "IF ")
    {
        current.remove(0,3);
        current = current.simplified();
        QString exp1;
        QString exp2;
        QString Operator;
        do
        {
            if(current.left(1) != ' ' && current.left(1) != '=' && current.left(1) != '>' && current.left(1) != '<')
            {
                exp1 += current.left(1);
                current.remove(0,1);
            }
            else break;
        }while(true);
        current = current.simplified();
        Operator = current.left(1);
        if(Operator == '>' || Operator == '=' || Operator == '<')
        {
            current.remove(0,1);
            current = current.simplified();
            do
            {
                if(current.left(1) != ' ' )
                {
                    exp2 += current.left(1);
                    current.remove(0,1);
                }
                else break;
            }while(true);
            current = current.simplified();
            if(current.left(5) == "THEN ")
            {
                current.remove(0,5);
                current = current.simplified();
                int number = current.toInt(&istrue);

                if(!current.isEmpty() && istrue)
                {
                    tree.push_back(QString::number((*itr).num) + " IF THEN");
                    tree.push_back("    " + exp1);
                    tree.push_back("    " + Operator);
                    tree.push_back("    " + exp2);
                    tree.push_back("    " + current);
                    ++itr;
                    return;
                }
            }
            else istrue = false;

        }
        else istrue = false;
    }
    else if( current.left(6)  == "INPUT " )
    {
        ++itr;
        return;
    }
    else if( current == "END")
    {
        ++itr;
        return;
    }
    if(!istrue)
    {
        tree.push_back(QString::number((*itr).num)+ " ERROR");
        (*itr).flag = false;
    }
    ++itr;

}


