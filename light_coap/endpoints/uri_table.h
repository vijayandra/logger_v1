#ifndef __URI_TABLE_H
#define __URI_TABLE_H

enum
{
    enDev_Version,
    enDev_Capabiliry,
    enDev_Memory
};

typedef struct
{
    char  uri[40];
    short len;
} lURI;

typedef struct
{
    char  uri1[20];
    char  uri2[20];
    short len1;
    short len2;
} sURI;

typedef struct
{
    short uri_idx;
    lURI  luri;
    sURI  suri;
} URI_Ref;

extern const URI_Ref URIList[];

#endif
