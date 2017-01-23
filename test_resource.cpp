/******************************************************************
  * File Name     : test_resource.h
  * Description   : 
  *
  * Copyright (C) 2016 Yangguang Li
  * Mail          : liyggyj@163.com
  * Author        : Yangguang Li
  * Created time  : 2016-12-13 10:36:00 PM
  * Last modified : 2016-12-13 10:36:00 PM
******************************************************************/

#include "resource.h"
#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>

int main()
{
    Resource* re = Resource::get_instance();
    for (int i = 0; i < 5; ++i) {
        Data *pdata = (Data *)malloc(sizeof(Data));
        if (pdata) {
            //dataAssign(pdata, "fieldInt", DATA_TYPED_INT, -999);
            //dataAssign(pdata, "fieldUInt", DATA_TYPED_UINT, 999);
            //dataAssign(pdata, "fieldBoolean", DATA_TYPED_BOOLEAN, 1);
            dataAssign(pdata, "fieldString", DATA_TYPED_STRING, "choose method A");
        }
        re->put_in(pdata);
    }
    while (re->get_size()) {
        printf ("There has %lu Data exist.\n", re->get_size());
        Data *p = re->take_out();
        if (p) {
            printf ("data->field: %s\n", p->field);
            printf ("data->type: 0x%x\n", p->type);
            if (DATA_TYPED_STRING == p->type)
                printf ("data->value: %s\n", p->value.s);
        }

    }
}
