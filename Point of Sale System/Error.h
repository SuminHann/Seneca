/* Citation and Sources...
Final Project Milestone 5 
Module: Error.h
Filename: Error.h
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
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H

namespace sdds{
    class Error{
        char* m_error;

        public:
        Error(); //set errorMsg to "No Error" state
        Error(const char* error); //set errorMsg to erroneous state
        // Error(const Error& other);
        ~Error();
        void set(const char* error);
        Error& operator=(const Error& rhs);
        operator bool() const;
        Error& clear();
        const char* getError() const;
    };
    std::ostream& operator<<(std::ostream& os, const Error& a);
}
#endif