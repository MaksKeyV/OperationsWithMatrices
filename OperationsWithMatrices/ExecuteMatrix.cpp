#include "Header.h"

// ������� ��� ���������� �������
// operand - �������
vector<vector<double>> Matrix::definitionOperand(string& operand)
{
	// �������-���������
	vector<vector<double>> result;

	// ���� ������� � ��� ����� ���������� �������
	if (usersMatrix.count(operand)) return usersMatrix[operand];

	// ���� ������� � ����� 
	if (all_of(operand.begin(), operand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; }))
	{
		// ������ ��� �������� �����
		vector<double> singleValue = { stod(operand) };
		result.push_back(singleValue);
	}

	return result;
}

// ������� ��� ���������� �������� ��� ����� ���������
// oper � ��������
// first_ � ������ �������
// second_ � ������ �������
void Matrix::executeMatrix(string oper, string firstOperand, string secondOperand)
{
	// ��������� ������ �������
	vector<vector<double>> MatrixFirs = definitionOperand(firstOperand);

	// ��������� ������ �������
	vector<vector<double>> MatrixSecond = definitionOperand(secondOperand);

	if (oper == "+")
	{
		if (MatrixFirs.size() != MatrixSecond.size() or MatrixFirs[0].size() != MatrixSecond[0].size())
		{
			throw string("������: ������� ������ �� ��������� ��� ��������");
		}

		// �������� ������� �������� ������
		MatrixSumm(MatrixFirs, MatrixSecond);
	}

	else if (oper == "-")
	{
		if (MatrixFirs.size() != MatrixSecond.size() or MatrixFirs[0].size() != MatrixSecond[0].size())
		{
			throw string("������: ������� ������ �� ��������� ��� ���������");
		}

		// �������� ������� ��������� ������
		MatrixSubt(MatrixFirs, MatrixSecond);
	}

	else if (oper == "*")
	{
		if (all_of(firstOperand.begin(), firstOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; }) and not(all_of(secondOperand.begin(), secondOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; })))
		{
			// ��������� ����� �� ������� (����� � ������ ��������)
			MatrixMultiplicationConst(MatrixSecond, stod(firstOperand));
		}

		else if (not(all_of(firstOperand.begin(), firstOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; })) and all_of(secondOperand.begin(), secondOperand.end(), [](char c) { return isdigit(c) or c == ',' or c == '-'; }))
		{
			// ��������� ������� �� ����� (����� �� ������ ��������)
			MatrixMultiplicationConst(MatrixFirs, stod(secondOperand));
		}

		else if (MatrixFirs[0].size() != MatrixSecond.size()) throw string("������: ������� ������ �� ��������� ��� ���������");

		// ��������� ���� ������
		else MatrixMultiplication(MatrixFirs, MatrixSecond);
	}

	// ����� ����������
	MatrixOut(MatrixResult);

	// ���������� ����������
	saveResult();
}

// ������� ��� ���������� �������� ��� ����� ��������
// oper � ��������
// first_ � �������
void Matrix::executeMatrix(string oper, string firstOperand)
{
	// ��������� ������ �������
	vector<vector<double>> MatrixFirs = definitionOperand(firstOperand);
	
	if (oper == "Det") 
	{
		if (MatrixFirs.size() != MatrixFirs[0].size()) throw string("������� ������ ���� ���������� ��� ���������� ������������");
		
		// ���������� ������������
		cout << "Det: " << MatrixDeterm(MatrixFirs);
	}

	if (oper == "T")
	{
		// ���������������� �������
		MatrixTranspose(MatrixFirs);

		// ����� ����������
		MatrixOut(MatrixResult);

		// ���������� ����������
		saveResult();
	}

	if (oper == "Norm")
	{
		// ���������� ��������� ���� �������
		cout << "Matrix Norms" << endl;
		cout << "Max Norm: " << MatrixNormMax(MatrixFirs) << endl;
		cout << "M Norm: " << MatrixNormM(MatrixFirs) << endl;
		cout << "L Norm: " << MatrixNormL(MatrixFirs) << endl;
		cout << "K Norm: " << MatrixNorm(MatrixFirs) << endl;
	}

	if (oper == "Inv")
	{
		if (MatrixFirs.size() != MatrixFirs[0].size()) throw string("������� ������ ���� ���������� ��� ���������� ��������");

		// ���������� �������� �������
		MatrixInverse(MatrixFirs);

		// ����� ����������
		MatrixOut(MatrixResult);

		// ���������� ����������
		saveResult();
	}

	// ���������� ����� �������
	if (oper == "Rang") cout << "Rang: " << MatrixRang(MatrixFirs) << endl;
}

// ������� ��� ������� � ������������ ���������� ���������� ��������
bool Matrix::requestSaveResult()
{
	string input;

	// ����, ���� �� ������� ���������� ����
	while (true)
	{
		cout << "��������� ��������� (Y/n)";

		// �������� ����
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

// ������� ��� ���������� ���������� ��������
void Matrix::saveResult()
{
	cout << endl << "������ ��������� ���������� ������� � ����������?" << endl;

	// ������ � ������������, ����� �� �� ��������� ���������
	if (not requestSaveResult())
	{
		system("cls");
		cout << "���������� ��������" << endl << endl;
		return;
	}
	cout << endl << endl;

	// ���� ��� �������� ����������
	bool flagSave = true;

	// ����, ���� ���������� �� ����� ��������
	do
	{
		flagSave = true;

		// ������ ����� ��� ���������� �������
		string matrixName = inputNameMatrix(false);

		if (matrixName == "back")
		{
			flagSave = false;
			system("cls");
			cout << "������: ��� 'back' ��������������� � �� ����� �������������� � �������� ����� �������" << endl << endl;
			continue;
		}

		// ��������, ���������� �� ��� ������� � ����� ������
		if (checkMatrixExist(matrixName))
		{
			cout << "������� � ������ '" << matrixName << "' ��� ����������, ������� ������������ �������?" << endl;

			// ������ ������������� ����������
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