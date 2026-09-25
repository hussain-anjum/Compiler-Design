#include <bits/stdc++.h>
using namespace std;

enum State
{
    q0, // Start state: no character has been read yet.
    q1  // Accepting state: a valid identifier has been read.
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
    set<State> nextStates;

    if (current == q0)
    {
        // The first character must be a letter or underscore.
        if (isLetter(ch) || ch == '_')
            nextStates.insert(q1);
    }

    else if (current == q1)
    {
        // After the first character, digits are also allowed.
        if (isLetter(ch) || isDigit(ch) || ch == '_')
            nextStates.insert(q1);
    }

    // An empty set means there is no transition for this character.
    return nextStates;
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
        set<State> current;
        current.insert(q0);

        // Process each input character
        for (int i = 0; i < (int)identifier.length(); i++)
        {
            char ch = identifier[i];
            set<State> next;

            // Visit each state in the current set.
            for (State state : current)
            {
                set<State> result = transition(state, ch);

                // Add the reachable states one at a time.
                for (State nextState : result)
                {
                    next.insert(nextState);
                }
            }

            current = next;

            // No reachable state means the identifier is invalid.
            if (current.empty())
                break;
        }

        cout << "\"" << identifier << "\" --> ";

        // count(q1) is 1 when q1 is present, otherwise 0.
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
