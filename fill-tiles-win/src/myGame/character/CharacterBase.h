//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_CHARACTERBASE_H
#define FILL_TILES_CHARACTERBASE_H

#include "../../myUtil/myUtil.h"

#include "../GameRoot.h"

namespace myGame{
    class FieldManager;
}

namespace myGame::character
{
    class CharacterBase : public ChildBase<CharacterBase>
    {
    DEF_WEAK_GET(CharacterBase);
    public:
        explicit CharacterBase(FieldManager *parentField);
        virtual ~CharacterBase() = default;
        virtual void Destroy();
        virtual void Update(IAppState* app);
    protected:
        FieldManager* getParentField();
    private:
        FieldManager* m_ParentalField;
    };
}


#endif //FILL_TILES_CHARACTERBASE_H
