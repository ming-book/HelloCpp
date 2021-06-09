#define WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
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
		else if(0 == strcmp(cmdBuf,"login")) {
			Login login = {"lyd","lydmm"};
			DataHeader dh = { sizeof(Login),CMD_LOGIN };
			//�������������������
			send(_sock, (char*)&dh, sizeof(DataHeader),0);
			send(_sock, (char*)&login, sizeof(Login), 0);
			//���շ������ķ�������
			DataHeader retHeader = {};
			LoginResult loginret = {};
			recv(_sock, (char*)&retHeader, sizeof(DataHeader), 0);
			recv(_sock, (char*)&loginret, sizeof(LoginResult), 0);
			printf("�û���%s ��¼�����LoginResult:%d\n", login.username,loginret.result);
		}
		else if (0 == strcmp(cmdBuf, "logout")) {
			Logout logout = { "lyd"};
			DataHeader dh = { sizeof(Logout),CMD_LOGOUT };
			//�������������������
			send(_sock, (char*)&dh, sizeof(DataHeader), 0);
			send(_sock, (char*)&logout, sizeof(Logout), 0);
			//���շ������ķ�������
			DataHeader retHeader = {};
			LogoutResult logoutret = {};
			recv(_sock, (char*)&retHeader, sizeof(DataHeader), 0);
			recv(_sock, (char*)&logoutret, sizeof(LogoutResult), 0);
			printf("�û���%s �˳������LoginResult:%d\n", logout.userName, logoutret.result);

		}
		else {
			printf("��֧�ֵ��������������\n");
		}
	}
	
	//�ر��׽���
	closesocket(_sock);
	WSACleanup();
	getchar();
	return 0;

}

