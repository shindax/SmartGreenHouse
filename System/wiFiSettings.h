#ifdef WORK_WI_FI
#define SSID      "OOO OKB Mikron"; 
#define PASSWORD  "7d2_495N"; 
#elif HOME_WI_FI
#define SSID      "shAsus";
#define PASSWORD  "StanislavShendakov7036";
#elif GREENHOUSE_WI_FI
#define SSID      "MERCUSYS_666C";
#define PASSWORD  "79701846";
#elif MY_REDME_WI_FI
#define SSID      "shRedmiNote";
#define PASSWORD  "shindax110";
#else
  #error "WI-FI point must be defined"
#endif

void wiFiConnect( const char* ssid, const char* password );
String getBoardMAC( void );
const char * getBoardName( String MAC );