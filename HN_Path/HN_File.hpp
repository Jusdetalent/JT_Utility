#ifndef HN_FILE_HPP_INCLUDED
#define HN_FILE_HPP_INCLUDED

    #include <string>

namespace hnapi
{
    namespace path
    {
        // Static methods
        bool isFileExist(std::string &dirname);
        bool isFileAbsolutePath(std::string &path);
        bool deleteFileFirstDirName(std::string &path);
        bool deleteFileFolderName(std::string &path);
        bool deleteFileFileName(std::string &path, int id);
        std::string getFileFileName(std::string &path);
        std::string getFileFolderName(std::string &path);
        std::string getFileExtension(std::string &path);
        bool isLocalFilePath(std::string &path);
        std::string getFileRoot(std::string &path);
    }
}

#endif // HN_FILE_HPP_INCLUDED
