#include "Header.h"

// ������� ��� �������� ������������� ������� �� �����
// matrixName � ��� �������
bool Matrix::checkMatrixExist(string matrixName)
{
    // ��������, ���� �� ������� � ����� ������
    if (usersMatrix.count(matrixName) == 0) return false;

    return true;
}

// ������� ��� �������� ������������ ��������� �����
// input � ���� ������������
bool Matrix::correctNumberMatrix(string& input)
{
    if (input.empty())
    {
        cout << "������: ���� �� ����� ���� ������" << endl;
        return false;
    }

    if (input == "." or input == "-." or input == "," or input == "-,")
    {
        cout << "������: ������������ ���� '" << input << "', ������ ������� ������ '.', '-.', ',', '-,'" << endl;
        return false;
    }

    if (input.length() > 20)
    {
        cout << "������: ����� '" << input << "' ������� ������� (��������� �� ����� 20 ��������)" << endl;
        return false;
    }

    // �������� �� ������� ����
    for (int i = 0; i < input.size(); i++)
    {
        if (isalpha(input[i]))
        {
            cout << "������: ������� ������������ ��������, ����� �� �����������" << endl;
            return false;
        }
    }
    
    // ������ ����� �� �������
    replace(input.begin(), input.end(), '.', ',');

    // ������� ������� '+' � ������
    int posNotPlus = input.find_first_not_of('+');
    input.erase(0, posNotPlus);

    // ���� ���� ������� ������ �� ������ '+', ������� ������
    if (input.empty())
    {
        cout << "������: ���� �� ����� �������� ������ �� �������� '+'" << endl;
        return false;
    }

    if (input == "-0" or input == "+0") input = '0';

    // ���� ������ ���������� � �������, ��������� ������� ����
    if (input[0] == ',')
    {
        input = '0' + input;
        return true;
    }

    // ����� �������� ������ � ������
    if (input.find('-', 1) != string::npos)
    {
        cout << "������: ����� ����� ���� ������ � ������ �����" << endl;
        return false;
    }

    // ���� ������� �������
    bool hasDecimal = false;

    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i])) continue;
       
        if (input[i] == '-') continue;

        if (input[i] == ',')
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

// ������� ��� �������� ������������ ����� �������
// name � ��� �������
bool Matrix::correctNameMatrix(string name)
{
    if (name.length() > 8) {
        cout << "������: ��� ������� '" << name << "' ������� �������, ��� ������� �� ������ ��������� 8 ��������" << endl;
        return false;
    }

    // ��������, ��� ��� ������� ������ �� ���� � ����, ���������� � �����
    regex pattern("^[A-Za-z][A-Za-z0-9]*$");
    return regex_match(name, pattern);
}

// ������� ��� �������� ������������ ������� �������
// str � ���������-���������
int Matrix::correctSizeMatrix(const string str)
{
    // ���� ��� �������� ������������ �����
    bool validNum;
    string input;

    // ����, ���� �� ����� ���������� ����
    do
    {
        validNum = true;
        cout << str;
        getline(cin, input);

        // ������� � ������ �������
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "back") return -1;

        if (input.empty())
        {
            cout << "������: ���� �� ����� ���� ������" << endl;
            validNum = false;
        }

        if (input.length() > 10)
        {
            cout << "������: �������� '" << input << "' ������� �������, ������ ������� �� ������ ��������� 10 ��������" << endl;
            validNum = false;
        }

        if (input == "0")
        {
            cout << "������: ������ ������� �� ����� ���� ����� '0'" << endl;
            validNum = false;
        }

        // ��������, ��� ������� ������ ����� �����
        if (not all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << "������: ������� ������ ����� �����" << endl;
            validNum = false;
        }
    } while (not validNum);

    // ���������� ������ �������, ��������������� � �����
    return stoi(input);
}

// ������� ��� ��������, ������� �� �������� ���� ���������
// oper � ��������
bool Matrix::twoOperator(string oper)
{
    return (oper == "+" or oper == "-" or oper == "*");
}
