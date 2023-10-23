#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

class Path {
private:
    std::string full_path;

public:
    // Constructor
    Path(std::string path)
        : full_path(path) {};

    void setPath(std::string path) {
        full_path = path;
        std::cout << "New path set with success : " << path << std::endl;
    };

    std::string vectorToStringWithDelimiter(const std::vector<std::string>& vec, const std::string& delimiter) {
        std::string result;

        for (size_t i = 0; i < vec.size(); ++i) {
            result += vec[i];
            if (i < vec.size() - 1) {
                result += delimiter;
            }
        }

        return result;
    }

    void toParent() {
        std::vector<std::string> inputVector = this->getSplit();
        if (!inputVector.empty()) {
            inputVector.pop_back();
        }
        this->full_path = vectorToStringWithDelimiter(inputVector, "/");
        std::cout << "Changed directory to parent : " << full_path << std::endl;
    }

    std::vector<std::string> getSplit() {
        std::vector<std::string> splitStrings;

        std::string temp_string = "";
        for (std::string::size_type i = 0; i < full_path.length(); i++) {
            char character = full_path[i];
            if (character == '/') {
                splitStrings.push_back(temp_string);
                temp_string = "";
            } else {
                temp_string += character;
            };
        };
        splitStrings.push_back(temp_string);

        return splitStrings;
    };

    void displayPath(){
        std::cout << "Working path : ";
        std::vector<std::string> items = this->getSplit();
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << items[i];
            if (i < items.size() - 1) {
                std::cout << "/";
            }
        }
        std::cout << std::endl;
    }

    std::string toString(){
        return full_path;
    }

    bool isFile(){
        std::filesystem::path temp_path(this->toString());
        return !(std::filesystem::is_regular_file(temp_path));
    }

    bool isDirectory(){
        std::filesystem::path temp_path(this->toString());
        return (std::filesystem::is_directory(temp_path));
    }

    void ls() {
        std::string adaptPath = "";
        if (full_path == "sdmc:") {
            std::cout << "You are in the root of the SD Card !" << std::endl;
            adaptPath = "/";
        }
        std::filesystem::path directoryPath(full_path+adaptPath);

        if ((this->isDirectory())) {
            std::cout << "Directory of " << this->full_path << ":" << std::endl;
            std::vector<std::string> directories;
            std::vector<std::string> files;
            for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
                if (std::filesystem::is_regular_file(entry)) {
                    std::string filename = entry.path().filename();
                    filename += "    ";
                    std::uintmax_t fileSize = std::filesystem::file_size(entry);
                    filename += std::to_string(fileSize);
                    filename += "b";
                    files.push_back(filename);
                } else if (std::filesystem::is_directory(entry)) {
                    std::string filename = entry.path().filename();
                    directories.push_back(filename);
                }
            }
            for (size_t i = 0; i < directories.size(); ++i) {if (i < directories.size()) {std::cout << "    "  << directories[i] << std::endl;}};
            for (size_t i = 0; i < files.size(); ++i) {if (i < files.size()) {std::cout << "    " << files[i] << std::endl;}};
            std::cout << std::endl;
        } else {
            std::cout << "The specified path is not a directory." << std::endl;
        }
    }

    void cd(std::string newFolder){
        std::string newPath = full_path + "/" + newFolder;
        if (!(std::filesystem::exists(newPath))){
            std::cout << newPath << " doesn't exists" << std::endl;
            return;
        }
        if (!(std::filesystem::is_directory(newPath))){
            std::cout << newPath << " is not a directory" << std::endl;
            return;
        }
        full_path = newPath;
        std::cout << "Changed directory : " << newPath << std::endl;
    }

};