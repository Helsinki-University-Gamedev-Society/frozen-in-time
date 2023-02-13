#include "game/cparser.hpp"

#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(" ");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

void replace_all(std::string& s, std::string const& toReplace, std::string const& replaceWith) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}

string prettify_command(string input) {
    vector<string> words;

    string cur_word;
    for(char &c : input) {
	if(WHITESPACE.contains(c)) {
	    if(cur_word.empty()) {
		continue;
	    } else {
		words.push_back(cur_word);
		cur_word = string("");
	    }
	} else {
	    // std::cout << cur_word << std::endl;
	    cur_word += c;
	}
    }
    if(not cur_word.empty()) {
	words.push_back(cur_word);
    }

    std::ostringstream pretty_stream;
    std::ostream_iterator<std::string> oit(pretty_stream, " ");
    std::copy(words.begin(), words.end(), oit);

    string pretty = pretty_stream.str();

    for(auto &[synonym, target_word] : SYNONYMS) {
	replace_all(pretty, synonym, target_word);
    }

    return rtrim(pretty);
}
