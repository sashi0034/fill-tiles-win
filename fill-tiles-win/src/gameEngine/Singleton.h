//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_SINGLETON_H
#define FILL_TILES_SINGLETON_H

#include "log.h"
#include <memory>

using std::unique_ptr;

namespace gameEngine
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
                LOG_ERR << "Singleton Object Is Already Exit." << std::endl;
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
