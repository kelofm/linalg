#ifndef LINALG_UTILITIES_CPP
#define LINALG_UTILITIES_CPP

// --- Utility Includes ---
#include "packages/macros/inc/exceptions.hpp"

// --- Internal Includes ---
#include "packages/utilities/inc/linalgutilities.hpp"


namespace cie::linalg {


void runtime_check( bool result, const char message[] )
{
    if( !result )
        CIE_THROW( std::runtime_error, message )
}

    
} // namespace cie::linalg

#endif