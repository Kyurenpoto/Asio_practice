#include "test.h"

#include <string_view>

#include "Asio_common/detail/Echo.h"
#include "Asio_common/detail/DetachedIOContext.h"
#include "boost/ut.hpp"

using namespace boost::ut;

void EchoSourceTest()
{
    test("echo source") = []
    {
        Messenger::Fake messenger;
        MessageSource::Fake sender(messenger);
        MessageTarget::Fake receiver(messenger);
        Input::Fake input;
        DefaultEchoSource echo(sender, receiver, input);

        SingleDetachedIOContext ioContext;
        ioContext.run([&echo]() { return echo.run(); });

        std::string_view transferred = messenger.read();
        expect(transferred.compare("test") == 0);
    };
}
