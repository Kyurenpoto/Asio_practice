#pragma once

#include "Asio_common/detail/EndPointString.h"
#include "Asio_common/detail/Messenger.h"

struct MessageSource
{
    virtual asio::awaitable<void> send(std::string_view message) = 0;

    struct Fake;
};

struct MessageSource::Fake final :
    public MessageSource
{
    Fake(Messenger::Fake& _messenger);

    asio::awaitable<void> send(std::string_view message) override;

private:
    Messenger::Fake& messenger;
};

struct DefaultMessageSource final :
    public MessageSource
{
    DefaultMessageSource(Messenger& _messenger);

    asio::awaitable<void> send(std::string_view message) override;

private:
    Messenger& messenger;
};

struct MessageTarget
{
    virtual asio::awaitable<void> receive(std::string& buf) = 0;

    struct Fake;
};

struct MessageTarget::Fake final :
    public MessageTarget
{
    Fake(Messenger::Fake& _messenger);

    asio::awaitable<void> receive(std::string& buf) override;

private:
    Messenger::Fake& messenger;
};

struct DefaultMessageTarget final :
    public MessageTarget
{
    DefaultMessageTarget(Messenger& _messenger, EndPointString& endpoint);

    asio::awaitable<void> receive(std::string& buf) override;

private:
    Messenger& messenger;
    EndPointString::Feature printer;
};
