/**
 * FujiNet for #Adam configuration program
 *
 * Perform Copy operation
 */

#include <conio.h>
#include <string.h>

#ifdef BUILD_ADAM
#include "adam/fuji_typedefs.h"
#include "adam/screen.h"
#include "adam/io.h"
#include "adam/globals.h"
#include "adam/input.h"
#include "adam/bar.h"
#endif /* BUILD_ADAM */

#ifdef BUILD_APPLE2
#include "apple2/fuji_typedefs.h"
#include "apple2/screen.h"
#include "apple2/io.h"
#include "apple2/globals.h"
#include "apple2/input.h"
#include "apple2/bar.h"
#endif /* BUILD_APPLE2 */

#ifdef BUILD_C64
#include "c64/fuji_typedefs.h"
#include "c64/screen.h"
#include "c64/io.h"
#include "c64/globals.h"
#include "c64/input.h"
#include "c64/bar.h"
#endif /* BUILD_C64 */

#ifdef BUILD_PC8801
#include "pc8801/fuji_typedefs.h"
#include "pc8801/screen.h"
#include "pc8801/io.h"
#include "pc8801/globals.h"
#include "pc8801/input.h"
#include "pc8801/bar.h"
#endif /* BUILD_PC8801 */

#ifdef BUILD_PC6001
#include "pc6001/fuji_typedefs.h"
#include "pc6001/screen.h"
#include "pc6001/io.h"
#include "pc6001/globals.h"
#include "pc6001/input.h"
#include "pc6001/bar.h"
#endif /* BUILD_Pc6001 */

#include "perform_copy.h"

char copy_destination_path[128];
char copy_host_name[32];
unsigned char copy_host_slot;

void perform_copy(void)
{
  clrscr();
  screen_perform_copy(hostSlots[selected_host_slot],source_path,hostSlots[copy_host_slot],path);
  while(1);
}
