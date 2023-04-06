#pragma once
#include "ConsoleUtils.h"
#include <iostream>
#include <string>

namespace ConsoleUtils
{
    void Print(std::string s)
    {
        std::cout << s << std::endl;
    }
    void Print()
    {
        Print("");
    }
    void WaitForKeyPress()
    {
        Print("[Press enter to continue...]");
        std::cin.get();
        //Print();
    }
}