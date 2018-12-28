//
// Created by gil on 18/12/18.
//

//TODO - var and

#include <iostream>
#include <regex>
#include "ShuntingYard.h"
// CPP program to evaluate a given
// expression where tokens are
// separated by space.


ShuntingYard::ShuntingYard(){
    initializeMap();

}


//ShuntingYard::ShuntingYard() {
//
//    initializeMap();
//}

void ShuntingYard::initializeMap() {
    this->precedences.insert(pair<char,int>('/',2));
    this->precedences.insert(pair<char, int>('*',2));
    this->precedences.insert(pair<char,int >('+',1));
    this->precedences.insert(pair<char,int >('-',1));
    this->precedences.insert(pair<char,int >('(',0));
    this->precedences.insert(pair<char,int >(')',0));
}
//
//// Function to find precedence of
//// operators.
//double ShuntingYard:: precedenceOp(char op) { // TODO change signature.
//    if (op == '(' || op == ')')
//        return 0;
//    if (op == '+' || op == '-')
//        return 1;
//    if (op == '*' || op == '/')
//        return 2;
//    return 0;
//}
//
//

int ShuntingYard::precedence(char operation) {
    if (this->precedences.count(operation)) {
        return this->precedences.at(operation);
    }
    throw "invalid operation!";
}

Expression *ShuntingYard::applyOp(Expression *left, Expression *right, char operation) {
    //    BinaryExpression *binaryExpression;
//    binaryExpression = new BinaryExpression(left, right);

    switch (operation) {
        case '+': {
            Plus *plus = new Plus(left, right);
//            Expression *plus = new Plus(left,right);
            //Plus plus1 = new Plus(left,right);
//            plus->calculate();
            return plus;
        }
        case '-': {
            Minus *minus1 = new Minus(left, right);
//            minus1->calculate();
            return minus1;
        }
        case '*': {
            Multiplication *multiplication = new Multiplication(left, right);
//            multiplication->calculate();
            return multiplication;
        }
        case '/': {
            Division *division = new Division(left, right);
//            division->calculate();
            return division;
        }
    }

}

int ShuntingYard:: checkNeg(string token) {
    int j, k = 0;
    int flag = 0; // the sign flag.
    regex reg3("[/^(\\+|\\-|-|\\*|\\/|||||,|-|||!|||))$/]");
    string check = " ";

        if(token.at(1) == '-') {
            flag = 1;
        }
    return flag;
}

// Function that returns value of
// expression after evaluation.
Expression* ShuntingYard:: evaluate(string tokens) {
    int i;

    // checking if the token is a variable from the vars maps
    DataBase* dataBase = DataBase::getInstance();
    if(dataBase->getStrDoubleMap().find(tokens) != dataBase->getStrDoubleMap().end()) {
        Expression* expression1 = new VariableExpression(tokens);
        return expression1;
    }

    // stack to store integer values.
    stack<Expression *> values;
//        queue<Expression> queue1;

    // stack to store operators.
    stack<char> ops;

    for (i = 0; i < tokens.length(); i++) {


        // Current token is a whitespace, skip it.
        if (tokens[i] == ' ')
            continue;

            // Current token is an opening brace, push it to 'ops'
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

            // Current token is a number, push it to stack for numbers.
        else if (isdigit(tokens[i])) {
            int val = 0;

            // There may be more than one
            // digits in number.
            while (i < tokens.length() && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            i--;
            Expression *num = new UnaryExpression(val);

            values.push(num);
        }

       // Closing brace encountered, solve
            // entire brace.
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                Expression* right = values.top();
                values.pop();

                Expression* left = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(left, right, op));
            }

            // pop opening brace.
            ops.pop();
        }

            // Current token is an operator.
        else {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while (!ops.empty() && precedence(ops.top())
                                   >= precedence(tokens[i])) {
                Expression* right = values.top();
                values.pop();

                Expression* left = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(left, right, op));
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while (!ops.empty()) {
        Expression* right = values.top();
        values.pop();

        Expression* left = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(left, right, op));
    }

    // Top of 'values' contains result, return it.

    return values.top();
}

int ShuntingYard:: test() {
    cout << evaluate("10 + 2 * 6") << "\n";
    cout << evaluate("100 * 2 + 12") << "\n";
    cout << evaluate("100 * ( 2 + 12 )") << "\n";
    cout << evaluate("100 * ( 2 + 12 ) / 14");
    return 0;
}



//// Function to perform arithmetic operations.
//Expression* ShuntingYard::applyOp(Expression *left, Expression *right, char operation) {
//
//
//}
