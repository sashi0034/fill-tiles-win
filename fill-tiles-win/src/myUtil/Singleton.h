//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_SINGLETON_H
#define FILL_TILES_SINGLETON_H

#include <stdafx.h>
#include "log.h"

using std::unique_ptr;

namespace myUtil
{
    template <typename T>
    class Singleton
    {
    private:
        static T* instance;
    public:
        Singleton()
        {
            if (instance != nullptr)
            {
                LOG_ERR << "Singleton Object Is Already Exit.";
                return;
            }
            instance = static_cast<T*>(this);
        }
        virtual ~Singleton()
        {
            instance = nullptr;
        }
        static T& GetInstance()
        {
            return *instance;
        }
    };
    template <typename T> T* Singleton<T>::instance = nullptr;
}

#endif //FILL_TILES_SINGLETON_H
