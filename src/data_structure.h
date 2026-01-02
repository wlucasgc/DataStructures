//=================================================================================================
// DATA STRUCTURE (BASE CLASS)
//=================================================================================================

#pragma once

//=================================================================================================
// LIBRARIES
//=================================================================================================

#include <Arduino.h>

//=================================================================================================
// CLASS
//=================================================================================================

class DataStructure {
    protected:
        DataStructure(): 
            _onChangeCallback(nullptr) {
        }
        
        void (*_onChangeCallback)();

    public:
        /**
         * @brief Sets a callback to be invoked when the data structure changes.
         * 
         * @param callback Function pointer to be called.
         * 
         * @note Passing a null pointer disables the callback.
         * @note The callback is triggered on operations like add, remove, clear,
         *       or size modifications.
         */

        void onChange(void (*callback)()) {
            this->_onChangeCallback = callback;
        };
};

//=================================================================================================