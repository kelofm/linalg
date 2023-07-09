#ifndef CIE_LINALG_VECTOR_EIGEN_ARRAY_IMPL_HPP
#define CIE_LINALG_VECTOR_EIGEN_ARRAY_IMPL_HPP

// --- Utility Includes ---
#include "packages/macros/inc/checks.hpp"
#include "packages/macros/inc/exceptions.hpp"

// --- STL Includes ---
#include <algorithm>


namespace cie::linalg {


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray()
    : EigenArray<TValue,ArraySize>::Base( _container ),
      _container()
{
    this->updateEigen();
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray(const std::initializer_list<typename EigenArray<TValue,ArraySize>::value_type>&& r_components)
    : EigenArray<TValue,ArraySize>::Base( _container )
{
    std::copy(
        r_components.begin(),
        r_components.end(),
        _container.begin()
    );
    this->updateEigen();
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray( const typename EigenArray<TValue,ArraySize>::eigen_type& r_eigenArray )
    : EigenArray<TValue,ArraySize>::Base( _container ),
      _container()
{
    std::copy(
        r_eigenArray.begin(),
        r_eigenArray.end(),
        _container.begin()
    );
    this->updateEigen();
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray( typename EigenArray<TValue,ArraySize>::container_type&& r_array )
    : EigenArray<TValue,ArraySize>::Base( _container ),
      _container( std::move(r_array) )
{
    this->updateEigen();
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray( const typename EigenArray<TValue,ArraySize>::container_type& r_array )
    : EigenArray<TValue,ArraySize>::Base( _container ),
      _container( r_array )
{
    this->updateEigen();
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray(const Eigen::Matrix<TValue,ArraySize,1>& r_eigenMatrix)
    : EigenArray<TValue,ArraySize>::Base(_container)
{
    CIE_BEGIN_EXCEPTION_TRACING

    const TValue* begin = &r_eigenMatrix(0,0);
    std::copy(begin,
              begin + ArraySize,
              _container.begin());

    CIE_END_EXCEPTION_TRACING
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray(const Eigen::Matrix<TValue,1,ArraySize>& r_eigenMatrix)
requires (ArraySize != 1)
    : EigenArray<TValue,ArraySize>::Base(_container)
{
    CIE_BEGIN_EXCEPTION_TRACING

    const TValue* begin = &r_eigenMatrix(0,0);
    std::copy(begin,
              begin + ArraySize,
              _container.begin());

    CIE_END_EXCEPTION_TRACING
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray( EigenArray<TValue,ArraySize>&& r_rhs )
    : EigenArray<TValue,ArraySize>::Base( _container ),
      _container( std::move(r_rhs._container) )
{
    this->updateEigen();
}


template <class TValue, int ArraySize>
EigenArray<TValue,ArraySize>::EigenArray( const EigenArray<TValue,ArraySize>& r_rhs )
    : EigenArray<TValue,ArraySize>::Base( _container ),
      _container( r_rhs._container )
{
    this->updateEigen();
}


template <class TValue, int ArraySize>
template <class ContainerType>
requires concepts::Container<ContainerType, TValue>
EigenArray<TValue,ArraySize>::EigenArray( const ContainerType& r_components )
    : EigenArray<TValue,ArraySize>::Base( _container ),
      _container()
{
    CIE_OUT_OF_RANGE_CHECK( r_components.size() == this->size() )
    std::copy(
        r_components.begin(),
        r_components.end(),
        this->begin()
    );
    this->updateEigen();
}


template <class TValue, int ArraySize>
inline EigenArray<TValue,ArraySize>&
EigenArray<TValue,ArraySize>::operator=( EigenArray<TValue,ArraySize>&& r_rhs )
{
    _container = std::move( r_rhs._container );
    this->updateEigen();

    return *this;
}


template <class TValue, int ArraySize>
inline EigenArray<TValue,ArraySize>&
EigenArray<TValue,ArraySize>::operator=( const EigenArray<TValue,ArraySize>& r_rhs )
{
    _container = r_rhs._container;
    this->updateEigen();

    return *this;
}


} // namespace cie::linalg


#endif