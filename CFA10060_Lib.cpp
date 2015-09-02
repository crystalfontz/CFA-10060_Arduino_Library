#include "CFA10060Lib.h"

#include <avr/pgmspace.h>
#include <HardwareSerial.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <WString.h>
#include <SPI.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

//See CFA10060Lib.h for library settings.

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CFA10006_ERROR_MESSAGES
const char err_Str_000[] PROGMEM = "NO_ERROR";
const char err_Str_001[] PROGMEM = "ADDCLUSTER_LOADFAT_EOC_FAIL";
const char err_Str_002[] PROGMEM = "ADDCLUSTER_LOADFAT_FAIL";
const char err_Str_003[] PROGMEM = "ADDCLUSTER_NEXTCLUSTER_FAIL";
const char err_Str_004[] PROGMEM = "ADDCLUSTER_NO_SPACE_AVAILABLE";
const char err_Str_005[] PROGMEM = "BMPTOLCD_CANT_REWIND_FILE";
const char err_Str_006[] PROGMEM = "BMPTOLCD_FILE_NOT_OPEN";
const char err_Str_007[] PROGMEM = "BMPTOLCD_INVALID_FILE_SIZE";
const char err_Str_008[] PROGMEM = "BMPTOLCD_MOVETONEXTSECTOR_DATA_FAIL";
const char err_Str_009[] PROGMEM = "BMPTOLCD_MOVETONEXTSECTOR_TRAILER_FAIL";
const char err_Str_010[] PROGMEM = "BMPTOLCD_STARTBLOCKREAD_DATA_FAIL";
const char err_Str_011[] PROGMEM = "BMPTOLCD_STARTBLOCKREAD_HEADER_FAIL";
const char err_Str_012[] PROGMEM = "BMPTOLCD_STARTBLOCKREAD_TRAILER_FAIL";
const char err_Str_013[] PROGMEM = "BMPTOLCD_USD_BLOCK_LENGTH_R1_DATA_FAIL";
const char err_Str_014[] PROGMEM = "BMPTOLCD_USD_BLOCK_LENGTH_R1_HEADER_FAIL";
const char err_Str_015[] PROGMEM = "BMPTOLCD_USD_BLOCK_LENGTH_R1_TRAILER_FAIL";
const char err_Str_016[] PROGMEM = "CHECKR1_RESPONSE_HAS_ERRORS";
const char err_Str_017[] PROGMEM = "CHECKR1_SPIGETRESPONSE_FAIL";
const char err_Str_018[] PROGMEM = "CLEARCLUSTER_FAT_BUFFER_WRITE_A_FAIL";
const char err_Str_019[] PROGMEM = "CLEARCLUSTER_FAT_BUFFER_WRITE_B_FAIL";
const char err_Str_020[] PROGMEM = "CREATEFILE_ALLOCATE_DIRECTORY_FAIL";
const char err_Str_021[] PROGMEM = "DELETE_FOPEN_FAIL";
const char err_Str_022[] PROGMEM = "DELETE_RESET_FILE_FAIL";
const char err_Str_023[] PROGMEM = "FAT16_END_OF_DIRECTORY_FAIL";
const char err_Str_024[] PROGMEM = "FAT32_ADD_END_OF_DIRECTORY_FAIL";
const char err_Str_025[] PROGMEM = "FCLOSE_NOT_OPEN_CANT_CLOSE";
const char err_Str_026[] PROGMEM = "FCLOSE_SYNCDIR_FAIL";
const char err_Str_027[] PROGMEM = "FGETC_FILE_NOT_OPEN";
const char err_Str_028[] PROGMEM = "FGETC_READ_BEYOND_END_OF_FILE";
const char err_Str_029[] PROGMEM = "FGETC_READSECTOR_FAIL";
const char err_Str_030[] PROGMEM = "FILENAME_INVALID_FIRST_CHARACTER";
const char err_Str_031[] PROGMEM = "FILENAME_INVALID_LENGTH";
const char err_Str_032[] PROGMEM = "FILENAME_MORE_THAN_ONE_DOT";
const char err_Str_033[] PROGMEM = "FINDCLUSTER_END_OF_DISK_FAIL";
const char err_Str_034[] PROGMEM = "FINDCLUSTER_LOADFAT_FAIL";
const char err_Str_035[] PROGMEM = "FINDCLUSTER_READSECTOR_FAIL";
const char err_Str_036[] PROGMEM = "FINDFILE_FILE_NOT_FOUND";
const char err_Str_037[] PROGMEM = "FINDFILE_NEXTDIRENTRY_FAIL";
const char err_Str_038[] PROGMEM = "FINDFILE_STARTDIRSCAN_FAIL";
const char err_Str_039[] PROGMEM = "FLUSH_DIR_BUFFER_WRITE_FAIL";
const char err_Str_040[] PROGMEM = "FLUSH_FAT_BUFFER_WRITE_FAIL";
const char err_Str_041[] PROGMEM = "FLUSH_WRITE_BUFFER_WRITE_FAIL";
const char err_Str_042[] PROGMEM = "FLUSHDIR_SYNCDIR_FAIL";
const char err_Str_043[] PROGMEM = "FOPEN_APPEND_SEEK_TO_END_FAIL";
const char err_Str_044[] PROGMEM = "FOPEN_CANT_OPEN_READ_ONLY_FOR_WRITE";
const char err_Str_045[] PROGMEM = "FOPEN_CREATE_FILE_FOR_WRITE_FAIL";
const char err_Str_046[] PROGMEM = "FOPEN_FILE_NOT_FOUND";
const char err_Str_047[] PROGMEM = "FOPEN_INVALID_MODE";
const char err_Str_048[] PROGMEM = "FOPEN_INVALID_NAME";
const char err_Str_049[] PROGMEM = "FOPEN_NO_FILE_HANDLE_AVAILABLE";
const char err_Str_050[] PROGMEM = "FOPEN_RESET_FILE_FOR_WRITE_FAIL";
const char err_Str_051[] PROGMEM = "FPUTBUFF_FPUTC_FAIL";
const char err_Str_052[] PROGMEM = "FPUTC_ADDCLUSTER_FIRST_FAIL";
const char err_Str_053[] PROGMEM = "FPUTC_ADDCLUSTER_NEXT_FAIL";
const char err_Str_054[] PROGMEM = "FPUTC_FILE_NOT_OPEN_FOR_WRITE";
const char err_Str_055[] PROGMEM = "FPUTC_INCREMENTFILEPOSITION_FAIL";
const char err_Str_056[] PROGMEM = "FPUTC_READSECTOR_FAIL";
const char err_Str_057[] PROGMEM = "FPUTS_FPUTC_FAIL";
const char err_Str_058[] PROGMEM = "FSEEK_FILE_NOT_OPEN";
const char err_Str_059[] PROGMEM = "FSEEK_NEXTCLUSTER_FAIL";
const char err_Str_060[] PROGMEM = "FSEEK_SEEK_BEYOND_END_OF_FILE";
const char err_Str_061[] PROGMEM = "FTELL_FILE_NOT_OPEN";
const char err_Str_062[] PROGMEM = "GET_VOLUME_FILE_NOT_FOUND";
const char err_Str_063[] PROGMEM = "GETDISKUSAGE_FIRST_READSECTOR_FAIL";
const char err_Str_064[] PROGMEM = "GETDISKUSAGE_NEXT_READSECTOR_FAIL";
const char err_Str_065[] PROGMEM = "GETEMPTYDIR_NEXTDIRENTRY_FAIL";
const char err_Str_066[] PROGMEM = "GETEMPTYDIR_STARTDIRSCAN_FAIL";
const char err_Str_067[] PROGMEM = "GETFILECOUNT_NEXTDIRENTRY_FAIL";
const char err_Str_068[] PROGMEM = "GETFILECOUNT_STARTDIRSCAN_FAIL";
const char err_Str_069[] PROGMEM = "GETFILENAME_FILE_NOT_FOUND";
const char err_Str_070[] PROGMEM = "GETFILENAME_NEXTDIRENTRY_FAIL";
const char err_Str_071[] PROGMEM = "GETFILENAME_STARTDIRSCAN_FAIL";
const char err_Str_072[] PROGMEM = "GETFILESIZE_FILE_NOT_OPEN";
const char err_Str_073[] PROGMEM = "GETNXTDIR_16_END_OF_DIRECTORY_FAIL";
const char err_Str_074[] PROGMEM = "GETNXTDIR_16_READSECTOR_FAIL";
const char err_Str_075[] PROGMEM = "GETNXTDIR_32_ADD_CLUSTER_TO_DIR_FAIL";
const char err_Str_076[] PROGMEM = "GETNXTDIR_32_ADDCLUSTER_FAIL";
const char err_Str_077[] PROGMEM = "GETNXTDIR_32_CLEARCLUSTER_FAIL";
const char err_Str_078[] PROGMEM = "GETNXTDIR_32_END_OF_DIRECTORY_FAIL";
const char err_Str_079[] PROGMEM = "GETNXTDIR_32_MOVETONEXTSECTOR_A_FAIL";
const char err_Str_080[] PROGMEM = "GETNXTDIR_32_MOVETONEXTSECTOR_B_FAIL";
const char err_Str_081[] PROGMEM = "GETPART1SECTORFROMMBR_READSECTOR_FAIL";
const char err_Str_082[] PROGMEM = "GETVOLUME_FILE_NOT_FOUND";
const char err_Str_083[] PROGMEM = "GETVOLUME_NEXTDIRENTRY_FAIL";
const char err_Str_084[] PROGMEM = "GETVOLUME_STARTDIRSCAN_FAIL";
const char err_Str_085[] PROGMEM = "LCDFRAME_MOVETONEXTSECTOR_FAIL";
const char err_Str_086[] PROGMEM = "LCDFRAME_STARTBLOCKREAD_FAIL";
const char err_Str_087[] PROGMEM = "LCDFRAME_USD_BLOCK_LENGTH_R1_FAIL";
const char err_Str_088[] PROGMEM = "LCDTOBMP_FILE_NOT_OPEN_FOR_WRITE";
const char err_Str_089[] PROGMEM = "LCDTOBMP_FPUTC_HEADER_FAIL";
const char err_Str_090[] PROGMEM = "LCDTOBMP_FPUTC_DATA_FAIL";
const char err_Str_091[] PROGMEM = "LCDTOBMP_FPUTC_PAD_FAIL";
const char err_Str_092[] PROGMEM = "LOADFAT_READSECTOR_FAIL";
const char err_Str_093[] PROGMEM = "MOVIEFRAMETOLCD_FILE_NOT_OPEN";
const char err_Str_094[] PROGMEM = "MOVIEFRAMETOLCD_FSEEK_FAIL";
const char err_Str_095[] PROGMEM = "MOVIEFRAMETOLCD_INVALID_FRAME";
const char err_Str_096[] PROGMEM = "MOVIEFRAMETOLCD_LCDFRAME_FAIL";
const char err_Str_097[] PROGMEM = "MOVIETOLCD_FILE_NOT_OPEN";
const char err_Str_098[] PROGMEM = "MOVIETOLCD_LCDFRAME_FAIL";
const char err_Str_099[] PROGMEM = "NEXTCLUSTER_END_OF_CHAIN_FAIL";
const char err_Str_100[] PROGMEM = "NEXTCLUSTER_END_OF_DISK_FAIL";
const char err_Str_101[] PROGMEM = "NEXTCLUSTER_LOADFAT_FAIL";
const char err_Str_102[] PROGMEM = "READBPB_FAT12_NOT_SUPPORTED";
const char err_Str_103[] PROGMEM = "READBPB_INVALID_SECTOR";
const char err_Str_104[] PROGMEM = "READBPB_INVALID_SIGNATURE";
const char err_Str_105[] PROGMEM = "READBPB_READSECTOR_FAIL";
const char err_Str_106[] PROGMEM = "READSECTOR_CMD16_SET_BLOCKLEN_FAIL";
const char err_Str_107[] PROGMEM = "READSECTOR_STARTBLOCKREAD_FAIL";
const char err_Str_108[] PROGMEM = "READSECTOR_WRITESECTOR_FAIL";
const char err_Str_109[] PROGMEM = "RECLAIM_LOADFAT_FAIL";
const char err_Str_110[] PROGMEM = "RECLAIM_NO_FIRST_LINK";
const char err_Str_111[] PROGMEM = "RESET_DELETE_BAD_FILE_HANDLE";
const char err_Str_112[] PROGMEM = "RESET_DELETE_CLOSE_FAIL";
const char err_Str_113[] PROGMEM = "RESET_DELETE_READSECTOR_FAIL";
const char err_Str_114[] PROGMEM = "RESET_DELETE_RECLAIM_FAIL";
const char err_Str_115[] PROGMEM = "SPIGETRESPONSE_BIT7_ZERO_FAIL";
const char err_Str_116[] PROGMEM = "SPRITETOLCD_FGETC_FAIL";
const char err_Str_117[] PROGMEM = "SPRITETOLCD_FILE_NOT_OPEN";
const char err_Str_118[] PROGMEM = "SPRITETOLCD_FSEEK_FAIL";
const char err_Str_119[] PROGMEM = "STARTBLOCKREAD_CHECKR1_FAIL";
const char err_Str_120[] PROGMEM = "STARTBLOCKREAD_ERROR_WAITING_FOR_TOKEN";
const char err_Str_121[] PROGMEM = "STARTBLOCKREAD_TIMEOUT_WAITING_FOR_TOKEN";
const char err_Str_122[] PROGMEM = "SYNCDIR_FILE_NOT_OPEN";
const char err_Str_123[] PROGMEM = "SYNCDIR_READSECTOR_FAIL";
const char err_Str_124[] PROGMEM = "USDINIT_CMD8_SEND_IF_COND_ERROR_BIT_SET_FAIL";
const char err_Str_125[] PROGMEM = "USDINIT_CMD8_SEND_IF_COND_NO_RESPONSE_FAIL";
const char err_Str_126[] PROGMEM = "USDINIT_GETPART1SECTORFROMMBR_FAIL";
const char err_Str_127[] PROGMEM = "USDINIT_GO_IDLE_STATE_NO_RESPONSE_FAIL";
const char err_Str_128[] PROGMEM = "USDINIT_NO_CARD_IN_SOCKET";
const char err_Str_129[] PROGMEM = "USDINIT_NO_IDLE_STATE_READBACK";
const char err_Str_130[] PROGMEM = "USDINIT_READBPB_FAIL";
const char err_Str_131[] PROGMEM = "USDINIT_V1_APPCMD41_SEND_OP_COND_ERROR_BIT_SET_FAIL";
const char err_Str_132[] PROGMEM = "USDINIT_V1_APPCMD41_SEND_OP_COND_NO_RESPONSE_FAIL";
const char err_Str_133[] PROGMEM = "USDINIT_V1_APPCMD41_SEND_OP_COND_TIMEOUT_FAIL";
const char err_Str_134[] PROGMEM = "USDINIT_V1_CMD55_APP_CMD_ERROR_BIT_SET_FAIL";
const char err_Str_135[] PROGMEM = "USDINIT_V1_CMD55_APP_CMD_NO_RESPONSE_FAIL";
const char err_Str_136[] PROGMEM = "USDINIT_V1_CMD58_READ_OCR_ERROR_BIT_SET_FAIL";
const char err_Str_137[] PROGMEM = "USDINIT_V1_CMD58_READ_OCR_INCOMPATIBLE_VOLTAGE_FAIL";
const char err_Str_138[] PROGMEM = "USDINIT_V1_CMD58_READ_OCR_NO_RESPONSE_FAIL";
const char err_Str_139[] PROGMEM = "USDINIT_V2_APPCMD41_SEND_OP_COND_ERROR_BIT_SET_FAIL";
const char err_Str_140[] PROGMEM = "USDINIT_V2_APPCMD41_SEND_OP_COND_NO_RESPONSE_FAIL";
const char err_Str_141[] PROGMEM = "USDINIT_V2_APPCMD41_SEND_OP_COND_TIMEOUT_FAIL";
const char err_Str_142[] PROGMEM = "USDINIT_V2_CMD55_APP_CMD_ERROR_BIT_SET_FAIL";
const char err_Str_143[] PROGMEM = "USDINIT_V2_CMD55_APP_CMD_NO_RESPONSE_FAIL";
const char err_Str_144[] PROGMEM = "USDINIT_V2_CMD58_READ_OCR_A_ERROR_BIT_SET_FAIL";
const char err_Str_145[] PROGMEM = "USDINIT_V2_CMD58_READ_OCR_A_INCOMPATIBLE_VOLTAGE_FAIL";
const char err_Str_146[] PROGMEM = "USDINIT_V2_CMD58_READ_OCR_A_NO_RESPONSE_FAIL";
const char err_Str_147[] PROGMEM = "USDINIT_V2_CMD58_READ_OCR_B_ERROR_BIT_SET_FAIL";
const char err_Str_148[] PROGMEM = "USDINIT_V2_CMD58_READ_OCR_B_INCOMPATIBLE_VOLTAGE_FAIL";
const char err_Str_149[] PROGMEM = "USDINIT_V2_CMD58_READ_OCR_B_NO_RESPONSE_FAIL";
const char err_Str_150[] PROGMEM = "WRITESECTOR_CMD16_SET_BLOCKLEN_FAIL";
const char err_Str_151[] PROGMEM = "WRITESECTOR_CMD24_ACCEPT_TIMEOUT";
const char err_Str_152[] PROGMEM = "WRITESECTOR_CMD24_WRITE_SINGLE_BLOCK_FAIL";
const char err_Str_153[] PROGMEM = "WRITESECTOR_CMD24_WRITE_TIMEOUT";
const char err_Str_154[] PROGMEM = "WRITESECTOR_CRC_OR_REJECT_FAIL";
const char err_Str_155[] PROGMEM = "I2C_HOST_I2C_SLSTATUS_ERROR";
const char err_Str_156[] PROGMEM = "I2C_LENGTH_LESS_THAN_2";
const char err_Str_157[] PROGMEM = "I2C_LENGTH_GREATER_THAN_30";
const char err_Str_158[] PROGMEM = "I2C_LENGTH_DOES_NOT_MATCH";
const char err_Str_159[] PROGMEM = "INTERFACE_COMMAND_OUT_OF_RANGE";
const char err_Str_160[] PROGMEM = "INTERFACE_PARAMETER_ERROR";

//const PROGMEM char * const PROGMEM Error_Strings[161] = {
const char *Error_Strings[] = {
	err_Str_000,err_Str_001,err_Str_002,err_Str_003,err_Str_004,err_Str_005,err_Str_006,
	err_Str_007,err_Str_008,err_Str_009,err_Str_010,err_Str_011,err_Str_012,err_Str_013,
	err_Str_014,err_Str_015,err_Str_016,err_Str_017,err_Str_018,err_Str_019,err_Str_020,
	err_Str_021,err_Str_022,err_Str_023,err_Str_024,err_Str_025,err_Str_026,err_Str_027,
	err_Str_028,err_Str_029,err_Str_030,err_Str_031,err_Str_032,err_Str_033,err_Str_034,
	err_Str_035,err_Str_036,err_Str_037,err_Str_038,err_Str_039,err_Str_040,err_Str_041,
	err_Str_042,err_Str_043,err_Str_044,err_Str_045,err_Str_046,err_Str_047,err_Str_048,
	err_Str_049,err_Str_050,err_Str_051,err_Str_052,err_Str_053,err_Str_054,err_Str_055,
	err_Str_056,err_Str_057,err_Str_058,err_Str_059,err_Str_060,err_Str_061,err_Str_062,
	err_Str_063,err_Str_064,err_Str_065,err_Str_066,err_Str_067,err_Str_068,err_Str_069,
	err_Str_070,err_Str_071,err_Str_072,err_Str_073,err_Str_074,err_Str_075,err_Str_076,
	err_Str_077,err_Str_078,err_Str_079,err_Str_080,err_Str_081,err_Str_082,err_Str_083,
	err_Str_084,err_Str_085,err_Str_086,err_Str_087,err_Str_088,err_Str_089,err_Str_090,
	err_Str_091,err_Str_092,err_Str_093,err_Str_094,err_Str_095,err_Str_096,err_Str_097,
	err_Str_098,err_Str_099,err_Str_100,err_Str_101,err_Str_102,err_Str_103,err_Str_104,
	err_Str_105,err_Str_106,err_Str_107,err_Str_108,err_Str_109,err_Str_110,err_Str_111,
	err_Str_112,err_Str_113,err_Str_114,err_Str_115,err_Str_116,err_Str_117,err_Str_118,
	err_Str_119,err_Str_120,err_Str_121,err_Str_122,err_Str_123,err_Str_124,err_Str_125,
	err_Str_126,err_Str_127,err_Str_128,err_Str_129,err_Str_130,err_Str_131,err_Str_132,
	err_Str_133,err_Str_134,err_Str_135,err_Str_136,err_Str_137,err_Str_138,err_Str_139,
	err_Str_140,err_Str_141,err_Str_142,err_Str_143,err_Str_144,err_Str_145,err_Str_146,
	err_Str_147,err_Str_148,err_Str_149,err_Str_150,err_Str_151,err_Str_152,err_Str_153,
	err_Str_154,err_Str_155,err_Str_156,err_Str_157,err_Str_158,err_Str_159,err_Str_160
};
#endif //CFA10006_ERROR_MESSAGES

#ifdef CFA10060_USE_I2C
# define SENDANDGETRESPONSE I2CSendCommandGetResponse
# define SENDANDCHECKREPLY(r) \
	if (!SENDANDGETRESPONSE(&command, &response, (r))) \
		{ SPRINTF(F("I2CSendCommandGetResponse returned false\n")); return 0; }
# define I2C_CHECK_ADDR() {if (I2CAddress == 0xFF) return 0;}
#endif

#ifdef CFA10060_USE_SPI
# define SENDANDGETRESPONSE SPISendCommandGetResponse
# define SENDANDCHECKREPLY(r) \
	if (!SPISendCommandGetResponse(&command, &response, (r))) \
		{ SPRINTF(F("SPISendCommandGetResponse returned false\n")); return 0; }
# define I2C_CHECK_ADDR() {}
#endif

#define REQSHORT(c,d,l,r) \
	I2C_CHECK_ADDR(); \
	command.command = (c); \
	if ((l) != 0) \
		memcpy(command.data, (d), (l)); \
	command.length = (l); \
	SENDANDCHECKREPLY((r))

#define REQSHORT0(c,r) \
	I2C_CHECK_ADDR(); \
	command.command = (c); \
	command.length = 0; \
	SENDANDCHECKREPLY((r))

#define REQSHORT1(c,d,r) \
	I2C_CHECK_ADDR(); \
	command.command = (c); \
	command.data[0] = (d); \
	command.length = 1; \
	SENDANDCHECKREPLY((r))

#define REQSHORT2(c,da,db,r) \
	I2C_CHECK_ADDR(); \
	command.command = (c); \
	command.data[0] = (da); \
	command.data[1] = (db); \
	command.length = 2; \
	SENDANDCHECKREPLY((r))

///////////////////////////////////////////////////////////////////////////////////////////////////


CFA10060::CFA10060()
{
	//class initialization
	haveError = 0;
	lastCursorType = 0;
#ifdef CFA10060_USE_I2C
	I2CAddress = 0xFF;
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t CFA10060::init(void)
{
	//find the CFA10060
	haveError = 0;
	lastCursorType = 0;

#ifdef CFA10060_USE_I2C
	I2CAddress = 0xFF;
	while (1)
	{
		SPRINTF(F("Searching for CFA10060 on I2C...\n"));
		I2CSearchForAddress();
		if (I2CAddress == 0xFF)
		{
			SPRINTF(F("CFA10060 not found.\n"));
			delay(1000);
		}
		else
		{
			SPRINTF(F("CFA10060 found.\n"));
			break;
		}
	}
	checkAndClearFileSystemErrors();
	return I2CAddress;
#endif

#ifdef CFA10060_USE_SPI
	//set the SPI bus rate
	SPI.setClockDivider(SPI_CLOCK_DIV16);
	//put the SS pin into the correct mode
	pinMode(CFA10060_SPI_SS_PIN, INPUT_PULLUP);
	//clear out SPI
	SPIClear();
	//clear any errors
	checkAndClearFileSystemErrors();
	//nothing to return
	SPRINTF(F("CFA10060 initialized on SPI.\n"));
	return 1;
#endif
}

uint8_t CFA10060::cmdPing(char data[])
{
	//Ping
	//Returns 1 if the CFA10060 replied with the same data that it was sent
	uint8_t		ret, i;
	//create the command packet
	I2C_CHECK_ADDR();
	command.command = CMD_PING;
	command.length = strlen(data);
	memcpy(command.data, data, command.length);
    //send the packet, get the reply
	SENDANDCHECKREPLY(command.length);
    //check returned data
    if (response.length != command.length)
    {
    	//length didnt match
    	SPRINTF(F("Ping returned length mismatch.\n"));
    	return 0;
    }
    if (memcmp(response.data, command.data, command.length) != 0)
    {
    	//data didnt match
#ifdef CFA10006_SERIAL_MESSAGES
    	SPRINTF(F("Ping returned data mismatch: "));
		for (i = 0; i <response.length; i++)
			Serial.write(response.data[i]);
		SPRINTF(F("\n"));
#endif
    	return 0;
    }
    //ok
    return 1;
}

uint8_t CFA10060::cmdGetVersion(char retVersion[])
{
	//Get FW version string (18 chars max length)
	uint8_t		ret;
	//create the command packet
	I2C_CHECK_ADDR();
	command.command = CMD_GET_VERSION;
	command.length = 0;
    //send the packet, get the reply
	SENDANDCHECKREPLY(18);
	//ok
    memcpy(retVersion, response.data, response.length);
    retVersion[response.length] = 0;
    return 1;
}

#ifdef CFA10060_USE_I2C
uint8_t CFA10060::cmdChangeI2CAddress(uint8_t newAddress)
{
	//Change I2C address location
	uint8_t		ret;
	I2C_CHECK_ADDR();

	SPRINTF(F("Change I2C address from %3d (0x%02X) to %3d (0x%02X)\n"),
			I2CAddress,I2CAddress, newAddress,newAddress);

	//Start the I2C transaction for this device's address
	Wire.beginTransmission(I2CAddress);
	//Send the command
	Wire.write(CMD_SET_I2C_ADDRESS);
	//Send the significant data length (will match the I2C since we are in control of it here)
	Wire.write(1);
	//Send the data
	Wire.write(newAddress);
	//Stop the I2C transaction
	Wire.endTransmission();
	//Give the device a little time to change its address and write the new address to its EEPROM/Flash.
	delay(250);
	//Go find the device at its new address.
	init();
	//done
	return I2CAddress == newAddress ? 1 : 0;
}
#endif

uint8_t CFA10060::cmdCheckAndClearFileSystemErrors(void)
{
	//Check & Clear FileSystem Errors
	return checkAndClearFileSystemErrors();
}

uint8_t CFA10060::cmdSetBacklightBrightness(uint8_t brightness)
{
	//Set LCD backlight brightness (0-100%)
	if (brightness > 100) return 0;
	REQSHORT1(CMD_GET_SET_BACKLIGHT_BRIGHTNESS, brightness, 1);
	//ok
    return 1;
}

uint8_t CFA10060::cmdGetBacklightBrightness(uint8_t &retBrighness)
{
	//Get LCD backlight brightness
	REQSHORT0(CMD_GET_SET_BACKLIGHT_BRIGHTNESS, 1);
	//ok
	retBrighness = response.data[0];
    return 1;
}

uint8_t CFA10060::cmdFillSolidColor(uint8_t R, uint8_t G, uint8_t B)
{
	//Fill the LCD with a solid color
	I2C_CHECK_ADDR();
	command.command = CMD_FILL_SCREEN_WITH_SOLID_COLOR;
    command.length = 3;
    command.data[0]= R;
    command.data[1]= G;
    command.data[2]= B;
    //send the packet, get the reply
    SENDANDCHECKREPLY(0);
	//ok
    return 1;
}

uint8_t CFA10060::cmdGetSDVolumeLabel(char retLabel[])
{
	//Read the uSD card's volume label
	I2C_CHECK_ADDR();
	command.command = CMD_GET_SD_CARD_VOLUME_LABEL;
    command.length = 0;
    //send the packet, get the reply
    SENDANDCHECKREPLY(0xFF);
	//ok
	memcpy(retLabel, response.data, response.length);
	response.data[response.length] = 0;
	checkAndClearFileSystemErrors();
    return 1;
}

uint8_t CFA10060::cmdGetFreeUsedSectors(uint32_t &retUsed, uint32_t &retFree)
{
	//Read the uSD card's volume label
	//This can take quite some time to return (1-10 seconds)
	REQSHORT0(CMD_GET_SD_CARD_FREE_USED_SECTORS, 8);
	if (response.length == 8)
	{
		//correct reply length
		retFree = (uint32_t)response.data[0];
		retFree |= (uint32_t)response.data[1] << 8;
		retFree |= (uint32_t)response.data[2] << 16;
		retFree |= (uint32_t)response.data[3] << 24;
		retUsed = (uint32_t)response.data[4];
		retUsed |= (uint32_t)response.data[5] << 8;
		retUsed |= (uint32_t)response.data[6] << 16;
		retUsed |= (uint32_t)response.data[7] << 24;
		//ok
		return 1;
	}
	//not a valid reply
    return 0;
}


uint8_t CFA10060::cmdGetNumFilesRootDir(uint16_t &retFileCount)
{
	//Read the uSD card's volume label
	REQSHORT0(CMD_GET_NUMBER_OF_FILES_IN_ROOT_DIR, 0xFF);
	if (response.length == 2)
	{
		//ok
		retFileCount = response.data[0] | (response.data[1] << 8);
		return 1;
	}
	//no valid reply?
	return 0;
}

uint8_t CFA10060::cmdGetFileDetails(uint16_t fileIndex, uint16_t &retIndex, uint32_t &retSize, char *retName)
{
	//Get specified file's size and name
	uint8_t i;
	REQSHORT2(CMD_GET_NAME_AND_SIZE_OF_FILE, (fileIndex & 0xFF), ((fileIndex >> 8) & 0xFF), 0xFF);
	if (response.length > 6)
	{
		retIndex = response.data[0] | (response.data[1] << 8);
		retSize = (uint32_t)response.data[2] | (((uint32_t)response.data[3])<<8) |
                (((uint32_t)response.data[4])<<16) | (((uint32_t)response.data[5])<<24);
		memcpy(retName, response.data+6, response.length-6);
		retName[response.length-6] = 0; //null terminate name
		//ok
		return 1;
	}
	//no valid reply?
	return 0;
}

uint8_t CFA10060::cmdFileOpen(char fileName[], uint8_t mode, uint8_t retHandle)
{
	//Open a file on the SD card using specified mode
	//  FOPEN_READ, FOPEN_CREATE_RESET_READ_WRITE, FOPEN_CREATE_PRESERVE_READ_WRITE
	//Returns the file handle
	I2C_CHECK_ADDR();
	command.command = CMD_FILE_OPEN;
    command.data[0] = mode;
    command.length = strlen(fileName)+1;
    memcpy(&command.data[1], fileName, command.length);
    //send the packet, get the reply
    SENDANDCHECKREPLY(1);
	SPRINTF(F(" len:%d "), response.length);
	if (response.length == 1)
	{
		//got file handle reply, ok
		retHandle = response.data[0];
		return 1;
	}
	//no valid reply?
	return 0;
}

uint8_t CFA10060::cmdFileRead(uint8_t fileHandle, uint8_t length, char retData[], uint8_t &retLength)
{
	//Read a file on the SD card that has been opened
	//Returns the data & read data length
	REQSHORT2(CMD_FILE_READ, fileHandle, length, 0xFF);
	if (response.length > 1)
	{
		if (response.data[0] != fileHandle)
			//response doesnt match req fileHandle?
			return 0;
		//copy data
		retLength = response.length-1;
		memcpy(retData, &response.data[1], retLength);
		//null terminate response
		retData[retLength] = 0;
		//ok
		return 1;
	}
	//response too short?
    return 0;
}

uint8_t CFA10060::cmdFileWrite(uint8_t fileHandle, char data[], uint8_t length, uint8_t &retDataWritten)
{
	//Write data to a file on the SD card that has been opened
	//Returns the written data length
	I2C_CHECK_ADDR();
	command.command = CMD_FILE_WRITE;
	command.length = length + 1;
    command.data[0]= fileHandle;
    memcpy(&command.data[1], data, length);
    //send the packet, get the reply
    SENDANDCHECKREPLY(0xFF);
	if (response.length == 2)
	{
		if (response.data[0] != fileHandle)
			//response doesnt match req fileHandle?
			return 0;
		retDataWritten = response.data[1];
		//ok
		return 1;
	}
	SPRINTF(F("write reply len: %d\n"), response.length);
	//response too short?
    return 0;
}

uint8_t CFA10060::cmdFileTell(uint8_t fileHandle, uint32_t &retPosition)
{
	//Read a file on the SD card that has been opened
	//Returns the data & read data length
	REQSHORT1(CMD_FILE_TELL, fileHandle, 0xFF);
	if (response.length == 5)
	{
		if (response.data[0] != fileHandle)
			//response doesnt match req fileHandle?
			return 0;
		retPosition = response.data[1] | (((uint32_t)response.data[2])<<8) |
	            (((uint32_t)response.data[3])<<16) | (((uint32_t)response.data[4])<<24);
		//ok
		return 1;
	}
	//response too short?
    return 0;
}

uint8_t CFA10060::cmdFileSeek(uint8_t fileHandle, uint32_t position)
{
	//Open a file on the SD card using specified mode
	//  FOPEN_READ, FOPEN_CREATE_RESET_READ_WRITE, FOPEN_CREATE_PRESERVE_READ_WRITE
	//Returns the file handle
	I2C_CHECK_ADDR();
	command.command = CMD_FILE_SEEK;
	command.length = 5;
	command.data[0] = fileHandle;
	command.data[1] = position & 0xFF;
	command.data[2] = (position >> 8) & 0xFF;
	command.data[3] = (position >> 16) & 0xFF;
	command.data[4] = (position >> 24) & 0xFF;

    //send the packet, get the reply
	SENDANDCHECKREPLY(0xFF);
	if (response.length == 1)
		if (response.data[0] == fileHandle)
			//ok
			return 1;
	//no valid reply?
	return 0;
}

uint8_t CFA10060::cmdFileClose(uint8_t fileHandle)
{
	//Read a file on the SD card that has been opened
	//Returns the data & read data length
	REQSHORT1(CMD_FILE_CLOSE, fileHandle, 0xFF);
	//ok
    return 1;
}

uint8_t CFA10060::cmdFileDelete(char fileName[])
{
	//Delete the specified file on the SD card
	uint8_t len;
	len = strlen(fileName)+1;
	REQSHORT(CMD_FILE_DELETE, fileName, len, 0xFF);
	//ok
	return 1;
}

uint8_t CFA10060::cmdSetColor(
	uint8_t fgR, uint8_t fgG, uint8_t fgB,
	uint8_t bgR, uint8_t bgG, uint8_t bgB
	)
{
	//Set foreground & background colors
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_SET_COLOR;
	command.length = 6;
	command.data[0] = fgR;
	command.data[1] = fgG;
	command.data[2] = fgB;
	command.data[3] = bgR;
	command.data[4] = bgG;
	command.data[5] = bgB;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdSetColor(uint8_t fgR, uint8_t fgG, uint8_t fgB)
{
	//Set foreground color only
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_SET_COLOR;
	command.length = 3;
	command.data[0] = fgR;
	command.data[1] = fgG;
	command.data[2] = fgB;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawLine(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
	//Draw a line on the LCD using previously set pixel color
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_LINE;
	command.length = 4;
	command.data[0] = startX;
	command.data[1] = startY;
	command.data[2] = endX;
	command.data[3] = endY;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawPixel(uint8_t x, uint8_t y)
{
	//Draw a pixel on the LCD using the specified color
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_PIXEL;
	command.length = 2;
	command.data[0] = x;
	command.data[1] = y;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b)
{
	//Draw a pixel on the LCD using the specified color
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_PIXEL;
	command.length = 5;
	command.data[0] = x;
	command.data[1] = y;
	command.data[2] = r;
	command.data[3] = g;
	command.data[4] = b;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawRectangle(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t fillOption)
{
	//Draw a rectangle on the LCD using the specified color
	//fillOption:
	// 0: outline of rectangle, in foreground
	// 1: filled rectangle, in background
	// 2: filled rectangle in background outlined by foreground
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_RECTANGLE;
	command.length = 5;
	command.data[0] = fillOption;
	command.data[1] = startX;
	command.data[2] = startY;
	command.data[3] = endX;
	command.data[4] = endY;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0xFF);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawRoundedRectangle(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t radius, uint8_t fillOption)
{
	//Draw a rounded rectangle on the LCD using the specified color
	//fillOption:
	// 0: outline of rectangle, in foreground
	// 1: filled rectangle, in background
	// 2: filled rectangle in background outlined by foreground
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_ROUNDED_RECTANGLE;
	command.length = 6;
	command.data[0] = fillOption;
	command.data[1] = startX;
	command.data[2] = startY;
	command.data[3] = endX;
	command.data[4] = endY;
	command.data[5] = radius;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawCircle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint8_t fillOption)
{
	//Draw a circle on the LCD using the specified color
	//fillOption:
	// 0: outline of rectangle, in foreground
	// 1: filled rectangle, in background
	// 2: filled rectangle in background outlined by foreground
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_CIRCLE;
	command.length = 4;
	command.data[0] = fillOption;
	command.data[1] = centerX;
	command.data[2] = centerY;
	command.data[3] = radius;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdLCDBitBlt(uint8_t sourceX, uint8_t sourceY, uint8_t destX, uint8_t destY, uint8_t sizeX, uint8_t sizeY)
{
	//Copy image from one area of the LCD to another area
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_BITBLT;
	command.length = 6;
	command.data[0] = sizeX;
	command.data[1] = sizeY;
	command.data[2] = sourceX;
	command.data[3] = sourceY;
	command.data[4] = destX;
	command.data[5] = destY;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawText(uint8_t sizeOption, uint8_t drawBackground, uint8_t x, uint8_t y, char text[])
{
	//Draw text to the LCD
	// sizeOption:		0=8x8 font, 1=12x16 font
	// drawBackground:	0=transparent, 1=solid
	uint8_t len;
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_TEXT;
	command.data[0] = sizeOption;
	command.data[1] = drawBackground;
	command.data[2] = x;
	command.data[3] = y;
	len = strlen(text);
	memcpy(&command.data[4], text, len+1);
	command.length = len+1+4;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdLCDCursor(Cursors_t cursorType, uint8_t &retCursorX, uint8_t &retCursorY, Pads_t &retEnterCancel)
{
	//Sets the LCD Cursor display option and returns cursor location and pad status
	lastCursorType = cursorType;
	REQSHORT1(CMD_LCD_CURSOR, (uint8_t)cursorType, 3);
	if (response.length == 3)
	{
		//got location data reply
		retCursorX = response.data[1];
		retCursorY = response.data[2];
		retEnterCancel = (Pads_t)response.data[0];
		//ok
		return 1;
	}
	//bad response data?
    return 0;
}

uint8_t CFA10060::cmdLCDCursor(Cursors_t cursorType)
{
	//Sets the LCD Cursor display option
	lastCursorType = cursorType;
	REQSHORT1(CMD_LCD_CURSOR, (uint8_t)cursorType, 3);
	if (response.length == 3)
		//ok
		return 1;
	//bad response data?
    return 0;
}

uint8_t CFA10060::cmdLCDCursor(uint8_t cursorIndex)
{
	//Sets the LCD Cursor display option
	lastCursorType = (Cursors_t)cursorIndex;
	REQSHORT1(CMD_LCD_CURSOR, cursorIndex, 3);
	if (response.length == 3)
		//ok
		return 1;
	//bad response data?
    return 0;
}

uint8_t CFA10060::cmdLCDCursor(uint8_t &retCursorX, uint8_t &retCursorY, Pads_t &retEnterCancel)
{
	//Gets the LCD Cursor location & pad status
	REQSHORT1(CMD_LCD_CURSOR, (uint8_t)lastCursorType, 3);
	if (response.length == 3)
	{
		//got location data reply
		retCursorX = response.data[1];
		retCursorY = response.data[2];
		retEnterCancel = (Pads_t)response.data[0];
		//ok
		return 1;
	}
	//bad response data?
    return 0;
}

uint8_t CFA10060::cmdDrawSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY)
{
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_SPRITE;
	command.length = 6;
	command.data[0] = spriteIndex;
	command.data[1] = 1;
	command.data[2] = sizeX;
	command.data[3] = sizeY;
	command.data[4] = x;
	command.data[5] = y;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdKeepSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY)
{
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_SPRITE;
	command.length = 6;
	command.data[0] = spriteIndex;
	command.data[1] = 0;
	command.data[2] = sizeX;
	command.data[3] = sizeY;
	command.data[4] = x;
	command.data[5] = y;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdStartSprite(uint8_t spriteIndex, uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY)
{
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_SPRITE;
	command.length = 6;
	command.data[0] = spriteIndex;
	command.data[1] = 2;
	command.data[2] = sizeX;
	command.data[3] = sizeY;
	command.data[4] = x;
	command.data[5] = y;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdMoveSprite(uint8_t spriteIndex, uint8_t oldX, uint8_t oldY, uint8_t newX, uint8_t newY, uint8_t sizeX, uint8_t sizeY)
{
	I2C_CHECK_ADDR();
	command.command = CMD_LCD_SPRITE;
	command.length = 8;
	command.data[0] = spriteIndex;
	command.data[1] = 3;
	command.data[2] = sizeX;
	command.data[3] = sizeY;
	command.data[4] = oldX;
	command.data[5] = oldY;
	command.data[6] = newX;
	command.data[7] = newY;
    //send the packet, get the reply
	SENDANDCHECKREPLY(0);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawSDBMPOnLCD(char fileName[])
{
	//Display a BMP located on the SD card to the LCD
	uint8_t len, i;
	len = strlen(fileName)+1;
	REQSHORT(CMD_PUSH_BMP_FROM_SD_CARD_TO_LCD, fileName, len, 0xFF);
	return 1;
}

uint8_t CFA10060::cmdPlaySDMovieOnLCD(char fileName[])
{
	//Display a movie located on the SD card on the LCD
	uint8_t len, i;
	len = strlen(fileName)+1;
	REQSHORT(CMD_PUSH_MOVIE_FROM_SD_CARD_TO_LCD, fileName, len, 0);
	//hold here until movie is finished
#ifdef CFA10060_USE_I2C
	while (I2CIsBusy())
		delay(50);
#endif
	return 1;
}

uint8_t CFA10060::cmdSaveLCDToSDBMP(char fileName[])
{
	//Save current LCD display image to BMP on SD card
	uint8_t len;
	len = strlen(fileName)+1;
	REQSHORT(CMD_SAVE_LCD_AS_BMP, fileName, len, 0xFF);
	//ok
	return 1;
}

uint8_t CFA10060::cmdDrawSDMoveFrameToLCD(uint8_t fileHandle, uint32_t frameNumber)
{
	//Display a single frame of a movie file on the SD card to the LCD
	//Movie file must have been opened by cmdFileOpen() first
	I2C_CHECK_ADDR();
	command.command = CMD_PUSH_MOVIE_FRAME_FROM_SD_CARD_TO_LCD;
	command.length = 5;
	command.data[0] = fileHandle;
	command.data[1] = (uint8_t)((uint32_t)(frameNumber)&(uint32_t)0xFF);
	command.data[2] = (uint8_t)((uint32_t)(frameNumber>>8)&(uint32_t)0xFF);
	command.data[3] = (uint8_t)((uint32_t)(frameNumber>>16)&(uint32_t)0xFF);
	command.data[4] = (uint8_t)((uint32_t)(frameNumber>>24)&(uint32_t)0xFF);
    //send the packet, get the reply
	SENDANDCHECKREPLY(1);
	//ok
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CFA10060_USE_I2C

inline uint8_t CFA10060::I2CIsBusy(void)
{
	//Send a degenerate I2C transaction to the display. It is just the start bit and addreess field, no data bytes.
	Wire.beginTransmission(I2CAddress);
	//End the I2C transaction. If the display is busy, it will NACK, which will make Wire.endTransmission() return a non-zero error code.
	return Wire.endTransmission();
}

uint8_t CFA10060::I2CSendCommandGetResponse(
	Transaction_t *command,
	Transaction_t *response,
	uint8_t receiveDataLength		// 0xFF: read a full buffer
)
{
	uint8_t		i;
	uint32_t	delayCount = 0;
	uint8_t		returnValue = 1;

	//make sure we have an address
	if (I2CAddress == 0xFF)
		return 0;

	//Start the I2C transaction for this device's address
	Wire.beginTransmission(I2CAddress);

	//Send the command
	Wire.write(command->command);

	//Send the significant data length (will match the I2C since we are in control of it here)
	Wire.write(command->length);

	//Send the data
	for(i = 0; i < command->length; i++)
		Wire.write(command->data[i]);

	//Stop the I2C transaction
	Wire.endTransmission();

	//empty out the return buffer
	memset(response->data, 0x00, MAXIMUM_DATA_LENGTH);

	//Stall here until the device has had time to complete the commmand and
	//prepare the response. Let the user know if it is taking a long time.
	//There are some operations (CMD_GET_SD_CARD_FREE_USED_SECTORS comes to mind)
	//that can take a long time to execute, especially for large uSD cards.
	while (I2CIsBusy())
	{
		delay(5);
		delayCount++;
#ifdef CFA10006_SERIAL_MESSAGES
		if (delayCount == 50)
			SPRINTF(F("Waiting..."));
		if (delayCount % 100 == 0)
			SPRINTF(F("."));
		if (delayCount > 3000)
			//too long? failed.
			break;
#endif
	}
#ifdef CFA10006_SERIAL_MESSAGES
	if (delayCount > 3000)
		SPRINTF(F(" giving up.\n"));
	else
		if (delayCount > 50)
			SPRINTF(F(" done.\n"));
#endif

	//Do the read. If the caller specified how many byres they expect the command
	//to return, request that many. Otherwise, request the maximum number of bytes
	//that will fit in the buffer, plus the command and length
	if (receiveDataLength == 0xFF)
		receiveDataLength = MAXIMUM_DATA_LENGTH;
	i = Wire.requestFrom(I2CAddress, (uint8_t)(receiveDataLength+2));

	//Check length, warn and continue if there is an error.
#ifdef CFA10006_SERIAL_MESSAGES
	if (i != receiveDataLength+2)
		SPRINTF(F("Wire.requestFrom fail. Expected %d bytes got %d bytes\n"), receiveDataLength+2, i);
#endif

	//Get the command byte of the response
	response->command = Wire.read();

	//Verify the sanity of the response. It should match the command sent.
#ifdef CFA10006_SERIAL_MESSAGES
	if ((response->command & 0x3F) != (command->command & 0x3F))
		//Warn and continue.
		SPRINTF(F("Received unexpected response of %3d (0x%02X) to command %3d (0x%02X).\n"),
				response->command & 0x3F, response->command & 0x3F,
				command->command & 0x3F,  command->command & 0x3F);
#endif

	//If the 7th bit (0x80) is set, the CFA10060 has rejected our packet as invalid.
#ifdef CFA10006_SERIAL_MESSAGES
	if ((response->command & CMD_NAK_RESPONSE_FLAG) != 0)
		//Warn and continue.
		SPRINTF(F("NAK %3d (0x%02X) received response to command %3d (0x%02X).\n"),
			response->command, response->command,
			command->command,  command->command);
#endif

	//If the 6th bit (0x40) is set, the CFA10060 has logged errors and we should ask what went wrong.
	haveError = 0;
	if ((response->command & CMD_ERR_RESPONSE_FLAG) != 0)
	{
		//Warn and continue.
		SPRINTF(F("Errors logged on CFA10060.\n"));
		haveError = 1;
	}

	//Find out how may bytes of the transfer the CFA10060 thinks are significant.
	response->length = Wire.read();

	//Range check the length. There should not be more than MAXIMUM_DATA_LENGTH, and
	//we should have at least response->length still available.
	if ((MAXIMUM_DATA_LENGTH < response->length) ||	(Wire.available() < response->length))
	{
		SPRINTF(F("Invalid length of %d in response to command %d. Truncating to %d.\n"),
				response->length, command->command, Wire.available());
		//Attempt to gracefully continue: Override the length
		response->length = Wire.available();
	}

	//Transfer over the data
	for (i = 0; i < response->length; i++)
		response->data[i] = Wire.read();

	return returnValue;
}


uint8_t CFA10060::I2CSearchForAddress(void)
{
	//Find out what the CFA10060 I2C address is now
	//returns 1 is found a device
	uint8_t		i;
	uint8_t		firstAddress = 0xFF;
	uint8_t		savedAddress;

	savedAddress = I2CAddress;

	//Assuming the CFA10060 is not busy, is should only be ready at one address.
	for (I2CAddress = 0; I2CAddress <= 127; I2CAddress++)
	{
		if (I2CIsBusy())
		{
			//No ACK at this address.
			//SPRINTF(F("NAK at %3d (0x%02X)\n"),I2CAddress,I2CAddress);
		}
		else
		{
			//Got an ACK, see if it is a CFA10060
			//SerPrintFF(F("ACK at %3d (0x%02X) <<<<\n"),CFA10060_I2C_Address,CFA10060_I2C_Address);
			//Additionally, we should verify the version string, since any device could ACK.
			command.command = CMD_GET_VERSION;
			command.length = 0;
			I2CSendCommandGetResponse(&command, &response, 0xFF);
			if (strncmp((char*)response.data, "CFA10060", 8) == 0)
			{
				//Verified found CFA10060
#ifdef CFA10006_SERIAL_MESSAGES
				SPRINTF(F("CFA10060 found at I2C address %3d (0x%02X). Version:\""),	I2CAddress, I2CAddress);
				for (i = 0; i < response.length; i++)
					Serial.write(response.data[i]);
				SPRINTF(F("\"\n"));
#endif

				//Record the first CFA10060
				if (firstAddress == 0xFF)
					firstAddress = I2CAddress;
			}
			else
			{
				//Not verified CFA10060
#ifdef CFA10006_SERIAL_MESSAGES
				SPRINTF(F("Device found at I2C address %3d (0x%02X), but version is not a CFA10060.\n"), I2CAddress, I2CAddress);
				SPRINTF(F("  Received:\""));
				for(i=0;i<response.length;i++)
					Serial.write(response.data[i]);
				SPRINTF(F("\"\n"));
#endif
			}
		}
	}
	if (firstAddress != 0xFF)
		I2CAddress = firstAddress;
	else
		I2CAddress = savedAddress;

	return firstAddress != 0xFF ? 1 : 0;
}

#endif //I2C


#ifdef CFA10060_USE_SPI

inline uint8_t CFA10060::SPIIsBusy(void)
{
	//make sure that the SS pin is deselected (high)
	if (!digitalRead(CFA10060_SPI_SS_PIN))
		//pin is low (selected), error!
		return 1;
	//SPI is not busy (returns 0 to match the I2C equiv function)
	return 0;
}

void CFA10060::SPIClear(void)
{
	//clear out any buffered SPI data
	uint8_t i;

	//bring the SS pin low (select the CFA10060 SPI)
	pinMode(CFA10060_SPI_SS_PIN,OUTPUT);
	digitalWrite(CFA10060_SPI_SS_PIN,LOW);
	delayMicroseconds(1); //small delay
	//read until response is 0xFF or counter reached
	for (i = 0; i < 128; i++)
	{
		if (SPI.transfer(0xFF) == 0xFF)
			break;
		delayMicroseconds(1);
	}
	//end the transmission (bring SS high)
	pinMode(5, INPUT_PULLUP);
}

uint8_t CFA10060::SPISendCommandGetResponse(
	Transaction_t *command,
	Transaction_t *response,
	uint8_t receiveDataLength		// ignored for SPI
)
{
	uint8_t		i;
	uint8_t		lastRet;
	uint32_t	delayCount;
	uint8_t		returnValue = 1;

	//make sure that the SS pin is deselected to begin with
	if (digitalRead(CFA10060_SPI_SS_PIN) == 0)
		//pin is low (selected), error!
		SPRINTF(F("SPI SS is busy?? Continuing anyway...\n"));

	//bring the SS pin low (select the CFA10060 SPI)
	pinMode(CFA10060_SPI_SS_PIN,OUTPUT);
	digitalWrite(CFA10060_SPI_SS_PIN,LOW);
	delayMicroseconds(1); //small delay

	//send the command and receive last response which is ignored
	SPI.transfer(command->command);
	lastRet = SPI.transfer(command->length);
	for (i = 0; i < command->length; i++)
		lastRet = SPI.transfer(command->data[i]);
	if (lastRet != 0xFF)
	{
		//read until we get 0xFF to flush out CFA10060 send buffer
		for (i = 0; i < 128; i++)
		{
			if (SPI.transfer(0xFF) == 0xFF)
				break;
			delayMicroseconds(1);
		}
		//SPRINTF(F("GOT DATA BACK? 0x%02X CLEARED: %d bytes\n"), lastRet, i);
	}

	//end the transmission (bring SS high)
	pinMode(5, INPUT_PULLUP);
	delayMicroseconds(25);
	memset(response->data, 0x00, MAXIMUM_DATA_LENGTH);

	//wait for a reply
	delayCount = 0;
	while(1)
	{
		//bring the SS pin low (select the CFA10060 SPI)
		pinMode(CFA10060_SPI_SS_PIN,OUTPUT);
		digitalWrite(CFA10060_SPI_SS_PIN,LOW);
		delayMicroseconds(1); //small delay
		//read the command
		response->command = SPI.transfer(0xFF);
		if (response->command != 0xFF)
			//appear to have read valid data, break loop and continue
			break;
		//end the transmission (bring SS high)
		pinMode(5, INPUT_PULLUP);

		//delay & messages
		delay(5);
		delayCount++;
#ifdef CFA10006_SERIAL_MESSAGES
		if (delayCount == 50)
			SPRINTF(F("Waiting..."));
		if (delayCount % 100 == 0)
			SPRINTF(F("."));
		if (delayCount > 3000)
			//too long? failed.
			break;
#endif
	}
	if (response->command == 0xFF)
	{
		//never got any data, return an error
		SPRINTF(F(" giving up.\n"));
		//SPRINTF(F("Did not receive a command response from the CFA10060.\n"));
		//end the transmission (bring SS high)
		pinMode(5, INPUT_PULLUP);
		delayMicroseconds(1);
		return 0;
	}
	if (delayCount > 50)
		SPRINTF(F(" done.\n"));

	/*
	for (delayCount = 0; delayCount < 5000000/50; delayCount++)
	{
		//bring the SS pin low (select the CFA10060 SPI)
		pinMode(CFA10060_SPI_SS_PIN,OUTPUT);
		digitalWrite(CFA10060_SPI_SS_PIN,LOW);
		delayMicroseconds(1); //small delay
		//read the command
		response->command = SPI.transfer(0xFF);
		if (response->command != 0xFF)
			//appear to have read valid data, break loop and continue
			break;
		//end the transmission (bring SS high)
		pinMode(5, INPUT_PULLUP);
		//no data to be read, delay and try again
		delayMicroseconds(50); //50uS = ~200uS full loop
	}
	if (response->command == 0xFF)
	{
		//never got any data, return an error
		SPRINTF(F("Never received a command response from the CFA10060.\n"));
		//end the transmission (bring SS high)
		pinMode(5, INPUT_PULLUP);
		delayMicroseconds(1);
		return 0;
	} */

	//read the length
	response->length = SPI.transfer(0xFF);

	//response should match the sent command
	if ((response->command & 0x3F) != (command->command & 0x3F))
		//Warn and continue.
		SPRINTF(F("Received unexpected response of 0x%02X to command 0x%02X.\n"),
				response->command, response->command,
				command->command & 0x3F,  command->command & 0x3F);

	//read up the data (we cant just stop reading at
	// receiveDataLength as the CFA10060 will buffer the data and send if next time creating sync issues)
	for (i = 0; i < response->length; i++)
		response->data[i] = SPI.transfer(0xFF);

	//end the transmission (bring SS high)
	pinMode(5, INPUT_PULLUP);
	delayMicroseconds(1);

	//debug: write delay from earlier
	//SPRINTF(F(" delayCount:%u "),delayCount);

	//If the 7th bit (0x80) is set, the CFA10060 has rejected our packet as invalid.
#ifdef CFA10006_SERIAL_MESSAGES
	if ((response->command & CMD_NAK_RESPONSE_FLAG) != 0)
		//Warn and continue.
		SPRINTF(F("NAK %3d (0x%02X) received response to command %3d (0x%02X).\n"),
			response->command, response->command,
			command->command,  command->command);
#endif

	//If the 6th bit (0x40) is set, the CFA10060 has logged errors and we should ask what went wrong.
	haveError = 0;
	if ((response->command & CMD_ERR_RESPONSE_FLAG) != 0)
	{
		//Warn and continue.
		SPRINTF(F("Errors logged on CFA10060.\n"));
		haveError = 1;
	}

	return returnValue;
}
#endif //SPI

uint8_t CFA10060::checkAndClearFileSystemErrors(void)
{
	uint8_t		i;
	uint8_t		returnValue = 1;

	//Check & Clear FileSystem Errors
	command.command = CMD_CHECK_AND_CLEAR_FILESYSTEM_ERRORS;
	command.length = 0;
	SENDANDGETRESPONSE(&command, &response, 20);

	//We expect the response length to be 20
#ifdef CFA10006_SERIAL_MESSAGES
	if (response.length != 20)
	{
		SPRINTF(F("RespLength=%3d "),response.length);
		SPRINTF(F("Resp=%3d = 0x%02X\n"),response.command,response.command);
	}
#endif

	//If there are errors, print them, otherwise silence.
	for(i = 0; i < response.length;)
	{
		if(response.data[i+1] != 0)
		{
#ifdef CFA10006_SERIAL_MESSAGES
			SPRINTF(F("  Error. Card:%s "), response.data[i] & 0x80 ? " Out" : "In ");
				if(response.data[i] & 0x40)
				{
					if(response.data[i] & 0x3F)
						SPRINTF(F("Command:%3d"),response.data[i] & ~(0x80 | 0x40));
					else
						SPRINTF(F("File/Command:None"));
				}
				else
					SPRINTF(F("File:%3d"),response.data[i] & ~(0x80 | 0x40));

#ifdef CFA10006_ERROR_MESSAGES
				SPRINTF(F(" ErrorCode:%3d (0x%02X) \""), response.data[i+1],response.data[i+1]);
				serialPrintP(Error_Strings[response.data[i+1]]);
				SPRINTF(F("\"\n"));
#else
				SPRINTF(F(" ErrorCode:%3d (0x%02X)\n"), response.data[i+1],response.data[i+1]);
#endif //CFA10006_ERROR_MESSAGES
#endif //CFA10006_SERIAL_MESSAGES
				returnValue = 0;
		}
		i += 2;
	}

	return returnValue;
}


///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//Serial messaging (if enabled)

#ifdef CFA10006_SERIAL_MESSAGES
// from: http://playground.arduino.cc/Main/Printf
void CFA10060::serPrintFF(const __FlashStringHelper *fmt, ...)
{
	char		tmp[128]; // resulting string limited to 128 chars
	va_list		args;

	va_start(args, fmt);
	vsnprintf_P(tmp, 128, (const char*)fmt, args);
	va_end(args);
	Serial.print(tmp);
}
// from: http://scott.dd.com.au/wiki/Arduino_Static_Strings
void CFA10060::serialPrintP(const char flashString[])
{
	uint8_t		c;
	for(;0x00 != (c = pgm_read_byte(flashString)); flashString++)
		Serial.write(c);
}
#endif //CFA10006_SERIAL_MESSAGES
