/*
#include "DX12Renderer.h"
#include <dxgi1_5.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx12.h"
namespace Cherry {
    namespace Rendering {
        bool DX12Renderer::CreateDevice(HWND hwnd)
        {

            DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
            {
                ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
                swapChainDesc.Width = 0;
                swapChainDesc.Height = 0;
                swapChainDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
                swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
                swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
                swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
                swapChainDesc.Scaling = DXGI_SCALING_ASPECT_RATIO_STRETCH;
                swapChainDesc.Stereo = false;
                D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_2;
                // [DEBUG] Enable debug interface
                #ifdef DX12_ENABLE_DEBUG_LAYER
                                ID3D12Debug* pdx12Debug = nullptr;
                                if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pdx12Debug))))
                                    pdx12Debug->EnableDebugLayer();
                #endif
                if (D3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(DX12Renderer::g_D3D12Device.GetAddressOf())) != S_OK) {
                    return false;
                }
                #ifdef DX12_ENABLE_DEBUG_LAYER
                                if (pdx12Debug != nullptr)
                                {
                                    ID3D12InfoQueue* pInfoQueue = nullptr;
                                    g_pd3dDevice->QueryInterface(IID_PPV_ARGS(&pInfoQueue));
                                    pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
                                    pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
                                    pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
                                    pInfoQueue->Release();
                                    pdx12Debug->Release();
                                }
                #endif

            {
                                    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
                                    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
                                    desc.NumDescriptors = APP_NUM_BACK_BUFFERS;
                                    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
                                    desc.NodeMask = 1;
                                    if (g_D3D12Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_D3D12RtvDescriptorHeap)) != S_OK)
                                        return false;

                                    SIZE_T rtvDescriptorSize = g_D3D12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
                                    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle =g_D3D12RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
                                    for (UINT i = 0; i < APP_NUM_BACK_BUFFERS; i++)
                                    {
                                        g_mainRenderTargetDescriptor[i] = rtvHandle;
                                        rtvHandle.ptr += rtvDescriptorSize;
                                    }
             }
             {
                                    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
                                    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
                                    desc.NumDescriptors = APP_SRV_HEAP_SIZE;
                                    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
                                    if (g_D3D12Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_D3D12SrvDescriptorHeap)) != S_OK)
                                        return false;
                                   heapAlloc.Create(g_pd3dDevice, g_pd3dSrvDescHeap);
             }

             {
                                    D3D12_COMMAND_QUEUE_DESC desc = {};
                                    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
                                    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
                                    desc.NodeMask = 1;
                                    if (g_D3D12Device->CreateCommandQueue(&desc, IID_PPV_ARGS(&g_D3D12CommandQueue)) != S_OK)
                                        return false;
             }

                                for (UINT i = 0; i < APP_NUM_FRAMES_IN_FLIGHT; i++)
                                    if (g_D3D12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_frameContext[i].CommandAllocator)) != S_OK)
                                        return false;

                                if (g_D3D12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_frameContext[0].CommandAllocator, nullptr, IID_PPV_ARGS(&g_pd3dCommandList)) != S_OK ||
                                    g_pd3dCommandList->Close() != S_OK)
                                    return false;

                                if (g_D3D12Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_fence)) != S_OK)
                                    return false;

                                g_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
                                if (g_fenceEvent == nullptr)
                                    return false;

                                {
                                    IDXGIFactory4* dxgiFactory = nullptr;
                                    IDXGISwapChain1* swapChain1 = nullptr;
                                    if (CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)) != S_OK)
                                        return false;
                                    if (dxgiFactory->CreateSwapChainForHwnd(g_pd3dCommandQueue, hWnd, &sd, nullptr, nullptr, &swapChain1) != S_OK)
                                        return false;
                                    if (swapChain1->QueryInterface(IID_PPV_ARGS(&g_pSwapChain)) != S_OK)
                                        return false;
                                    swapChain1->Release();
                                    dxgiFactory->Release();
                                    g_pSwapChain->SetMaximumFrameLatency(APP_NUM_BACK_BUFFERS);
                                    g_hSwapChainWaitableObject = g_pSwapChain->GetFrameLatencyWaitableObject();
                                }

                                CreateRenderTarget();
                                return true;
            }

            return false;
            }
            void DX12Renderer::CreateRenderTarget()
            {
                for (UINT i = 0; i < APP_NUM_BACK_BUFFERS; i++)
                {
                    ID3D12Resource* pBackBuffer = nullptr;
                    g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
                    g_D3D12Device->CreateRenderTargetView(pBackBuffer, nullptr, g_mainRenderTargetDescriptor[i]);
                    g_mainRenderTargetResource[i] = pBackBuffer;
                }
            };
            void CleanupRenderTarget()
            {
                WaitForPendingOperations();

                for (UINT i = 0; i < DX12Renderer::APP_NUM_BACK_BUFFERS; i++)
                    if (g_mainRenderTargetResource[i]) { g_mainRenderTargetResource[i]->Release(); g_mainRenderTargetResource[i] = nullptr; }
            };

            void WaitForPendingOperations()
            {
                g_D3D12->Signal(g_fence, ++g_fenceLastSignaledValue);

                g_fence->SetEventOnCompletion(g_fenceLastSignaledValue, g_fenceEvent);
                ::WaitForSingleObject(g_fenceEvent, INFINITE);
            }

            ComPtr<DX12Renderer::FrameContext> WaitForNextFrameContext()
            {
                ComPtr<DX12Renderer::FrameContext> frame_context = &g_frameContext[g_frameIndex % APP_NUM_FRAMES_IN_FLIGHT];
                if (g_fence->GetCompletedValue() < frame_context->FenceValue)
                {
                    g_fence->SetEventOnCompletion(frame_context->FenceValue, g_fenceEvent);
                    HANDLE waitableObjects[] = { g_hSwapChainWaitableObject, g_fenceEvent };
                    ::WaitForMultipleObjects(2, waitableObjects, TRUE, INFINITE);
                }
                else
                    ::WaitForSingleObject(g_hSwapChainWaitableObject, INFINITE);

                return frame_context;
            }


        void DX12Renderer::CreateSRVDescriptorHeap()
        {
            DX12Renderer::g_D3D12SrvDescriptorHeap;

        }
    }
}
*/
