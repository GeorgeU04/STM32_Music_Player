#include "../Inc/ILI9341.h"
#include "main.h"

inline void writeCommand(uint8_t cmd) {
  CDX_GPIO_Port->BSRR = (CDX_Pin << 16);                  // set CDX low
  CSX_GPIO_Port->BSRR = (CSX_Pin << 16);                  // set CSX low
  D0_GPIO_Port->ODR = (D0_GPIO_Port->ODR & 0xFF00) | cmd; // set D0-D7
  WRX_GPIO_Port->BSRR = (WRX_Pin << 16);                  // set WRX low
  WRX_GPIO_Port->BSRR = (WRX_Pin);                        // set WRX high
  CSX_GPIO_Port->BSRR = (CSX_Pin);                        // set CSX high
}

inline void writeData(uint8_t data) {
  CDX_GPIO_Port->BSRR = (CDX_Pin);                         // set CDX high
  CSX_GPIO_Port->BSRR = (CSX_Pin << 16);                   // set CSX low
  D0_GPIO_Port->ODR = (D0_GPIO_Port->ODR & 0xFF00) | data; // set D0-D7
  WRX_GPIO_Port->BSRR = (WRX_Pin << 16);                   // set WRX low
  WRX_GPIO_Port->BSRR = (WRX_Pin);                         // set WRX high
  CSX_GPIO_Port->BSRR = (CSX_Pin);                         // set CSX high
}

void ILI9341Init(void) {
  /* Power control B */
  writeCommand(LCD_POWERB); // 0xCF
  writeData(0x00);
  writeData(0xC1);
  writeData(0x30);

  /* Power on sequence control */
  writeCommand(LCD_POWER_SEQ); // 0xED
  writeData(0x64);
  writeData(0x03);
  writeData(0x12);
  writeData(0x81);

  /* Driver timing control A */
  writeCommand(LCD_DTCA); // 0xE8
  writeData(0x85);
  writeData(0x00);
  writeData(0x78);

  /* Power control A */
  writeCommand(LCD_POWERA); // 0xCB
  writeData(0x39);
  writeData(0x2C);
  writeData(0x00);
  writeData(0x34);
  writeData(0x02);

  /* Pump ratio control */
  writeCommand(LCD_PRC); // 0xF7
  writeData(0x20);

  /* Driver timing control B */
  writeCommand(LCD_DTCB); // 0xEA
  writeData(0x00);
  writeData(0x00);

  /* Power control 1 */
  writeCommand(LCD_POWER1); // 0xC0
  writeData(0x23);

  /* Power control 2 */
  writeCommand(LCD_POWER2); // 0xC1
  writeData(0x10);

  /* VCOM control 1 */
  writeCommand(LCD_VCOM1); // 0xC5
  writeData(0x3E);
  writeData(0x28);

  /* VCOM control 2 */
  writeCommand(LCD_VCOM2); // 0xC7
  writeData(0x86);

  /* Memory Access Control */
  writeCommand(LCD_MAC); // 0x36
  writeData(0x48);

  /* Vertical scroll start address */
  writeCommand(LCD_VSCRSADD); // 0x37
  writeData(0x00);

  /* Pixel format */
  writeCommand(LCD_PIXEL_FORMAT); // 0x3A
  writeData(0x55);                // 16-bit color

  /* Frame rate control */
  writeCommand(LCD_FRMCTR1); // 0xB1
  writeData(0x00);
  writeData(0x18);

  /* Display function control */
  writeCommand(LCD_DFC); // 0xB6
  writeData(0x08);
  writeData(0x82);
  writeData(0x27);

  /* 3 Gamma function disable */
  writeCommand(LCD_3GAMMA_EN); // 0xF2
  writeData(0x00);

  /* Gamma curve selected */
  writeCommand(LCD_GAMMA); // 0x26
  writeData(0x01);

  /* Positive gamma correction */
  writeCommand(LCD_PGAMMA); // 0xE0
  writeData(0x0F);
  writeData(0x31);
  writeData(0x2B);
  writeData(0x0C);
  writeData(0x0E);
  writeData(0x08);
  writeData(0x4E);
  writeData(0xF1);
  writeData(0x37);
  writeData(0x07);
  writeData(0x10);
  writeData(0x03);
  writeData(0x0E);
  writeData(0x09);
  writeData(0x00);

  /* Negative gamma correction */
  writeCommand(LCD_NGAMMA); // 0xE1
  writeData(0x00);
  writeData(0x0E);
  writeData(0x14);
  writeData(0x03);
  writeData(0x11);
  writeData(0x07);
  writeData(0x31);
  writeData(0xC1);
  writeData(0x48);
  writeData(0x08);
  writeData(0x0F);
  writeData(0x0C);
  writeData(0x31);
  writeData(0x36);
  writeData(0x0F);

  /* Exit sleep mode */
  writeCommand(LCD_SLEEP_OUT);
  HAL_Delay(150);

  /* Display ON */
  writeCommand(LCD_DISPLAY_ON);
  HAL_Delay(150);

  /* Normal display mode */
  writeCommand(LCD_NORMAL_MODE_ON);
}
