/**
 * @file
 * This file contains the implementation of RbFunction_pexp, the
 * pexp() function.
 *
 * @brief Implementation of RbFunction_pexp
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

#include "RbFunction_pexp.h"
#include "RbDouble.h"
#include "RbObject.h"
#include "DAGNode.h"
#include "RbException.h"
#include "RbStatistics.h"

const StringVector RbFunction_pexp::rbClass = StringVector("pexp") + RbFunction::rbClass;

/** Define the argument rules */

/** Add to symbol table */
//static bool fxn_pexp = SymbolTable::globalTable().add("pexp", new RbFunction_pexp());


/** Default constructor, allocate workspace */
RbFunction_pexp::RbFunction_pexp(void)
    : RbFunction(), value(new RbDouble(0)) {

	argRules.push_back( ArgumentRule("q", "double", NULL, new RbDouble(0.0), NULL ) );
	argRules.push_back( ArgumentRule("rate", "double", new RbDouble(1.0), new RbDouble(0.0), NULL) );
	returnType = "double";
} 

/** Copy constructor */
RbFunction_pexp::RbFunction_pexp(const RbFunction_pexp& s)
    : RbFunction(s), value(new RbDouble(0)) {
    
	argRules.push_back( ArgumentRule("q", "double", NULL, new RbDouble(0.0), NULL ) );
	argRules.push_back( ArgumentRule("rate", "double", new RbDouble(1.0), new RbDouble(0.0), NULL) );
	returnType = "double";
}

/** Destructor, delete workspace */
RbFunction_pexp::~RbFunction_pexp() {

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
RbObject* RbFunction_pexp::clone(void) const {

    RbObject *x = new RbFunction_pexp( *this );
    return x;
}

RbObject& RbFunction_pexp::operator=(const RbObject& obj) {

    try {
        // Use built-in fast down-casting first
        const RbFunction_pexp& x = dynamic_cast<const RbFunction_pexp&> (obj);

        RbFunction_pexp& y = (*this);
        y = x;
        return y;
    } catch (std::bad_cast & bce) {
        try {
            // Try converting the value to an argumentRule
            const RbFunction_pexp& x = dynamic_cast<const RbFunction_pexp&> (*(obj.convertTo("pexp")));

            RbFunction_pexp& y = (*this);
            y = x;
            return y;
        } catch (std::bad_cast & bce) {
            RbException e("Not supported assignment of " + obj.getClass()[0] + " to pexp");
            throw e;
        }
    }

    // dummy return
    return (*this);
}

RbFunction_pexp& RbFunction_pexp::operator=(const RbFunction_pexp& obj) {

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
void RbFunction_pexp::print(std::ostream &c) const {

    c << "RbFunction_pexp" << std::endl;
}

void RbFunction_pexp::printValue(std::ostream &o) const {

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
void RbFunction_pexp::dump(std::ostream& c){
    //TODO implement

    std::string message = "Dump function of RbFunction_pexp not fully implemented!";
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
void RbFunction_pexp::resurrect(const RbDumpState& x){
    //TODO implement
    std::string message = "Resurrect function of RbFunction_pexp not fully implemented!";
    RbException e;
    e.setMessage(message);
    throw e;
}

std::string RbFunction_pexp::toString(void) const {

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
bool RbFunction_pexp::equals(const RbObject* o) const {

    return false;
}


/** Get number of argument rules */
const int RbFunction_pexp::getNumberOfRules(void) const {
    return 1;
}

/** Execute function */
RbObject* RbFunction_pexp::executeOperation(const std::vector<DAGNode*>& arguments) {

    /* Get actual argument */
    RbDouble *x      = (RbDouble*) arguments[0]->getValue();
    RbDouble *lambda = (RbDouble*) arguments[1]->getValue();

    value->setValue(RbStatistics::Exponential::cdf(*lambda,*x));

    return value;
}

RbObject* RbFunction_pexp::convertTo(const std::string& type) const {

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
bool RbFunction_pexp::isConvertibleTo(const std::string& type) const {

    return false;
}
