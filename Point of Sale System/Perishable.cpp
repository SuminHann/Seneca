/* Citation and Sources...
Final Project Milestone 5 
Module: Perishable.cpp
Filename: Perishable.cpp
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
#include "Perishable.h"
using namespace std;

namespace sdds{
    char Perishable::itemType() const{
        return 'P';
    }
    Date Perishable::date() const{
        return m_date;
    }
    std::ostream& Perishable::write(std::ostream& os) const{
        Item::write(os);
        if(*this){
            if(m_displayType == POS_LIST){
                os << " " << m_date << " |";
            }
            else if(m_displayType == POS_FORM){
                os << "Expiry date: " << m_date << endl;
                os << "=============^" << endl;
            }
        }
        return os;
    }
    std::istream& Perishable::read(std::istream& is){
        Item::read(is);
        if(m_ErrorState.getError() != ERROR_POS_EMPTY && !(is.fail())){
            Date tempDate;
            tempDate.dateOnly(true);
            cout << "Expiry date (YYYY/MM/DD)" << endl;
            do{
                cout << "> ";
                is >> tempDate;
                tempDate.validation();
                if(!tempDate){
                    tempDate.clear();
                }
                else{
                    m_date.dateOnly(true);
                    m_date = tempDate;
                }
            }while(!m_date);
        }
        return is;
    }
    std::ofstream& Perishable::save(std::ofstream& of) const{
        Item::save(of);
        if(*this){
            of << "," << m_date;
        }
        return of;
    }
    std::ifstream& Perishable::load(std::ifstream& inputfile){
        Item::load(inputfile);
        if(*this){
            Date tempDate;
            tempDate.dateOnly(true);
            inputfile.ignore();
            inputfile >> tempDate;
            if(tempDate){
                m_date.dateOnly(true);
                m_date = tempDate;
            }
            else{
                m_ErrorState = tempDate.error();
            }
        }
        return inputfile;
    }
}