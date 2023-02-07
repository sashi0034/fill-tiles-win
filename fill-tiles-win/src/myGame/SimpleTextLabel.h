//
// Created by sashi0034 on 2022/07/16.
//

#ifndef FILL_TILES_SIMPLETEXTLABEL_H
#define FILL_TILES_SIMPLETEXTLABEL_H

#include "ActorBase.h"
#include "NinePatchImage.h"
#include "TextPassage.h"
#include "GameRoot.h"

namespace myGame
{

    // todo: 必要なさそうなら消去
    class SimpleTextLabel
    {
    public:
        SimpleTextLabel(GameRoot* gameRoot, SpriteTexture& sprRootRef, const Vec2<double>& bgSize);
        NinePatchImage* GetBg();
        TextPassage* GetText();
    private:
        SpriteTexture& m_SprRootRef;
        unique_ptr<NinePatchImage> m_Background;
        unique_ptr<TextPassage> m_TextPassage;

        void initText(GameRoot *root, const std::string &str, const Vec2<double> &bgSize);
        void initBackground(GameRoot *root, const Vec2<double> &size);
    };

} // myGame

#endif //FILL_TILES_SIMPLETEXTLABEL_H
