#include "Asio_common/detail/Messenger.h"

#include <coroutine>

asio::awaitable<void> Messenger::Fake::send(std::string& buf)
{
    transferred = buf;

    co_return;
}

asio::awaitable<void> Messenger::Fake::receive(std::string& buf, std::size_t& n)
{
    buf = transferred;
    n = transferred.size();

    co_return;
}

void Messenger::Fake::write(std::string_view value)
{
    transferred = value;
}

std::string_view Messenger::Fake::read()
{
    return transferred;
}

DefaultMessenger::DefaultMessenger(asio::ip::tcp::socket& _socket) :
    socket(_socket)
{}

asio::awaitable<void> DefaultMessenger::send(std::string& buf)
{
    co_await asio::async_write(socket, asio::buffer(buf, buf.length()), asio::use_awaitable);
}

asio::awaitable<void> DefaultMessenger::receive(std::string& buf, std::size_t& n)
{
    asio::streambuf streambuf;
    n = co_await asio::async_read_until(socket, streambuf, "\r\n\r\n", asio::use_awaitable);

    std::istream is(&streambuf);
    is >> buf;
}
