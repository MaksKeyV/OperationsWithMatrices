#include "Header.h"


bool Matrix::checkMatrixExist(string matrixName)
{
    if (usersMatrix.count(matrixName) == 0) return false;

    return true;
}

bool Matrix::correctNumberMatrix(string& input)
{
    if (input.empty())
    {
        cout << "������: ���� �� ����� ���� ������" << endl;
        return false;
    }

    if (input == "." or input == "-." or input == "," or input == "-,")
    {
        cout << "������: ������������ �����" << endl;
        return false;
    }

    if (numeric_limits<double>::max)
    {
        //cout << "������: ������� ����� ������� ������" << endl;
        //return false;
    }

    bool hasDecimal = false;

    replace(input.begin(), input.end(), '.', ',');

    if (input == "-0" or input == "+0") 
        input = '0';

    if (input[0] == ',')
    {
        input = '0' + input;
        return true;
    }

    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i])) continue;

        if (input[i] == '-' && i == 0)
        {
            continue;
        }
        else if (input[i] == '-' && i != 0)
        {
            cout << "������: ����� ����� ���� ������ � ������ �����" << endl;
            return false;
        }
        else if (input[i] == ',')
        {
            if (hasDecimal)
            {
                cout << "������: ������� ����� ��� ������������" << endl;
                return false;
            }
            hasDecimal = true;
            continue;
        }

        cout << "������: ������������ ������ '" << input[i] << "'" << endl;
        return false;
    }

    return true;
}

bool Matrix::correctNameMatrix(string name)
{
    regex pattern("^[A-Za-z][A-Za-z0-9]*$");
    return regex_match(name, pattern);
}

int Matrix::correctSizeMatrix(const string prompt)
{
    bool validNum;
    string input;

    do
    {
        validNum = true;
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "������: ���� �� ����� ���� ������" << endl;
            validNum = false;
            continue;
        }

        if (numeric_limits<double>::max)
        {
            //cout << "������: ������ ������� ����� ������� ������" << endl;
            //return false;
        }

        if (input == "0")
        {
            cout << "������: ������ ������� �� ����� ���� ����� '0'" << endl;
            validNum = false;
            continue;
        }

        for (int i = 0; i < input.size(); i++)
        {
            if (!isdigit(input[i]))
            {
                cout << "������: ������� ������ ����� �����" << endl;
                validNum = false;
                break;
            }
        }
    } while (not validNum);

    return stoi(input);
}

bool Matrix::twoOperator(string oper)
{
    return (oper == "+" or oper == "-" or oper == "*");
}
