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
	//����һ��socket
	SOCKET sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//��һ������˿�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;  //IPV4��ַ
	_sin.sin_port = htons(4567);//����������ת�������ֽ���
	//_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&_sin, sizeof(sockaddr_in))) {
		printf("ERROR,�����ڽ��տͻ������ӵ�����˿�ʧ��\n");
	}
	else {
		printf("������˿ڳɹ�������\n");
	}
	//3.listen ��������˿�
	if (SOCKET_ERROR == listen(sock, 5)) {
		printf("��������˿�ʧ��");

	}
	else {
		printf("��������˿ڳɹ�");
	}
	//accept �ȴ����տͻ��˵�����
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	_cSock = accept(sock, (sockaddr *)&clientAddr, &nAddrLen);
	if (_cSock == INVALID_SOCKET)
	{
		printf("���󣬽��յ���Ч�ͻ��˵�SOCKET...\n");
	}
	printf("�¿ͻ��˼��룬c_Socket=%d,P=%s\n",(int)_cSock, inet_ntoa(clientAddr.sin_addr));

	char recvBuf[128] = {};
	while (true)
	{
		DataHeader header = {};
		//���տͻ������������
		int nLen = recv(_cSock, (char*)&header, sizeof(DataHeader), 0);
		if (nLen <= 0) {
			printf("�ͻ����Ѿ��˳��������Ѿ�����\n");
			break;
		}
		printf("�յ����%d,���ݵĳ���%d\n", header.cmd, header.dataLength);
		switch (header.cmd)
		{
		case CMD_LOGIN: {
			Login login = {};
			recv(_cSock, (char*)&login, sizeof(Login), 0);
			//�����û���������ȷ�Ĺ���
			printf("���յ��û���%s��¼.���룺%s\n", login.username, login.PassWorld);
			LoginResult ret = {1};
			send(_cSock, (char *)&header, sizeof(DataHeader),0);
			send(_cSock, (char*)&ret, sizeof(LoginResult), 0);
		}
						break;
		case CMD_LOGOUT: {
			Logout logout = {};
			recv(_cSock, (char*)&logout, sizeof(Logout), 0);
			//�����û���������ȷ�Ĺ���
			printf("���յ��û���%s�˳�\n", logout.userName);
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
	
	//�ر��׽���
	closesocket(_cSock);
	getchar();
	WSACleanup();
	return 0;

}
