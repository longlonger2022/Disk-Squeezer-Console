#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <direct.h>


//函数声明
void showHelp();
void showVersion();
void unknownOption(const std::string& option);
void wt(std::string disk);
void cmd(std::string disk);
LPCWSTR CstrToLPCWSTR(const char* str);
std::string IntToString(int num);


//主函数
int main(int argc, char* argv[]) {
    //定义变量
    std::string disk;
    //判断参数个数
    //如果参数个数小于等于1，则输出帮助信息
    if (argc > 1) {
        //设置参数
        std::string option = argv[1];
        //判断参数
        //如果参数为-h或-help或/h或/help或/h或/help，则输出帮助信息
        if (option == "-help" || option == "-h" || option == "/?" || option == "-?" || option == "/help" || option == "/h") {
            showHelp();
        }
        //如果参数为-v或-version或/v或/version或/v或/version，则输出版本信息
        else if (option == "-version" || option == "-v" || option == "/version" || option == "/v" || option == "-ver" || option == "/ver") {
            showVersion();
        }
        //如果参数为-d或-disk或/d或/disk，则准备榨干
        else if (option == "-disk" || option == "-d" || option == "/disk" || option == "/d") {
            //判断参数个数
            //如果参数个数小于等于2，则输出帮助信息
            if (argc > 2) {
                //定义变量
                std::string mode = argv[2];
                //判断参数
                //如果参数为-cmd或-c或/cmd或/c，则准备命令模式
                if (mode == "-command" || mode == "-cmd" || mode == "-c" || mode == "/command" || mode == "/cmd" || mode == "/c") {
                    bool isCmdMode = true;
                    //判断参数个数
                    //如果参数个数小于等于3，则输出帮助信息
                    if (argc > 3) {
                        //定义变量
                        std::string disk = argv[3];
                        //判断参数长度
                        //如果参数长度大于等于1且小于等于3，则判断参数是否为有效盘符
                        if (disk.size() >= 1 && disk.size() <= 3) {
                            //判断参数是否为有效盘符
                            //判断参数是否为字母
                            if (disk >= "A" && disk <= "Z" || disk >= "a" && disk <= "z") {
                                //判断参数长度
                                //如果参数长度为1，则添加冒号
                                if (disk.size() == 1) {
                                    disk = disk + ":";
                                    cmd(disk);
                                }
                                //如果参数长度为2，则判断第二个字符是否为冒号
                                else if (disk.size() == 2) {
                                    if (disk[1] == ':') {
                                        cmd(disk);
                                    }
                                    //如果第二个字符不是冒号，则输出帮助信息
                                    else {
                                        std::cout << "Please enter a valid drive letter.\n";
                                        std::cout << "请输入有效盘符。\n";
                                    }
                                }
                                //如果参数长度为3，则判断第二个字符是否为冒号，第三个字符是否为反斜杠
                                else if (disk.size() == 3) {
                                    if (disk[1] == ':' && disk[2] == '\\') {
                                        disk.erase(2, 1);
                                        cmd(disk);
                                    }
                                    //如果第二个字符不是冒号或第三个字符不是反斜杠，则输出帮助信息
                                    else {
                                        std::cout << "Please enter a valid drive letter.\n";
                                        std::cout << "请输入有效盘符。\n";
                                    }
                                }
                            }
                            //如果参数不是字母，则输出帮助信息
                            else {
                                std::cout << "Please enter a valid drive letter.\n";
                                std::cout << "请输入有效盘符。\n";
                            }
                        }
                        //如果参数长度小于1或大于3，则输出帮助信息
                        else {
                            std::cout << "Please enter a valid drive letter.\n";
                            std::cout << "请输入有效盘符。\n";
                        }
                    }
                    //如果参数个数小于等于2，则输出帮助信息
                    else {
                        std::cout << "Please enter a valid drive letter.\n";
                        std::cout << "请输入有效盘符。\n";
                    }
                }
                //如果参数为-write或-wt或-w或/write或/wt或/w，则准备写入模式
                else if (mode == "-write" || mode == "-wt" || mode == "-w" || mode == "/write" || mode == "/wt" || mode == "/w") {
                    bool isCmdMode = false;
                    //判断参数个数
                    //如果参数个数大于等于3，则判断参数是否为有效盘符
                    if (argc > 3) {
                        //定义变量
                        std::string disk = argv[3];
                        //判断参数长度
                        //如果参数长度大于等于1且小于等于3，则判断参数是否为有效盘符
                        if (disk.size() >= 1 && disk.size() <= 3) {
                            //如果参数是字母，则判断参数长度
                            if (disk >= "A" && disk <= "Z" || disk >= "a" && disk <= "z") {
                                //如果参数长度为1，则加上冒号
                                if (disk.size() == 1) {
                                    disk = disk + ":";
                                    wt(disk);
                                }
                                //如果参数长度为2，则判断第二个字符是否为冒号
                                else if (disk.size() == 2) {
                                    if (disk[1] == ':') {
                                        wt(disk);
                                    }
                                    //如果第二个字符不是冒号，则输出帮助信息
                                    else {
                                        std::cout << "Please enter a valid drive letter.\n";
                                        std::cout << "请输入有效盘符。\n";
                                    }
                                }
                                //如果参数长度为3，则判断第二个字符是否为冒号，第三个字符是否为反斜杠
                                else if (disk.size() == 3) {
                                    if (disk[1] == ':' && disk[2] == '\\') {
                                        disk.erase(2, 1);
                                        wt(disk);
                                    }
                                    //如果第二个字符不是冒号，则输出帮助信息
                                    else {
                                        std::cout << "Please enter a valid drive letter.\n";
                                        std::cout << "请输入有效盘符。\n";
                                    }
                                }
                            }
                            //如果参数不是字母，则输出帮助信息
                            else {
                                std::cout << "Please enter a valid drive letter.\n";
                                std::cout << "请输入有效盘符。\n";
                            }
                        }
                        //如果参数长度小于1或大于3，则输出帮助信息
                        else {
                            std::cout << "Please enter a valid drive letter.\n";
                            std::cout << "请输入有效盘符。\n";
                        }
                    }
                }
                //如果是其他未知命令，则显示未知命令
                else {
                    unknownOption(mode);
                }
            }
            else {
                std::cout << "Please enter a valid drive letter and mode.\n";
                std::cout << "请输入有效盘符和模式。\n";
            }
        }
        //如果输入未知命令
        else {
            unknownOption(option);
        }
    }
    //如果没有输入任何命令
    else {
        std::cout << "No options provided.\n";
        std::cout << "Use -help or -h for usage information.\n";
        std::cout << "没有输入任何命令。\n";
        std::cout << "输入 -help 或 -h 获取更多信息和帮助。\n";
    }

    return 0;
}


// 处理未知选项
void unknownOption(const std::string& option) {
    std::cout << "Unknown option: " << option << "\n";
    std::cout << "Use -help or -h for usage information.\n";
    std::cout << "未知的命令：" << option << "\n";
    std::cout << "输入 -help 或 -h 获取更多信息和帮助。\n";
}

// 显示帮助信息
void showHelp() {
    std::cout << "Usage: squeeze [options][mode]\n";
    std::cout << "Options:\n";
    std::cout << "    -help, -h             Show this help message\n";
    std::cout << "    -version, -ver, -v    Show version information\n";
    std::cout << "    -disk, -d             Squeeze options [mode]\n";
    std::cout << "        -w, -wt, -write             Write mode [drive letter]\n";
    std::cout << "        -c, -cmd, -command          Command mode [drive letter]\n";
    std::cout << "用法：squeeze [选项][模式]\n";
    std::cout << "选项:\n";
    std::cout << "    -help, -h, -?         显示帮助\n";
    std::cout << "    -version, -ver, -v    显示版本信息\n";
    std::cout << "    -disk, -d             榨干选项[模式]\n";
    std::cout << "        -w, -wt, -write             写入模式[盘符]\n";
    std::cout << "        -c, -cmd, -command          命令模式[盘符]\n";
}

// 显示版本信息
void showVersion() {
    std::cout << "Disk-Squeezer-Console version 1.0.0\n";
}

void wt(std::string disk) {
    double space = 0.0;
    double percentage;
    percentage = 0.0;
    std::string filepath = disk;
    filepath.append("\\squeezedisk");
    BOOL result = CreateDirectory(CstrToLPCWSTR(filepath.c_str()), NULL);
    if (result == 0) {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "The directory already exists.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "目录已存在。\n";
            std::cerr << "错误代码 Error code: ERROR_ALREADY_EXISTS\033[0m\n";
        }
        else if (error == ERROR_ACCESS_DENIED) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Access denied. Please run the program as an administrator.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "拒绝访问。请以管理员身份运行程序。\n";
            std::cerr << "错误代码 Error code: ERROR_ACCESS_DENIED\033[0m\n";
        }
        else if (error == ERROR_BAD_PATHNAME) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Invalid path.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "无效的路径。\n";
            std::cerr << "错误代码 Error code: ERROR_BAD_PATHNAME\033[0m\n";
        }
        else if (error == ERROR_INVALID_PARAMETER) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Invalid parameter.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "无效的参数。\n";
            std::cerr << "错误代码 Error code: ERROR_INVALID_PARAMETER\033[0m\n";
        }
        else if (error == ERROR_PATH_NOT_FOUND) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Path not found.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "路径未找到。\n";
            std::cerr << "错误代码 Error code: ERROR_PATH_NOT_FOUND\033[0m\n";
        }
        else if (error == ERROR_DIRECTORY) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Directory name invalid.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "目录名称无效。\n";
            std::cerr << "错误代码 Error code: ERROR_DIRECTORY\033[0m\n";
        }
        else if (error == ERROR_INVALID_DRIVE) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Invalid drive.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "无效的驱动器。\n";
            std::cerr << "错误代码 Error code: ERROR_INVALID_DRIVE\033[0m\n";
        }
        else if (error == ERROR_NOT_SAME_DEVICE) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "The specified path is on a different device.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "指定的路径位于不同的设备上。\n";
            std::cerr << "错误代码 Error code: ERROR_NOT_SAME_DEVICE\033[0m\n";
        }
        else if (error == ERROR_SHARING_VIOLATION) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "The file is already open by another process.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "文件已被其他进程打开。\n";
            std::cerr << "错误代码 Error code: ERROR_SHARING_VIOLATION\033[0m\n";
        }
        else if (error == ERROR_TOO_MANY_OPEN_FILES) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Too many open files.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "打开的文件过多。\n";
            std::cerr << "错误代码 Error code: ERROR_TOO_MANY_OPEN_FILES\033[0m\n";
        }
        else if (error == ERROR_WRITE_PROTECT) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "The disk is write-protected.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "磁盘被写保护。\n";
            std::cerr << "错误代码 Error code: ERROR_WRITE_PROTECT\033[0m\n";
        }
        else if (error == ERROR_DISK_FULL) {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "The disk is full.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "磁盘已满。\n";
            std::cerr << "错误代码 Error code: ERROR_DISK_FULL\033[0m\n";
        }
        else {
            std::cerr << "\033[1;31mFailed to create the directory.\n";
            std::cerr << "Unknown error.\n";
            std::cerr << "创建目录失败。\n";
            std::cerr << "未知错误。\033[0m\n";
        }
    }
    else {
        std::string dirpath = filepath;
        filepath.append("\\squeezedisk.dll");
        DWORD64 qwFreeBytesToCaller = 0;
        DWORD64 qwTotalBytes = 0;
        DWORD64 qwFreeBytes = 0;
        BOOL bResult = GetDiskFreeSpaceExA(disk.c_str(), (PULARGE_INTEGER)&qwFreeBytesToCaller, (PULARGE_INTEGER)&qwTotalBytes, (PULARGE_INTEGER)&qwFreeBytes);
        std::ofstream file(filepath.c_str());
        if (file.is_open()) {
            while (true) {
                percentage = (space * 1.00) / (qwFreeBytes * 1.00) * 100.00;
                std::cout << "\r正在榨干…… squeezing..." << "[" << percentage << "%]";
                int count;
                for (count = 0; count <= percentage / 2; count++) {
                    std::cout << "█";
                }
                for (int j = 0; j <= 50 - count; j++) {
                    std::cout << "\033[2m█\033[0m";
                }
                file << "你好";
                space += 7;
                if (!file) {
                    system("cls");
                    std::cout << "正在榨干…… squeezing..." << "[" << 100 << "%]" << "██████████████████████████████████████████████████" << std::endl;
                    std::cout << "完成！Done!" << std::endl;
                    SetFileAttributes(CstrToLPCWSTR(dirpath.c_str()), FILE_ATTRIBUTE_HIDDEN);
                    file.close();  // 关闭文件
                    break;
                }
            }
        }
        else {
            std::cout << "Unable to create and open file." << std::endl;
            std::cout << "无法创建并打开文件。" << std::endl;
            Sleep(100);
        }
    }
}


void cmd(std::string disk) {
    long long a;
    long name;
    a = 1099511627776;
    name = 1;
    std::string filepath = disk + "\\squeezedisk";
    std::string command = "md " + filepath;
    system(command.c_str());
    while (true) {
        command = "";
        command = "fsutil file createnew ";
        command.append(filepath);
        command.append("\\");
        command.append(IntToString(name));
        command.append(" 1099511627776");
        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "命令成功运行！The command ran successfully!" << std::endl;
            name += 1;
        }
        else {
            if (a == 1) {
                std::cout << "完成！Done!";
                SetFileAttributes(CstrToLPCWSTR(filepath.c_str()), FILE_ATTRIBUTE_HIDDEN);
                break;
            }
            else {
                if (a == 1099511627776) {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 549755813888");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 549755813888;
                    }
                }
                else if (a == 549755813888) {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 1073741824");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 1073741824;
                    }
                }
                else if (a == 1073741824) {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 536870912");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 536870912;
                    }
                }
                else if (a == 536870912) {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 1048576");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 1048576;
                    }
                }
                else if (a == 1048576) {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 524288");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 524288;
                    }
                }
                else if (a == 524288) {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 1024");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 1024;
                    }
                }
                else if (a == 1024) {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 512");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 512;
                    }
                }
                else {
                    command = "fsutil file createnew ";
                    command.append(filepath);
                    command.append("\\");
                    command.append(IntToString(name));
                    command.append(" 1");
                    result = system(command.c_str());
                    name += 1;
                    if (result != 0) {
                        a = 1;
                    }
                }
            }
        }
    }
}




LPCWSTR CstrToLPCWSTR(const char* str) {
    if (str == nullptr) return L"";

    // 获取字符串长度
    int length = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    if (length == 0) return L"";

    // 分配足够的内存来存储宽字符字符串
    wchar_t* wideStr = new wchar_t[length];

    // 执行转换
    MultiByteToWideChar(CP_ACP, 0, str, -1, wideStr, length);

    return wideStr;
}

std::string IntToString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}
