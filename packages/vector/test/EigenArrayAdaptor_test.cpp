// --- Utility Includes ---
#include "packages/testing/inc/essentials.hpp"
#include "packages/stl_extension/inc/StaticArray.hpp"

// --- Internal Includes ---
#include "packages/vector/inc/EigenArrayAdaptor.hpp"


namespace cie::linalg {


CIE_TEST_CASE( "EigenArrayAdaptor", "[vector]" )
{
    CIE_TEST_CASE_INIT( "EigenArrayAdaptor" )

    using RawArray     = StaticArray<int, 2>;
    using Adaptor      = EigenArrayAdaptor<int, 2>;
    using ConstAdaptor = ConstEigenArrayAdaptor<int, 2>;

    RawArray raw;
    raw[0] = 0;
    raw[1] = 1;

    CIE_TEST_REQUIRE_NOTHROW( Adaptor(raw) );
    Adaptor adaptor( raw );

    CIE_TEST_REQUIRE( adaptor.size() == 2 );
    CIE_TEST_CHECK( adaptor[0] == 0 );
    CIE_TEST_CHECK( adaptor[1] == 1 );

    int counter = 0;
    for ( auto& r_value : adaptor )
    {
        CIE_TEST_CHECK( r_value == counter++ );
        r_value = counter;
    }

    CIE_TEST_CHECK( adaptor[0] == 1 );
    CIE_TEST_CHECK( adaptor[1] == 2 );

    {
        auto& r_wrapped = adaptor.wrapped();
        CIE_TEST_REQUIRE( r_wrapped.size() == 2 );
        CIE_TEST_CHECK( r_wrapped[0] == 1 );
        CIE_TEST_CHECK( r_wrapped[1] == 2 );

        r_wrapped[0] = 0;
        r_wrapped[1] = 1;
        CIE_TEST_CHECK( r_wrapped[0] == 0 );
        CIE_TEST_CHECK( r_wrapped[1] == 1 );
    }

    CIE_TEST_REQUIRE_NOTHROW( ConstAdaptor(raw) );
    ConstAdaptor constAdaptor( raw );

    CIE_TEST_REQUIRE( constAdaptor.size() == 2 );
    CIE_TEST_CHECK( constAdaptor[0] == 0 );
    CIE_TEST_CHECK( constAdaptor[1] == 1 );

    counter = 0;
    for ( auto& r_value : constAdaptor )
        CIE_TEST_CHECK( r_value == counter++ );
}

} // namespace cie::linalg
