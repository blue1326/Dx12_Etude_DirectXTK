#ifndef Engine_ComponentHolder_h__
#define Engine_ComponentHolder_h__

#include "Component.h"
#include "Templates.h"
using namespace Engine::Singleton;
using namespace Engine::Components;

namespace Engine
{
	namespace Components
	{
		class CComponentHolder : public CSingleton<CComponentHolder>
		{
		public:
			CComponentHolder();
			~CComponentHolder();
		public:
			bool InitComponents();
			HRESULT Reserve_ComponentHolder(const unsigned int& iSize);
			void AddOriginComponent(const std::string _ComponentName, std::shared_ptr<CComponent> _ComponentOrigin);
			std::shared_ptr<CComponent> Clone_Component(const std::string _ComponentName);
			std::shared_ptr<CComponent> Get_Component(const std::string _ComponentName);
			typedef std::map<const std::string, std::shared_ptr<CComponent>> MAPCOMPONENT;
		public:
			void Destroy();
		private:
			std::shared_ptr<CComponent> Find_Component(const std::string _ComponentName);
		private:
			MAPCOMPONENT m_OriginComponents;
			
		};
	}
}

#endif // ComponentHolder_h__
