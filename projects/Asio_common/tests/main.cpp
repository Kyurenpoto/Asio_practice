#include "test.h"

#include "boost/ut.hpp"

using namespace boost::ut;

int main()
{
    "MessageSourceTest"_test = []
    {
        MessageSourceTest();
    };
    "MessageTargetTest"_test = []
    {
        MessageTargetTest();
    };
    "EchoSourceTest"_test = []
    {
        EchoSourceTest();
    };
    "EchoTargetTest"_test = []
    {
        EchoTargetTest();
    };

    return 0;
}
