#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input.txt");

    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        lineCount++;
        charCount += line.length();

        bool inWord = false;
        for (int i = 0; i < line.length(); i++)
        {
            char ch = line[i];

            if (ch == ' ' || ch == '\t')
            {
                inWord = false;
            }
            else
            {
                if (!inWord)
                {
                    wordCount++;
                    inWord = true;
                }
            }
        }
    }
    file.close();

    cout << endl;
    cout << "Characters: " << charCount << endl;
    cout << "Words     : " << wordCount << endl;
    cout << "Lines     : " << lineCount << endl;

    return 0;
}