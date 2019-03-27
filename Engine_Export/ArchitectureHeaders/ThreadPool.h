#ifndef Engine_ThreadPool_h__
#define Engine_ThreadPool_h__
#include <functional>
#include <future>
namespace Engine
{
	namespace Architecture 
	{
		class CThreadPool
		{
		public:
			CThreadPool();
			~CThreadPool();

			void Init();
			void update();

			enum TREADCOUNT
			{
				TR_FIRST,TR_SECOND,TR_THIRD,TR_FOURTH,TR_MAXCOUNT 
			};
		private:

			unique_ptr<thread> m_MaInThread[TR_MAXCOUNT];
			unique_ptr<thread> m_SubThread[TR_MAXCOUNT];
			unique_ptr<thread> m_BGThread[TR_MAXCOUNT];
			mutex mtx;
			
			queue<function<void()>> m_Tasks;
			std::condition_variable m_Condition;

		
			void test(TREADCOUNT _cnt);

			void test2();
			bool m_IsStop;

			template <class _F, class ... _Args>
			auto Enqueue(_F&& f, _Args&& ... args)
				->std::future<decltype(std::forward<_F>(f)(
					std::forward<_Args>(args)...))>
			{
				typedef decltype(std::forward<_F>(f)(std::forward<_Args>(args)...)) return_type;

				// don't allow enqueueing after stopping the pool
				if (m_IsStop) {
					throw std::runtime_error("enqueue on stopped ThreadPool");
				}

				auto task = std::make_shared<std::packaged_task<return_type()>>
					(std::bind(std::forward<_F>(f), std::forward<_Args>(args)...));

				std::future<return_type> result = task->get_future();

				{
					std::unique_lock<std::mutex> lock(mtx);
					m_Tasks.push([task]() { (*task)(); }); 
				}
				m_Condition.notify_one();

				return result;
			}
		};

	}
}


#endif // ThreadMgr_h__
