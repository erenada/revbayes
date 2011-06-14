/**
 * @file
 * This file contains the implementation of Func_readAlignment.
 *
 * @brief Implementation of Func_readAlingment
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date$
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @package functions
 * @since Version 1.0, 2009-09-03
 *
 * $Id$
 */

#include "Boolean.h"
#include "ContainerNode.h"
#include "Func_readAlignment.h"
#include "NclReader.h"
#include "RbException.h"
#include "RbNames.h"
#include "ValueContainer.h"
#include "ValueRule.h"
#include "VectorString.h"

/** Clone object */
Func_readAlignment* Func_readAlignment::clone( void ) const {
    
    return new Func_readAlignment( *this );
}


/** Execute function */
DAGNode* Func_readAlignment::execute( void ) {
    // get the global instance of the NCL reader
    NclReader& reader = NclReader::getInstance();
    
    const VectorString* fn       = static_cast<const VectorString*>( args[0].getValue() );
    const RbString* fileFormat   = static_cast<const RbString*>( args[1].getValue() );
    const RbString* dataType     = static_cast<const RbString*>( args[2].getValue() );
    const Boolean* isInterleaved = static_cast<const Boolean*>( args[3].getValue() );

    std::vector<CharacterMatrix*>* m = reader.readMatrices(fn->getStdVector(),fileFormat->getValue(),dataType->getValue(),isInterleaved->getValue());
    
    // create a value container with all matrices
    ValueContainer* vc = new ValueContainer(m);
    
    return new ContainerNode( vc );
}


/** Get argument rules */
const ArgumentRules& Func_readAlignment::getArgumentRules( void ) const {
    
    static ArgumentRules argumentRules;
    static bool          rulesSet = false;
    
    if (!rulesSet) 
    {
        argumentRules.push_back( new ValueRule( "file", VectorString_name ) );
        argumentRules.push_back( new ValueRule( "format", RbString_name ) );
        argumentRules.push_back( new ValueRule( "type", RbString_name ) );
        argumentRules.push_back( new ValueRule( "interleaved", Boolean_name ) );
        rulesSet = true;
    }
    
    return argumentRules;
}


/** Get class vector describing type of object */
const VectorString& Func_readAlignment::getClass( void ) const {
    
    static VectorString rbClass = VectorString( Func_readAlignment_name ) + RbFunction::getClass();
    return rbClass;
}


/** Get return type */
const TypeSpec Func_readAlignment::getReturnType( void ) const {
    
    return TypeSpec( Alignment_name );
}

