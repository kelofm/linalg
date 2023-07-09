#ifndef CIE_LINALG_EIGEN_MATRIX_IMPL_HPP
#define CIE_LINALG_EIGEN_MATRIX_IMPL_HPP

// --- Linalg Includes ---
#include "packages/matrix/inc/EigenMatrix.hpp"

// --- Utility Includes ---
#include "packages/macros/inc/checks.hpp"


namespace cie::linalg {


template <class MatrixType>
EigenMatrix<MatrixType>::EigenMatrix( const EigenMatrix<MatrixType>& r_rhs )
    : _wrapped( r_rhs._wrapped )
{
}


template <class MatrixType>
EigenMatrix<MatrixType>::EigenMatrix( EigenMatrix<MatrixType>&& r_rhs )
    : _wrapped( std::move(r_rhs._wrapped) )
{
}


template <class MatrixType>
EigenMatrix<MatrixType>::EigenMatrix( MatrixType&& r_wrapped )
    : _wrapped( std::move(r_wrapped) )
{
}


template <class MatrixType>
EigenMatrix<MatrixType>::EigenMatrix( const MatrixType& r_wrapped )
    : _wrapped( r_wrapped )
{
}


template <class MatrixType>
EigenMatrix<MatrixType>::EigenMatrix( const MatrixType&& r_wrapped )
    : _wrapped( r_wrapped )
{
}


template <class MatrixType>
EigenMatrix<MatrixType>::EigenMatrix( typename EigenMatrix<MatrixType>::size_type rowSize,
                                      typename EigenMatrix<MatrixType>::size_type columnSize )
requires concepts::ConstructibleFrom<MatrixType, typename EigenMatrix<MatrixType>::size_type, typename EigenMatrix<MatrixType>::size_type>
    : _wrapped( rowSize, columnSize )
{
}


template <class MatrixType>
inline EigenMatrix<MatrixType>&
EigenMatrix<MatrixType>::operator=( MatrixType&& r_wrapped )
{
    CIE_BEGIN_EXCEPTION_TRACING

    _wrapped = std::move(r_wrapped);
    return *this;

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType>
inline EigenMatrix<MatrixType>&
EigenMatrix<MatrixType>::operator=( const MatrixType& r_wrapped )
{
    CIE_BEGIN_EXCEPTION_TRACING

    _wrapped = r_wrapped;
    return *this;

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType>
inline EigenMatrix<MatrixType>&
EigenMatrix<MatrixType>::operator=( const MatrixType&& r_wrapped )
{
    CIE_BEGIN_EXCEPTION_TRACING

    _wrapped = r_wrapped;
    return *this;

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType>
inline typename EigenMatrix<MatrixType>::value_type&
EigenMatrix<MatrixType>::at( typename EigenMatrix<MatrixType>::size_type rowIndex,
                             typename EigenMatrix<MatrixType>::size_type columnIndex )
{
    CIE_OUT_OF_RANGE_CHECK( rowIndex < this->rowSize() )
    CIE_OUT_OF_RANGE_CHECK( columnIndex < this->columnSize() )

    return _wrapped( rowIndex, columnIndex );
}


template <class MatrixType>
inline typename EigenMatrix<MatrixType>::value_type
EigenMatrix<MatrixType>::at( typename EigenMatrix<MatrixType>::size_type rowIndex,
                             typename EigenMatrix<MatrixType>::size_type columnIndex ) const
{
    CIE_OUT_OF_RANGE_CHECK( rowIndex < this->rowSize() )
    CIE_OUT_OF_RANGE_CHECK( columnIndex < this->columnSize() )

    return _wrapped( rowIndex, columnIndex );
}


template <class MatrixType>
inline typename EigenMatrix<MatrixType>::value_type&
EigenMatrix<MatrixType>::operator()( typename EigenMatrix<MatrixType>::size_type rowIndex,
                                     typename EigenMatrix<MatrixType>::size_type columnIndex )
{
    return this->at( rowIndex, columnIndex );
}


template <class MatrixType>
inline typename EigenMatrix<MatrixType>::value_type
EigenMatrix<MatrixType>::operator()( typename EigenMatrix<MatrixType>::size_type rowIndex,
                                     typename EigenMatrix<MatrixType>::size_type columnIndex ) const
{
    return this->at( rowIndex, columnIndex );
}


template <class MatrixType>
inline void
EigenMatrix<MatrixType>::resize( typename EigenMatrix<MatrixType>::size_type rowSize,
                                 typename EigenMatrix<MatrixType>::size_type columnSize )
requires concepts::detail::HasResize<MatrixType,typename EigenMatrix<MatrixType>::size_type,typename EigenMatrix<MatrixType>::size_type>
{
    CIE_BEGIN_EXCEPTION_TRACING

    _wrapped.resize( rowSize, columnSize );

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType>
inline typename EigenMatrix<MatrixType>::size_type
EigenMatrix<MatrixType>::rowSize() const
{
    return _wrapped.rows();
}


template <class MatrixType>
inline typename EigenMatrix<MatrixType>::size_type
EigenMatrix<MatrixType>::columnSize() const
{
    return _wrapped.cols();
}


template <class MatrixType>
inline MatrixType&
EigenMatrix<MatrixType>::wrapped()
{
    return _wrapped;
}


template <class MatrixType>
inline const MatrixType&
EigenMatrix<MatrixType>::wrapped() const
{
    return _wrapped;
}


template <class MatrixType>
inline
EigenMatrix<MatrixType>::operator MatrixType&()
{
    return this->wrapped();
}


template <class MatrixType>
inline
EigenMatrix<MatrixType>::operator const MatrixType&() const
{
    return this->wrapped();
}


template <class MatrixType>
inline std::ostream&
operator<<(std::ostream& r_stream, const EigenMatrix<MatrixType>& r_matrix)
{
    CIE_BEGIN_EXCEPTION_TRACING

    return r_stream << r_matrix.wrapped();

    CIE_END_EXCEPTION_TRACING
}


template <class MatrixType>
EigenMatrix<MatrixType>
EigenMatrix<MatrixType>::makeZeroMatrix()
{
    return EigenMatrix<MatrixType>(MatrixType::Zero());
}


template <class MatrixType>
EigenMatrix<MatrixType>
EigenMatrix<MatrixType>::makeIdentityMatrix()
{
    return EigenMatrix<MatrixType>(MatrixType::Identity());
}


} // namespace cie::linalg


#endif