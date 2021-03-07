#pragma once

#include <string>

struct Input
{
    virtual std::string value() const = 0;

    struct Fake;
};

struct Input::Fake final :
    public Input
{
    std::string value() const override;
};

struct DefaultInput final :
    public Input
{
    std::string value() const override;
};
