/**
 * FujiNet for #Adam configuration program
 *
 * Connect to existing WiFi connection
 */

#include <string.h>
#include "connect_wifi.h"

#ifdef BUILD_ADAM
#include "adam/io.h"
#include "adam/screen.h"
#include "adam/globals.h"
#endif /* BUILD_ADAM */

#ifdef BUILD_APPLE2
#include "apple2/io.h"
#include "apple2/screen.h"
#include "apple2/globals.h"
#endif /* BUILD_APPLE2 */

#ifdef BUILD_C64
#include "c64/io.h"
#include "c64/screen.h"
#include "c64/globals.h"
#endif /* BUILD_C64 */

#ifdef BUILD_PC8801
#include "pc8801/io.h"
#include "pc8801/screen.h"
#include "pc8801/globals.h"
#endif /* BUILD_PC8801 */

#ifdef BUILD_PC6001
#include "pc6001/io.h"
#include "pc6001/screen.h"
#include "pc6001/globals.h"
#endif /* BUILD_PC6001 */

void connect_wifi(void)
{
  unsigned char retries=20;
  NetConfig nc;
  unsigned char s;
    
  memcpy(&nc,io_get_ssid(),sizeof(NetConfig));

  state = SET_WIFI;
  
  screen_connect_wifi(&nc);

  while (retries>0)
    {
      s=io_get_wifi_status();
      switch (s)
	{
	case 1:
	  screen_error("  NO SSID AVAILABLE.");
	  return;
	case 3:
	  screen_error("  CONNECTION SUCCESSFUL.");
	  state=HOSTS_AND_DEVICES;
	  return;
	case 4:
	  screen_error("  CONNECT FAILED.");
	  return;
	case 5:
	  screen_error("  CONNECTION LOST.");
	  return;
	default:
	  retries--;
	  break;
	}
    }

  screen_error("  UNABLE TO CONNECT.");
  state=SET_WIFI;
}
