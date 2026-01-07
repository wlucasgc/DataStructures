//=================================================================================================
// DATA STRUCTURE (BASE CLASS)
//=================================================================================================

#pragma once

//=================================================================================================
// LIBRARIES
//=================================================================================================

#include <Arduino.h>
#include "IDataStructureCallback.h"

//=================================================================================================
// CLASS
//=================================================================================================

class DataStructure {
    protected:
        IDataStructureCallback* _callback;

        DataStructure():
            _callback(nullptr) {
        }

        void _executeCallback() {
            if(this->_callback) {
                this->_callback->execute();
            }
        }

    public:
        /**
         * @brief Sets a callback object to be invoked when the data structure changes.
         * 
         * @param callback Reference to an object implementing IDataStructureCallback.
         * 
         * @note The provided callback object must remain valid for the lifetime
         *       of the data structure or until another callback is set.
         * @note Passing a different callback replaces the previously set one.
         * @note The callback is invoked only when a modifying operation succeeds.
         */
        void setCallback(IDataStructureCallback& callback) {
            this->_callback = &callback;
        };

        /**
         * @brief Removes the callback.
         * 
         * @note After calling this method, no callback will be invoked
         *       on data structure modification events.
         */
        void clearCallback() {
            this->_callback = nullptr;
        }
};

//=================================================================================================