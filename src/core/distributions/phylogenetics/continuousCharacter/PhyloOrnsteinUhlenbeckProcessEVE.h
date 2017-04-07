#ifndef PhyloOrnsteinUhlenbeckProcessEVE_H
#define PhyloOrnsteinUhlenbeckProcessEVE_H

#include "AbstractPhyloContinuousCharacterProcess.h"
#include "MatrixReal.h"

#include <vector>

namespace RevBayesCore {
    
    /**
     * @brief Homogeneous distribution of character state evolution along a tree class (PhyloCTMC).
     *
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2015-01-23, version 1.0
     */
    class PhyloOrnsteinUhlenbeckProcessEVE : public AbstractPhyloContinuousCharacterProcess {
        
    public:
        // Note, we need the size of the alignment in the constructor to correctly simulate an initial state
        PhyloOrnsteinUhlenbeckProcessEVE(const TypedDagNode<Tree> *t, size_t ns );
        virtual                                                            ~PhyloOrnsteinUhlenbeckProcessEVE(void);                                                              //!< Virtual destructor
        
        // public member functions
        // pure virtual
        virtual PhyloOrnsteinUhlenbeckProcessEVE*                           clone(void) const;                                                                      //!< Create an independent clone
        
        // non-virtual
        double                                                              computeLnProbability(void);
        void                                                                setAlpha(const TypedDagNode< double >* a);
        void                                                                setAlpha(const TypedDagNode< RbVector< double > >* a);
        void                                                                setRootState(const TypedDagNode< double >* s);
        void                                                                setSigma(const TypedDagNode< double >* s);
        void                                                                setSigma(const TypedDagNode< RbVector< double > >* s);
        void                                                                setTheta(const TypedDagNode< double >* t);
        void                                                                setTheta(const TypedDagNode< RbVector< double > >* t);
        
        
    protected:
        // virtual methods that may be overwritten, but then the derived class should call this methods
        virtual void                                                        keepSpecialization(DagNode* affecter);
        void                                                                recursivelyFlagNodeDirty(const TopologyNode& n);
        void                                                                resetValue( void );
        virtual void                                                        restoreSpecialization(DagNode *restorer);
        void                                                                simulateRecursively(const TopologyNode& node, std::vector< ContinuousTaxonData > &t);
        std::vector<double>                                                 simulateRootCharacters(size_t n);
        double                                                              sumRootLikelihood(void);
        virtual void                                                        touchSpecialization(DagNode *toucher, bool touchAll);
        
        void                                                                computeCovariance(MatrixReal &cv);
        void                                                                computeCovarianceRecursive(const TopologyNode &n, MatrixReal &cv);
        void                                                                computeExpectation(std::vector<double> &e);
        void                                                                computeExpectationRecursive(const TopologyNode &n, double me, std::vector<double> &e);
        size_t                                                              computeMrcaIndex(const TopologyNode *l, const TopologyNode *r);
//        void                                                                computeLeafExpectation(std::vector<double> &e);
        void                                                                computeVarianceRecursive(const TopologyNode &n, std::vector<double> &v);
        void                                                                expandExpectation(std::vector<double> &e);
        void                                                                expandCovariance(MatrixReal &cv);

        // Parameter management functions.
        virtual void                                                        swapParameterInternal(const DagNode *oldP, const DagNode *newP);                         //!< Swap a parameter
        
    private:
        double                                                              computeRootState(void) const;
        double                                                              computeBranchAlpha(size_t idx) const;
        double                                                              computeBranchSigma(size_t idx) const;
        double                                                              computeBranchTheta(size_t idx) const;
        void                                                                recursiveComputeRootToTipDistance( std::vector<double> &m, double v, const TopologyNode &n, size_t ni );
        std::set<size_t>                                                    recursiveComputeDistanceMatrix( MatrixReal &m, const TopologyNode &node, size_t node_index );
        
        const TypedDagNode< double >*                                       root_state;
        const TypedDagNode< double >*                                       homogeneous_alpha;
        const TypedDagNode< double >*                                       homogeneous_sigma;
        const TypedDagNode< double >*                                       homogeneous_theta;
        const TypedDagNode< RbVector< double > >*                           heterogeneous_alpha;
        const TypedDagNode< RbVector< double > >*                           heterogeneous_sigma;
        const TypedDagNode< RbVector< double > >*                           heterogeneous_theta;
        
        size_t                                                              num_tips;
        std::vector<std::vector<double> >                                   obs;
        std::vector<double>*                                                means;
//        std::vector<double>*                                                stored_means;
        MatrixReal*                                                         phylogenetic_covariance_matrix;
//        MatrixReal*                                                         stored_phylogenetic_covariance_matrix;
        MatrixReal                                                          inverse_phylogenetic_covariance_matrix;
        bool                                                                changed_covariance;
        bool                                                                needs_covariance_recomputation;
        bool                                                                needs_scale_recomputation;
        
    };
    
}


#endif
