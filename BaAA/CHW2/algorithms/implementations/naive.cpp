#include <string>

unsigned int search(const std::string& text, const std::string& pattern)
{
    for (unsigned int i = 0; i < text.size() - pattern.size(); ++i)
    {
        bool matches = true;
        for (unsigned int j = 0; j < pattern.size(); ++j)
        {
            if (pattern[j] != '?' && pattern[j] != text[i + j])
            {
                matches = false;
                break;
            }
        }
        if (matches) return i;
    }
    return text.size();
}