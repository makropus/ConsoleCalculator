#include "calc.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    string task = string(argv[1]);
    
    list<string> data = splitString(task);
    trimBrackets(data);
    float result;
    try
    {
        result =  compute(data, data.begin(), data.end());
    }
    catch(string wrongArg)
    {
        cout << "некорректный ввод, строка содержит недопустимое выражение " << wrongArg<< endl;
        return 0;
    }

    printf("Результат: %.2f\n", result);

    return 0; 
} 
