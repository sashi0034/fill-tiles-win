//
// Created by sashi0034 on 2022/05/28.
//

#include "AnimTest.h"
#include "GameRoot.h"

namespace myGame
{
    AnimTest::AnimTest(IChildrenPool<ActorBase> *belonging)
            : ActorBase(belonging),
              m_Action(coroutine<CoroTask>::pull_type{std::bind(wait, std::placeholders::_1, this)})
    {
        m_Image = GameRoot::GetInstance().RscImage->dango_wolf_24x24.get();

        //m_Target = SpriteTexture::Create(m_Image);
        m_Texture->SetSrcRect(Rect<int>{0,0,24, 24});

        std::cout << "#1" << std::endl;
    }

    CoroTask AnimTest::wait(coroutine<CoroTask>::push_type &yield, AnimTest *self)
    {
        yield();

        auto& mainRoot = GameRoot::GetInstance();
        auto appState = mainRoot.GetAppState();
        auto screenSize = appState->GetScreenSize().CastTo<double>();
        self->m_Pos = screenSize/2.0;
        self->m_Texture->SetPosition(self->m_Pos);

        /* example */
//        mainRoot.GetTextureAnimator().TargetTo(self->m_Target)
//                ->AnimGraph(Vec2<int>{24, 24})->SetFrameLoop(10)->SetCellSrcStart(Vec2<int>{0, 0})
//                ->AddFrame(Vec2<int>{0, 0}, 0.2)
//                ->AddFrame(Vec2<int>{1, 0}, 0.2)
//                ->AddFrame(Vec2<int>{2, 0}, 0.2)
//                ->AddFrame(Vec2<int>{3, 0}, 0.2);
//
//        mainRoot.GetTextureAnimator().TargetTo(self->m_Target)
//                ->AnimScale(Vec2{3.0, 3.0}, 5.0)->SetLoop(1)
//                ->Then()
//                ->AnimPosition(Vec2<double>{64, 64}, 3.0)->SetEase(EAnimEase::Linear)->SetLoop(2)->SetRelative(false)
//                ->With()
//                ->AnimRotation(60, 3.0)->SetEase(EAnimEase::Linear)->SetLoop(2)
//                ->Then()
//                ->AnimPosition(Vec2<double>{32, 32}, 3.0)->SetEase(EAnimEase::Linear)->SetLoop(2)->SetRelative(true)
//                ->Then()
//                ->DelayVirtual([]() { std::cout << "finished animation?" << std::endl; }, 1.0)
//                ->Then()
//                ->DelayVirtual([]() { std::cout << "yes!" << std::endl; }, 0)
//                ->Then()
//                ->DelayVirtual([]() { std::cout << "finished animation!" << std::endl; }, 0.5);


        yield();
//
//        for (int i=0; i<256; ++i)
//        {
//            self->m_Pos = self->m_Pos + Vec2<double>{128.0-i, 128.0-i} * appState->GetTime().GetDeltaSec();
//            yield(CoroTask::RespondPending());
//
//        }
//        self->m_View->SetRotationDeg(45);

    }

    void AnimTest::Update(IAppState *)
    {
        if (m_Action) m_Action();
    }

}
