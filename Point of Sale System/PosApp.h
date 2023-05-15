/* Citation and Sources...
Final Project Milestone 5 
Module: PosApp.h
Filename: PosApp.h
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
#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Bill.h"

namespace sdds{
    class PosApp{
        char m_fileName[128];
        Item* Iptr[MAX_NO_ITEMS];
        int nptr;
        void actionTitle(const char* title);
        
        public:
        PosApp();
        PosApp(const char* fileName);
        int menu();
        bool addItems();
        bool removeItem();
        int selectItem();
        void stockItem();
        void listItems();
        void POS();
        void saveRecs();
        bool loadRecs(char* fileName);
        void run();
        Item* search(const char sku[MAX_SKU_LEN]);
    };
}



#endif