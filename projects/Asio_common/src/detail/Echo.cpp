#include "Asio_common/detail/Echo.h"

DefaultEchoSource::DefaultEchoSource(MessageSource& source, MessageTarget& target, Input& _input) :
    sender(source),
    receiver(target),
    input(_input)
{}

asio::awaitable<void> DefaultEchoSource::run()
{
    co_await sender.send(input.value());

    std::string buf;

    co_await receiver.receive(buf);
}

InfiniteEchoSource::InfiniteEchoSource(MessageSource& source, MessageTarget& target, Input& input) :
    unit(source, target, input)
{}

asio::awaitable<void> InfiniteEchoSource::run()
{
    for (;;)
    {
        co_await unit.run();
    }
}

ShortenedEchoSource::ShortenedEchoSource(asio::ip::tcp::socket& socket) :
    messenger(socket),
    endpoint(socket)
{}

asio::awaitable<void> ShortenedEchoSource::run()
{
    DefaultMessageSource source(messenger);
    DefaultMessageTarget target(messenger, endpoint);
    DefaultInput input;
    InfiniteEchoSource echo(source, target, input);

    co_await echo.run();
}

DefaultEchoTarget::DefaultEchoTarget(MessageSource& source, MessageTarget& target) :
    sender(source),
    receiver(target)
{}

asio::awaitable<void> DefaultEchoTarget::run()
{
    std::string buf;

    co_await receiver.receive(buf);

    co_await sender.send(buf);
}

InfiniteEchoTarget::InfiniteEchoTarget(MessageSource& source, MessageTarget& target) :
    unit(source, target)
{}

asio::awaitable<void> InfiniteEchoTarget::run()
{
    for (;;)
    {
        co_await unit.run();
    }
}

ShortenedEchoTarget::ShortenedEchoTarget(asio::ip::tcp::socket& socket) :
    messenger(socket),
    endpoint(socket)
{}

asio::awaitable<void> ShortenedEchoTarget::run()
{
    DefaultMessageSource sender(messenger);
    DefaultMessageTarget receiver(messenger, endpoint);
    InfiniteEchoTarget echo(sender, receiver);

    co_await echo.run();
}
