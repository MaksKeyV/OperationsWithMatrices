#include "Header.h"


vector<vector<double>> Matrix::MatrixSumm(vector<vector<double>>& MatrixFirs, vector<vector<double>>& MatrixSecond)
{
	MatrixResult = vector<vector<double>>(MatrixFirs.size(), vector<double>(MatrixFirs[0].size()));

	for (int i = 0; i < MatrixFirs.size(); i++)
		for (int j = 0; j < MatrixFirs[0].size(); j++)
			MatrixResult[i][j] = MatrixFirs[i][j] + MatrixSecond[i][j];
		
	return MatrixResult;
}

vector<vector<double>> Matrix::MatrixSubt(vector<vector<double>>& MatrixFirs, vector<vector<double>>& MatrixSecond)
{
	MatrixResult = vector<vector<double>>(MatrixFirs.size(), vector<double>(MatrixFirs[0].size()));

	for (int i = 0; i < MatrixFirs.size(); i++)
		for (int j = 0; j < MatrixFirs[0].size(); j++)
			MatrixResult[i][j] = MatrixFirs[i][j] - MatrixSecond[i][j];
		
	

	return MatrixResult;
}

double Matrix::MatrixDeterm(vector<vector<double>>& MatrixFirs)
{
	const int sizeMatrix = MatrixFirs.size();
	
	if (sizeMatrix == 1) return MatrixFirs[0][0];

	else if (sizeMatrix == 2) return ((MatrixFirs[0][0] * MatrixFirs[1][1]) - (MatrixFirs[1][0] * MatrixFirs[0][1]));

	else if (sizeMatrix == 3) return ((MatrixFirs[0][0] * MatrixFirs[1][1] * MatrixFirs[2][2]) 
		+ (MatrixFirs[0][1] * MatrixFirs[1][2] * MatrixFirs[2][0]) 
		+ (MatrixFirs[2][1] * MatrixFirs[1][0] * MatrixFirs[0][2]) 
		- (MatrixFirs[0][2] * MatrixFirs[1][1] * MatrixFirs[2][0]) 
		- (MatrixFirs[0][0] * MatrixFirs[1][2] * MatrixFirs[2][1]) 
		- (MatrixFirs[0][1] * MatrixFirs[1][0] * MatrixFirs[2][2]));
	else
	{
		double DetermResult = 0;
		
		for (int i = 0; i < MatrixFirs.size(); i++)
		{
			vector<vector<double>> minorMatrix(sizeMatrix - 1, vector<double>(sizeMatrix - 1));

			for (int j = 1; j < MatrixFirs[0].size(); j++)
			{
				int collumIndex = 0;
				for (int collum = 0; collum < MatrixFirs.size(); collum++)
				{
					if (collum == i) continue;

					minorMatrix[j - 1][collumIndex] = MatrixFirs[j][collum];
					collumIndex++;

				}
			}
			DetermResult += (i % 2 == 0 ? 1 : (-1)) * MatrixFirs[0][i] * MatrixDeterm(minorMatrix);
		}

		return DetermResult;
	}
}

vector<vector<double>> Matrix::MatrixMultiplication(vector<vector<double>>& MatrixFirs, vector<vector<double>>& MatrixSecond)
{
	MatrixResult = vector<vector<double>>(MatrixFirs.size(), vector<double>(MatrixSecond[0].size()));

	for (int i = 0; i < MatrixFirs.size(); i++)
	{
		for (int j = 0; j < MatrixSecond[0].size(); j++)
		{
			MatrixResult[i][j] = 0;
			for (int k = 0; k < MatrixSecond.size(); k++)
			{
				MatrixResult[i][j] += MatrixFirs[i][k] * MatrixSecond[k][j];
			}
		}
	}

	return MatrixResult;
}

vector<vector<double>> Matrix::MatrixMultiplicationConst(vector<vector<double>>& MatrixFirs, double constValue)
{
	MatrixResult = vector<vector<double>>(MatrixFirs.size(), vector<double>(MatrixFirs[0].size()));

	for (int i = 0; i < MatrixFirs.size(); i++)
		for (int j = 0; j < MatrixFirs[0].size(); j++)
			MatrixResult[i][j] = MatrixFirs[i][j] * constValue;

	return MatrixResult;
}

vector<vector<double>> Matrix::MatrixTranspose(vector<vector<double>>& MatrixFirs)
{
	MatrixResult = vector<vector<double>>(MatrixFirs[0].size(), vector<double>(MatrixFirs.size()));

	for (int i = 0; i < MatrixFirs.size(); i++)
		for (int j = 0; j < MatrixFirs[0].size(); j++)
			MatrixResult[j][i] = MatrixFirs[i][j];
		
	return MatrixResult;
}

double Matrix::MatrixNormMax(vector<vector<double>>& MatrixFirs)
{
	double maxValue = 0;

	for (auto i : MatrixFirs) maxValue = max(maxValue, *max_element(i.begin(), i.end()));

	return maxValue;
}

double Matrix::MatrixNormM(vector<vector<double>>& MatrixFirs)
{
	double maxValueNorm = 0;

	for (int i = 0; i < MatrixFirs.size(); i++)
	{
		double valueNorm = 0;
		for (int j = 0; j < MatrixFirs[0].size(); j++)
			valueNorm += abs(MatrixFirs[i][j]);
		maxValueNorm = max(maxValueNorm, valueNorm);
	}

	return maxValueNorm;
}

double Matrix::MatrixNormL(vector<vector<double>>& MatrixFirs)
{
	double maxValueNorm = 0;

	for (int i = 0; i < MatrixFirs[0].size(); i++)
	{
		double valueNorm = 0;
		for (int j = 0; j < MatrixFirs.size(); j++)
			valueNorm += abs(MatrixFirs[j][i]);
		maxValueNorm = max(maxValueNorm, valueNorm);
	}

	return maxValueNorm;
}

double Matrix::MatrixNorm(vector<vector<double>>& MatrixFirs)
{
	double sumValueNorm = 0;

	for (int i = 0; i < MatrixFirs.size(); i++)
		for (int j = 0; j < MatrixFirs[i].size(); j++)
			sumValueNorm += pow(MatrixFirs[i][j], 2);

	return sqrt(sumValueNorm);
}

vector<vector<double>> Matrix::MatrixInverse(vector<vector<double>>& MatrixFirs)
{
	double determ = MatrixDeterm(MatrixFirs);
	if (determ == 0) throw string("Матрица не обратима, определитель равен 0");

	MatrixResult = vector<vector<double>>(MatrixFirs.size(), vector<double>(MatrixFirs[0].size()));
	int sizeMatrix = MatrixFirs.size();

	if (sizeMatrix == 1)
	{
		MatrixResult[0][0] = 1.0 / (MatrixFirs[0][0]);
		return MatrixResult;
	}

	vector<vector<double>> matrix = vector<vector<double>>(MatrixFirs.size(), vector<double>(MatrixFirs[0].size()));

	for (int i = 0; i < MatrixFirs.size(); i++)
	{
		for (int j = 0; j < MatrixFirs[0].size(); j++)
		{
			vector<vector<double>> minorMatrix(sizeMatrix - 1, vector<double>(sizeMatrix - 1));
			
			int collumIndex = 0;

			for (int collum = 0; collum < MatrixFirs.size(); collum++)
			{
				if (collum == j) continue;
				int rowIndex = 0;

				for (int row = 0; row < MatrixFirs.size(); row++)
				{
					if (row == i) continue;

					minorMatrix[rowIndex][collumIndex] = MatrixFirs[row][collum];
					rowIndex++;
				}
				collumIndex++;
			}
			matrix[i][j] += ((i + j) % 2 == 0 ? 1 : (-1)) * MatrixDeterm(minorMatrix);
		}
	}

	matrix = MatrixTranspose(matrix);

	return MatrixResult = MatrixMultiplicationConst(matrix, (1.0 / determ));
}

int Matrix::MatrixRang(vector<vector<double>>& MatrixFirs) 
{
	int rank = MatrixFirs[0].size();;

	for (int row = 0; row < rank; row++) 
	{
		if (MatrixFirs[row][row] != 0) 
		{
			for (int collum = 0; collum < MatrixFirs.size(); collum++)
			{
				if (collum != row)
				{
					double mult = MatrixFirs[collum][row] / MatrixFirs[row][row];

					for (int i = 0; i < rank; i++) 
						MatrixFirs[collum][i] -= mult * MatrixFirs[row][i];
				}
			}
		}
		else 
		{
			bool reduce = true;
			
			for (int i = row + 1; i < MatrixFirs.size(); i++)
			{
				if (MatrixFirs[i][row] != 0) 
				{
					swap(MatrixFirs[row], MatrixFirs[i]);
					reduce = false;
					break;
				}
			}
			
			if (reduce) 
			{
				rank--;
				for (int i = 0; i < MatrixFirs.size(); i++)
					MatrixFirs[i][row] = MatrixFirs[i][rank];
			}
			row--;
		}
	}
	return rank;
}

void Matrix::outputAllMatrix()
{
	if (usersMatrix.empty())
	{
		cout << "Нет сохраненных матриц" << endl << endl;
		return;
	}

	for (auto i : usersMatrix)
	{
		cout << "Матрица '" << i.first << "':" << endl;

		MatrixOut(i.second); 
		cout << endl;
	}
}

