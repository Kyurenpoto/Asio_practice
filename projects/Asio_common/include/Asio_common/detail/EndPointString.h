#pragma once

#include "asio.hpp"

struct EndPointString
{
    virtual std::string value() const = 0;

    struct Feature final
    {
    private:
        static constexpr size_t MAX_SIZE = 1024 - 1;
        static constexpr size_t MIN_SIZE = 1;

    public:
        Feature(EndPointString& _origin);

        void printWithBuf(std::size_t n, std::string_view buf);

    private:
        EndPointString& origin;
    };
};

struct DefaultEndPointString final :
    public EndPointString
{
private:
    DefaultEndPointString(const std::string address, const uint_least64_t port);

public:
    DefaultEndPointString(const asio::ip::tcp::socket& socket);

    std::string value() const override;

private:
    std::string endpoint;
};
