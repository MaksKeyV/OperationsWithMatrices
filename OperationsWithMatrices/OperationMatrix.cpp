#include "Header.h"

// Функция для сложения матриц
// MatrixFirst – первая матрица
// MatrixSecond – вторая матрица
vector<vector<double>> Matrix::MatrixSumm(vector<vector<double>>& MatrixFirst, vector<vector<double>>& MatrixSecond)
{
	// Результирующая матрица
	MatrixResult = vector<vector<double>>(MatrixFirst.size(), vector<double>(MatrixFirst[0].size()));

	// Проход по всем элементам матриц построчно и по столбцам
	for (int i = 0; i < MatrixFirst.size(); i++)
		for (int j = 0; j < MatrixFirst[0].size(); j++)
			MatrixResult[i][j] = MatrixFirst[i][j] + MatrixSecond[i][j];
		
	return MatrixResult;
}

// Функция для вычитания матриц
// MatrixFirst – первая матрица
// MatrixSecond – вторая матрица
vector<vector<double>> Matrix::MatrixSubt(vector<vector<double>>& MatrixFirst, vector<vector<double>>& MatrixSecond)
{
	// Результирующая матрица
	MatrixResult = vector<vector<double>>(MatrixFirst.size(), vector<double>(MatrixFirst[0].size()));

	// Проход по всем элементам матриц построчно и по столбцам
	for (int i = 0; i < MatrixFirst.size(); i++)
		for (int j = 0; j < MatrixFirst[0].size(); j++)
			MatrixResult[i][j] = MatrixFirst[i][j] - MatrixSecond[i][j];

	return MatrixResult;
}

// Функция для вычисления определителя матрицы
// MatrixFirst – матрица
double Matrix::MatrixDeterm(vector<vector<double>>& MatrixFirst)
{
	// Если матрица 1×1, определитель — единственный элемент
	if (MatrixFirst.size() == 1) return MatrixFirst[0][0];

	// Если матрица 2×2, используем формулу для нахождения определителя
	else if (MatrixFirst.size() == 2) return ((MatrixFirst[0][0] * MatrixFirst[1][1]) - (MatrixFirst[1][0] * MatrixFirst[0][1]));

	// Если матрица 3×3, используем формулу для нахождения определителя
	else if (MatrixFirst.size() == 3) return ((MatrixFirst[0][0] * MatrixFirst[1][1] * MatrixFirst[2][2])
		+ (MatrixFirst[0][1] * MatrixFirst[1][2] * MatrixFirst[2][0]) 
		+ (MatrixFirst[2][1] * MatrixFirst[1][0] * MatrixFirst[0][2]) 
		- (MatrixFirst[0][2] * MatrixFirst[1][1] * MatrixFirst[2][0]) 
		- (MatrixFirst[0][0] * MatrixFirst[1][2] * MatrixFirst[2][1]) 
		- (MatrixFirst[0][1] * MatrixFirst[1][0] * MatrixFirst[2][2]));
	else
	{
		double DetermResult = 0;
		
		for (int i = 0; i < MatrixFirst.size(); i++)
		{
			// Формируем минор матрицы
			vector<vector<double>> minorMatrix(MatrixFirst.size() - 1, vector<double>(MatrixFirst.size() - 1));

			// Проход по строкам, начиная со второй
			for (int j = 1; j < MatrixFirst.size(); j++)
			{
				int collumIndex = 0;
				for (int collum = 0; collum < MatrixFirst.size(); collum++)
				{
					// Пропускаем текущий столбец
					if (collum == i) continue;

					// Заполняем минор соответствующими элементами
					minorMatrix[j - 1][collumIndex] = MatrixFirst[j][collum];
					collumIndex++;
				}
			}
			// Вычисляем определитель по формуле Лапласа
			DetermResult += (i % 2 == 0 ? 1 : (-1)) * MatrixFirst[0][i] * MatrixDeterm(minorMatrix);
		}
		return DetermResult;
	}
}

// Функция для умножения матриц
// MatrixFirst – первая матрица
// MatrixSecond – вторая матрица
vector<vector<double>> Matrix::MatrixMultiplication(vector<vector<double>>& MatrixFirst, vector<vector<double>>& MatrixSecond)
{
	// Результирующая матрица
	MatrixResult = vector<vector<double>>(MatrixFirst.size(), vector<double>(MatrixSecond[0].size()));

	// Проход по строкам первой матрицы
	for (int i = 0; i < MatrixFirst.size(); i++)
	{
		// Проход по столбцам второй матрицы
		for (int j = 0; j < MatrixSecond[0].size(); j++)
		{
			MatrixResult[i][j] = 0;
			// Складываем произведения соответствующих элементов строки и столбца
			for (int k = 0; k < MatrixSecond.size(); k++)
				MatrixResult[i][j] += MatrixFirst[i][k] * MatrixSecond[k][j];
		}
	}
	return MatrixResult;
}

// Функция для умножения матрицы на число
// MatrixFirst – матрица
// constValue – значение константы 
vector<vector<double>> Matrix::MatrixMultiplicationConst(vector<vector<double>>& MatrixFirst, double constValue)
{
	// Результирующая матрица
	MatrixResult = vector<vector<double>>(MatrixFirst.size(), vector<double>(MatrixFirst[0].size()));

	// Проход по всем элементам матриц построчно и по столбцам, умножая на константу
	for (int i = 0; i < MatrixFirst.size(); i++)
		for (int j = 0; j < MatrixFirst[0].size(); j++)
			MatrixResult[i][j] = MatrixFirst[i][j] * constValue;

	return MatrixResult;
}

// Функция для транспонирования матрицы
// MatrixFirst – матрица
vector<vector<double>> Matrix::MatrixTranspose(vector<vector<double>>& MatrixFirst)
{
	// Результирующая матрица
	MatrixResult = vector<vector<double>>(MatrixFirst[0].size(), vector<double>(MatrixFirst.size()));

	// Проход по всем элементам матриц построчно и по столбцам
	for (int i = 0; i < MatrixFirst.size(); i++)
		for (int j = 0; j < MatrixFirst[0].size(); j++)
			MatrixResult[j][i] = MatrixFirst[i][j];
		
	return MatrixResult;
}

// Функция для вычисления максимальной нормы матрицы
// MatrixFirst – матрица
double Matrix::MatrixNormMax(vector<vector<double>>& MatrixFirst)
{
	// Если матрица 1x1, то возвращаем единственный элемент
	if (MatrixFirst.size() == 1) return MatrixFirst[0][0];

	double maxValue = 0;

	// Проход по всем строкам матрицы и находим максимальный элемент
	for (int i = 0; i < MatrixFirst.size(); i++) 
		maxValue = max(maxValue, *max_element(MatrixFirst[i].begin(), MatrixFirst[i].end()));

	return maxValue;
}

// Функция для вычисления нормы строки матрицы (норма M)
// MatrixFirst – матрица
double Matrix::MatrixNormM(vector<vector<double>>& MatrixFirst)
{
	double maxValueNorm = 0;

	// Проход по строкам матрицы
	for (int i = 0; i < MatrixFirst.size(); i++)
	{
		double valueNorm = 0;

		// Проход по столбцам матрицы
		for (int j = 0; j < MatrixFirst[0].size(); j++)
			// Суммируем абсолютные значения элементов строки
			valueNorm += abs(MatrixFirst[i][j]);
		// Находим максимальную норму строк
		maxValueNorm = max(maxValueNorm, valueNorm);
	}
	return maxValueNorm;
}

// Функция для вычисления нормы столбца матрицы (норма L)
// MatrixFirst – матрица
double Matrix::MatrixNormL(vector<vector<double>>& MatrixFirst)
{
	double maxValueNorm = 0;

	// Проход по столбцам матрицы
	for (int i = 0; i < MatrixFirst[0].size(); i++)
	{
		double valueNorm = 0;

		// Проход по строкам матрицы
		for (int j = 0; j < MatrixFirst.size(); j++)
			// Суммируем абсолютные значения элементов столбца
			valueNorm += abs(MatrixFirst[j][i]);
		// Находим максимальную норму столбцов
		maxValueNorm = max(maxValueNorm, valueNorm);
	}

	return maxValueNorm;
}

// Функция для вычисления Евклидовой нормы матрицы
// MatrixFirst – матрица
double Matrix::MatrixNorm(vector<vector<double>>& MatrixFirst)
{
	double sumValueNorm = 0;

	// Проход по всем элементам матриц построчно и по столбцам, суммируем их квадраты
	for (int i = 0; i < MatrixFirst.size(); i++)
		for (int j = 0; j < MatrixFirst[0].size(); j++)
			sumValueNorm += pow(MatrixFirst[i][j], 2);

	// Возвращаем квадратный корень из суммы квадратов
	return sqrt(sumValueNorm);
}

// Функция для вычисления обратной матрицы
// MatrixFirst – матрица
vector<vector<double>> Matrix::MatrixInverse(vector<vector<double>>& MatrixFirst)
{
	double determ = MatrixDeterm(MatrixFirst);

	// Если определитель равен 0 — матрица необратима
	if (determ == 0) throw string("Матрица не обратима, определитель равен 0");

	// Результирующая матрица
	MatrixResult = vector<vector<double>>(MatrixFirst.size(), vector<double>(MatrixFirst.size()));
	
	// Обратная к матрице 1×1 — это 1/элемент
	if (MatrixFirst.size() == 1)
	{
		MatrixResult[0][0] = 1.0 / (MatrixFirst[0][0]);
		return MatrixResult;
	}

	// Матрица для алгебраических дополнений
	vector<vector<double>> matrix = vector<vector<double>>(MatrixFirst.size(), vector<double>(MatrixFirst.size()));

	// Проход по всем элементам матриц построчно и по столбцам
	for (int i = 0; i < MatrixFirst.size(); i++)
	{
		for (int j = 0; j < MatrixFirst[0].size(); j++)
		{
			// Формируем минор матрицы
			vector<vector<double>> minorMatrix(MatrixFirst.size() - 1, vector<double>(MatrixFirst.size() - 1));
			
			int collumIndex = 0;

			for (int collum = 0; collum < MatrixFirst.size(); collum++)
			{
				// Пропускаем текущий столбец
				if (collum == j) continue;
				int rowIndex = 0;

				for (int row = 0; row < MatrixFirst.size(); row++)
				{
					// Пропускаем текущую строку
					if (row == i) continue;

					minorMatrix[rowIndex][collumIndex] = MatrixFirst[row][collum];
					rowIndex++;
				}
				collumIndex++;
			}
			// Вычисляем определитель по формуле Лапласа
			matrix[i][j] += ((i + j) % 2 == 0 ? 1 : (-1)) * MatrixDeterm(minorMatrix);
		}
	}

	// Транспонируем матрицу
	matrix = MatrixTranspose(matrix);

	// Делим матрицу на определитель — получаем обратную матрицу
	return MatrixResult = MatrixMultiplicationConst(matrix, (1.0 / determ));
}

// Функция для вычисления ранга матрицы
// MatrixFirst – матрица
int Matrix::MatrixRang(vector<vector<double>>& MatrixFirst) 
{
	// Изначально ранг равен количеству столбцов
	int rank = MatrixFirst[0].size();

	// Проход по строкам матрицы
	for (int row = 0; row < rank; row++) 
	{
		// Проверяем, не нулевой ли диагональный элемент
		if (MatrixFirst[row][row] != 0) 
		{
			// Цикл для обнуления текущего столбца во всех строках, кроме текущей
			for (int collum = 0; collum < MatrixFirst.size(); collum++)
			{
				if (collum != row)
				{
					// Множитель для вычитания строки
					double mult = MatrixFirst[collum][row] / MatrixFirst[row][row];

					for (int i = 0; i < rank; i++) 
						MatrixFirst[collum][i] -= mult * MatrixFirst[row][i];
				}
			}
		}
		else 
		{
			// Флаг, нужно ли уменьшать ранг
			bool reduce = true;
			
			for (int i = row + 1; i < MatrixFirst.size(); i++)
			{
				// Если нашли строку с ненулевым элементом, меняем строки местами
				if (MatrixFirst[i][row] != 0) 
				{
					swap(MatrixFirst[row], MatrixFirst[i]);
					reduce = false;
					break;
				}
			}
			
			// Если не нашли строку с ненулевым элементом в столбце
			if (reduce) 
			{
				// Уменьшаем ранг
				rank--;

				// Перемещаем последний столбец на место текущего
				for (int i = 0; i < MatrixFirst.size(); i++)
					MatrixFirst[i][row] = MatrixFirst[i][rank];
			}

			// Уменьшаем индекс строки
			row--;
		}
	}
	return rank;
}

// Функция для вывода всех пользовательских матриц
void Matrix::outputAllMatrix()
{
	// Если список пользовательских матриц пуст
	if (usersMatrix.empty())
	{
		cout << "Нет сохраненных матриц" << endl << endl;
		return;
	}

	// Перебираем все сохранённые матрицы
	for (auto i : usersMatrix)
	{
		cout << "Матрица '" << i.first << "':" << endl;

		// Вывод матрицы
		MatrixOut(i.second); 
		cout << endl;
	}
}

