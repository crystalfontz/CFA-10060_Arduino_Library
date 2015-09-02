#ifndef CFA10060LIB_H_
#define CFA10060LIB_H_

#include "Arduino.h"
#include "twi.h"
#include "Wire.h"
#include <SPI.h>

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
		This limitation does not apply to SPI.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Library settings

#define CFA10060_USE_I2C			/* if defined the I2C interface is used to communicate with the CFA10060 */
//#define CFA10060_USE_SPI			/* if defined the SPI interface is used to communicate with the CFA10060 */

#define CFA10060_SPI_SS_PIN		5	/* set the Arduino IO pin used for the CFA10060 SPI SS signal (5 is default on the Uno) */

#define CFA10006_SERIAL_MESSAGES	/* if defined enables runtime information to be written to serial out */
#define CFA10006_ERROR_MESSAGES		/* if defined enables error message text in serial out (uses 5342 bytes flash) */

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CFA10060 Commands
//System
#define CMD_PING									(0)
#define CMD_GET_VERSION								(1)
#define	CMD_SET_I2C_ADDRESS							(2)
#define	CMD_CHECK_AND_CLEAR_FILESYSTEM_ERRORS		(3)
//uSD card operations
#define CMD_GET_SD_CARD_VOLUME_LABEL				(4)
#define CMD_GET_SD_CARD_FREE_USED_SECTORS			(5)
#define CMD_GET_NUMBER_OF_FILES_IN_ROOT_DIR			(6)
#define CMD_GET_NAME_AND_SIZE_OF_FILE				(7)
#define CMD_FILE_OPEN								(8)
#define CMD_FILE_READ								(9)
#define CMD_FILE_WRITE						  		(10)
#define CMD_FILE_SEEK								(11)
#define CMD_FILE_TELL								(12)
#define CMD_FILE_CLOSE								(13)
#define CMD_FILE_DELETE								(14)
//LCD operations
#define CMD_GET_SET_BACKLIGHT_BRIGHTNESS			(15)
#define CMD_FILL_SCREEN_WITH_SOLID_COLOR			(16)
#define CMD_LCD_SET_COLOR							(17)
#define CMD_LCD_PIXEL								(18)
#define CMD_LCD_LINE								(19)
#define CMD_LCD_RECTANGLE							(20)
#define CMD_LCD_ROUNDED_RECTANGLE					(21)
#define CMD_LCD_CIRCLE								(22)
#define CMD_LCD_BITBLT								(23)
#define CMD_LCD_TEXT								(24)
#define CMD_LCD_CURSOR								(25)
#define CMD_LCD_SPRITE								(26)
//LCD <=> uSD card operations
#define CMD_SAVE_LCD_AS_BMP							(27)
#define CMD_PUSH_BMP_FROM_SD_CARD_TO_LCD			(28)
#define CMD_PUSH_MOVIE_FROM_SD_CARD_TO_LCD			(29)
#define CMD_PUSH_MOVIE_FRAME_FROM_SD_CARD_TO_LCD	(30)
#define CMD_PUSH_SPRITE_FROM_SD_CARD_TO_LCD			(31)
#define NUMBER_OF_COMMANDS							(32)

//Packet flags
#define CMD_NAK_RESPONSE_FLAG						(0x80)
#define CMD_ERR_RESPONSE_FLAG						(0x40)

//File modes for CMD_FILE_OPEN
#define FOPEN_READ									(0)		/* READ-ONLY, file must exist (initial file position = 0) */
#define FOPEN_CREATE_RESET_READ_WRITE				(1)		/* WRITE or read, create or reset on open (initial file position = 0) */
#define FOPEN_CREATE_PRESERVE_READ_WRITE			(2)		/* WRITE or read, create or preserve content on open (initial file position = EOF+1) */

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
#   warning warning WIRE library not used??
#   define MAXIMUM_DATA_LENGTH (TWI_BUFFER_LENGTH - 2)
#  endif
# else
#  ifdef BUFFER_LENGTH
#   warning warning TWI library not used??
#   define MAXIMUM_DATA_LENGTH (BUFFER_LENGTH - 2)
#  else
#   warning WIRE / TWI libraries not used??
#   define MAXIMUM_DATA_LENGTH (30)
#  endif
# endif
#endif

#ifdef CFA10060_USE_SPI
# define MAXIMUM_DATA_LENGTH 64
#endif

//Macros for serial messages
#ifdef CFA10006_SERIAL_MESSAGES
# define SPRINTF(...) serPrintFF(__VA_ARGS__)
#else
# define SPRINTF(...)
#endif

//library class
class CFA10060
{
public:
	//structs
	typedef struct
	{
		uint8_t command;
		uint8_t length;
		uint8_t data[MAXIMUM_DATA_LENGTH];
	} Transaction_t;

	typedef enum
	{
		cursorOff = 0,
		cursorArrowNormal,
		cursorText08,
		cursorText16,
		cursorArrowMove,
		cursorArrowWait,
		cursorWaitNoArrow
	} Cursors_t;

	typedef enum
	{
		NoState = 0,
		Enter,
		Cancel
	} Pads_t;

	//functions
	CFA10060();
	uint8_t init(void);
#ifdef CFA10060_USE_I2C
	uint8_t I2CIsBusy(void);
#endif
#ifdef CFA10060_USE_SPI
	uint8_t SPIIsBusy(void);
#endif
	inline uint8_t errorReported(void) {return haveError;}

	uint8_t cmdPing(char data[]);
	uint8_t cmdGetVersion(char retVersion[]);
#ifdef CFA10060_USE_I2C
	uint8_t cmdChangeI2CAddress(uint8_t newAddress);
#endif
	uint8_t cmdCheckAndClearFileSystemErrors(void);

	uint8_t cmdGetSDVolumeLabel(char retLabel[]);
	uint8_t cmdGetFreeUsedSectors(uint32_t &retUsed, uint32_t &retFree);
	uint8_t cmdGetNumFilesRootDir(uint16_t &retFileCount);
	uint8_t cmdGetFileDetails(uint16_t fileIndex, uint16_t &retIndex, uint32_t &retSize, char *retName);
	uint8_t cmdFileOpen(char fileName[], uint8_t mode, uint8_t retHandle);
	uint8_t cmdFileRead(uint8_t fileHandle, uint8_t length, char retData[], uint8_t &retLength);
	uint8_t cmdFileTell(uint8_t fileHandle, uint32_t &retPosition);
	uint8_t cmdFileSeek(uint8_t fileHandle, uint32_t position);
	uint8_t cmdFileClose(uint8_t fileHandle);
	uint8_t cmdFileWrite(uint8_t fileHandle, char data[], uint8_t length, uint8_t &retDataWritten);
	uint8_t cmdFileDelete(char fileName[]);

	uint8_t cmdSetBacklightBrightness(uint8_t brightness); //set
	uint8_t cmdGetBacklightBrightness(uint8_t &retBrighness); //get
	uint8_t cmdFillSolidColor(uint8_t R, uint8_t G, uint8_t B);
	uint8_t cmdSetColor(uint8_t fgR, uint8_t fgG, uint8_t fgB, uint8_t bgR, uint8_t bgG, uint8_t bgB);
	uint8_t cmdSetColor(uint8_t fgR, uint8_t fgG, uint8_t fgB);
	uint8_t cmdDrawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
	uint8_t cmdDrawPixel(uint8_t x, uint8_t y);
	uint8_t cmdDrawPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
	uint8_t cmdDrawRectangle(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t fillOption);
	uint8_t cmdDrawRoundedRectangle(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t radius, uint8_t fillOption);
	uint8_t cmdDrawCircle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint8_t fillOption);
	uint8_t cmdLCDBitBlt(uint8_t sourceX, uint8_t sourceY, uint8_t destX, uint8_t destY, uint8_t sizeX, uint8_t sizeY);
	uint8_t cmdDrawText(uint8_t sizeOption, uint8_t drawBackground, uint8_t x, uint8_t y, char text[]);

	uint8_t cmdLCDCursor(Cursors_t cursorType);
	uint8_t cmdLCDCursor(uint8_t cursorIndex);
	uint8_t cmdLCDCursor(uint8_t &retCursorX, uint8_t &retCursorY, Pads_t &retEnterCancel);
	uint8_t cmdLCDCursor(Cursors_t cursorType, uint8_t &retCursorX, uint8_t &retCursorY, Pads_t &retEnterCancel);

	uint8_t cmdKeepSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY);
	uint8_t cmdDrawSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY);
	uint8_t cmdStartSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY);
	uint8_t cmdMoveSprite(uint8_t spriteIndex, uint8_t oldX, uint8_t oldY, uint8_t newX, uint8_t newY, uint8_t sizeX, uint8_t sizeY);

	uint8_t cmdDrawSDBMPOnLCD(char fileName[]);
	uint8_t cmdSaveLCDToSDBMP(char fileName[]);
	uint8_t cmdPlaySDMovieOnLCD(char fileName[]);
	uint8_t cmdDrawSDMoveFrameToLCD(uint8_t fileHandle, uint32_t frameNumber);

private:
	//vars
#ifdef CFA10060_USE_I2C
	uint8_t			I2CAddress;
#endif
	Transaction_t	command;
	Transaction_t	response;
	uint8_t			lastCursorType;
	uint8_t			haveError;

	//functions
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
