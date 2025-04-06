#include "Header.h"


void Matrix::executeMatrix(string oper, string firstOperand, string secondOperand)
{
	vector<vector<double>> MatrixFirs;
	vector<vector<double>> MatrixSecond;

	if (usersMatrix.count(firstOperand)) MatrixFirs = usersMatrix[firstOperand];

	if (usersMatrix.count(secondOperand)) MatrixSecond = usersMatrix[secondOperand];


	if (all_of(firstOperand.begin(), firstOperand.end(), ::isdigit))
	{
		vector<double> singleValueFirst = { stod(firstOperand) };
		MatrixFirs.push_back(singleValueFirst);
		singleValueFirst.clear();
	}

	if (all_of(secondOperand.begin(), secondOperand.end(), ::isdigit))
	{
		vector<double> singleValueSecond = { stod(secondOperand) };
		MatrixSecond.push_back(singleValueSecond);
		singleValueSecond.clear();
	}

	if (oper == "+")
	{
		if (MatrixFirs.size() != MatrixSecond.size() or MatrixFirs[0].size() != MatrixSecond[0].size())
		{
			throw string("Ошибка: размеры матриц не совпадают для сложения");
		}

		MatrixSumm(MatrixFirs, MatrixSecond);
	}

	else if (oper == "-")
	{
		if (MatrixFirs.size() != MatrixSecond.size() or MatrixFirs[0].size() != MatrixSecond[0].size())
		{
			throw string("Ошибка: размеры матриц не совпадают для вычитания");
		}

		MatrixSubt(MatrixFirs, MatrixSecond);
	}

	else if (oper == "*")
	{
		if (all_of(firstOperand.begin(), firstOperand.end(), ::isdigit) and not(all_of(secondOperand.begin(), secondOperand.end(), ::isdigit)))
		{
			MatrixMultiplicationConst(MatrixSecond, stod(firstOperand));
		}

		else if (not(all_of(firstOperand.begin(), firstOperand.end(), ::isdigit)) and all_of(secondOperand.begin(), secondOperand.end(), ::isdigit))
		{
			MatrixMultiplicationConst(MatrixFirs, stod(secondOperand));
		}

		else if (MatrixFirs[0].size() != MatrixSecond.size()) throw string("Ошибка: размеры матриц не совпадают для умножения");

		else MatrixMultiplication(MatrixFirs, MatrixSecond);
	}

	MatrixOut(MatrixResult);
	saveResult();
}

void Matrix::executeMatrix(string oper, string firstOperand)
{
	vector<vector<double>> MatrixFirs = usersMatrix[firstOperand];

	if (oper == "D") cout << MatrixDeterm(MatrixFirs);

	if (oper == "T")
	{
		MatrixTranspose(MatrixFirs);
		MatrixOut(MatrixResult);
		saveResult();
	}

	if (oper == "Norm")
	{
		cout << MatrixNormMax(MatrixFirs) << endl;
		cout << MatrixNormM(MatrixFirs) << endl;
		cout << MatrixNormL(MatrixFirs) << endl;
		cout << MatrixNorm(MatrixFirs) << endl;
	}

	if (oper == "Inv")
	{
		if (MatrixFirs.size() != MatrixFirs[0].size()) throw runtime_error("Матрица должна быть квадратной для вычисления обратной");
		MatrixInverse(MatrixFirs);
		MatrixOut(MatrixResult);
		saveResult();
	}

	if (oper == "Rang") cout << MatrixRang(MatrixFirs) << endl;
}

bool Matrix::requestSaveResult()
{
	string input;

	while (true)
	{
		cout << "Сохранить результат (Y/n)";
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

void Matrix::saveResult()
{
	cout << endl << "Хотите сохранить полученную матрицу в результате?" << endl;

	if (not requestSaveResult())
	{
		system("cls");
		cout << "Сохранение отменено" << endl << endl;
		return;
	}
	cout << endl << endl;

	bool flagSave = true;

	do
	{
		flagSave = true;
		string matrixName = inputNameMatrix(false);

		if (matrixName == "back")
		{
			flagSave = false;
			system("cls");
			cout << "Ошибка: имя 'back' зарезервировано и не может использоваться в качестве имени матрицы" << endl << endl;
			continue;
		}

		if (checkMatrixExist(matrixName))
		{
			cout << "Матрица с именем '" << matrixName << "' уже существует, желаете перезаписать матрицу?" << endl;

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