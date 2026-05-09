#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream file("input4.txt");
    string line;
    int lineNum = 0;

    set<char> operators = {
        '+', '-', '*', '/', '%',
        '=', '<', '>',
        '!', '&', '|', '^', '~'};

    cout << endl;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        lineNum++;

        int count = 0;
        int i = 0;
        while (i < line.length())
        {
            if (operators.count(line[i]))
            {
                // checks for double op
                if (i + 1 < line.length() && operators.count(line[i + 1]))
                {
                    count++;
                    i += 2;
                }
                else
                {
                    count++;
                    i++;
                }
            }
            else
            {
                i++;
            }
        }

        cout << line << " -->";
        cout << " Total Operator: " << count << endl << endl;
    }

    file.close();
    return 0;
}
