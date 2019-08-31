/*
 * File source file
 * By Henock @ Comedac
 * 07/ 12/ 2016 :: 13:03
 */

 #include "HN_File.hpp"
 #include <cstring>
 #include <cstdio>
 #include <sys/stat.h>

 using namespace hnapi::path;

 // Static methods
bool hnapi::path::isFileExist(std::string &dirname)
{
    // Obtain file statistics
    struct stat fileStat;
    int i = stat(dirname.c_str(), &fileStat);

    /*
    printf("%d %d %d %d %d %d %ld [%ld] %ld %ld %d\n",
            fileStat.st_mode,
            fileStat.st_ino,
            fileStat.st_dev,
            fileStat.st_nlink,
            fileStat.st_uid,
            fileStat.st_gid,
            fileStat.st_size,
            fileStat.st_atime,
            fileStat.st_mtime,
            fileStat.st_ctime,
            i);
            */

    if(i == -1 || !S_ISREG(fileStat.st_mode))
        return false;

    // Can arrive here only with success
    return true;
}

bool hnapi::path::isFileAbsolutePath(std::string &path)
{
    // Data pointers
    const char *buffer = path.c_str();
    int b_len = strlen(buffer), li = 0;

    // Analyze if root
    if(buffer[0] == '\\' || buffer[0] == '/')
        return true;

    // If driver
    for(int i = 0; i < b_len; i++)
    {
        switch(buffer[i])
        {
            case '\\':
            case '/':
                {
                    if(li == ':'){return true;}
                }
                break;
        }
        li = buffer[i];
    }

    // Can not arrive here
    return false;
}

bool hnapi::path::deleteFileFirstDirName(std::string &path)
{
    return true;
}

bool hnapi::path::deleteFileFolderName(std::string &path)
{
    return true;
}

bool hnapi::path::deleteFileFileName(std::string &path, int id)
{
    return true;
}

std::string hnapi::path::getFileFileName(std::string &path)
{
    // Generate pointers
    const char *buffer = path.c_str();
    int b_len = strlen(buffer), i_len = b_len;
    bool breaked = false;

    // Point on separator
    for(; b_len >= 0; b_len--)
        {
        if(buffer[b_len] == '\\'
        || buffer[b_len] == '/')
            {
            breaked = true;
            break;
        }
    }

    if(b_len == 0 && !breaked)
        return buffer;

    // Build data to return
    char filename[260];
    int j = 0;
    memset(filename, 0, 260 * sizeof(char));
    for(b_len++; b_len < i_len; b_len++)
        {
        filename[j] = buffer[b_len];
        j++;
    }

    // Return filename
    return filename;
}


std::string hnapi::path::getFileFolderName(std::string &path)
{
    // Generate pointers
    const char *buffer = path.c_str();
    int b_len = strlen(buffer);
    bool breaked = false;

    // Point on separator
    for(; b_len >= 0; b_len--)
        {
        if(buffer[b_len] == '\\'
        || buffer[b_len] == '/')
            {
            breaked = true;
            break;
        }
    }

    if(b_len == 0 && !breaked)
        return buffer;

    // Build data to return
    char filename[260];
    int j = 0;
    for(; j <= b_len; j++){
        filename[j] = buffer[j];
    }filename[j] = '\0';

    // Return filename
    return filename;
}

std::string hnapi::path::getFileExtension(std::string &path)
{
    // Build data pointers
    const char *buffer = path.c_str();
    int b_len = strlen(buffer), i;
    std::string extension;

    // Place cursor
    for(i = b_len; i >= 0; i--)
        {
        if(buffer[i] == '.')
        {
            break;
        }
    }

    // Loop for getting file extension
    for(i++; i < b_len; i++)
    {
        extension+= buffer[i];
    }

    return extension;
}

bool hnapi::path::isLocalFilePath(std::string &path)
{
    // Verify if file exist
    if(hnapi::path::isFileExist(path))
        return true;

    // Get file root
    std::string root = hnapi::path::getFileRoot(path);
    if(root == "file:")
        return true;

    // Unable to find it on local
    return false;
}

std::string hnapi::path::getFileRoot(std::string &path)
{
    // Build data pointers
    const char *buffer = path.c_str();
    int b_len = strlen(buffer), i;
    std::string root;

    // Loop for getting file root
    for(i = 0; i < b_len; i++)
    {
        root+= buffer[i];
        if(buffer[i] == ':')
            break;
    }

    // Return root
    return root;
}


