#ifndef DispersalExtinctionRootStructureFunction_H
#define DispersalExtinctionRootStructureFunction_H

#include "RbVector.h"
#include "Simplex.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

#include <vector>

namespace RevBayesCore {
    
    class DispersalExtinctionRootStructureFunction : public TypedFunction<Simplex> {
        
    public:
        DispersalExtinctionRootStructureFunction(TypedDagNode<RbVector<double> >* rf, TypedDagNode<Simplex>* rs);
        virtual                                            ~DispersalExtinctionRootStructureFunction(void);                                                         //!< Virtual destructor
        
        // public member functions
        DispersalExtinctionRootStructureFunction*           clone(void) const;                                                                  //!< Create an independent clone
        void                                                keep(DagNode* affecter);
        void                                                restore(DagNode *restorer);
        void                                                reInitialized(void);                                                                //!< The arguments have been re-initialized
        void                                                touch(DagNode *toucher );
        void                                                update(void);
        
    protected:
        void                                                swapParameterInternal(const DagNode *oldP, const DagNode *newP);                    //!< Implementation of swaping parameters
        
    private:
        void                                                makeBits(void);
        void                                                makeIdxByRangeSize(void);
        
        // members
        const TypedDagNode<RbVector<double> >*              root_frequencies;
<<<<<<< HEAD
        const TypedDagNode<RbVector<double> >*              rangeSize;
=======
        const TypedDagNode<Simplex>*                        rangeSize;
>>>>>>> development
//        const TypedDagNode<int>*                            maxRangeSize;
        
        std::vector<std::vector<unsigned> >                 bits;
        std::map<std::vector<unsigned>, unsigned>           inverseBits;
        std::vector<std::vector<unsigned> >                 idxByRangeSize;
        size_t                                              numCharacters;
        size_t                                              num_states;
    };
    
}


#endif /* defined(__revbayes_proj__DispersalExtinctionRootStructureFunction__) */
