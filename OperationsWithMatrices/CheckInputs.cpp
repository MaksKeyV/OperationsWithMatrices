#include "Header.h"

// Функция для проверки существования матрицы по имени
// matrixName – имя матрицы
bool Matrix::checkMatrixExist(string matrixName)
{
    // Проверка, есть ли матрица с таким именем
    if (usersMatrix.count(matrixName) == 0) return false;

    return true;
}

// Функция для проверки корректности числового ввода
// input – ввод пользователя
bool Matrix::correctNumberMatrix(string& input)
{
    if (input.empty())
    {
        cout << "Ошибка: ввод не может быть пустым" << endl;
        return false;
    }

    if (input == "." or input == "-." or input == "," or input == "-,")
    {
        cout << "Ошибка: некорректный ввод '" << input << "', нельзя вводить только '.', '-.', ',', '-,'" << endl;
        return false;
    }

    if (input.length() > 20)
    {
        cout << "Ошибка: число '" << input << "' слишком длинное (допустимо не более 20 символов)" << endl;
        return false;
    }

    // Проверка на наличие букв
    for (int i = 0; i < input.size(); i++)
    {
        if (isalpha(input[i]))
        {
            cout << "Ошибка: введено некорректное значение, буквы не допускаются" << endl;
            return false;
        }
    }
    
    // Замена точки на запятую
    replace(input.begin(), input.end(), '.', ',');

    // Убираем символы '+' в начале
    int posNotPlus = input.find_first_not_of('+');
    input.erase(0, posNotPlus);

    // Если ввод состоит только из знаков '+', выводим ошибку
    if (input.empty())
    {
        cout << "Ошибка: ввод не может состоять только из символов '+'" << endl;
        return false;
    }

    if (input == "-0" or input == "+0") input = '0';

    // Если строка начинается с запятой, добавляем ведущий ноль
    if (input[0] == ',')
    {
        input = '0' + input;
        return true;
    }

    // Минус разрешён только в начале
    if (input.find('-', 1) != string::npos)
    {
        cout << "Ошибка: минус может быть только в начале числа" << endl;
        return false;
    }

    // Флаг наличия запятой
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

// Функция для проверки корректности имени матрицы
// name – имя матрицы
bool Matrix::correctNameMatrix(string name)
{
    if (name.length() > 8) {
        cout << "Ошибка: имя матрицы '" << name << "' слишком длинное, имя матрицы не должно превышать 8 символов" << endl;
        return false;
    }

    // Проверка, что имя состоит только из букв и цифр, начинается с буквы
    regex pattern("^[A-Za-z][A-Za-z0-9]*$");
    return regex_match(name, pattern);
}

// Функция для проверки корректности размера матрицы
// str – сообщение-подсказка
int Matrix::correctSizeMatrix(const string str)
{
    // Флаг для проверки корректности ввода
    bool validNum;
    string input;

    // Цикл, пока не будет корректный ввод
    do
    {
        validNum = true;
        cout << str;
        getline(cin, input);

        // Перевод в нижний регистр
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "back") return -1;

        if (input.empty())
        {
            cout << "Ошибка: ввод не может быть пустым" << endl;
            validNum = false;
        }

        if (input.length() > 10)
        {
            cout << "Ошибка: значение '" << input << "' слишком длинное, размер матрицы не должен превышать 10 символов" << endl;
            validNum = false;
        }

        if (input == "0")
        {
            cout << "Ошибка: размер матрицы не может быть равен '0'" << endl;
            validNum = false;
        }

        // Проверка, что введено только целое число
        if (not all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "Ошибка: введите только целое число" << endl;
            validNum = false;
        }
    } while (not validNum);

    // Возвращаем размер матрицы, преобразованный в число
    return stoi(input);
}

// Функция для проверки, требует ли операция двух операндов
// oper – оператор
bool Matrix::twoOperator(string oper)
{
    return (oper == "+" or oper == "-" or oper == "*");
}
