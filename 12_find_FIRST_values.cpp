#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> productions;
vector<string> order;

bool isNonTerminal(string s)
{
    return !s.empty() && s[0] >= 'A' && s[0] <= 'Z';
}

set<string> computeFirst(string X)
{
    set<string> result;

    if (!isNonTerminal(X))
    {
        result.insert(X);
        return result;
    }

    for (vector<string> rule : productions[X])
    {
        if (rule.size() == 1 && rule[0] == "e")
        {
            result.insert("e");
            continue;
        }

        bool allDeriveEpsilon = true;
        for (string Y : rule)
        {
            set<string> firstY = computeFirst(Y);

            for (string sym : firstY)
                if (sym != "e")
                    result.insert(sym);

            if (firstY.find("e") == firstY.end())
            {
                allDeriveEpsilon = false;
                break;
            }
        }

        if (allDeriveEpsilon)
            result.insert("e");
    }

    return result;
}
vector<string> tokenize(string s)
{
    vector<string> tokens;
    stringstream ss(s);
    string word;
    while (ss >> word)
        tokens.push_back(word);
    return tokens;
}

int main()
{
    ifstream file("input12.txt");
    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        // find arrow
        size_t pos = line.find("->");
        if (pos == string::npos)
            continue;

        string lhs = line.substr(0, pos);
        string rhs = line.substr(pos + 2);

        // head = first token of lhs
        vector<string> headTokens = tokenize(lhs);
        if (headTokens.empty())
            continue;
        string head = headTokens[0];

        // split rhs by |
        vector<string> alts;
        string cur = "";
        for (int i = 0; i < rhs.length(); i++)
        {
            if (rhs[i] == '|')
            {
                alts.push_back(cur);
                cur = "";
            }
            else
                cur += rhs[i];
        }
        alts.push_back(cur);

        for (string a : alts)
        {
            vector<string> symbols = tokenize(a);
            if (!symbols.empty())
                productions[head].push_back(symbols);
        }

        if (find(order.begin(), order.end(), head) == order.end())
            order.push_back(head);
    }
    file.close();

    // cout << "\n===== FIRST Sets =====" << endl;
    for (string nt : order)
    {
        set<string> f = computeFirst(nt);

        cout << "FIRST(" << nt << ") = { ";
        bool first = true;
        for (string sym : f)
        {
            if (!first)
                cout << ", ";
            cout << sym;
            first = false;
        }
        cout << " }" << endl;
    }

    return 0;
}