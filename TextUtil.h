#pragma once  //I use this instead of #ifndef #define #endif  

#include <string>

using namespace std;

string ToLower(const string& text);
string NormalizeName(const string& name);
bool NamesMatch(const string& realName, const string& searchedName);
