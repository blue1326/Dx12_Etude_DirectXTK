#ifndef Engine_Interface_h__
#define Engine_Interface_h__


namespace Engine
{
	namespace System
	{
		interface IDeviceNotify
		{
			virtual void OnDeviceLost() = 0;
			virtual void OnDeviceRestored() = 0;
		};
	}
}

#endif // Interface_h__
