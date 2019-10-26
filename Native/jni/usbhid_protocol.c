#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

static int gDevNodeFd = -1;

enum {
	CMD_SEND_BATT_LEVEL = 0x11,
};

#define HIDGFD "/dev/hidg0"

static int constructAndSendPacket(uint8_t cmd, uint8_t *payload, uint8_t payloadLen)
{
	int ret, i = 0;
	uint16_t crc, packetLen = 0;
	uint8_t *buffer = NULL;

	packetLen = payloadLen + 6;
	if(packetLen > 255){
		ERROR("payloadSize limit to %d bytes, overflow...\n", 255 - 6);
		return -1;
	}

	buffer = malloc(packetLen);
	buffer[0] = 0xAA;
	buffer[1] = payloadLen + 4;
	buffer[2] = cmd;
	memcpy(buffer + 3, payload, payloadLen);
	buffer[packetLen - 1] = 0x55;

	crc = getCrc16Check(buffer + 1, payloadLen + 2);

	buffer[payloadLen + 3] = crc >> 8;
	buffer[payloadLen + 3 + 1] = (uint8_t)(crc & 0x00ff);

#if 0
	DBG("\n=============================\n");
	for(i=0; i<payloadLen + 6; i++)
	{
		DBG("0x%x : ", *(buffer+i));
	}
	DBG("\n=============================\n");
#endif
	uint8_t numWrite = packetLen / 16; //once write limit 16bytes
	uint8_t endWrite = packetLen % 16;
	i = 0;
	if(numWrite == 0){
		ret = write(gDevNodeFd, buffer, packetLen);
		if(ret < packetLen)
			return ret;
		DBG("[once]: wirte %d bytes\n", ret);
	}else{
		while(i < numWrite){
			ret = write(gDevNodeFd, buffer, 16);
			if(ret < 16){
				free(buffer);
				buffer = NULL;
				return ret;
			}
			DBG("[multi-%d]: wirte %d bytes\n", i + 1, ret);
			i++;
			buffer += 16;
		}
		if(endWrite > 0)
		{
			ret = write(gDevNodeFd, buffer, endWrite);
			if(ret < endWrite){
				free(buffer);
				buffer = NULL;
				return ret;
			}
			DBG("[multi-%d]: wirte %d bytes\n", i + 1, ret);
		}
	}

	free(buffer);
	buffer = NULL;

	return 0;
}

int usbHidSend(uint8_t cmd, uint8_t *payload, uint8_t payloadLen)
{
	int ret = 0;

	if(gDevNodeFd < 0)
	{
		ERROR("DevNode(%s) not opened\n", HIDGFD);
		return -1;
	}

	ret = constructAndSendPacket(cmd, payload, payloadLen);
	if(ret){
		ERROR("constructAndSendPacket error:%d\n", ret);
		return -1;
	}

	return 0;
}

int openDevNode()
{
	if ((gDevNodeFd = open(HIDGFD, O_RDWR)) < 0)
	{
		DBG("open dev node(%s) error\n", HIDGFD);
		return -1;
	}

	return 0;
}

void closeDevNode()
{
	close(gDevNodeFd);
	gDevNodeFd = -1;
}
#if 0
int main(int argc, const char *argv[])
{
	int ret = 0;
	uint8_t level = 100;

	if(openDevNode())
	{
		DBG("openDevNode failed...\n");
		return -1;
	}
	DBG("openDevNode successfully, fd:%d\n", gDevNodeFd);

	ret = usbHidSend(CMD_SEND_BATT_LEVEL, &level, sizeof(level));
	if(!ret) DBG("usbHidSend cmd:0x%x ok\n", CMD_SEND_BATT_LEVEL);

	closeDevNode();

	return 0;
}
#endif
