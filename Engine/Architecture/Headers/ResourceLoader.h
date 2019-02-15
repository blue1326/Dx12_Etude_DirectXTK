#ifndef Engine_ResourceLoader_h__
#define Engine_ResourceLoader_h__
#include "Component.h"
using namespace Engine::Components;
namespace Engine
{
	namespace Architecture
	{
		class CResourceLoader
		{
		public:
			CResourceLoader();
			~CResourceLoader();

		public:
			HRESULT LoadStart();

		public:
			typedef map<const wchar_t*, shared_ptr<CComponent>> LoadElements;
			void SetLoadElements(const LoadElements& _elements);
		private:
			LoadElements m_LoadElements;
		private:
			unique_ptr<thread> m_Thread;
			static void Load(void* pArgs);
			int m_iMaxLoadElements;
			int m_iLoadedElements;

			wchar_t m_LoadedText[255];
			bool isLoadFlag;
			HRESULT Load_Resource();
		public:
			float GetLoadingPercentage();
			bool GetLoadFlag() { return isLoadFlag; }
			const wchar_t* GetLoadText() { return m_LoadedText; }
		public:
			static unique_ptr<CResourceLoader> Create();
		};


	}
}



#endif // ResourceLoader_h__
