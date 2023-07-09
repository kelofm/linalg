#ifndef CIE_LINALG_MATRIX_OPERATORS_IMPL_HPP
#define CIE_LINALG_MATRIX_OPERATORS_IMPL_HPP

// --- Utility Includes ---
#include "packages/macros/inc/exceptions.hpp"
#include "packages/macros/inc/checks.hpp"


namespace cie::linalg {


// -----------------------------------------------------------
// IN-PLACE OPERATORS
// -----------------------------------------------------------

template <class MatrixType>
void
operator+=( EigenMatrix<MatrixType>& r_lhs, const EigenMatrix<MatrixType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    r_lhs.wrapped() += r_rhs.wrapped();

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType>
void
operator-=( EigenMatrix<MatrixType>& r_lhs, const EigenMatrix<MatrixType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    r_lhs.wrapped() -= r_rhs.wrapped();

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType, class ValueType>
requires std::is_same_v<ValueType, typename MatrixType::value_type>
void
operator+=( EigenMatrix<MatrixType>& r_lhs, ValueType rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    r_lhs.wrapped() += rhs;

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType, class ValueType>
requires std::is_same_v<ValueType, typename MatrixType::value_type>
void
operator-=( EigenMatrix<MatrixType>& r_lhs, ValueType rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    r_lhs.wrapped() -= rhs;

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType, class ValueType>
requires std::is_same_v<ValueType, typename MatrixType::value_type>
void
operator*=( EigenMatrix<MatrixType>& r_lhs, ValueType rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    r_lhs.wrapped() *= rhs;

    CIE_END_EXCEPTION_TRACING
}


// -----------------------------------------------------------
// MATRIX-VECTOR OPERATORS
// -----------------------------------------------------------

template <concepts::DynamicMatrix MatrixType, class ValueType>
EigenVector<ValueType>
operator*( const EigenMatrix<MatrixType>& r_lhs, const EigenVector<ValueType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    CIE_OUT_OF_RANGE_CHECK( r_lhs.columnSize() == Size(r_rhs.size()) )

    EigenVector<ValueType> output( r_lhs.rowSize() );
    output.wrapped() = r_lhs.wrapped() * r_rhs.wrapped();

    return output;

    CIE_END_EXCEPTION_TRACING
}


template <concepts::DynamicMatrix MatrixType, class ValueType>
EigenVector<ValueType>
operator*( const EigenVector<ValueType>& r_lhs, const EigenMatrix<MatrixType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    CIE_OUT_OF_RANGE_CHECK( Size(r_lhs.size()) == r_rhs.rowSize() )

    EigenVector<ValueType> output( r_rhs.columnSize() );
    output.wrapped() = (r_lhs.wrapped().transpose() * r_rhs.wrapped()).transpose();

    return output;

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType, class ValueType, int ArraySize>
requires (EigenMatrix<MatrixType>::ColumnTag == ArraySize)
EigenArray<ValueType, EigenMatrix<MatrixType>::RowTag>
operator*( const EigenMatrix<MatrixType>& r_lhs,
           const EigenArray<ValueType,ArraySize>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    EigenArray<ValueType, EigenMatrix<MatrixType>::RowTag> output;
    output.wrapped() = r_lhs.wrapped() * r_rhs.wrapped();

    return output;

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType, class ValueType, int ArraySize>
requires (EigenMatrix<MatrixType>::RowTag == ArraySize)
EigenArray<ValueType, EigenMatrix<MatrixType>::ColumnTag>
operator*( const EigenArray<ValueType,ArraySize>& r_lhs,
           const EigenMatrix<MatrixType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    EigenArray<ValueType, EigenMatrix<MatrixType>::ColumnTag> output;
    output.wrapped() = (r_lhs.wrapped().transpose() * r_rhs.wrapped()).transpose();

    return output;

    CIE_END_EXCEPTION_TRACING
}


// -----------------------------------------------------------
// MATRIX-MATRIX OPERATORS
// -----------------------------------------------------------

template <class MatrixType>
EigenMatrix<MatrixType>
operator+( const EigenMatrix<MatrixType>& r_lhs, const EigenMatrix<MatrixType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    return EigenMatrix<MatrixType>( (r_lhs.wrapped() + r_rhs.wrapped()).eval() );

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType>
EigenMatrix<MatrixType>
operator-( const EigenMatrix<MatrixType>& r_lhs, const EigenMatrix<MatrixType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    return EigenMatrix<MatrixType>( (r_lhs.wrapped() - r_rhs.wrapped()).eval() );

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType, class ValueType>
requires std::is_same_v<ValueType, typename MatrixType::value_type>
EigenMatrix<MatrixType>
operator*( ValueType lhs, const EigenMatrix<MatrixType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    return EigenMatrix<MatrixType>(
        lhs * r_rhs.wrapped()
    );

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType, class ValueType>
requires std::is_same_v<ValueType, typename MatrixType::value_type>
EigenMatrix<MatrixType>
operator*( const EigenMatrix<MatrixType>& r_lhs, ValueType rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    return EigenMatrix<MatrixType>(
        r_lhs.wrapped() * rhs
    );

    CIE_END_EXCEPTION_TRACING
}


template <class ValueType>
DynamicEigenMatrix<ValueType>
operator*( const DynamicEigenMatrix<ValueType>& r_lhs, const DynamicEigenMatrix<ValueType>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    return DynamicEigenMatrix<ValueType>(
        (r_lhs.wrapped() * r_rhs.wrapped()).eval()
    );

    CIE_END_EXCEPTION_TRACING
}


template <class ValueType, int LHSSize, int InnerSize, int RHSSize>
StaticEigenMatrix<ValueType, LHSSize, RHSSize>
operator*( const StaticEigenMatrix<ValueType, LHSSize, InnerSize>& r_lhs,
           const StaticEigenMatrix<ValueType, InnerSize, RHSSize>& r_rhs )
{
    CIE_BEGIN_EXCEPTION_TRACING

    return StaticEigenMatrix<ValueType, LHSSize, RHSSize>(
        (r_lhs.wrapped() * r_rhs.wrapped())
    );

    CIE_END_EXCEPTION_TRACING
}


} // namespace cie::linalg


#endif