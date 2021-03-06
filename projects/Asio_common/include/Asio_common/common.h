#pragma once

#include <memory>

struct Executable
{
    virtual void execute() = 0;
};

struct Server final :
    public Executable
{
private:
    struct Impl;

public:
    Server(int nThreads, uint_least16_t port);
    Server(uint_least16_t port);
    ~Server();

    void execute() override;

private:
    std::unique_ptr<Impl> impl;
};

struct Client final :
    public Executable
{
private:
    struct Impl;

public:
    Client(uint_least16_t port);
    ~Client();

    void execute() override;

private:
    std::unique_ptr<Impl> impl;
};
