#ifndef Engine_AppCore_h__
#define Engine_AppCore_h__
#include "Interface.h"

namespace Engine
{
	namespace System
	{
		class AppCore : public IDeviceNotify
		{
		public:
			AppCore();
			virtual ~AppCore();

		public:
			// IDeviceNotify
			virtual void OnDeviceLost() =0;
			virtual void OnDeviceRestored() =0;
		private:

		};
	}
}
#endif // Engine_AppCore_h__
