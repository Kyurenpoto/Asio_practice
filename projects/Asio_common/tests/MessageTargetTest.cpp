#include "test.h"

#include <string_view>

#include "Asio_common/detail/Message.h"
#include "Asio_common/detail/DetachedIOContext.h"
#include "boost/ut.hpp"

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
        SingleDetachedIOContext ioContext;
        ioContext.run([&receiver, &transferred]() { return receiver.receive(transferred); });

        expect(transferred.compare("test") == 0);
    };
}
