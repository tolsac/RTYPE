/*
** main.cpp for main in /home/tolsa/Documents/R-type/NetworkManager
** 
** Made by tolsa_c
** Login   <tolsa@ubuntu>
** 
** Started on  Thu Dec 27 08:44:15 2012 tolsa_c
** Last update Thu Dec 27 11:33:55 2012 tolsa_c
*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>

void	hexdump2(char *desc, char *addr, int len)
{
	int i;
	char buff[17];
	char *pc = addr;

	if (desc != NULL)
		printf ("%s:\n", desc);
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
/*
int main()
{
Serialization	s;
struct Header hdr_ser = {2,4,8,16,13};
struct Header hdr_deser;
char		*buffer;
struct Packet p_ser;
struct Packet p_deser;

p_ser.header = hdr_ser;
memcpy(p_ser.data, "coucou mec !", 13);

buffer = new char[sizeof(struct Header) + 13];
bzero(buffer, sizeof(struct Header) + 13);
s.serialize_packet(buffer, p_ser);
hexDump("p_ser", &p_ser, sizeof(struct Header) + 13);

s.deserialize_packet(buffer, p_deser);
hexDump("p_deser", &p_deser, sizeof(struct Header) + 13);
getchar();
printf("%d\n%d\n%d\n%d\n%d\n%s\n", p_deser.header.magic,
p_deser.header.checksum,
p_deser.header.timestamp,
p_deser.header.commandId,
p_deser.header.dataSize,
p_deser.data);

}
*/
