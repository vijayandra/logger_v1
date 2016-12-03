#ifndef __ENDPOINT_H
#define __ENDPOINT_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define COAP_VERSION_LEN            6
#define COAP_FILE_READ_LEN_MAX    256
#define COAP_FILE_LEN             32

typedef unsigned long int  COAP_lenum;
typedef unsigned short     COAP_senum;


typedef struct
{
    unsigned short int  MsgId;
    unsigned short int  MsgLen;
} MsgTag;

typedef char (DeviceIdStr)[COAP_VERSION_LEN];
typedef char (FileDataStr)[COAP_FILE_READ_LEN_MAX];
typedef char (XFileName)[ COAP_FILE_LEN ];

typedef struct
{
    MsgTag         Tag;
    DeviceIdStr    DevVer;
    DeviceIdStr    DevID;
} DeviceCapabilities;

typedef struct
{
    MsgTag         Tag;
    COAP_lenum     off;
    COAP_senum     len;
    FileDataStr    data;
} FileData;

typedef struct
{
    MsgTag         Tag;
    XFileName      fname;
} TFileName;

#endif
