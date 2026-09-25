#include <bits/stdc++.h>
using namespace std;

// Group alternatives with the same first character, then find their common prefix.
void leftFactor(string head, vector<string> alternatives, string base, int& number)
{
    vector<bool> used(alternatives.size(), false);
    vector<string> result;
    vector<string> newHeads;
    vector<vector<string>> newRules;

    for (int i = 0; i < (int)alternatives.size(); i++)
    {
        if (used[i])
            continue;

        used[i] = true;
        if (alternatives[i].empty())
        {
            result.push_back("e");
            continue;
        }

        vector<string> group;
        group.push_back(alternatives[i]);

        for (int j = i + 1; j < (int)alternatives.size(); j++)
        {
            if (!used[j] && !alternatives[j].empty() &&
                alternatives[i][0] == alternatives[j][0])
            {
                group.push_back(alternatives[j]);
                used[j] = true;
            }
        }

        if (group.size() == 1)
        {
            result.push_back(group[0]);
            continue;
        }

        string common = group[0];
        for (int j = 1; j < (int)group.size(); j++)
        {
            int k = 0;
            while (k < (int)common.length() && k < (int)group[j].length() &&
                   common[k] == group[j][k])
                k++;
            common = common.substr(0, k);
        }

        // New names: S', S'', S''', ...
        number++;
        string newHead = base;
        for (int j = 0; j < number; j++)
            newHead += "'";

        vector<string> remaining;
        for (int j = 0; j < (int)group.size(); j++)
            remaining.push_back(group[j].substr(common.length()));

        result.push_back(common + newHead);
        newHeads.push_back(newHead);
        newRules.push_back(remaining);
    }

    cout << head << " -> ";
    for (int i = 0; i < (int)result.size(); i++)
    {
        if (i != 0)
            cout << " | ";
        cout << result[i];
    }
    cout << endl;

    // Factor the new rules too, if they still have common prefixes.
    for (int i = 0; i < (int)newHeads.size(); i++)
        leftFactor(newHeads[i], newRules[i], base, number);
}

int main()
{
    ifstream file("input11.txt");
    if (!file)
    {
        cout << "Error opening input11.txt!" << endl;
        return 1;
    }

    string line;
    cout << "\nLeft Factoring Result:\n";
    while (getline(file, line))
    {
        string production = "";
        for (int i = 0; i < (int)line.length(); i++)
        {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r')
                production += line[i];
        }
        if (production.empty())
            continue;

        // Input non-terminals are single uppercase letters, such as S and E.
        if (production.length() < 4 || production.substr(1, 2) != "->" ||
            production[0] < 'A' || production[0] > 'Z' ||
            production.find('\'') != string::npos)
        {
            cout << "Invalid format: " << line << endl;
            continue;
        }

        string head = production.substr(0, 1);
        string rhs = production.substr(3) + "|";
        string alternative = "";
        vector<string> alternatives;
        bool valid = true;

        for (int i = 0; i < (int)rhs.length(); i++)
        {
            if (rhs[i] != '|')
                alternative += rhs[i];
            else
            {
                if (alternative.empty())
                {
                    valid = false;
                    break;
                }
                // e alone means epsilon; e inside eS is a terminal.
                if (alternative == "e")
                    alternative = "";

                // Repeated alternatives do not need to be factored.
                bool exists = false;
                for (int j = 0; j < (int)alternatives.size(); j++)
                    if (alternatives[j] == alternative)
                        exists = true;
                if (!exists)
                    alternatives.push_back(alternative);
                alternative = "";
            }
        }

        if (!valid)
        {
            cout << "Empty alternative: use e for epsilon." << endl;
            continue;
        }

        int number = 0;
        leftFactor(head, alternatives, head, number);
    }
    file.close();
    return 0;
}
