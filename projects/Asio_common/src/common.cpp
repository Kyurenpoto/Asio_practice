#include "Asio_common/common.h"

#include "spdlog/spdlog.h"
#include "scn/scn.h"
#include "asio.hpp"

namespace
{
    void printReceived(const std::string& endpoint, std::size_t n, std::string buf)
    {
        if (n == 0)
            fmt::print("Empty Message from {}\n", endpoint);
        else if (n >= 1024)
            fmt::print("Over sized message from {}\n", endpoint);
        else
            fmt::print("Message from {}: {}\n", endpoint, buf);
    }
}

Server::Server(int nThreads, uint_least16_t port) :
    impl(std::make_unique<Impl>(nThreads, port))
{}

Server::~Server() = default;

struct Server::Impl
{
    Impl(int nThreads, uint_least16_t _port) :
        io_context(nThreads),
        port(_port)
    {}

    void execute();

private:
    asio::awaitable<void> listener();
    asio::awaitable<void> echo(asio::ip::tcp::socket socket);

private:
    asio::io_context io_context;
    uint_least16_t port;
};

void Server::execute()
{
    impl->execute();
}

void Server::Impl::execute()
{
    try
    {
        asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto) { io_context.stop(); });

        asio::co_spawn(io_context, listener(), asio::detached);

        io_context.run();
    }
    catch (std::exception& e)
    {
        spdlog::error("Exception: {}\n", e.what());
    }
}

asio::awaitable<void> Server::Impl::listener()
{
    auto executor = co_await asio::this_coro::executor;
    asio::ip::tcp::acceptor acceptor(executor, { asio::ip::tcp::v4(), port });
    for (;;)
    {
        asio::ip::tcp::socket socket = co_await acceptor.async_accept(asio::use_awaitable);
        asio::co_spawn(executor, echo(std::move(socket)), asio::detached);
    }
}

asio::awaitable<void> Server::Impl::echo(asio::ip::tcp::socket socket)
{
    const std::string endpoint = fmt::format("({}:{})",
        socket.remote_endpoint().address().to_string(), port);

    try
    {
        std::string buf;
        for (;;)
        {
            std::size_t n = co_await socket.async_read_some(asio::buffer(buf), asio::use_awaitable);
            
            printReceived(endpoint, n, buf);
            if (n == 0 || n >= 1024)
            {
                n = 0;
                buf = "";
            }

            co_await socket.async_write_some(asio::buffer(buf, n), asio::use_awaitable);
        }
    }
    catch (std::exception& e)
    {
        spdlog::error("echo Exception: {}\n", e.what());
    }
}

Client::Client(uint_least16_t port) :
    impl(std::make_unique<Impl>(port))
{}

Client::~Client() = default;

struct Client::Impl
{
    Impl(uint_least16_t _port) :
        port(_port)
    {}

    void execute();

private:
    asio::awaitable<void> terminal();

    bool isValidBufSize(const std::size_t n);

private:
    asio::io_context io_context;
    uint_least16_t port;
};

void Client::execute()
{
    impl->execute();
}

void Client::Impl::execute()
{
    try
    {
        asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto) { io_context.stop(); });

        asio::co_spawn(io_context, terminal(), asio::detached);

        io_context.run();
    }
    catch (std::exception& e)
    {
        spdlog::error("Exception: {}\n", e.what());
    }
}

asio::awaitable<void> Client::Impl::terminal()
{
    try
    {
        asio::ip::tcp::endpoint server_addr(asio::ip::make_address("127.0.0.1"), port);
        asio::ip::tcp::socket socket(io_context);
        asio::connect(socket, &server_addr);

        const std::string endpoint = fmt::format("({}:{})",
            socket.remote_endpoint().address().to_string(), port);

        for (;;)
        {
            std::string buf;
            scn::prompt("Enter message: ", "{}", buf);
            if (!isValidBufSize(buf.size()))
                continue;

            co_await socket.async_write_some(asio::buffer(buf), asio::use_awaitable);

            size_t n = co_await socket.async_read_some(asio::buffer(buf), asio::use_awaitable);

            printReceived(endpoint, n, buf);
        }
    }
    catch (std::exception& e)
    {
        spdlog::error("Exception: {}\n", e.what());
    }
}

bool Client::Impl::isValidBufSize(const std::size_t n)
{
    if (n == 0)
    {
        fmt::print("Cannot send empty message!\n");

        return false;
    }
    if (n >= 1024)
    {
        fmt::print("Cannot send message over 1024 bytes!\n");
        fmt::print("Requested bytes: {}\n", n);

        return false;
    }

    return true;
}
