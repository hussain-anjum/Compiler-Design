#include <bits/stdc++.h>
using namespace std;

vector<string> heads;
vector<vector<string>> rules;
vector<string> target;
vector<string> steps;
int attempts = 0;
bool limitReached = false;

vector<string> split(string text)
{
    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word)
        words.push_back(word);
    return words;
}

bool isNonTerminal(string symbol)
{
    for (int i = 0; i < (int)heads.size(); i++)
        if (heads[i] == symbol)
            return true;
    return false;
}

string toText(vector<string> symbols)
{
    if (symbols.empty())
        return "e";

    string text = symbols[0];
    for (int i = 1; i < (int)symbols.size(); i++)
        text += " " + symbols[i];
    return text;
}

bool derive(vector<string> current, int depth)
{
    if (current == target)
        return true;

    // Find the first non-terminal from the left.
    int position = -1;
    for (int i = 0; i < (int)current.size(); i++)
    {
        if (isNonTerminal(current[i]))
        {
            position = i;
            break;
        }
        // Terminals before the first non-terminal cannot change.
        if (i >= (int)target.size() || current[i] != target[i])
            return false;
    }
    if (position == -1)
        return false;

    int terminalCount = 0;
    for (int i = 0; i < (int)current.size(); i++)
        if (!isNonTerminal(current[i]))
            terminalCount++;
    if (terminalCount > (int)target.size())
        return false;

    // Prevent endless searching in recursive grammars.
    if (depth >= 100 || attempts >= 10000)
    {
        limitReached = true;
        return false;
    }
    attempts++;

    for (int i = 0; i < (int)rules.size(); i++)
    {
        if (heads[i] != current[position])
            continue;

        vector<string> next;
        for (int j = 0; j < position; j++)
            next.push_back(current[j]);
        for (int j = 0; j < (int)rules[i].size(); j++)
            next.push_back(rules[i][j]);
        for (int j = position + 1; j < (int)current.size(); j++)
            next.push_back(current[j]);

        steps.push_back(toText(next));
        if (derive(next, depth + 1))
            return true;
        steps.pop_back(); // This choice failed; try the next alternative.
    }
    return false;
}

int main()
{
    ifstream file("input15.txt");
    if (!file)
    {
        cout << "Error opening input15.txt!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        if (split(line).empty())
            continue;
        size_t arrow = line.find("->");
        if (arrow == string::npos)
        {
            cout << "Invalid production: " << line << endl;
            return 1;
        }

        vector<string> head = split(line.substr(0, arrow));
        if (head.size() != 1 || head[0] == "e")
        {
            cout << "Use one non-terminal on the left of ->." << endl;
            return 1;
        }

        string rhs = line.substr(arrow + 2) + "|";
        string alternative = "";
        for (int i = 0; i < (int)rhs.length(); i++)
        {
            if (rhs[i] != '|')
                alternative += rhs[i];
            else
            {
                vector<string> rule = split(alternative);
                if (rule.empty())
                {
                    cout << "Empty alternative: use e for epsilon." << endl;
                    return 1;
                }
                for (int j = 0; j < (int)rule.size(); j++)
                {
                    if (rule[j] == "e" && rule.size() > 1)
                    {
                        cout << "Use e alone for epsilon." << endl;
                        return 1;
                    }
                }
                if (rule[0] == "e")
                    rule.clear();
                heads.push_back(head[0]);
                rules.push_back(rule);
                alternative = "";
            }
        }
    }
    file.close();

    if (heads.empty())
    {
        cout << "No productions found." << endl;
        return 1;
    }

    cout << "Enter target (space-separated symbols, e for empty): ";
    if (!getline(cin, line))
        return 1;
    target = split(line);
    if (target.size() == 1 && target[0] == "e")
        target.clear();
    for (int i = 0; i < (int)target.size(); i++)
    {
        if (isNonTerminal(target[i]) || target[i] == "e")
        {
            cout << "Target must contain terminals only." << endl;
            return 1;
        }
    }

    vector<string> start;
    start.push_back(heads[0]);
    steps.push_back(heads[0]);

    if (derive(start, 0))
    {
        cout << "\nLeftmost Derivation:\n";
        cout << steps[0] << endl;
        for (int i = 1; i < (int)steps.size(); i++)
            cout << "=> " << steps[i] << endl;
    }
    else if (limitReached)
        cout << "Search limit reached; result is inconclusive." << endl;
    else
        cout << "No leftmost derivation exists for this target." << endl;

    return 0;
}
