#ifndef CIE_LINALG_EIGEN_ARRAY_ADAPTOR_HPP
#define CIE_LINALG_EIGEN_ARRAY_ADAPTOR_HPP

// --- External Includes ---
#include "Eigen/Dense"

// --- Utility Includes ---
#include "packages/stl_extension/inc/StaticArray.hpp"

// --- Internal Includes ---
#include "packages/vector/inc/AbsEigenVector.hpp"

// --- STL Includes ---
#include <array>


namespace cie::linalg {


/// Eigen interface for an existing array
template <class ValueType, Size ArraySize>
using EigenArrayAdaptor = AbsEigenVector< Eigen::Map<Eigen::Matrix<ValueType, ArraySize, 1>>,
                                          StaticArray<ValueType, ArraySize> >;

/// Eigen interface for an existing const array
template <class ValueType, Size ArraySize>
using ConstEigenArrayAdaptor = AbsEigenVector< Eigen::Map<const Eigen::Matrix<ValueType, ArraySize, 1>>,
                                               const StaticArray<ValueType, ArraySize> >;


} // namespace cie::linalg


#endif