# BatteryCapacityUpdate
Use usb gadget hid to transfer Phone's battery capacity to PC

protocol define:
|SOF  |LEN  |CMD  |PAYLOAD     |CRC16 |EOF  |
|1Byte|1Byte|1Byte|最大249Bytes|2Bytes|1Byte|
|0xAA |     |0x11-|                   |0x55 |
LEN = LEN + CMD + PAYLOAD + CRC16 = PAYLOAD + 4
CRC16 = (LEN+CMD+PAYLOAD)'s crc
