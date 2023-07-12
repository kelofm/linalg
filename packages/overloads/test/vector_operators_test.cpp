// --- Utility Includes ---
#include "packages/testing/inc/essentials.hpp"
#include "packages/stl_extension/inc/StaticArray.hpp"

// --- Internal Includes ---
#include "packages/overloads/inc/vector_operators.hpp"
#include "packages/vector/inc/EigenArrayAdaptor.hpp"
#include "packages/vector/inc/EigenArray.hpp"
#include "packages/vector/inc/EigenVectorAdaptor.hpp"
#include "packages/vector/inc/EigenVector.hpp"


namespace cie::linalg {


CIE_TEST_CASE("vector_operators", "[vector]")
{
    CIE_TEST_CASE_INIT("vector_operators")

    {
        CIE_TEST_CASE_INIT("EigenArray")

        using Raw          = StaticArray<int, 2>;
        using Wrapper      = EigenArray<int, 2>;
        using Adaptor      = EigenArrayAdaptor<int, 2>;
        using ConstAdaptor = EigenArrayAdaptor<int, 2>;

        Raw raw0, raw1;
        Adaptor adaptor0(raw0), adaptor1(raw1);
        adaptor0[0] = 0;
        adaptor0[1] = 1;
        adaptor1[0] = 2;
        adaptor1[1] = 3;

        ConstAdaptor constAdaptor0(raw0), constAdaptor1(raw1);

        Wrapper wrapper0, wrapper1;
        wrapper0[0] = 0;
        wrapper0[1] = 1;
        wrapper1[0] = 2;
        wrapper1[1] = 3;

        CIE_TEST_CHECK_NOTHROW(adaptor0 += adaptor1);
        CIE_TEST_REQUIRE(adaptor0.size() == 2);
        CIE_TEST_CHECK(adaptor0[0] == 2);
        CIE_TEST_CHECK(adaptor0[1] == 4);

        CIE_TEST_CHECK_NOTHROW(adaptor1 -= adaptor0);
        CIE_TEST_REQUIRE(adaptor1.size() == 2);
        CIE_TEST_CHECK(adaptor1[0] == 0);
        CIE_TEST_CHECK(adaptor1[1] == -1);

        CIE_TEST_CHECK_NOTHROW(adaptor0 *= -2);
        CIE_TEST_REQUIRE(adaptor0.size() == 2);
        CIE_TEST_CHECK(adaptor0[0] == -4);
        CIE_TEST_CHECK(adaptor0[1] == -8);

        {
            CIE_TEST_REQUIRE_NOTHROW(adaptor0 * 2);

            auto result = adaptor0 * 2;
            CIE_TEST_REQUIRE(result.size() == 2);
            CIE_TEST_CHECK(result[0] == -8);
            CIE_TEST_CHECK(result[1] == -16);
        }

        {
            CIE_TEST_REQUIRE_NOTHROW(adaptor0 + adaptor1);

            auto result = adaptor0 + adaptor1;
            CIE_TEST_REQUIRE(result.size() == 2);
            CIE_TEST_CHECK(result[0] == -4);
            CIE_TEST_CHECK(result[1] == -9);
        }

        {
            CIE_TEST_REQUIRE_NOTHROW(adaptor0 - adaptor1);

            auto result = adaptor0 - adaptor1;
            CIE_TEST_REQUIRE(result.size() == 2);
            CIE_TEST_CHECK(result[0] == -4);
            CIE_TEST_CHECK(result[1] == -7);
        }
    }

    {
        CIE_TEST_CASE_INIT("EigenVector")

        using Raw          = std::vector<int>;
        using Wrapper      = EigenVector<int>;
        using Adaptor      = EigenVectorAdaptor<int>;
        using ConstAdaptor = EigenVectorAdaptor<int>;

        Raw raw0(2), raw1(2);
        Adaptor adaptor0(raw0), adaptor1(raw1);
        adaptor0[0] = 0;
        adaptor0[1] = 1;
        adaptor1[0] = 2;
        adaptor1[1] = 3;

        ConstAdaptor constAdaptor0(raw0), constAdaptor1(raw1);

        Wrapper wrapper0(2), wrapper1(2);
        wrapper0[0] = 0;
        wrapper0[1] = 1;
        wrapper1[0] = 2;
        wrapper1[1] = 3;

        CIE_TEST_CHECK_NOTHROW(adaptor0 += adaptor1);
        CIE_TEST_REQUIRE(adaptor0.size() == 2);
        CIE_TEST_CHECK(adaptor0[0] == 2);
        CIE_TEST_CHECK(adaptor0[1] == 4);

        CIE_TEST_CHECK_NOTHROW(adaptor1 -= adaptor0);
        CIE_TEST_REQUIRE(adaptor1.size() == 2);
        CIE_TEST_CHECK(adaptor1[0] == 0);
        CIE_TEST_CHECK(adaptor1[1] == -1);

        CIE_TEST_CHECK_NOTHROW(adaptor0 *= -2);
        CIE_TEST_REQUIRE(adaptor0.size() == 2);
        CIE_TEST_CHECK(adaptor0[0] == -4);
        CIE_TEST_CHECK(adaptor0[1] == -8);

        {
            CIE_TEST_REQUIRE_NOTHROW(adaptor0 * 2);

            auto result = adaptor0 * 2;
            CIE_TEST_REQUIRE(result.size() == 2);
            CIE_TEST_CHECK(result[0] == -8);
            CIE_TEST_CHECK(result[1] == -16);
        }

        {
            CIE_TEST_REQUIRE_NOTHROW(adaptor0 + adaptor1);

            auto result = adaptor0 + adaptor1;
            CIE_TEST_REQUIRE(result.size() == 2);
            CIE_TEST_CHECK(result[0] == -4);
            CIE_TEST_CHECK(result[1] == -9);
        }

        {
            CIE_TEST_REQUIRE_NOTHROW(adaptor0 - adaptor1);

            auto result = adaptor0 - adaptor1;
            CIE_TEST_REQUIRE(result.size() == 2);
            CIE_TEST_CHECK(result[0] == -4);
            CIE_TEST_CHECK(result[1] == -7);
        }
    }
}


} // namespace cie::linalg