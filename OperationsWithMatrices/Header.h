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

// Класс с операциями (+, -, *) над матрицами
class MathMatrix 
{
public:
	// Двумерный вектор для хранения элементов матрицы
	vector<vector<double>> matrixData;

	// Конструктор по умолчанию
	MathMatrix() = default;

	// Конструктор с инициализацией матрицы
	// inputData – входная матрица
	MathMatrix(vector<vector<double>> inputData) : matrixData(inputData) {};

	// Перегрузка оператора сложения двух матриц
	// secondMatrix – матрица, с которой складываем текущую
	MathMatrix operator+(MathMatrix& secondMatrix);

	// Перегрузка оператора вычитания двух матриц
	// secondMatrix – матрица, которую вычитаем из текущей
	MathMatrix operator-(MathMatrix& secondMatrix);

	// Перегрузка оператора умножения двух матриц
	// secondMatrix – матрица, на которую умножается текущая
	MathMatrix operator*(MathMatrix& secondMatrix);

	// Перегрузка оператора умножения матрицы на число
	// number – число, на которое умножаем матрицу
	MathMatrix operator*(double number);

	// Перегрузка оператора умножения числа на матрицу
	// number – множитель
	// matrix – матрица-множимое
	friend MathMatrix operator*(double number, MathMatrix& matrix);
};

// Класс для матричных операций
class Matrix
{
	public:
		// Вектор для хранения результата операции над матрицами
		vector<vector<double>> MatrixResult;

		// Словарь, содержащий пользовательские матрицы
		map<string, vector<vector<double>>> usersMatrix;

		// Множество допустимых операций над матрицами 
		const set<string> Operations = { "+", "-", "*", "Det", "T", "Norm", "Inv", "Rang"};
		
		// Точность отображения
		int precision = 3;
		 
		// Функция для вычисления определителя матрицы
		// MatrixFirst – матрица
		double MatrixDeterm(vector<vector<double>>& MatrixFirst);

		// Функция для транспонирования матрицы
		// MatrixFirst – матрица
		vector<vector<double>> MatrixTranspose(vector<vector<double>>& MatrixFirst);

		// Функция для вычисления максимальной нормы матрицы
		// MatrixFirst – матрица
		double MatrixNormMax(vector<vector<double>>& MatrixFirst);

		// Функция для вычисления нормы строки матрицы (норма M)
		// MatrixFirst – матрица
		double MatrixNormM(vector<vector<double>>& MatrixFirst);

		// Функция для вычисления нормы столбца матрицы (норма L)
		// MatrixFirst – матрица
		double MatrixNormL(vector<vector<double>>& MatrixFirst);

		// Функция для вычисления Евклидовой нормы матрицы
		// MatrixFirst – матрица
		double MatrixNorm(vector<vector<double>>& MatrixFirst);

		// Функция для вычисления обратной матрицы
		// MatrixFirst – матрица
		vector<vector<double>> MatrixInverse(vector<vector<double>>& MatrixFirst);

		// Функция для вычисления ранга матрицы
		// MatrixFirst – матрица
		int MatrixRang(vector<vector<double>>& MatrixFirst);

		// Преобразование строки в объект MathMatrix (по имени матрицы или числу)
		// input – строка, представляющая имя матрицы или число
		MathMatrix OperandToMatrix(string input);

		// Функция для вывода всех пользовательских матриц
		void outputAllMatrix();
		


	

		// Функция для выполнения операции над двумя матрицами
		// oper – операция
		// first_ – первая матрица
		// second_ – вторая матрица
		void executeMatrix(string oper, string first_, string second_);

		// Функция для выполнения операции над одной матрицей
		// oper – операция
		// first_ – матрица
		void executeMatrix(string oper, string first_);

		// Функция для запроса у пользователя сохранения результата операции
		bool requestSaveResult();

		// Функция для сохранения результата операции
		void saveResult();
		


		// Функция для вычисления ширины колонок матрицы при форматированном выводе
		// matrix – матрица
		vector<int> columnWidths(vector<vector<double>>& matrix);

		// Функция для вывода одной матрицы
		// MatrixFirst – матрица
		void MatrixOut(vector<vector<double>>& MatrixFirst);

		// Функция для округления значения по текущей точности
		// value – число
		double roundValue(double value);

		// Функция для применения точности к элементам матрицы
		// matrix – матрица
		void applyPrecision(vector<vector<double>>& matrix);



		// Функция для проверки существования матрицы по имени
		// matrixName – имя матрицы
		bool checkMatrixExist(string matrixName);

		// Функция для проверки корректности числового ввода
		// input – ввод пользователя
		bool correctNumberMatrix(string& input);

		// Функция для проверки корректности имени матрицы
		// name – имя матрицы
		bool correctNameMatrix(string name);

		// Функция для проверки корректности размера матрицы
		// str – сообщение-подсказка
		int correctSizeMatrix(const string str);
		
		// Функция для проверки, требует ли операция двух операндов
		// oper – оператор
		bool twoOperator(string oper);


		// Функция для запроса имени матрицы у пользователя
		// fladOutMsg – флаг, нужно ли выводить сообщение о вводе
		string inputNameMatrix(bool fladOutMsg);

		// Функция для ввода новой матрицы от пользователя
		void inputMatrix();

		// Функция для удаления выбранной пользователем матрицы
		void deleteMatrix();

		// Функция для запроса имени операнда у пользователя
		// strOperand - строка-подсказка
		string inputMatrixOperand(string strOperand);

		// Функция для выполнения операций над матрицами по пользовательскому вводу
		void userCalculateMatrix();

		// Функция для изменения точности вывода чисел
		void changePrecision();

		// Функция для отображения главного меню программы
		void menu();

};
