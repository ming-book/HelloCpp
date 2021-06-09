#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#include <iostream>
using namespace std;
enum CMD {
	CMD_LOGIN,
	CMD_LOGOUT,
	CMD_ERROR
};
struct DataHeader {
	short dataLength;
	short cmd;
};
struct Login {
	char username[32];
	char PassWorld[32];
};
struct LoginResult {
	int result;
};
struct Logout {
	char userName[32];
};
struct LogoutResult {
	int result;
};
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
	_cSock = accept(sock, (sockaddr *)&clientAddr, &nAddrLen);
	if (_cSock == INVALID_SOCKET)
	{
		printf("错误，接收到无效客户端的SOCKET...\n");
	}
	printf("新客户端加入，c_Socket=%d,P=%s\n",(int)_cSock, inet_ntoa(clientAddr.sin_addr));

	char recvBuf[128] = {};
	while (true)
	{
		DataHeader header = {};
		//接收客户端请求的数据
		int nLen = recv(_cSock, (char*)&header, sizeof(DataHeader), 0);
		if (nLen <= 0) {
			printf("客户端已经退出，任务已经结束\n");
			break;
		}
		printf("收到命令：%d,数据的长度%d\n", header.cmd, header.dataLength);
		switch (header.cmd)
		{
		case CMD_LOGIN: {
			Login login = {};
			recv(_cSock, (char*)&login, sizeof(Login), 0);
			//忽略用户名密码正确的过程
			printf("接收到用户：%s登录.密码：%s\n", login.username, login.PassWorld);
			LoginResult ret = {1};
			send(_cSock, (char *)&header, sizeof(DataHeader),0);
			send(_cSock, (char*)&ret, sizeof(LoginResult), 0);
		}
						break;
		case CMD_LOGOUT: {
			Logout logout = {};
			recv(_cSock, (char*)&logout, sizeof(Logout), 0);
			//忽略用户名密码正确的过程
			printf("接收到用户：%s退出\n", logout.userName);
			LogoutResult ret = { 1 };
			send(_cSock, (char *)&header, sizeof(DataHeader), 0);
			send(_cSock, (char*)&ret, sizeof(LogoutResult), 0);
		
		}
						   break;
		default:
			header.cmd = CMD_ERROR;
			header.dataLength = 0;
			send(_cSock, (char*)&header, sizeof(DataHeader), 0);
			break;
		}
	
	}
	
	//关闭套接字
	closesocket(_cSock);
	getchar();
	WSACleanup();
	return 0;

}
