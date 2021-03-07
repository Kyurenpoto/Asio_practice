#include "CoroutineRunner.h"

void runCoroutine(AwaitableAction coro)
{
    asio::io_context context;
    asio::co_spawn(context, coro(), asio::detached);
    context.run();
}
