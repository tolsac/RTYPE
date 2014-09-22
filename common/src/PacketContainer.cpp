/* Auteur: Bertrand Boyer */
/* Commencé le 22/12/12. */
/* Dernière modification: 08/01/13. */

#include <iostream>

#include <PacketContainer.h>

PacketContainer::PacketContainer(void)
{
	this->magic = Protocol::MAGIC;
	time(((time_t*)&(this->timestamp)));
	this->sizeData = 0;
	this->commandID = 0;
	memset(this->data, 0, Protocol::SIZE);
	this->checkSum = this->calculateCheckSum();
	this->offset = 0;
	this->valid = false;
	this->ps = NULL;
}

PacketContainer::PacketContainer(int commandID)
{
	this->magic = Protocol::MAGIC;
	time(((time_t*)&(this->timestamp)));
	this->sizeData = Protocol::mapSize.find(commandID)->second;
	this->commandID = commandID;
	memset(this->data, 0, Protocol::SIZE);
	this->checkSum = this->calculateCheckSum();
	this->offset = 0;
	this->valid = true;
	this->ps = NULL;
}

PacketContainer::PacketContainer(void *buff)
{
	Header	*hdr = NULL;
	void	*dt = NULL;

	hdr = static_cast<Header*>(buff);
	if (hdr->magic != Protocol::MAGIC)
	{
		this->valid = false;
		return;
	}
	this->magic = hdr->magic;
	this->timestamp = hdr->timestamp;
	if (Protocol::mapSize.count(hdr->commandId) == 0)
	{
		this->valid = false;
		return;
	}
	this->commandID = hdr->commandId;
	if (Protocol::mapSize.find(commandID)->second != hdr->dataSize)
	{
		this->valid = false;
		return;
	}
	this->sizeData = hdr->dataSize;
	memset(this->data, 0, Protocol::SIZE);
	if (this->sizeData != 0)
	{
		dt = static_cast<char*>(buff) + sizeof(Header);
		memcpy(this->data, dt, this->sizeData);
	}
	if (hdr->checksum != this->calculateCheckSum())
	{
		this->valid = false;
		return;
	}
	this->checkSum = hdr->checksum;
	this->offset = this->sizeData;
	this->valid = true;
	this->ps = reinterpret_cast<PacketContainer::PacketSerialised*>(buff);

	//this->displayPacket();

	/*
	std::cout << "ps magic:" << this->ps->header.magic << std::endl;
	std::cout << "ps checksum:" << this->ps->header.checksum << std::endl;
	std::cout << "ps timestamp:" << this->ps->header.timestamp << std::endl;
	std::cout << "ps commandID:" << this->ps->header.commandId << std::endl;
	std::cout << "ps sizeData:" << this->ps->header.dataSize << std::endl;
	*/
}

PacketContainer::~PacketContainer(void)
{
//	if (this->ps != NULL)
	//	delete ps;
}

/* Getters. */
uint32_t			PacketContainer::getCheckSum() const
{
	return (this->checkSum);
}

time_t				PacketContainer::getTimestamp() const
{
	return (this->timestamp);
}

uint16_t			PacketContainer::getCommandID() const
{
	return (this->commandID);
}

uint16_t			PacketContainer::getSizeData() const
{
	return (this->sizeData);
}

int					PacketContainer::getOffset() const
{
	return (this->offset);
}

char				*PacketContainer::getData() const
{
	return ((char*) this->data);
}

PacketContainer::PacketSerialised*	PacketContainer::getPacketSerialised()
{
	PacketContainer::PacketSerialised	*serial = NULL;

	if (this->ps != NULL)
		return (this->ps);
	if (!(this->valid))
		return (NULL);
	serial = new PacketContainer::PacketSerialised;
	serial->header.magic = this->magic;
	serial->header.checksum = this->checkSum;
	serial->header.timestamp = this->timestamp;
	serial->header.commandId = this->commandID;
	serial->header.dataSize = this->sizeData;
	memcpy(serial->data, this->data, this->sizeData);
	this->ps = serial;
	return (serial);
}

/* Méthodes. */
int					PacketContainer::displayPacket() const
{
	std::cout << "Magic (" << sizeof(this->magic) << "): " << this->magic << std::endl;
	std::cout << "CheckSum (" << sizeof(this->checkSum) << "): " << this->checkSum << std::endl;
	std::cout << "Timestamp (" << sizeof(this->timestamp) << "): " << this->timestamp << std::endl;
	std::cout << "ID command (" << sizeof(this->commandID) << "): " << this->commandID << std::endl;
	std::cout << "Size Data (" << sizeof(this->sizeData) << "): " << this->sizeData << std::endl;
	std::cout << "Valid (" << sizeof(this->valid) << "): " << this->valid << std::endl;
	std::cout << "Data: [" << this->data << "]" << std::endl;
	//this->hexdump("Hexdump Data:", (char*) this->data, Protocol::SIZE);
	return (0);
}

int					PacketContainer::addData(const void *data, int size)
{
	if (((this->sizeData - this->offset) < size) || !(this->valid))
		return (-1);
	memcpy((this->data + this->offset), data, size);
	this->offset = this->offset + size;
	this->checkSum = this->calculateCheckSum();
	return (0);
}

void*				PacketContainer::extractData(int offset, int size, void *dest)
{
	if (offset + size > this->sizeData)
		return (NULL);
	memcpy(dest, &(this->data[offset]), size);
	return(dest);
}

bool				PacketContainer::isEmpty() const
{
	return (this->offset == 0);
}

bool				PacketContainer::isValid() const
{
	return (this->valid);
}

bool				PacketContainer::checkMagic()
{
	return (this->magic == Protocol::MAGIC);
}

uint32_t			PacketContainer::calculateCheckSum()
{
	uint32_t			cs;
	int				i;

	i = -1;
	cs = 0;
	while (++i < this->sizeData)
		cs += ((this->data[i] * i) % 0xFF);
	return (cs);
}

/* Méthodes pour la sérialisation. */
unsigned char				*PacketContainer::serialize_uint32(unsigned char *buffer, uint32_t arg)
{
	buffer[3] = (arg >> 24);
	buffer[2] = (arg >> 16);
	buffer[1] = (arg >> 8);
	buffer[0] = (arg);
	return (buffer + sizeof(uint32_t));
}

unsigned char				*PacketContainer::serialize_uint16(unsigned char *buffer, uint16_t arg)
{
	buffer[1] = (arg >> 8);
	buffer[0] = (arg);
	return (buffer + sizeof(uint16_t));
}

unsigned char				*PacketContainer::serialize_char(unsigned char *buffer, char arg)
{
	buffer[0] = (arg);
	return (buffer + sizeof(char));
}

unsigned char				*PacketContainer::serialize_string(unsigned char *buffer, char *arg, int len)
{
	int				i;

	i = -1;
	while (++i < len)
		buffer = serialize_char(buffer, arg[i]);
	return (buffer);
}

unsigned char				*PacketContainer::serialize_header(unsigned char *buffer, PacketContainer::Header& arg)
{
	buffer = serialize_uint32(buffer, arg.magic);
	buffer = serialize_uint32(buffer, arg.checksum);
	buffer = serialize_uint32(buffer, (uint32_t)arg.timestamp);
	buffer = serialize_uint16(buffer, arg.commandId);
	buffer = serialize_uint16(buffer, arg.dataSize);
	return (buffer);
}

unsigned char				*PacketContainer::serialize_packet(unsigned char *buffer, PacketContainer::PacketSerialised& arg)
{
	buffer = serialize_header(buffer, arg.header);
	buffer = serialize_string(buffer, arg.data, arg.header.dataSize);
	return (buffer);
}

unsigned char				*PacketContainer::deserialize_uint32(unsigned char *buffer, uint32_t *arg)
{
	memcpy((char*)arg, buffer, sizeof(uint32_t));
	return (buffer + sizeof(uint32_t));
}

unsigned char				*PacketContainer::deserialize_uint16(unsigned char *buffer, uint16_t *arg)
{
	memcpy((char*)arg, buffer, sizeof(uint16_t));
	return (buffer + sizeof(uint16_t));
}

unsigned char				*PacketContainer::deserialize_char(unsigned char *buffer, char *arg)
{
	memcpy(arg, buffer, sizeof(char));
	return (buffer + sizeof(char));
}

unsigned char				*PacketContainer::deserialize_string(unsigned char *buffer, char *arg, int len)
{
	memcpy(arg, buffer, len);
	return (buffer + len);
}

unsigned char				*PacketContainer::deserialize_header(char *sbuffer, PacketContainer::Header& arg)
{
	unsigned char				*buffer;

	buffer = reinterpret_cast<unsigned char *>(sbuffer);
	buffer = deserialize_uint32(buffer, &arg.magic);
	buffer = deserialize_uint32(buffer, &arg.checksum);
	buffer = deserialize_uint32(buffer, (uint32_t*)&arg.timestamp);
	buffer = deserialize_uint16(buffer, &arg.commandId);
	buffer = deserialize_uint16(buffer, &arg.dataSize);
	return (buffer);
}

unsigned char				*PacketContainer::deserialize_packet(char *sbuffer,  PacketContainer::PacketSerialised& arg)
{
	unsigned char				*buffer;

	buffer = deserialize_header(sbuffer, arg.header);
	buffer = deserialize_string(buffer, arg.data, arg.header.dataSize);
	return (buffer);
}

void						PacketContainer::hexdump(const std::string &desc, char *addr, int len) const
{
	int						i;
	char					buff[17];
	char					*pc = addr;

	printf ("%s:\n", desc.c_str());
	for (i = 0; i < len; i++)
	{
		if ((i % 16) == 0)
		{
			if (i != 0)
				printf ("  %s\n", buff);
			printf ("  %04x ", i);
		}
		printf (" %02x", pc[i]);
		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buff[i % 16] = '.';
		else
			buff[i % 16] = pc[i];
		buff[(i % 16) + 1] = '\0';
	}
	printf("\n");
}
