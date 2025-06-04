#include "Header.h"

// �������������� ������ � ������ MathMatrix (�� ����� ������� ��� �����)
// input � ������, �������������� ��� ������� ��� �����
MathMatrix Matrix::OperandToMatrix(string operand) 
{
	// ���� ������� � ��� ����� ���������� �������
	if (usersMatrix.count(operand)) return MathMatrix(usersMatrix[operand]);

	// ���� ������� � ����� 
	if (all_of(operand.begin(), operand.end(), [](char c) { return isdigit(c) || c == ',' || c == '.' || c == '-'; })) return MathMatrix({ { stod(operand) } });

	throw string("������: �� ������� ���������� ������� '" + operand + "'");
}

// ������� ��� ���������� �������� ��� ����� ���������
// oper � ��������
// first_ � ������ �������
// second_ � ������ �������
void Matrix::executeMatrix(string oper, string firstOperand, string secondOperand) 
{
	// ��������� ������ �������
	MathMatrix firstMatrix = OperandToMatrix(firstOperand);

	// ��������� ������ �������
	MathMatrix secondMatrix = OperandToMatrix(secondOperand);

	// ���������� ��� �������� ���������� ��������
	MathMatrix operationResult;

	// �������� ������
	if (oper == "+") operationResult = firstMatrix + secondMatrix;

	// ��������� ������
	else if (oper == "-") operationResult = firstMatrix - secondMatrix;


	else if (oper == "*") 
	{
		// ��������: �������� �� ����� ������� ��������
		bool firstIsNumber = firstMatrix.matrixData.size() == 1 and firstMatrix.matrixData[0].size() == 1;

		// ��������: �������� �� ������ ������� ��������
		bool secondIsNumber = secondMatrix.matrixData.size() == 1 and secondMatrix.matrixData[0].size() == 1;

		// ����� * �������
		if (firstIsNumber and not secondIsNumber) operationResult = secondMatrix * firstMatrix.matrixData[0][0];

		// ������� * �����
		else if (not firstIsNumber and secondIsNumber) operationResult = firstMatrix * secondMatrix.matrixData[0][0];

		// ������� * �������
		else operationResult = firstMatrix * secondMatrix;
	}
	else throw string("�������� �� ��������������");

	// ��������� ���������
	MatrixResult = operationResult.matrixData;

	// ����� ����������
	MatrixOut(MatrixResult);
	// ���������� ����������
	saveResult();
}

// ������� ��� ���������� �������� ��� ����� ��������
// oper � ��������
// first_ � �������
void Matrix::executeMatrix(string oper, string operand) 
{
	// ��������� �������
	MathMatrix matrixOperand = OperandToMatrix(operand);

	if (oper == "Det") 
	{
		if (matrixOperand.matrixData.size() != matrixOperand.matrixData[0].size()) throw string("������� ������ ���� ���������� ��� ���������� ������������");
		// ���������� ������������
		cout << "Det: " << MatrixDeterm(matrixOperand.matrixData);
	}
	else if (oper == "T") 
	{
		// ���������������� �������
		MatrixTranspose(matrixOperand.matrixData);
		// ����� ����������
		MatrixOut(MatrixResult);
		// ���������� ����������
		saveResult();
	}
	else if (oper == "Norm") 
	{
		// ���������� ��������� ���� �������
		cout << "Matrix Norms" << endl;
		cout << "Max Norm: " << MatrixNormMax(matrixOperand.matrixData) << endl;
		cout << "M Norm: " << MatrixNormM(matrixOperand.matrixData) << endl;
		cout << "L Norm: " << MatrixNormL(matrixOperand.matrixData) << endl;
		cout << "K Norm: " << MatrixNorm(matrixOperand.matrixData) << endl;
	}
	else if (oper == "Inv") 
	{
		if (matrixOperand.matrixData.size() != matrixOperand.matrixData[0].size()) throw string("������� ������ ���� ���������� ��� ���������� ��������");

		// ���������� �������� �������
		MatrixInverse(matrixOperand.matrixData);

		// ����� ����������
		MatrixOut(MatrixResult);

		// ���������� ����������
		saveResult();
	}
	// ���������� ����� �������
	else if (oper == "Rang") cout << "Rang: " << MatrixRang(matrixOperand.matrixData) << endl;
	
	else throw string("����������� ��������");
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

		if (input == "y" or input == "Y") return true;

		else if (input == "n" or input == "N") return false;

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
