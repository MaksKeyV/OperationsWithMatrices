#include "Header.h"

// Функция для запроса имени матрицы у пользователя
// fladOutMsg – флаг, нужно ли выводить сообщение о вводе
string Matrix::inputNameMatrix(bool fladOutMsg)
{
    string matrixName;

    // Цикл запроса имени, пока оно некорректно
    do 
    {
        cout << "Существующие пользовательские матрицы" << endl;

        // Выводим список существующих пользовательских матриц
        outputAllMatrix();

        // Если флаг fladOutMsg установлен в true, выводим сообщение о вводе
        if (fladOutMsg) 
        {
            cout << "Введите название матрицы или команду 'back', чтобы вернуться в меню" << endl;
            cout << "Если введенное имя матрицы уже существует, матрица будет перезаписана" << endl;
        }

        cout << "Имя должно начинаться с латинской буквы и может содержать цифры" << endl;
        cout << "Введите имя матрицы: ";
        getline(cin, matrixName);

        // Перевод в нижний регистр
        transform(matrixName.begin(), matrixName.end(), matrixName.begin(), ::tolower);

        // Проверка, соответствует ли имя матрицы корректному формату
        if (not correctNameMatrix(matrixName))
        {
            system("cls");
            cout << "Ошибка: имя матрицы должно начинаться с латинской буквы и может содержать цифры" << endl << endl;
        }
    } while (not correctNameMatrix(matrixName));

    return matrixName;
}

// Функция для ввода новой матрицы от пользователя
void Matrix::inputMatrix()
{
    // Запрашиваем имя матрицы
    string matrixName = inputNameMatrix(true);

    if (matrixName == "back")
    {
        system("cls");
        return;
    }

    // Запрашиваем количество строк для матрицы
    int row = correctSizeMatrix("Введите количество строк: ");

    if (row == -1)
    {
        system("cls");
        return;
    }

    // Запрашиваем количество столбцов для матрицы
    int collum = correctSizeMatrix("Введите количество столбцов: ");

    if (collum == -1)
    {
        system("cls");
        return;
    }

    // Создаем матрицу заданных размеров
    vector<vector<double>> matrix(row, vector<double>(collum));

    // Проход по строкам матрицы
    for (int i = 0; i < row; i++)
    {
        // Проход по столбцам матрицы
        for (int j = 0; j < collum; j++)
        {
            string input;

            // Флаг для проверки корректности ввода
            bool validInput = false;

            // Цикл, пока не введено корректное число
            while (!validInput)
            {
                cout << "Введите " << matrixName << "[" << i + 1 << "][" << j + 1 << "]: ";
                getline(cin, input);

                // Перевод в нижний регистр
                transform(input.begin(), input.end(), input.begin(), ::tolower);

                if (input == "back")
                {
                    system("cls");
                    return;
                }

                // Проверка, является ли введенное значение корректным числом
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

    // Применение точности ко всем элементам матрицы
    applyPrecision(matrix);

    usersMatrix[matrixName] = matrix;

    system("cls");

    // Проверка, существует ли уже матрица с таким именем
    if (checkMatrixExist(matrixName)) cout << "Матрица с именем '" << matrixName << "' перезаписана" << endl;

    cout << "Введенная матрица '" << matrixName << "':" << endl;

    // Вывод матрицы
    MatrixOut(matrix);
    cout << endl;
}

// Функция для удаления выбранной пользователем матрицы
void Matrix::deleteMatrix()
{
    // Проверяем, есть ли сохраненные матрицы
    if (usersMatrix.empty())
    {
        cout << "Нет сохраненных матриц" << endl << endl;
        return;
    }

    cout << "Введите название матрицы или команду 'back', чтобы вернуться в меню" << endl << endl;

    // Запрашиваем имя матрицы
    string matrixName = inputNameMatrix(false);

    system("cls");

    if (matrixName == "back") return;

    // Проверка, существует ли уже матрица с таким именем
    if (checkMatrixExist(matrixName))
    {
        // Удаляем матрицу
        usersMatrix.erase(matrixName);
        cout << "Матрица '" << matrixName << "' была удалена" << endl << endl;
    }
    else  cout << "Ошибка: матрица с именем '" << matrixName << "' не найдена" << endl << endl;
}


// Функция для запроса имени операнда у пользователя
// strOperand - строка-подсказка
string Matrix::inputMatrixOperand(string strOperand)
{
    string matrixName;

    // Флаг для проверки корректности ввода
    bool correctInput = true;

    // Цикл, пока не будет корректный ввод
    do
    {
        cout << strOperand << ": ";
        getline(cin, matrixName);

        // Перевод в нижний регистр
        transform(matrixName.begin(), matrixName.end(), matrixName.begin(), ::tolower);

        if (matrixName == "back") return "back";

        // Проверка, состоит ли имя из цифр, точки, запятой или минуса
        if (all_of(matrixName.begin(), matrixName.end(), [](char c) { return isdigit(c) or c == '.' or c == ',' or c == '-'; }))
        {
            // Проверка, является ли введенное значение корректным числом
            if (correctNumberMatrix(matrixName)) return matrixName;
            correctInput = false;
        }
        // Проверка, состоит ли имя из букв и цифр
        else if (all_of(matrixName.begin(), matrixName.end(), ::isalnum))
        {
            // Проверка, соответствует ли имя матрицы корректному формату
            if (not correctNameMatrix(matrixName)) correctInput = false;

            // Проверка, существует ли уже матрица с таким именем
            else if (checkMatrixExist(matrixName)) return matrixName;
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


// Функция для выполнения операций над матрицами по пользовательскому вводу
void Matrix::userCalculateMatrix()
{
    cout << "Существующие пользовательские матрицы" << endl;
    // Вывод всех сохраненных матриц
    outputAllMatrix();

    cout << "Поддерживаемые операции:" << endl
        << "Матричное сложение  \"+\"" << endl
        << "Матричное вычитание \"-\"" << endl
        << "Матричное умножение \"*\"" << endl
        << "Детерминант матрицы \"Det\"" << endl
        << "Транспонирование матрицы \"T\"" << endl
        << "Норма матрицы \"Norm\"" << endl
        << "Обратная матрица \"Inv\"" << endl
        << "Ранг матрицы \"Rang\"" << endl
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

    // Проверка на существование операции
    if (Operations.count(oper) == 0)
    {
        system("cls");
        cout << "Ошибка: нет такого оператора '" << oper << "'" << endl << endl;
        return;
    }

    // Запрашиваем первый операнд
    string firstMatrix = inputMatrixOperand("Введите первый операнд");

    if (firstMatrix == "back")
    {
        system("cls");
        return;
    }

    // Формируем строку выражения с первым операндом
    string expr = "'" + oper + "' " + firstMatrix;
    string secondMatrix;

    // Проверка на необходимость второго операнда
    if (twoOperator(oper))
    {
        // Запрашиваем второй операнд
        secondMatrix = inputMatrixOperand("Введите второй операнд");

        if (secondMatrix == "back")
        {
            system("cls");
            return;
        }
        // Формируем выражение с двумя операндами
        expr = firstMatrix + " '" + oper + "' " + secondMatrix;
    }

    try
    {
        system("cls");
        cout << "Входная строка: " << expr << endl << endl;

        // Проверка на необходимость второго операнда
        if (twoOperator(oper))
        {
            // Выполнение операции над двумя матрицами
            executeMatrix(oper, firstMatrix, secondMatrix);
        }
        else
        {
            // Выполнение операции над одной матрицей
            executeMatrix(oper, firstMatrix);
        }
        cout << endl << endl;
    }
    catch (string err)
    {
        // Вывод ошибок выполнения
        cout << err << endl << endl;
    }
}

// Функция для применения точности к элементам матрицы
// matrix – матрица
void Matrix::changePrecision()
{
    cout << "Введите требуемое количество знаков после запятой в виде неотрицательного целого числа меньше 4" << endl;
    cout << "Ввод значения: ";
    string input;

    int number = 0;

    getline(cin, input);

    // Проверка, что ввод содержит только цифры
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
            // Установка точности
            precision = number;
            cout << endl << endl;
        }
        else cout << "Неправильный ввод, требуется число меньше 4" << endl << endl;
    }
    else cout << "Неправильный ввод, требуется неотрицательное целое число" << endl << endl;

    // Применение точности ко всем матрицам
    if (not usersMatrix.empty()) for (auto& i : usersMatrix) applyPrecision(i.second);
}

// Функция для отображения главного меню программы
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

        // Получаем пункт от пользователя
        command = _getch();
        system("cls");

        switch (command)
        {
        case '1':
            // Создать и добавить матрицу
            inputMatrix();
            break;
        case '2':
            // Вывод всех сохраненных матриц
            cout << "Существующие пользовательские матрицы" << endl;
            outputAllMatrix();
            break;
        case '3':
            // Удалить матрицу
            deleteMatrix();
            break;
        case '4':
            // Очистить консоль
            system("cls");
            break;
        case '5':
            // Ввод выражения для вычислений
            userCalculateMatrix();
            break;
        case '6':
            // Изменение точности
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
    
    // Запускаем главное меню программы
    matrix.menu();
}       