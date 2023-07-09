#ifndef CIE_LINALG_EIGEN_VECTOR_ADAPTOR_HPP
#define CIE_LINALG_EIGEN_VECTOR_ADAPTOR_HPP

// --- External Includes ---
#include "Eigen/Dense"

// --- Internal Includes ---
#include "packages/vector/inc/AbsEigenVector.hpp"

// --- STL Includes ---
#include <vector>


namespace cie::linalg {


/// Eigen interface for an existing vector
template <class ValueType, class ...Arguments>
using EigenVectorAdaptor = AbsEigenVector< Eigen::Map<Eigen::Matrix<ValueType, Eigen::Dynamic, 1>>,
                                           std::vector<ValueType,Arguments...> >;

/// Eigen interface for an existing const vector
template <class ValueType, class ...Arguments>
using ConstEigenVectorAdaptor = AbsEigenVector< Eigen::Map<const Eigen::Matrix<ValueType, Eigen::Dynamic, 1>>,
                                                const std::vector<ValueType,Arguments...> >;


} // namespace cie::linalg


#endif