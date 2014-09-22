/*
** TcpSocket.cpp for TcpSocket in /home/tolsa/Documents/Socket
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Tue Dec 11 15:39:17 2012 tolsa_c
** Last update Wed Jan  9 21:00:31 2013 tolsa_c
*/

#include <stdio.h>
#include <errno.h>
#include <ATcpSocket.h>
#include <TcpSocketWin.h>

TcpSocketWin::TcpSocketWin()
{
	struct protoent	*p;

	p = getprotobyname("TCP");
	this->_valid = true;
	this->_socket = socket(AF_INET, SOCK_STREAM, p->p_proto);
	if (this->_socket <= 0)
		this->_valid = false;
	//  if (!this->unblock())
	//  this->_valid = false;
}

TcpSocketWin::TcpSocketWin(socket_t s)
{
	this->_valid = true;
	this->_socket = s;
	// if (!this->unblock())
	//	this->_valid = false;
}

TcpSocketWin::~TcpSocketWin()
{
	this->closeSocket();
}

bool			TcpSocketWin::block()
{
	u_long	nonBlockingMode = 0;

	if (ioctlsocket(this->_socket, FIONBIO, &nonBlockingMode) == -1)
		return (false);
	return (true);
}

bool			TcpSocketWin::unblock()
{
	u_long	nonBlockingMode = 1;

	if (ioctlsocket(this->_socket, FIONBIO, &nonBlockingMode) == -1)
		return (false);
	return (true);
}

bool			TcpSocketWin::connectSocket(const std::string& ip, int port)
{
	struct sockaddr_in	srv;
	int			        ret;

	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(ip.c_str());
	srv.sin_port = htons(port);
	if ((ret = connect(this->_socket, (struct sockaddr *)&srv, sizeof(srv))) == -1)
		perror("connect");
	if (ret == 0)
		return (true);
	return (false);
}

int			TcpSocketWin::read(char *buff, int len)
{
	int			ret;

	ret = recv(this->_socket, buff, len, 0);
	return (ret);
}

int			TcpSocketWin::bytesAvailable()
{
	int			ret;
	char		buff[65536];

	ret = recv(this->_socket, buff, 65535, MSG_PEEK);
	return (ret);
}

int			TcpSocketWin::copyQueue(char *buff, int len)
{
	return (recv(this->_socket, buff, 65535, MSG_PEEK));
}

int			TcpSocketWin::readAll(char *buff)
{
	return (this->read(buff, 65535));
}

int			TcpSocketWin::write(const std::string& buff, int len)
{
	int			ret;

	ret = send(this->_socket, buff.c_str(), len, 0);
	return (ret);
}

int			TcpSocketWin::writePacket(PacketContainer::PacketSerialised *packet)
{
	int			ret;

	ret = 0;
	ret += send(this->_socket, (char*)(&packet->header.magic), sizeof(uint32_t), 0);
	ret += send(this->_socket, (char*)(&packet->header.checksum), sizeof(uint32_t), 0);
	ret += send(this->_socket, (char*)(&packet->header.timestamp), sizeof(uint32_t), 0);
	ret += send(this->_socket, (char*)(&packet->header.commandId), sizeof(uint16_t), 0);
	ret += send(this->_socket, (char*)(&packet->header.dataSize), sizeof(uint16_t), 0);
	ret += send(this->_socket, (packet->data), packet->header.dataSize, 0);
	if (ret != (int)(sizeof(PacketContainer::Header) + packet->header.dataSize))
		return (-1);
	return (ret);
}

bool			TcpSocketWin::dataAvailable()
{
	fd_set                sready;
	struct timeval        nowait;

	FD_ZERO(&sready);
	FD_SET((unsigned int)this->_socket, &sready);
	memset((char *)&nowait, 0, sizeof(nowait));
	select(this->_socket + 1, &sready, NULL, NULL, &nowait);
	if (FD_ISSET(this->_socket, &sready))
		return (true);
	else
		return (false);
}

int			TcpSocketWin::closeSocket()
{
	int		ret;

	ret = closesocket(this->_socket);
	WSACleanup();
	return (ret);
}

socket_t		TcpSocketWin::getSocket() const
{
	return (this->_socket);
}

void			TcpSocketWin::flush()
{
	char			buff[65536];
	int			bav;

	bav = this->bytesAvailable();
	this->read(buff, bav);
}
