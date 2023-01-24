//
// Created by sashi0034 on 2022/05/21.
//

#ifndef FILL_TILES_CHILDRENPOOL_H
#define FILL_TILES_CHILDRENPOOL_H

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

#if 0
namespace gameEngine
{
    template<typename T> class IReferencePool
    {
    public:
        virtual void Register(shared_ptr<T>& child)=0;
        virtual bool Release(T* child) = 0;
    };


    template<typename T> class ReferencePool : public IReferencePool<T>
    {
        std::vector<weak_ptr<T>> m_Pool{};
        int currentProcessingIndex = 0;

        void collectGarbage(std::vector<int> &upwardIndexes)
        {
            for (int i = upwardIndexes.size() - 1; i >= 0; --i)
            {
                int index = upwardIndexes[i];
                m_Pool.erase(m_Pool.begin() + index);
            }
        }
    public:
        void Register(shared_ptr<T>& child) override
        {
            weak_ptr<T> reference = child;
            m_Pool.template emplace_back(reference);
        };
        bool Release(T* child) override
        {
            if (m_Pool.empty()) return false;

            auto iter = findIterator(child);

            if (iter==m_Pool.end()) return false;

            *iter = nullptr;

            return true;
        }
        void ProcessEach(std::function<void(shared_ptr<T>&)> process)
        {
            int size =m_Pool.size();
            std::vector<int> garbage{};

            for (int i = 0; i < size; ++i)
            {
                currentProcessingIndex = i;
                if (m_Pool[i] != nullptr)
                    process(m_Pool[i]);
                else
                    garbage.push_back(i);
            }

            currentProcessingIndex = 0;
            collectGarbage(garbage);
        }
        void Release()
        {
            m_Pool = std::vector<shared_ptr<T>>{};
        }
        ~ChildrenPool()
        {
            assert(m_Pool.size()==0);
        }
    };
}
#endif

#endif //FILL_TILES_CHILDRENPOOL_H
