/******************************************************************
  * File Name     : resource.h
  * Description   : 
  *
  * Copyright (C) 2016 Yangguang Li
  * Mail          : liyggyj@163.com
  * Author        : Yangguang Li
  * Created time  : 2016-12-13 03:35:06 PM
  * Last modified : 2016-12-13 03:35:06 PM
******************************************************************/
#ifndef __RESOURCE_H__
# define __RESOURCE_H__

# include "singleton.h"
# include "data.h"
# include <list>
# include <cstdlib>
# include <cstddef>
# include <stdio.h>


class Resource : public Singleton<Resource>
{
    friend class Singleton<Resource>;
    public:
        void put_in(Data* pdata);
        Data *take_out();
        //bool empty();
        size_t get_size() { return list_sz; }

    protected:
        Resource(): Singleton<Resource>(), list_sz(0) {}
        virtual ~Resource();
    private:
        std::list<Data *> _data_list;
        size_t list_sz;
};

inline void
Resource::put_in(Data* pdata)
{
    if (checkDataComplet(pdata) >= 0) {
        _data_list.push_front(pdata);
        ++list_sz;
    } else {
        printf ("data not complete.\n");
    }
    
}

inline Data*
Resource::take_out()
{
    Data *pdata = NULL;
    if (list_sz > 0) {
        pdata = _data_list.front();
        _data_list.pop_front();
        --list_sz;
    }
    return pdata;
}

inline
Resource::~Resource()
{
    while (!_data_list.empty()) {
        Data *p = _data_list.front();
        _data_list.pop_front();
        dataFree(p);
    }
}


#endif

