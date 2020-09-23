#include "f_s_communicat.h"

uint8_t parm_PacketLength[2] = {0x00, 0x00};
uint8_t parm_PageID[2] = {0x00, 0x00};
uint8_t parm_CheckSum[2] = {0x00, 0x00};

uint8_t cmd[512] = {0};

// 01H
uint8_t * GetImage()
{
    bzero(cmd, 512);

    parm_CheckSum[0] = 0x00;
    parm_CheckSum[1] = 0x00;

    parm_PacketLength[0] = 0x00;
    parm_PacketLength[1] = 0x03;

    uint16_t sum = 0;
    sum = PACKET_MARK_COMMEND[0] + parm_PacketLength[1] + CMD_GetImage[0];
    parm_CheckSum[1] = sum&0xFF;
    parm_CheckSum[0] = sum>>8;

    cmd[0] = PACKET_HEAD[0];
    cmd[1] = PACKET_HEAD[1];
    cmd[2] = PACKET_ADDRESS[0];
    cmd[3] = PACKET_ADDRESS[1];
    cmd[4] = PACKET_ADDRESS[2];
    cmd[5] = PACKET_ADDRESS[3];
    cmd[6] = PACKET_MARK_COMMEND[0];
    cmd[7] = parm_PacketLength[0];
    cmd[8] = parm_PacketLength[1];
    cmd[9] = CMD_GetImage[0];
    cmd[10] = parm_CheckSum[0];
    cmd[11] = parm_CheckSum[1];

    return cmd;
}

// 02H
uint8_t * GenChar(uint8_t buffID)
{
    bzero(cmd, 512);

    parm_CheckSum[0] = 0x00;
    parm_CheckSum[1] = 0x00;

    parm_PacketLength[0] = 0x00;
    parm_PacketLength[1] = 0x04;

    uint16_t sum = 0;
    sum = PACKET_MARK_COMMEND[0] + parm_PacketLength[1] + CMD_GenChar[0] + buffID;
    parm_CheckSum[1] = sum&0xFF;
    parm_CheckSum[0] = sum>>8;

    cmd[0] = PACKET_HEAD[0];
    cmd[1] = PACKET_HEAD[1];
    cmd[2] = PACKET_ADDRESS[0];
    cmd[3] = PACKET_ADDRESS[1];
    cmd[4] = PACKET_ADDRESS[2];
    cmd[5] = PACKET_ADDRESS[3];
    cmd[6] = PACKET_MARK_COMMEND[0];
    cmd[7] = parm_PacketLength[0];
    cmd[8] = parm_PacketLength[1];
    cmd[9] = CMD_GenChar[0];
    cmd[10] = PARM_CharBufferID_1[0];
    cmd[11] = parm_CheckSum[0];
    cmd[12] = parm_CheckSum[1];

    if (buffID == 0x01)
        cmd[10] = PARM_CharBufferID_1;
    else if(buffID == 0x02)
        cmd[10] = PARM_CharBufferID_2;

    return cmd;
}

// 03H
uint8_t * Match()
{
    bzero(cmd, 512);

    parm_CheckSum[0] = 0x00;
    parm_CheckSum[1] = 0x00;

    parm_PacketLength[0] = 0x00;
    parm_PacketLength[1] = 0x03;

    uint16_t sum = 0;
    sum = PACKET_MARK_COMMEND[0] + parm_PacketLength[1] + CMD_Match[0];
    parm_CheckSum[1] = sum&0xFF;
    parm_CheckSum[0] = sum>>8;

    cmd[0] = PACKET_HEAD[0];
    cmd[1] = PACKET_HEAD[1];
    cmd[2] = PACKET_ADDRESS[0];
    cmd[3] = PACKET_ADDRESS[1];
    cmd[4] = PACKET_ADDRESS[2];
    cmd[5] = PACKET_ADDRESS[3];
    cmd[6] = PACKET_MARK_COMMEND[0];
    cmd[7] = parm_PacketLength[0];
    cmd[8] = parm_PacketLength[1];
    cmd[9] = CMD_Match[0];
    cmd[10] = parm_CheckSum[0];
    cmd[11] = parm_CheckSum[1];

    return cmd;
}

// 05H
uint8_t * RegModel()
{
    bzero(cmd, 512);

    parm_CheckSum[0] = 0x00;
    parm_CheckSum[1] = 0x00;

    parm_PacketLength[0] = 0x00;
    parm_PacketLength[1] = 0x03;

    uint16_t sum = 0;
    sum = PACKET_MARK_COMMEND[0] + parm_PacketLength[1] + CMD_RegModel[0];
    parm_CheckSum[1] = sum&0xFF;
    parm_CheckSum[0] = sum>>8;

    cmd[0] = PACKET_HEAD[0];
    cmd[1] = PACKET_HEAD[1];
    cmd[2] = PACKET_ADDRESS[0];
    cmd[3] = PACKET_ADDRESS[1];
    cmd[4] = PACKET_ADDRESS[2];
    cmd[5] = PACKET_ADDRESS[3];
    cmd[6] = PACKET_MARK_COMMEND[0];
    cmd[7] = parm_PacketLength[0];
    cmd[8] = parm_PacketLength[1];
    cmd[9] = CMD_RegModel[0];
    cmd[10] = parm_CheckSum[0];
    cmd[11] = parm_CheckSum[1];

    return cmd;
}

// 06H
uint8_t * StoreChar(uint8_t buffID, uint16_t pageID)
{
    bzero(cmd, 512);

    parm_CheckSum[0] = 0x00;
    parm_CheckSum[1] = 0x00;

    parm_PacketLength[0] = 0x00;
    parm_PacketLength[1] = 0x06;

    parm_PageID[1] = pageID & 0xFF;
    parm_PageID[0] = pageID >> 8;

    uint16_t sum = 0;
    sum = PACKET_MARK_COMMEND[0] + parm_PacketLength[1] + CMD_StoreChar[0];
    parm_CheckSum[1] = sum&0xFF;
    parm_CheckSum[0] = sum>>8;

    cmd[0] = PACKET_HEAD[0];
    cmd[1] = PACKET_HEAD[1];
    cmd[2] = PACKET_ADDRESS[0];
    cmd[3] = PACKET_ADDRESS[1];
    cmd[4] = PACKET_ADDRESS[2];
    cmd[5] = PACKET_ADDRESS[3];
    cmd[6] = PACKET_MARK_COMMEND[0];
    cmd[7] = parm_PacketLength[0];
    cmd[8] = parm_PacketLength[1];
    cmd[9] = CMD_RegModel[0];
    cmd[10]= PARM_CharBufferID_2[0];
    cmd[11]= PARM_PageNum[0];
    cmd[12]= PARM_PageNum[1];
    cmd[13] = parm_CheckSum[0];
    cmd[14] = parm_CheckSum[1];

    if (buffID == 0x01)
        cmd[10] = PARM_CharBufferID_1[0];
    else if(buffID == 0x02)
        cmd[10] = PARM_CharBufferID_2[0];

    return cmd;
}

// 10H
uint8_t * Enroll()
{
    bzero(cmd, 512);

    parm_CheckSum[0] = 0x00;
    parm_CheckSum[1] = 0x00;

    parm_PacketLength[0] = 0x00;
    parm_PacketLength[1] = 0x03;

    uint16_t sum = 0;
    sum = PACKET_MARK_COMMEND[0] + parm_PacketLength[1] + CMD_Enroll[0];
    parm_CheckSum[1] = sum&0xFF;
    parm_CheckSum[0] = sum>>8;

    cmd[0] = PACKET_HEAD[0];
    cmd[1] = PACKET_HEAD[1];
    cmd[2] = PACKET_ADDRESS[0];
    cmd[3] = PACKET_ADDRESS[1];
    cmd[4] = PACKET_ADDRESS[2];
    cmd[5] = PACKET_ADDRESS[3];
    cmd[6] = PACKET_MARK_COMMEND[0];
    cmd[7] = parm_PacketLength[0];
    cmd[8] = parm_PacketLength[1];
    cmd[9] = CMD_Enroll[0];
    cmd[10]= parm_CheckSum[0];
    cmd[11]= parm_CheckSum[1];

    return cmd;
}

// 11H
uint8_t * Identify()
{
    bzero(cmd, 512);

    parm_CheckSum[0] = 0x00;
    parm_CheckSum[1] = 0x00;

    parm_PacketLength[0] = 0x00;
    parm_PacketLength[1] = 0x03;

    uint16_t sum = 0;
    sum = PACKET_MARK_COMMEND[0] + parm_PacketLength[1] + CMD_Identify[0];
    parm_CheckSum[1] = sum&0xFF;
    parm_CheckSum[0] = sum>>8;

    cmd[0] = PACKET_HEAD[0];
    cmd[1] = PACKET_HEAD[1];
    cmd[2] = PACKET_ADDRESS[0];
    cmd[3] = PACKET_ADDRESS[1];
    cmd[4] = PACKET_ADDRESS[2];
    cmd[5] = PACKET_ADDRESS[3];
    cmd[6] = PACKET_MARK_COMMEND[0];
    cmd[7] = parm_PacketLength[0];
    cmd[8] = parm_PacketLength[1];
    cmd[9] = CMD_Identify[0];
    cmd[10]= parm_CheckSum[0];
    cmd[11]= parm_CheckSum[1];

    return cmd;
}
