#include "test.h"

#include <string_view>

#include "Asio_common/detail/Message.h"
#include "boost/ut.hpp"

#include "CoroutineRunner.h"

using namespace boost::ut;

void MessageTargetTest()
{
    test("recv") = []
    {
        Messenger::Fake messenger;
        EndPointString::Fake endpoint;
        DefaultMessageTarget receiver(messenger, endpoint);
        messenger.write("test");

        std::string transferred;
        runCoroutine(receiver.receive(transferred));

        expect(transferred.compare("test") == 0);
    };
}
