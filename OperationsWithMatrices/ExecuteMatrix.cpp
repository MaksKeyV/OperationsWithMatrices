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
			throw string("������: ������� ������ �� ��������� ��� ��������");
		}

		MatrixSumm(MatrixFirs, MatrixSecond);
	}

	else if (oper == "-")
	{
		if (MatrixFirs.size() != MatrixSecond.size() or MatrixFirs[0].size() != MatrixSecond[0].size())
		{
			throw string("������: ������� ������ �� ��������� ��� ���������");
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

		else if (MatrixFirs[0].size() != MatrixSecond.size()) throw string("������: ������� ������ �� ��������� ��� ���������");

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
		if (MatrixFirs.size() != MatrixFirs[0].size()) throw runtime_error("������� ������ ���� ���������� ��� ���������� ��������");
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
		cout << "��������� ��������� (Y/n)";
		input = _getch();

		if (input == "y" || input == "Y") return true;

		else if (input == "n" || input == "N") return false;

		else
		{
			system("cls");
			cout << "������: ������� 'Y' (��) ��� 'n' (���)" << endl;
		}
	}
}

void Matrix::saveResult()
{
	cout << endl << "������ ��������� ���������� ������� � ����������?" << endl;

	if (not requestSaveResult())
	{
		system("cls");
		cout << "���������� ��������" << endl << endl;
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
			cout << "������: ��� 'back' ��������������� � �� ����� �������������� � �������� ����� �������" << endl << endl;
			continue;
		}

		if (checkMatrixExist(matrixName))
		{
			cout << "������� � ������ '" << matrixName << "' ��� ����������, ������� ������������ �������?" << endl;

			if (requestSaveResult())
			{
				usersMatrix[matrixName] = MatrixResult;
				system("cls");
				cout << "������� '" << matrixName << "' ������������" << endl << endl;
			}
			else
			{
				system("cls");
				cout << "���������� ��������" << endl << endl;
				cout << "������� ����� ��� ������� ��� ���������� ���������� ������� � ����������" << endl << endl;
				flagSave = false;
			}
		}
		else
		{
			usersMatrix[matrixName] = MatrixResult;
			system("cls");
			cout << "������� '" << matrixName << "' ���������" << endl << endl;
		}
	} while (not flagSave);
}