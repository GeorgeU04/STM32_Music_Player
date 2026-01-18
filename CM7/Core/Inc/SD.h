#ifndef SD_H
#define SD_H

#include <stdint.h>

struct track {
  char trackTitle[64];
  uint32_t trackDuration;
  uint16_t trackNumber;
};

struct album {
  struct track trackList[36];
  char AlbumName[64];
  char artistName[64];
  uint16_t trackCount;
};

int8_t readAlbumData(struct album *album);
int8_t readAlbumCover();
int8_t mountSDCard();

#endif // !SD_H
