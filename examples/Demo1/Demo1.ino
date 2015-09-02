/*********************************************************
This is an example use of the Crystalfontz CFA10060
hardware and CFA10060 Arduino library.

NOTE:
The files located in the "Demos_MicroSD_Contents" directory
must be copied onto the root directory of a microSD card
which is then inserted into the CFA10060.

The library can communicate with the CFA10060 via the I2C
or SPI interface.
By default the I2C interface is used. To select the SPI
interface, edit the "CFA10060Lib.h" library file.

Distributed under the "Unlicense" software license.
See: http://unlicense.org/
**********************************************************/

#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "CFA10060Lib.h"

//the CFA10060 device/library
CFA10060 display;

//setup function
void setup()
{
  delay(500);                             //short sleep to stop debugging reset errors
  Serial.begin(115200);                   //start serial at 115200 baud
  Serial.println("Doing setup...");
  //Wire.begin();			          //use the I2C bus
  SPI.begin();		          //by default we are not using the SPI interface
  display.init();			  //initialize the CFA10060
  Serial.println("Setup done.");
}

void do_fade_blank(uint8_t speed = 3)
  //small function do fade out the display.  
  //brightness down, blank the lcd, brightness up
{
  uint8_t x;
  //fade out the display brightness
  for (x = 100; x > 0; x--)
  {
    display.cmdSetBacklightBrightness(x);
    delay(speed); 
  }
  //black the display
  display.cmdFillSolidColor(0, 0, 0);
  //fade in the display brightness
  for (x = 0; x < 100; x++)
  {
    display.cmdSetBacklightBrightness(x);    
    delay(speed);
  }
}  

//the main program
void loop()
{
  //lets ping the display first to make sure its present & alive
  Serial.println("Doing Ping...");
  if (!display.cmdPing("pingdata"))
    Serial.println("Ping FAILED.");
  else
    Serial.println("Ping OK.");

  //clear out any errors
  Serial.println("Clearing Errors...");
  display.cmdCheckAndClearFileSystemErrors();
  Serial.println("Cleared.");

  //turn off the cursor (just in case it was left on)
  display.cmdLCDCursor(CFA10060::cursorOff);
  //blank the LCD to black
  display.cmdFillSolidColor(0, 0, 0);
  
  //main demo loop
  while (1)
  {
    uint8_t x, y;
    uint8_t x_old, y_old;
    uint32_t t;
   
    //first up, display the CF intro banner
    display.cmdDrawSDBMPOnLCD("cfintro.bmp");
    //wait for 2sec
    delay(2000);
    //fade blank display
    do_fade_blank();
    
    //draw a simple primitives example display
    //draw a set of graded blue lines up the display
    for (x = 0; x < 128; x++)
    {
      //set the blue color shade
      display.cmdSetColor(0,0,x*2, 0,0,0);
      //draw the blue line
      display.cmdDrawLine(x,0, (127-x),127);
      //set the red color shade
      display.cmdSetColor(x*2,0,0, 0,0,0);
      //draw the red line
      display.cmdDrawLine(0,x, 127,(127-x));
    }
    //draw a rounded rect in the middle of the display
    display.cmdSetColor(255,255,255, 40,40,40);
    display.cmdDrawRoundedRectangle(28,28, 100,100, 10, CFA10060::drawOutlineAndFilled);
    //write some text in it
    display.cmdSetColor(255,255,0, 0,0,0);
    display.cmdDrawText(37,74, "WELCOME", CFA10060::font8x8, CFA10060::bgTransparent);    
    display.cmdDrawText(58,64, "TO", CFA10060::font8x8, CFA10060::bgTransparent);    
    display.cmdDrawText(52,54, "THE", CFA10060::font8x8, CFA10060::bgTransparent);    
    display.cmdDrawText(33,44, "CFA10060", CFA10060::font8x8, CFA10060::bgTransparent);
    //wait for 4sec
    delay(4000);
    //fade blank display
    do_fade_blank();

    //show cursor / touchpad demo
    display.cmdFillSolidColor(50,50,50);
    //turn on the cursor
    display.cmdLCDCursor(CFA10060::cursorArrowNormal);
    //do the cursor position/update loop
    for (t = 0; t < 10000; t++)
    {
      //local vars
      CFA10060::Pads_t pads;
      char temps[8];
      static uint8_t cursor_type = 1; //=CFA10060::cursorArrowNormal
      static uint8_t lx = 64;
      static uint8_t ly = 64;
      
      //get cursor position & touch pad state
      display.cmdLCDCursor(x, y, pads);
      
      //check for touchpad button presses
      if (pads == CFA10060::Cancel)
        //cancel pressed, clear the display
        display.cmdFillSolidColor(50,50,50);
      if (pads == CFA10060::Enter)
      {
        //enter pressed, change cursor type
        cursor_type++;
        if (cursor_type > 6)
          cursor_type = 0;
        display.cmdLCDCursor(cursor_type);
      }

      //check is pointed position has changed
      if ((lx != x) || (ly != y))
      {
        //has changed, draw tracking line
        display.cmdSetColor(0,255,255, 0,0,0);
        display.cmdDrawLine(x, y, lx, ly);
        //update position text information
        display.cmdSetColor(255,255,255, 50,50,50);
        display.cmdDrawRectangle(0,0, (7*8),9, CFA10060::drawFilled);
        itoa(x, temps, 10);
        display.cmdDrawText(0,0, temps, CFA10060::font8x8, CFA10060::bgSolid);
        itoa(y, temps, 10);
        display.cmdDrawText((4*8),0, temps, CFA10060::font8x8, CFA10060::bgSolid);
      }
      //keep location for next loop
      lx = x;
      ly = y;
      
      if (!(t%100))
      {
        //draw screen countdown
        display.cmdSetColor(255,100,100, 50,50,50);
        itoa((10000-t)/100, temps, 10);
        display.cmdDrawRectangle(105,0, 127,9, CFA10060::drawFilled);
        display.cmdDrawText(108,0, temps, CFA10060::font8x8, CFA10060::bgSolid);      
      }
    }
    //turn off the cursor
    display.cmdLCDCursor(CFA10060::cursorOff);
    //finished cursor demo, fade blank display
    do_fade_blank();
    
    //draw a few bitmaps
    display.cmdDrawSDBMPOnLCD("img00.bmp");
    delay(3500);
    display.cmdDrawSDBMPOnLCD("img18.bmp");
    delay(3500);    
    display.cmdDrawSDBMPOnLCD("img08.bmp");
    delay(3500);    
    display.cmdDrawSDBMPOnLCD("img19.bmp");
    delay(3500);        
    display.cmdDrawSDBMPOnLCD("img04.bmp");
    delay(3500);
    //done
    do_fade_blank();
    
    //sprite example
    //draw bitmap containing sprites
    display.cmdDrawSDBMPOnLCD("icons.bmp");
    //save a sprite from it
    // the lightbulb icon is at pixel location 96,64
    display.cmdKeepSprite(0, 96,64, 32,32);
    //display a background bitmap
    display.cmdDrawSDBMPOnLCD("img07.bmp");
    //display the sprite on top
    // cmdStartSprite saves the image under the new sprite position first
    // so it can be drawn back when using the cmdMoveSprite command.
    display.cmdStartSprite(0, 60,94, 32,32);
    x_old = 60; y_old = 94;
    //quick delay
    delay(1000);
    //loop to draw the sprite moving across the display
    for (t = 0; t < 102; t++)
    {
      //calculate the Y position
      float y = 64-16+sin(t/(float)8)*32;
      //move the sprite from the old location to the new location
      display.cmdMoveSprite(0, x_old,y_old, t,y, 32,32);
      //save the location for the next loop
      x_old = t;
      y_old = y;
      //small delay
      delay(70);
    }
    //done
    delay(1000);
    do_fade_blank();
       
    //play the demo movie file
    display.cmdPlaySDMovieOnLCD("bris.vid");
    //done
    do_fade_blank();

    //loop back to the start of the demo
  }
  //we dont get this far
}



