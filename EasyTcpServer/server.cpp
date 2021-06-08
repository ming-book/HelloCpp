#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#include <iostream>
using namespace std;
int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//建立一个socket
	SOCKET sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//绑定一个网络端口
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;  //IPV4地址
	_sin.sin_port = htons(4567);//主机的数据转成网络字节序
	//_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&_sin, sizeof(sockaddr_in))) {
		printf("ERROR,绑定用于接收客户端连接的网络端口失败\n");
	}
	else {
		printf("绑定网络端口成功。。。\n");
	}
	//3.listen 监听网络端口
	if (SOCKET_ERROR == listen(sock, 5)) {
		printf("监听网络端口失败");

	}
	else {
		printf("监听网络端口成功");
	}
	//accept 等待接收客户端的连接
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	//send 向客户端发送数据
	char msgbuf[] = "Hello,i'm server";
	while (true)
	{
		_cSock = accept(sock, (sockaddr *)&clientAddr, &nAddrLen);
		if (_cSock == INVALID_SOCKET)
		{
			printf("错误，接收到无效客户端的SOCKET...\n");
		}
		//send 向客户端发送数据
		printf("新客户端加入，IP=%s\n",inet_ntoa(clientAddr.sin_addr));
		send(_cSock, msgbuf, strlen(msgbuf) + 1, 0);
	}
	
	//关闭套接字
	closesocket(_cSock);
	WSACleanup();
	return 0;

}
