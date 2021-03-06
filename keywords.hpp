#ifndef KEYWORDS_HPP
#define KEYWORDS_HPP

#include <iostream>
#include <vector>
#include "token.hpp"
#include "functions.hpp"
#include "runtime.hpp"

int __command_pop(std::vector<Token> tokens, int i)
{
    Runtime.stack_pop();
	return 0;
}

int __command_size(std::vector<Token> tokens, int i)
{
    Runtime.stack_push(Runtime.stack[Runtime.stack_index].size());
	return 0;
}

int __command_type(std::vector<Token> tokens, int i)
{
	StackElement se = Runtime.stack_peek();
	StackElement code = StackElement("code", true, false, false);
	StackElement integer = StackElement("integer", true, false, false);
	StackElement string = StackElement("string", true, false, false);
	StackElement word = StackElement("word", true, false, false);
	StackElement unknown = StackElement("unknown", true, false, false);

	if (se.isCode())
		Runtime.stack_push(code);
	else if (se.isInt())
		Runtime.stack_push(integer);
	else if (se.isString())
		Runtime.stack_push(string);
	else if (se.isWord())
		Runtime.stack_push(word);
	else Runtime.stack_push(unknown);
	return 0;
}

int __command_file(std::vector<Token> tokens, int i)
{
	int mode = 0; /*
					0 -> Read File
					1 -> Append File Content
					2 -> Write File
					3 -> Delete File
					4 -> Exists File
				  */

	StackElement fmode = Runtime.stack_peek();
	StackElement file = Runtime.stack_peek();
	StackElement content;

	std::ifstream inf;
	std::ofstream of;

	if (!fmode.isInt())
	{
		std::cout << "error: file: mode: filemode must be an integer (\"" << fmode.getStr() << "\" is not)!" << std::endl;
		exit(1);
	}
	else mode = fmode.getInt();

	if (!file.isString())
	{
		std::cout << "error: file: mode: filemode must be an string (\"" << fmode.getStr() << "\" is not)!" << std::endl;
		exit(1);
	}

	switch (mode)
	{
		case 0: // Read File
			inf.open(file.getStr());
			Runtime.stack_push(StackElement(std::string((std::istreambuf_iterator<char>(inf)), std::istreambuf_iterator<char>())));
			break;
		case 1: // Append File Content
			of.open(file.getStr(), std::ios::app | std::ios::out);
			of << Runtime.stack_peek().getStr();
			break;
		case 2: // Write/Replace Complete File
			remove(file.getStr().c_str());
			of.open(file.getStr());
			of << Runtime.stack_peek().getStr();
			break;
		case 3: // Delete File
			if (remove(file.getStr().c_str()) != 0)
			{
				std::cout << "error: file: file " << file.getStr() << " not found!" << std::endl;
				exit(1);
			}
			break;
		case 4: // Exists File
			if (std::ifstream(file.getStr()).is_open())
				Runtime.stack_push(StackElement(1));
			else
				Runtime.stack_push(StackElement(0));
			break;
		default:
			std::cout << "error: file: unknown mode: " << mode << std::endl;
			exit(1);
			break;
	}

	return 0;
}


int __command_while(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.isCode() && e2.isCode())
    {
        std::vector<Token> tokens = Lexer.lex({e2.getStr()});
        std::vector<Token> tokens2 = Lexer.lex({e1.getStr()});

        while (true)
        {
            Executor.execute(tokens, false, false);
            StackElement e = Runtime.stack_peek();

            if (!e.isInt())
            {
                std::cout << "error: while: \"" << e.getStr() << "\" must be an integer (0 or 1/false or true)!" << std::endl;
            }

            if (e.getInt() == 1)
                Executor.execute(tokens2, true, false);
            else
                break;


            if (Runtime._break)
            {
                Runtime._break = false;
                return 0;
            }
        }
    }
    else
    {
        if (!e1.isCode())
            std::cout << "error: while: can't run \"" << e1.getStr() << "\": is no code-scope!" << std::endl;
        else
            std::cout << "error: while: can't run \"" << e2.getStr() << "\": is no code-scope!" << std::endl;
        exit(1);
    }
	return 0;

}

int __command_swap(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    Runtime.stack_push(e1);
    Runtime.stack_push(e2);
	return 0;
}

int __command_dup(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    Runtime.stack_push(e1);
    Runtime.stack_push(e1);
	return 0;
}

int __command_func(std::vector<Token> tokens, int i)
{
    StackElement name = Runtime.stack_peek();
    StackElement content = Runtime.stack_peek();

    if (name.isWord() && content.isCode())
    {
        Functions.addFunction(name.getStr(), Lexer.lex({content.getStr()}));
        // std::cout << "\nFunction \"" << name.getStr() << "\" created!" << std::endl;
    }
    else
    {
        if (!name.isWord())
            std::cout << "error: func: wrong syntax: \"" << name.getStr() << "\" must be a word!" << std::endl;
        else
            std::cout << "error: func: wrong syntax: \"" << content.getStr() << "\" must be a code-scope!" << std::endl;

        exit (1);
    }
	return 0;
}

int __command_rep(std::vector<Token> tokens, int i)
{
    StackElement content = Runtime.stack_peek();
    StackElement repeat = Runtime.stack_peek();

    if (!content.isCode())
    {
        std::cout << "error: rep: can't run content " << content.getStr() << ": is no code-scope!" << std::endl;
        exit(1);
    }
    else if (!repeat.isInt())
    {
        std::cout << "error: rep: can't repeat " << repeat.getStr() << " times: is no integer!" << std::endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < repeat.getInt(); i++)
        {
            Executor.execute(Lexer.lex({content.getStr()}), true, false);
        }
    }
	return 0;
}

int __command_out(std::vector<Token> tokens, int i)
{
    // std::cout.precision(10);
    // std::cout.setf(std::ios::fixed);

    StackElement se = Runtime.stack_peek();


    if (!Runtime.debug)
    {
        if (se.isInt())
        {
            long long i2 = se.getInt();
            long double i = se.getInt();
            // std::cout << "?=" << i2 << "/" << se.getInt() << std::endl;

            if (se.isInt() < 0)
            {
                i *= -1;
            }

            if ((i - i2) < 0.000001)
            {
                std::cout.unsetf(std::ios::fixed);
                std::cout << std::noshowpoint << i;
            }
            else
            {
                std::cout << std::fixed << i;
                std::cout.unsetf(std::ios::fixed);
            }
        }
        else
            std::cout << se.getStr();
    }

    if (Runtime.debug)
    {
        std::cout << "\nOUT   >> \"";
        std::cout << "\"" << std::endl << std::endl;
    }
	return 0;
}

int __command_outl(std::vector<Token> tokens, int i)
{
    std::cout.unsetf(std::ios::scientific);
    std::cout.unsetf(std::ios::floatfield);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(5);

    StackElement se = Runtime.stack_peek();
    //std::cout << se.getTypeStr() << std::endl;

    if (Runtime.debug)
    {
        std::cout << "\nOUTL  >> \"";
        std::cout << se.getStr() << "\"\n" << std::endl;
    }

    if (!Runtime.debug)
    {
        if (se.isInt())
        {
            long long i2 = se.getInt();
            long double i = se.getInt();
            // std::cout << "?=" << i2 << "/" << se.getInt() << std::endl;

            if (se.isInt() < 0)
            {
                i *= -1;
            }

            if ((i - i2) < 0.000001)
            {
                std::cout.unsetf(std::ios::fixed);
                std::cout << std::noshowpoint << i << std::endl;
            }
            else
            {
                std::cout << std::fixed << i << std::endl;
                std::cout.unsetf(std::ios::fixed);
            }
        }
        else
            std::cout << se.getStr() << std::endl;
    }

	return 0;
}

int __command__if(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.isCode() && e2.isInt())
    {
        if (e2.getInt() == 1)
            Executor.execute(Lexer.lex({e1.getStr()}), false, false);
    }
    else
    {
        if (!e1.isCode())
            std::cout << "error: if: can't run \"" << e1.getStr() << "\": is no code-scope!" << std::endl;
        else
            std::cout << "error: if: \"" << e2.getStr() << "\" must be a number (0 or 1/false or true)!" << std::endl;
        exit(1);
    }

	return 0;
}

int __command__else(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.isCode() && e2.isInt())
    {
        if (e2.getInt() == 0)
            Executor.execute(Lexer.lex({e1.getStr()}), false, false);
    }
    else
    {
        if (!e1.isCode())
            std::cout << "error: else: can't run \"" << e1.getStr() << "\": is no code-scope!" << std::endl;
        else
            std::cout << "error: else: \"" << e2.getStr() << "\" must be a number (0 or 1/false or true)!" << std::endl;
        exit(1);
    }

	return 0;
}

int __command_run(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();

    if (se.isWord())
        Functions.runFunction(se.getStr());
    else if (se.isCode())
        Executor.execute(Lexer.lex({se.getStr()}), false, false);
    else
    {
        std::cout << "error: run: can't run \"" << se.getStr() << "\": it's not a word and not a code-scope" << std::endl;
        exit(1);
    }

    // if (se.isWord())
    //     std::cout << Functions.getContent(se.getStr()) << std::endl << std::endl;

	return 0;
}

int __command_set(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();
    StackElement val = Runtime.stack_peek();

    if (se.isWord())
    {
        Variables.setVariable(std::string("$"+se.getStr()), val);
    }
    else
    {
        std::cout << "error: set: \"" << se.getStr() << "\" must be a word" << std::endl;
    }

	return 0;
}

int __command_inp(std::vector<Token> tokens, int i)
{
    std::string s;
    std::getline(std::cin, s);

    if (Runtime.is_number(s))
        Runtime.stack_push(StackElement(std::stoi(s)));
    else
        Runtime.stack_push(StackElement(s));

		return 0;
}

int __command_pick(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();

    if (se.isInt())
        Runtime.stack_push(Runtime.stack_peek_at(se.getInt()));
    else
    {
        std::cout << "error: pick: integer expected, found " << se.getTypeStr() << std::endl;
        exit(1);
    }

	return 0;
}

int __command_index(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();

    if (Runtime.debug)
        std::cout << "INDEX: current stack = stack " << se.getStr() << std::endl;

    if (se.isInt())
        Runtime.set_stack_index(se.getInt());
    else
    {
        std::cout << "error: index: integer expected, found " << se.getTypeStr() << std::endl;
        exit(1);
    }

	return 0;
}

int __command_charr(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();

    if (se.isString())
    {
        for (char c : se.getStr())
        {
            std::string p = "";
            p += c;

            if (Runtime.debug)
                std::cout << "charr: push(" << se.getStr() << "/" << c << "): " << p << std::endl;

            Runtime.stack_push(StackElement(p, false, false, false));
        }


        Runtime.stack_push(StackElement(se.getStr().size()));
    }
    else
    {
        std::cout << "error: charr: string expected, found " << se.getTypeStr() << std::endl;
        exit(1);
    }

	return 0;
}
#endif
