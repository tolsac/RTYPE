/*
** NetworkManager.h for NetworkManager in /home/tolsa/Documents/R-type/Network/libsocket/only_srv
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Mon Dec 24 07:33:24 2012 tolsa_c
** Last update Wed Jan  9 22:40:18 2013 tolsa_c
*/

#ifndef NETWORKMANAGER_H_
# define NETWORKMANAGER_H_

#include <TcpServer.h>
#include <TcpSocket.h>
#include <ICallback.hh>
#include <Mutex.hh>
#include <Logger.h>

class NetworkManager : public ICallback
{
public:
	NetworkManager();
	~NetworkManager();

	int							getPacketAvailableCount();
	void						sendPacket(PacketContainer::PacketSerialised*, Connexion*, bool);
	void						init();
	void						run();
	PacketInfo					*readPacket();
	void						update();
	bool						takeConnexionList();
	bool						releaseConnexionList();
	std::list<Connexion*>&		getConnexionList();
	bool						takePacketList();
	bool						releasePacketList();
	std::list<PacketInfo*>&		getPacketList();
	Connexion					*getConnexionByLogin(std::string const&);
	Connexion					*getConnexionByNetInfos(std::string const&, int);
	void						operator()();

	Mutex						mPacket;
	Mutex						mConnexion;

private:
	std::list<PacketInfo*>		_lstPackets;
	std::list<Connexion*>		_lstConnexions;
	TcpServer					_tcpServer;
	UdpSocket					*_udpSocket;
};

#endif /* !NETWORKMANAGER_H_ */
