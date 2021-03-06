#include "Asio_common/detail/HandledException.h"

#include "spdlog/spdlog.h"

void LoggedException::handle(std::exception& e) const
{
    spdlog::error("Exception: {}\n", e.what());
}

HandledException::HandledException(CatchedException& _catchAction) :
    catchAction(_catchAction)
{}

void HandledException::handle(NormalAction tryAction)
{
    try
    {
        tryAction();
    }
    catch (std::exception& e)
    {
        catchAction.handle(e);
        
        return;
    }
}

asio::awaitable<void> HandledException::handle(AwaitableAction tryAction)
{
    try
    {
        co_await tryAction();
    }
    catch (std::exception& e)
    {
        catchAction.handle(e);

        co_return;
    }
}
