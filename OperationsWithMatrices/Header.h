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
namespace fs = filesystem;


class Matrix
{
	public:
		vector<vector<double>> MatrixResult;
		map<string, vector<vector<double>>> usersMatrix;
		const set<string> Operations = { "+", "-", "*", "Det", "T", "Norm", "Inv", "Rang"};
		int precision = 3;
		

		vector<vector<double>> MatrixSumm(vector<vector<double>>& MatrixFirs, vector<vector<double>>& MatrixSecond);

		vector<vector<double>> MatrixSubt(vector<vector<double>>& MatrixFirs, vector<vector<double>>& MatrixSecond);

		double MatrixDeterm(vector<vector<double>>& MatrixFirs);

		vector<vector<double>> MatrixMultiplication(vector<vector<double>>& MatrixFirs, vector<vector<double>>& MatrixSecond);

		vector<vector<double>> MatrixMultiplicationConst(vector<vector<double>>& MatrixFirs, double constValue);

		vector<vector<double>> MatrixTranspose(vector<vector<double>>& MatrixFirs);

		double MatrixNormMax(vector<vector<double>>& MatrixFirs);

		double MatrixNormM(vector<vector<double>>& MatrixFirs);

		double MatrixNormL(vector<vector<double>>& MatrixFirs);

		double MatrixNorm(vector<vector<double>>& MatrixFirs);

		vector<vector<double>> MatrixInverse(vector<vector<double>>& MatrixFirs);

		int MatrixRang(vector<vector<double>>& MatrixFirs);

		void outputAllMatrix();
		
		void MatrixOut(vector<vector<double>>& MatrixFirs);



		void executeMatrix(string oper, string first_, string second_);

		void executeMatrix(string oper, string first_);

		bool requestSaveResult();

		void saveResult();
		


		bool checkMatrixExist(string matrixName);

		bool correctNumberMatrix(string& input);

		bool correctNameMatrix(string name);

		int correctSizeMatrix(const string prompt);
		
		bool twoOperator(string oper);

		vector<int> columnWidths(vector<vector<double>>& matrix);

		void changePrecision();



		string inputNameMatrix(bool fladOutMsg);

		void inputMatrix();

		void deleteMatrix();

		string inputMatrixOperand(string strOperand);

		void userCalculateMatrix();

		void menu();
};
