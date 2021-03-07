#include "Asio_common/detail/DetachedIOContext.h"

DetachedIOContext::DetachedIOContext(int nThreads) :
    ioContext(nThreads)
{}

void DetachedIOContext::run(AwaitableAction target)
{
    LoggedException logger;
    HandledException handler(logger);
    handler.handle([this, target]() { spawn(target); });
}

asio::ip::tcp::socket DetachedIOContext::socket()
{
    return asio::ip::tcp::socket(ioContext);
}

void DetachedIOContext::spawn(AwaitableAction target)
{
    asio::signal_set signals(ioContext, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) { ioContext.stop(); });

    asio::co_spawn(ioContext, target(), asio::detached);

    ioContext.run();
}

void SingleDetachedIOContext::run(AwaitableAction target)
{
    LoggedException logger;
    HandledException handler(logger);
    handler.handle([this, target]() { spawn(target); });
}

void SingleDetachedIOContext::spawn(AwaitableAction target)
{
    asio::co_spawn(ioContext, target(), asio::detached);

    ioContext.run();
}
