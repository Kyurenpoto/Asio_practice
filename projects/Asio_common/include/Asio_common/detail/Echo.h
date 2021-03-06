#pragma once

#include "Message.h"

struct EchoSource final
{
    EchoSource(asio::ip::tcp::socket socket);

    asio::awaitable<void> run();

private:
    DefaultMessageSource sender;
    DefaultMessageTarget receiver;
};

struct EchoTarget final
{
    EchoTarget(asio::ip::tcp::socket socket);

    asio::awaitable<void> run();

private:
    DefaultMessageSource sender;
    DefaultMessageTarget receiver;
};
