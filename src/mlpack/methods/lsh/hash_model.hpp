//#ifndef __HASH_MODEL_HPP
//#define __HASH_MODEL_HPP

#ifndef __MLPACK_METHODS_NEIGHBOR_SEARCH_HASH_MODEL_HPP
#define __MLPACK_METHODS_NEIGHBOR_SEARCH_HASH_MODEL_HPP

#include <mlpack/core.hpp>
#include <vector>
#include <string>

#include <mlpack/core/metrics/lmetric.hpp>

namespace mlpack 
{
    namespace neighbor 
    {
        class hashModel 
        {
        public:
            static const size_t minHashType;// = 1;
            static const size_t maxHashType;// = 2;

//            hashModel(const arma::mat& referenceSet,
//                      const size_t hashType,
//                      const size_t secondHashSize = 99901,
//                      const size_t bucketSize = 500,  
//                      
//                      const size_t numProj = 10,
//                      const size_t numTables = 10,
//                      const double hashWidth = 0.0,
//                                       
//                      const size_t dimensions = 1,
//                      const size_t planes = 1);
            
            hashModel();

            ~hashModel();

            void BuildHash();
            
            void setParams(const arma::mat& referenceSet,
                            const size_t hashType,
                            const size_t secondHashSize,
                            const size_t bucketSize,
                
                            const size_t numProj,
                            const size_t numTables,
                            const double hashWidthIn,

                            const size_t dimensions,
                            const size_t planes);
            
            template<typename VecType>
            arma::rowvec hashQuery(const VecType& queryPoint, size_t numTablesToSearch) const;

            /**
             * Serialize the LSH model.
             *
             * @param ar Archive to serialize to.
             */
            template<typename Archive>
            void Serialize(Archive& ar, const unsigned int /* version */);

        private:
            void hashType2StableDistribution(size_t numRowsInTable);
            
            template<typename VecType>    
            arma::mat hashTypeHyperplaneOnePoint(const VecType& queryPoint, size_t numTablesToSearch) const;
            
            const arma::mat* referenceSet;          //! Reference dataset.            
            size_t hashType;
            size_t secondHashSize;                  //! The big prime representing the size of the second hash.
            size_t bucketSize;                      //! The bucket size of the second hash.
            arma::vec secondHashWeights;            //! The weights of the second hash.                     
            arma::Mat<size_t> secondHashTable;      //! The final hash table; should be (< secondHashSize) x bucketSize.
            arma::Col<size_t> bucketContentSize;    //! The number of elements present in each hash bucket; should be secondHashSize.
            arma::Col<size_t> bucketRowInHashTable; //! For a particular hash value, points to the row in secondHashTable corresponding to this value.  Should be secondHashSize.  
            
            size_t numProj;                         //! The number of projections.           
            size_t numTables;                       //! The number of hash tables.
            double hashWidth;                       //! The hash width.
            std::vector<arma::mat> projections;     //! The std::vector containing the projection matrix of each table. should be [numProj x dims] x numTables          
            arma::mat offsets;                      //! The list of the offsets 'b' for each of the projection for each table. should be numProj x numTables   
            
            size_t numDimensions;                   //! dimensionality
            size_t numPlanes;                       //! number of planes 
            std::vector<arma::mat> planes;          //! Matrix containing the planes for the hyperplane hash                                             
        }; // class hashModel

    } // namespace neighbor
} // namespace mlpack

#include "hash_model_impl.hpp"

#endif /* HASH_MODEL_HPP */
