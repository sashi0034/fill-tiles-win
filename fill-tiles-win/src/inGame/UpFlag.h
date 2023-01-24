//
// Created by sashi0034 on 2022/07/19.
//

#ifndef FILL_TILES_UPFLAG_H
#define FILL_TILES_UPFLAG_H


namespace inGame
{
    class UpFlag
    {
    public:
        UpFlag() = default;
        [[nodiscard]] bool IsUp() const;
        void GoDown();
        void operator=(UpFlag) = delete;
    private:
        bool isUp = true;
    };
}


#endif //FILL_TILES_UPFLAG_H
