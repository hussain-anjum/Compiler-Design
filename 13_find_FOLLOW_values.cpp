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

// FIRST of a sequence of symbols (e.g. the trailer beta), used by FOLLOW rules.
// Returns "e" in the set only when the whole sequence can derive epsilon.
set<string> computeFirstOfSequence(vector<string> seq, int start)
{
    set<string> result;

    bool allDeriveEpsilon = true;
    for (int i = start; i < (int)seq.size(); i++)
    {
        set<string> firstY = computeFirst(seq[i]);

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
    ifstream file("input13.txt");
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

    map<string, set<string>> follow;

    // Rule 1: place $ in FOLLOW(S), where S is the start symbol
    string startSymbol = order[0];
    follow[startSymbol].insert("$");

    // Repeat until nothing more can be added to any FOLLOW set
    bool changed = true;
    while (changed)
    {
        changed = false;

        for (string A : order)
        {
            for (vector<string> rule : productions[A])
            {
                for (int i = 0; i < (int)rule.size(); i++)
                {
                    string B = rule[i];
                    if (!isNonTerminal(B))
                        continue;

                    // beta = symbols after B  ->  A -> alpha B beta
                    set<string> firstBeta = computeFirstOfSequence(rule, i + 1);

                    // Rule 2: everything in FIRST(beta) except e goes into FOLLOW(B)
                    for (string sym : firstBeta)
                    {
                        if (sym != "e" && follow[B].find(sym) == follow[B].end())
                        {
                            follow[B].insert(sym);
                            changed = true;
                        }
                    }

                    // Rule 3: if beta is empty (A -> alpha B) or FIRST(beta) contains e,
                    //         then everything in FOLLOW(A) is in FOLLOW(B)
                    if (firstBeta.find("e") != firstBeta.end())
                    {
                        for (string sym : follow[A])
                        {
                            if (follow[B].find(sym) == follow[B].end())
                            {
                                follow[B].insert(sym);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "\n===== FOLLOW Sets =====" << endl;
    for (string nt : order)
    {
        cout << "FOLLOW(" << nt << ") = { ";
        bool first = true;
        // iterate in reverse so $ (lowest in ASCII) prints last
        for (auto it = follow[nt].rbegin(); it != follow[nt].rend(); ++it)
        {
            if (!first)
                cout << ", ";
            cout << *it;
            first = false;
        }
        cout << " }" << endl;
    }

    return 0;
}
