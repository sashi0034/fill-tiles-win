//
// Created by sashi0034 on 2022/05/05.
//

#ifndef FILL_TILES_LIBRARYTEST_H
#define FILL_TILES_LIBRARYTEST_H


#include <rxcpp/rx.hpp>
#include <boost/coroutine2/coroutine.hpp>

namespace inGame
{
    enum class ETest{
        hoge0,
        hoge1,
    };

    class LibraryTest
    {
        rxcpp::subjects::subject<int> m_TestSubject;
        rxcpp::composite_subscription m_Subscription;
        int m_T = 0;
        static void func(boost::coroutines2::coroutine<int>::push_type &yield, LibraryTest* self);
    public:
        LibraryTest();
        void Update();
    };
}


#endif //FILL_TILES_LIBRARYTEST_H
