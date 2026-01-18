#include "../Inc/SD.h"
#include "../../FATFS/App/fatfs.h"
#include <stdint.h>
#include <string.h>

int8_t mountSDCard() {
  FATFS FatFs;
  FRESULT result = f_mount(&FatFs, (TCHAR const *)"", 1);
  return result;
}

int8_t readAlbumData(struct album *album) {
  char buffer[200];
  FIL Fil;
  FATFS FatFs;
  FRESULT result = f_mount(&FatFs, (TCHAR const *)"", 1);
  return result;
  // if (!f_chdir("Illmatic"))
  //   return -2;
  if (f_open(&Fil, "test.txt", FA_READ) != FR_OK)
    return -3;
  f_gets(buffer, sizeof(buffer), &Fil);
  strncpy(album->AlbumName, buffer, sizeof(album->AlbumName));
  f_close(&Fil);
  return 0;
}

int8_t readAlbumCover();
