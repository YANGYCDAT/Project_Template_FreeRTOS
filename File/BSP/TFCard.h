#ifndef TF_CARD_H
#define TF_CARD_H

#include "TF_Card_SPI_DMA.h"
#include "stdarg.h"
#include "stdio.h"

extern FATFS FFats;
extern FRESULT Mount_Result;
extern FRESULT File_Result;

void SD_Mount(void);
void SD_printf(const char* fmt, ...);

#endif
