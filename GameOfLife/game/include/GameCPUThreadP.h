#pragma once
#include "GameCPUThreads.h"
#include "ThreadPool.h"

class GameCPUThreadP :
    public GameCPUThreads
{
private:
    ThreadPool* m_threadPool;
    void process();

public:
    GameCPUThreadP(int, int);
    ~GameCPUThreadP() override { delete m_threadPool; }
};

