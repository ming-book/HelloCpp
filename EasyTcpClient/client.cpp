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
	while (true) {
		char cmdBuf[128] = {};
		scanf("%s",cmdBuf);
		if (0 == strcmp(cmdBuf, "exit")) {
			break;
		}
		else {
			send(_sock, cmdBuf, strlen(cmdBuf) + 1, 0);
		}
		//3.���շ���������
		char recvBuf[128] = {};
		int n_len = recv(_sock, recvBuf, 128, 0);
		if (n_len > 0) {
			if (strcmp(recvBuf, "????") == 0) {
				printf("��֪���㷢�͵���ʲô");
			}else{
			DataPackage *dp = (DataPackage *)recvBuf;
			printf("���յ����ݣ����䣺%d,������%s\n", dp->age,dp->name);
			}
		}
	}
	
	//�ر��׽���
	closesocket(_sock);
	WSACleanup();
	getchar();
	return 0;

}

