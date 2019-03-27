#include "stdafx.h"
#include "ThreadPool.h"
Engine::Architecture::CThreadPool::CThreadPool()
{

}

Engine::Architecture::CThreadPool::~CThreadPool()
{

}

void Engine::Architecture::CThreadPool::Init()
{
	for (int i = 0; i < TR_MAXCOUNT; i++)
	{
		m_MaInThread[i] = make_unique<thread>();
		m_SubThread[i] = make_unique<thread>();
		m_BGThread[i] = make_unique<thread>();
	}
}

void Engine::Architecture::CThreadPool::update()
{
	vector<future<void>> res;
	auto lamda = &CThreadPool::test2;
	//Enqueue(test2());
	res.push_back(Enqueue([&]() {return test2(); }));

	//auto lamda = (this->*test2)();
	//Enqueue(lamda);
}

void Engine::Architecture::CThreadPool::test(TREADCOUNT _cnt)
{
	while (true)
	{
		mtx.lock();
		
		mtx.unlock();
	}
}

void Engine::Architecture::CThreadPool::test2()
{

}
