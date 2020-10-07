#include "pch.h"

#include "Framework\\Managers\\Network Manager\\Core\\NetworkManager.h"

Uniquis::NetworkManager::NetworkManager()
{
	const unsigned __int16 Version = ((2 << 8) + 2);

	WSAData Data;

	if (WSAStartup(Version, &(Data)))
	{
		OutputDebugString(L"[ERROR] Initialization of Winsock failed! \n");
	}
}

Uniquis::NetworkManager::~NetworkManager()
{

}

Uniquis::NetworkManager& Uniquis::NetworkManager::getReference()
{
	static NetworkManager Instance;

	return Instance;
}

void Uniquis::NetworkManager::createSocket(NetworkProtocol type)
{
	SOCKET Socket;

	switch (type)
	{
		case NetworkProtocol::UDP:
		{
			Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

			break;
		}

		case NetworkProtocol::TCP:
		{
			Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			break;
		}
	}

	if (Socket == INVALID_SOCKET)
	{
		OutputDebugStringA(std::string("[ERROR] Socket initializsation failed! Error code: ").append(std::to_string(WSAGetLastError()).c_str()).append("\n").c_str());
	}

	this->vSockets.push_back(Socket);
}

void Uniquis::NetworkManager::sendTo(const std::wstring& address)
{
	SOCKADDR_IN Address;

	__int8 Buffer[256];

	Address.sin_family           = AF_INET;
	Address.sin_port             = htons(1234);
	Address.sin_addr.S_un.S_addr = inet_addr(std::string(address.begin(), address.end()).c_str());

	bind(this->vSockets[0], reinterpret_cast<SOCKADDR*>(&(Address)), sizeof(SOCKADDR_IN));

	strcpy(Buffer, "Hallo Welt!");

	if (sendto(this->vSockets[0], Buffer, strlen(Buffer), 0, reinterpret_cast<SOCKADDR*>(&(Address)), sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		OutputDebugString(L"[ERROR] Bytes could not be sent! \n");

		OutputDebugStringA(std::string("[ERROR] Error code: ").append(std::to_string(WSAGetLastError()).c_str()).append("\n").c_str());
	}
}

void Uniquis::NetworkManager::receiveFrom(const std::wstring& address)
{
	SOCKADDR_IN RemoteAddress;

	__int32 RemoteAddressLength = sizeof(SOCKADDR_IN);

	char Buffer[256];
	
	if (recvfrom(this->vSockets[0], Buffer, 256, 0, reinterpret_cast<SOCKADDR*>(&(RemoteAddress)), &(RemoteAddressLength)) == SOCKET_ERROR)
	{
		OutputDebugString(L"[ERROR] Bytes could not be received! \n");

		OutputDebugStringA(std::string("[ERROR] Error code: ").append(std::to_string(WSAGetLastError()).c_str()).append("\n").c_str());
	}

	OutputDebugStringA(Buffer);
	OutputDebugStringA("\n");
}