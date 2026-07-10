#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input10.txt");
    string line;
    bool inMultiLine = false;

    set<string> keywords = {
        "int", "float", "double", "char", "bool", "void",
        "if", "else", "for", "while", "do", "switch", "case",
        "break", "continue", "return", "class", "struct",
        "true", "false", "const", "static", "using", "namespace"};

    set<char> singleOps = {
        '+', '-', '*', '/', '%',
        '=', '<', '>',
        '!', '&', '|', '^', '~'};

    set<string> doubleOps = {
        "==", "!=", "<=", ">=",
        "&&", "||", "++", "--",
        "+=", "-=", "*=", "/=",
        "<<", ">>"};

    cout << endl;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        int i = 0;

        while (i < line.length())
        {
            if (line[i] == ' ' || line[i] == '\t')
            {
                i++;
                continue;
            }
            // check inside a multi-line comment or not
            if (inMultiLine)
            {
                if (i + 1 < line.length() && line[i] == '*' && line[i + 1] == '/')
                {
                    inMultiLine = false;
                    i += 2;
                }
                else
                {
                    i++;
                }
                continue;
            }

            // check single comment
            if (i + 1 < line.length() && line[i] == '/' && line[i + 1] == '/')
            {
                break;
            }

            // check start /* or not
            if (i + 1 < line.length() && line[i] == '/' && line[i + 1] == '*')
            {
                inMultiLine = true;
                i += 2;
                continue;
            }

            // check double op
            if (i + 1 < line.length())
            {
                string two = string(1, line[i]) + string(1, line[i + 1]);
                if (doubleOps.count(two))
                {
                    // cout << "Token: " << two << " --> Operator" << endl;
                    cout << two << endl;
                    i += 2;
                    continue;
                }
            }

            // check single op
            if (singleOps.count(line[i]))
            {
                // cout << "Token: " << line[i] << "  --> Operator" << endl;
                cout << line[i] << endl;
                i++;
                continue;
            }

            if (isalpha(line[i]) || line[i] == '_')
            {
                string token = "";
                while (i < line.length() && (isalpha(line[i]) || isdigit(line[i]) || line[i] == '_'))
                {
                    token += line[i];
                    i++;
                }
                if (keywords.count(token))
                    // cout << "Token: " << token << " --> Keyword" << endl;
                    cout << token << endl;
                else
                    // cout << "Token: " << token << " --> Identifier" << endl;
                    cout << token << endl;
                continue;
            }

            // check constant
            if (isdigit(line[i]))
            {
                string token = "";
                while (i < line.length() && (isdigit(line[i]) || line[i] == '.'))
                {
                    token += line[i];
                    i++;
                }
                // cout << "Token: " << token << " --> Constant" << endl;
                cout << token << endl;
                continue;
            }

            if (line[i] == ';' || line[i] == '(' || line[i] == ')' ||
                line[i] == '{' || line[i] == '}')
            {
                i++;
                continue;
            }
            // cout << "Token: " << line[i] << " --> Unknown" << endl;
            i++;
        }
    }

    file.close();
    return 0;
}
