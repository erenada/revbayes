#include "UpDownScaleProposal.h"
#include "RandomNumberFactory.h"
#include "RandomNumberGenerator.h"
#include "RbException.h"
#include "TreeUtilities.h"
#include "TypedDagNode.h"

#include <cmath>
#include <iostream>

using namespace RevBayesCore;

/**
 * Constructor
 *
 * Here we simply allocate and initialize the Proposal object.
 */
UpDownScaleProposal::UpDownScaleProposal( double l ) : Proposal(),
<<<<<<< HEAD
    upScalarVariables(  ),
    upVectorVariables(  ),
    upTreeVariables(  ),
    downScalarVariables(  ),
    downVectorVariables(  ),
    downTreeVariables(  ),
=======
    up_scalar_variables(  ),
    up_vector_variables(  ),
    up_tree_variables(  ),
    down_scalar_variables(  ),
    down_vector_variables(  ),
    down_tree_variables(  ),
>>>>>>> development
    lambda( l )
{
    
}


/**
 * Add a variable.
 */
void UpDownScaleProposal::addVariable( StochasticNode<double> *v, bool up)
{
    
    
    // add it to the nodes vector
    addNode( v );
    
    // add it to my internal vector
    if ( up == true )
    {
        up_scalar_variables.push_back( v );
    }
    else
    {
        down_scalar_variables.push_back( v );
    }
    
}


/**
 * Add a variable.
 */
void UpDownScaleProposal::addVariable( StochasticNode<RbVector<double> > *v, bool up)
{
    
    
    // add it to the nodes vector
    addNode( v );
    
    // add it to my internal vector
    if ( up == true )
    {
        up_vector_variables.push_back( v );
    }
    else
    {
        down_vector_variables.push_back( v );
    }
    
}


/**
 * Add a variable.
 */
void UpDownScaleProposal::addVariable( StochasticNode<Tree> *v, bool up )
{
    
    
    // add it to the nodes vector
    addNode( v );
    
    // add it to my internal vector
    if ( up == true )
    {
        up_tree_variables.push_back( v );
    }
    else
    {
        down_tree_variables.push_back( v );
    }
    
}


/**
 * The cleanProposal function may be called to clean up memory allocations after AbstractMove
 * decides whether to accept, reject, etc. the proposed value.
 *
 */
void UpDownScaleProposal::cleanProposal( void )
{
    
}

/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the proposal.
 */
UpDownScaleProposal* UpDownScaleProposal::clone( void ) const
{
    
    return new UpDownScaleProposal( *this );
}


/**
 * Get Proposals' name of object
 *
 * \return The Proposals' name.
 */
const std::string& UpDownScaleProposal::getProposalName( void ) const
{
    static std::string name = "UpDownScaling";
    
    return name;
}


/**
 * Perform the proposal.
 *
 * A scaling Proposal draws a random uniform number u ~ unif(-0.5,0.5)
 * and scales the current vale by a scaling factor
 * sf = exp( lambda * u )
 * where lambda is the tuning parameter of the Proposal to influence the size of the proposals.
 *
 * \return The hastings ratio.
 */
double UpDownScaleProposal::doProposal( void )
{
    
    // Get random number generator
    RandomNumberGenerator* rng     = GLOBAL_RNG;
    
    // Generate new value (no reflection, so we simply abort later if we propose value here outside of support)
    double u = rng->uniform01();
    double scaling_factor = std::exp( lambda * ( u - 0.5 ) );
    
    double scalingCount = 0.0;
    
<<<<<<< HEAD
    storedUpScalarValues = std::vector<double>(upScalarVariables.size(), 0.0);
=======
    stored_up_scalar_values = std::vector<double>(up_scalar_variables.size(), 0.0);
>>>>>>> development
    // scale all the single variable up
    for (size_t i=0; i<up_scalar_variables.size(); ++i)
    {
<<<<<<< HEAD
        storedUpScalarValues[i] = upScalarVariables[i]->getValue();
        upScalarVariables[i]->getValue() *= scaling_factor;
        ++scalingCount;
    }
    
    storedUpVectorValues = std::vector<std::vector<double> >(upVectorVariables.size(), std::vector<double>());
=======
        stored_up_scalar_values[i] = up_scalar_variables[i]->getValue();
        up_scalar_variables[i]->getValue() *= scaling_factor;
        ++scalingCount;
    }
    
    stored_up_vector_values = std::vector<std::vector<double> >(up_vector_variables.size(), std::vector<double>());
>>>>>>> development
    // scale all the vector variables up
    for (size_t i=0; i<up_vector_variables.size(); ++i)
    {
<<<<<<< HEAD
        RbVector<double> &v = upVectorVariables[i]->getValue();

        storedUpVectorValues[i] = std::vector<double>(v.size(), 0.0);
        for (size_t j=0; j<v.size(); ++j)
        {
            storedUpVectorValues[i][j] = v[j];
=======
        RbVector<double> &v = up_vector_variables[i]->getValue();

        stored_up_vector_values[i] = std::vector<double>(v.size(), 0.0);
        for (size_t j=0; j<v.size(); ++j)
        {
            stored_up_vector_values[i][j] = v[j];
>>>>>>> development
            v[j] *= scaling_factor;
        }
        scalingCount += v.size();
    }
    
<<<<<<< HEAD
    storedUpTreeValues = std::vector<std::vector<double> >(upTreeVariables.size(), std::vector<double>());
=======
    stored_up_tree_values = std::vector<std::vector<double> >(up_tree_variables.size(), std::vector<double>());
>>>>>>> development
    // scale all the tree variables up
    for (size_t i=0; i<up_tree_variables.size(); ++i)
    {
        
        Tree& tau = up_tree_variables[i]->getValue();
        
        TopologyNode& node = tau.getRoot();

<<<<<<< HEAD
        storedUpTreeValues[i] = std::vector<double>(tau.getNumberOfNodes(), 0.0);
        TreeUtilities::getAges(&tau, &node, storedUpTreeValues[i]);
=======
        stored_up_tree_values[i] = std::vector<double>(tau.getNumberOfNodes(), 0.0);
        TreeUtilities::getAges(&tau, &node, stored_up_tree_values[i]);
>>>>>>> development
        
        // rescale the subtrees
        TreeUtilities::rescaleSubtree(&tau, &node, scaling_factor );
        
        scalingCount += tau.getNumberOfInteriorNodes();
    }
    
<<<<<<< HEAD
    storedDownScalarValues = std::vector<double>(downScalarVariables.size(), 0.0);
=======
    stored_down_scalar_values = std::vector<double>(down_scalar_variables.size(), 0.0);
>>>>>>> development
    // scale all the single variable down
    for (size_t i=0; i<down_scalar_variables.size(); ++i)
    {
<<<<<<< HEAD
        storedDownScalarValues[i] = downScalarVariables[i]->getValue();
        downScalarVariables[i]->getValue() /= scaling_factor;
        --scalingCount;
    }
    
    storedDownVectorValues = std::vector<std::vector<double> >(downVectorVariables.size(), std::vector<double>());
=======
        stored_down_scalar_values[i] = down_scalar_variables[i]->getValue();
        down_scalar_variables[i]->getValue() /= scaling_factor;
        --scalingCount;
    }
    
    stored_down_vector_values = std::vector<std::vector<double> >(down_vector_variables.size(), std::vector<double>());
>>>>>>> development
    // scale all the vector variables down
    for (size_t i=0; i<down_vector_variables.size(); ++i)
    {
<<<<<<< HEAD
        RbVector<double> &v = downVectorVariables[i]->getValue();

        storedDownVectorValues[i] = std::vector<double>(v.size(), 0.0);
        for (size_t j=0; j<v.size(); ++j)
        {
            storedDownVectorValues[i][j] = v[j];
=======
        RbVector<double> &v = down_vector_variables[i]->getValue();

        stored_down_vector_values[i] = std::vector<double>(v.size(), 0.0);
        for (size_t j=0; j<v.size(); ++j)
        {
            stored_down_vector_values[i][j] = v[j];
>>>>>>> development
            v[j] /= scaling_factor;
        }
        scalingCount -= v.size();
    }
    
<<<<<<< HEAD
    storedDownTreeValues = std::vector<std::vector<double> >(downTreeVariables.size(), std::vector<double>());
=======
    stored_down_tree_values = std::vector<std::vector<double> >(down_tree_variables.size(), std::vector<double>());
>>>>>>> development
    // scale all the tree variables down
    for (size_t i=0; i<down_tree_variables.size(); ++i)
    {
        
        Tree& tau = down_tree_variables[i]->getValue();
        
        TopologyNode& node = tau.getRoot();
        
<<<<<<< HEAD
        storedDownTreeValues[i] = std::vector<double>(tau.getNumberOfNodes(), 0.0);
        TreeUtilities::getAges(&tau, &node, storedDownTreeValues[i]);
=======
        stored_down_tree_values[i] = std::vector<double>(tau.getNumberOfNodes(), 0.0);
        TreeUtilities::getAges(&tau, &node, stored_down_tree_values[i]);
>>>>>>> development

        // rescale the subtrees
        TreeUtilities::rescaleSubtree(&tau, &node, 1.0/scaling_factor );
        
        scalingCount -= tau.getNumberOfInteriorNodes();
    }
    
    // compute the Hastings ratio
    double lnHastingsratio = scalingCount * log( scaling_factor );
    
    return lnHastingsratio;
}


/**
 * Prepare the proposal, e.g., pick the UpDown that we want to change.
 * Here we do not need to do any preparation.
 */
void UpDownScaleProposal::prepareProposal( void )
{
    
}


/**
 * Print the summary of the Proposal.
 *
 * The summary just contains the current value of the tuning parameter.
 * It is printed to the stream that it passed in.
 *
 * \param[in]     o     The stream to which we print the summary.
 */
void UpDownScaleProposal::printParameterSummary(std::ostream &o) const
{
    
    o << "lambda = " << lambda;
    
}


/**
 * Remove a variable.
 */
void UpDownScaleProposal::removeVariable( StochasticNode<double> *v, bool up)
{
    
    
    // add it to the nodes vector
    removeNode( v );
    
    // add it to my internal vector
    if ( up == true )
    {
        up_scalar_variables.erase(std::remove(up_scalar_variables.begin(), up_scalar_variables.end(), v), up_scalar_variables.end());
    }
    else
    {
        down_scalar_variables.erase(std::remove(down_scalar_variables.begin(), down_scalar_variables.end(), v), down_scalar_variables.end());
    }
    
}


/**
 * Remove a variable.
 */
void UpDownScaleProposal::removeVariable( StochasticNode<RbVector<double> > *v, bool up)
{
    
    
    // add it to the nodes vector
    removeNode( v );
    
    // add it to my internal vector
    if ( up == true )
    {
        up_vector_variables.erase(std::remove(up_vector_variables.begin(), up_vector_variables.end(), v), up_vector_variables.end());
    }
    else
    {
        down_vector_variables.erase(std::remove(down_vector_variables.begin(), down_vector_variables.end(), v), down_vector_variables.end());
    }
    
}


/**
 * Remove a variable.
 */
void UpDownScaleProposal::removeVariable( StochasticNode<Tree> *v, bool up )
{
    
    
    // add it to the nodes vector
    removeNode( v );
    
    // add it to my internal vector
    if ( up == true )
    {
        up_tree_variables.erase(std::remove(up_tree_variables.begin(), up_tree_variables.end(), v), up_tree_variables.end());
    }
    else
    {
        down_tree_variables.erase(std::remove(down_tree_variables.begin(), down_tree_variables.end(), v), down_tree_variables.end());
    }
    
}


/**
 * Reject the Proposal.
 *
 * Since the Proposal stores the previous value and it is the only place
 * where complex undo operations are known/implement, we need to revert
 * the value of the variable/DAG-node to its original value.
 */
void UpDownScaleProposal::undoProposal( void )
{
    
    // scale all the single variable up
    for (size_t i=0; i<up_scalar_variables.size(); ++i)
    {
<<<<<<< HEAD
        upScalarVariables[i]->getValue() = storedUpScalarValues[i];
=======
        up_scalar_variables[i]->getValue() = stored_up_scalar_values[i];
>>>>>>> development
    }
    
    // scale all the vector variables up
    for (size_t i=0; i<up_vector_variables.size(); ++i)
    {
        RbVector<double> &v = up_vector_variables[i]->getValue();
        for (size_t j=0; j<v.size(); ++j)
        {
<<<<<<< HEAD
            v[j] = storedUpVectorValues[i][j];
=======
            v[j] = stored_up_vector_values[i][j];
>>>>>>> development
        }
    }
    
    // scale all the tree variables up
    for (size_t i=0; i<up_tree_variables.size(); ++i)
    {
        
        Tree& tau = up_tree_variables[i]->getValue();
        
        TopologyNode& node = tau.getRoot();
        
        // rescale the subtrees
<<<<<<< HEAD
        TreeUtilities::setAges(&tau, &node, storedUpTreeValues[i] );
=======
        TreeUtilities::setAges(&tau, &node, stored_up_tree_values[i] );
>>>>>>> development
    }
    
    // scale all the single variable down
    for (size_t i=0; i<down_scalar_variables.size(); ++i)
    {
<<<<<<< HEAD
        downScalarVariables[i]->getValue() = storedDownScalarValues[i];
=======
        down_scalar_variables[i]->getValue() = stored_down_scalar_values[i];
>>>>>>> development
    }
    
    // scale all the vector variables down
    for (size_t i=0; i<down_vector_variables.size(); ++i)
    {
        RbVector<double> &v = down_vector_variables[i]->getValue();
        for (size_t j=0; j<v.size(); ++j)
        {
<<<<<<< HEAD
            v[j] = storedDownVectorValues[i][j];
=======
            v[j] = stored_down_vector_values[i][j];
>>>>>>> development
        }
    }
    
    // scale all the tree variables down
    for (size_t i=0; i<down_tree_variables.size(); ++i)
    {
        
        Tree& tau = down_tree_variables[i]->getValue();
        
        TopologyNode& node = tau.getRoot();
        
        // rescale the subtrees
<<<<<<< HEAD
        TreeUtilities::setAges(&tau, &node, storedDownTreeValues[i] );
=======
        TreeUtilities::setAges(&tau, &node, stored_down_tree_values[i] );
>>>>>>> development
    }
    
}


/**
 * Swap the current variable for a new one.
 *
 * \param[in]     oldN     The old variable that needs to be replaced.
 * \param[in]     newN     The new RevVariable.
 */
void UpDownScaleProposal::swapNodeInternal(DagNode *oldN, DagNode *newN)
{
    
    for (size_t i = 0; i < up_scalar_variables.size(); ++i)
    {
        if ( up_scalar_variables[i] == oldN )
        {
            up_scalar_variables[i] = static_cast<StochasticNode<double> *>(newN);
        }
    }
    
    for (size_t i = 0; i < up_vector_variables.size(); ++i)
    {
        if ( up_vector_variables[i] == oldN )
        {
            up_vector_variables[i] = static_cast<StochasticNode<RbVector<double> > *>(newN);
        }
    }
    
    for (size_t i = 0; i < up_tree_variables.size(); ++i)
    {
        if ( up_tree_variables[i] == oldN )
        {
            up_tree_variables[i] = static_cast<StochasticNode<Tree> *>(newN);
        }
    }
    
    for (size_t i = 0; i < down_scalar_variables.size(); ++i)
    {
        if ( down_scalar_variables[i] == oldN )
        {
            down_scalar_variables[i] = static_cast<StochasticNode<double> *>(newN);
        }
    }
    
    for (size_t i = 0; i < down_vector_variables.size(); ++i)
    {
        if ( down_vector_variables[i] == oldN )
        {
            down_vector_variables[i] = static_cast<StochasticNode<RbVector<double> > *>(newN);
        }
    }
    
    for (size_t i = 0; i < down_tree_variables.size(); ++i)
    {
        if ( down_tree_variables[i] == oldN )
        {
            down_tree_variables[i] = static_cast<StochasticNode<Tree> *>(newN);
        }
    }
    
}


/**
 * Tune the Proposal to accept the desired acceptance ratio.
 *
 * The acceptance ratio for this Proposal should be around 0.44.
 * If it is too large, then we increase the proposal size,
 * and if it is too small, then we decrease the proposal size.
 */
void UpDownScaleProposal::tune( double rate )
{
    
    if ( rate > 0.44 )
    {
        lambda *= (1.0 + ((rate-0.44)/0.56) );
    }
    else
    {
        lambda /= (2.0 - rate/0.44 );
    }
    
}

