#include "Dependencies.h"
#include "Game.cpp"
int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, game, NULL);
    pthread_join(tid, NULL);
    return 0;
}
