## Adafruit GFX Library original text:

This is the core graphics library for all our displays, providing a common set of graphics primitives (points, lines, circles, etc.). It needs to be paired with a hardware-specific library for each display device we carry (to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, check license.txt for more information.
All text above must be included in any redistribution.

This library carries exactly the same licensing terms as the original, any changes made in this repo are assumed to be under the same terms as the original too.

## Library fork supporting SSD1306/SH1106 displays on mbed 5/6 RTOS

Although many newer mbed RTOS chipsets have inbuilt hardware LCD drivers, there's sometimes a need to use a more basic display, such as an OLED or LCD unit. This is a fork of the Adafruit_GFX library with changes to run on mbed 5/6 RTOS. It is derived from a few sources:

* Most of the hard work was done by [AdaFruit in the Adafruit_GFX repo](https://github.com/adafruit/Adafruit-GFX-Library)
* I then combined the latest Adafruit_GFX master with the [work originally done to support SSD1306 on mbed 2](https://os.mbed.com/users/nkhorman/code/Adafruit_GFX/) 
* On top of this I added support for SH1106 displays (after doing a bit of digging and datasheet analysis). 
* You can use the regular [Adafruit_GFX introductory guide](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview) as this fork has high compatibility. 
* It also integrates well with tcMenu, IoAbstraction and TaskManagerIO.

## Different construction between version

If you prefer to stay temporarily with the old version here is the link, we do recommend you move forward, and the work to do so should be trivial for most, but here is the old link: https://github.com/TcMenu/Adafruit-GFX-mbed-fork/releases/tag/mb0.1.1

## Constructing and using a display object

For SPI, we recommend that you create the object using `new` once the system is initialised, sometimes trying to use SPI in any way before this results in board crashes. This is as simple as deferring the creation.
    
    // Global variable
    AdafruitSSD1306Spi* gfx;

    // then somewhere during setup
    gfx = new AdafruitSSD1306Spi(SPIWithSettings(&spi, PF_13, 10000000), PD_15, PF_12, 64, 128, ENCMODE_UTF8, SSD_1306);
    gfx->begin();

For I2C you can use either the above method or just use a global variable providing it an I2C pointer and the address of the device:

    AdafruitSSD1306I2c gfx(&i2c, NC, SSD_I2C_ADDRESS, 64, 132, ENCMODE_UTF8, SH_1106);

The above assume you want to use UTF-8 encoding.

Once created usage is almost exactly the same as regular Adafruit_GFX with tcUnicode also available (even down to the print interface).

## Issues

Never raise issues in the core Adafruit_GFX repository as this fork is now very different, please raise the issue here first for us to triage it.

## Usage

This library can work with SSD1306 and SH1106 displays over I2C or SPI. There's a couple of really simple examples packaged that show basic usage. However, you can look at almost any Adafruit example, as this library is completely compatible.

This library integrates with IoAbstraction to provide a complete Print interface that is nearly compatible with Arduino's print functions. You also need `IoAbstraction` to use this library. 

Performance, at the moment the SSD1306 class could be significantly optimised. However, our first aim is to get it stable on mbed 5/6, we'll look at performance later.

## What is the purpose of this fork:

Every fork should state what it's purpose is. This fork is purely to provide mbed support for a few popular displays, we do not intend to change the core libraries in any way. It allows mbed V6 users to take advantage of the excellent Adafruit_GFX library. We have set it up to work with platformIO, but it should also work with any other build system.

Important note about bug fixes: do not put in PRs for the core graphics class here, only mbed and display specific fixes will be applied. Instead apply any changes to the core and then we'll re-pull the change here.

# Bitmaps and fonts with the library

- With TcMenu Designer you can now export and even create bitmaps suitable for use with this library. You can use the GIMP photo editor to save a .xbm file and use the array saved in the file to draw a bitmap with the drawXBitmap function. See the main tcMenu repo to download. 
- 'Fonts' folder contains bitmap fonts for use with recent (1.1 and later) Adafruit_GFX. To use a font in your Arduino sketch, \#include the corresponding .h file and pass address of GFXfont struct to setFont(). As of 2024 you must choose a font, either TcUnicode or Ada Gfx. This fork now always uses the tcUnicode library for text.
- You can use TcMenu Designer to export custom fonts, it has a font export utility.
