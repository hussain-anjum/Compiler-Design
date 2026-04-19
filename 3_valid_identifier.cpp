#include <bits/stdc++.h>
using namespace std;

int main()
{
    set<string> keywords = {
        "int", "float", "double", "char", "bool", "void",
        "if", "else", "for", "while", "do", "switch", "case",
        "break", "continue", "return", "class", "struct",
        "public", "private", "protected", "new", "delete",
        "true", "false", "const", "static", "include", "using",
        "namespace", "cout", "cin", "endl", "string", "auto"};

    ifstream file("input3.txt");

    string identifier;

    cout << endl;
    while (getline(file, identifier))
    {
        if (identifier.empty())
            continue;

        bool isValid = true;

        if (!isalpha(identifier[0]) && identifier[0] != '_')
        {
            isValid = false;
        }
        else
        {
            for (int i = 1; i < identifier.length(); i++)
            {
                if (!isalpha(identifier[i]) && !isdigit(identifier[i]) && identifier[i] != '_')
                {
                    isValid = false;
                    break;
                }
            }
        }
        if (isValid && keywords.count(identifier))
        {
            isValid = false;
        }

        cout << identifier << " --> ";
        if (isValid)
            cout << "Valid Identifier" << endl;
        else
            cout << "Invalid Identifier" << endl;
    }

    file.close();
    return 0;
}