#ifndef __F_S_COMMUNICAT_H_
#define __F_S_COMMUNICAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_system.h"

/* 包固定信息 */
#define PACKET_HEAD                                     (uint8_t[]){0xEF, 0x01}
#define PACKET_ADDRESS                                  (uint8_t[]){0xFF, 0xFF, 0xFF, 0xFF}
#define PACKET_MARK_COMMEND                                     (uint8_t[]){0x01}
#define PACKET_MARK_ANSWER                                  (uint8_t[]){0x07}

/* 控制指令 */
#define CMD_GetImage                                    (uint8_t[]){0x01} 
#define CMD_GenChar                                      (uint8_t[]){0x02} 
#define CMD_Match                                           (uint8_t[]){0x03} 
#define CMD_Search                                         (uint8_t[]){0x04}
#define CMD_RegModel                                    (uint8_t[]){0x05}
#define CMD_StoreChar                                   (uint8_t[]){0x06}
#define CMD_LoadChar                                    (uint8_t[]){0x07}
#define CMD_UpChar                                    (uint8_t[]){0x08}
#define CMD_DownChar                                    (uint8_t[]){0x09}
#define CMD_UpImage                                    (uint8_t[]){0x0A}
#define CMD_DownImage                                    (uint8_t[]){0x0B}
#define CMD_DelectChar                                    (uint8_t[]){0x0C}
#define CMD_Empty                                    (uint8_t[]){0x0D}
#define CMD_WirteReg                                    (uint8_t[]){0x0E}
#define CMD_ReadSysParm                                    (uint8_t[]){0x0F}
#define CMD_Enroll                                    (uint8_t[]){0x10}
#define CMD_Identify                                    (uint8_t[]){0x11}
#define CMD_SetPwd                                    (uint8_t[]){0x12}
#define CMD_VfyPwd                                    (uint8_t[]){0x13}
#define CMD_GetRandomCode                                    (uint8_t[]){0x14}
#define CMD_SetChipAddr                                    (uint8_t[]){0x15}
#define CMD_ReadINPage                                    (uint8_t[]){0x16}
#define CMD_PortControl                                    (uint8_t[]){0x17}
#define CMD_WriteNotepad                                    (uint8_t[]){0x18}
#define CMD_ReadNotepad                                    (uint8_t[]){0x19}
#define CMD_BurnCode                                    (uint8_t[]){0x1A}
#define CMD_HighSpeedSearch                                    (uint8_t[]){0x1B}
#define CMD_GenBinImane                                    (uint8_t[]){0x1C}

/* 指令参数 */
#define PARM_CharBufferID_1                 (uint8_t[]){0x01}
#define PARM_CharBufferID_2                 (uint8_t[]){0x02}
#define PARM_StartPage              (uint8_t[]){0x00, 0x00}
#define PARM_PageNum                (uint8_t[]){0x00, 0x08}

// 01H
uint8_t * GetImage();
// 02H
uint8_t * GenChar(uint8_t buffID);
// 03H
uint8_t * Match();
// 05H
uint8_t * RegModel();
// 06H
uint8_t * StoreChar(uint8_t buffID, uint16_t pageID);
// 10H
uint8_t * Enroll();
// 11H
uint8_t * Identify();

#endif