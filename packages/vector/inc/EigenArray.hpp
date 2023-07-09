#ifndef CIE_LINALG_VECTOR_EIGEN_ARRAY_HPP
#define CIE_LINALG_VECTOR_EIGEN_ARRAY_HPP

// --- External Includes ---
#include <Eigen/Dense>

// --- Utility Includes ---
#include "packages/compile_time/packages/concepts/inc/container_concepts.hpp"
#include "packages/stl_extension/inc/StaticArray.hpp"

// --- Internal Includes ---
#include "packages/vector/inc/AbsEigenVector.hpp"

// --- STL Includes ---
#include <array>


namespace cie::linalg {


template <class TValue, int ArraySize>
class EigenArray : public AbsEigenVector<Eigen::Map<Eigen::Matrix<TValue,ArraySize,1>>,
                                         StaticArray<TValue,ArraySize>>
{
private:
    using container_type = StaticArray<TValue,ArraySize>;

    using Base = AbsEigenVector<Eigen::Map<Eigen::Matrix<TValue,ArraySize,1>>,
                                container_type>;

public:
    static const Size array_size = ArraySize;

    using typename Base::eigen_type;

    using typename Base::value_type;

    using typename Base::size_type;

public:
    EigenArray();

    EigenArray(const std::initializer_list<value_type>&& r_components);

    EigenArray(container_type&& r_array);

    EigenArray(const container_type& r_array);

    EigenArray(const eigen_type& r_eigenArray);

    EigenArray(const Eigen::Matrix<TValue,ArraySize,1>& r_eigenMatrix);

    EigenArray(const Eigen::Matrix<TValue,1,ArraySize>& r_eigenMatrix)
    requires (ArraySize != 1);

    EigenArray(EigenArray<TValue,ArraySize>&& r_rhs);

    EigenArray(const EigenArray<TValue,ArraySize>& r_rhs);

    template <class ContainerType>
    requires concepts::Container<ContainerType, TValue>
    EigenArray(const ContainerType& r_components);

    EigenArray<TValue,ArraySize>& operator=(EigenArray<TValue,ArraySize>&& r_rhs);

    EigenArray<TValue,ArraySize>& operator=(const EigenArray<TValue,ArraySize>& r_rhs);

private:
    container_type _container;
}; // class EigenArray


} // namespace cie::linalg


#include "packages/vector/impl/EigenArray_impl.hpp"

#endif