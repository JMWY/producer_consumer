/******************************************************************
  * File Name     : producer.h
  * Description   : 
  *
  * Copyright (C) 2016 Yangguang Li
  * Mail          : liyggyj@163.com
  * Author        : Yangguang Li
  * Created time  : 2016-12-13 02:36:22 PM
  * Last modified : 2016-12-13 02:36:22 PM
******************************************************************/
#ifndef __PRODUCER_H__
# define __PRODUCER_H__

# include <stdio.h>
# include <pthread.h>
# include "data.h"
# include "resource.h"

void producer_register();

void *pro1(void *arg);
void *pro2(void *arg);


ThreadInfo pinfo[] = {
{
   .name = "producer thread A",
   .descripe = "do print number: 0~9"
},
{
   .name = "producer thread B",
   .descripe = "do print number: 10~19"
}

};	


void *pro1(void *arg) {
    int val=10;
    ThreadInfo *p = (thrd_info *)arg;
    printf("produce 1: %s\n", p->name);
    printf("produce 1: %s\n", p->descripe);
    while ((sleep(1), val--)) {
        Data *pdata = (Data *)malloc(sizeof(struct Data));
        dataAssign(pdata, p->name, DATA_TYPED_STRING, "A");
        if(pdata)
            Resource::get_instance()->put_in(pdata);
    }
        
		//printf ("%d%c", val++ % 10 , (val % 10 == 9)? '\n' : '\t');
    return (void *)1;
}

void *pro2(void *arg) {
    int val=5;
    printf("produce 2: %s\n", ((ThreadInfo *)arg)->name);
    printf("produce 2: %s\n", ((ThreadInfo *)arg)->descripe);
    while (val--) {
        Data *pdata = (Data *)malloc(sizeof(struct Data));
        dataAssign(pdata, ((ThreadInfo *)arg)->name, DATA_TYPED_STRING, "B");
        if(pdata)
            Resource::get_instance()->put_in(pdata);
		//fprintf (stdout, "%d%c", val++ % 10 + 10, (val % 10 == 9) ? '\n' : '\t');
		sleep(1);
    }
    return (void *)2;
}


void producer_register()
{

        pthread_t pid1;
        pthread_t pid2;
        void *status1;
        void *status2;
        pthread_create(&pid1, NULL, pro1, (void *)pinfo);
        pthread_create(&pid2, NULL, pro2, (void *)(pinfo+1));
        pthread_join(pid1, &status1);
        printf ("pthread1 returned: %p\n", status1);
        pthread_join(pid2, &status2);
        printf ("pthread2 returned: %p\n", status2);
}


#endif
