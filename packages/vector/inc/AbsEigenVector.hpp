#ifndef CIE_LINALG_ABS_EIGEN_VECTOR_HPP
#define CIE_LINALG_ABS_EIGEN_VECTOR_HPP

// --- External Includes ---
#include <Eigen/Core>

// --- Utility Includes ---
#include "packages/types/inc/types.hpp"
#include "packages/compile_time/packages/concepts/inc/container_concepts.hpp"

// --- STL Includes ---
#include <ostream>
#include <optional>


namespace cie::linalg {


/// Nothing to do with mathematical eigenvectors
template <class TEigen, class TBase>
class AbsEigenVector
{
public:
    using eigen_type = TEigen;

    using base_type = TBase;

    using value_type = typename base_type::value_type;

    using size_type = Size;

    using iterator = typename base_type::iterator;

    using const_iterator = typename base_type::const_iterator;

    using pointer = typename base_type::pointer;

    using const_pointer = typename base_type::const_pointer;

    static const int RowTag = TEigen::RowsAtCompileTime;

    static const int ColumnTag = TEigen::ColsAtCompileTime;

public:
    AbsEigenVector(TBase& r_wrapped)
    requires concepts::ConstructibleFrom<TEigen, value_type*, size_type>;

    AbsEigenVector(TBase& r_wrapped)
    requires (!concepts::ConstructibleFrom<TEigen, value_type*, size_type>);

    AbsEigenVector(TBase& r_wrapped, size_type size)
    requires concepts::ConstructibleFrom<TEigen, value_type*, size_type>;

    AbsEigenVector(AbsEigenVector&& r_rhs) = default;

    AbsEigenVector& operator=(AbsEigenVector&& r_rhs) noexcept = default;

    virtual ~AbsEigenVector() {static_assert(concepts::Container<AbsEigenVector>);}

    value_type& at(size_type index)
    requires concepts::NonConst<TBase>;

    value_type& operator[](size_type index)
    requires concepts::NonConst<TBase>;

    iterator begin()
    requires concepts::NonConst<TBase>;

    iterator end()
    requires concepts::NonConst<TBase>;

    value_type at(size_type index) const;

    value_type operator[](size_type index) const;

    const_iterator begin() const;

    const_iterator end() const;

    size_type size() const;

    pointer data() noexcept;

    const_pointer data() const noexcept;

    eigen_type& wrapped()
    requires concepts::NonConst<TBase>;

    const eigen_type& wrapped() const;

    operator const eigen_type&() const;

    TBase& base()
    requires concepts::NonConst<TBase>;

    const TBase& base() const;

    operator const TBase&() const;

protected:
    AbsEigenVector() noexcept;

    void setBase(TBase& r_wrapped);

    void updateEigen()
    requires concepts::ConstructibleFrom<TEigen, value_type*, size_type>;

    void updateEigen()
    requires (!concepts::ConstructibleFrom<TEigen, value_type*, size_type>);

private:
    AbsEigenVector(const AbsEigenVector& r_rhs) = delete;

private:
    std::optional<base_type*> _p_base;

    eigen_type _eigenVector;
}; // class AbsEigenVector


template <class TEigen, class TBase>
std::ostream& operator<<(std::ostream& r_stream, const AbsEigenVector<TEigen,TBase>& r_vector);


} // namespace cie::linalg


namespace cie::concepts {
template <class T>
concept EigenVector
=  NumericContainer<T>
&& requires (T instance)
{
    typename T::eigen_type;
};
} // namespace cie::concepts


#include "packages/vector/impl/AbsEigenVector_impl.hpp"

#endif