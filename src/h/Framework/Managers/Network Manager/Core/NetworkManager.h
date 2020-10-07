#pragma once

namespace Uniquis
{
	enum class NetworkProtocol
	{
		UDP,
		TCP
	};

	class NetworkManager
	{
	public:

		std::vector<SOCKET> vSockets;

	private:

		NetworkManager();

	public:

		NetworkManager(const NetworkManager&) = delete;

		NetworkManager(const NetworkManager&&) = delete;

		~NetworkManager();

	public:

		static NetworkManager& getReference();

		void createSocket(NetworkProtocol type);
		void sendTo(const std::wstring& address);
		void receiveFrom(const std::wstring& address);

	public:

		void operator=(const NetworkManager&) = delete;
	};
}