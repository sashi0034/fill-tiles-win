//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_CHARACTERBASE_H
#define FILL_TILES_CHARACTERBASE_H

#include "../../gameEngine/gameEngine.h"
#include "../GameRoot.h"

namespace inGame{
    class IFieldManager;
}

namespace inGame::character
{
    class CharacterBase : public ChildBase<CharacterBase>
    {
    DEF_WEAK_GET(CharacterBase);
    public:
        explicit CharacterBase(IFieldManager *parentField);
        virtual ~CharacterBase() = default;
        virtual void Destroy();
        virtual void Update(IAppState* app);
    protected:
        IFieldManager* getParentField();
    private:
        IFieldManager* m_ParentalField;
    };
}


#endif //FILL_TILES_CHARACTERBASE_H
