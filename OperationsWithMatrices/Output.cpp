#include "Header.h"

// Функция для вычисления ширины колонок матрицы при форматированном выводе
// matrix – матрица
vector<int> Matrix::columnWidths(vector<vector<double>>& matrix)
{
    // Вектор для хранения ширины каждой колонки
    vector<int> colWidth(matrix[0].size());

    // Проход по столбцам матрицы
    for (int j = 0; j < matrix[0].size(); j++)
    {
        int maxWidth = 0;

        // Проход по строкам матрицы
        for (int i = 0; i < matrix.size(); i++)
        {
            stringstream ss;
            // Устанавка нужной точности
            ss << fixed << setprecision(precision) << matrix[i][j];
            string str = ss.str();
            // Замена запятой на точку
            replace(str.begin(), str.end(), ',', '.');

            // Проверка, является ли текущая строка самой длинной в столбце
            if (str.size() > maxWidth) maxWidth = str.size();
        }
        colWidth[j] = maxWidth;
    }

    return colWidth;
}

// Функция для вывода одной матрицы
// matrix – матрица
void Matrix::MatrixOut(vector<vector<double>>& matrix)
{
    // Получаем ширину каждого столбца для выравнивания
    vector<int> colWidths = columnWidths(matrix);

    // Проход по строкам матрицы
    for (int i = 0; i < matrix.size(); i++)
    {
        string strRow = "|";

        // Проход по столбцам матрицы
        for (int j = 0; j < matrix[0].size(); j++)
        {
            stringstream ss;
            // Устанавка нужной точности
            ss << fixed << setprecision(precision) << matrix[i][j];
            string str = ss.str();
            // Замена запятой на точку
            replace(str.begin(), str.end(), ',', '.');

            stringstream formatted;
            formatted << setw(colWidths[j]) << str;

            if (j != 0) strRow += " ";
            strRow += formatted.str();
        }

        strRow += "|";
        cout << strRow << endl;
    }
}

// Функция для округления значения по текущей точности
// value – число
double Matrix::roundValue(double value)
{
    // Вычисляем степень
    double degreRound = pow(10, precision);

    // Округляем число и возвращаем результат
    return round(value * degreRound) / degreRound;
}

// Функция для применения точности к элементам матрицы
// matrix – матрица
void Matrix::applyPrecision(vector<vector<double>>& matrix)
{
    // Проход по всем элементам матриц построчно и по столбцам
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[0].size(); j++)
            // Округляем значение по заданной точности и сохраняем
            matrix[i][j] = roundValue(matrix[i][j]);
}
