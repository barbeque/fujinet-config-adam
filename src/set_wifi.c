/**
 * FujiNet for #Adam configuration program
 *
 * Set new WiFi connection
 */

#include <string.h>
#include "set_wifi.h"
#include "die.h"

#ifdef BUILD_ADAM
#include "adam/io.h"
#include "adam/fuji_typedefs.h"
#include "adam/screen.h"
#include "adam/bar.h"
#include "adam/input.h"
#include "adam/globals.h"
#endif /* BUILD_ADAM */

#ifdef BUILD_APPLE2
#include "apple2/io.h"
#include "apple2/fuji_typedefs.h"
#include "apple2/screen.h"
#include "apple2/bar.h"
#include "apple2/input.h"
#include "apple2/globals.h"
#endif /* BUILD_APPLE2 */

#ifdef BUILD_C64
#include "c64/io.h"
#include "c64/fuji_typedefs.h"
#include "c64/screen.h"
#include "c64/bar.h"
#include "c64/input.h"
#include "c64/globals.h"
#endif /* BUILD_APPLE2 */

#ifdef BUILD_PC8801
#include "pc8801/io.h"
#include "pc8801/fuji_typedefs.h"
#include "pc8801/screen.h"
#include "pc8801/bar.h"
#include "pc8801/input.h"
#include "pc8801/globals.h"
#endif /* BUILD_PC8801 */

#ifdef BUILD_PC6001
#include "pc6001/io.h"
#include "pc6001/fuji_typedefs.h"
#include "pc6001/screen.h"
#include "pc6001/bar.h"
#include "pc6001/input.h"
#include "pc6001/globals.h"
#endif /* BUILD_PC6001 */

WSSubState ws_subState;

NetConfig nc;

static unsigned char numNetworks;

void set_wifi_set_ssid(unsigned char i)
{
  SSIDInfo *s = io_get_scan_result(i);
  memcpy(nc.ssid,s->ssid,32);
}

void set_wifi_select(void)
{
  unsigned char k=0;
  
  screen_set_wifi_select_network(numNetworks);

  bar_set(0,3,numNetworks,0);

  while(ws_subState==WS_SELECT)
    ws_subState=input_set_wifi_select();
}

void set_wifi_custom(void)
{
  screen_set_wifi_custom();
  input_line_set_wifi_custom(nc.ssid);
  ws_subState=WS_PASSWORD;
}

void set_wifi_password(void)
{
  screen_set_wifi_password();
  input_line_set_wifi_password(nc.password);
  ws_subState=WS_DONE;
}

void set_wifi_scan(void)
{
  char i;
  
  screen_set_wifi(io_get_adapter_config());

  numNetworks = io_scan_for_networks();

  if (numNetworks > 16)
    numNetworks = 16;

  if (io_error())
    {
      screen_error("COULD NOT WS_SCAN NETWORKS");
      die();
    }

  for (i=0;i<numNetworks;i++)
    {
      SSIDInfo *s = io_get_scan_result(i);
      screen_set_wifi_display_ssid(i,s);
    }

  ws_subState=WS_SELECT;
}

void set_wifi_done(void)
{
  io_set_ssid(&nc);
  state=CONNECT_WIFI;
}

void set_wifi(void)
{
  while (state == SET_WIFI)
    {
      switch(ws_subState)
	{
	case WS_SCAN:
	  set_wifi_scan();
	  break;
	case WS_SELECT:
	  set_wifi_select();
	  break;
	case WS_CUSTOM:
	  set_wifi_custom();
	  break;
	case WS_PASSWORD:
	  set_wifi_password();
	  break;
	case WS_DONE:
	  set_wifi_done();
	  break;
	}
    }
}
