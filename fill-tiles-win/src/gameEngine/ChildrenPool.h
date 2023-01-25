//
// Created by sashi0034 on 2022/05/21.
//

#ifndef FILL_TILES_CHILDRENPOOL_H
#define FILL_TILES_CHILDRENPOOL_H

#include <stdafx.h>

using std::unique_ptr;

namespace gameEngine
{
    template<typename T> class IChildrenPool
    {
    public:
        virtual T* Birth(T* child) = 0;
        virtual bool Destroy(T* child) = 0;
    };


    template<typename T> class ChildrenPool : public IChildrenPool<T>
    {
        std::vector<unique_ptr<T>> m_Pool{};
        int currentProcessingIndex = 0;

        typename std::vector<unique_ptr<T>>::iterator findIterator(T* target)
        {
            assert(!m_Pool.empty());
            assert(currentProcessingIndex < int(m_Pool.size()));

            if (target == m_Pool[currentProcessingIndex].get()) return m_Pool.begin() + currentProcessingIndex;

            auto iter = std::find_if(
                    m_Pool.begin(), m_Pool.end(),
                    [target](unique_ptr<T>& child) {
                        return child.get() == target;
                    });

            return iter;
        }

        void collectGarbage(std::vector<int> &upwardIndexes)
        {
            for (int i = upwardIndexes.size() - 1; i >= 0; --i)
            {
                int index = upwardIndexes[i];
                m_Pool.erase(m_Pool.begin() + index);
            }
        }
    public:
        T* Birth(T* child) override
        {
            m_Pool.push_back(unique_ptr<T>(child));
            return child;
        };
        template<class CastedType> CastedType* BirthAs(CastedType* child)
        {
            static_assert(std::is_base_of<T, CastedType>::value, "Child type cannot cast to base type.");
            Birth(child);
            return child;
        }
        bool Destroy(T* child) override
        {
            if (m_Pool.empty()) return false;

            auto iter = findIterator(child);

            if (iter==m_Pool.end()) return false;

            *iter = nullptr;

            return true;
        }
        void ProcessEach(std::function<void(T&)> process)
        {
            int size =m_Pool.size();
            std::vector<int> garbage{};

            for (int i = 0; i < size; ++i)
            {
                currentProcessingIndex = i;
                if (m_Pool[i] != nullptr)
                    process(*m_Pool[i]);
                else
                    garbage.push_back(i);
            }

            currentProcessingIndex = 0;
            collectGarbage(garbage);
        }
        int Count()
        {
            return m_Pool.size();
        }
        void Release()
        {
            m_Pool = std::vector<unique_ptr<T>>{};
        }
        ~ChildrenPool()
        {
            Release();
        }
    };
}

#endif //FILL_TILES_CHILDRENPOOL_H
