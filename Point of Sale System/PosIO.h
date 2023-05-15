/* Citation and Sources...
Final Project Milestone 5 
Module: PosIO.h
Filename: PosIO.h
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
#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#include <iostream>
#include "Error.h"

namespace sdds{
    class PosIO{
        public:
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual std::ofstream& save(std::ofstream& of) const = 0;
        virtual std::ifstream& load(std::ifstream& inputfile) = 0;
    };
    std::ostream& operator<<(std::ostream& os, PosIO& obj);
    std::ofstream& operator<<(std::ofstream& os, PosIO& obj);
    std::istream& operator>>(std::istream& is, PosIO& obj);
    std::ifstream& operator>>(std::ifstream& is, PosIO& obj);
}

#endif