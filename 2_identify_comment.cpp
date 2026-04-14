#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input2.txt");

    string line;
    int lineNum = 0;
    bool inMultiLine = false;

    cout << endl;
    while (getline(file, line))
    {
        lineNum++;

        int start = 0;
        while (start < line.length() && (line[start] == ' ' || line[start] == '\t'))
        {
            start++;
        }
        string trimString = line.substr(start);

        if (inMultiLine)
        {
            cout << "Multi Line Comment" << endl;
            if (trimString.find("*/") != string::npos)
            {
                inMultiLine = false; // if finds */ multi line is complete
            }
        }
        // single line comment
        else if (trimString.length() >= 2 && trimString[0] == '/' && trimString[1] == '/')
        {
            cout << "Single Line Comment" << endl;
        }

        // multi line
        else if (trimString.length() >= 2 && trimString[0] == '/' && trimString[1] == '*')
        {
            cout << "Multi Line Comment" << endl;
            if (trimString.find("*/") == string::npos)
            {
                inMultiLine = true; // if not find */, flag on
            }
        }

        // inline comment
        else if (trimString.find("//") != string::npos)
        {
            cout << "Inline Comment" << endl;
        }
        else
        {
            cout << "Not a Comment" << endl;
        }
    }
    file.close();

    return 0;
}