/* Citation and Sources...
Final Project Milestone 5 
Module: Item.h
Filename: Item.h
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
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "POS.h"
#include "PosIO.h"
#include "Error.h"
#include "Date.h"

namespace sdds{
    class Item : public PosIO{
        char SKU[MAX_SKU_LEN];
        char* m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;

        protected:
        int m_displayType;
        Error m_ErrorState;

        public:
        Item();
        Item(Item&);
        Item& operator=(const Item&);
        virtual ~Item();
        bool operator==(const char* sku) const;
        bool operator>(const Item& a) const;
        int operator+=(int rhs);
        int operator-=(int rhs);
        operator bool() const;
        virtual char itemType() const = 0;
        Item& displayType(int type);
        char* name() const;
        double cost() const;
        int quantity() const;
        bool taxed() const;
        const char* sku() const;
        double price() const;
        // virtual Date date() const =0;
        Item& clear();
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
        std::ofstream& save(std::ofstream& of) const;
        std::ifstream& load(std::ifstream& inputfile);
        std::ostream& bprint(std::ostream& os) const;
    };
    double operator+=(double value, const Item& rhs);
}

#endif