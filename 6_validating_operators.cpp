#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input5.txt");
    string line;

    set<char> singleOps = {
        '+', '-', '*', '/', '%',
        '=', '<', '>',
        '!', '&', '|', '^', '~'};

    set<string> doubleOps = {
        "==", "!=", "<=", ">=",
        "&&", "||", "++", "--",
        "+=", "-=", "*=", "/="};

    cout << endl;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        bool isValid = true;
        int i = 0;

        while (i < line.length())
        {
            if (line[i] == ' ' || line[i] == '\t' ||
                isalpha(line[i]) || isdigit(line[i]) || line[i] == '_' ||
                line[i] == ';' || line[i] == '(' ||
                line[i] == ')' || line[i] == '{' || line[i] == '}')
            {
                i++;
                continue;
            }

            // check double operator
            if (i + 1 < line.length())
            {
                string two = string(1, line[i]) + string(1, line[i + 1]);
                if (doubleOps.count(two))
                {
                    i += 2;
                    continue;
                }
            }

            // check single operator
            if (singleOps.count(line[i]))
            {
                i++;
                continue;
            }

            // unknown character found
            isValid = false;
            break;
        }

        cout << line << " ---> ";
        if (isValid)
            cout << "Valid Operator" << endl;
        else
            cout << "Invalid Operator" << endl;
    }

    file.close();
    return 0;
}