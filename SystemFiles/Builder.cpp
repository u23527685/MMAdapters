/**
 * @file Builder.cpp
 * @brief Implementation of common Builder functionality.
 *
 * Provides the default constructor and a generic build() that delegates
 * Query construction to Query's constructor taking a Builder*.
 */

#include "Builder.h"
#include "Query.h" 

Builder::Builder(){
    item=nullptr;
    type="";
    question="";
}

/**
 * @brief Build a Query using this builder's state.
 *
 * The Query constructor reads the Builder's protected members to initialize
 * itself. The returned Query is dynamically allocated and must be deleted
 * by the caller.
 *
 * @return Pointer to a newly allocated Query.
 */
Query* Builder::build(){
    return new Query(this);
}