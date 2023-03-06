// Intermcu packet decoder
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include "linebuffer.h"
#include "intermcu_packets.h"

/**
 * Force tight packing.
 */
#define PACKED __attribute__((__packed__))

/**
 * Buffer length of an INTERMCU PRINT message
 */
#define INTERMCU_PRINT_BUFF_LENGTH 128

/**
 * The packet types.
 */
typedef enum {
	// UDP
	INTERMCU_PACKETTYPE_INFORM_PACKET = 0x11, ///< Incoming RDP packet
	INTERMCU_PACKETTYPE_UPDATE_PACKET = 0x12, ///< Send an RDP or UDP packet
	INTERMCU_PACKETTYPE_UPDATE_TX_STATE = 0x13, ///< Send tsorRdpState when it changes
	INTERMCU_PACKETTYPE_INFORM_SNIFFER_PACKET = 0x14, ///< Incoming RDP packet when in sniffer mode
	INTERMCU_PACKETTYPE_READ_VERSION = 0x15, ///< Requests the firmware version number
	INTERMCU_PACKETTYPE_REPLY_VERSION = 0x16, ///< Reports the firmware version number
	INTERMCU_PACKETTYPE_INFORM_V2_PACKET = 0x17, ///< Incoming RDP packet (V2)
	INTERMCU_PACKETTYPE_ACK = 0x7F, ///< Generic ACK for RDP traffic

	// RDP (with ACKs)
	// Wifi scanning packets
	INTERMCU_PACKETTYPE_SCAN_REQUEST = 0x35, ///< Perform a scan of local wifi stations and return the results
	INTERMCU_PACKETTYPE_SCAN_RESULTS = 0x36, ///< The overall results of a wifi scan
	INTERMCU_PACKETTYPE_SCAN_DETAIL_REQ = 0x30, ///< Request a single entry result of the wifi scan
	INTERMCU_PACKETTYPE_SCAN_DETAIL = 0x31, ///< The result of a single scan entry

	// Mac get/set
	INTERMCU_PACKETTYPE_GET_MAC = 0x80,  ///< A request for a MAC
	INTERMCU_PACKETTYPE_MAC_RESULTS = 0x33, ///< The response to a MAC request
	INTERMCU_PACKETTYPE_PAIRWITHHOST = 0x83, ///< A bunch of information to pair with the host

	// Wifi control packets
	INTERMCU_PACKETTYPE_AP_CONNECT = 0x96,  ///< Set an active AP and immediately connect to it
	INTERMCU_PACKETTYPE_AP_DISCONNECT = 0x97, ///< Disconnect from an active AP
	INTERMCU_PACKETTYPE_AP_STATUS_REQUEST = 0x2D, ///< Get details of the current AP
	INTERMCU_PACKETTYPE_AP_DETAILS = 0x2C, ///< Details of the current AP
	INTERMCU_PACKETTYPE_AP_WPS_SCAN = 0x98, ///< Start performing a WPS scan
	INTERMCU_PACKETTYPE_AP_WPS_FINISHED = 0x34, ///< Message to indicate that WPS scanning has finished

	// RDP packet protocol
	INTERMCU_PACKETTYPE_RDP_CONFIGURE = 0x20, ///< Set the endpoint for the AP to connect to
	INTERMCU_PACKETTYPE_RDP_DISCONNECT = 0x22, ///< Disconnect from RDP
	INTERMCU_PACKETTYPE_RDP_SEND = 0x2B, ///< Here is an RDP packet (if trioii -> wifi, please send OTA. if wifi -> trioii, informing a remote RDP has arrived)
	INTERMCU_PACKETTYPE_RDP_DNS_LOOKUP = 0x21,  ///< Request a DNS lookup
	INTERMCU_PACKETTYPE_RDP_DNS_RESULTS = 0x2E, ///< Return the results of a DNS lookup

	// Welcome challenge and response
	INTERMCU_PACKETTYPE_WELCOME_CHALLENGE = 0xB0, ///< A challenge request for a welcome packet
	INTERMCU_PACKETTYPE_WELCOME_RESPONSE = 0x32,  ///< The response for a challenge request
	INTERMCU_PACKETTYPE_UNCONFIGURE = 0xB2, ///< Reset all access point settings and go back to factory defaults
	INTERMCU_PACKETTYPE_FACTORY_RESET = 0xB3, ///< Reset all access point settings and go back to factory defaults
	INTERMCU_PACKETTYPE_ENTER_DEEP_SLEEP = 0xB4, ///< Request that the device enters deep sleep mode
	INTERMCU_PACKETTYPE_ENTER_SETUP_MODE = 0x23, ///< Tell the device to enter setup mode
	INTERMCU_PACKETTYPE_ENTER_TEST_MODE = 0x37, ///< Request that the device enters test mode
	INTERMCU_PACKETTYPE_BOOT_RECORD = 0x24, ///< A packet indicating that the wifi chip has booted up

	//Wifi PRINT packets
	INTERMCU_PACKETTYPE_JN_PRINT = 0x38, ///< Print a message on JN's UART0

	// EMC endpoints for the ESP32
	INTERMCU_PACKETTYPE_EMC_CONFIG = 0x40, ///< Set/Get the Emc config (mode, channel, power)
	INTERMCU_PACKETTYPE_EMC_TXRX_COUNTER = 0x41, ///< Get the Tx and Rx counters from the EMC test
	INTERMCU_PACKETTYPE_EMC_WIFI_CONFIG = 0x42, ///< Get the Tx and Rx counters from the EMC test

	//ESP LPC Commands
	INTERMCU_PACKETTYPE_RDP_TO_UNIHUB = 0x45, ///< A command for data between LPC and ESP
	INTERMCU_PACKETTYPE_RDP_FROM_UNIHUB = 0x46,  ///< A command for data between ESP and LPC
	INTERMCU_PACKETTYPE_CHECK_GOTO_SERVER = 0x47,  ///< Check to see whether Trio cloud has a GOTO server
	INTERMCU_PACKETTYPE_UNIHUB_GENERIC_U16 = 0x48,   ///< Send the device list or whatever stuff to Unihub
	INTERMCU_PACKETTYPE_UNIHUB_PAIRING_LED = 0x49, ///< Sends the Unihub pairing LED colour
	INTERMCU_PACKETTYPE_UNIHUB_NETWORK_LED = 0x4A, ///< Sends the Unihub network LED colour
	INTERMCU_PACKETTYPE_UNIHUB_VERSION_NUM = 0x4B,  ///< Sends the Unihub version number
	INTERMCU_PACKETTYPE_UNIHUB_FACTORY_RESET = 0x4C, ///< Sends a factory reset command
	INTERMCU_PACKETTYPE_UNIHUB_TO_TRIO_UI = 0x4D, ///< Sends UI Data to Trio
	INTERMCU_PACKETTYPE_UNIHUB_HTTP_CLOUD_ENV = 0x57, ///< Sends HTTP Cloud environment configuration

	// ESP -> CAD JN Commands
	INTERMCU_PACKETTYPE_SYSTEM_STATUS_REQUEST = 0x70,    ///< Request command for the systems status codes (HAN, Elec, Gas, WiFi and cloud)
	INTERMCU_PACKETTYPE_ZB_NWK_INFO_REQUEST = 0x71,      ///< Request command for the zigbee network info (Status, PAN ID, Short ID, Channel, RSSI)
	INTERMCU_PACKETTYPE_DEVICE_INFO_REQUEST = 0x72,      ///< Request command for the device info (Serial num, EUI, install code, FW version)
	INTERMCU_PACKETTYPE_LEAVE_WIFI_NWK = 0x73,           ///< Request to leave current WiFi network (it is needed to clear the credentials stored in flash)

	// CAD JN -> ESP Commands. Used to provide info to the app when in a local access connection
	INTERMCU_PACKETTYPE_SYSTEM_STATUS_RESULT = 0x78,   ///< Sends the HAN, Elec, Gas, WiFi and cloud error and suberror codes
	INTERMCU_PACKETTYPE_ZB_NWK_INFO_RESULT = 0x79,     ///< Sends the details of the current zibgee network (Status, PAN ID, Short ID, Channel, RSSI)
	INTERMCU_PACKETTYPE_DEVICE_INFO_RESULT = 0x7A,     ///< Sends the details of the device (Serial num, EUI, install code, FW version)
	INTERMCU_PACKETTYPE_RESET_REQUEST = 0x7B,          ///< Request command to reset the user data on the CAD/Trio (uses IntermcuResetTypes)
	INTERMCU_PACKETTYPE_ZB_NWK_ACTION_REQUEST = 0x7C,  ///< Request command to leave/join the current zb network (uses IntermcuZBLeaveJoinTypes)

} IntermcuPackettype_t;

/**
 * subcommands to be used with INTERMCU_PACKETTYPE_UNIHUB_GENERIC_U16 packet type
 */
typedef enum {
  INTERMCU_SUBCMD_DEVICE_LIST = 0x00, // sends device list to Unihub
  INTERMCU_SUBCMD_FIRMWARE_UPGRADES = 0x01, // sends getfirmware upgrades to Unihub

} IntermcuU16PacketSubCmd_t;

/**
 * Inform packet types
 */
typedef enum {
	INTERMCU_INFORM_PACKET_V1 = 0,
	INTERMCU_INFORM_PACKET_V2,
} IntermcuInformPacketTypes;

/**
 * @brief Enumeration of connection states returned from IntermcuApDetailsPacket_t
 */
typedef enum {
    E_WIFI_UNCONNECTED = 0x41,        // Negative range used for internal/trio ii states
    E_WIFI_ENTERING_FLASH_MODE = 0x42,
    E_WIFI_FLASH_MODE_BOOTING = 0x43,
    E_WIFI_FLASH_MODE = 0x44,
    E_WIFI_LEAVING_FLASH_MODE = 0x45,
    E_WIFI_PAIRING_WITH_HOST = 0x46,
    E_WIFI_BATTERY_MODE = 0x47,
    E_WIFI_CHECK_ENABLED_STATUS = 0x48,
    E_WIFI_DISABLED_STATUS = 0x49,
    E_WIFI_IDLE = 0,                // Here on reported / managed by WIFI firmware
    E_WIFI_CONNECTING,

    // -- DEPRECIATED STATES
    E_WIFI_WRONG_PASSWORD,
    E_WIFI_NO_AP_FOUND,
    E_WIFI_CONNECT_FAIL,
    // ------

    E_WIFI_GOT_IP,
    E_WIFI_RDP_CONNECTED,
    E_WIFI_SETUP_MODE,
    E_WIFI_VERIFYING_AP,
    E_WIFI_TEST_MODE,
    E_WIFI_868_TEST_MODE
}IntermcuApConnectionState;

/**
 * @brief Enumeration of reset types to remove user data on the JN
 */
typedef enum {
    E_RESET_SETTINGS = 1,
    E_RESET_DATA = 2,
    E_RESET_ALL = 4,
    E_FACTORY_RESET = 8
}IntermcuResetTypes;

/**
 * @brief Enumeration of zb network request types
 */
typedef enum {
    E_LEAVE= 0,
    E_JOIN = 1
}IntermcuZBLeaveJoinTypes;

/**
 * The large header for inter-MCU packets.
 */
typedef struct {
	uint8_t packetType; ///< Packet type
	uint16_t dataSize; ///< The size of the following data (0..250)
	uint8_t seqNum; ///< Wrapping sequence number
} PACKED IntermcuLgePacketHeader_t;

/**
 * Packet of any or unkown packetType (incomplete type)
 */
typedef struct {
	IntermcuLgePacketHeader_t header;
	uint8_t payload[];
} PACKED IntermcuGenericPacket_t;

/**
 * An ACK packet
 */
typedef struct {
	IntermcuLgePacketHeader_t header; ///< Common packet header
	uint8_t ackPacketType; ///< Packet type we're ACK'ing
} PACKED IntermcuAckPacket_t;

/**
 * @brief An Empty packet - i.e. just the header is received. For events which don't require
 * any data.
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
} PACKED IntermcuEmptyPacket_t;

/**
 * @brief PRINT packet - contains a character to print on JN's UART0
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	char buffToPrint[INTERMCU_PRINT_BUFF_LENGTH]; ///< Characters to send to JN for printing
} PACKED IntermcuPrintPacket_t;

/**
 * @brief Packet to request a wifi scan
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t forceScan; ///< Whether to force a full scan or just retrieve the cached results
} PACKED IntermcuScanRequest_t;

/**
 * @brief Packet to provide the overall results of a scan
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t numStations; ///< The number of stations reported in the last scan
} PACKED IntermcuScanResults_t;

/**
 * @brief Packet to request a station from the result of the scan
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t stationIndex; ///< The index of the station to request
} PACKED IntermcuScanDetailReq_t;

/**
 * @brief Packet to return the detail of a station found during a scan
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t bssid[6]; ///< The base station MAC
	uint8_t ssid[32]; ///< The ssid of the station
	uint8_t ssid_len; ///< How much of the SSID is in use
	uint8_t channel; ///< The channel this AP uses
	int8_t rssi; ///< Detected signal strength
	uint8_t authmode; ///< The authorisation this base station uses
	uint8_t is_hidden; ///< Whether the station is hidden
	int16_t freq_offset; ///< A radio characteristic of the AP, an offset used within the channel to avoid overlap.
	int16_t freqcal_val; ///< A radio characteristic of the AP, an offset used within the channel to avoid overlap.
} PACKED IntermcuScanDetail_t;

/**
 * @brief Packet to transmit a MAC address, either to communicate the existing value
 * or to instruct that it change to a particular value
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t stationMac[6]; ///< The MAC of the station device
	uint8_t softApMac[6]; ///< The MAC of the soft-ap device
} PACKED IntermcuMacPacket_t;

/**
 * @brief Packet to pair the wifi chip with the host system
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t stationMac[6]; ///< The MAC of the station device
	uint8_t softApMac[6]; ///< The MAC of the soft-ap device
	uint8_t setupSsid[32]; ///< The setup SSID
	uint8_t setupPin[16]; ///< The setup PIN
} PACKED IntermcuPairPacket_t;

/**
 * @brief Packet to transmit a set of connection details back to the sender
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t conStatus; ///< The connection status, see ESP wifi_station_get_connect_status for values
	int8_t rssi; ///< The signal strength at the moment
	uint8_t ssid[32]; ///< The SSID currently active
	uint8_t bssid[6]; ///< The MAC of the base station - only valid when connected
	uint32_t deviceIp; ///< The IP of the device on the network, if connected
} PACKED IntermcuApDetailsPacket_t;

/**
 * @brief Packet to request that the wifi chip connects to a particular AP
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t ssid[32]; ///< The 32 byte SSID
	uint8_t pw[64]; ///< 64 bytes of password
} PACKED IntermcuApConnectPacket_t;

/**
 * @brief Packet to request that the current endpoint change. All subsequent UDP packets
 * will go to this point.
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint32_t ip; ///< The endpoint IP
	uint32_t port; ///< The endpoint port
} PACKED IntermcuRdpEndpoint_t;

/**
 * @brief Packet to request a DNS lookup
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t hostName[64]; ///< The hostname to lookup, max 64 bytes (for now), null terminated
} PACKED IntermcuDnsLookup_t;

/**
 * @brief The results of a DNS lookup, the IP
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint32_t ip; ///< The IP found, or 0 if the host was unresolved
} PACKED IntermcuDnsResult_t;

/**
 * @brief A welcome request, 8 bytes of random data
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t challenge[8]; ///< 8 bytes of random challenge data
} PACKED IntermcuWelcomeChallenge_t;

/**
 * @brief A welcome response, the CRC of the 8 bytes of random data
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint16_t response; ///< The challenge response, the CRC of the random data
	uint8_t device_type; ///< The device identifier, should match the ROR schema
	uint8_t major; ///< The device major version
	uint8_t minor; ///< The device minor version
	uint8_t build; ///< The build number
	uint8_t stationMac[6]; ///< The station MAC
	uint8_t softApMac[6]; ///< The soft-AP MAC
	uint8_t serialNumber[16]; ///< The serial number of this device
	uint8_t deviceConfigured; ///< Whether the device has been configured
	uint8_t setupSsid[32]; ///< The setup mode AP name
	uint8_t apPin[16]; ///< Max 16 characters of null terminated ASCII PIN we're using for AP setup
} PACKED IntermcuWelcomeResp_t;

/**
 * @brief Packet to transmit the system status codes when in local access mode
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t han_errorcode; ///< Error code of the HAN
	uint8_t han_suberrcode; ///< Sub error Code of the HAN
	uint8_t elec_errorcode; ///< Error code of the electricity meter
	uint8_t elec_suberrcode; ///< Sub error code of the electricity meter
	uint8_t gas_errorcode; ///< Error code of the gas meter
	uint8_t gas_suberrcode; ///< Sub error code of the gas meter
	uint8_t wifi_errorcode; ///< Error code of the WiFi network
	uint8_t wifi_suberrcode; ///< Sub error code of the WiFi network
	uint8_t cloud_errorcode; ///< Error code of the cloud connection
	uint8_t cloud_suberrcode; ///< Sub error code of the cloud connection
} PACKED IntermcuSystemStatusResult_t;

/**
 * @brief Packet to transmit the zb network details when in local access mode
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t zb_netstatus; ///< Status of the zb network
	uint16_t panid; ///< PAN ID
	uint16_t shortid; /// Short ID (a.k.a Node ID);
	uint8_t channel; ///< Current operating channel
	int8_t zb_rssi; ///< RSSI of the zibgee network signal
} PACKED IntermcuZBNetworkInfoResult_t;

/**
 * @brief Packet to transmit device info when in local access mode
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t serialnumber[16]; ///< serial number of the device
	uint64_t eui; ///< device EUI
	uint8_t installcode[16]; /// Install code
	uint8_t installcodesize; /// size of install code
	uint32_t fwversion; ///< Version of App fw
} PACKED IntermcuDeviceInfoResult_t;

/**
 * @brief Packet to transmit a the ap details stored in manufacturing data when in local access mode
 */
typedef struct {
	IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
	uint8_t ssid[32]; ///< The 32 byte SSID
	uint8_t pw[64]; ///< 64 bytes of password
} PACKED IntermcuManuApPacket_t;

/*
 * @brief Structure for passing the EMC test config
 */
typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint8_t u8Mode;     ///< Mode to set/get, using enum from GEO/Zigbee/geozigbee_MfgTest.h
  uint8_t u8Channel;  ///< Channel to set/get
  uint8_t s8Power;    ///< Power to set/get
  uint8_t u8Command;  ///< Get=0/Set=1
} PACKED IntermcuEmcConfig_t;

typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint16_t u16TxCounter; ///< TxCounter
  uint16_t u16RxCounter; ///< RxCounter
} PACKED IntermcuEmcTxRxCounter_t;

/*
 * @brief Structure for passing the EMC test config
 */
typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint8_t u8OnOff;  /// Turn the access point on or off
  uint8_t u8Channel;  ///< Channel to set/get
} PACKED IntermcuEmcWifiConfig_t;

typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint16_t u16SeqNum;
  uint8_t u8Command;
  uint8_t* psPbuf;
} PACKED IntermcuRdpFromUnihub_t;

typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint8_t* psPbuf;
  uint8_t u8Command;
} PACKED IntermcuRdpToUnihub_t;

typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint8_t bBoolean;
} PACKED IntermcuBoolean_t;

typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint8_t u8Num;
} PACKED IntermcuUint8_t;

typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint16_t u16Num;
} PACKED IntermcuUint16_t;

typedef struct {
  IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for serial port
  uint32_t u32Num;
} PACKED IntermcuUint32_t;

typedef struct {
    uint8_t isHotWaterZone;
    uint8_t isHotWaterOn;
    uint8_t awayMode;
    uint8_t adhoc;
    uint8_t isValidZone;
    uint8_t isZoneCreated;
    uint8_t sensorComms;
    int16_t currentTemp;
    int16_t setTemp;
    int16_t nextSetTemp;
    uint16_t nextEventTimeOffset;
    uint16_t adhocStartTime;
} PACKED IntermcuCosyZoneData_t;

typedef struct {
    IntermcuLgePacketHeader_t intermcuHeader; ///< Intermcu packet header for Cosy UI Data
    IntermcuCosyZoneData_t intermcuCosyZoneData[3];
} PACKED IntermcuCosyUIData_t;


static void handle_INFORM_PACKET         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UPDATE_PACKET         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UPDATE_TX_STATE       (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_INFORM_SNIFFER_PACKET (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_READ_VERSION          (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_REPLY_VERSION         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_INFORM_V2_PACKET      (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_ACK                   (struct linebuffer *lb, const IntermcuAckPacket_t              *packet);
static void handle_SCAN_REQUEST          (struct linebuffer *lb, const IntermcuScanRequest_t            *packet);
static void handle_SCAN_RESULTS          (struct linebuffer *lb, const IntermcuScanResults_t            *packet);
static void handle_SCAN_DETAIL_REQ       (struct linebuffer *lb, const IntermcuScanDetailReq_t          *packet);
static void handle_SCAN_DETAIL           (struct linebuffer *lb, const IntermcuScanDetail_t             *packet);
static void handle_GET_MAC               (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_MAC_RESULTS           (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_PAIRWITHHOST          (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_AP_CONNECT            (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_AP_DISCONNECT         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_AP_STATUS_REQUEST     (struct linebuffer *lb, const IntermcuEmptyPacket_t            *packet);
static void handle_AP_DETAILS            (struct linebuffer *lb, const IntermcuApDetailsPacket_t        *packet);
static void handle_AP_WPS_SCAN           (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_AP_WPS_FINISHED       (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RDP_CONFIGURE         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RDP_DISCONNECT        (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RDP_SEND              (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RDP_DNS_LOOKUP        (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RDP_DNS_RESULTS       (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_WELCOME_CHALLENGE     (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_WELCOME_RESPONSE      (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNCONFIGURE           (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_FACTORY_RESET         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_ENTER_DEEP_SLEEP      (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_ENTER_SETUP_MODE      (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_ENTER_TEST_MODE       (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_BOOT_RECORD           (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_JN_PRINT              (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_EMC_CONFIG            (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_EMC_TXRX_COUNTER      (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_EMC_WIFI_CONFIG       (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RDP_TO_UNIHUB         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RDP_FROM_UNIHUB       (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_CHECK_GOTO_SERVER     (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNIHUB_GENERIC_U16    (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNIHUB_PAIRING_LED    (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNIHUB_NETWORK_LED    (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNIHUB_VERSION_NUM    (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNIHUB_FACTORY_RESET  (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNIHUB_TO_TRIO_UI     (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_UNIHUB_HTTP_CLOUD_ENV (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_SYSTEM_STATUS_REQUEST (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_ZB_NWK_INFO_REQUEST   (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_DEVICE_INFO_REQUEST   (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_LEAVE_WIFI_NWK        (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_SYSTEM_STATUS_RESULT  (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_ZB_NWK_INFO_RESULT    (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_DEVICE_INFO_RESULT    (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_RESET_REQUEST         (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_ZB_NWK_ACTION_REQUEST (struct linebuffer *lb, const IntermcuGenericPacket_t          *packet);
static void handle_incorrect_length      (struct linebuffer *lb, const uint8_t *data, uint32_t count);
static void handle_unknown_type          (struct linebuffer *lb, const uint8_t *data, uint32_t count);

// Function to describe an intermcu packet
// the function should output text to the linebuffer argument
// the data argument points to the packet header (excluding the sync bytes)
// the count argument includes the header and payload but not the sync bytes or trailing CRC
// the function should return one of normal_color or bold_color depending how important or unusual the packet is
uint8_t intermcu_packet(struct linebuffer *lb,
                        const uint8_t     *data,
                        uint32_t           count,
                        uint8_t            normal_color,
                        uint8_t            bold_color)
{
  const IntermcuGenericPacket_t *genericPacket = (const void*)data;

  switch (genericPacket->header.packetType)
  {
    case INTERMCU_PACKETTYPE_INFORM_PACKET:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_INFORM_PACKET               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UPDATE_PACKET:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UPDATE_PACKET               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UPDATE_TX_STATE:           if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UPDATE_TX_STATE             (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_INFORM_SNIFFER_PACKET:     if (count == sizeof(IntermcuEmptyPacket_t)){ handle_INFORM_SNIFFER_PACKET       (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_READ_VERSION:              if (count == sizeof(IntermcuEmptyPacket_t)){ handle_READ_VERSION                (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_REPLY_VERSION:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_REPLY_VERSION               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_INFORM_V2_PACKET:          if (count == sizeof(IntermcuEmptyPacket_t)){ handle_INFORM_V2_PACKET            (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_ACK:                       if (count == sizeof(IntermcuAckPacket_t  )){ handle_ACK                         (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_SCAN_REQUEST:              if (count == sizeof(IntermcuScanRequest_t)){ handle_SCAN_REQUEST                (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_SCAN_RESULTS:              if (count == sizeof(IntermcuScanResults_t)){ handle_SCAN_RESULTS                (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_SCAN_DETAIL_REQ:           if (count == sizeof(IntermcuScanDetailReq_t)){ handle_SCAN_DETAIL_REQ           (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_SCAN_DETAIL:               if (count == sizeof(IntermcuScanDetail_t)){ handle_SCAN_DETAIL                  (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_GET_MAC:                   if (count == sizeof(IntermcuEmptyPacket_t)){ handle_GET_MAC                     (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_MAC_RESULTS:               if (count == sizeof(IntermcuEmptyPacket_t)){ handle_MAC_RESULTS                 (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_PAIRWITHHOST:              if (count == sizeof(IntermcuEmptyPacket_t)){ handle_PAIRWITHHOST                (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_AP_CONNECT:                if (count == sizeof(IntermcuEmptyPacket_t)){ handle_AP_CONNECT                  (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_AP_DISCONNECT:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_AP_DISCONNECT               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_AP_STATUS_REQUEST:         if (count == sizeof(IntermcuEmptyPacket_t)){ handle_AP_STATUS_REQUEST           (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_AP_DETAILS:                if (count == sizeof(IntermcuApDetailsPacket_t)){ handle_AP_DETAILS              (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_AP_WPS_SCAN:               if (count == sizeof(IntermcuEmptyPacket_t)){ handle_AP_WPS_SCAN                 (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_AP_WPS_FINISHED:           if (count == sizeof(IntermcuEmptyPacket_t)){ handle_AP_WPS_FINISHED             (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RDP_CONFIGURE:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RDP_CONFIGURE               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RDP_DISCONNECT:            if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RDP_DISCONNECT              (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RDP_SEND:                  if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RDP_SEND                    (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RDP_DNS_LOOKUP:            if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RDP_DNS_LOOKUP              (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RDP_DNS_RESULTS:           if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RDP_DNS_RESULTS             (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_WELCOME_CHALLENGE:         if (count == sizeof(IntermcuEmptyPacket_t)){ handle_WELCOME_CHALLENGE           (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_WELCOME_RESPONSE:          if (count == sizeof(IntermcuEmptyPacket_t)){ handle_WELCOME_RESPONSE            (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNCONFIGURE:               if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNCONFIGURE                 (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_FACTORY_RESET:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_FACTORY_RESET               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_ENTER_DEEP_SLEEP:          if (count == sizeof(IntermcuEmptyPacket_t)){ handle_ENTER_DEEP_SLEEP            (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_ENTER_SETUP_MODE:          if (count == sizeof(IntermcuEmptyPacket_t)){ handle_ENTER_SETUP_MODE            (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_ENTER_TEST_MODE:           if (count == sizeof(IntermcuEmptyPacket_t)){ handle_ENTER_TEST_MODE             (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_BOOT_RECORD:               if (count == sizeof(IntermcuEmptyPacket_t)){ handle_BOOT_RECORD                 (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_JN_PRINT:                  if (count >= sizeof(IntermcuEmptyPacket_t)){ handle_JN_PRINT                    (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_EMC_CONFIG:                if (count == sizeof(IntermcuEmptyPacket_t)){ handle_EMC_CONFIG                  (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_EMC_TXRX_COUNTER:          if (count == sizeof(IntermcuEmptyPacket_t)){ handle_EMC_TXRX_COUNTER            (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_EMC_WIFI_CONFIG:           if (count == sizeof(IntermcuEmptyPacket_t)){ handle_EMC_WIFI_CONFIG             (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RDP_TO_UNIHUB:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RDP_TO_UNIHUB               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RDP_FROM_UNIHUB:           if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RDP_FROM_UNIHUB             (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_CHECK_GOTO_SERVER:         if (count == sizeof(IntermcuEmptyPacket_t)){ handle_CHECK_GOTO_SERVER           (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNIHUB_GENERIC_U16:        if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNIHUB_GENERIC_U16          (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNIHUB_PAIRING_LED:        if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNIHUB_PAIRING_LED          (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNIHUB_NETWORK_LED:        if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNIHUB_NETWORK_LED          (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNIHUB_VERSION_NUM:        if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNIHUB_VERSION_NUM          (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNIHUB_FACTORY_RESET:      if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNIHUB_FACTORY_RESET        (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNIHUB_TO_TRIO_UI:         if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNIHUB_TO_TRIO_UI           (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_UNIHUB_HTTP_CLOUD_ENV:     if (count == sizeof(IntermcuEmptyPacket_t)){ handle_UNIHUB_HTTP_CLOUD_ENV       (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_SYSTEM_STATUS_REQUEST:     if (count == sizeof(IntermcuEmptyPacket_t)){ handle_SYSTEM_STATUS_REQUEST       (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_ZB_NWK_INFO_REQUEST:       if (count == sizeof(IntermcuEmptyPacket_t)){ handle_ZB_NWK_INFO_REQUEST         (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_DEVICE_INFO_REQUEST:       if (count == sizeof(IntermcuEmptyPacket_t)){ handle_DEVICE_INFO_REQUEST         (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_LEAVE_WIFI_NWK:            if (count == sizeof(IntermcuEmptyPacket_t)){ handle_LEAVE_WIFI_NWK              (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_SYSTEM_STATUS_RESULT:      if (count == sizeof(IntermcuEmptyPacket_t)){ handle_SYSTEM_STATUS_RESULT        (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_ZB_NWK_INFO_RESULT:        if (count == sizeof(IntermcuEmptyPacket_t)){ handle_ZB_NWK_INFO_RESULT          (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_DEVICE_INFO_RESULT:        if (count == sizeof(IntermcuEmptyPacket_t)){ handle_DEVICE_INFO_RESULT          (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_RESET_REQUEST:             if (count == sizeof(IntermcuEmptyPacket_t)){ handle_RESET_REQUEST               (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    case INTERMCU_PACKETTYPE_ZB_NWK_ACTION_REQUEST:     if (count == sizeof(IntermcuEmptyPacket_t)){ handle_ZB_NWK_ACTION_REQUEST       (lb, (const void*)data); return normal_color; }else{ handle_incorrect_length(lb, data, count); return bold_color; }
    default:
      handle_unknown_type(lb, data, count);
      return bold_color;
  }
}

static void handle_INFORM_PACKET(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UPDATE_PACKET(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UPDATE_TX_STATE(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_INFORM_SNIFFER_PACKET(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_READ_VERSION(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_REPLY_VERSION(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_INFORM_V2_PACKET(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_ACK(struct linebuffer *lb, const IntermcuAckPacket_t *packet)
{
  linebuffer_printf(lb, "ack(seq=%u,type=%02X)", packet->header.seqNum, packet->ackPacketType);
}

static void handle_SCAN_REQUEST(struct linebuffer *lb, const IntermcuScanRequest_t *packet)
{
  linebuffer_printf(lb, "SCAN_REQUEST(force=%u)", packet->forceScan);
}

static void handle_SCAN_RESULTS(struct linebuffer *lb, const IntermcuScanResults_t *packet)
{
  linebuffer_printf(lb, "SCAN_RESULTS(numStations=%u)", packet->numStations);
}

static void handle_SCAN_DETAIL_REQ(struct linebuffer *lb, const IntermcuScanDetailReq_t *packet)
{
  linebuffer_printf(lb, "SCAN_DETAIL_REQ(stationIndex=%u)", packet->stationIndex);
}

static void handle_SCAN_DETAIL(struct linebuffer *lb, const IntermcuScanDetail_t *packet)
{
  uint32_t ssid_length = sizeof(packet->ssid);

  if (packet->ssid_len < ssid_length)
  {
    ssid_length = packet->ssid_len;
  }

  linebuffer_printf(lb, "SCAN_DETAILS BSSID=%02X:%02X:%02X:%02X:%02X:%02X SSID=",
    packet->bssid[0], packet->bssid[1], packet->bssid[2], packet->bssid[3], packet->bssid[4], packet->bssid[5]);

  linebuffer_print_string(lb, packet->ssid, ssid_length);

  linebuffer_printf(lb, " CH=%u RSSI=%i AUTHMODE=%u HID=%u Foffs=%i Fcalv=%i",
    (unsigned int)packet->channel,
    (int)packet->rssi,
    (unsigned int)packet->authmode,
    (unsigned int)packet->is_hidden,
    (int)packet->freq_offset,
    (int)packet->freqcal_val);
}

static void handle_GET_MAC(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_MAC_RESULTS(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_PAIRWITHHOST(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_AP_CONNECT(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_AP_DISCONNECT(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_AP_STATUS_REQUEST(struct linebuffer *lb, const IntermcuEmptyPacket_t *packet)
{
  linebuffer_printf(lb, "AP_STATUS_REQUEST");
}

static void handle_AP_DETAILS(struct linebuffer *lb, const IntermcuApDetailsPacket_t *packet)
{
  linebuffer_printf(lb, "AP_DETAILS=%u RSSI=%i SSID=",
    (unsigned int)packet->conStatus, // FIXME enum to string
    (int)packet->rssi);

  linebuffer_print_string(lb, packet->ssid, sizeof(packet->ssid));

  linebuffer_printf(lb, " BSSID=%02X:%02X:%02X:%02X:%02X:%02X IP=%u.%u.%u.%u",
    packet->bssid[0], packet->bssid[1], packet->bssid[2], packet->bssid[3], packet->bssid[4], packet->bssid[5],
    (unsigned int)((packet->deviceIp >> 24) & 0xFF), (unsigned int)((packet->deviceIp >> 16) & 0xFF), (unsigned int)((packet->deviceIp >>  8) & 0xFF), (unsigned int)((packet->deviceIp >>  0) & 0xFF));
}

static void handle_AP_WPS_SCAN(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_AP_WPS_FINISHED(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RDP_CONFIGURE(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RDP_DISCONNECT(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RDP_SEND(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RDP_DNS_LOOKUP(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RDP_DNS_RESULTS(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_WELCOME_CHALLENGE(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_WELCOME_RESPONSE(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNCONFIGURE(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_FACTORY_RESET(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_ENTER_DEEP_SLEEP(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_ENTER_SETUP_MODE(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_ENTER_TEST_MODE(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_BOOT_RECORD(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_JN_PRINT(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "PRINT");
  linebuffer_print_string(lb, packet->payload, packet->header.dataSize);
}

static void handle_EMC_CONFIG(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_EMC_TXRX_COUNTER(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_EMC_WIFI_CONFIG(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RDP_TO_UNIHUB(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RDP_FROM_UNIHUB(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_CHECK_GOTO_SERVER(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNIHUB_GENERIC_U16(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNIHUB_PAIRING_LED(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNIHUB_NETWORK_LED(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNIHUB_VERSION_NUM(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNIHUB_FACTORY_RESET(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNIHUB_TO_TRIO_UI(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_UNIHUB_HTTP_CLOUD_ENV(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_SYSTEM_STATUS_REQUEST(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_ZB_NWK_INFO_REQUEST(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_DEVICE_INFO_REQUEST(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_LEAVE_WIFI_NWK(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_SYSTEM_STATUS_RESULT(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_ZB_NWK_INFO_RESULT(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_DEVICE_INFO_RESULT(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_RESET_REQUEST(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_ZB_NWK_ACTION_REQUEST(struct linebuffer *lb, const IntermcuGenericPacket_t *packet)
{
  linebuffer_printf(lb, "unimplemented packet type x%02X:", packet->header.packetType);
  linebuffer_print_hex(lb, packet->payload, packet->header.dataSize);
}

static void handle_incorrect_length(struct linebuffer *lb, const uint8_t *data, uint32_t count)
{
  linebuffer_printf(lb, "packet type x%02X incorrect length %u:", data[0], (unsigned int)count);
  linebuffer_print_hex(lb, data, count);
}

static void handle_unknown_type(struct linebuffer *lb, const uint8_t *data, uint32_t count)
{
  linebuffer_printf(lb, "unknown packet type x%02X length %u:", data[0], (unsigned int)count);
  linebuffer_print_hex(lb, data, count);
}
