#include "ArgumentRule.h"
#include "ArgumentRules.h"
#include "ConstantNode.h"
#include "Model.h"
#include "Natural.h"
#include "OptionRule.h"
#include "Mcmcmc.h"
#include "Real.h"
#include "RevObject.h"
#include "RbException.h"
#include "RlModel.h"
#include "RlMonitor.h"
#include "RlMove.h"
#include "RlMcmcmc.h"
#include "RlString.h"
#include "TypeSpec.h"
#include "WorkspaceVector.h"


using namespace RevLanguage;

Mcmcmc::Mcmcmc() : WorkspaceToCoreWrapperObject<RevBayesCore::Mcmcmc>()
{
    
    ArgumentRules* runArgRules = new ArgumentRules();
    runArgRules->push_back( new ArgumentRule("generations", Natural::getClassTypeSpec(), ArgumentRule::BY_VALUE ) );
    methods.addFunction("run", new MemberProcedure( RlUtils::Void, runArgRules) );
    
    ArgumentRules* burninArgRules = new ArgumentRules();
    burninArgRules->push_back( new ArgumentRule("generations", Natural::getClassTypeSpec(), ArgumentRule::BY_VALUE ) );
    burninArgRules->push_back( new ArgumentRule("tuningInterval", Natural::getClassTypeSpec(), ArgumentRule::BY_VALUE ) );
    methods.addFunction("burnin", new MemberProcedure( RlUtils::Void, burninArgRules) );
    
    ArgumentRules* operatorSummaryArgRules = new ArgumentRules();
    methods.addFunction("operatorSummary", new MemberProcedure( RlUtils::Void, operatorSummaryArgRules) );
    
}


/** Clone object */
Mcmcmc* Mcmcmc::clone(void) const {
    
    return new Mcmcmc(*this);
}


void Mcmcmc::constructInternalObject( void ) {
    // we free the memory first
    delete value;
    
    // now allocate a new MCMC object
    const RevBayesCore::Model&                  mdl     = static_cast<const Model &>( model->getRevObject() ).getValue();
    const RevBayesCore::RbVector<RevBayesCore::Move>&    mvs     = static_cast<const WorkspaceVector<Move> &>( moves->getRevObject() ).getVectorRbPointer();
    const RevBayesCore::RbVector<RevBayesCore::Monitor>& mntr    = static_cast<const WorkspaceVector<Monitor> &>( monitors->getRevObject() ).getVectorRbPointer();
    const std::string &                         sched   = static_cast<const RlString &>( moveSchedule->getRevObject() ).getValue();
    const int                                   nc      = static_cast<const Natural&>( numChains->getRevObject() ).getValue();
    const int                                   si      = static_cast<const Natural&>( swapInterval->getRevObject() ).getValue();
    const double                                delth   = static_cast<const Real&>( deltaHeat->getRevObject() ).getValue();
    
    value = new RevBayesCore::Mcmcmc(mdl, mvs, mntr, sched, nc, si, delth);
    
}


/* Map calls to member methods */
RevPtr<RevVariable> Mcmcmc::executeMethod(std::string const &name, const std::vector<Argument> &args, bool &found)
{
    
    
    if (name == "run")
    {
        found = true;
        
        // get the member with give index
        int gen = static_cast<const Natural &>( args[0].getVariable()->getRevObject() ).getValue();
        value->run( gen );
        
        return NULL;
    }
    else if (name == "burnin")
    {
        found = true;
        
        // get the member with give index
        int gen = static_cast<const Natural &>( args[0].getVariable()->getRevObject() ).getValue();
        int tuningInterval = static_cast<const Natural &>( args[1].getVariable()->getRevObject() ).getValue();
        value->burnin( gen, tuningInterval );
        
        return NULL;
    }
    else if ( name == "operatorSummary")
    {
        found = true;
        
        value->printOperatorSummary();
        
        return NULL;
    }
    
    return RevObject::executeMethod( name, args, found );
}


/** Get Rev type of object */
const std::string& Mcmcmc::getClassType(void) {
    
    static std::string revType = "Mcmcmc";
    
    return revType;
}

/** Get class type spec describing type of object */
const TypeSpec& Mcmcmc::getClassTypeSpec(void) {
    
    static TypeSpec revTypeSpec = TypeSpec( getClassType(), new TypeSpec( WorkspaceToCoreWrapperObject<RevBayesCore::Mcmc>::getClassTypeSpec() ) );
    
    return revTypeSpec;
}



/** Return member rules (no members) */
const MemberRules& Mcmcmc::getParameterRules(void) const {
    
    static MemberRules memberRules;
    static bool rulesSet = false;
    
    if ( !rulesSet )
    {
        
        memberRules.push_back( new ArgumentRule("model"        , Model::getClassTypeSpec()                   , ArgumentRule::BY_CONSTANT_REFERENCE ) );
        memberRules.push_back( new ArgumentRule("monitors"     , WorkspaceVector<Monitor>::getClassTypeSpec(), ArgumentRule::BY_VALUE ) );
        memberRules.push_back( new ArgumentRule("moves"        , WorkspaceVector<Move>::getClassTypeSpec()   , ArgumentRule::BY_VALUE ) );
        memberRules.push_back( new ArgumentRule("numChains"    , Natural::getClassTypeSpec()                 , ArgumentRule::BY_VALUE, ArgumentRule::ANY, new Natural(4) ) );
        memberRules.push_back( new ArgumentRule("swapInterval" , Natural::getClassTypeSpec()                 , ArgumentRule::BY_VALUE, ArgumentRule::ANY, new Natural(100)) );
        memberRules.push_back( new ArgumentRule("deltaHeat"    , Real::getClassTypeSpec()                    , ArgumentRule::BY_VALUE, ArgumentRule::ANY, new Real(0.2) ) );
        
        std::vector<std::string> options;
        options.push_back( "sequential" );
        options.push_back( "random" );
        options.push_back( "single" );
        
        memberRules.push_back( new OptionRule( "moveschedule", new RlString( "random" ), options ) );
        
        rulesSet = true;
    }
    
    return memberRules;
}


/** Get type spec */
const TypeSpec& Mcmcmc::getTypeSpec( void ) const {
    
    static TypeSpec typeSpec = getClassTypeSpec();
    
    return typeSpec;
}


/** Get type spec */
void Mcmcmc::printValue(std::ostream &o) const {
    
    o << "Mcmcmc";
}


/** Set a member variable */
void Mcmcmc::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var) {
    
    if ( name == "model") {
        model = var;
    }
    else if ( name == "moves") {
        moves = var;
    }
    else if ( name == "monitors") {
        monitors = var;
    }
    else if ( name == "moveschedule") {
        moveSchedule = var;
    }
    else if ( name == "numChains" ) {
        numChains = var;
    }
    else if ( name == "deltaHeat" )
    {
        deltaHeat = var;
    }
    else if ( name == "swapInterval" )
    {
        swapInterval = var;
    }
    else {
        RevObject::setConstParameter(name, var);
    }
}