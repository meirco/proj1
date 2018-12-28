//
// Created by gil on 18/12/18.
//

#include "Expression.h"

#ifndef EX3_CONDITION_H
#define EX3_CONDITION_H

#endif //EX3_CONDITION_H

class Condition {
public:
    virtual bool evaluate() =0;
};

class CompareCondition : public Condition {
protected:
    double left;
    double right;
public:
    CompareCondition(double left1, double right1) : left(left1), right(right1) {}
    CompareCondition() {}

    virtual bool evaluate() =0;
};

class OperatorSmall : public CompareCondition {
public:
    OperatorSmall(double left1, double right1) : CompareCondition(left1, right1) {}

public:
    bool evaluate(){
        return left < right;
    }
};

class OperatorBig : public CompareCondition{
public:
    OperatorBig(double left1, double right1)  : CompareCondition(left1, right1) {}

    bool evaluate(){
        return this->left > this->right;
    }
};

class OperatorSmallEqual : public CompareCondition{
public:
    OperatorSmallEqual(double left1, double right1)  : CompareCondition(left1, right1) {}

    bool evaluate(){
        return this->left <= this->right;
    }
};

class OperatorBigEqual : public CompareCondition{
public:
    OperatorBigEqual(double left1, double right1)  : CompareCondition(left1, right1) {}

    bool evaluate(){
        return this->left >= this->right;
    }
};

class OperatorNotEqual : public CompareCondition{
public:
    OperatorNotEqual(double left1, double right1)  : CompareCondition(left1, right1) {}

    bool evaluate(){
        return this->left != this->right;
    }
};

class OperatorEquals : public CompareCondition{
public:
    OperatorEquals(double left1, double right1)  : CompareCondition(left1, right1) {}

    bool evaluate(){
        return this->left == this->right;
    }
};

// ()
//|
//&