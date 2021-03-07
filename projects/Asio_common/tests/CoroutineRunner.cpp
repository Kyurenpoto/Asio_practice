#include "CoroutineRunner.h"

void runCoroutine(asio::awaitable<void> coroutine)
{
    asio::io_context context;
    asio::co_spawn(context, std::move(coroutine), asio::detached);
    context.run();
}
