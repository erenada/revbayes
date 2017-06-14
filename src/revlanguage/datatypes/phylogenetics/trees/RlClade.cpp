#include "ConstantNode.h"
#include "Ellipsis.h"
#include "ModelVector.h"
#include "RlClade.h"
#include "RbUtil.h"
#include "RealPos.h"
#include "RlString.h"
#include "TypeSpec.h"

#include <sstream>

using namespace RevLanguage;

/** Default constructor */
Clade::Clade(void) : ModelObject<RevBayesCore::Clade>()
{
    
}

/** Construct from core Clade */
Clade::Clade(RevBayesCore::Clade *c) : ModelObject<RevBayesCore::Clade>( c )
{
    
}

/** Construct from core Clade */
Clade::Clade(const RevBayesCore::Clade &t) : ModelObject<RevBayesCore::Clade>( new RevBayesCore::Clade( t ) )
{
    
}

/** Construct from DAG node */
Clade::Clade(RevBayesCore::TypedDagNode<RevBayesCore::Clade> *n) : ModelObject<RevBayesCore::Clade>( n )
{
    
}



/** Construct */
Clade::Clade(const Clade &t) : ModelObject<RevBayesCore::Clade>( t )
{
    
}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the process.
 */
Clade* Clade::clone(void) const
{
    
	return new Clade(*this);
}


void Clade::constructInternalObject( void ) 
{
    // we free the memory first
    if ( dag_node != NULL )
    {
        if ( dag_node->decrementReferenceCount() == 0 )
        {
            delete dag_node;
        }
    }
    
    // get clade constraint flags
    bool match = static_cast<const RlBoolean &>( optional_match->getRevObject() ).getValue();
    bool neg = static_cast<const RlBoolean &>( is_negative_constraint->getRevObject() ).getValue();
    
    // now allocate a new Clade
    std::vector<RevBayesCore::Taxon> n;
    for (std::vector<RevPtr<const RevVariable> >::iterator it = names.begin(); it != names.end(); ++it) 
    {
        RevBayesCore::Taxon t = RevBayesCore::Taxon(static_cast<const RlString &>( (*it)->getRevObject() ).getValue());
        n.push_back( t );
    }
    
    // now add names to new clade
    for (std::vector<RevPtr<const RevVariable> >::iterator it = names_vector.begin(); it != names_vector.end(); ++it)
    {
        const ModelVector<RlString> &tmp = static_cast<const ModelVector<RlString> &>( (*it)->getRevObject() );
        
        for(size_t i=0; i<tmp.size(); ++i)
        {
            RevBayesCore::Taxon t = RevBayesCore::Taxon( tmp.getElement(i)->getValue() );
            n.push_back( t );
        }
        
    }
    
    // now allocate a new Clade
<<<<<<< HEAD
    for (std::vector<RevPtr<const RevVariable> >::iterator it = clades.begin(); it != clades.end(); ++it)
    {
        const RevBayesCore::Clade &c = static_cast<const Clade &>( (*it)->getRevObject() ).getValue();
=======
    std::vector<RevBayesCore::Clade> optional_constraints;
    for (std::vector<RevPtr<const RevVariable> >::iterator it = clades.begin(); it != clades.end(); ++it)
    {
        
        const RevBayesCore::Clade &c = static_cast<const Clade &>( (*it)->getRevObject() ).getValue();
        
        if (match) {
            optional_constraints.push_back(c);
        }
        
>>>>>>> development
        const std::vector<RevBayesCore::Taxon> &taxa = c.getTaxa();
        for(size_t i=0; i<taxa.size(); ++i)
        {
            const RevBayesCore::Taxon &t = taxa[i];
            n.push_back( t );
        }
<<<<<<< HEAD
        
=======
>>>>>>> development
    }
    
    
    RevBayesCore::Clade *c = new RevBayesCore::Clade(n);
    
    // set the age if provided
    if ( age->getRevObject() != RevNullObject::getInstance() )
    {
        double a = static_cast<const RealPos &>( age->getRevObject() ).getValue();
        c->setAge( a );
    }
    
    // set the number of missing if provided
    if ( missing->getRevObject() != RevNullObject::getInstance() )
    {
        int n = static_cast<const Natural &>( missing->getRevObject() ).getValue();
        c->setNumberMissingTaxa( n );
    }
    
    // set optional clade constraints if provided
    if (match && optional_constraints.size() > 0)
    {
        c->setOptionalConstraints( optional_constraints );
    }
    
    
    // set optional match clade constraint
    c->setOptionalMatch( match );

    // set negative clade constraint
    c->setNegativeConstraint( neg );
    

    dag_node = new RevBayesCore::ConstantNode<RevBayesCore::Clade>("", c);
    dag_node->incrementReferenceCount();
    
}


/**
 * Get the Rev name for the constructor function.
 *
 * \return Rev name of constructor function.
 */
std::string Clade::getConstructorFunctionName( void ) const
{
    // create a constructor function name variable that is the same for all instance of this class
    std::string c_name = "clade";
    
    return c_name;
}


/** Return member rules (no members) */
const MemberRules& Clade::getParameterRules(void) const
{
    
    static MemberRules memberRules;
    static bool rules_set = false;
    
    if ( !rules_set )
    {
        memberRules.push_back( new Ellipsis( "Taxon names as string values.", RlString::getClassTypeSpec() ) );
        memberRules.push_back( new Ellipsis("Taxon names as a vector of string values.", ModelVector<RlString>::getClassTypeSpec() ) );
        memberRules.push_back( new Ellipsis( "Taxa as clade objects.", Clade::getClassTypeSpec() ) );
        memberRules.push_back( new ArgumentRule("age", RealPos::getClassTypeSpec(), "The age of the clade (optional).", ArgumentRule::BY_VALUE, ArgumentRule::ANY, NULL ) );
        memberRules.push_back( new ArgumentRule("missing", Natural::getClassTypeSpec(), "Number of missing taxa in the clade (optional).", ArgumentRule::BY_VALUE, ArgumentRule::ANY, NULL ) );
        memberRules.push_back( new ArgumentRule("negative", RlBoolean::getClassTypeSpec(), "Is this a negative clade constraint?", ArgumentRule::BY_VALUE, ArgumentRule::ANY, new RlBoolean(false) ) );
        memberRules.push_back( new ArgumentRule("optional_match", RlBoolean::getClassTypeSpec(), "Clade constraint satisfied when any Clade argument matched", ArgumentRule::BY_VALUE, ArgumentRule::ANY, new RlBoolean(false) ) );
//        memberRules.push_back( new ArgumentRule("optional_constraints", ModelVector<Clade>::getClassTypeSpec(), "Optional clade constraints, i.e. this clade constraint or any optional clade constraint must be satisifed (optional).", ArgumentRule::BY_VALUE, ArgumentRule::ANY, NULL ) );
        
<<<<<<< HEAD
=======
        
>>>>>>> development
        rules_set = true;
    }
    
    return memberRules;
}


/** Get Rev type of object */
const std::string& Clade::getClassType(void)
{
    
    static std::string rev_type = "Clade";
    
	return rev_type; 
}

/** Get class type spec describing type of object */
const TypeSpec& Clade::getClassTypeSpec(void)
{
    
    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( ModelObject<RevBayesCore::Clade>::getClassTypeSpec() ) );
    
	return rev_type_spec; 
}


/** Get type spec */
const TypeSpec& Clade::getTypeSpec( void ) const
{
    
    static TypeSpec type_spec = getClassTypeSpec();
    
    return type_spec;
}


/** Set a member variable */
void Clade::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var)
{
    
    if ( name == "taxonName" || (name == "" && var->getRevObject().getTypeSpec() == RlString::getClassTypeSpec() ) )
    {
        names.push_back( var );
    }
    else if ( name == "" && var->getRevObject().getTypeSpec() == Clade::getClassTypeSpec() )
    {
        clades.push_back( var );
    }
    else if ( name == "" && var->getRevObject().getTypeSpec() == ModelVector<RlString>::getClassTypeSpec() )
    {
        names_vector.push_back( var );
    }

    else if ( name == "age")
    {
        age = var;
    }
    else if ( name == "missing")
    {
        missing = var;
    }
    else if ( name == "negative" )
    {
        is_negative_constraint = var;
    }
    else if ( name == "optional_match" )
    {
        optional_match = var;
    }
//    else if ( name == "optional_constraints" )
//    {
//        optional_constraints = var;
//    }
    else
    {
        RevObject::setConstParameter(name, var);
    }
}

