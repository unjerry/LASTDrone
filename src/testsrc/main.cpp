#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
int main()
{
    // mail.cock.li
    // TCP:SOCK_STREAM
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(587);
    gethostbyname("mail.cock.li");
    return 0;
}
