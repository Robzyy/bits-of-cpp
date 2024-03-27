// Compile with -std=c++17 (std::filestream) 

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <vector>

#define SYMLINK_NAME "LedFx"

struct FolderVersionPair {
    std::filesystem::directory_entry folder;
    std::string version;
};

std::string getVersionFromName(const std::filesystem::directory_entry dirEntry)
{
    // Example: "D:\\Program Files\\LedFx_core\\LedFx_core--v2.0.89"
    // 1. Convert std::filesystem::directory_entry to std::filesystem::path
    // 2. Get only the filename from full path: "LedFx_core--v2.0.89"
    // 3. Convert to std::string
    std::string version = dirEntry.path().filename().u8string();

    // Get last '-' character and keep everything after it: "v2.0.89"
    version = version.substr(version.find_last_of('-') + 1);

    // Check if there is a 'v' and remove it : "2.0.89"
    if (version[0] == 'v') {
        version = version.substr(1, version.length() - 1);
    }

    return version;
}

std::vector<FolderVersionPair> getFolderVersionPairs()
{
    namespace fs = std::filesystem;

    const auto CurrentPath = fs::current_path();

    std::vector<FolderVersionPair> pairs {};

    for (auto const& dirEntry : fs::directory_iterator(CurrentPath)) {
        // Consider only directories that are not symlinks
        if (fs::is_directory(dirEntry) && !fs::is_symlink(dirEntry)) {
            pairs.push_back({ dirEntry, getVersionFromName(dirEntry) });
        }
    }

    return pairs;
}

void createSymlink(std::filesystem::directory_entry latest)
{
    namespace fs = std::filesystem;

    fs::path x = latest.path();
    fs::path exec = x /= "LedFx.exe";

    if (fs::exists(exec)) {
        std::cout << "Deleting old symlink.\n";
        fs::remove(SYMLINK_NAME);
        std::cout << "Creating new symlink to " << exec << '\n';
        fs::create_symlink(exec, SYMLINK_NAME);
    }
}

int main()
{
    std::cout << "This app will create a symlink that will redirect to the highest LedFX version available.\n\n";
    auto pairs = getFolderVersionPairs();

    std::sort(
        pairs.begin(), pairs.end(), [](FolderVersionPair a, FolderVersionPair b) {
            return (a.version > b.version);
        });

    std::cout << "Detected versions:\n";
    for (const auto& pair : pairs) {
        std::cout << "- " << pair.version << '\n';
    }

    std::cout << "\e[1;31m\n"
              << "--------------------------------------------------------------------------------\n"
              << "Admin rights are needed to create symlinks. Make sure you run this app as admin!\n"
              << "--------------------------------------------------------------------------------\n"
              << "\e[0mContinue? [y/N]: ";
    char answer = std::cin.get();
    switch (answer) {
    case 'n':
    case 'N':
    case '\n':
        return 0;

    case 'y':
    case 'Y':
        std::cout << '\n';
        createSymlink(pairs[0].folder);
        break;

    default:
        std::cout << "Unrecognized input\n";
        return -1;
    }
}
