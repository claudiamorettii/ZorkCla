#include <algorithm>
#include <cctype>

#include "TextUtil.h"

string NormalizeName(const string& name)
{
    string normalizedName = name;

    transform(normalizedName.begin(), normalizedName.end(), normalizedName.begin(), [](unsigned char character)
        {
            return static_cast<char>(tolower(character));
        });

    normalizedName.erase(remove_if(normalizedName.begin(), normalizedName.end(), [](unsigned char character)
        {
            return isspace(character);
        }), normalizedName.end());

    return normalizedName;
}

bool NamesMatch(const string& realName, const string& searchedName)
{
    string normalizedRealName = NormalizeName(realName);
    string normalizedSearchedName = NormalizeName(searchedName);

    if (normalizedSearchedName.empty())
    {
        return false;
    }

    return normalizedRealName == normalizedSearchedName ||
        normalizedRealName.find(normalizedSearchedName) != string::npos;
}

string ToLower(const string& text)
{
    string lowerText = text;

    transform(lowerText.begin(), lowerText.end(), lowerText.begin(), [](unsigned char character)
        {
            return static_cast<char>(tolower(character));
        });

    return lowerText;
}