/*
71. Simplify Path

Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a double period '..' refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated as a single slash '/'. For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period '.' or double period '..')
Return the simplified canonical path.



Example 1:

Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.
Example 2:

Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
Example 3:

Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

link: https://leetcode.com/problems/simplify-path/

Date: 2023-08-27
*/

#include <iostream>
#include <vector>

std::string simplifyPath(std::string path)
{

    std::vector<std::string> listOfDir;
    std::string resultString, directories;

    resultString.push_back('/' );

    for ( int i = 0; i < path.length(); ++i )
    {
        if (path[i] == '/')
        {
            continue;
        }
        else
        {
            directories.push_back(path[i]);
        }

        if (directories.compare("..") == 0)
        {
            if (!listOfDir.empty())
            {
                listOfDir.pop_back();
            }
        }
        else if (directories.compare(".") == 0)
        {
            listOfDir.clear();
            continue;
        }
        else if (directories.length() != 0)
        {
            listOfDir.push_back(directories);
        }
    }

    std::vector<std::string> reversePath;
    while (!listOfDir.empty()) {
        reversePath.push_back(listOfDir.back());
        listOfDir.erase(listOfDir.end() - 1);
    }

    while (!reversePath.empty()) {
        std::string temp = reversePath[reversePath.size() - 1];

        if (reversePath.size() != 1)
            resultString.append(temp + "/");
        else
            resultString.append(temp);

        reversePath.erase(reversePath.end() - 1);
    }

    return resultString;
}

int main()
{
    std::string str("/home//foo/"); //expected output: "/home/foo"
    std::string res = simplifyPath(str);
    std::cout << "/home//foo/ simplified path is: " << res << std::endl;

    std::string str2("/../"); //expected output: "/"
    std::string res2 = simplifyPath(str2);
    std::cout << "/../ simplified path is: " << res2 << std::endl;

    std::string str3("/../../../home");  //expected output: "/home"
    std::string res3 = simplifyPath(str3);
    std::cout << "/../../../home simplified path is: " << res3 << std::endl;

    std::string str4("/home//foo//bar//////dir"); //expected output: "/home/foo/bar/dir"
    std::string res4 = simplifyPath(str4);
    std::cout << "/home//foo//bar//////dir simplified path is: " << res4 << std::endl;

    return 0;
}