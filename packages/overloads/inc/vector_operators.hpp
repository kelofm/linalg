#ifndef CIE_LINALG_OVERLOADS_VECTOR_OPERATORS_HPP
#define CIE_LINALG_OVERLOADS_VECTOR_OPERATORS_HPP

// --- Utility Includes ---
#include "packages/stl_extension/inc/StaticArray.hpp"

// --- LinAlg Includes ---
#include "packages/matrix/inc/concepts.hpp"
#include "packages/vector/inc/EigenArray.hpp"
#include "packages/vector/inc/EigenVector.hpp"


namespace cie::linalg {


// -----------------------------------------------------------
// IN-PLACE OPERATORS
// -----------------------------------------------------------

template <class EigenType, class BaseType, class ValueType>
requires (std::is_same_v<ValueType, typename BaseType::value_type> && concepts::NonConst<BaseType>)
void
operator*=( AbsEigenVector<EigenType,BaseType>& r_lhs, ValueType rhs );


template <class EigenType, class BaseType>
requires concepts::NonConst<BaseType>
void
operator+=( AbsEigenVector<EigenType, BaseType>& r_lhs,
            const AbsEigenVector<EigenType, BaseType>& r_rhs );


template <class EigenType, class BaseType>
requires concepts::NonConst<BaseType>
void
operator-=( AbsEigenVector<EigenType, BaseType>& r_lhs,
            const AbsEigenVector<EigenType, BaseType>& r_rhs );


// -----------------------------------------------------------
// SCALAR-VECTOR OPERATORS
// -----------------------------------------------------------

template <class EigenType, class BaseType, concepts::Numeric ValueType>
requires concepts::DynamicArray<EigenType>
inline EigenVector<ValueType>
operator*( ValueType lhs, const AbsEigenVector<EigenType,BaseType>& r_rhs );


template <class EigenType, class BaseType, concepts::Numeric ValueType>
requires concepts::DynamicArray<EigenType>
inline EigenVector<ValueType>
operator*( const AbsEigenVector<EigenType,BaseType>& r_lhs, ValueType rhs );


template <class EigenType, class BaseType, concepts::Numeric ValueType>
requires concepts::StaticArray<EigenType>
inline EigenArray<ValueType, AbsEigenVector<EigenType,BaseType>::RowTag>
operator*( ValueType lhs, const AbsEigenVector<EigenType,BaseType>& r_rhs );


template <class EigenType, class BaseType, concepts::Numeric ValueType>
requires concepts::StaticArray<EigenType>
inline EigenArray<ValueType, AbsEigenVector<EigenType,BaseType>::RowTag>
operator*( const AbsEigenVector<EigenType,BaseType>& r_lhs, ValueType rhs );


// -----------------------------------------------------------
// VECTOR-VECTOR OPERATORS
// -----------------------------------------------------------

template <class EigenType, class ValueType, int ArraySize>
EigenArray<ValueType, ArraySize>
operator+( const AbsEigenVector<EigenType, StaticArray<ValueType,ArraySize>>& r_lhs,
           const AbsEigenVector<EigenType, StaticArray<ValueType,ArraySize>>& r_rhs );


template <class EigenType, class ValueType, int ArraySize>
EigenArray<ValueType, ArraySize>
operator-( const AbsEigenVector<EigenType, StaticArray<ValueType,ArraySize>>& r_lhs,
           const AbsEigenVector<EigenType, StaticArray<ValueType,ArraySize>>& r_rhs );


template <class EigenType, class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>
operator+( const AbsEigenVector<EigenType, std::vector<ValueType,Arguments...>>& r_lhs,
           const AbsEigenVector<EigenType, std::vector<ValueType,Arguments...>>& r_rhs );


template <class EigenType, class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>
operator-( const AbsEigenVector<EigenType, std::vector<ValueType,Arguments...>>& r_lhs,
           const AbsEigenVector<EigenType, std::vector<ValueType,Arguments...>>& r_rhs );


} // namespace cie::linalg

#include "packages/overloads/impl/vector_operators_impl.hpp"

#endif