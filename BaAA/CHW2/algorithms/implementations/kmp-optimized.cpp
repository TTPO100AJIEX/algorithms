#include <cstddef>
#include <string>
#include <vector>

unsigned int search(const std::string& text, const std::string& pat)
{
    std::string pattern = pat;
    size_t patternSize = pattern.size(), textSize = text.size();
    pattern += '!';

    std::vector <unsigned int> patternBlocks(patternSize), patternBlocksSpecific(patternSize);
    patternBlocks[0] = patternBlocksSpecific[0] = 0;
    for (unsigned int i = 1; i < patternSize; ++i)
    {
        unsigned int prefixSize = patternBlocks[i - 1];
        while (prefixSize != 0 && pattern[i] != '?' && pattern[prefixSize] != '?' && pattern[i] != pattern[prefixSize])
            prefixSize = patternBlocks[prefixSize - 1];
        patternBlocks[i] = prefixSize + (pattern[i] == pattern[prefixSize] || pattern[i] == '?' || pattern[prefixSize] == '?');
        
        if (pattern[patternBlocks[i]] != pattern[i + 1] && pattern[patternBlocks[i]] != '?' && pattern[i + 1] != '?') patternBlocksSpecific[i] = patternBlocks[i];
        else patternBlocksSpecific[i] = (patternBlocks[i] == 0) ? 0 : patternBlocksSpecific[patternBlocks[i] - 1];
    }
    
    for (unsigned int i = 0, matched = 0; i < textSize; ++i)
    {
        while (matched != 0 && pattern[matched] != '?' && pattern[matched] != text[i]) matched = patternBlocksSpecific[matched - 1];
        if (pattern[matched] == text[i] || pattern[matched] == '?') ++matched;

        if (matched == patternSize)
        {
            matched = patternBlocksSpecific[matched - 1];
            return i - patternSize + 1;
        }
    }
    return text.size();
}