#pragma once

#include "asio.hpp"

struct EndPointString
{
    virtual std::string value() const = 0;

    struct Fake;
    struct Feature;
};

struct EndPointString::Fake final :
    public EndPointString
{
    std::string value() const override;
};

struct EndPointString::Feature final
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

struct DefaultEndPointString final :
    public EndPointString
{
    DefaultEndPointString(const asio::ip::tcp::socket& socket);

private:
    DefaultEndPointString(const std::string address, const uint_least64_t port);
    DefaultEndPointString(const std::string _endpoint);

public:
    std::string value() const override;

private:
    std::string endpoint;
};
