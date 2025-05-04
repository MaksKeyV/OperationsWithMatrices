#include "Header.h"

// Функция для извлечения матрицы
// operand - операнд
vector<vector<double>> Matrix::definitionOperand(string& operand)
{
	// Матрица-результат
	vector<vector<double>> result;

	// Если операнд — имя ранее сохранённой матрицы
	if (usersMatrix.count(operand)) return usersMatrix[operand];

	// Если операнд — число 
	if (all_of(operand.begin(), operand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; }))
	{
		// Вектор для хранения числа
		vector<double> singleValue = { stod(operand) };
		result.push_back(singleValue);
	}

	return result;
}

// Функция для выполнения операции над двумя матрицами
// oper – операция
// first_ – первая матрица
// second_ – вторая матрица
void Matrix::executeMatrix(string oper, string firstOperand, string secondOperand)
{
	// Извлекаем первую матрицу
	vector<vector<double>> MatrixFirs = definitionOperand(firstOperand);

	// Извлекаем вторую матрицу
	vector<vector<double>> MatrixSecond = definitionOperand(secondOperand);

	if (oper == "+")
	{
		if (MatrixFirs.size() != MatrixSecond.size() or MatrixFirs[0].size() != MatrixSecond[0].size())
		{
			throw string("Ошибка: размеры матриц не совпадают для сложения");
		}

		// Вызываем функцию сложения матриц
		MatrixSumm(MatrixFirs, MatrixSecond);
	}

	else if (oper == "-")
	{
		if (MatrixFirs.size() != MatrixSecond.size() or MatrixFirs[0].size() != MatrixSecond[0].size())
		{
			throw string("Ошибка: размеры матриц не совпадают для вычитания");
		}

		// Вызываем функцию вычитания матриц
		MatrixSubt(MatrixFirs, MatrixSecond);
	}

	else if (oper == "*")
	{
		if (all_of(firstOperand.begin(), firstOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; }) and not(all_of(secondOperand.begin(), secondOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; })))
		{
			// Умножение числа на матрицу (число в первом операнде)
			MatrixMultiplicationConst(MatrixSecond, stod(firstOperand));
		}

		else if (not(all_of(firstOperand.begin(), firstOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; })) and all_of(secondOperand.begin(), secondOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; }))
		{
			// Умножение матрицы на число (число во втором операнде)
			MatrixMultiplicationConst(MatrixFirs, stod(secondOperand));
		}

		else if (MatrixFirs[0].size() != MatrixSecond.size()) throw string("Ошибка: размеры матриц не совпадают для умножения");

		// Умножение двух матриц
		else MatrixMultiplication(MatrixFirs, MatrixSecond);
	}

	// Вывод результата
	MatrixOut(MatrixResult);

	// Сохранение результата
	saveResult();
}

// Функция для выполнения операции над одной матрицей
// oper – операция
// first_ – матрица
void Matrix::executeMatrix(string oper, string firstOperand)
{
	// Извлекаем первую матрицу
	vector<vector<double>> MatrixFirs = definitionOperand(firstOperand);
	
	if (oper == "Det") 
	{
		if (MatrixFirs.size() != MatrixFirs[0].size()) throw string("Матрица должна быть квадратной для вычисления детерминанта");
		
		// Вычисление определителя
		cout << "Det: " << MatrixDeterm(MatrixFirs);
	}

	if (oper == "T")
	{
		// Транспонирование матрицы
		MatrixTranspose(MatrixFirs);

		// Вывод результата
		MatrixOut(MatrixResult);

		// Сохранение результата
		saveResult();
	}

	if (oper == "Norm")
	{
		// Вычисление различных норм матрицы
		cout << "Matrix Norms" << endl;
		cout << "Max Norm: " << MatrixNormMax(MatrixFirs) << endl;
		cout << "M Norm: " << MatrixNormM(MatrixFirs) << endl;
		cout << "L Norm: " << MatrixNormL(MatrixFirs) << endl;
		cout << "K Norm: " << MatrixNorm(MatrixFirs) << endl;
	}

	if (oper == "Inv")
	{
		if (MatrixFirs.size() != MatrixFirs[0].size()) throw string("Матрица должна быть квадратной для вычисления обратной");

		// Вычисление обратной матрицы
		MatrixInverse(MatrixFirs);

		// Вывод результата
		MatrixOut(MatrixResult);

		// Сохранение результата
		saveResult();
	}

	// Вычисление ранга матрицы
	if (oper == "Rang") cout << "Rang: " << MatrixRang(MatrixFirs) << endl;
}

// Функция для запроса у пользователя сохранения результата операции
bool Matrix::requestSaveResult()
{
	string input;

	// Цикл, пока не получим корректный ввод
	while (true)
	{
		cout << "Сохранить результат (Y/n)";

		// Получаем ввод
		input = _getch();

		if (input == "y" || input == "Y") return true;

		else if (input == "n" || input == "N") return false;

		else
		{
			system("cls");
			cout << "Ошибка: введите 'Y' (да) или 'n' (нет)" << endl;
		}
	}
}

// Функция для сохранения результата операции
void Matrix::saveResult()
{
	cout << endl << "Хотите сохранить полученную матрицу в результате?" << endl;

	// Запрос у пользователя, хочет ли он сохранить результат
	if (not requestSaveResult())
	{
		system("cls");
		cout << "Сохранение отменено" << endl << endl;
		return;
	}
	cout << endl << endl;

	// Флаг для контроля сохранения
	bool flagSave = true;

	// Цикл, пока сохранение не будет успешным
	do
	{
		flagSave = true;

		// Запрос имени для сохранения матрицы
		string matrixName = inputNameMatrix(false);

		if (matrixName == "back")
		{
			flagSave = false;
			system("cls");
			cout << "Ошибка: имя 'back' зарезервировано и не может использоваться в качестве имени матрицы" << endl << endl;
			continue;
		}

		// Проверка, существует ли уже матрица с таким именем
		if (checkMatrixExist(matrixName))
		{
			cout << "Матрица с именем '" << matrixName << "' уже существует, желаете перезаписать матрицу?" << endl;

			// Запрос подтверждения перезаписи
			if (requestSaveResult())
			{
				usersMatrix[matrixName] = MatrixResult;
				system("cls");
				cout << "Матрица '" << matrixName << "' перезаписана" << endl << endl;
			}
			else
			{
				system("cls");
				cout << "Сохранение отменено" << endl << endl;
				cout << "Введите снова имя матрицы для сохранения полученную матрицу в результате" << endl << endl;
				flagSave = false;
			}
		}
		else
		{
			usersMatrix[matrixName] = MatrixResult;
			system("cls");
			cout << "Матрица '" << matrixName << "' сохранена" << endl << endl;
		}
	} while (not flagSave);
}