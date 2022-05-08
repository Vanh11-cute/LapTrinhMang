#include <stdio.h>
#include <WinSock2.h>
#include <string.h> 
#include <stdlib.h> 
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

#define INFO_BUFFER_SIZE 32767

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }
	char buf[256];
    char buffer[2048];
    while(1){
	
        string input;

        getline(cin, input);

        // string message = "Information by client: " + input;

        const char* output = input.c_str();

        send(client, output, strlen(output), 0);

        int valread = recv(client, buf, sizeof(buf), 0);

        if (valread <= 0)
        {
            if (valread == -1) {
                valread = WSAGetLastError();
            }
            break;
        }

        if (valread < sizeof(buf)) {
            buf[valread] = 0;
        }
    
	}
    closesocket(client);

    WSACleanup();
}
