#include "calc.hpp"

list<string> opList ({"/", "*", "-", "+"});

/*
1.  Нарезать строку на операнды, скобки и числа (список задач = СЗ)
        1.1 Обработка некоректного ввода 
        1.2 Нарезка скобок 
2.  Проход по СЗ 4 раза по очерёдности операций: / * + -
        2.1 Захож в рекурсию при "("" и выход из рекурсии при ")" 
*/
float getNum(string strNum)
{
    replace(strNum.begin(), strNum.end(), ',', '.'); //поддержка ',' как разделителя
    try
    {
        return stof(strNum);
    }
    catch(const std::exception& e)
    {
        throw strNum;
    }
}

float operation(string a, string op, string b)
{
    switch (op[0])
    {
    case '/':
        return getNum(a) / getNum(b);
    case '*':
        return getNum(a) * getNum(b);
    case '-':
        return getNum(a) - getNum(b);
    case '+':
        return getNum(a) + getNum(b);     
    }
    return 0;
}

float compute(list<string> &commands, list<string>::iterator start, list<string>::iterator finish)
{
    float result = 0;
    for(auto it = start; it != finish;)
    {
        for (auto op : opList)
        {
            if ((*it).compare(op) == 0)
            {
                if ((*prev(it)).compare(")") == 0) //если первое(левое) значение скобки
                {//заходим в рекурсию для вычисления скобок
                    auto bracketBegin = it; // brackedEnd == prev(it)
                    int openBracketsCount = 1;
                    while (openBracketsCount != 0)
                    {
                        --bracketBegin;
                        if((*bracketBegin).compare(")") == 0) openBracketsCount++;
                        else                       
                        if ((*bracketBegin).compare("(") == 0) openBracketsCount--;   
                    }
                    float tmp = compute(commands, next(bracketBegin), prev(it));
                    commands.erase(bracketBegin, it); //удаляем всю скобку
                    commands.insert(it, to_string(tmp)); //вставляем значение скобки как первое(левое) значение
                }
                if ((*next(it)).compare("(") == 0) //если второе(правое) значение скобки 
                {
                    auto bracketEnd = next(it); 
                    int openBracketsCount = 1;
                    while (openBracketsCount != 0)
                    {   
                        ++bracketEnd;
                        if((*bracketEnd).compare("(") == 0) openBracketsCount++;
                        else                       
                        if ((*bracketEnd).compare(")") == 0) openBracketsCount--;                        
                    }
                    float tmp = compute(commands, next(next(it)), bracketEnd);
                    commands.erase(next(it), next(bracketEnd)); //удаляем всю скобку
                    commands.insert(next(it), to_string(tmp)); //вставляем значение скобки как первое(левое) значение
                }
                result = operation(*prev(it), op, *next(it));
                *it = to_string(result);
                commands.erase(prev(it));
                commands.erase(next(it));
            }
        }
        ++it;
    }
    return result;
}




//TODO дописать функцию отделающую скобки от строк и вставляющую их в список операндов и чисел как отдельное значение
void trimBrackets (list<string> &data)
{
    for (list<string>::iterator it = data.begin(); it != data.end(); ++it)
    {

        while ((*it).front() == '(')
        {             
            data.insert(it , "(" );
            (*it) = (*it).erase(0, 1);
  
        }

        while ((*it).back() == ')'  && (*it).size() != 1)
        {             
            data.insert(next(it) , ")" );
            (*it) = (*it).erase((*it).size() - 1, 1);
        }
    }   
}


list<string> splitString(string str, char splitter) 
{ 
    list<string> words;
    string tmp = ""; 
    for (int i = 0; i < str.size(); i++) 
    { 
        if (str[i] == splitter ) 
        { 
            if (tmp.compare("") != 0)
                words.push_back(tmp);            
            tmp = "";            
        } 
        else
            tmp = tmp + str[i]; 

        if (i == str.size() - 1  && tmp.compare("") != 0)
            words.push_back(tmp);  
    }
    return words; 
}


