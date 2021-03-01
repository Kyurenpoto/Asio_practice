#include "Asio_common/common.h"

int main()
{
    Client client(55555);
    client.execute();

    return 0;
}
