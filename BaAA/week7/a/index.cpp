#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t; std::cin >> s >> t; s += "!";

    std::vector <unsigned int> br(s.size()); br[0] = 0;
    std::vector <unsigned int> brs(s.size()); brs[0] = 0;
    for (unsigned int i = 1; i < s.size() - 1; ++i)
    {
        unsigned int index = i - 1;
        while (index != 0 && s[i] != s[br[index]]) index = br[index] - 1;
        br[i] = br[index] + (s[i] == s[br[index]]);
        
        if (s[br[i]] != s[i + 1]) brs[i] = br[i];
        else brs[i] = (br[i] == 0) ? 0 : brs[br[i] - 1];
    }

    std::vector <unsigned int> answers;
    unsigned int matched = 0;
    for (unsigned int i = 0; i < t.size(); ++i)
    {
        while (matched != 0 && s[matched] != t[i]) matched = brs[matched - 1];

        if (s[matched] == t[i]) ++matched;
        if (matched == s.size() - 1)
        {
            matched = brs[matched - 1];
            answers.push_back(i - s.size() + 2);
        }
    }
    std::cout << answers.size() << '\n';
    for (const unsigned int& answer : answers) std::cout << answer << '\n';
}
