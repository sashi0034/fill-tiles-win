//
// Created by sashi0034 on 2022/08/06.
//

#include <boost/lexical_cast.hpp>
#include "ReadObjectInObjectGroup.h"
#include "../../Player.h"
#include "../../character/PuniCat.h"
#include "../../character/Fairy.h"
#include "../../character/SolidRock.h"
#include "../../character/GrowingChick.h"
#include "../../character/WarpTile.h"
#include "../../character/WinTile.h"


void inGame::field::tileMap::ReadObjectInObjectGroup(inGame::IMainScene *mainScene, const std::string &objectType,
                                                     const std::string &objectName, const Vec2<int> &pos,
                                                     std::unordered_map<std::string, std::string> &objectProperty)
{
    auto field = mainScene->GetFieldManager();
    auto characterPool = field->GetCharacterPool();
    auto matPos = MatPos(pos / FieldManager::PixelPerMat);

    if (objectType=="restart")
    {
        int level = boost::lexical_cast<int>(objectProperty["level"]);

        field->GetMineFlowerManager()->GetMineFlowerClassByLevel(level)->SetRespawnMatPos(matPos);
    }
    else if (objectType=="fairy")
    {
        characterPool->Birth(new character::Fairy(mainScene, matPos, objectProperty["talk"]));
    }
    else if (objectType=="catfish")
    {
        characterPool->Birth(new character::Catfish(mainScene, matPos));
    }
    else if (objectType=="punicat")
    {
        characterPool->Birth(new character::PuniCat(mainScene, matPos));
    }
    else if (objectType=="solid_rock")
    {
        characterPool->Birth(new character::SolidRock(mainScene, matPos));
    }
    else if (objectType=="chick")
    {
        characterPool->Birth(new character::GrowingChick(mainScene, matPos));
    }
    else if (objectType=="warp")
    {
        assert(objectProperty["key"].length()==1);
        characterPool->Birth(new character::WarpTile(mainScene, matPos, objectProperty["key"][0]));
    }
    else if (objectType=="win")
    {
        characterPool->Birth(new character::WinTile(mainScene, matPos));
    }
    else if (objectType=="test")
    {
        std::cout << pos.ToString() << std::endl;
    }
    else
    {
        assert(!"Invalid Object Exits In objectgroup.");
    }
    (void)objectName;
    (void)objectProperty;
}
