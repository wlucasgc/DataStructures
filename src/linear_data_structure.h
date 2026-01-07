//=================================================================================================
// LINEAR DATA STRUCTURE (BASE CLASS)
//=================================================================================================

#pragma once

//=================================================================================================
// LIBRARIES
//=================================================================================================

#include <vector>
#include "data_structure.h"

//=================================================================================================
// CLASS
//=================================================================================================

template <typename T>
class LinearDataStructure : public DataStructure {
    protected:
        byte _maxSize;
        bool _allowDuplicates;
        std::vector<T> _elements;
    
        LinearDataStructure():
            DataStructure(),
            _maxSize(0),
            _allowDuplicates(true) {
        }

        /**
         * @brief Replaces the element at the specified index. 
         * 
         * @param index Zero-based index of the element to replace.
         * @param element New value to store at the index.
         * 
         * @return true if the element was successfully set and matches the new value,
         *         false if index was out of bounds.
         * 
         * @note Index 0 is the first element.
         * @note Triggers onChange callback if a callback is set.
         */
        const bool _set(const byte& index, const T& element) {
            if(index >= this->_elements.size()) {
                return(false);
            }
            
            this->_elements.at(index) = element;

            if(this->_elements.at(index) != element) {
                return(false);
            }

            this->_executeCallback();

            return(true);
        }

        /**
         * @brief Inserts an element at the specified index.
         * 
         * @param index Zero-based position where the element should be inserted.
         * @param element The element to insert.
         * 
         * @return true if the element was successfully inserted, false if full,
         *         duplicate rejected, or insertion failed.
         *
         * @note If index is equal to the current size, the element is appended at the end.
         * @note Triggers onChange callback if a callback is set and insertion succeeds.
         */
        const bool _insert(const byte& index, const T& element) {
            if(this->isFull()) {
                return(false);
            }

            if(!this->_allowDuplicates && this->exists(element)) {
                return(false);
            }
            
            const byte sizeBefore = this->_elements.size();

            this->_elements.insert(this->_elements.begin() + index, element);
            
            if(this->_elements.size() <= sizeBefore) {
                return(false);
            }

            this->_executeCallback();

            return(true);
        }

        /**
         * @brief Removes the element at the specified index.
         * 
         * @param index Zero-based index of the element to remove.
         *
         * @return true if the element was successfully removed, false if index
         *         was out of bounds or removal failed.
         * 
         * @note Validates index bounds before removal.
         * @note Triggers onChange callback if a callback is set and removal succeeded.
         */
        const bool _remove(const byte& index) {
            if(index >= this->_elements.size()) {
                return(false);
            }
            
            const byte sizeBefore = this->_elements.size();

            this->_elements.erase(this->_elements.begin() + index);
            
            if(this->_elements.size() >= sizeBefore) {
                return(false);
            }

            this->_executeCallback();

            return(true);
        }
        
        /**
         * @brief Removes duplicate elements from the linear data structure.
         * 
         * @note Keeps the first occurrence of each element and removes all subsequent
         *       duplicates, preserving the original order.
         */
        void _removeDuplicates() {
            if(this->_elements.size() < 2) {
                return;
            }
            
            byte indexA = 0;
            
            while(indexA < this->_elements.size() - 1) {
                T elementA = this->_elements.at(indexA);
                byte indexB = indexA + 1;
                
                while(indexB < this->_elements.size()) {
                    T elementB = this->_elements.at(indexB);

                    if(elementA != elementB) {
                        indexB++;
                        continue;
                    }
                    
                    this->_elements.erase(this->_elements.begin() + indexB);
                }

                indexA++;
            }
        }

    public:
        /**
         * @brief Sets the maximum size limit.
         * 
         * @param maxSize New maximum size limit for the linear data structure.
         *
         * @note If maxSize is 0, removes the size limit (no maximum).
         * @note Removes elements from the end if current size exceeds maxSize.
         * @note No elements are removed if current size is already ≤ maxSize.
         */
        void setMaxSize(const byte& maxSize) {
            this->_maxSize = maxSize;

            if(this->_maxSize == 0) {
                return;
            }
            
            while(this->_elements.size() > this->_maxSize) {
                this->_remove(this->_elements.size() - 1);
            }
        }

        /**
         * @brief Gets the current maximum size limit of the linear data structure.
         * 
         * @return Current maxSize value (0 means no maximum limit).
         * 
         * @note Returns 0 when no size limit is set.
         */
        const byte getMaxSize() const {
            return(this->_maxSize);
        }

        /**
         * @brief Sets whether duplicate elements are allowed in the linear data structure.
         * 
         * @param allowDuplicates true to allow duplicates, false to remove them.
         *
         * @note If set to false, immediately removes all duplicate elements.
         */
        void setAllowDuplicates(const bool& allowDuplicates) {
            this->_allowDuplicates = allowDuplicates;

            if(!this->_allowDuplicates) {
                this->_removeDuplicates();
            }
        }

        /**
         * @brief Gets whether duplicate elements are currently allowed.
         * 
         * @return true if duplicates are allowed, false otherwise.
         */
        const bool getAllowDuplicates() const {
            return(this->_allowDuplicates);
        }

        /**
         * @brief Checks if the specified element exists in the linear data structure.
         * 
         * @param element Element to search for.
         *
         * @return true if element is found, false otherwise.
         */
        const bool exists(const T& element) {
            for(byte i = 0 ; i < this->_elements.size() ; i++) {
                if(element == this->_elements.at(i)) {
                    return(true);
                }
            }

            return(false);
        }

        /**
         * @brief Gets the current number of elements in the linear data structure.
         * 
         * @return Number of elements currently stored.
         */
        const byte size() const {
            return(this->_elements.size());
        }
        
        /**
         * @brief Checks whether the linear data structure is empty.
         * 
         * @return true if the structure contains no elements, false otherwise.
         */
        const bool isEmpty() const {
            return(this->_elements.size() == 0);
        }

        /**
         * @brief Checks whether the data structure is full.
         * 
         * @return true if the structure has reached its maximum capacity,
         *         false otherwise.
         * 
         * @note If maxSize is set to 0, the structure is considered unbounded
         *       and this method always returns false.
         */
        const bool isFull() const {
            if(this->_maxSize == 0) {
                return(false);
            }

            return(this->_elements.size() == this->_maxSize);
        }

        /**
         * @brief Retrieves the element at the specified index.
         * 
         * @param index Zero-based index of the element to retrieve.
         * @param element Reference where the retrieved value will be stored.
         * 
         * @return true if the element was successfully retrieved,
         *         false if the index is out of bounds.
         * 
         * @note Index 0 refers to the first element.
         * @note The output parameter is only modified when the method returns true.
         */     
        const bool get(const byte& index, T& element) {
            if(index >= this->_elements.size()) {
                return(false);
            }

            element = this->_elements.at(index);
            return(true);
        }

        /**
         * @brief Appends all elements from another linear data structure.
         * 
         * @param other Source linear data structure whose elements will be appended.
         * 
         * @return true if all elements were successfully appended,
         *         false if the operation would exceed the maximum size.
         * 
         * @note If maxSize is greater than 0, this method checks capacity before
         *       appending any element.
         * @note Elements are appended in the same order as in the source linear data structure.
         * @note No partial insertion occurs if the maximum size would be exceeded.
         */
        const bool extend(LinearDataStructure<T>& other) {
            if(this->_maxSize > 0 && this->_elements.size() + other.size() > this->_maxSize) {
                return(false);
            }
            
            for(byte i = 0 ; i < other.size() ; i++) {
                T element;
                other.get(i, element);
                this->_insert(this->size(), element);
            }

            return(true);
        }

        /**
         * @brief Replaces the contents of the structure with another one.
         * 
         * @param other Source linear data structure to copy elements from.
         * 
         * @return true if all elements were successfully copied,
         *         false if the source size exceeds the maximum capacity.
         * 
         * @note The current contents are cleared before copying.
         * @note If maxSize is greater than 0, capacity is checked before clearing.
         * @note Elements are copied in the same order as in the source linear data structure.
         */
        const bool copy(LinearDataStructure<T>& other) {
            if(this->_maxSize > 0 && other.size() > this->_maxSize) {
                return(false);
            }

            this->clear();
            
            for(byte i = 0 ; i < other.size() ; i++) {
                T element;
                other.get(i, element);
                this->_insert(this->size(), element);
            }

            return(true);
        }
        
        /**
         * @brief Removes all elements from the linear data structure.
         * 
         * @return true if the structure was successfully cleared,
         *         false if the structure is not empty after the operation.
         * 
         * @note Triggers the onChange callback if a callback is set and clearing succeeds.
         */
        const bool clear() {
            const byte sizeBefore = this->_elements.size();

            this->_elements.clear();
            
            if(!this->isEmpty()) {
                return(false);
            }

            if(this->_elements.size() == sizeBefore) {
                return(true);
            }

            this->_executeCallback();
            
            return(true);
        }
};

//=================================================================================================