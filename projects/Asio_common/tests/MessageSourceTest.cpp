#include "test.h"

#include <string_view>

#include "Asio_common/detail/Message.h"
#include "Asio_common/detail/DetachedIOContext.h"
#include "boost/ut.hpp"

using namespace boost::ut;

void MessageSourceTest()
{
    test("send") = []
    {
        Messenger::Fake messenger;
        DefaultMessageSource sender(messenger);

        SingleDetachedIOContext ioContext;
        ioContext.run([&sender]() { return sender.send("test"); });

        std::string_view transferred = messenger.read();
        expect(transferred.compare("test" "\r\n\r\n") == 0);
    };
}
