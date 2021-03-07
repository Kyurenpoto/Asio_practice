#include "Asio_common/common.h"

#include "asio.hpp"

#include "Asio_common/detail/HandledException.h"
#include "Asio_common/detail/DetachedIOContext.h"
#include "Asio_common/detail/Echo.h"

Server::Server(int nThreads, uint_least16_t port) :
    impl(std::make_unique<Impl>(nThreads, port))
{}

Server::Server(uint_least16_t port) :
    Server(1, port)
{}

Server::~Server() = default;

struct Server::Impl final :
    public Executable
{
    Impl(int nThreads, uint_least16_t _port) :
        ioContext(nThreads),
        port(_port)
    {}

    void execute() override;

private:
    asio::awaitable<void> listener();
    asio::awaitable<void> echo(asio::ip::tcp::socket socket);

private:
    DetachedIOContext ioContext;
    uint_least16_t port;
};

void Server::execute()
{
    impl->execute();
}

void Server::Impl::execute()
{
    ioContext.run([&]() { return listener(); });
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
    ShortenedEchoTarget echo(socket);

    LoggedException logger;
    HandledException handler(logger);
    co_await handler.handle(AwaitableAction([&echo]()->asio::awaitable<void> { co_await echo.run(); }));
}

Client::Client(uint_least16_t port) :
    impl(std::make_unique<Impl>(port))
{}

Client::~Client() = default;

struct Client::Impl final :
    public Executable
{
    Impl(uint_least16_t _port) :
        port(_port)
    {}

    void execute() override;

private:
    asio::awaitable<void> echo();
    asio::ip::tcp::socket config();

private:
    DetachedIOContext ioContext;
    uint_least16_t port;
};

void Client::execute()
{
    impl->execute();
}

void Client::Impl::execute()
{
    ioContext.run([&]() { return echo(); });
}

asio::awaitable<void> Client::Impl::echo()
{
    asio::ip::tcp::socket socket(config());
    ShortenedEchoSource echo(socket);

    LoggedException logger;
    HandledException handler(logger);
    co_await handler.handle(AwaitableAction([&echo]()->asio::awaitable<void> { co_await echo.run(); }));
}

asio::ip::tcp::socket Client::Impl::config()
{
    asio::ip::tcp::endpoint server_addr(asio::ip::make_address("127.0.0.1"), port);
    asio::ip::tcp::socket socket = ioContext.socket();
    asio::connect(socket, &server_addr);

    return socket;
}
