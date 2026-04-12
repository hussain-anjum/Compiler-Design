#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input2.txt");

    string line;
    int lineNum = 0;

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

        // cout << "Line " << lineNum << ": " << line << endl;

        // single line
        if (trimString.length() >= 2 && trimString[0] == '/' && trimString[1] == '/')
        {
            cout << "Single Line Comment" << endl;
        }
        // multi line
        else if (trimString.length() >= 4 && trimString[0] == '/' && trimString[1] == '*' && trimString[trimString.length() - 2] == '*' && trimString[trimString.length() - 1] == '/')
        {
            cout << "Multi Line Comment" << endl;
        }
        else
        {
            cout << "Not a Comment" << endl;
        }
    }
    file.close();

    return 0;
}