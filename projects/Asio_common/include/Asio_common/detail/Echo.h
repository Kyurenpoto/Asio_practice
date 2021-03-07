#pragma once

#include "Message.h"
#include "Input.h"

struct EchoSource
{
    virtual asio::awaitable<void> run() = 0;
};

struct DefaultEchoSource final :
    public EchoSource
{
    DefaultEchoSource(MessageSource& source, MessageTarget& target, Input& _input);

    asio::awaitable<void> run() override;

private:
    MessageSource& sender;
    MessageTarget& receiver;
    Input& input;
};

struct InfiniteEchoSource final :
    public EchoSource
{
    InfiniteEchoSource(MessageSource& source, MessageTarget& target, Input& input);

    asio::awaitable<void> run() override;

private:
    DefaultEchoSource unit;
};

struct ShortenedEchoSource final :
    public EchoSource
{
    ShortenedEchoSource(asio::ip::tcp::socket& socket);

    asio::awaitable<void> run() override;

private:
    DefaultMessenger messenger;
    DefaultEndPointString endpoint;
};

struct EchoTarget
{
    virtual asio::awaitable<void> run() = 0;
};

struct DefaultEchoTarget final :
    public EchoTarget
{
    DefaultEchoTarget(MessageSource& source, MessageTarget& target);

    asio::awaitable<void> run() override;

private:
    MessageSource& sender;
    MessageTarget& receiver;
};

struct InfiniteEchoTarget final :
    public EchoTarget
{
    InfiniteEchoTarget(MessageSource& source, MessageTarget& target);

    asio::awaitable<void> run() override;

private:
    DefaultEchoTarget unit;
};

struct ShortenedEchoTarget final :
    public EchoSource
{
    ShortenedEchoTarget(asio::ip::tcp::socket& socket);

    asio::awaitable<void> run() override;

private:
    DefaultMessenger messenger;
    DefaultEndPointString endpoint;
};
