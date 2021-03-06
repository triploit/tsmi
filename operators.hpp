#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <iostream>
#include <math.h>
#include "functions.hpp"
#include "runtime.hpp"

void __command_equals(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        if (e1.getInt() == e2.getInt())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr() == e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr() == e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr() == e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr() == e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else
    {
        std::cout << "error: operator==: can't check " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }

    Runtime.stack_push(StackElement(0));
}

void __command_not_equals(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        if (e1.getInt() != e2.getInt())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr() != e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr() != e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr() != e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr() != e2.getStr())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else
    {
        std::cout << "error: operator!=: can't check " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }

    Runtime.stack_push(StackElement(0));
}

void __command_add(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        Runtime.stack_push(StackElement(e1.getInt()+e2.getInt()));
        return;
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "STRING")
    {
        Runtime.stack_push(StackElement(e1.getStr()+e2.getStr()));
        return;
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "WORD")
    {
        Runtime.stack_push(StackElement(e1.getStr()+e2.getStr(), true));
        return;
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "STRING")
    {
        Runtime.stack_push(StackElement(e1.getStr()+e2.getStr()));
        return;
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "WORD")
    {
        Runtime.stack_push(StackElement(e1.getStr()+e2.getStr()));
        return;
    }
    else
    {
        std::cout << "error: operator+: can't add " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }
}

void __command_sub(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        Runtime.stack_push(StackElement(e1.getInt()-e2.getInt()));
        return;
    }
    else
    {
        std::cout << "error: operator-: can't sub " << e1.getTypeStr() << " from " << e2.getTypeStr() << std::endl;
        exit(1);
    }
}

void __command_mul(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        Runtime.stack_push(StackElement(e1.getInt()*e2.getInt()));
        return;
    }
    else
    {
        std::cout << "error: operator*: can't mult " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }
}

void __command_div(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        Runtime.stack_push(StackElement(e1.getInt()/e2.getInt()));
        return;
    }
    else
    {
        std::cout << "error: operator/: can't div " << e1.getTypeStr() << " from " << e2.getTypeStr() << std::endl;
        exit(1);
    }
}

void __command_mod(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        Runtime.stack_push(StackElement(fmod(e1.getInt(),e2.getInt())));
        return;
    }
    else
    {
        std::cout << "error: operator%: can't modulo " << e1.getTypeStr() << " from " << e2.getTypeStr() << std::endl;
        exit(1);
    }
}

void __command_less(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        if (e1.getInt() < e2.getInt())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() < e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() < e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() < e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() < e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else
    {
        std::cout << "error: operator<: can't check " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }

    Runtime.stack_push(StackElement(0));
}

void __command_greater(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        if (e1.getInt() > e2.getInt())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() > e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() > e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() > e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() > e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else
    {
        std::cout << "error: operator>: can't check " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }

    Runtime.stack_push(StackElement(0));
}

void __command_less_or_equals(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        if (e1.getInt() <= e2.getInt())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() <= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() <= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() <= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() <= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else
    {
        std::cout << "error: operator<=: can't check " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }

    Runtime.stack_push(StackElement(0));
}

void __command_greater_or_equals(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.getTypeStr() == "INT" && e2.getTypeStr() == "INT")
    {
        if (e1.getInt() >= e2.getInt())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() >= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() >= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "WORD" && e2.getTypeStr() == "STRING")
    {
        if (e1.getStr().size() >= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else if (e1.getTypeStr() == "STRING" && e2.getTypeStr() == "WORD")
    {
        if (e1.getStr().size() >= e2.getStr().size())
        {
            Runtime.stack_push(StackElement(1));
            return;
        }
    }
    else
    {
        std::cout << "error: operator>=: can't check " << e1.getTypeStr() << " and " << e2.getTypeStr() << std::endl;
        exit(1);
    }

    Runtime.stack_push(StackElement(0));
}


#endif
