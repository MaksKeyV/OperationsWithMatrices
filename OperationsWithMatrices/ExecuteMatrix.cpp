#include "Header.h"

// Преобразование строки в объект MathMatrix (по имени матрицы или числу)
// input – строка, представляющая имя матрицы или число
MathMatrix Matrix::OperandToMatrix(string operand) 
{
	// Если операнд — имя ранее сохранённой матрицы
	if (usersMatrix.count(operand)) return MathMatrix(usersMatrix[operand]);

	// Если операнд — число 
	if (all_of(operand.begin(), operand.end(), [](char c) { return isdigit(c) || c == ',' || c == '.' || c == '-'; })) return MathMatrix({ { stod(operand) } });

	throw string("Ошибка: не удалось распознать операнд '" + operand + "'");
}

// Функция для выполнения операции над двумя матрицами
// oper – операция
// first_ – первая матрица
// second_ – вторая матрица
void Matrix::executeMatrix(string oper, string firstOperand, string secondOperand) 
{
	// Извлекаем первую матрицу
	MathMatrix firstMatrix = OperandToMatrix(firstOperand);

	// Извлекаем вторую матрицу
	MathMatrix secondMatrix = OperandToMatrix(secondOperand);

	// Переменная для хранения результата операции
	MathMatrix operationResult;

	// Сложение матриц
	if (oper == "+") operationResult = firstMatrix + secondMatrix;

	// Вычитание матриц
	else if (oper == "-") operationResult = firstMatrix - secondMatrix;


	else if (oper == "*") 
	{
		// Проверка: является ли левый операнд скаляром
		bool firstIsNumber = firstMatrix.matrixData.size() == 1 and firstMatrix.matrixData[0].size() == 1;

		// Проверка: является ли правый операнд скаляром
		bool secondIsNumber = secondMatrix.matrixData.size() == 1 and secondMatrix.matrixData[0].size() == 1;

		// Число * матрица
		if (firstIsNumber and not secondIsNumber) operationResult = secondMatrix * firstMatrix.matrixData[0][0];

		// Матрица * число
		else if (not firstIsNumber and secondIsNumber) operationResult = firstMatrix * secondMatrix.matrixData[0][0];

		// Матрица * матрица
		else operationResult = firstMatrix * secondMatrix;
	}
	else throw string("Операция не поддерживается");

	// Сохраняем результат
	MatrixResult = operationResult.matrixData;

	// Вывод результата
	MatrixOut(MatrixResult);
	// Сохранение результата
	saveResult();
}

// Функция для выполнения операции над одной матрицей
// oper – операция
// first_ – матрица
void Matrix::executeMatrix(string oper, string operand) 
{
	// Извлекаем матрицу
	MathMatrix matrixOperand = OperandToMatrix(operand);

	if (oper == "Det") 
	{
		if (matrixOperand.matrixData.size() != matrixOperand.matrixData[0].size()) throw string("Матрица должна быть квадратной для вычисления детерминанта");
		// Вычисление определителя
		cout << "Det: " << MatrixDeterm(matrixOperand.matrixData);
	}
	else if (oper == "T") 
	{
		// Транспонирование матрицы
		MatrixTranspose(matrixOperand.matrixData);
		// Вывод результата
		MatrixOut(MatrixResult);
		// Сохранение результата
		saveResult();
	}
	else if (oper == "Norm") 
	{
		// Вычисление различных норм матрицы
		cout << "Matrix Norms" << endl;
		cout << "Max Norm: " << MatrixNormMax(matrixOperand.matrixData) << endl;
		cout << "M Norm: " << MatrixNormM(matrixOperand.matrixData) << endl;
		cout << "L Norm: " << MatrixNormL(matrixOperand.matrixData) << endl;
		cout << "K Norm: " << MatrixNorm(matrixOperand.matrixData) << endl;
	}
	else if (oper == "Inv") 
	{
		if (matrixOperand.matrixData.size() != matrixOperand.matrixData[0].size()) throw string("Матрица должна быть квадратной для вычисления обратной");

		// Вычисление обратной матрицы
		MatrixInverse(matrixOperand.matrixData);

		// Вывод результата
		MatrixOut(MatrixResult);

		// Сохранение результата
		saveResult();
	}
	// Вычисление ранга матрицы
	else if (oper == "Rang") cout << "Rang: " << MatrixRang(matrixOperand.matrixData) << endl;
	
	else throw string("Неизвестная операция");
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

		if (input == "y" or input == "Y") return true;

		else if (input == "n" or input == "N") return false;

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
