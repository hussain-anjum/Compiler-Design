#include <bits/stdc++.h>
using namespace std;

// a
bool matchA(string s)
{
    return s == "a";
}

// a*b+
bool matchAstarBplus(string s)
{
    if (s.empty())
        return false;

    int i = 0;

    while (i < s.length() && s[i] == 'a')
        i++;

    if (i == s.length())
        return false;

    while (i < s.length() && s[i] == 'b')
        i++;

    return i == s.length();
}

// abb
bool matchAbb(string s)
{
    return s == "abb";
}

int main()
{
    ifstream file("input7.txt");
    string s;

    cout << endl;
    while (getline(file, s))
    {
        if (s.empty())
            continue;

        cout << s << " --> ";

        if (matchA(s))
            cout << "Pattern Matched: a" << endl;
        else if (matchAbb(s))
            cout << "Pattern Matched: abb" << endl;
        else if (matchAstarBplus(s))
            cout << "Pattern Matched: a*b+" << endl;
        else
            cout << "No Pattern Matched" << endl;
    }

    file.close();
    return 0;
}
