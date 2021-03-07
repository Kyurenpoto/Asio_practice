#include "Asio_common/detail/EndPointString.h"

#include "spdlog/spdlog.h"

std::string EndPointString::Fake::value() const
{
    return "test";
}

EndPointString::Feature::Feature(EndPointString& _origin) :
    origin(_origin)
{}

void EndPointString::Feature::printWithBuf(std::size_t n, std::string_view buf)
{
    if (n < MIN_SIZE)
        spdlog::warn("Empty message from {}\n", origin.value());
    else if (n > MAX_SIZE)
        fmt::print("Over sized message from {}\n", origin.value());
    else
        fmt::print("Message from {}: {}\n", origin.value(), buf);
}

DefaultEndPointString::DefaultEndPointString(const asio::ip::tcp::socket& socket) :
    DefaultEndPointString(socket.remote_endpoint().address().to_string(), socket.remote_endpoint().port())
{}

DefaultEndPointString::DefaultEndPointString(const std::string address, const uint_least64_t port) :
    endpoint(fmt::format("({}:{})", address, port))
{}

DefaultEndPointString::DefaultEndPointString(const std::string _endpoint) :
    endpoint(_endpoint)
{}

std::string DefaultEndPointString::value() const
{
    return endpoint;
}
