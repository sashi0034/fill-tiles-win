//
// Created by sashi0034 on 2022/09/17.
//

#ifndef FILL_TILES_POLLFLAG_H
#define FILL_TILES_POLLFLAG_H


namespace inGame
{
    class PollFlag
    {
    public:
        explicit PollFlag(bool flag);

        void PutPoll();
        bool GetFlagWithoutTake() const;
        bool TakePoll();
    private:
        bool _flag = false;
    };
}


#endif //FILL_TILES_POLLFLAG_H
