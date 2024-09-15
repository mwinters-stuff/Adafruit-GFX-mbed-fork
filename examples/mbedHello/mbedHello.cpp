/**
 * the simplest possible example of using an OLED display with our library
 */

#include <cstdio>
#include "mbed.h"
#include <PlatformDetermination.h>
#include <TaskManager.h>
//#include "Adafruit_SSD1306_I2c.h" (for i2c displays)
#include "oled/AdafruitSSD1306Spi.h"
#include <Fonts/OpenSansRegular7pt.h>

bool running = true;

// For I2C instead of SPI
//#include "oled/AdafruitSSD1306I2c.h"
//I2C i2c(PF_0,PF_1);
//#define SSD_I2C_ADDRESS ..
//AdafruitSSD1306I2c gfx(i2c, NC, SSD_I2C_ADDRESS, 64, 132, SH_1106);

SPI spi(PB_5, PB_4, PB_3);
AdafruitSSD1306Spi* gfx;

int main()
{
    gfx = new AdafruitSSD1306Spi(SPIWithSettings(&spi, PF_13, 10000000), PD_15, PF_12, 64, 128, ENCMODE_UTF8, SSD_1306);

    gfx->begin();

    gfx->clearDisplay();
    gfx->setFont(OpenSansRegular7pt);
    gfx->setCursor(0, 16);
    gfx->setTextColor(WHITE);
    gfx->print("Hello mbed");


    // actually cause the write to take place.
    gfx->display();

    taskManager.scheduleFixedRate(1, [] {
        gfx->fillRect(0, 20, gfx->width(), 20, BLACK);
        gfx->setFont(OpenSansRegular7pt);
        gfx->setCursor(0, 20);
        gfx->print(millis());

        // actually cause the write to take place.
        gfx->display();
    }, TIME_SECONDS);

    while(running) {
        taskManager.runLoop();
    }
}