//
// Created by sashi0034 on 2022/08/15.
//

#include "SwitchAcornManager.h"
#include "character/SwitchAcorn.h"


namespace myGame
{
    using character::ESwitchAcornKind;

    SwitchAcornManager::SwitchAcornManager(MainScene *mainScene)
    : mainScene(mainScene)
    {}

    rx::observable<SwitchAcornEventArgs*> SwitchAcornManager::OnSwitch()
    {
        return m_OnSwitch.get_observable();
    }

//    rx::subscriber<SwitchAcornEventArgs *> SwitchAcornManager::SubscribeSwitch()
//    {
//        return m_OnSwitch.get_subscriber();
//    }

    character::ESwitchAcornKind SwitchAcornManager::GetCurrSwitch()
    {
        return m_CurrSwitch;
    }

    void SwitchAcornManager::GoNextSwitch(character::SwitchButton *pushedButton)
    {
        m_CurrSwitch = ESwitchAcornKind((int(m_CurrSwitch) + 1) % int(ESwitchAcornKind::Max));

        auto next = SwitchAcornEventArgs{pushedButton, m_CurrSwitch};
        m_OnSwitch.get_subscriber().on_next(&next);
    }

} // myGame