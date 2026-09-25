#include <bits/stdc++.h>
using namespace std;

vector<string> nonTerminals;
vector<string> heads;
vector<vector<string>> rules;
vector<vector<string>> first;

// Return the position of a non-terminal, or -1 for a terminal.
int findNonTerminal(string symbol)
{
    for (int i = 0; i < (int)nonTerminals.size(); i++)
        if (nonTerminals[i] == symbol)
            return i;
    return -1;
}

bool contains(vector<string> values, string symbol)
{
    for (int i = 0; i < (int)values.size(); i++)
        if (values[i] == symbol)
            return true;
    return false;
}

// & lets this function update the original vector.
// Return true only when a NEW symbol is added.
bool addSymbol(vector<string>& values, string symbol)
{
    if (contains(values, symbol))
        return false;
    values.push_back(symbol);
    return true;
}

vector<string> split(string text)
{
    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word)
        words.push_back(word);
    return words;
}

bool readGrammar(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        if (split(line).empty())
            continue;
        size_t arrow = line.find("->");
        if (arrow == string::npos)
        {
            cout << "Missing -> in: " << line << endl;
            return false;
        }
        vector<string> head = split(line.substr(0, arrow));
        if (head.size() != 1 || head[0] == "e")
        {
            cout << "Use one non-terminal before ->." << endl;
            return false;
        }
        addSymbol(nonTerminals, head[0]);

        string rhs = line.substr(arrow + 2) + "|";
        string alternative = "";
        for (int i = 0; i < (int)rhs.length(); i++)
        {
            if (rhs[i] != '|')
                alternative += rhs[i];
            else
            {
                vector<string> rule = split(alternative);
                if (rule.empty() || (rule.size() > 1 && contains(rule, "e")))
                {
                    cout << "Use e alone for an empty alternative." << endl;
                    return false;
                }
                heads.push_back(head[0]);
                rules.push_back(rule);
                alternative = "";
            }
        }
    }
    if (nonTerminals.empty())
    {
        cout << "No productions found." << endl;
        return false;
    }
    first.resize(nonTerminals.size());
    return true;
}

void computeFirst()
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < (int)rules.size(); i++)
        {
            int a = findNonTerminal(heads[i]);
            bool allNullable = true;

            // Scan the right side from left to right.
            for (int j = 0; j < (int)rules[i].size(); j++)
            {
                string symbol = rules[i][j];
                if (symbol == "e")
                    continue;

                int b = findNonTerminal(symbol);
                if (b == -1)
                {
                    // A terminal goes directly into FIRST(A).
                    if (addSymbol(first[a], symbol))
                        changed = true;
                    allNullable = false;
                    break;
                }

                // Copy FIRST(B), except epsilon, into FIRST(A).
                for (int k = 0; k < (int)first[b].size(); k++)
                {
                    if (first[b][k] != "e")
                        if (addSymbol(first[a], first[b][k]))
                            changed = true;
                }
                if (!contains(first[b], "e"))
                {
                    allNullable = false;
                    break;
                }
            }
            if (allNullable)
                if (addSymbol(first[a], "e"))
                    changed = true;
        }
    }
}

void printSet(string label, string head, vector<string> values)
{
    cout << label << "(" << head << ") = { ";
    for (int i = 0; i < (int)values.size(); i++)
    {
        if (i != 0)
            cout << ", ";
        cout << values[i];
    }
    cout << " }" << endl;
}
vector<vector<string>> follow;

void computeFollow()
{
    follow.resize(nonTerminals.size());
    // Rule 1: The start symbol gets $.
    follow[0].push_back("$");

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < (int)rules.size(); i++)
        {
            int a = findNonTerminal(heads[i]);
            for (int j = 0; j < (int)rules[i].size(); j++)
            {
                int b = findNonTerminal(rules[i][j]);
                if (b == -1)
                    continue;

                // Rule 2: Add FIRST of the part after B, except epsilon.
                bool restNullable = true;
                for (int k = j + 1; k < (int)rules[i].size(); k++)
                {
                    string symbol = rules[i][k];
                    int c = findNonTerminal(symbol);
                    if (c == -1)
                    {
                        if (addSymbol(follow[b], symbol))
                            changed = true;
                        restNullable = false;
                        break;
                    }
                    for (int m = 0; m < (int)first[c].size(); m++)
                    {
                        if (first[c][m] != "e")
                            if (addSymbol(follow[b], first[c][m]))
                                changed = true;
                    }
                    if (!contains(first[c], "e"))
                    {
                        restNullable = false;
                        break;
                    }
                }

                // Rule 3: If nothing follows B, or the rest can become
                // epsilon, copy FOLLOW(A) into FOLLOW(B).
                if (restNullable)
                {
                    for (int k = 0; k < (int)follow[a].size(); k++)
                        if (addSymbol(follow[b], follow[a][k]))
                            changed = true;
                }
            }
        }
    }
}

int main()
{
    if (!readGrammar("input13.txt"))
        return 1;

    computeFirst();
    computeFollow();
    for (int i = 0; i < (int)nonTerminals.size(); i++)
        printSet("FOLLOW", nonTerminals[i], follow[i]);
    return 0;
}
