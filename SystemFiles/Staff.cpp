#include "Staff.h"

Staff::Staff(std::string name){
    this->name=name;
    next=nullptr;
}

Staff::~Staff(){}

std::string Staff::getName(){
    return name;
}

void Staff::setNext(Staff* staff){
    next=staff;
}

Staff* Staff::getNext(){
    return next;
}