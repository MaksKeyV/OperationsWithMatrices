#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <filesystem>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <conio.h>
#include <regex>


using namespace std;

// ����� ��� ��������� ��������
class Matrix
{
	public:
		// ������ ��� �������� ���������� �������� ��� ���������
		vector<vector<double>> MatrixResult;

		// �������, ���������� ���������������� �������
		map<string, vector<vector<double>>> usersMatrix;

		// ��������� ���������� �������� ��� ��������� 
		const set<string> Operations = { "+", "-", "*", "Det", "T", "Norm", "Inv", "Rang"};
		
		// �������� �����������
		int precision = 3;
		 


		// ������� ��� �������� ������
		// MatrixFirst � ������ �������
		// MatrixSecond � ������ �������
		vector<vector<double>> MatrixSumm(vector<vector<double>>& MatrixFirst, vector<vector<double>>& MatrixSecond);

		// ������� ��� ��������� ������
		// MatrixFirst � ������ �������
		// MatrixSecond � ������ �������
		vector<vector<double>> MatrixSubt(vector<vector<double>>& MatrixFirst, vector<vector<double>>& MatrixSecond);

		// ������� ��� ���������� ������������ �������
		// MatrixFirst � �������
		double MatrixDeterm(vector<vector<double>>& MatrixFirst);

		// ������� ��� ��������� ������
		// MatrixFirst � ������ �������
		// MatrixSecond � ������ �������
		vector<vector<double>> MatrixMultiplication(vector<vector<double>>& MatrixFirst, vector<vector<double>>& MatrixSecond);

		// ������� ��� ��������� ������� �� �����
		// MatrixFirst � �������
		// constValue � �������� ��������� 
		vector<vector<double>> MatrixMultiplicationConst(vector<vector<double>>& MatrixFirst, double constValue);

		// ������� ��� ���������������� �������
		// MatrixFirst � �������
		vector<vector<double>> MatrixTranspose(vector<vector<double>>& MatrixFirst);

		// ������� ��� ���������� ������������ ����� �������
		// MatrixFirst � �������
		double MatrixNormMax(vector<vector<double>>& MatrixFirst);

		// ������� ��� ���������� ����� ������ ������� (����� M)
		// MatrixFirst � �������
		double MatrixNormM(vector<vector<double>>& MatrixFirst);

		// ������� ��� ���������� ����� ������� ������� (����� L)
		// MatrixFirst � �������
		double MatrixNormL(vector<vector<double>>& MatrixFirst);

		// ������� ��� ���������� ���������� ����� �������
		// MatrixFirst � �������
		double MatrixNorm(vector<vector<double>>& MatrixFirst);

		// ������� ��� ���������� �������� �������
		// MatrixFirst � �������
		vector<vector<double>> MatrixInverse(vector<vector<double>>& MatrixFirst);

		// ������� ��� ���������� ����� �������
		// MatrixFirst � �������
		int MatrixRang(vector<vector<double>>& MatrixFirst);

		// ������� ��� ������ ���� ���������������� ������
		void outputAllMatrix();
		


		// ������� ��� ���������� �������
		// operand - �������
		vector<vector<double>> definitionOperand(string& operand);

		// ������� ��� ���������� �������� ��� ����� ���������
		// oper � ��������
		// first_ � ������ �������
		// second_ � ������ �������
		void executeMatrix(string oper, string first_, string second_);

		// ������� ��� ���������� �������� ��� ����� ��������
		// oper � ��������
		// first_ � �������
		void executeMatrix(string oper, string first_);

		// ������� ��� ������� � ������������ ���������� ���������� ��������
		bool requestSaveResult();

		// ������� ��� ���������� ���������� ��������
		void saveResult();
		


		// ������� ��� ���������� ������ ������� ������� ��� ��������������� ������
		// matrix � �������
		vector<int> columnWidths(vector<vector<double>>& matrix);

		// ������� ��� ������ ����� �������
		// MatrixFirst � �������
		void MatrixOut(vector<vector<double>>& MatrixFirst);

		// ������� ��� ���������� �������� �� ������� ��������
		// value � �����
		double roundValue(double value);

		// ������� ��� ���������� �������� � ��������� �������
		// matrix � �������
		void applyPrecision(vector<vector<double>>& matrix);



		// ������� ��� �������� ������������� ������� �� �����
		// matrixName � ��� �������
		bool checkMatrixExist(string matrixName);

		// ������� ��� �������� ������������ ��������� �����
		// input � ���� ������������
		bool correctNumberMatrix(string& input);

		// ������� ��� �������� ������������ ����� �������
		// name � ��� �������
		bool correctNameMatrix(string name);

		// ������� ��� �������� ������������ ������� �������
		// str � ���������-���������
		int correctSizeMatrix(const string str);
		
		// ������� ��� ��������, ������� �� �������� ���� ���������
		// oper � ��������
		bool twoOperator(string oper);

		

		// ������� ��� ������� ����� ������� � ������������
		// fladOutMsg � ����, ����� �� �������� ��������� � �����
		string inputNameMatrix(bool fladOutMsg);

		// ������� ��� ����� ����� ������� �� ������������
		void inputMatrix();

		// ������� ��� �������� ��������� ������������� �������
		void deleteMatrix();

		// ������� ��� ������� ����� �������� � ������������
		// strOperand - ������-���������
		string inputMatrixOperand(string strOperand);

		// ������� ��� ���������� �������� ��� ��������� �� ����������������� �����
		void userCalculateMatrix();

		// ������� ��� ��������� �������� ������ �����
		void changePrecision();

		// ������� ��� ����������� �������� ���� ���������
		void menu();

};
