#include "Asio_common/common.h"

int main()
{
    Server server(1, 55555);
    server.execute();

    return 0;
}
