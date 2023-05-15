/* Citation and Sources...
Final Project Milestone 5 
Module: PosIO.cpp
Filename: PosIO.cpp
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2023/04/16  Preliminary release
2020/04/16  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and 
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include "PosIO.h"

using namespace std;

namespace sdds{
    std::ostream& operator<<(std::ostream& os, PosIO& obj){
        return obj.write(os);
    }
    std::ofstream& operator<<(std::ofstream& os, PosIO& obj){
        return obj.save(os);
    }
    std::istream& operator>>(std::istream& is, PosIO& obj){
        return obj.read(is);
    }
    std::ifstream& operator>>(std::ifstream& is, PosIO& obj){
        return obj.load(is);
    }
}