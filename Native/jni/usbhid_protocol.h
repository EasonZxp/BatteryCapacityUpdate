#ifndef  __USBHID_PROTOCOL_H
#define  __USBHID_PROTOCOL_H

extern int usbHidSend(uint8_t cmd, uint8_t *payload, uint8_t payloadLen);
extern int openDevNode();
extern void closeDevNode();

#endif
