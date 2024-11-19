//
// Created by yunti on 24-11-19.
//
#include "KernelLib.h"
#include <fstream>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#endif

namespace KernelLib {

    std::string getVersion() {
        return "1.0.0";
    }

    std::string readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::in);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return "";
        }

        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
        file.close();
        return content;
    }

} // namespace KernelLib