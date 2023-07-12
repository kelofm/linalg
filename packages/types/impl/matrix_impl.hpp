#ifndef CIE_LINALG_MATRIX_IMPL_HPP
#define CIE_LINALG_MATRIX_IMPL_HPP

// --- Linalg Includes ---
#include "packages/types/inc/matrix.hpp"

// --- Utility Includes ---
#include "packages/macros/inc/checks.hpp"
#include "packages/stl_extension/inc/StaticArray.hpp"

// --- STL Includes ---
#include <string>


namespace cie::linalg {


template <concepts::Numeric TValue>
Matrix<TValue>::Matrix( Size size1, Size size2, TValue value ) :
    size1_( size1 ),
    size2_( size2 ),
    data_( size1 * size2, value ),
    _transpose(false)
{
}


template <concepts::Numeric TValue>
Matrix<TValue>::Matrix(Size size1, Size size2) :
	Matrix(size1, size2, 0.0)
{
}


template <concepts::Numeric TValue>
Matrix<TValue>::Matrix() :
	Matrix(0, 0)
{
}


template <concepts::Numeric TValue>
Matrix<TValue>::Matrix( const std::vector<TValue>& rowMajorData, Size size1 ) :
    size1_( size1 ),
    size2_( 0 ),
    data_( rowMajorData ),
    _transpose(false)
{
    if( size1 != 0 )
        size2_ = rowMajorData.size( ) / size1;
    else
    {
        CIE_OUT_OF_RANGE_CHECK(  rowMajorData.size()==0 )
    }

    CIE_OUT_OF_RANGE_CHECK( size1_ * size2_ == rowMajorData.size( ) )
}


template <concepts::Numeric TValue>
Matrix<TValue>::Matrix( const std::vector<DoubleVector>& vectorOfRows ) :
    size1_( vectorOfRows.size( ) ),
    size2_( 0 ),
    _transpose(false)
{
    if( size1_ != 0 )
    {
        size2_ = vectorOfRows.front( ).size( );
        data_.resize( size1_ * size2_ );

        for( Size i = 0; i < size1_; ++i )
        {
            CIE_OUT_OF_RANGE_CHECK(  vectorOfRows[i].size( ) == size2_ )
            std::copy( vectorOfRows[i].begin( ), vectorOfRows[i].end( ), data_.begin( ) + ( i * size2_ ) );
        }
    }
}


template <concepts::Numeric TValue>
inline TValue& Matrix<TValue>::operator()( Size i, Size j )
{
    CIE_OUT_OF_RANGE_CHECK(i < _size1 && j < _size2)
    if (!_transpose)
        return data_[i * size2_ + j];
    else
        return data_[j*size2_ + i];
}


template <concepts::Numeric TValue>
inline TValue Matrix<TValue>::operator()( Size i, Size j ) const
{
    CIE_OUT_OF_RANGE_CHECK(i < _size1 && j < _size2)
    if (!_transpose)
        return data_[i * size2_ + j];
    else
        return data_[j*size2_ + i];
}


template <concepts::Numeric TValue>
inline TValue& Matrix<TValue>::operator[]( Size i )
{
    return data_[i];
}


template <concepts::Numeric TValue>
inline TValue Matrix<TValue>::operator[]( Size i ) const
{
    return data_[i];
}


template <concepts::Numeric TValue>
inline Size Matrix<TValue>::size1( ) const
{
    return size1_;
}


template <concepts::Numeric TValue>
inline Size Matrix<TValue>::size2( ) const
{
    return size2_;
}


template <concepts::Numeric TValue>
inline Size Matrix<TValue>::size() const
{
    return data_.size();
}


template <concepts::Numeric TValue>
inline StaticArray<Size, 2> Matrix<TValue>::sizes( ) const
{
    return { size1_, size2_ };
}


template <concepts::Numeric TValue>
inline typename Matrix<TValue>::iterator
Matrix<TValue>::begin()
{
    return this->data_.begin();
}


template <concepts::Numeric TValue>
inline typename Matrix<TValue>::const_iterator
Matrix<TValue>::begin() const
{
    return this->data_.begin();
}


template <concepts::Numeric TValue>
inline typename Matrix<TValue>::iterator
Matrix<TValue>::end()
{
    return this->data_.end();
}


template <concepts::Numeric TValue>
inline typename Matrix<TValue>::const_iterator
Matrix<TValue>::end() const
{
    return this->data_.end();
}


template <concepts::Numeric TValue>
inline void Matrix<TValue>::transpose()
{
    Size temp = size1_;
    size1_      = size2_;
    size2_      = temp;
    _transpose  = !_transpose;
}


template <concepts::Numeric TValue>
inline Size
Matrix<TValue>::rows() const
{
    return this->size1();
}


template <concepts::Numeric TValue>
inline Size
Matrix<TValue>::cols() const
{
    return this->size2();
}


} // namespace cie::linalg

#endif