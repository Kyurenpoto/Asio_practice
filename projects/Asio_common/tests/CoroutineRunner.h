#pragma once

#include "asio.hpp"
#include "Asio_common/detail/HandledException.h"

void runCoroutine(AwaitableAction coro);
