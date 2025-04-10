#include "Header.h"


bool Matrix::checkMatrixExist(string matrixName)
{
    if (usersMatrix.count(matrixName) == 0) return false;

    return true;
}

bool Matrix::correctNumberMatrix(string& input)
{
    if (input.empty())
    {
        cout << "Ошибка: ввод не может быть пустым" << endl;
        return false;
    }

    if (input == "." or input == "-." or input == "," or input == "-,")
    {
        cout << "Ошибка: некорректный ввод '" << input << "', нельзя вводить '.', '-.', ',', '-,'" << endl;
        return false;
    }

    if (input.length() > 20)
    {
        cout << "Ошибка: число '" << input << "' слишком длинное (допустимо не более 20 символов)" << endl;
        return false;
    }

    for (char c : input)
    {
        if (isalpha(c))
        {
            cout << "Ошибка: введено некорректное значение, буквы не допускаются" << endl;
            return false;
        }
    }
    
    replace(input.begin(), input.end(), '.', ',');

    int posNotPlus = input.find_first_not_of('+');
    input.erase(0, posNotPlus);

    if (input.empty())
    {
        cout << "Ошибка: ввод не может состоять только из символов '+'" << endl;
        return false;
    }

    if (input == "-0" or input == "+0") input = '0';

    if (input[0] == ',')
    {
        input = '0' + input;
        return true;
    }

    if (input.find('-', 1) != string::npos)
    {
        cout << "Ошибка: минус может быть только в начале числа" << endl;
        return false;
    }

    bool hasDecimal = false;

    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i])) continue;
       
        if (input[i] == '-') continue;

        if (input[i] == ',')
        {
            if (hasDecimal)
            {
                cout << "Ошибка: дробная часть уже присутствует" << endl;
                return false;
            }
            hasDecimal = true;
            continue;
        }

        cout << "Ошибка: некорректный символ '" << input[i] << "'" << endl;
        return false;
    }

    return true;
}

bool Matrix::correctNameMatrix(string name)
{
    if (name.length() > 8) {
        cout << "Ошибка: имя матрицы '" << name << "' слишком длинное, имя матрицы не должно превышать 8 символов" << endl;
        return false;
    }

    regex pattern("^[A-Za-z][A-Za-z0-9]*$");
    return regex_match(name, pattern);
}

int Matrix::correctSizeMatrix(const string prompt)
{
    bool validNum;
    string input;

    do
    {
        validNum = true;
        cout << prompt;
        getline(cin, input);

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "back") return -1;

        if (input.empty())
        {
            cout << "Ошибка: ввод не может быть пустым" << endl;
            validNum = false;
            continue;
        }

        if (input.length() > 10)
        {
            cout << "Ошибка: значение '" << input << "' слишком длинное, размер матрицы не должен превышать 10 символов" << endl;
            validNum = false;
            continue;
        }

        if (input == "0")
        {
            cout << "Ошибка: размер матрицы не может быть равен '0'" << endl;
            validNum = false;
            continue;
        }

        for (int i = 0; i < input.size(); i++)
        {
            if (!isdigit(input[i]))
            {
                cout << "Ошибка: введите только целое число" << endl;
                validNum = false;
                break;
            }
        }
    } while (not validNum);

    return stoi(input);
}

bool Matrix::twoOperator(string oper)
{
    return (oper == "+" or oper == "-" or oper == "*");
}
