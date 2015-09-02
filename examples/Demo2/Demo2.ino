*********************************************************
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

#include <CFA10060_Lib.h>
#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>

//the CFA10060 device/library
CFA10060 display;

//setup function
void setup()
{
	delay(500);                             //short sleep to stop debugging reset errors
	Serial.begin(115200);                   //start serial at 115200 baud
	Serial.println("Doing setup...");
#ifdef CFA10060_USE_I2C                   /* defined in CFA10060Lib.h */
	Wire.begin();	          		  //use the I2C bus if selected
#endif
#ifdef CFA10060_USE_SPI                   /* defined in CFA10060Lib.h */
	SPI.begin();	                          //use the SPI interface if selected
#endif  
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
		uint32_t			t;
		uint8_t				filehandle;
		uint8_t				len, written;
		uint8_t				c;
		uint8_t				x, y;
		CFA10060::Pads_t	pads;
		char				temps[16];

		//first up, display the CF intro banner
		display.cmdDrawSDBMPOnLCD("cfintro.bmp");
		//wait for 2sec
		delay(2000);
		//fade blank display
		do_fade_blank();

		//do file write speed test with LCD counter
		display.cmdSetColor(255, 255, 255, 0, 0, 0);
		display.cmdDrawText(24, 110, "FILE WRITE", CFA10060::font8x8, CFA10060::bgSolid);
		display.cmdDrawText(24, 100, "SPEED TEST", CFA10060::font8x8, CFA10060::bgSolid);
		delay(750);
		if (display.cmdFileOpen("write.tst", CFA10060::fileCreateResetReadWrite, filehandle))
		{
			//file opened ok
			display.cmdDrawText(8, 80, "Writing 100KB", CFA10060::font8x8, CFA10060::bgSolid);
			for (t = 0; t < 6250; t++) // 100,000 / 16 = 6250
			{
				//write 16 bytes to the file
				display.cmdFileWrite(filehandle, "thisis16bytes...", 16, len);
#ifdef CFA10060_USE_SPI
				delay(30);  //need a small delay if using SPI
#endif
				if ((t % 62) == 0)
				{
					//progress display
					itoa(t / 62, temps, 10);
					display.cmdDrawText(8, 70, temps, CFA10060::font8x8, CFA10060::bgSolid);
					display.cmdDrawText(32, 70, "%", CFA10060::font8x8, CFA10060::bgSolid);
				}
			}
			//done
			display.cmdDrawText(8, 70, "done.", CFA10060::font8x8, CFA10060::bgSolid);
			display.cmdFileClose(filehandle);
		}
		else
		{
			//file open failed
			display.cmdDrawText(8, 80, "fileopen() error", CFA10060::font8x8, CFA10060::bgSolid);
		}
		delay(3000);

		//fade blank display
		do_fade_blank();

		//do file read speed test
		display.cmdSetColor(255,255,255, 0,0,0);
		display.cmdDrawText(24, 110, "FILE READ", CFA10060::font8x8, CFA10060::bgSolid);
		display.cmdDrawText(24, 100, "SPEED TEST", CFA10060::font8x8, CFA10060::bgSolid);
		delay(750);
		if (display.cmdFileOpen("bris.vid", CFA10060::fileRead, filehandle))
		{
			//file opened ok
			display.cmdDrawText(8, 80, "Reading 100KB", CFA10060::font8x8, CFA10060::bgSolid);
			for (t = 0; t < 6250; t++) // 100,000 / 16 = 6250
			{
				//read 16 bytes from the file
				display.cmdFileRead(filehandle, 16, temps, len);
#ifdef CFA10060_USE_SPI
				delay(10);  //need a small delay if using SPI
#endif
				if ((t % 62) == 0)
				{
					//progress display
					itoa(t / 62, temps, 10);
					display.cmdDrawText(8, 70, temps, CFA10060::font8x8, CFA10060::bgSolid);
					display.cmdDrawText(32, 70, "%", CFA10060::font8x8, CFA10060::bgSolid);
				}
			}
			//done
			display.cmdDrawText(8, 70, "done.", CFA10060::font8x8, CFA10060::bgSolid);
			display.cmdFileClose(filehandle);
		}
		else
		{
			//file open failed
			display.cmdSetColor(255, 40, 40, 0, 0, 0);
			display.cmdDrawText(0, 80, "fileopen() error", CFA10060::font8x8, CFA10060::bgSolid);
		}
		delay(3000);

		//fade blank display
		do_fade_blank();

		//read a text file and write it to the display
		display.cmdSetColor(255, 255, 255, 0, 0, 0);
		display.cmdDrawText(10, 118, "TEXT FILE TEST", CFA10060::font8x8, CFA10060::bgSolid);
		delay(750);
		if (display.cmdFileOpen("demo2.txt", CFA10060::fileRead, filehandle))
		{
			//file opened ok
			for (t = 0; t < 8; t++)
			{
				//read 16 characters at a time and display them as a line of text
				//128 pixels wide lcd / 8 pixel wide font = 16 characters across the LCD
				//128 pixels high lcd / 10 pixels high font = 11 characters down the LCD
				for (y = 0; y < 108; y += 10)
				{
					display.cmdFileRead(filehandle, 16, temps, len);
					display.cmdDrawText(0, 108 - y, temps, CFA10060::font8x8, CFA10060::bgSolid);
				}
				delay(1500);
			}
			//done
			display.cmdDrawText(0, 0, "done.           ", CFA10060::font8x8, CFA10060::bgSolid);
			display.cmdFileClose(filehandle);
		}
		else
		{
			//file open failed
			display.cmdSetColor(255, 40, 40, 0, 0, 0);
			display.cmdDrawText(0, 80, "fileopen() error", CFA10060::font8x8, CFA10060::bgSolid);
		}
		delay(3000);


		//display pointer arrow, and write pointer location to a text file
		display.cmdSetColor(255, 255, 255, 0, 0, 0);
		display.cmdDrawText(4, 118, "CURSOR POSITION", CFA10060::font8x8, CFA10060::bgSolid);
		display.cmdDrawText(4, 108, "FILE WRITE TEST", CFA10060::font8x8, CFA10060::bgSolid);
		delay(750);
		if (display.cmdFileOpen("csrpos.txt", CFA10060::fileCreateResetReadWrite, filehandle))
		{
			//file opened ok
			display.cmdLCDCursor(CFA10060::cursorArrowNormal);
			for (t = 0; t < 100; t++)
			{
				//read the cursor position
				display.cmdLCDCursor(x, y, pads);
				//write position to the file
				display.cmdFileWrite(filehandle, "x=", 2, written);
				itoa(x, temps, 10);
				len = strlen(temps);
				display.cmdFileWrite(filehandle, temps, len, written);
				display.cmdFileWrite(filehandle, " y=", 3, written);
				itoa(y, temps, 10);
				len = strlen(temps);
				display.cmdFileWrite(filehandle, temps, len, written);
				display.cmdFileWrite(filehandle, "\n", 1, written);

				//display timer countdown
				itoa(100-t, temps, 10);
				display.cmdSetColor(255,255,255, 0,0,0);
				display.cmdDrawRectangle(0,0, (4*8),10, CFA10060::drawFilled);
				display.cmdDrawText(0, 0, temps, CFA10060::font8x8, CFA10060::bgSolid);
				delay(200);
			}
			//done
			display.cmdLCDCursor(CFA10060::cursorOff);
			display.cmdDrawText(0, 0, "done.           ", CFA10060::font8x8, CFA10060::bgSolid);
			display.cmdFileClose(filehandle);
		}
		else
		{
			//file open failed
			display.cmdSetColor(255, 40, 40, 0, 0, 0);
			display.cmdDrawText(0, 80, "fileopen() error", CFA10060::font8x8, CFA10060::bgSolid);
		}
		delay(3000);

		//clear out any errors
		display.cmdCheckAndClearFileSystemErrors();

		//loop back to the start of the demo
	}
	//we dont get this far
}



