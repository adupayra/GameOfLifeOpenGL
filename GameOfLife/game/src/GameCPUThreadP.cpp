#include "GameCPUThreadP.h"

GameCPUThreadP::GameCPUThreadP(int dimension, int cellsPerDim): Game(dimension, cellsPerDim)
{
	m_nThreads = std::thread::hardware_concurrency();
	m_cellsPerThread = m_nbCells / m_nThreads;
	m_threadPool = new ThreadPool(m_nThreads);
}


void GameCPUThreadP::process()
{
	std::vector<std::future<void>> results;
	int i = 0;
	for (i = 0; i < m_nThreads - 1; i++) {
		int index = i * m_cellsPerThread;
		results.emplace_back(m_threadPool->enqueue(&GameCPUThreadP::processCells, this, index, index + m_cellsPerThread));
	}
	results.emplace_back(m_threadPool->enqueue(&GameCPUThreadP::processCells, this, i * m_cellsPerThread, m_nbCells - 1));


	for (std::future<void>& f : results) {
		f.get();
	}

	std::swap(m_cells, m_newCells);
}

void GameCPUThreadP::processCells(int start, int end)
{
	int nbNeighbours = 0;
	for (int i = start; i < end; i++) {
		nbNeighbours = getAliveNeighbours(i);
		m_newCells[i] = m_rules->isAlive(m_cells[i], nbNeighbours);
	}
}