#ifndef CIE_LINALG_VECTOR_EIGEN_VECTOR_HPP
#define CIE_LINALG_VECTOR_EIGEN_VECTOR_HPP

// --- External Includes ---
#include <Eigen/Dense>

// --- Utility Includes ---
#include "packages/compile_time/packages/concepts/inc/container_concepts.hpp"

// --- Internal Includes ---
#include "packages/vector/inc/AbsEigenVector.hpp"

// --- STL Includes ---
#include <vector>


namespace cie::linalg {


template <class ValueType, class ...Arguments>
class EigenVector : public AbsEigenVector< Eigen::Map<Eigen::Matrix<ValueType,Eigen::Dynamic,1>>,
                                           std::vector<ValueType,Arguments...> >
{
private:
    using container_type = std::vector<ValueType,Arguments...>;
    using base_type = AbsEigenVector< Eigen::Map<Eigen::Matrix<ValueType,Eigen::Dynamic,1>>,
                                      container_type >;

public:
    using typename base_type::eigen_type;
    using typename base_type::value_type;
    using typename base_type::size_type;

public:
    EigenVector();

    EigenVector(size_type size);

    EigenVector(const std::initializer_list<value_type>&& r_components);

    EigenVector(container_type&& r_vector);

    EigenVector(const container_type& r_vector);

    EigenVector(const eigen_type& r_eigenArray);

    EigenVector(EigenVector<ValueType,Arguments...>&& r_rhs);

    EigenVector(const EigenVector<ValueType,Arguments...>& r_rhs);

    template <class ContainerType>
    requires concepts::Container<ContainerType,ValueType>
    EigenVector(const ContainerType& r_components);

    EigenVector<ValueType,Arguments...>& operator=(EigenVector<ValueType,Arguments...>&& r_rhs);

    EigenVector<ValueType,Arguments...>& operator=(const EigenVector<ValueType,Arguments...>& r_rhs);

private:
    container_type _container;
}; // class EigenVector


} // namespace cie::linalg

#include "packages/vector/impl/EigenVector_impl.hpp"

#endif