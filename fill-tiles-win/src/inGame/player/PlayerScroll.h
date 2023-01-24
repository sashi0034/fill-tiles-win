//
// Created by sashi0034 on 2022/08/17.
//

#ifndef FILL_TILES_PLAYERSCROLL_H
#define FILL_TILES_PLAYERSCROLL_H

namespace inGame{
    class ScrollManager;
    class FieldEventManager;
}

namespace inGame::player
{

    class PlayerScroll
    {
    public:
        PlayerScroll(FieldEventManager *fieldEvent, ScrollManager *scrollManager, SpriteTexture *playerSprite);
        void UpdateFixedly();
        void ChangeFocus(SpriteTexture* target);
        void ResetFocus();
        void RequestResetScroll();
    private:
        FieldEventManager* fieldEvent;
        ScrollManager* scrollManager;
        SpriteTexture* m_PlayerSprite{};
        SpriteTexture* m_FocusingSprite{};

        void scrollByTracking(const Vec2<double> &trackingPos);
        bool m_ShouldResetScroll = false;
    };

} // inGame

#endif //FILL_TILES_PLAYERSCROLL_H
