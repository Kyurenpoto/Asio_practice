#include "test.h"

#include <string_view>

#include "Asio_common/detail/Message.h"
#include "boost/ut.hpp"

#include "CoroutineRunner.h"

using namespace boost::ut;

void MessageSourceTest()
{
    test("send") = []
    {
        Messenger::Fake messenger;
        DefaultMessageSource sender(messenger);

        runCoroutine(sender.send("test"));

        std::string_view transferred = messenger.read();
        expect(transferred.compare("test" "\r\n\r\n") == 0);
    };
}
