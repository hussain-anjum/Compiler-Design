#include <bits/stdc++.h>
using namespace std;

enum State
{
    q0,  // Start state.
    q1,  // Identifier or keyword.
    q2,  // Integer, such as 42.
    q3,  // Single-character operator.
    q4,  // Decimal point read; a digit must come next.
    q5,  // Decimal number, such as 3.14.
    dead // Invalid token.
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

// A DFA has exactly one next state for each state and input character.
State transition(State current, char ch)
{
    switch (current)
    {
    case q0:
        // The first character decides which type of token to check.
        if (isalpha(ch) || ch == '_')
            return q1;
        if (isdigit(ch))
            return q2;
        if (singleOps.count(ch))
            return q3;
        return dead;

    case q1:
        // Identifiers may contain letters, digits and underscores.
        if (isalpha(ch) || isdigit(ch) || ch == '_')
            return q1;
        return dead;

    case q2:
        // More digits keep the number an integer; a dot starts a decimal.
        if (isdigit(ch))
            return q2;
        if (ch == '.')
            return q4;
        return dead;

    case q3:
        // Double operators are checked separately in main().
        return dead;

    case q4:
        // A decimal point alone is not enough: require a digit after it.
        if (isdigit(ch))
            return q5;
        return dead;

    case q5:
        if (isdigit(ch))
            return q5;
        return dead;

    default:
        return dead;
    }
}

int main()
{
    ifstream file("input9.txt");
    string token;

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    cout << endl;

    while (getline(file, token))
    {
        if (token.empty())
            continue;

        // Recognize a listed double operator before running the DFA.
        if (token.length() == 2 && doubleOps.count(token))
        {
            cout << "\"" << token
                 << "\" --> Operator (Double)" << endl;
            continue;
        }

        State current = q0;

        // Read the token one character at a time.
        for (int i = 0; i < (int)token.length(); i++)
        {
            current = transition(current, token[i]);

            if (current == dead)
                break;
        }

        cout << "\"" << token << "\" --> ";

        // Classify the token using its final state.
        if (current == q1)
        {
            if (keywords.count(token))
                cout << "Keyword" << endl;
            else
                cout << "Identifier" << endl;
        }
        else if (current == q2 || current == q5)
        {
            cout << "Constant" << endl;
        }
        else if (current == q3)
        {
            cout << "Operator (Single)" << endl;
        }
        else
        {
            cout << "Invalid Token" << endl;
        }
    }

    file.close();
    return 0;
}
