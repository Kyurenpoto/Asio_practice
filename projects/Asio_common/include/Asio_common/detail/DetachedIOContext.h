#pragma once

#include "Asio_common/detail/HandledException.h"

struct DetachedIOContext final
{
    DetachedIOContext(int nThreads = 1);
    void run(AwaitableAction target);
    asio::ip::tcp::socket socket();

private:
    void spawn(AwaitableAction target);

private:
    asio::io_context ioContext;
};
