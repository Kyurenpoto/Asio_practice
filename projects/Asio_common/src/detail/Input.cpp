#include "Asio_common/detail/Input.h"

#include <iostream>

#include "spdlog/spdlog.h"

struct BufSize
{
private:
    static constexpr std::size_t MAX_SIZE = 1024 - 1;
    static constexpr std::size_t MIN_SIZE = 1;

public:
    BufSize(const std::string& buf);

    bool valid() const;
    void logInfo() const;

private:
    std::size_t size;
};

BufSize::BufSize(const std::string& buf) :
    size(buf.size())
{}

bool BufSize::valid() const
{
    return size >= MIN_SIZE && size <= MAX_SIZE;
}

void BufSize::logInfo() const
{
    if (size > MAX_SIZE)
    {
        spdlog::error("Cannot send message over 1024 bytes!\n");
        spdlog::error("Requested bytes: {}\n", size);
    }

    if (size < MIN_SIZE)
        spdlog::warn("Cannot send empty message!\n");
}

std::string Input::value() const
{
    for (;;)
    {
        std::string buf;
        fmt::print("Enter message: ");
        std::cin >> buf;
        if (std::cin.eof())
            throw std::ios_base::failure("EOF");

        BufSize size(buf);
        size.logInfo();
        if (size.valid())
            return buf;
    }
}
