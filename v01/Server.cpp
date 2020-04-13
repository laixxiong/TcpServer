#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    // 1. 建立一个socket
    int listen_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // 2. 绑定接受客户端连接的端口bind
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(INADDR_ANY); // htonl(INADDR_ANY);
    server_addr.sin_port = htons(4567);  // host to net unsigned short

    if (bind(listen_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        printf("错误，绑定网络端口失败...\n");
    }
    else
    {
        printf("绑定网络端口成功\n");
    }
    // 3. 监听网络端口listen
    if (listen(listen_fd, 1024) == -1)
    {
        printf("错误，监听网络端口失败...\n");
    }
    else
    {
        printf("监听网络端口成功\n");
    }
    // 4. 等待接受客户端连接accept
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    bzero(&client_addr, client_len);
    int accept_fd = 0;
    char msgBuf[] = "Hello, I'm Server.";
    while (true)
    {
        accept_fd =  accept(listen_fd, (sockaddr*)&client_addr, &client_len);
        if (accept_fd == -1)
        {
            printf("错误，接收到无效客户端SOCKET...\n");
        }
        printf("新客户端加入：IP = %s \n", inet_ntoa(client_addr.sin_addr));  // inet_addr
        // 5. 向客户端发送一条数据send
        send(accept_fd, msgBuf, strlen(msgBuf)+1, 0);

        // close(accept_fd);
    }
    // 6. 关闭socket
    close(listen_fd);
    return 0;
}