#include "Asio_common/detail/Message.h"

MessageSource::Fake::Fake(Messenger::Fake& _messenger) :
    messenger(_messenger)
{}

asio::awaitable<void> MessageSource::Fake::send(std::string_view message)
{
    std::string buf(message);
    co_await messenger.send(buf);
}

DefaultMessageSource::DefaultMessageSource(Messenger& _messenger) :
    messenger(_messenger)
{}

asio::awaitable<void> DefaultMessageSource::send(std::string_view message)
{
    std::string buf = std::string(message) + "\r\n\r\n";
    co_await messenger.send(buf);
}

MessageTarget::Fake::Fake(Messenger::Fake& _messenger) :
    messenger(_messenger)
{}

asio::awaitable<void> MessageTarget::Fake::receive(std::string& buf)
{
    size_t n;
    co_await messenger.receive(buf, n);
}

DefaultMessageTarget::DefaultMessageTarget(Messenger& _messenger, EndPointString& endpoint) :
    messenger(_messenger),
    printer(endpoint)
{}

asio::awaitable<void> DefaultMessageTarget::receive(std::string& buf)
{
    size_t n;
    co_await messenger.receive(buf, n);
    printer.printWithBuf(n, buf);
}
