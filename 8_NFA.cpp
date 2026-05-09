#include <bits/stdc++.h>
using namespace std;

enum State {q0,q1,rejcet};

State transition(State current, char ch)
{
    switch (current)
    {
    case q0:
        // q0, start state
        if (isalpha(ch) || ch == '_')
            return q1;
        else
            return rejcet;

    case q1:
        // q1, accepting state
        if (isalpha(ch) || isdigit(ch) || ch == '_')
            return q1;
        else
            return rejcet;

    case rejcet:
        return rejcet;
    }
    return rejcet;
}

int main()
{
    ifstream file("input8.txt");
    string identifier;

    set<string> keywords = {
        "int", "float", "double", "char", "bool", "void",
        "if", "else", "for", "while", "do", "switch", "case",
        "break", "continue", "return", "class", "struct",
        "true", "false", "const", "static", "using", "namespace"};

    cout << endl;
    while (getline(file, identifier))
    {
        if (identifier.empty())
            continue;

        State current = q0;

        for (int i = 0; i < identifier.length(); i++)
        {
            current = transition(current, identifier[i]);
            if (current == rejcet)
                break;
        }

        cout << "\"" << identifier << "\" --> ";

        // accept if final state is q1 and not a keyword
        if (current == q1 && !keywords.count(identifier))
            cout << "Accepted by NFA (Valid)" << endl << endl;
        else if (keywords.count(identifier))
            cout << "Reserved Keyword" << endl;
        else
            cout << "Rejected by NFA (Invalid)" << endl << endl;
    }

    file.close();
    return 0;
}
