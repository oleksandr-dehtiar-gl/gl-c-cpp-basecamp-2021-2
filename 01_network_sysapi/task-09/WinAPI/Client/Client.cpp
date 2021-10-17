// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <winsock2.h> 
#pragma comment(lib, "WS2_32.lib")
using namespace std;

DWORD WINAPI clientReceive(LPVOID lpParam) {
	char buffer[1024] = { 0 };
	SOCKET server = *(SOCKET*)lpParam;
	while (true) {
		if (recv(server, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
			cout << "recv function failed with error: " << WSAGetLastError() << endl;
			return -1;
		}
		if (strcmp(buffer, "exit\n") == 0) {
			cout << "Server disconnected." << endl;
			return 1;
		}
		cout << "Server: " << buffer << endl;
		memset(buffer, 0, sizeof(buffer));
	}
	return 1;
}

DWORD WINAPI clientSend(LPVOID lpParam) {
	char buffer[1024] = { 0 };
	SOCKET server = *(SOCKET*)lpParam;
	while (true) {
		fgets(buffer, 1024, stdin);
		if (send(server, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
			cout << "send failed with error: " << WSAGetLastError() << endl;
			return -1;
		}
		if (strcmp(buffer, "exit") == 0) {
			cout << "Thank you for using the application" << endl;
			break;
		}
	}
	return 1;
}

int main() {
	WSADATA WSAData;
	SOCKET server;
	SOCKADDR_IN addr;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Socket creation failed with error: " << WSAGetLastError() << endl;
		return -1;
	}

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);
	if (connect(server, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		cout << "Server connection failed with error: " << WSAGetLastError() << endl;
		return -1;
	}

	cout << "Connected to server!" << endl;
	cout << "Now you can use our live chat application. " << " Enter \"exit\" to disconnect" << endl;

	DWORD tid;
	HANDLE t1 = CreateThread(NULL, 0, clientReceive, &server, 0, &tid);
	if (t1 == NULL) cout << "Thread creation error: " << GetLastError();
	HANDLE t2 = CreateThread(NULL, 0, clientSend, &server, 0, &tid);
	if (t2 == NULL) cout << "Thread creation error: " << GetLastError();

	WaitForSingleObject(t1, INFINITE);
	WaitForSingleObject(t2, INFINITE);
	closesocket(server);
	WSACleanup();
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
