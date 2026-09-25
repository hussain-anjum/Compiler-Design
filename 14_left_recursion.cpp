#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input14.txt");

    if (!file)
    {
        cout << "Error opening input14.txt!" << endl;
        return 1;
    }

    string line;
    cout << "\nLeft Recursion Removal Result:\n";

    // Read one production from each line.
    while (getline(file, line))
    {
        string production = "";

        // Remove spaces and tabs.
        for (int i = 0; i < (int)line.length(); i++)
        {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r')
                production += line[i];
        }

        if (production.empty())
            continue;

        // Input format: A->Aabb|BC (single uppercase non-terminals).
        if (production.length() < 4 || production.substr(1, 2) != "->" ||
            production[0] < 'A' || production[0] > 'Z' ||
            production.find('\'') != string::npos)
        {
            cout << "Invalid format: " << line << endl;
            continue;
        }

        string head = production.substr(0, 1);
        string rhs = production.substr(3);
        vector<string> recursive;
        vector<string> nonRecursive;
        string alternative = "";
        bool valid = true;

        // Extra | lets us process the last alternative in the same way.
        rhs += '|';
        for (int i = 0; i < (int)rhs.length(); i++)
        {
            if (rhs[i] != '|')
            {
                alternative += rhs[i];
            }
            else
            {
                if (alternative.empty())
                {
                    valid = false;
                    break;
                }

                if (alternative.substr(0, 1) == head)
                {
                    // Aabb becomes abb. Ignore A -> A itself.
                    if (alternative.length() > 1)
                        recursive.push_back(alternative.substr(1));
                }
                else
                {
                    nonRecursive.push_back(alternative);
                }
                alternative = "";
            }
        }

        if (!valid)
        {
            cout << "Empty alternative: use e for epsilon." << endl;
            continue;
        }

        if (nonRecursive.empty())
        {
            cout << head << " has no non-recursive alternative; it cannot derive a terminal string." << endl;
            continue;
        }

        string newHead = head + "'";
        cout << head << " -> ";

        for (int i = 0; i < (int)nonRecursive.size(); i++)
        {
            if (i != 0)
                cout << " | ";

            if (recursive.empty())
                cout << nonRecursive[i];
            else
            {
                // For beta = e, print only the new non-terminal.
                if (nonRecursive[i] != "e")
                    cout << nonRecursive[i];
                cout << newHead;
            }
        }
        cout << endl;

        if (!recursive.empty())
        {
            cout << newHead << " -> ";
            for (int i = 0; i < (int)recursive.size(); i++)
            {
                if (i != 0)
                    cout << " | ";
                cout << recursive[i] << newHead;
            }
            cout << " | e" << endl;
        }
    }

    file.close();
    return 0;
}
