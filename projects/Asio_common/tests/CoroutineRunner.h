#pragma once

#include "asio.hpp"

void runCoroutine(asio::awaitable<void> coroutine);
