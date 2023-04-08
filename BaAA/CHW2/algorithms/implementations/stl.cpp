#include <string_view>
#include <regex>
#include <set>

#include <iostream>
std::set<unsigned int> search(std::string_view text, std::string_view pattern)
{
    std::set<unsigned int> answer;
    text = text.substr(1);
    pattern = pattern.substr(1);

    std::regex exp("(eco)");
    std::smatch res;
    std::string str = "first second third forth second";

    std::string::const_iterator searchStart( str.cbegin() );
    while ( std::regex_search( searchStart, str.cend(), res, exp ) )
    {
        std::cout << ( searchStart == str.cbegin() ? "" : " " ) << res[0];  
        searchStart = res.suffix().first;
        std::cout << std::distance(searchStart, str.cbegin()) << std::endl;
    }
    std::cout << std::endl;
    return answer;
    /*std::set<unsigned int> answer;
    std::string_view::size_type index = text.find(pattern, 0);
    while (index != std::string_view::npos)
    {
        answer.insert(index);
        index = text.find(pattern, index + 1);
    }
    return answer;*/
}