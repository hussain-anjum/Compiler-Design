#include <bits/stdc++.h>
using namespace std;

enum State
{
    q0,
    q1,
    q2,
    q3,
    dead
};

set<char> singleOps = {
    '+', '-', '*', '/', '%',
    '=', '<', '>',
    '!', '&', '|', '^', '~'};

set<string> doubleOps = {
    "==", "!=", "<=", ">=",
    "&&", "||", "++", "--",
    "+=", "-=", "*=", "/=",
    "<<", ">>"};

set<string> keywords = {
    "int", "float", "double", "char", "bool", "void",
    "if", "else", "for", "while", "do", "switch", "case",
    "break", "continue", "return", "class", "struct",
    "true", "false", "const", "static", "using", "namespace"};

State transition(State current, char ch)
{
    switch (current)
    {
    case q0:
        if (isalpha(ch) || ch == '_')
            return q1;
        if (isdigit(ch))
            return q2;
        if (singleOps.count(ch))
            return q3;
        return dead;

    case q1:
        if (isalpha(ch) || isdigit(ch) || ch == '_')
            return q1;
        return dead;

    case q2:
        if (isdigit(ch))
            return q2;
        if (ch == '.')
            return q2;
        return dead;

    case q3:
        return dead;

    default:
        return dead;
    }
}

int main()
{
    ifstream file("input9.txt");
    string token;

    cout << endl;
    while (getline(file, token))
    {
        if (token.empty())
            continue;

        // check double operator
        if (token.length() == 2 && doubleOps.count(token))
        {
            cout << "\"" << token << "\" --> Operator (Double)" << endl;
            continue;
        }

        State current = q0;
        for (int i = 0; i < token.length(); i++)
        {
            current = transition(current, token[i]);
            if (current == dead)
                break;
        }

        cout << "\"" << token << "\" --> ";

        if (current == q1)
        {
            if (keywords.count(token))
                cout << "Keyword" << endl;
            else
                cout << "Identifier" << endl;
        }
        else if (current == q2)
            cout << "Constant" << endl;
        else if (current == q3)
            cout << "Operator (Single)" << endl;
        else
            cout << "Invalid Token" << endl;
    }

    file.close();
    return 0;
}