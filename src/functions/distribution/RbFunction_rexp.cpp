/**
 * @file
 * This file contains the implementation of RbFunction_rexp, the
 * rexp() function.
 *
 * @brief Implementation of RbFunction_rexp
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author Fredrik Ronquist and the REvBayes core team
 * @license GPL version 3
 * @version 1.0
 * @since Version 1.0, 2009-08-26
 *
 * $Id$
 */

#include "RbFunction_rexp.h"
#include "RbDouble.h"
#include "RbInt.h"
#include "RbObject.h"
#include "DAGNode.h"
#include "RbException.h"
#include "RbStatistics.h"

const StringVector RbFunction_rexp::rbClass = StringVector("rexp") + RbFunction::rbClass;

/** Define the argument rules */

/** Add to symbol table */
//static bool fxn_rexp = SymbolTable::globalTable().add("rexp", new RbFunction_rexp());


/** Default constructor, allocate workspace */
RbFunction_rexp::RbFunction_rexp(void)
    : RbFunction(), value(new RbDouble(0)) {

	argRules.push_back( ArgumentRule("n", "int", new RbInt(1), new RbInt(0), NULL) );
	argRules.push_back( ArgumentRule("rate", "double", new RbDouble(1.0), new RbDouble(0.0), NULL) );
	returnType = "double";
} 

/** Copy constructor */
RbFunction_rexp::RbFunction_rexp(const RbFunction_rexp& s)
    : RbFunction(s), value(new RbDouble(0)) {
    
	argRules.push_back( ArgumentRule("n", "int", new RbInt(1), new RbInt(0), NULL) );
	argRules.push_back( ArgumentRule("rate", "double", new RbDouble(1.0), new RbDouble(0.0), NULL) );
	returnType = "double";
}

/** Destructor, delete workspace */
RbFunction_rexp::~RbFunction_rexp() {

    delete value;
}

/**
 * @brief clone function
 *
 * This function creates a deep copy of this object.
 *
 * @see RbObject.clone()
 * @returns           return a copy of this object
 *
 */
RbObject* RbFunction_rexp::clone(void) const {

    RbObject *x = new RbFunction_rexp( *this );
    return x;
}

RbObject& RbFunction_rexp::operator=(const RbObject& obj) {

    try {
        // Use built-in fast down-casting first
        const RbFunction_rexp& x = dynamic_cast<const RbFunction_rexp&> (obj);

        RbFunction_rexp& y = (*this);
        y = x;
        return y;
    } catch (std::bad_cast & bce) {
        try {
            // Try converting the value to an argumentRule
            const RbFunction_rexp& x = dynamic_cast<const RbFunction_rexp&> (*(obj.convertTo("rexp")));

            RbFunction_rexp& y = (*this);
            y = x;
            return y;
        } catch (std::bad_cast & bce) {
            RbException e("Not supported assignment of " + obj.getClass()[0] + " to rexp");
            throw e;
        }
    }

    // dummy return
    return (*this);
}

RbFunction_rexp& RbFunction_rexp::operator=(const RbFunction_rexp& obj) {

    argRules = obj.argRules;
    returnType = obj.returnType;
    (*value) = (*obj.value);
    return (*this);
}

/**
 * @brief print function
 *
 * This function prints this object.
 *
 * @see RbObject.print()
 * @param c           the stream where to print to
 *
 */
void RbFunction_rexp::print(std::ostream &c) const {

    c << "RbFunction_rexp" << std::endl;
}

void RbFunction_rexp::printValue(std::ostream &o) const {

    o << value << std::endl;
}

/**
 * @brief dump function
 *
 * This function dumps this object.
 *
 * @see RbObject.dump()
 * @param c           the stream where to dump to
 *
 */
void RbFunction_rexp::dump(std::ostream& c){
    //TODO implement

    std::string message = "Dump function of RbFunction_rexp not fully implemented!";
    RbException e;
    e.setMessage(message);
    throw e;
}

/**
 * @brief resurrect function
 *
 * This function resurrects this object.
 *
 * @see RbObject.resurrect()
 * @param x           the object from which to resurrect
 *
 */
void RbFunction_rexp::resurrect(const RbDumpState& x){
    //TODO implement
    std::string message = "Resurrect function of RbFunction_rexp not fully implemented!";
    RbException e;
    e.setMessage(message);
    throw e;
}

std::string RbFunction_rexp::toString(void) const {

	char temp[30];
	sprintf(temp, "%1.6lf", value->getValue());
	std::string tempStr = temp;
    return "Value = " + tempStr;
}


/**
 * @brief overloaded == operators
 *
 * This function compares this object
 *
 * @param o           the object to compare to
 *
 */
bool RbFunction_rexp::equals(const RbObject* o) const {

    return false;
}


/** Get number of argument rules */
const int RbFunction_rexp::getNumberOfRules(void) const {
    return 1;
}

/** Execute function */
RbObject* RbFunction_rexp::executeOperation(const std::vector<DAGNode*>& arguments) {

    /* Get actual argument */
    RbInt    *n      = (RbInt*) arguments[0]->getValue();
    RbDouble *lambda = (RbDouble*) arguments[1]->getValue();

// TODO need to implement
//    value->setValue(RbStatistics::expal::rexp(*mu,*sigma,*x));

    return value;
}

RbObject* RbFunction_rexp::convertTo(const std::string& type) const {

    return NULL;
}

/**
 * @brief is convertible to
 *
 * This function checks if this data type can be converted into the given data type.
 *
 * @param dt         the data type we want to convert to
 * @returns          true, if it can be converted
 *
 */
bool RbFunction_rexp::isConvertibleTo(const std::string& type) const {

    return false;
}
