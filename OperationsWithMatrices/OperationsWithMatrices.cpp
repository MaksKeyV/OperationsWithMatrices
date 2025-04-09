
#include "Header.h"

string Matrix::inputNameMatrix(bool fladOutMsg)
{
    string matrixName;

    do
    {
        if (fladOutMsg) cout << "Введите название матрицы или команду 'back', чтобы вернуться в меню" << endl;

        cout << "Имя должно начинаться с латинской буквы и может содержать цифры" << endl;
        cout << "Введите имя матрицы: ";
        getline(cin, matrixName);

        transform(matrixName.begin(), matrixName.end(), matrixName.begin(), ::tolower);

        if (not correctNameMatrix(matrixName))
        {
            system("cls");
            cout << "Ошибка: имя матрицы должно начинаться с латинской буквы и может содержать цифры" << endl << endl;
        }
    } while (not correctNameMatrix(matrixName));

    return matrixName;
}

void Matrix::inputMatrix()
{
    string matrixName = inputNameMatrix(true);

    if (matrixName == "back")
    {
        system("cls");
        return;
    }

    int row = correctSizeMatrix("Введите количество строк: ");
    int collum = correctSizeMatrix("Введите количество столбцов: ");

    vector<vector<double>> matrix(row, vector<double>(collum));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < collum; j++)
        {
            string input;
            bool validInput = false;

            while (!validInput)
            {
                cout << "Введите " << matrixName << "[" << i + 1 << "][" << j + 1 << "]: ";
                getline(cin, input);

                if (correctNumberMatrix(input))
                {
                    matrix[i][j] = stod(input);

                    validInput = true;
                }
                else
                {
                    cout << "Ошибка: введите корректное число" << endl;
                }
            }
        }
    }

    usersMatrix[matrixName] = matrix;

    system("cls");
    cout << "Введенная матрица '" << matrixName << "':" << endl;
    MatrixOut(matrix);
    cout << endl;
}

void Matrix::deleteMatrix()
{
    if (usersMatrix.empty())
    {
        cout << "Нет сохраненных матриц" << endl << endl;
        return;
    }

    cout << "Существующие пользовательские матрицы" << endl;
    outputAllMatrix();

    string matrixName = inputNameMatrix(true);

    system("cls");

    if (matrixName == "back") return;

    if (checkMatrixExist(matrixName))
    {
        usersMatrix.erase(matrixName);
        cout << "Матрица '" << matrixName << "' была удалена" << endl << endl;
    }
    else  cout << "Ошибка: матрица с именем '" << matrixName << "' не найдена" << endl << endl;
}

string Matrix::inputMatrixOperand(string strOperand)
{
    string matrixName;

    bool correctInput = true;

    do
    {
        cout << strOperand << ": ";
        getline(cin, matrixName);

        transform(matrixName.begin(), matrixName.end(), matrixName.begin(), ::tolower);

        if (matrixName == "back") return "back";

        if (all_of(matrixName.begin(), matrixName.end(), [](char s) { return isdigit(s) || s == '.' || s == ',' || s == '-'; }))
        {
            if (correctNumberMatrix(matrixName)) return matrixName;
            correctInput = false;
        }
        else if (all_of(matrixName.begin(), matrixName.end(), ::isalnum))
        {
            if (not correctNameMatrix(matrixName))
            {
                cout << "Ошибка: имя матрицы должно начинаться с латинской буквы и может содержать цифры" << endl << endl;
                correctInput = false;
            }

            if (checkMatrixExist(matrixName)) return matrixName;
            else  cout << "Ошибка: матрица с именем '" << matrixName << "' не найдена" << endl << endl;
            correctInput = false;
        }
        else
        {
            cout << "Ошибка: ввод должен содержать только латинские буквы, цифры, '.', ',', или '-'" << endl << endl;
            correctInput = false;
        }
    } while (not correctInput);

    return "back";
}

void Matrix::userCalculateMatrix()
{
    cout << "Существующие пользовательские матрицы" << endl;
    outputAllMatrix();

    cout << "Поддерживаемые операции:" << endl
        << "Матричное сложение  \"+\"" << endl
        << "Матричное вычитание \"-\"" << endl
        << "Матричное умножение \"*\"" << endl
        << "Детерминант матрицы \"Det\"" << endl
        << "Транспонирование матрицы \"T\"" << endl
        << "Норма матрицы \"Norm\"" << endl
        << "Норма матрицы \"Inv\"" << endl
        << "Норма матрицы \"Rang\"" << endl
        << "Вернуться в меню \"back\"" << endl << endl;

    cout << "Введите оператор: ";
    string oper;
    getline(cin, oper);

    if (oper == "back")
    {
        system("cls");
        return;
    }

    if (oper.empty())
    {
        cout << "Ошибка: ввод не может быть пустым" << endl << endl;
        return;
    }

    if (Operations.count(oper) == 0)
    {
        system("cls");
        cout << "Ошибка: нет такого оператора '" << oper << "'" << endl << endl;
        return;
    }

    string firstMatrix = inputMatrixOperand("Введите первый операнд");

    if (firstMatrix == "back")
    {
        system("cls");
        return;
    }

    string expr = "'" + oper + "'" + firstMatrix;
    string secondMatrix;

    if (twoOperator(oper))
    {
        secondMatrix = inputMatrixOperand("Введите второй операнд");

        if (secondMatrix == "back")
        {
            system("cls");
            return;
        }
        expr = firstMatrix + "'" + oper + "'" + secondMatrix;
    }

    try
    {
        system("cls");
        cout << "Входная строка: " << expr << endl << endl;

        if (twoOperator(oper))
        {
            executeMatrix(oper, firstMatrix, secondMatrix);
        }
        else
        {
            executeMatrix(oper, firstMatrix);
        }
        cout << endl << endl;
    }
    catch (string err)
    {
        cout << err << endl << endl;
    }
}

void Matrix::changePrecision()
{
    cout << "Введите требуемое количество знаков после запятой в виде неотрицательного целого числа меньше 4" << endl;
    cout << "Ввод значения: ";
    string input;

    int number = 0;

    getline(cin, input);

    if (input.find_first_not_of("1234567890") == -1)
    {
        if (input.empty())
        {
            cout << "Неправильный ввод, введена пустая строка" << endl << endl;
            return;
        }

        number = stoi(input);

        if (number >= 0 and number <= 3)
        {
            precision = number;
            cout << endl << endl;
        }
        else cout << "Неправильный ввод, требуется число меньше 4" << endl << endl;
    }
    else cout << "Неправильный ввод, требуется неотрицательное целое число" << endl << endl;
}

void Matrix::menu()
{
    int command = 0;

    do
    {
        cout << "Выберите пункт для работы с программой:" << endl
            << "1 - Создать и добавить переменные к матрице" << endl
            << "2 - Вывод всех сохраненных матриц" << endl
            << "3 - Удаление матрицы" << endl
            << "4 - Очистка консоли" << endl
            << "5 - Ввод выражения" << endl
            << "6 - Ввод точности вывода, текущая: " << precision << endl
            << "0 - Завершение работы" << endl << endl;

        command = _getch();
        system("cls");

        switch (command)
        {
        case '1':
            inputMatrix();
            break;
        case '2':
            cout << "Существующие пользовательские матрицы" << endl;
            outputAllMatrix();
            break;
        case '3':
            deleteMatrix();
            break;
        case '4':
            system("cls");
            break;
        case '5':
            userCalculateMatrix();
            break;
        case '6':
            changePrecision();
            break;
        case '0':
            cout << endl << "Работа завершена" << endl;
            return;
        default:
            cout << "Некорректный ввод комманды, попробуйте снова" << endl << endl;
        }
    } while (command != '9');
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    Matrix matrix;
    
    matrix.menu();
}
