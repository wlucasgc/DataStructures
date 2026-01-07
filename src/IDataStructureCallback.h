//=================================================================================================
// DATA STRUCTURE CALLBACK (INTERFACE)
//=================================================================================================

#ifndef I_DATA_STRUCTURE_CALLBACK_H
#define I_DATA_STRUCTURE_CALLBACK_H

//=================================================================================================
// INTERFACE
//=================================================================================================

class IDataStructureCallback {
    public:
        /**
         * @brief Executes the callback action.
         * 
         * @note The action is executed when a change occurs in the observed data structure.
         * @note The Implementation must be provided by the user of the interface.
         */
        virtual void execute() = 0;
};

#endif

//=================================================================================================