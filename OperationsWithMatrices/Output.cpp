#include "Header.h"

// ������� ��� ���������� ������ ������� ������� ��� ��������������� ������
// matrix � �������
vector<int> Matrix::columnWidths(vector<vector<double>>& matrix)
{
    // ������ ��� �������� ������ ������ �������
    vector<int> colWidth(matrix[0].size());

    // ������ �� �������� �������
    for (int j = 0; j < matrix[0].size(); j++)
    {
        int maxWidth = 0;

        // ������ �� ������� �������
        for (int i = 0; i < matrix.size(); i++)
        {
            stringstream sstr;
            // ��������� ������ ��������
            sstr << fixed << setprecision(precision) << matrix[i][j];
            string str = sstr.str();
            // ������ ������� �� �����
            replace(str.begin(), str.end(), ',', '.');

            // ��������, �������� �� ������� ������ ����� ������� � �������
            if (str.size() > maxWidth) maxWidth = str.size();
        }
        colWidth[j] = maxWidth;
    }

    return colWidth;
}

// ������� ��� ������ ����� �������
// matrix � �������
void Matrix::MatrixOut(vector<vector<double>>& matrix)
{
    // �������� ������ ������� ������� ��� ������������
    vector<int> colWidths = columnWidths(matrix);

    // ������ �� ������� �������
    for (int i = 0; i < matrix.size(); i++)
    {
        string strRow = "|";

        // ������ �� �������� �������
        for (int j = 0; j < matrix[0].size(); j++)
        {
            stringstream sstr;
            // ��������� ������ ��������
            sstr << fixed << setprecision(precision) << matrix[i][j];
            string str = sstr.str();
            // ������ ������� �� �����
            replace(str.begin(), str.end(), ',', '.');

            stringstream formatted;
            formatted << setw(colWidths[j]) << str;

            if (j != 0) strRow += " ";
            strRow += formatted.str();
        }

        strRow += "|";
        cout << strRow << endl;
    }
}

// ������� ��� ���������� �������� �� ������� ��������
// value � �����
double Matrix::roundValue(double value)
{
    // ��������� �������
    double degreRound = pow(10, precision);

    // ��������� ����� � ���������� ���������
    return round(value * degreRound) / degreRound;
}

// ������� ��� ���������� �������� � ��������� �������
// matrix � �������
void Matrix::applyPrecision(vector<vector<double>>& matrix)
{
    // ������ �� ���� ��������� ������ ��������� � �� ��������
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[0].size(); j++)
            // ��������� �������� �� �������� �������� � ���������
            matrix[i][j] = roundValue(matrix[i][j]);
}
