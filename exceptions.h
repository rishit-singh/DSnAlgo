#pragma once

#include <string.h>
#include "algorithms.h"

#define EXCEPTIONS_H
#define EXCEPTIONS_H

namespace ErrorHandler
{
    class Exception
    {
    public:
        char* Message;

        Exception(char* message) //
        {
            // strcpy(message, this->Message);
            this->Message = message;
        }
        
        Exception(); 
    };

    Exception* UnsortedArrayException = new Exception("Array not sorted."),
     *InvalidSortCriteria = new Exception("Invalid sorting criteria.");
};