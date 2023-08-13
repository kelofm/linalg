#ifndef CIE_LINALG_EIGEN_MATRIX_HPP
#define CIE_LINALG_EIGEN_MATRIX_HPP

// --- Utility Includes ---
#include "packages/types/inc/types.hpp"
#include "packages/compile_time/packages/concepts/inc/container_concepts.hpp"

// --- STL Includes ---
#include <ostream>


namespace cie::linalg {


template <class MatrixType>
class EigenMatrix
{
public:
    using Wrapped = MatrixType;

    using value_type = typename MatrixType::value_type;

    using size_type  = Size;

    static const int RowTag    = MatrixType::RowsAtCompileTime;

    static const int ColumnTag = MatrixType::ColsAtCompileTime;

public:
    EigenMatrix() = default;

    EigenMatrix(const EigenMatrix<MatrixType>& r_rhs);

    EigenMatrix(EigenMatrix<MatrixType>&& r_rhs);

    EigenMatrix(MatrixType&& r_wrapped);

    EigenMatrix(const MatrixType& r_wrapped);

    EigenMatrix(const MatrixType&& r_wrapped);

    EigenMatrix(size_type rowSize, size_type columnSize)
    requires concepts::ConstructibleFrom<MatrixType, size_type, size_type>;

    EigenMatrix<MatrixType>& operator=(EigenMatrix<MatrixType>&& r_rhs) = default;

    EigenMatrix<MatrixType>& operator=(const EigenMatrix<MatrixType>& r_rhs) = default;

    EigenMatrix<MatrixType>& operator=(MatrixType&& r_wrapped);

    EigenMatrix<MatrixType>& operator=(const MatrixType& r_wrapped);

    EigenMatrix<MatrixType>& operator=(const MatrixType&& r_wrapped);

    value_type& at(size_type rowIndex,
                   size_type columnIndex);

    value_type at(size_type rowIndex,
                  size_type columnIndex) const;

    value_type& operator()(size_type rowIndex,
                           size_type columnIndex);

    value_type operator()(size_type rowIndex,
                          size_type columnIndex) const;

    void resize(size_type rowSize, size_type columnSize)
    requires concepts::detail::HasResize<MatrixType,size_type,size_type>;

    Size rowSize() const;

    Size columnSize() const;

    MatrixType& wrapped();

    const MatrixType& wrapped() const;

    explicit operator MatrixType& ();

    explicit operator const MatrixType& () const;

    static EigenMatrix makeZeroMatrix();

    static EigenMatrix makeIdentityMatrix();

protected:
    MatrixType _wrapped;
};


template <class MatrixType>
std::ostream& operator<<(std::ostream& r_stream, const EigenMatrix<MatrixType>& r_matrix);


} // namespace cie::linalg


namespace cie::concepts {

template <class T>
concept EigenMatrix
= requires (T instance)
{
    typename T::value_type;
    typename T::size_type;
    {T::RowTag};
    {T::ColumnTag};
    {instance.at(typename T::size_type(), typename T::size_type())};
    {instance(typename T::size_type(), typename T::size_type())};
    {instance.rowSize()};
    {instance.columnSize()};
};

} // namespace cie::concepts


#include "packages/matrix/impl/EigenMatrix_impl.hpp"

#endif
