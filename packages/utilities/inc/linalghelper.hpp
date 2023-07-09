#ifndef CIE_LINALG_HELPER_HPP
#define CIE_LINALG_HELPER_HPP

// --- Utility Includes ---
#include "packages/compile_time/packages/concepts/inc/container_concepts.hpp"
#include "packages/types/inc/types.hpp"

// --- Internal Includes ---
#include "packages/types/inc/vectortypes.hpp"
#include "packages/types/inc/matrix.hpp"

// --- STL Includes ---
#include <iomanip>
#include <ostream>
#include <stdexcept>

namespace cie::linalg {
namespace linalghelper {


template<class RowFunction>
void writeRow( const RowFunction& vector, Size size, std::ostream& out, Size digits );

template<concepts::NumericContainer ContainerType>
void write( const ContainerType& vector, std::ostream& out = std::cout );

template<concepts::Numeric ValueType>
void write( const Matrix<ValueType>& matrix, std::ostream& out = std::cout );


} // namespace linalghelper
} // namespace cie::linalg

#include "packages/utilities/impl/linalghelper_impl.hpp"

#endif