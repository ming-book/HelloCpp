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
	//����socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock) {
		printf("���󣬽���socket ʧ�ܡ�����\n");
	}
	else {
		printf("����socket �ɹ�...\n");
	}
	//���ӷ�����
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int ret =connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret) {
		printf("����Connect ʧ�ܡ�����\n");
	}
	else {
		printf("����connect  �ɹ����� \n");
	}
	//3.���շ���������
	char recvBuf[256] = {};
	int n_len = recv(_sock, recvBuf, 256, 0);
	if (n_len > 0) {
		printf("���յ����ݣ�%s\n", recvBuf);
	}
	
	//�ر��׽���
	closesocket(_sock);
	WSACleanup();
	getchar();
	return 0;

}