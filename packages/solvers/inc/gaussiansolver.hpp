#ifndef CIE_LINALG_GAUSSIAN_SOLVER_HPP
#define CIE_LINALG_GAUSSIAN_SOLVER_HPP

// --- Utility Includes ---
#include "packages/compile_time/packages/concepts/inc/container_concepts.hpp"
#include "packages/types/inc/types.hpp"

// --- Internal Includes ---
#include "packages/types/inc/matrix.hpp"
#include "packages/utilities/inc/linalgutilities.hpp"

namespace cie::linalg {

// Solve linear system of equations
template <class ValueType, concepts::NumericContainer ContainerType>
ContainerType solve(    const Matrix<ValueType>& matrix,
                        const ContainerType& vector );

} // namespace cie::linalg

#include "packages/solvers/impl/gaussiansolver_impl.hpp"

#endif