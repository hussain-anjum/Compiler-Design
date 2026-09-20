#include <bits/stdc++.h>
using namespace std;

enum State
{
    q0,
    q1
};

// Check letters and digits
bool isLetter(char ch)
{
    return (ch >= 'A' && ch <= 'Z') ||
           (ch >= 'a' && ch <= 'z');
}

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

// NFA transition function
set<State> transition(State current, char ch)
{
    if (current == q0)
    {
        if (isLetter(ch) || ch == '_')
            return {q1};
    }

    else if (current == q1)
    {
        if (isLetter(ch) || isDigit(ch) || ch == '_')
            return {q1};
    }

    return {};
}

int main()
{
    ifstream file("input8.txt");

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string identifier;

    set<string> keywords = {
        "int", "float", "double", "char", "bool", "void",
        "if", "else", "for", "while", "do", "switch",
        "case", "break", "continue", "return",
        "class", "struct", "true", "false",
        "const", "static", "using", "namespace",
        "auto", "public", "private", "protected",
        "template", "virtual", "new", "delete"};

    while (getline(file, identifier))
    {
        set<State> current = {q0};

        // Process each input character
        for (char ch : identifier)
        {
            set<State> next;

            for (State state : current)
            {
                set<State> result = transition(state, ch);

                next.insert(result.begin(), result.end());
            }

            current = next;

            if (current.empty())
                break;
        }

        cout << "\"" << identifier << "\" --> ";

        // Check accepting state
        if (current.count(q1))
        {
            if (keywords.count(identifier))
                cout << "Reserved Keyword";
            else
                cout << "Accepted by NFA (Valid)";
        }
        else
        {
            cout << "Rejected by NFA (Invalid)";
        }

        cout << endl;
    }

    file.close();

    return 0;
}
