/******************************************************************
  * File Name     : consumer.h
  * Description   : 
  *
  * Copyright (C) 2016 Yangguang Li
  * Mail          : liyggyj@163.com
  * Author        : Yangguang Li
  * Created time  : 2016-12-13 03:04:23 PM
  * Last modified : 2016-12-13 03:04:23 PM
******************************************************************/
#ifndef __CONSUME_H__
# define  __CONSUME_H__
# include <stdio.h>
# include "data.h"
# include "resource.h"

void consumer_register();

void consumer_register()
{
    //int n = 10;
    while ((sleep(1), 1)) {
        printf ("start consume...\n");
        Resource *re = Resource::get_instance();
        Data *p = re->take_out();
        printf ("get data: %p\n", p);
        if (p) {
            printf ("geted data: %p\n", p);
            dataShow(p);
        }

        dataFree(p);
    }

}

#endif
