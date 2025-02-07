
#include "log.h"

static int g_variable = 5;
static void Log(const char* message){  
    std::cout << message << std::endl;
}

void Log::setLevel(Level level){
    this->level = level;
}

void Log::showErrorLevel(const char* message){
    if(this->level == Level::Error){
        std::cout << message << std::endl;
    }
}

void Log::showWarningLevel(const char* message){
    if(this->level == Level::Warning){
        std::cout << message << std::endl;
    }
}

void Log::showInfoLevel(const char* message){
    if(this->level == Level::Info){
        std::cout << message << std::endl;
    }
}