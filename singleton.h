/******************************************************************
  * File Name     : sigleton.h
  * Description   : 
  *
  * Copyright (C) 2016 Yangguang Li
  * Mail          : liyggyj@163.com
  * Author        : Yangguang Li
  * Created time  : 2016-12-13 03:38:09 PM
  * Last modified : 2016-12-13 03:38:09 PM
******************************************************************/
#ifndef __SIGLETON_H__
# define __SIGLETON_H__

# include <pthread.h>

template<class T>
class Singleton {
    public:
        static T* get_instance() {
            if (NULL == _instance) {
                pthread_mutex_lock (&_mutex);
                if (NULL == _instance) {
                    _instance = new T();
                }
                pthread_mutex_unlock (&_mutex);
            }
  
            return _instance;
        }

    protected:
        Singleton() {}
        ~Singleton() {
            if (_instance) {
                T *p = _instance;
                _instance = NULL;
                delete p;
            }       
        }

    private:
        static T *_instance;
        static pthread_mutex_t _mutex;
};

template<class T> T * Singleton<T>::_instance = NULL;
template<class T> pthread_mutex_t Singleton<T>::_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
template<class T>
inline T& Singleton<T>::get_instance {
    if (NULL == _instance) {
        pthread_mutex_lock (&_mutex);
        if (NULL == _instance) {
            _instance = new T();
        }
        pthread_mutex_unlock (&_mutex);
    }

    return _instance;
}
*/

#endif


