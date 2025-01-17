#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>

int main() {
    std::string code;
    std::getline(std::cin, code);

    // 将代码写入文件
    std::ofstream codeFile("temp.cpp");
    codeFile << code;
    codeFile.close();

    // 编译代码
    int compileResult = system("g++ temp.cpp -o temp");
    if (compileResult != 0) {
        std::cout << "编译错误" << std::endl;
        return 1;
    }

    // 执行代码
    FILE* pipe = popen("./temp", "r");
    if (!pipe) {
        std::cout << "执行错误" << std::endl;
        return 1;
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    // 输出结果
    std::cout << result << std::endl;

    return 0;
} 