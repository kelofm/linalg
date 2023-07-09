#ifndef CIE_LINALG_VECTOR_EIGEN_VECTOR_IMPL_HPP
#define CIE_LINALG_VECTOR_EIGEN_VECTOR_IMPL_HPP

// --- Utility Includes ---
#include "packages/macros/inc/checks.hpp"

// --- STL Includes ---
#include <algorithm>


namespace cie::linalg {


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector()
    : EigenVector<ValueType,Arguments...>::base_type( _container, 0 ),
      _container()
{
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector( const std::initializer_list<typename EigenVector<ValueType,Arguments...>::value_type>&& r_components )
    : EigenVector<ValueType,Arguments...>::base_type( _container, r_components.size() ),
      _container( r_components )
{
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector( const EigenVector<ValueType,Arguments...>::eigen_type& r_eigenArray )
    : EigenVector<ValueType,Arguments...>::base_type( _container, r_eigenArray.size() ),
      _container( r_eigenArray.size() )
{
    std::copy(
        r_eigenArray.begin(),
        r_eigenArray.end(),
        _container.begin()
    );
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector( typename EigenVector<ValueType,Arguments...>::container_type&& r_vector )
    : EigenVector<ValueType,Arguments...>::base_type( _container, r_vector.size() ),
      _container( std::move(r_vector) )
{
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector( const typename EigenVector<ValueType,Arguments...>::container_type& r_vector )
    : EigenVector<ValueType,Arguments...>::base_type( _container, r_vector.size() ),
      _container( r_vector )
{
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector( EigenVector<ValueType,Arguments...>&& r_rhs )
    : EigenVector<ValueType,Arguments...>::base_type( _container, r_rhs.size() ),
      _container( std::move(r_rhs._container) )
{
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector( const EigenVector<ValueType,Arguments...>& r_rhs )
    : EigenVector<ValueType,Arguments...>::base_type( _container, r_rhs.size() ),
      _container( r_rhs._container )
{
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
EigenVector<ValueType,Arguments...>::EigenVector( typename EigenVector<ValueType,Arguments...>::size_type size )
    : EigenVector<ValueType,Arguments...>::base_type( _container, size ),
      _container( size )
{
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
template <class ContainerType>
requires concepts::Container<ContainerType, ValueType>
EigenVector<ValueType,Arguments...>::EigenVector( const ContainerType& r_components )
    : EigenVector<ValueType,Arguments...>::base_type( _container, r_components.size() ),
      _container( r_components.size() )
{
    std::copy(
        r_components.begin(),
        r_components.end(),
        this->begin()
    );
    this->updateEigen();
}


template <class ValueType, class ...Arguments>
inline EigenVector<ValueType,Arguments...>&
EigenVector<ValueType,Arguments...>::operator=( EigenVector<ValueType,Arguments...>&& r_rhs )
{
    CIE_CHECK(
        r_rhs.size() == this->size(),
        "lhs size (" + std::to_string(this->size()) + ") != rhs size (" + std::to_string(r_rhs.size()) + ")"
    )

    _container = std::move( r_rhs._container );
    this->updateEigen();

    return *this;
}


template <class ValueType, class ...Arguments>
inline EigenVector<ValueType,Arguments...>&
EigenVector<ValueType,Arguments...>::operator=( const EigenVector<ValueType,Arguments...>& r_rhs )
{
    CIE_CHECK(
        r_rhs.size() == this->size(),
        "lhs size (" + std::to_string(this->size()) + ") != rhs size (" + std::to_string(r_rhs.size()) + ")"
    )

    _container = r_rhs._container;
    this->updateEigen();

    return *this;
}


} // namespace cie::linalg


#endif