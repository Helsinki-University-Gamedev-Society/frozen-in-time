#ifndef _FILE_ACCESS_
#define _FILE_ACCESS_

#include <filesystem>
#include <string>

#include <SDL_filesystem.h>

using std::string;

// This is relative to the game executable
const std::filesystem::path GAME_BASE_PATH = SDL_GetBasePath();

class FileAccessor {
public:
    FileAccessor();
    FileAccessor(string path);

    void set_path(string path);
    void reset_path();

    string get_full_path(string relative_path);
    string read_file(string path);
private:
    std::filesystem::path base_path;
};

#endif // _FILE_ACCESS_
