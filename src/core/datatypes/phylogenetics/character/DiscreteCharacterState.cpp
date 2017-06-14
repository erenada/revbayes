#include "DiscreteCharacterState.h"
#include "RbException.h"

<<<<<<< HEAD
=======
#include <string>
#include <vector>


>>>>>>> development
using namespace RevBayesCore;



/** Constructor */
<<<<<<< HEAD
DiscreteCharacterState::DiscreteCharacterState(size_t n) : CharacterState(),
    index_single_state( 0 ),
    num_observed_states( 0 ),
    state(n),
    weighted( false )
=======
DiscreteCharacterState::DiscreteCharacterState(size_t n) : CharacterState()
>>>>>>> development
{


}

/** Equals comparison */
bool DiscreteCharacterState::operator==(const CharacterState& x) const
{

    const DiscreteCharacterState* derivedX = dynamic_cast<const DiscreteCharacterState*>( &x );

    if (derivedX != NULL)
    {
<<<<<<< HEAD
        return derivedX->state == state;
=======
        return derivedX->getState() == getState();
>>>>>>> development
    }

    return false;
}


/** Not equals comparison */
bool DiscreteCharacterState::operator!=(const CharacterState& x) const
{

    return !operator==(x);
}


bool DiscreteCharacterState::operator<(const CharacterState &x) const
{

    const DiscreteCharacterState* derivedX = static_cast<const DiscreteCharacterState*>(&x);
    if ( derivedX != NULL )
    {
<<<<<<< HEAD
        RbBitSet myState = state;
        RbBitSet yourState = derivedX->state;
=======
        const RbBitSet& myState = getState();
        const RbBitSet& yourState = derivedX->getState();
>>>>>>> development
        return ( myState < yourState );
    }

    return false;
}


void DiscreteCharacterState::operator++( void )
{

    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot increment an ambiguous character.");
    }

<<<<<<< HEAD
    // unset the current state
    state.unset( index_single_state );

    // incremement our state index;
    ++index_single_state;

    // now set the bit of the state
    state.set(index_single_state);
=======
    size_t index = getStateIndex();
    ++index;
    
    if ( index >= getNumberOfStates() )
    {
        throw RbException("Cannot increment character state any further; we are already at the last state.");
    }
    
    // unset the current state
    setStateByIndex( index );
//
//    // incremement our state index;
//    ++index_single_state;
//
//    // now set the bit of the state
//    state.set(index_single_state);
>>>>>>> development

}


void DiscreteCharacterState::operator++( int i )
{

    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot increment an ambiguous character.");
    }
<<<<<<< HEAD

    // unset the current state
    state.unset( index_single_state );

    // incremement our state index;
    ++index_single_state;

    // now set the bit of the state
    state.set(index_single_state);
=======
    
    size_t index = getStateIndex();
    ++index;
    
    if ( index >= getNumberOfStates() )
    {
        throw RbException("Cannot increment character state any further; we are already at the last state.");
    }

    
    // unset the current state
    setStateByIndex( index );
>>>>>>> development

}

void DiscreteCharacterState::operator+=( int i )
{

    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot increment an ambiguous character.");
    }
<<<<<<< HEAD

    // unset the current state
    state.unset( index_single_state );

    // incremement our state index;
    index_single_state += i;

    // now set the bit of the state
    state.set(index_single_state);
=======
    
    size_t index = getStateIndex();
    index += i;

    if ( index >= getNumberOfStates() )
    {
        throw RbException("Cannot increment character state any further; we are already at the last state.");
    }

    
    // unset the current state
    setStateByIndex( index );

//    // unset the current state
//    state.unset( index_single_state );
//
//    // incremement our state index;
//    index_single_state += i;
//
//    // now set the bit of the state
//    state.set(index_single_state);
>>>>>>> development

}

void DiscreteCharacterState::operator--( void )
{

    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot decrement an ambiguous character.");
    }
<<<<<<< HEAD

    // unset the current state
    state.unset( index_single_state );

    // incremement our state index;
    --index_single_state;

    // now set the bit of the state
    state.set(index_single_state);
=======
    
    
    size_t index = getStateIndex();
    
    if ( index == 0 )
    {
        throw RbException("Cannot decrement character state any further; we are already at the first state.");
    }

    --index;
    
    // unset the current state
    setStateByIndex( index );
>>>>>>> development

}


void DiscreteCharacterState::operator--( int i )
{

    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot decrement an ambiguous character.");
    }
<<<<<<< HEAD

    // unset the current state
    state.unset( index_single_state );

    // incremement our state index;
    --index_single_state;

    // now set the bit of the state
    state.set(index_single_state);
=======
    
    
    size_t index = getStateIndex();
    
    if ( index == 0 )
    {
        throw RbException("Cannot decrement character state any further; we are already at the first state.");
    }
    
    --index;
    
    // unset the current state
    setStateByIndex( index );
>>>>>>> development

}

void DiscreteCharacterState::operator-=( int i )
{

    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot decrement an ambiguous character.");
    }
<<<<<<< HEAD

    // unset the current state
    state.unset( index_single_state );

    // incremement our state index;
    index_single_state -= i;

    // now set the bit of the state
    state.set(index_single_state);
=======
    
    size_t index = getStateIndex();
    
    if ( index < i )
    {
        throw RbException("Cannot decrement character state any further; we are already at the first state.");
    }
    
    index -= i;
    
    // unset the current state
    setStateByIndex( index );
>>>>>>> development

}


<<<<<<< HEAD
void DiscreteCharacterState::addState(const std::string &symbol)
{
    ++num_observed_states;

    std::string labels = getStateLabels();
    size_t pos = labels.find(symbol);

    state.set( pos );
    index_single_state = pos;
}


size_t DiscreteCharacterState::getNumberObservedStates(void) const
{
    return num_observed_states;
}


size_t DiscreteCharacterState::getNumberOfStates(void) const
{
    return state.size();
}


const RbBitSet& DiscreteCharacterState::getState(void) const
{
    return state;
}


size_t DiscreteCharacterState::getStateIndex(void) const
{
    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot get the index of an ambiguous state.");
    }

    return index_single_state;
}



=======

std::string DiscreteCharacterState::getStateDescription(void) const
{
    return getStringValue();
}


std::vector<std::string> DiscreteCharacterState::getStateDescriptions(void) const
{
    std::string state_labels = getStateLabels();
    
    std::vector<std::string> state_descriptions(state_labels.size());
    for (size_t i = 0; i < state_labels.size(); i++)
    {
        state_descriptions[i] = state_labels[i];
    }
    
    return state_descriptions;
}


>>>>>>> development
std::string DiscreteCharacterState::getStringValue(void) const
{

    if ( isMissingState() )
    {
        return "?";
    }

    if ( isGapState() )
    {
        return "-";
    }

    std::string tmp_val = "";
    std::string labels = getStateLabels();
    size_t size = labels.size();
    for (size_t i = 0; i < size; ++i)
    {
<<<<<<< HEAD
        bool isSet = state.isSet( i );
        if (isSet)
=======
        bool is_set = isStateSet( i );
        if ( is_set == true )
>>>>>>> development
        {
            tmp_val += labels[i];
        }
    }

    std::string val = "";
    if ( tmp_val.size() > 1 )
    {
        val = "(" + tmp_val.substr(0,1);
        for ( size_t i = 1; i<tmp_val.size(); ++i )
        {
            val += " " + tmp_val.substr(i,1);
        }
        val += ")";
    }
    else
    {
        val = tmp_val;
    }

    return val;
}


bool DiscreteCharacterState::isAmbiguous( void ) const
{

    return isMissingState() || isGapState() || ( getNumberObservedStates() > 1 );
}


<<<<<<< HEAD
bool DiscreteCharacterState::isStateSet(size_t index) const
{
    return state.isSet(index);
}


void DiscreteCharacterState::setToFirstState(void)
{
    num_observed_states = 1;
    index_single_state = 0;
    state.clear();
    state.set( 0 );
}


void DiscreteCharacterState::setStateByIndex(size_t index)
{

    num_observed_states = 1;
    index_single_state = index;
    state.clear();
    state.set( index );
}



void DiscreteCharacterState::setState(const std::string &s)
{

    std::string labels = getStateLabels();

    num_observed_states = 0;
    state.clear();

    for (size_t i = 0; i < s.size(); i++)
    {
        ++num_observed_states;

        size_t pos = labels.find(s[i]);
        state.set(pos);
        index_single_state = pos;
    }

}


const std::vector<double> DiscreteCharacterState::getWeights() const {
    
    // @Bastien: Change this function as needed!beta
    return std::vector<double>(num_observed_states, 1.0);
}



bool DiscreteCharacterState::isWeighted() const {

  return weighted;

}


void DiscreteCharacterState::setWeighted(bool wd) {

  weighted = wd;
  return ;

}
=======
size_t DiscreteCharacterState::getStateIndex(void) const
{
    if ( isAmbiguous() == true )
    {
        throw RbException("Cannot get the index of an ambiguous state.");
    }
    
    RbBitSet bs = getState();
    
    return bs.getFirstSetBit();
}


bool DiscreteCharacterState::isStateSet(size_t index) const
{
    RbBitSet bs = getState();
    
    return bs.isSet(index);
}


size_t DiscreteCharacterState::getNumberObservedStates(void) const
{
    RbBitSet bs = getState();
    return bs.getNumberSetBits();
}


size_t DiscreteCharacterState::getNumberOfStates(void) const
{
    RbBitSet bs = getState();
    return bs.size();
}



const std::vector<double> DiscreteCharacterState::getWeights() const {
    
    // @Bastien: Change this function as needed!beta
    return std::vector<double>(getNumberObservedStates(), 1.0);
}
//
//
//
//bool DiscreteCharacterState::isWeighted() const {
//
//  return weighted;
//
//}
//
//
//void DiscreteCharacterState::setWeighted(bool wd) {
//
//  weighted = wd;
//  return ;
//
//}
>>>>>>> development
