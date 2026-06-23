#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__



#define SSD1306_USE_I2C




// Include the HAL driver for your specific chip
#include "stm32f1xx_hal.h"

// Choose your screen size
#define SSD1306_HEIGHT          64
#define SSD1306_WIDTH           128

// I2C Configuration
#define SSD1306_I2C_PORT        hi2c1
#define SSD1306_I2C_ADDR (0x3C << 1)

// Feature Toggles (leave as is for now)
#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
#define SSD1306_INCLUDE_FONT_16x26

#endif /* __SSD1306_CONF_H__ */
