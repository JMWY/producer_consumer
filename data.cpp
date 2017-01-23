/******************************************************************
  * File Name     : data.cpp
  * Description   : 
  *
  * Copyright (C) 2016 Yangguang Li
  * Mail          : liyggyj@163.com
  * Author        : Yangguang Li
  * Created time  : 2016-12-14 10:06:26 AM
  * Last modified : 2016-12-14 10:06:26 AM
******************************************************************/

#include "data.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int checkDataComplet(Data *pdata)
{
    if (pdata) {
        //printf ("do filed check\n");
        dataCheckField(pdata->field, -1);
        //printf ("do type check\n");
        dataCheckType(pdata->type, -1);
        //printf ("type check done\n");
        return 0;
    }
    return -1;
}

char *dataFieldAssign(char *dest, const char *src)
{
    size_t n = strlen(src);
    char *ret;
    if (DATA_FIELD_LENGTH -1 <  n) {
        return NULL;
    }

    ret = strncpy(dest, src, n);
    dest[n] = '\0';
    return ret;
}

int dataAssign(Data *pdata, const char *name, DataType type, ...)
{
    if (!pdata) {
        printf ("pointer is NULL\n");
        return -1;
    }
    
    char *str;
    va_list ap;
    
    va_start(ap, type);

    if (dataFieldAssign(pdata->field, name) == NULL) {
        return -1;
    }
    pdata->type = type;
    switch (type) {
    case DATA_TYPED_INT:
        pdata->value.i = va_arg(ap, int32_t);
        break;
    case DATA_TYPED_UINT:
        pdata->value.ui = va_arg(ap, uint32_t);
        break;
    case DATA_TYPED_LLONG:
        pdata->value.ll = va_arg(ap, int64_t);
        break;
    case DATA_TYPED_ULLONG:
        pdata->value.ull = va_arg(ap, uint64_t);
        break;
    case DATA_TYPED_DOUBLE:
        pdata->value.d = va_arg(ap, double);
        break;
    case DATA_TYPED_BOOLEAN:
        pdata->value.b = !!va_arg(ap, int);
        break;
    case DATA_TYPED_STRING:
        str = va_arg(ap, char *);
        printf ("assign str: %s\n", str);
        if (str && !(pdata->value.s = strdup(str))) {
            printf ("assign pdata->value.s error: %s\n", pdata->value.s);
            return -1;
        }
        break;
    default:
        printf("assign value failed, for no found type supported\n");
        return -1;
    }
    return 0;
}

void dataShow(Data *p)
{
    
    printf ("data->field: %s\n", p->field);
    printf ("data->type: 0x%x\n", p->type);
    if (DATA_TYPED_STRING == p->type) {
        printf ("data->value: %s\n", p->value.s);
    } else if (DATA_TYPED_DOUBLE == p->type) {
        printf ("data->value: %.2f\n", p->value.d);
    } else {
        printf ("data->value: 0x%x\n", p->value.ui);
    }

}

void dataFree(Data *p)
{
    if (p) {
        if (DATA_TYPED_STRING == p->type) {
            free(p->value.s);
        }
        free(p);
        p = NULL;
    }
}




