#include <map>
#include <set>
#include <string>

using std::map;
using std::set;
using std::string;

const map<string, string> SYNONYMS = {
    {"pick up", "take"},
    {"investigate", "inspect"},
    {"look at", "inspect"},
    {"look around", "look"},
    {"scout", "look"},
    {"the", ""},
    {"to", ""},
    {"with", ""},
};

const set<char> WHITESPACE{' '};

void replace_all(std::string& s, std::string const& toReplace, std::string const& replaceWith);
string prettify_command(string input);
