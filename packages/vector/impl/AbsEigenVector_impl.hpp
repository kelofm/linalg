#ifndef CIE_LINALG_ABS_EIGEN_VECTOR_IMPL_HPP
#define CIE_LINALG_ABS_EIGEN_VECTOR_IMPL_HPP

// --- Linalg Includes ---
#include "packages/vector/inc/AbsEigenVector.hpp"

// --- Utility Includes ---
#include "packages/macros/inc/exceptions.hpp"


namespace cie::linalg {


template <class EigenType, class BaseType>
AbsEigenVector<EigenType,BaseType>::AbsEigenVector( BaseType& r_base )
requires concepts::ConstructibleFrom<EigenType, typename AbsEigenVector<EigenType, BaseType>::value_type*, typename AbsEigenVector<EigenType, BaseType>::size_type>
    : _r_base( r_base ),
      _eigenVector( &r_base[0], r_base.size() )
{
}


template <class EigenType, class BaseType>
AbsEigenVector<EigenType,BaseType>::AbsEigenVector( BaseType& r_base )
requires (!concepts::ConstructibleFrom<EigenType, typename AbsEigenVector<EigenType, BaseType>::value_type*, typename AbsEigenVector<EigenType, BaseType>::size_type>)
    : _r_base( r_base ),
      _eigenVector( &r_base[0] )
{
}


template <class EigenType, class BaseType>
AbsEigenVector<EigenType, BaseType>::AbsEigenVector( BaseType& r_base, typename AbsEigenVector<EigenType, BaseType>::size_type size )
requires concepts::ConstructibleFrom<EigenType, typename AbsEigenVector<EigenType, BaseType>::value_type*, typename AbsEigenVector<EigenType, BaseType>::size_type>
    : _r_base( r_base ),
      _eigenVector( &r_base[0], size )
{
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::value_type&
AbsEigenVector<EigenType,BaseType>::operator[]( typename AbsEigenVector<EigenType,BaseType>::size_type index )
requires concepts::NonConst<BaseType>
{
    return _r_base[index];
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::value_type&
AbsEigenVector<EigenType,BaseType>::at( typename AbsEigenVector<EigenType,BaseType>::size_type index )
requires concepts::NonConst<BaseType>
{
    return this->operator[]( index );
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::iterator
AbsEigenVector<EigenType,BaseType>::begin()
requires concepts::NonConst<BaseType>
{
    return _r_base.begin();
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::iterator
AbsEigenVector<EigenType,BaseType>::end()
requires concepts::NonConst<BaseType>
{
    return _r_base.end();
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::value_type
AbsEigenVector<EigenType,BaseType>::operator[]( typename AbsEigenVector<EigenType,BaseType>::size_type index ) const
{
    return _r_base[index];
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::value_type
AbsEigenVector<EigenType,BaseType>::at( typename AbsEigenVector<EigenType,BaseType>::size_type index ) const
{
    return this->operator[]( index );
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::const_iterator
AbsEigenVector<EigenType,BaseType>::begin() const
{
    return _r_base.begin();
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::const_iterator
AbsEigenVector<EigenType,BaseType>::end() const
{
    return _r_base.end();
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::size_type
AbsEigenVector<EigenType,BaseType>::size() const
{
    return _r_base.size();
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::pointer
AbsEigenVector<EigenType,BaseType>::data() noexcept
{
    return _r_base.data();
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::const_pointer
AbsEigenVector<EigenType,BaseType>::data() const noexcept
{
    return _r_base.data();
}


template <class EigenType, class BaseType>
inline typename AbsEigenVector<EigenType,BaseType>::eigen_type&
AbsEigenVector<EigenType,BaseType>::wrapped()
requires concepts::NonConst<BaseType>
{
    return _eigenVector;
}


template <class EigenType, class BaseType>
inline const typename AbsEigenVector<EigenType,BaseType>::eigen_type&
AbsEigenVector<EigenType,BaseType>::wrapped() const
{
    return _eigenVector;
}


template <class EigenType, class BaseType>
inline
AbsEigenVector<EigenType,BaseType>::operator const typename AbsEigenVector<EigenType,BaseType>::eigen_type&() const
{
    return _eigenVector;
}


template <class EigenType, class BaseType>
inline BaseType&
AbsEigenVector<EigenType,BaseType>::base()
requires concepts::NonConst<BaseType>
{
    return _r_base;
}


template <class EigenType, class BaseType>
inline const BaseType&
AbsEigenVector<EigenType,BaseType>::base() const
{
    return _r_base;
}


template <class EigenType, class BaseType>
inline
AbsEigenVector<EigenType,BaseType>::operator const BaseType&() const
{
    return _r_base;
}


template <class EigenType, class BaseType>
inline void
AbsEigenVector<EigenType, BaseType>::updateEigen()
requires concepts::ConstructibleFrom<EigenType, typename AbsEigenVector<EigenType, BaseType>::value_type*, typename AbsEigenVector<EigenType, BaseType>::size_type>
{
    // Placement new => no allocation involved
    new (&_eigenVector) typename AbsEigenVector<EigenType, BaseType>::eigen_type( &_r_base[0], _r_base.size() );
}


template <class EigenType, class BaseType>
inline void
AbsEigenVector<EigenType, BaseType>::updateEigen()
requires (!concepts::ConstructibleFrom<EigenType, typename AbsEigenVector<EigenType, BaseType>::value_type*, typename AbsEigenVector<EigenType, BaseType>::size_type>)
{
    // Placement new => no allocation involved
    new (&_eigenVector) typename AbsEigenVector<EigenType, BaseType>::eigen_type( &_r_base[0] );
}



template <class EigenType, class BaseType>
std::ostream& operator<<(std::ostream& r_stream, const AbsEigenVector<EigenType,BaseType>& r_vector)
{
    return r_stream << r_vector.wrapped();
}


} // namespace cie::linalg


#endif