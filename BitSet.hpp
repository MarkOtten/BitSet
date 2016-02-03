#ifndef BitSet_hpp
#define BitSet_hpp
#include <iostream>


/*  The BitSet class contains a pointer to a number of unsigned longs. The bits of the afformentioned unsigned longs are
 * used to represent the presence of (1) or absence of (0) a value. This class is useful when representing data in a
 * memory constrained environment, and differs from the standard library bitSet class in that it can also perform the following
 *  set operations: union, intersection, difference, and ones complement.
 */

class BitSet
{
public:
    
    BitSet(const BitSet &);
    
    BitSet(unsigned maxValue);
    
    ~BitSet();
    
    void set_union(const BitSet &);

    void intersection(const BitSet &);

    void difference(const BitSet &);

    void onesComplement();

    // add a new element to the set. returns false if input is invalid.
    bool addElement(unsigned long);

    // delete an element from the set. returns false if not a member.
    bool deleteElement(unsigned long);

    bool isMember(unsigned long);

    unsigned int numElements();

    void printElements();

private:
    
    //internal representation of our set.
    unsigned long *set;
    
    // [0 , maxValue-1]
    unsigned maxElementValue;

    //keeps track of the number of elements pointed to by set
    unsigned numBuckets;

    //the number of items in the set
    unsigned int numItems;

    //iterates through set and counts elements (1's) present
    unsigned int getNumElements();

    //disallow assignment
    BitSet &operator=(const BitSet &);

    //given a number returns the given bucket that the number will reside in
    unsigned bucketNumber(unsigned  number);

    //given a number returns the bit representation of the number assuming 
    //that the correct bucket is being acessed
     unsigned long bitRepresentation(unsigned  number);


};
#endif