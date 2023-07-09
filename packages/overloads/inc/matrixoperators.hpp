#ifndef CIE_LINALG_MATRIX_OPERATORS
#define CIE_LINALG_MATRIX_OPERATORS

// --- Utility Includes ---
#include "packages/compile_time/packages/concepts/inc/container_concepts.hpp"

// --- Internal Includes ---
#include "packages/types/inc/arraytypes.hpp"
#include "packages/types/inc/vectortypes.hpp"
#include "packages/types/inc/matrix.hpp"

namespace cie::linalg {

template <concepts::Numeric ValueType, concepts::Numeric ScalarType>
Matrix<ValueType> operator+(const Matrix<ValueType>& matrix, ScalarType scalar);

template <concepts::Numeric ValueType, concepts::Numeric ScalarType>
Matrix<ValueType> operator+(ScalarType scalar, const Matrix<ValueType>& matrix);

template <concepts::Numeric ValueType, concepts::Numeric ScalarType>
Matrix<ValueType> operator-(const Matrix<ValueType>& matrix, ScalarType scalar);

template <concepts::Numeric ValueType>
Matrix<ValueType> operator+(const Matrix<ValueType>& lhs, const Matrix<ValueType>& rhs);

template <concepts::Numeric ValueType>
Matrix<ValueType> operator-(const Matrix<ValueType>& lhs, const Matrix<ValueType>& rhs);

template <concepts::Numeric ValueType, concepts::Numeric ScalarType>
Matrix<ValueType> operator*(const Matrix<ValueType>& matrix, ScalarType scalar);

template <concepts::Numeric ValueType, concepts::Numeric ScalarType>
Matrix<ValueType> operator*(ScalarType scalar, const Matrix<ValueType>& matrix);

template <concepts::Numeric ValueType, concepts::Numeric ScalarType>
Matrix<ValueType> operator/(const Matrix<ValueType>& matrix, ScalarType scalar);

template <concepts::Numeric ValueType, concepts::NumericContainer ContainerType>
ContainerType operator*(const ContainerType& vector, const Matrix<ValueType>& matrix);

template <concepts::Numeric ValueType, concepts::NumericContainer ContainerType>
ContainerType operator*(const Matrix<ValueType>& matrix, const ContainerType& vector);

template <concepts::Numeric ValueType>
Matrix<ValueType> operator*(const Matrix<ValueType>& lhs, const Matrix<ValueType>& rhs);

} // namespace linalg

#include "packages/overloads/impl/matrixoperators_impl.hpp"

#endif