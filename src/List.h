//=================================================================================================
// LIST
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
class List : public LinearDataStructure<T> {
    public:
        /**
         * @brief Constructs an empty list.
         */
        List():
            LinearDataStructure<T>() {
        }
        
        /**
         * @brief Appends an element to the end of the list.
         * 
         * @param element Value to be appended.
         * 
         * @return true if the element was successfully appended,
         *         false otherwise.
         * 
         * @note Triggers onChange callback if a callback is set and the
         *       insertion succeeds.
         */
        const bool append(const T& element) {
            return(this->_insert(this->size(), element));
        }

        /**
         * @brief Inserts an element at the specified index.
         * 
         * @param index Zero-based index where the element will be inserted.
         * @param element Value to be inserted.
         * 
         * @return true if the element was successfully inserted,
         *         false if the index is out of bounds or the structure is full.
         * 
         * @note Existing elements at and after the index are shifted.
         * @note Triggers onChange callback if a callback is set and the insertion succeeds.
         */
        const bool insert(const byte& index, const T& element) {
            return(this->_insert(index, element));
        }

        /**
         * @brief Removes the element at the specified index.
         * 
         * @param index Zero-based index of the element to remove.
         * 
         * @return true if the element was successfully removed,
         *         false if the index is out of bounds.
         * 
         * @note Elements after the index are shifted to fill the gap.
         * @note Triggers onChange callback if a callback is set and the removal succeeds.
         */
        const bool remove(const byte& index) {
            return(this->_remove(index));
        }

        /**
         * @brief Reverses the order of elements in the list.
         * 
         * @return true if the list was successfully reversed.
         * 
         * @note No action is taken if the list contains fewer than two elements.
         * @note Triggers onChange callback if a callback is set and the reversal succeeds.
         */
        const bool reverse() {
            if(this->size() < 2) {
                return(true)
            }
            
            std::vector<T> reversed;

            for(byte i = this->size(); i > 0 ; i--) {
                T element;
                this->get(i - 1, element);
                reversed.push_back(element);
            }

            this->_elements = reversed;
            return(true);
        }

        /**
         * @brief Sorts the elements in ascending order.
         * 
         * @return true if the structure was successfully sorted.
         * 
         * @note No action is taken if the structure contains fewer than two elements.
         * @note Sorting is performed using an iterative merge sort algorithm.
         * @note Triggers the onChange callback if a callback is set and sorting succeeds.
         */
        const bool sort() {
            const byte size = this->size();

            if(size < 2) {
                return(true);
            }

            std::vector<T> buffer;
            buffer.reserve(size);

            for(byte width = 1; width < size; width *= 2) {
                for(byte left = 0; left < size; left += 2 * width) {
                    byte mid   = min(left + width, size);
                    byte right = min(left + 2 * width, size);
                    byte i = left;
                    byte j = mid;
                    T element;

                    buffer.clear();

                    while(i < mid && j < right) {
                        element = this->_elements[this->_elements[i] <= this->_elements[j] ? i++ : j++];
                        buffer.push_back(element);
                    }

                    while(i < mid) {
                        element = this->_elements[i++];
                        buffer.push_back(element);
                    }

                    while(j < right) {
                        element = this->_elements[j++];
                        buffer.push_back(element);
                    }

                    for(byte k = 0; k < buffer.size(); k++) {
                        this->_elements[left + k] = buffer[k];
                    }
                }
            }

            if(this->_onChangeCallback) {
                this->_onChangeCallback();
            }

            return(true);
        }
};

//=================================================================================================