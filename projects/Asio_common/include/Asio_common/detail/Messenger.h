#pragma once

#include "asio.hpp"

struct Messenger
{
    virtual asio::awaitable<void> send(std::string& buf) = 0;
    virtual asio::awaitable<void> receive(std::string& buf, std::size_t& n) = 0;

    struct Fake;
};

struct Messenger::Fake final :
    public Messenger
{
    asio::awaitable<void> send(std::string& buf) override;
    asio::awaitable<void> receive(std::string& buf, std::size_t& n) override;

    void write(std::string_view value);
    std::string_view read();

private:
    std::string transferred;
};

struct DefaultMessenger final :
    public Messenger
{
    DefaultMessenger(asio::ip::tcp::socket& _socket);

    asio::awaitable<void> send(std::string& buf) override;
    asio::awaitable<void> receive(std::string& buf, std::size_t& n) override;

private:
    asio::ip::tcp::socket& socket;
};
