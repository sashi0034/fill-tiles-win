
// 参考: 弱参照クラスを自作する by shinya (id:shinya_game_app)
// https://flat-leon.hatenablog.com/entry/cpp_impl_weak_ref

#ifndef FILL_TILES_WEAKPTR_H
#define FILL_TILES_WEAKPTR_H

#include <stdafx.h>

namespace myUtil
{
    class PtrInfo
    {
    public:
        void *m_Ptr = nullptr;
        int m_RefCount = 0;

        PtrInfo(void *ptr) : m_Ptr(ptr)
        {}

        void Inc()
        { ++m_RefCount; }

        static void Dec(PtrInfo *&p_info)
        {
            if (!p_info) { return; }

            --p_info->m_RefCount;
            if (p_info->m_RefCount == 0)
            {
                delete p_info;
                p_info = nullptr;
            }
        }

        bool IsNull() const
        { return m_Ptr == nullptr; }

        template<class T>
        T *GetPtr() const
        { return reinterpret_cast<T *>(m_Ptr); }

        int GetRefCount() const
        { return m_RefCount; }
    };

    template<class T>
    class WeakPtrController;

    template<class T>
    class WeakPtr
    {
        friend class WeakPtrController<T>;

        myUtil::PtrInfo *m_PtrInfo = nullptr;
    public:
        ~WeakPtr()
        {
            myUtil::PtrInfo::Dec(m_PtrInfo);
        }

        WeakPtr()
        {}

        explicit WeakPtr(myUtil::PtrInfo *p_ptrInfo) : m_PtrInfo(p_ptrInfo)
        {
            if (m_PtrInfo)
            {
                m_PtrInfo->Inc();
            }
        }

        WeakPtr(const WeakPtr &other) : m_PtrInfo(other.m_PtrInfo)
        {
            if (m_PtrInfo)
            {
                m_PtrInfo->Inc();
            }
        }

        WeakPtr &operator=(const WeakPtr &other)
        {
            myUtil::PtrInfo::Dec(m_PtrInfo);
            m_PtrInfo = other.m_PtrInfo;
            if (m_PtrInfo)
            {
                m_PtrInfo->Inc();
            }
            return *this;
        }

        void Clear()
        {
            myUtil::PtrInfo::Dec(m_PtrInfo);
            m_PtrInfo = nullptr;
        }

        template<class U>
        WeakPtr<U> ToUpCasted()
        {
            static_assert(std::is_base_of<U, T>::value, "U is not the base class of T.");
            return WeakPtr<U>(m_PtrInfo);
        }

        template<class U>
        WeakPtr<U> ToDownCasted()
        {
            static_assert(std::is_base_of<T, U>::value, "U must be a derived class of T.");
            if (dynamic_cast<U*>(GetPtr()))
            {
                return WeakPtr<U>(m_PtrInfo);
            }
            // ダウンキャストに失敗
            return WeakPtr<U>(nullptr);
        }

        bool IsNull() const
        { return m_PtrInfo == nullptr || m_PtrInfo->IsNull(); }

        T *GetPtr() const
        { return m_PtrInfo ? m_PtrInfo->GetPtr<T>() : nullptr; }

        T &operator*() const
        {
            assert(!IsNull());
            return *GetPtr();
        }

        T *operator->() const
        {
            assert(!IsNull());
            return GetPtr();
        }

        operator T *() const
        { return GetPtr(); }

        int GetRefCount() const
        { return m_PtrInfo ? m_PtrInfo->GetRefCount() : 0; }
    };

    template<class T>
    class WeakPtrController
    {
        WeakPtr<T> m_WeakPtr;
    public:
        ~WeakPtrController()
        {
            if (m_WeakPtr.m_PtrInfo)
            {
                m_WeakPtr.m_PtrInfo->m_Ptr = nullptr;
            }
        }

        explicit WeakPtrController(T *ptr) : m_WeakPtr(new myUtil::PtrInfo(ptr))
        {}

        WeakPtrController() = delete;

        WeakPtrController(const WeakPtrController &other) = default;

        WeakPtrController &operator=(const WeakPtrController &other) = default;

        template<class U>
        WeakPtr<U> ToDownCastedUnsafely(U *self)
        {
            (void) self;
            static_assert(std::is_base_of<T, U>::value, "");
            return WeakPtr<U>(m_WeakPtr.m_PtrInfo);
        }

        WeakPtr<T> GetWeakPtr()
        { return m_WeakPtr; }
    };
}

#define DEF_WEAK_CONTROLLER(type) \
    public:  WeakPtr<type> GetWeakPtr(){ return m_WeakPtrController.GetWeakPtr(); } \
    protected: WeakPtrController<type> m_WeakPtrController{this}

#define DEF_WEAK_GET(type) public: WeakPtr<type> GetWeakPtr(){ return m_WeakPtrController.ToDownCastedUnsafely<type>(this); }


#endif //FILL_TILES_WEAKPTR_H
