#include "test.h"

#include <string_view>

#include "Asio_common/detail/Echo.h"
#include "boost/ut.hpp"

#include "CoroutineRunner.h"

using namespace boost::ut;

void EchoTargetTest()
{
    test("echo target") = []
    {
        Messenger::Fake messenger;
        MessageSource::Fake sender(messenger);
        MessageTarget::Fake receiver(messenger);
        DefaultEchoTarget echo(sender, receiver);

        messenger.write("test");

        runCoroutine(echo.run());

        std::string_view transferred = messenger.read();
        expect(transferred.compare("test") == 0);
    };
}
