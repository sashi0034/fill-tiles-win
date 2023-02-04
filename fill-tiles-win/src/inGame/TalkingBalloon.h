//
// Created by sashi0034 on 2022/07/01.
//

#ifndef FILL_TILES_TALKINGBALLOON_H
#define FILL_TILES_TALKINGBALLOON_H

#include "SDL_ttf.h"
#include "ActorBase.h"
#include "GameRoot.h"
#include "MainScene.h"
#include "NinePatchImage.h"
#include "TextPassage.h"

namespace inGame
{
    class TalkingBalloon : public ActorBase
    {
        DEF_WEAK_GET(TalkingBalloon);
    public:
        static TalkingBalloon* Create(MainScene *scene, const std::string &text, const MatPos &pos);
    private:
        TalkingBalloon(MainScene *scene, const std::string &text, const Vec2<double> &pos);
        SpriteTexture m_SpriteRoot = SpriteTexture::Create();
        MainScene* m_Scene;
        std::string m_Text;

        static const inline Vec2<double> bgSize = Vec2<double>{128.0, 48.0};
        unique_ptr<NinePatchImage> m_Background;
        TextPassage m_TextPassage;

        void initBackground(MainScene *scene);
        void initTextPassage();

        CoroTask startAppear(CoroTaskYield &yield);

        void performAnimGuruGuruChar(CoroTaskYield &yield, const double duration, std::string &currStr,
                                     int numGruGru);
    };
}


#endif //FILL_TILES_TALKINGBALLOON_H
