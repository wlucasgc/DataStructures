//=================================================================================================
// STACK
//=================================================================================================

#pragma once

//=================================================================================================
// LIBRARIES
//=================================================================================================

#include "LinearDataStructure.h"

//=================================================================================================
// CLASS
//=================================================================================================

template <typename T>
class Stack : public LinearDataStructure<T> {
    public:
        /**
         * Constructs an empty stack.
         */
        Stack():
            LinearDataStructure<T>() {
        }
        
        /**
         * @brief Adds an element to the end of the stack.
         * 
         * @param element Value to be added to the stack.
         * 
         * @return true if the element was successfully added, false otherwise.
         * 
         * @note Triggers the onChange callback if a callback is set and the insertion succeeds.
         */
        const bool add(const T& element) {
            return(this->_insert(this->size(), element));
        }

        /**
         * @brief Retrieves the element at the end of the stack without removing it.
         * 
         * @param element Reference where the retrieved value will be stored.
         * 
         * @return true if the element was successfully retrieved, false otherwise.
         * 
         * @note The output parameter is only modified when the method returns true.
         */
        const bool peek(T& element) {
            return(this->get(this->size() - 1, element));
        }
        
        /**
         * @brief Removes the element at the end of the stack.
         * 
         * @return true if the element was successfully removed, false otherwise.
         * 
         * @note Triggers the onChange callback if a callback is set and the removal succeeds.
         */
        const bool pop() {
            return(this->_remove(this->size() - 1));
        }
};

//=================================================================================================