#include <map>
#include <set>
#include <string>
#include <vector>

using std::map;
using std::set;
using std::string;
using std::vector;

const map<string, string> SYNONYMS = {
    {"pick up", "take"},
    {"the", ""},
    {"to", ""},
    {"with", ""},
};

const set<char> WHITESPACE{' '};

void replace_all(std::string& s, std::string const& toReplace, std::string const& replaceWith);
string prettify_command(string input);
