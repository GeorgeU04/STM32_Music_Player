#ifndef GUI_H
#define GUI_H

#define BUFFER_LINES 60
#define HOR_RES 240
#include "SD.h"

void initScreen(void);
void drawMainScreen(struct album album);
#endif // !GUI_H
