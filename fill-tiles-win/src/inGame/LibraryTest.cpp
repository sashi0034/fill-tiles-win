//
// Created by sashi0034 on 2022/05/05.
//
#include <boost/coroutine2/coroutine.hpp>
#include <iostream>
#include <boost/version.hpp>
#include "LibraryTest.h"
#include "magic_enum.h"

typedef boost::coroutines2::coroutine<int> coro_t;




namespace inGame
{

    LibraryTest::LibraryTest()
    {
        auto observer = m_TestSubject.get_observable();

        m_Subscription = observer
                .subscribe([](int v) {
                    std::cout << "subscribe: " << v << std::endl;
                });

        std::cout << magic_enum::enum_name(ETest::hoge0) << std::endl;
    }

    void LibraryTest::func(coro_t::push_type& yield, LibraryTest* self)
    {
        std::cout << 2 << " ";
        yield(3); // {3}をメインコンテキストに戻す
        std::cout << 5 << " ";

        std::cout << "self value: " << self->m_T << std::endl;

        yield(6); // {6}をメインコンテキストに戻す
    }


    void LibraryTest::Update()
    {
        m_T += 1;
        if (m_T==5)
        {
            coro_t::pull_type source{std::bind(func, std::placeholders::_1, this)};

            if (source) //プルコルーチンが有効かどうかをテストする
                std::cout << source.get() << " "; // データ値にアクセス

            std::cout << 4 << " ";

            if (source) {
                source(); // コンテキストスイッチ
                std::cout << source.get() << " "; // データ値にアクセス
            }

            m_TestSubject.get_subscriber().on_next(12345);

            std::cout << "boost version:" << BOOST_VERSION << std::endl;
            std::cout << "boost lib version:" << BOOST_LIB_VERSION << std::endl;

            printf("sample1 end.\n");

            m_Subscription.unsubscribe();
        }
    }

}
