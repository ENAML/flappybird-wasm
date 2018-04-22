/**
 * -----------------------------------------------------------------------------
 * Various Container Structures...
 * -----------------------------------------------------------------------------
 */
#pragma once

#include <vector>
#include <stdio.h>


/**
 * TODO:
 * - add insert(item, idx) method
 * - add remove(idx) method
 */
template <class TYPE>
class ArrayList
{
    public:
    using Vec_TYPE = std::vector<TYPE>;

    protected:
    Vec_TYPE mVec;

    public:
    // Constructor
    ArrayList() {
        // printf("\n\n[CONSTRUCTING ARRAYLIST] \n\n");
    }
    
    // Destructor
    virtual ~ArrayList() {
        // printf("\n\n[DESTROYING ARRAYLIST] \n\n");
    }

    void push(TYPE t) {
        this->mVec.push_back(t);
    }

    TYPE pop() {
        assert(this->size() > 0);
        
        auto elBack = this->mVec.back();
        this->mVec.pop_back();
        return elBack;
    }

    TYPE *get(size_t idx) {
        assert(idx >= 0 && idx < this->size());

        auto ai = &this->mVec.at(idx);
        return ai;
    }

    void set(size_t idx, TYPE t) {
        assert(idx >= 0 && idx < this->size());
        
        this->mVec.at(idx) = t;
    }

    /**
     * returns the # of elements currently in the list
     * (not including empty space)
     */
    size_t size() {
        return this->mVec.size();
    }

    /**
     * returns the max # of elements that can be stored
     * in current memory region
     */
    size_t max() {
        return this->mVec.max_size();
    }

    /**
     * removes all items in list
     */
    void clear() {
        this->mVec.clear();
    }

    typename Vec_TYPE::iterator begin() {
        return this->mVec.begin();
    }

    typename Vec_TYPE::iterator end() {
        return this->mVec.end();
    }

    
    /**
     * calls some lambda function `functor` on each item in ArrayList
     * 
     * lambda function `functor` structured as follows
     * ```
     * auto lambdaFunction = [](TYPE* val, int idx) {
     *     {{ do something }} 
     * };
     * ```
     * 
     */
    template<typename Functor>
    void for_each(Functor function)
    {
        for (int i = 0; i < this->size(); i++)
        {
            function(this->get(i), i);
        }
    }

    /**
     * attempt at a lightweight implementation of `std::remove_if`
     * 
     * lambda function `functor` structured as follows
     * ```
     * auto lambdaFunction = [](TYPE* val, int idx) {
     *      return {{ TRUE / FALSE condition }};
     * };
     * ```
     */
    template<typename Functor>
    size_t remove_if(Functor functor)
    {
        size_t removeCount = 0;

        for (int i = 0; i < this->size(); i++)
        {
            if ( functor(this->get(i), i) )
            {
                // println("match!: %i", i);
                removeCount += 1;
            }            
            else
            {
                if (removeCount > 0)
                {
                    *this->get(i - removeCount) = *this->get(i);
                }
            }
        }

        for (int i = 0; i < removeCount; i++)
        {
            this->pop();
        }

        return removeCount;
    }
};
