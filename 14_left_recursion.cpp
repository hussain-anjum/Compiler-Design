#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of alternatives: ";
    cin >> n;
    cin.ignore();

    string head;
    cout << "Enter production head: ";
    getline(cin, head);

    vector<string> recursive;
    vector<string> nonRecursive;

    cout << "Enter " << n << " alternatives:" << endl;
    for (int i = 0; i < n; i++)
    {
        string alt;
        cout << "Alternative " << i + 1 << ": ";
        getline(cin, alt);

        if (alt.substr(0, head.length()) == head)
        {
            string alpha = alt.substr(head.length());
            recursive.push_back(alpha);
        }
        else
        {
            // β
            nonRecursive.push_back(alt);
        }
    }

    cout << "\nLeft Recursion Removal Result: " << endl;

    if (recursive.empty())
    {
        cout << "No left recursion found." << endl;
        cout << head << " --> ";
        for (int i = 0; i < nonRecursive.size(); i++)
        {
            if (i != 0)
                cout << " | ";
            cout << nonRecursive[i];
        }
        cout << endl;
        return 0;
    }

    string newHead = head + "'";

    cout << head << " --> ";
    for (int i = 0; i < nonRecursive.size(); i++)
    {
        if (i != 0)
            cout << " | ";
        cout << nonRecursive[i] << newHead;
    }
    cout << endl;

    cout << newHead << " --> ";
    for (int i = 0; i < recursive.size(); i++)
    {
        if (i != 0)
            cout << " | ";
        cout << recursive[i] << newHead;
    }
    cout << " | e" << endl;

    return 0;
}