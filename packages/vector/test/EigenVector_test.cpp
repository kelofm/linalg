// --- Utility Includes ---
#include "packages/testing/inc/essentials.hpp"

// --- Internal Includes ---
#include "packages/vector/inc/EigenVector.hpp"


namespace cie::linalg {


CIE_TEST_CASE( "EigenVector", "[vector]" )
{
    CIE_TEST_CASE_INIT( "EigenVector" )

    EigenVector<int> vector(2), tmp(2);

    CIE_TEST_CHECK_NOTHROW( vector[0] = 0 );
    CIE_TEST_CHECK_NOTHROW( vector[1] = 1 );
    CIE_TEST_REQUIRE( vector.size() == 2 );
    CIE_TEST_CHECK( vector[0] == 0 );
    CIE_TEST_CHECK( vector[1] == 1 );
    CIE_TEST_CHECK( vector.at(0) == 0 );
    CIE_TEST_CHECK( vector.at(1) == 1 );

    CIE_TEST_CHECK_NOTHROW( tmp = vector );
    CIE_TEST_REQUIRE( tmp.size() == 2 );
    CIE_TEST_CHECK( tmp[0] == 0 );
    CIE_TEST_CHECK( tmp[1] == 1 );

    CIE_TEST_CHECK_NOTHROW( tmp[0] = 2 );
    CIE_TEST_CHECK_NOTHROW( tmp[1] = 3 );
    CIE_TEST_CHECK( tmp[0] == 2 );
    CIE_TEST_CHECK( tmp[1] == 3 );
    CIE_TEST_CHECK( vector[0] == 0 );
    CIE_TEST_CHECK( vector[1] == 1 );

    {
        const auto& eigenVector = vector.wrapped();
        CIE_TEST_REQUIRE( eigenVector.size() == 2 );
        CIE_TEST_CHECK( eigenVector[0] == 0 );
        CIE_TEST_CHECK( eigenVector[1] == 1 );

        const auto& eigenTmp = tmp.wrapped();
        CIE_TEST_REQUIRE( eigenTmp.size() == 2 );
        CIE_TEST_CHECK( eigenTmp[0] == 2 );
        CIE_TEST_CHECK( eigenTmp[1] == 3 );
    }

    EigenVector<int> copyConstructed(vector);
    CIE_TEST_REQUIRE( copyConstructed.size() == 2 );
    CIE_TEST_CHECK( copyConstructed[0] == 0 );
    CIE_TEST_CHECK( copyConstructed[1] == 1 );

    EigenVector<int> moveConstructed = EigenVector<int>(vector);
    CIE_TEST_REQUIRE( moveConstructed.size() == 2 );
    CIE_TEST_CHECK( moveConstructed[0] == 0 );
    CIE_TEST_CHECK( moveConstructed[1] == 1 );

    int reference = 0;
    for ( auto& value : vector )
    {
        CIE_TEST_CHECK( value == reference++ );
        value = 2 - value;
    }

    CIE_TEST_CHECK( vector[0] == 2 );
    CIE_TEST_CHECK( vector[1] == 1 );
}


} // namespace cie::linalg
