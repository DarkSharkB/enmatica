#include <enma.hpp>
#include <gtest/gtest.h>

sint32 main(sint32 argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    sint32 result = RUN_ALL_TESTS();

    system("pause");
    return result;
}