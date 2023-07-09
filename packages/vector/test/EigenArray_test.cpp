// --- Utility Includes ---
#include "packages/testing/inc/essentials.hpp"

// --- Internal Includes ---
#include "packages/vector/inc/EigenArray.hpp"


namespace cie::linalg {


CIE_TEST_CASE( "EigenArray", "[vector]" )
{
    CIE_TEST_CASE_INIT( "EigenArray" )

    EigenArray<int, 2> array, tmp;

    CIE_TEST_CHECK_NOTHROW( array[0] = 0 );
    CIE_TEST_CHECK_NOTHROW( array[1] = 1 );
    CIE_TEST_REQUIRE( array.size() == 2 );
    CIE_TEST_CHECK( array[0] == 0 );
    CIE_TEST_CHECK( array[1] == 1 );
    CIE_TEST_CHECK( array.at(0) == 0 );
    CIE_TEST_CHECK( array.at(1) == 1 );

    CIE_TEST_CHECK_NOTHROW( tmp = array );
    CIE_TEST_REQUIRE( tmp.size() == 2 );
    CIE_TEST_CHECK( tmp[0] == 0 );
    CIE_TEST_CHECK( tmp[1] == 1 );

    CIE_TEST_CHECK_NOTHROW( tmp[0] = 2 );
    CIE_TEST_CHECK_NOTHROW( tmp[1] = 3 );
    CIE_TEST_CHECK( tmp[0] == 2 );
    CIE_TEST_CHECK( tmp[1] == 3 );
    CIE_TEST_CHECK( array[0] == 0 );
    CIE_TEST_CHECK( array[1] == 1 );

    {
        const auto& eigenArray = array.wrapped();
        CIE_TEST_REQUIRE( eigenArray.size() == 2 );
        CIE_TEST_CHECK( eigenArray[0] == 0 );
        CIE_TEST_CHECK( eigenArray[1] == 1 );

        const auto& eigenTmp = tmp.wrapped();
        CIE_TEST_REQUIRE( eigenTmp.size() == 2 );
        CIE_TEST_CHECK( eigenTmp[0] == 2 );
        CIE_TEST_CHECK( eigenTmp[1] == 3 );
    }

    EigenArray<int, 2> copyConstructed(array);
    CIE_TEST_REQUIRE( copyConstructed.size() == 2 );
    CIE_TEST_CHECK( copyConstructed[0] == 0 );
    CIE_TEST_CHECK( copyConstructed[1] == 1 );

    EigenArray<int, 2> moveConstructed = EigenArray<int,2>(array);
    CIE_TEST_REQUIRE( moveConstructed.size() == 2 );
    CIE_TEST_CHECK( moveConstructed[0] == 0 );
    CIE_TEST_CHECK( moveConstructed[1] == 1 );

    int reference = 0;
    for ( auto& value : array )
    {
        CIE_TEST_CHECK( value == reference++ );
        value = 2 - value;
    }

    CIE_TEST_CHECK( array[0] == 2 );
    CIE_TEST_CHECK( array[1] == 1 );
}


} // namespace cie::linalg