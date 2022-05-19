#pragma once 

#include <string_view>
#include <optional>
#include <string>
#include <cstdlib>

std::string_view
DeleteWhiteSpace(std::string_view line) 
{
    while(!line.empty() && isspace(line[0])) {
        line.remove_prefix(1);
    }
    while(!line.empty() && isspace(line[line.size()- 1])) {
        line.remove_suffix(1);
    }
    return line;
}

std::pair<std::string_view, std::optional<std::string_view>>
SplitStrOpt(std::string_view line, std::string_view delimiter = " ") 
{
    auto pos = line.find(delimiter);
    if(pos == line.npos) {
        return {DeleteWhiteSpace(line), std::nullopt};
    }
    return {DeleteWhiteSpace(line.substr(0, pos)), 
            DeleteWhiteSpace(line.substr(pos + delimiter.length()))};
}

std::pair<std::string_view, std::string_view>
SplieStrStr(std::string_view line, std::string_view delimiter = " ")
{
    auto [head, tail] = SplitStrOpt(line, delimiter);
    return {head, tail.value_or("")};
}

double
ConvertStrToDbl(std::string_view line) 
{
    char* end;
    return std::strtod(line.data(), &end);
}