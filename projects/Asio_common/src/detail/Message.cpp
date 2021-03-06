#include "Asio_common/detail/Message.h"

DefaultMessageSource::DefaultMessageSource(asio::ip::tcp::socket& _socket) :
    socket(_socket)
{}

asio::awaitable<void> DefaultMessageSource::send(std::string_view message)
{
    std::string buf = std::string(message) + "\n";

    co_await asio::async_write(socket, asio::buffer(buf, buf.length()), asio::use_awaitable);
}

DefaultMessageTarget::DefaultMessageTarget(asio::ip::tcp::socket& _socket) :
    socket(_socket),
    endpoint(socket),
    printer(endpoint)
{}

asio::awaitable<void> DefaultMessageTarget::receive(std::string& buf)
{
    asio::streambuf streambuf;
    size_t n = co_await asio::async_read_until(socket, streambuf, "\n", asio::use_awaitable);

    std::istream is(&streambuf);
    is >> buf;

    printer.printWithBuf(n, buf);
}
