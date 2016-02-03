#include "BitSet.hpp"



BitSet::~BitSet(){
        delete[] set;
}



BitSet::BitSet(const BitSet  &setter){

        numBuckets = setter.numBuckets;
        maxElementValue = setter.maxElementValue;
        set = new unsigned long[numBuckets];

        for(int i = 0; i < numBuckets;i++)
                set[i] = setter.set[i];

        numItems = setter.numItems;
}



BitSet::BitSet(unsigned maxValue){

        numItems = 0;

        numBuckets = (bucketNumber(maxValue) + 1);

        maxElementValue = maxValue-1;

        set = new unsigned long[numBuckets];

        for(unsigned i = 0; i<numBuckets;i++)
                set[i] = 0;

}



void BitSet::set_union(const BitSet & other){


        if(other.maxElementValue > maxElementValue)
                maxElementValue = other.maxElementValue;


        if( other.numBuckets > numBuckets ){
                unsigned oldNumBuckets = numBuckets;

                numBuckets = other.numBuckets;

                unsigned long *temp = new unsigned long[numBuckets];

                 for(int i = 0;i < numBuckets;i++)
                        temp[i] = other.set[i];


                for(int j = 0;j < oldNumBuckets; j++)
                        temp[j] |= set[j];


                delete[] set;

                set = new unsigned long[numBuckets];

                for(int k = 0;k < numBuckets;k++)
                        set[k] = temp[k];


                 delete[] temp;

        }
        else if(numBuckets > other.numBuckets){

                for(int i = 0; i < other.numBuckets;i++)
                        set[i] |= other.set[i];
        }
        else{

                for(int i = 0; i < numBuckets;i++)
                        set[i] |= other.set[i];
        }

        numItems = getNumElements();
}



void BitSet::intersection(const BitSet &other){


        if(numBuckets > other.numBuckets){
                unsigned long *temp = new unsigned long[other.numBuckets];
                numBuckets = other.numBuckets;


                 for(int i=0;i<numBuckets;i++)
                        temp[i]=set[i];

                delete[] set;
                set = new unsigned long[numBuckets];

                for(int j=0;j < numBuckets;j++)
                        set[j]=temp[j];

                delete[] temp;
        }

        for(int i = 0; i<numBuckets;i++)
                set[i] &= other.set[i];


        numItems = getNumElements();

}



void BitSet::difference(const BitSet &other){

        int buckets = numBuckets;

        if(numBuckets > other.numBuckets)
                buckets = other.numBuckets;


        for(int i = 0; i < buckets;i++)
                set[i] ^=  (set[i]&other.set[i]);


        numItems = getNumElements();

}



void BitSet::onesComplement(){

        for(int i = 0; i < numBuckets;i++)
                set[i] = ~set[i];

        numItems = getNumElements();

}



bool BitSet::addElement(unsigned long value){


        if( (value > maxElementValue) || ((bitRepresentation(value) & set[bucketNumber(value)]) != 0) ){
                return false;
        }

        numItems++;

        unsigned long valAd = bitRepresentation(value);

        set[bucketNumber(value)] |= valAd;

        return true;
}



bool BitSet::deleteElement(unsigned long value){

         if( (value > maxElementValue) || ((bitRepresentation(value) & set[bucketNumber(value)]) == 0) ){
                 return false;
         }

        numItems--;

        unsigned long valRm = bitRepresentation(value);

        set[bucketNumber(value)] ^= valRm;

        return true;
}



bool BitSet::isMember(unsigned long value){

        unsigned long val = bitRepresentation(value);

        if( (value > maxElementValue) || ((val & set[bucketNumber(value)])== 0) )
                return false;
        else
                return true;
}



unsigned int BitSet:: numElements(){
        return numItems;
}



unsigned int BitSet:: getNumElements(){

        unsigned int numItem = 0;

        for(int i = 0; i < numBuckets; i++){

                for(int j = 0; j < 64; j++){

                        unsigned long val = 1;
                        val = val << j;

                        if( ((set[i]&val) != 0) && ((i*64 + j) <= maxElementValue))
                                numItem++;
                }
        }

        return numItem;
}



void BitSet::printElements(){

        for(int i = 0; i < numBuckets; i++){

                for(int j = 0; j < 64; j++){

                        unsigned long val = 1;
                        val = val << j;

                        if((set[i]&val) != 0){
                                int num = i*64 + (j);

                                if((i*64 + j) <= maxElementValue)
                                        std::cout<<num<<std::endl;
                        }
                }
        }

}



//the first bucket's domain is [0, 63], after which it is  [x, x+64) , (x = 64 + (n-1)*64 )
unsigned BitSet::bucketNumber(unsigned  number){

        unsigned bucketNum = number / 63;

        if(number > 64){
            
                bucketNum = number / 64;

        }
        else{
                if((bucketNum > 0) & ((number % 63) == 0 ))
                        bucketNum--;
        }

        return bucketNum;
}



unsigned long BitSet::bitRepresentation(unsigned  number){

        unsigned long val = 1;

        int amount = number%63;

        if(number > 63){
                amount = number-63;
                amount %= 64;
        }


        if(amount == 0 ){

                if(number != 0)
                        val = val << 63;
        }
        else{

                if(number > 63)
                        val = val << (amount-1);
                 else
                        val = val << amount;

        }

        return val;
}


