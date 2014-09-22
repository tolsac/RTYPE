/* Header de la classe PacketContainer. */
/* Auteur: Bertrand Boyer */
/* Commenc� le 22/12/12. */
/* Derni�re modification: 08/01/13. */

#ifndef __PACKETCONTAINERZ_H__
#define __PACKETCONTAINERZ_H__

#include <cstdio>
#include <ctime>
#include <stdint.h>
#include <string.h>

#include <Protocol.h>

#define _USE_32BIT_TIME_T

class PacketContainer
{
public:
	struct Header									/* Structure du header des paquets. */
	{
		uint32_t	magic;							/* Nombre magique, teste la validit� du paquet. */
		uint32_t	checksum;						/* Autre �l�ment de test de validit� du paquet. */
		uint32_t	timestamp;						/* Date d'envoi du paquet. */
		uint16_t	commandId;						/* Identifiant de la commande. */
		uint16_t	dataSize;						/* Taille de la donn�e envoy�e. */
	};

	struct PacketSerialised							/* Structure d'un paquet s�rialis�. */
	{
		struct Header	header;						/* Header s�rialis�. */
		char			data[Protocol::SIZE];		/* Data s�rialis�e. */
	};	

private:
	uint32_t			magic;						/* Nombre magique, teste la validit� du paquet. */
	uint32_t			checkSum;					/* Autre �l�ment de test de validit� du paquet. */
	uint32_t			timestamp;					/* Date d'envoi du paquet. */
	uint16_t			commandID;					/* Identifiant de la commande. */
	uint16_t			sizeData;					/* Taille de la donn�e envoy�e. */
	char				data[Protocol::SIZE];		/* Data du packet. */
	int					offset;						/* Index d'�criture dans la data du packet.*/
	bool				valid;						/* Validit� du paquet. */
	PacketSerialised	*ps;						/* Pointeur vers le paquet serialis�, pr�t pour l'envoi. */

public:
	/* Constructeurs et destructeur */
	PacketContainer(void);
	PacketContainer(int commandID);
	PacketContainer(void *buff);
	~PacketContainer(void);

	/* Setters. */
	//  void				setTarger(Connexion*);
	/* Getters. */
	uint32_t			getCheckSum() const;
	time_t				getTimestamp() const;
	uint16_t			getCommandID() const;
	uint16_t			getSizeData() const;
	int					getOffset() const;
	char				*getData() const;
	PacketSerialised	*getPacketSerialised();

	/* M�thodes. */
	int					displayPacket() const;			/* Affiche le contenu du packet. */
	int					addData(const void *data, int size);	/* Ajoute une donn�e dans le packet. */
	void				*extractData(int offset, int size, void *dest);			/* Extrait size octet de la data depuis l'offset. */
	bool				isEmpty() const;				/* Vrai si le paquet ne contient aucune donn�e. Faux sinon. */
	bool				isValid() const;				/* Vrai si le paquet est valide. Faux sinon. */
	bool				checkMagic();
	uint32_t			calculateCheckSum();			/* Calcule le checksum d'un paquet. */
	unsigned char		*deserialize_header(char *, PacketContainer::Header&);

private:
	void			hexdump(const std::string&, char*, int) const;

	/* M�thodes pour la s�rialisation du paquet. */
	unsigned char			*serialize_uint32(unsigned char *, uint32_t);
	unsigned char			*serialize_uint16(unsigned char *, uint16_t);
	unsigned char			*serialize_char(unsigned char *, char);
	unsigned char			*serialize_string(unsigned char *, char *, int);
	unsigned char			*serialize_header(unsigned char *, PacketContainer::Header&);
	unsigned char			*serialize_packet(unsigned char *, PacketContainer::PacketSerialised&); //Du coup je ne suis pas certain du prototypage...

	unsigned char			*deserialize_uint32(unsigned char *, uint32_t*);
	unsigned char			*deserialize_uint16(unsigned char *, uint16_t*);
	unsigned char			*deserialize_char(unsigned char *, char*);
	unsigned char			*deserialize_string(unsigned char *, char *, int);
	unsigned char			*deserialize_packet(char *, PacketContainer::PacketSerialised&); //Ici non plus je ne sais pas si c'est le bon prototype.
};

#endif /* __PACKETCONTAINER_H__ */
