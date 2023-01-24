//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_ARRAYUTIL_H
#define FILL_TILES_ARRAYUTIL_H

#include <vector>
#include <algorithm>
#include "assert.h"
#include "cstdint"

namespace gameEngine
{
    namespace arrayUtil
    {
        template<typename T>
        int FindIndex(const std::vector<T> *arr, T target)
        {
            auto size = (*arr).size();
            if (size == 0) return -1;
            auto iter = std::find((*arr).begin(), (*arr).end(), target);
            size_t index = std::distance((*arr).begin(), iter);
            if (index == size)
            {
                return -1;
            }
            return index;
        }

        template<typename T>
        typename std::vector<T>::iterator FindIter(const std::vector<T> *arr, T target)
        {
            assert((*arr).size()!=0);
            auto iter = std::find((*arr).begin(), (*arr).end(), target);
            return iter;
        }

        template<typename T>
        int Remove(std::vector<T> *arr, T target)
        {
            int index = FindIndex<T>(arr, target);
            if (index == -1) return -1;
            (*arr).erase((*arr).begin() + index);
            return 0;
        }

        template<typename T>
        void RemoveList(std::vector<T> *targetArray, const std::vector<int> &upwardIndexes)
        {
            int beforeIndex = INT32_MAX;
            for (int i = upwardIndexes.size() - 1; i >= 0; --i)
            {
                int index = upwardIndexes[i];

                assert(beforeIndex > index);
                beforeIndex = index;

                targetArray->erase(targetArray->begin() + index);
            }
        }
    }
}


#endif //FILL_TILES_ARRAYUTIL_H
