#include "Header.h"

vector<int> Matrix::columnWidths(vector<vector<double>>& matrix)
{
    vector<int> colWidth(matrix[0].size());

    for (int j = 0; j < matrix[0].size(); j++)
    {
        int maxWidth = 0;

        for (int i = 0; i < matrix.size(); i++)
        {
            stringstream ss;
            ss << fixed << setprecision(precision) << matrix[i][j];
            string str = ss.str();
            replace(str.begin(), str.end(), ',', '.');
            if (str.size() > maxWidth) maxWidth = str.size();
        }
        colWidth[j] = maxWidth;
    }

    return colWidth;
}

void Matrix::MatrixOut(vector<vector<double>>& matrix)
{
    vector<int> colWidths = columnWidths(matrix);

    for (int i = 0; i < matrix.size(); i++)
    {
        string strRow = "|";

        for (int j = 0; j < matrix[0].size(); j++)
        {
            stringstream ss;
            ss << fixed << setprecision(precision) << matrix[i][j];
            string str = ss.str();
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
