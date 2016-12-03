#ifndef __GLOBAL_VAR__PIC32_IWSCOPE_IWSCOPE
#define __GLOBAL_VAR__PIC32_IWSCOPE_IWSCOPE
#include "options.h"
//#include "firm_struct.h"

#define  ENUART1 0
#define  ENUART2 1
#define  ENUART3 2

#ifndef _SPECIAL_INCLUDE_C
#define FIX_EXTERN extern
#else
#define FIX_EXTERN
#endif


FIX_EXTERN unsigned char crx_buff[BUFFER_LEN];
FIX_EXTERN unsigned char ctx_buff[BUFFER_LEN];
FIX_EXTERN unsigned char rsp[1500];
FIX_EXTERN unsigned char scratch_raw[1500];
FIX_EXTERN unsigned char *endpoint_ptr;

#endif
