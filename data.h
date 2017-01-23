/******************************************************************
  * File Name     : data.h
  * Description   : 
  *
  * Copyright (C) 2016 Yangguang Li
  * Mail          : liyggyj@163.com
  * Author        : Yangguang Li
  * Created time  : 2016-12-14 10:00:40 AM
  * Last modified : 2016-12-14 10:00:40 AM
******************************************************************/
#ifndef __DATA_H__
#define __DATA_H__
 
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define DATA_FIELD_LENGTH  80

typedef enum {
    DATA_TYPED_INT     = 1 << 0, /* integer case */
    DATA_TYPED_UINT    = 1 << 1, /* unsigned integer case */
    DATA_TYPED_LLONG   = 1 << 2, /* long long case */
    DATA_TYPED_ULLONG  = 1 << 3, /* unsigned long long case */
    DATA_TYPED_DOUBLE  = 1 << 4, /* double case */
    DATA_TYPED_BOOLEAN = 1 << 5, /* boolean(character) case */
    DATA_TYPED_STRING  = 1 << 6, /* string case */
} DataType;

typedef struct Data{
    char field[DATA_FIELD_LENGTH];
    DataType type;
    union {
        int32_t i;          /* type is INT */
        uint32_t ui;        /* type is UINT */
        int64_t ll;         /* type is LLONG */
        uint64_t ull;       /* type is ULLONG */
        double d;           /* type is DOUBLE */
        char b;             /* type is BOOLEN */
        char *s;            /* type is STRING */
    } value;

} Data;

# define dataCheckType(type, retval)               \
    do {                                           \
        if (!(type & 0x7f) || (type & (type-1))) {             \
            return retval;                         \
        }                                          \
    } while(0)

# define dataCheckField(field, retval)             \
    do {                                           \
        if (!field) {                              \
            return retval;                          \
        }                                          \
    } while(0)

int checkDataComplet(Data *pdata);

static char *dataFieldAssign(char *dest, const char *src);

int dataAssign(Data *pdata, const char *name, DataType type, ...);

# define makeData(name, type, ...)                            \
    do {                                                      \
        Data *pdata = (Data *)malloc(sizeof(struct Data));    \
        if (dataAssign(pdata, name, type, __VA_ARGS__) < 0) { \
            free(pdata);                                      \
            pdata = NULL;                                     \
        }                                                     \
        return pdata;                                         \
    } while(0)

void dataShow(Data *pdata);

void dataFree(Data *pdata);


typedef struct ThreadInfo{
    const char *name;
    const char *descripe;
    int nbrothers;
} ThreadInfo;


#endif
