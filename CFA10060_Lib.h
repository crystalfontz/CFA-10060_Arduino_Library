/*********************************************************
Crystalfontz CFA10060 Arduino interface library.

Crystalfontz: http://www.crystalfontz.com
Library Source: https://github.com/crystalfontz/CFA-10060_Arduino_Library

Distributed under the "Unlicense" software license.
See: http://unlicense.org/
**********************************************************/

#ifndef CFA10060LIB_H_
#define CFA10060LIB_H_

#include "Arduino.h"

#include <avr/pgmspace.h>
#include <HardwareSerial.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <WString.h>

/* NOTES:
	I2C Buffer Limitation:
		The standard Arduino TWI and Wire libraries default to a small(ish) buffer
		size of 32 bytes. The CFA10060 can use I2C packets larger than this.
		If larger packets are required, you'll need to edit one line in each of the
		two library header files (change to a value between 32 and 130 bytes):
			Arduino\hardware\arduino\avr\libraries\Wire\utility\twi.h
				#define TWI_BUFFER_LENGTH 130
			Arduino\hardware\arduino\avr\libraries\Wire\Wire.h
				#define BUFFER_LENGTH 130
				
		This limitation does not apply to the Arduino SPI library.
		Note however that the CFA10060's SPI maximum command length is 62 bytes.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Library settings

#define CFA10060_USE_I2C			/* if defined the I2C interface is used to communicate with the CFA10060 */
//#define CFA10060_USE_SPI			/* if defined the SPI interface is used to communicate with the CFA10060 */

#define CFA10060_SPI_SS_PIN		5	/* set the Arduino IO pin used for the CFA10060 SPI SS signal (5 is default on the Uno) */

#define CFA10006_SERIAL_MESSAGES	/* if defined enables runtime information to be written to serial out */
//#define CFA10006_ERROR_MESSAGES	/* if defined enables error message text in serial out (uses 5342 bytes flash) */

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Check Settings
#ifdef CFA10060_USE_I2C
# ifdef CFA10060_USE_SPI
#  error CFA10060 - USE I2C *OR* SPI, NOT BOTH!
# endif
#endif
#ifndef CFA10060_USE_I2C
# ifndef CFA10060_USE_SPI
#  error CFA10060 - NO INTERFACE SELECTED, USE I2C OR SPI!
# endif
#endif

//include required serial IO libs
#ifdef CFA10060_USE_I2C
# include "Wire.h"
#endif
#ifdef CFA10060_USE_SPI
//#include "twi.h"
# include <SPI.h>
#endif

//Maximum data buffer length (see NOTE above)
#ifdef CFA10060_USE_I2C
# ifdef TWI_BUFFER_LENGTH
#  ifdef BUFFER_LENGTH
#   if (TWI_BUFFER_LENGTH >= BUFFER_LENGTH)
#    define MAXIMUM_DATA_LENGTH (BUFFER_LENGTH - 2)
#   else
#    define MAXIMUM_DATA_LENGTH (TWI_BUFFER_LENGTH - 2)
#   endif
#  else
#   warning warning WIRE library not used ? ?
#   define MAXIMUM_DATA_LENGTH (TWI_BUFFER_LENGTH - 2)
#  endif
# else
#  ifdef BUFFER_LENGTH
#   warning TWI library not used ? ?
#   define MAXIMUM_DATA_LENGTH (BUFFER_LENGTH - 2)
#  else
#   warning WIRE / TWI libraries not used ? ?
#   define MAXIMUM_DATA_LENGTH (30)
#  endif
# endif
#endif

#ifdef CFA10060_USE_SPI
# define MAXIMUM_DATA_LENGTH 64
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//library class
class CFA10060
{
public:
	//public structures
	typedef enum
	{
		cursorOff = 0,				//display no cursor
		cursorArrowNormal,			//display an arrow cursor
		cursorText08,				//display text selection I bar for the 8x8 font
		cursorText16,				//display text selection I bar for the 12x16 font
		cursorArrowMove,			//display move/drag cursor
		cursorArrowWait,			//display arrow cursor with hourglass
		cursorWaitNoArrow			//display hourglass cursor
	} Cursors_t;

	typedef enum
	{
		NoState = 0,				//returned when neither enter or cancel pads are touched
		Enter,						//returned when the enter pad is touched
		Cancel						//returned when the cancel pad is touched
	} Pads_t;

	typedef enum
	{
		fileRead = 0,				//open the file read only
		fileCreateResetReadWrite,	//open a new file for reading and writing
		fileCreatePreserveReadWrite	//open an existing file for reading and writing
	} FileOpen_t;
	
	typedef enum
	{
		drawOutline = 0,			//outline is in foreground color
		drawFilled,					//fill is in background color
		drawOutlineAndFilled		//outline is in foreground color, fill is in background color
	} Draw_t;
	
	typedef enum
	{
		font8x8 = 0,				//simple 8x8 pixel font (small)
		font12x16					//simple 12x16 pixel font (large)
	} Font_t;
	
	typedef enum
	{
		bgTransparent = 0,			//no background is drawn under the characters
		bgSolid						//solid background in background color is drawn under the characters
	} FontBackground_t;

	typedef struct
	{
		uint8_t		R;
		uint8_t		G;
		uint8_t		B;
	} Color_t;
		
	//public functions
	CFA10060();
	
	//initialize the library (must be run first)
	uint8_t init(void);
	//check if any errors have been reported
	inline uint8_t errorReported(void) {return haveError;}

	//==========================================================
	//========= CFA10060 commands ==============================

	/*
		cmdPing sends data to the CFA10060, waits for a reply
		and then checks the returned ping data against the sent data.
		If the data matches, the function returns true (1).
	*/
	uint8_t cmdPing(char data[]);

	/*
		cmdGetVersion requests hardware and firmware version information
		from the CFA10060. It is returned in retVersion (max
		length of 18 chars)
		The returned value is true (1) if successful.
	*/
	uint8_t cmdGetVersion(char retVersion[]);

#ifdef CFA10060_USE_I2C
	/*
		cmdChangeI2CAddress requests the CFA10060 change its I2C address
		to the specified newAddress. The new address is saved in EEPROM.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdChangeI2CAddress(uint8_t newAddress);
#endif

	/*
		cmdCheckAndClearFileSystemErrors prints any pending CFA10060 error
		messages to the serial console (if enabled), then clears the error
		buffer.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdCheckAndClearFileSystemErrors(void);

	/*
		cmdGetSDVolumeLabel reads the inserted microSD cards volume label
		and returns it in retLabel.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdGetSDVolumeLabel(char retLabel[]);

	/*
		cmdGetFreeUsedSectors returns the number of used, and the number of
		free sectors on the inserted microSD card. A sector is normally
		512 byts in size.
		The returned value is true (1) if successful.
		This command may take sometime to return (1-10 seconds).
	*/
	uint8_t cmdGetFreeUsedSectors(uint32_t &retUsed, uint32_t &retFree);

	/*
		cmdGetNumFilesRootDir returns in retFileCount the number of files
		in the microSD card's root directory.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdGetNumFilesRootDir(uint16_t &retFileCount);

	/*
		cmdGetFileDetails returns size and name information of the
		specified file at fileIndex on the microSD card.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdGetFileDetails(uint16_t fileIndex, uint16_t &retIndex, uint32_t &retSize, char *retName);

	/*
		cmdFileOpen opens the specified fileName on the mciroSD card
		in mode (see FileOpen_t for file modes), and returns the
		file handle in retHandle.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFileOpen(char fileName[], FileOpen_t mode, uint8_t &retHandle);

	/*
		cmdFileRead reads length data bytes from the file previously opened
		by cmdFileOpen() into retData. retLength returns the amount of data
		actually read. If the returned retLengthis not equal to the requested
		length, then the end of the file has been reached, or an error has occoured.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFileRead(uint8_t fileHandle, uint8_t length, char retData[], uint8_t &retLength);

	/*
		cmdFileWrite writes length data bytes from data to the specified file.
		retDataWritten returns the amount of data actually written to the file.	
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFileWrite(uint8_t fileHandle, char data[], uint8_t length, uint8_t &retDataWritten);

	/*
		cmdFileTell returns in retPosition the current file pointer location for
		the file specifed by fileHandle.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFileTell(uint8_t fileHandle, uint32_t &retPosition);

	/*
		cmdFileSeek changes the current file pointer location for fileHandle to
		the specified absolute position.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFileSeek(uint8_t fileHandle, uint32_t position);

	/*
		cmdFileClose closes the opened file specified by fileHandle.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFileClose(uint8_t fileHandle);

	/*
		cmdFileDelete removes the specified file from the filesystem.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFileDelete(char fileName[]);

	/*
		cmdSetBacklightBrightness sets the LCD backlight level to percent
		brightness (0-100 values valid).
		The returned value is true (1) if successful.
	*/
	uint8_t cmdSetBacklightBrightness(uint8_t brightness);

	/*
		cmdGetBacklightBrightness returns the current backlight brightness in
		percent.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdGetBacklightBrightness(uint8_t &retBrighness);

	/*
		cmdFillSolidColor fills the LCD with the specified R,G,B color.
		Valid R,G,B values are 0-255.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdFillSolidColor(uint8_t R, uint8_t G, uint8_t B);
	uint8_t cmdFillSolidColor(Color_t color);

	/*
		cmdSetColor sets the foreground and background colors to be used in
		following LCD commands.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdSetColor(uint8_t fgR, uint8_t fgG, uint8_t fgB, uint8_t bgR, uint8_t bgG, uint8_t bgB);
	uint8_t cmdSetColor(Color_t fgColor, Color_t bgColor);

	/*
		cmdSetColor sets the foreground color to be used in
		following LCD commands.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdSetColor(uint8_t fgR, uint8_t fgG, uint8_t fgB);

	/*
		cmdDrawLine draws a line on the LCD from the start x,y pixel location to
		the end x,y pixel location in the color set by the cmdSetColor() function.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);

	/*
		cmdDrawPixel draws a pixel on the LCD at the specified x,y pixel location in
		the color set by the cmdSetColor() function.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawPixel(uint8_t x, uint8_t y);

	/*
		cmdDrawPixel draws a pixel on the LCD at the specified x,y pixel location in
		the R,G,B color specified.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);

	/*
		cmdDrawRectangle draws a rectangle on the LCD at the specified start and end
		x,y pixel locations. See Draw_t for information on draw modes.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawRectangle(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, Draw_t drawOption);
	
	/*
		cmdDrawRoundedRectangle draws a rounded rectangle on the LCD at the specified
		start and end x,y pixel locations with the specified corner radius.
		See Draw_t for information on draw modes.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawRoundedRectangle(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t radius, Draw_t drawOption);
	
	/*
		cmdDrawCircle draws a circle on the LCD at the specified center x,y pixel
		location with the specified radius.	See Draw_t for information on draw modes.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawCircle(uint8_t centerX, uint8_t centerY, uint8_t radius, Draw_t drawOption);
	
	/*
		cmdLCDBitBlt copies the currently displayed LCD image source area to the
		specified destination area.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdLCDBitBlt(uint8_t sourceX, uint8_t sourceY, uint8_t destX, uint8_t destY, uint8_t sizeX, uint8_t sizeY);
	
	/*
		cmdDrawText displays the specified text on the LCD at the specified x,y location.
		See Font_t and FontBackground_t for information on those options.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawText(uint8_t x, uint8_t y, char text[], Font_t sizeOption, FontBackground_t backgroundOption);

	/*
		cmdLCDCursor displays the touchpad curor in the specified style (or hides it).
		The returned value is true (1) if successful.
	*/
	uint8_t cmdLCDCursor(Cursors_t cursorType);

	/*
		cmdLCDCursor displays the touchpad curor in the specified style (or hides it).
		The returned value is true (1) if successful.
	*/
	uint8_t cmdLCDCursor(uint8_t cursorIndex);

	/*
		cmdLCDCursor returns the current x,y pixel location of the touchpad cursor, and
		the	status of the enter/cancel pads.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdLCDCursor(uint8_t &retCursorX, uint8_t &retCursorY, Pads_t &retEnterCancel);

	/*
		cmdLCDCursor displays the touchpad curor in the specified style (or hides it),
		and also returns the current x,y pixel location of the touchpad cursor &
		the	status of the enter/cancel pads.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdLCDCursor(Cursors_t cursorType, uint8_t &retCursorX, uint8_t &retCursorY, Pads_t &retEnterCancel);

	/*
		cmdKeepSprite saves the image displayed at the specified x,y position of
		sizeX,sizeY (1x1 to 32x32 pixel size valid) into sprite
		position spriteIndex (0-3 valid).
		The returned value is true (1) if successful.
	*/
	uint8_t cmdKeepSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY);

	/*
		cmdDrawSprite draws a previously saved sprite to the specified x,y pixel location.
		Pixel values of R=4,G=4,B=4 are transparent.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY);

	/*
		cmdStartSprite saves the image under the specified x,y pixel location to
		spriteIndex+1, then draws sprite at spriteIndex to the same x,y location.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdStartSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY);

	/*
		cmdMoveSprite moves a previously started/moved sprite from oldX,oldY pixel
		location to newX,newY. 
		The returned value is true (1) if successful.
	*/
	uint8_t cmdMoveSprite(uint8_t spriteIndex, uint8_t oldX, uint8_t oldY, uint8_t newX, uint8_t newY, uint8_t sizeX, uint8_t sizeY);

	/*
		cmdDrawSDBMPOnLCD draws the specified BMP format image contained on
		the microSD card to the LCD. 
		The BMP file must be Windows format, 128x128 pixels in size, and
		24bit color.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawSDBMPOnLCD(char fileName[]);

	/*
		cmdSaveLCDToSDBMP saves the current LCD image to the specified BMP file
		on the microSD card. The created BMP file will be in Windows format,
		128x128 pixels in size, and	24bit color.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdSaveLCDToSDBMP(char fileName[]);

	/*
		cmdPlaySDMovieOnLCD plays the specified video file located on the microSD card
		to the LCD. See CFA10060 documention for video file format.
		The video file will be played until end of file is reached.
		The returned value is true (1) if successful.
	*/
	uint8_t cmdPlaySDMovieOnLCD(char fileName[]);

	/*
	cmdDrawSDMoveFrameToLCD draws the single specified frame number of the video file
	to the LCD. See CFA10060 documention for video file format.
	Movie file must have been opened by cmdFileOpen() first.
	The returned value is true (1) if successful.
	*/
	uint8_t cmdDrawSDMoveFrameToLCD(uint8_t fileHandle, uint32_t frameNumber);

	//==========================================================
	//==========================================================

private:
	//private structures
	typedef struct
	{
		uint8_t command;
		uint8_t length;
		uint8_t data[MAXIMUM_DATA_LENGTH];
	} Transaction_t;
	
	//private variables
#ifdef CFA10060_USE_I2C
	uint8_t			I2CAddress;
#endif
	Transaction_t	command;
	Transaction_t	response;
	uint8_t			lastCursorType;
	uint8_t			haveError;

	//functions
	uint8_t isBusy(void);
#ifdef CFA10060_USE_I2C
	uint8_t I2CSendCommandGetResponse(Transaction_t *command, Transaction_t *response, uint8_t receiveDataLength);
	uint8_t I2CSearchForAddress(void);
#endif
#ifdef CFA10060_USE_SPI
	uint8_t SPISendCommandGetResponse(Transaction_t *command, Transaction_t *response, uint8_t receiveDataLength);
	void SPIClear(void);
#endif
	uint8_t checkAndClearFileSystemErrors(void);

#ifdef CFA10006_SERIAL_MESSAGES
	void serPrintFF(const __FlashStringHelper *fmt, ...);
	void serialPrintP(const char flash_string[]);
#endif

};

#endif
