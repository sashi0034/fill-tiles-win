//
// Created by sashi0034 on 2022/07/01.
//

#ifndef FILL_TILES_WEAKCOLLECTION_H
#define FILL_TILES_WEAKCOLLECTION_H

#include "vector"
#include "functional"
#include "WeakPtr.h"

namespace gameEngine
{
    template <class T>
    class WeakCollection
    {
    public:
        WeakCollection(){}

        void Add(T* element)
        {
            m_Collection.push_back(element->GetWeakPtr());
        }
        void ForEach(const std::function<void(T*)>& process)
        {
            for (int i=m_Collection.size()-1; i>=0; --i)
            {
                if (auto ptr = m_Collection[i].GetPtr())
                    process(ptr);
                else
                    m_Collection.erase(m_Collection.begin() + i);
            }
        }
    private:
        std::vector<WeakPtr<T>> m_Collection{};
    };
}


#endif //FILL_TILES_WEAKCOLLECTION_H
