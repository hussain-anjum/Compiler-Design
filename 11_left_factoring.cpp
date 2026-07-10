#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cin.ignore();

    string head;
    cout << "Enter production head: ";
    getline(cin, head);

    vector<string> alternatives;

    cout << "Enter " << n << " alternatives:" << endl;
    for (int i = 0; i < n; i++)
    {
        string alt;
        cout << "Alternative " << i + 1 << ": ";
        getline(cin, alt);
        alternatives.push_back(alt);
    }

    string common = alternatives[0];

    for (int i = 1; i < alternatives.size(); i++)
    {
        string temp = "";
        int minLen = min(common.length(), alternatives[i].length());

        for (int j = 0; j < minLen; j++)
        {
            if (common[j] == alternatives[i][j])
                temp += common[j];
            else
                break;
        }
        common = temp;
    }

    cout << "\nLeft Factoring Result:" << endl << endl;

    if (common.empty())
    {
        cout << "No common prefix found. Left factoring not needed." << endl;
        cout << head << " --> ";
        for (int i = 0; i < alternatives.size(); i++)
        {
            if (i != 0)
                cout << " | ";
            cout << alternatives[i];
        }
        cout << endl;
        return 0;
    }

    // new production head A'
    string newHead = head + "'";

    // print A
    cout << head << " --> " << common << newHead << endl;

    // print A'
    cout << newHead << " --> ";
    for (int i = 0; i < alternatives.size(); i++)
    {
        if (i != 0)
            cout << " | ";

        string remaining = alternatives[i].substr(common.length());

        if (remaining.empty())
            cout << "e"; // epsilon
        else
            cout << remaining;
    }
    cout << endl;

    return 0;
}
