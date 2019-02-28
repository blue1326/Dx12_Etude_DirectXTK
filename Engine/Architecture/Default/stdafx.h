// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>


//#include <wrl/client.h> //????용도불명
#include <wrl/event.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")


#include <d3d12.h>
#include "d3dx12.h"


#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif


#include <DirectXMath.h>
#include <DirectXColors.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <exception>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <unordered_map>
#include <string>
#include <queue>

//#include <unordered_map>

#include <pix.h>


#ifdef _DEBUG
#include <dxgidebug.h>
#endif


//
//#include "Audio.h"
#include "CommonStates.h"
#include "DirectXHelpers.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#include "DescriptorHeap.h"
//#include "Effects.h"
#include "GamePad.h"
//#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
//#include "Model.h"
#include "Mouse.h"
//#include "PrimitiveBatch.h"
//#include "ResourceUploadBatch.h"
//#include "RenderTargetState.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h" 
//#include "VertexTypes.h"

#pragma comment(lib,"RuntimeObject.lib")
#pragma comment(lib,"../../../bin/System.lib")
#pragma comment(lib,"../../../bin/Components.lib")

using namespace std;
// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
