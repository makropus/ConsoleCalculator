#pragma once
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;


//list<string> parseInput(int argNum, char *argValues[]);

//TODO дописать функцию отделающую скобки от строк и вставляющую их в список операндов и чисел как отдельное значение
float getNum(string strNum);
float operation(string a, string op, string b);

float compute(list<string> &commands, list<string>::iterator start, list<string>::iterator finish);

void trimBrackets (list<string> &data);

list<string> splitString(string str, char splitter = ' ') ;

/*
1.  Нарезать строку на операнды, скобки и числа (список задач = СЗ)
        1.1 Обработка некоректного ввода 
        1.2 Нарезка скобок 
2.  Проход по СЗ 4 раза по очерёдности операций: / * + -
        2.1 Захож в рекурсию при "("" и выход из рекурсии при ")" 
*/