#include "objPosArrayList.h"
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP; // Initialize the objPosArrayList with ARRAY_MAX_CAP default value

    aList = new objPos[sizeArray];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = nullptr;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList == sizeArray) {
        throw std::length_error("ArrayList is not big enough to insert element."); // throw error if attempting to add more than the array list size cap
    }

    for (int i = sizeList - 1; i >= 0; i--) {
        aList[i+1].setObjPos(aList[i]); // copy the current indexes objPos to next, starting from right most element --> shifts everything to the right
    }

    aList[0].setObjPos(thisPos); // set new head element and increment sizeList
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList == sizeArray) {
        throw std::length_error("ArrayList is not big enough to insert element."); // throw error if attempting to add more than the array list size cap
    }

    aList[sizeList].setObjPos(thisPos); // set new tail element and increment sizeList
    sizeList++;
}

void objPosArrayList::removeHead()
{
    if (sizeList > 0) {
        for (int i = 1; i < sizeList + 1; i++) {
            aList[i-1].setObjPos(aList[i]); // copy the current indexes objPos to previous --> Shifts everything to the left
        }

        sizeList--;
    }
}

void objPosArrayList::removeTail()
{
    if (sizeList > 0) {
        aList[sizeList] = objPos(); // remove/reset tail element and decrement sizeList
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]); // head of list is always the first element in the array
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]); // tail of list is always the size of the list - 1 in array
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index > sizeArray - 1) {
        throw std::out_of_range("Invalid indexes when getting element from objPosArrayList."); // throw error if attempting to access out of bounds
    }
    returnPos.setObjPos(aList[index]);
}