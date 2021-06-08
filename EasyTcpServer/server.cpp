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
	//send ��ͻ��˷�������
	char msgbuf[] = "Hello,i'm server";
	while (true)
	{
		_cSock = accept(sock, (sockaddr *)&clientAddr, &nAddrLen);
		if (_cSock == INVALID_SOCKET)
		{
			printf("���󣬽��յ���Ч�ͻ��˵�SOCKET...\n");
		}
		//send ��ͻ��˷�������
		printf("�¿ͻ��˼��룬IP=%s\n",inet_ntoa(clientAddr.sin_addr));
		send(_cSock, msgbuf, strlen(msgbuf) + 1, 0);
	}
	
	//�ر��׽���
	closesocket(_cSock);
	WSACleanup();
	return 0;

}