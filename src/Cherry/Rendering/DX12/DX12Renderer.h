
#pragma once
/* 
	#include "Windows.h"
	#include "wrl/client.h"
	#include "d3d12.h"
	#include "dxgi.h"
	#include <dxgi1_5.h>
	using namespace Microsoft::WRL;

namespace Cherry {
	namespace Rendering {
		class DX12Renderer {

		public:
			static const int APP_NUM_FRAMES_IN_FLIGHT = 2;
			static const int APP_NUM_BACK_BUFFERS = 2;
			static const int APP_SRV_HEAP_SIZE = 64;
			ComPtr<ID3D12Device> g_D3D12Device;
			ComPtr<ID3D12DescriptorHeap> g_D3D12RtvDescriptorHeap;
			ComPtr<ID3D12DescriptorHeap> g_D3D12SrvDescriptorHeap;
			ComPtr<ID3D12CommandQueue> g_D3D12CommandQueue;
			ComPtr<ID3D12CommandList> g_D3D12CommandList;
			ComPtr<ID3D12Fence> g_D3D12Fence;
			struct FrameContext
			{
				ComPtr<ID3D12CommandAllocator> CommandAllocator;
				UINT64                      FenceValue;
			};
			FrameContext g_frameContext[APP_NUM_FRAMES_IN_FLIGHT] = {};
			UINT                         g_frameIndex;

			ComPtr<ID3D12GraphicsCommandList> g_pd3dCommandList;
			HANDLE                       g_fenceEvent;
			UINT64                       g_fenceLastSignaledValue;
		    ComPtr<IDXGISwapChain3> g_pSwapChain;
			bool                         g_SwapChainOccluded;
			HANDLE                       g_hSwapChainWaitableObject;
			ComPtr<ID3D12Resource> g_mainRenderTargetResource[APP_NUM_BACK_BUFFERS];
			D3D12_CPU_DESCRIPTOR_HANDLE  g_mainRenderTargetDescriptor[APP_NUM_BACK_BUFFERS];

			void CreateSRVDescriptorHeap();
			bool CreateDevice(HWND hwnd);
			void CleanupDevice();
			void CreateRenderTarget();
			ComPtr<FrameContext> WaitForNextFrameContext();
		};
	}
}
*/