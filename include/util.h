#pragma once
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <vector>

uint8_t* read_bin_file(const std::string file_name){
    FILE* file = std::fopen(file_name.c_str(), "rb");
    if(file == nullptr){
        return nullptr;
    }
    //首先获取文件大小
    std::fseek(file, 0L, SEEK_END); // 移动指针到文件末尾处
    uint64_t fileSize = std::ftell(file);
    std::rewind(file); //重置文件指针到开始处 
    uint8_t* data = (uint8_t*)malloc(fileSize);
    if (data == nullptr || file == nullptr){
        return nullptr;
    }
    std::size_t byteRead = std::fread(data, sizeof(unsigned char), fileSize, file);
    // 检查是否成功读取了预期数量的字节
    if(byteRead != fileSize){
        std::cerr << "读取文件发生错误" << std::endl;
    }

    std::fclose(file);
    return data; 

}
