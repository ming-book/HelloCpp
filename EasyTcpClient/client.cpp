#define WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
using namespace std;
struct DataPackage {
	int age;
	char name[32];

};
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
	while (true) {
		char cmdBuf[128] = {};
		scanf("%s",cmdBuf);
		if (0 == strcmp(cmdBuf, "exit")) {
			break;
		}
		else {
			send(_sock, cmdBuf, strlen(cmdBuf) + 1, 0);
		}
		//3.接收服务器数据
		char recvBuf[128] = {};
		int n_len = recv(_sock, recvBuf, 128, 0);
		if (n_len > 0) {
			if (strcmp(recvBuf, "????") == 0) {
				printf("不知道你发送的是什么");
			}else{
			DataPackage *dp = (DataPackage *)recvBuf;
			printf("接收到数据：年龄：%d,姓名：%s\n", dp->age,dp->name);
			}
		}
	}
	
	//关闭套接字
	closesocket(_sock);
	WSACleanup();
	getchar();
	return 0;

}

