/* Citation and Sources...
Final Project Milestone 5 
Module: NonPerishable.h
Filename: NonPerishable.h
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

#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H
#include "Item.h"

namespace sdds{
    class NonPerishable : public Item{
        public:
        char itemType() const;
        std::ostream& write(std::ostream& os) const;
    };
}


#endif