#define WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
using namespace std;
int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//建立socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock) {
		printf("错误，建立socket 失败。。。\n");
	}
	else {
		printf("建立socket 成功...\n");
	}
	//连接服务区
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int ret =connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret) {
		printf("建立Connect 失败。。。\n");
	}
	else {
		printf("建立connect  成功。。 \n");
	}
	//3.接收服务器数据
	char recvBuf[256] = {};
	int n_len = recv(_sock, recvBuf, 256, 0);
	if (n_len > 0) {
		printf("接收到数据：%s\n", recvBuf);
	}
	
	//关闭套接字
	closesocket(_sock);
	WSACleanup();
	getchar();
	return 0;

}