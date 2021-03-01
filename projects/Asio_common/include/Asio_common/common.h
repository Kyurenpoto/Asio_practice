#pragma once

#include <memory>

struct Server
{
private:
    struct Impl;

public:
    Server(int nThreads, uint_least16_t port);
    ~Server();

    void execute();

private:
    std::unique_ptr<Impl> impl;
};

struct Client
{
private:
    struct Impl;

public:
    Client(uint_least16_t port);
    ~Client();

    void execute();

private:
    std::unique_ptr<Impl> impl;
};
