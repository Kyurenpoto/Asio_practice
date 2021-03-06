#pragma once

#include "Asio_common/detail/EndPointString.h"

struct MessageSource
{
    virtual asio::awaitable<void> send(std::string_view message) = 0;
};

struct DefaultMessageSource final :
    public MessageSource
{
    DefaultMessageSource(asio::ip::tcp::socket& _socket);

    asio::awaitable<void> send(std::string_view message) override;

private:
    asio::ip::tcp::socket& socket;
};

struct MessageTarget
{
    virtual asio::awaitable<void> receive(std::string& buf) = 0;
};

struct DefaultMessageTarget final :
    public MessageTarget
{
    DefaultMessageTarget(asio::ip::tcp::socket& _socket);

    asio::awaitable<void> receive(std::string& buf) override;

private:
    asio::ip::tcp::socket& socket;
    DefaultEndPointString endpoint;
    DefaultEndPointString::Feature printer;
};
