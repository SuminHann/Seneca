/* Citation and Sources...
Final Project Milestone 5 
Module: NonPerishable.cpp
Filename: NonPerishable.cpp
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
#include "NonPerishable.h"
using namespace std;

namespace sdds{
    char NonPerishable::itemType() const{
        return 'N';
    }
    std::ostream& NonPerishable::write(std::ostream& os) const{
        if(m_displayType == POS_LIST){
            Item::write(os);
            if(m_ErrorState.getError() != ERROR_POS_EMPTY){
                os << "    N / A   |";
            }
        }
        else if(m_displayType == POS_FORM){
            Item::write(os);
            if(m_ErrorState.getError() != ERROR_POS_EMPTY){
                os << "=============^" << endl;
            }
        }
        return os;
    }
}

