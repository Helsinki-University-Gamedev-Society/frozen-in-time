#include <fstream>
#include <iterator>

#include "utils/file_access.hpp"

FileAccessor::FileAccessor(): base_path(GAME_BASE_PATH) {}

FileAccessor::FileAccessor(string path): base_path(GAME_BASE_PATH / path) {}

void FileAccessor::set_path(string path) {
    base_path = GAME_BASE_PATH / path;
}

void FileAccessor::reset_path() {
    base_path = GAME_BASE_PATH;
}

string FileAccessor::get_full_path(string relative_path) {
    return base_path / relative_path;
}

string FileAccessor::read_file(string path) {
    std::ifstream ifs(base_path / path);

    return std::string((std::istreambuf_iterator<char>(ifs)),
		       (std::istreambuf_iterator<char>()));
}

void FileAccessor::write_file(string path, string contents) {
    std::ofstream ofs(base_path / path);

    ofs << contents;
}
