#include "Asio_common/detail/Echo.h"

#include "Asio_common/detail/Input.h"

EchoSource::EchoSource(asio::ip::tcp::socket& socket) :
    sender(socket),
    receiver(socket)
{}

asio::awaitable<void> EchoSource::run()
{
    Input input;
    for (;;)
    {
        co_await sender.send(input.value());

        std::string buf;

        co_await receiver.receive(buf);
    }
}

EchoTarget::EchoTarget(asio::ip::tcp::socket& socket) :
    sender(socket),
    receiver(socket)
{}

asio::awaitable<void> EchoTarget::run()
{
    for (;;)
    {
        std::string buf;

        co_await receiver.receive(buf);

        co_await sender.send(buf);
    }
}
