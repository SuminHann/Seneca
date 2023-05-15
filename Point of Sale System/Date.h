/* Citation and Sources...
Final Project Milestone 5 
Module: Date.h
Filename: Date.h
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

#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Error.h"
#include "Utils.h"

namespace sdds{
    class Date{
        int m_year;
        int m_month;
        int m_day;
        int m_hour;
        int m_minute;
        bool m_dateOnly;
        Error m_error;

        public:
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour, int minute=0);
        Date& operator=(const Date&);
        void validation();
        void clear();
        bool operator==(const Date& rhs) const;
        bool operator!=(const Date& rhs) const ;
        bool operator<(const Date& rhs) const; 
        bool operator>(const Date& rhs) const;
        bool operator<=(const Date& rhs) const;
        bool operator>=(const Date& rhs) const;
        Date& dateOnly(bool dateOnly);
        operator bool() const;
        const Error& error() const;
        const int year() const;
        const int month() const;
        const int day() const;
        const int hour() const;
        const int minute() const;
        const bool dateOnly() const;
        friend std::istream& operator>>(std::istream& is, Date& a);
    };
    std::ostream& operator<<(std::ostream& os, const Date& a);
    
}
#endif