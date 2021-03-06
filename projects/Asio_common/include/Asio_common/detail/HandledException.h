#pragma once

#include <functional>

#include "asio.hpp"

using NormalAction = std::function<void()>;
using AwaitableAction = std::function<asio::awaitable<void>()>;

struct CatchedException
{
    virtual void handle(std::exception& e) const = 0;
};

struct LoggedException final :
    public CatchedException
{
    void handle(std::exception& e) const override;
};

struct HandledException final
{
    HandledException(CatchedException& _catchAction);

    void handle(NormalAction tryAction);
    asio::awaitable<void> handle(AwaitableAction tryAction);

private:
    CatchedException& catchAction;
};