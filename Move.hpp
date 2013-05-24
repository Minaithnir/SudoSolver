#ifndef MOVE_H
#define MOVE_H


class Move
{
    public:
        Move();
        virtual ~Move();
    protected:

        unsigned int X;
        unsigned int Y;
        int digit;
    private:
};

#endif // MOVE_H
