#include "ShadersManager.h"

#include <cassert>
#include <D3D11.h>
#include <fstream>
#include <string>
#include <vector>

#include <DxErrorChecker.h>

namespace 
{
    void computeShaderByteCode(const std::wstring& fileName, std::vector<char>& shaderByteCode)
    {
        assert(!fileName.empty());

        // Clear vector content
        shaderByteCode.clear();

        // Open shader file, compile it and 
        std::ifstream fin;
        fin.open(fileName.c_str(), std::ios::binary); 

        assert(fin.is_open());

        fin.seekg(0, std::ios_base::end); 
        size_t size = static_cast<size_t> (fin.tellg()); 
        fin.seekg(0, std::ios_base::beg); 
        shaderByteCode.resize(size); 
        fin.read(&shaderByteCode[0], size); 
        fin.close();
    }

    void buildShapesVertexLayout(ID3D11Device * const device, std::vector<char>& shaderByteCode, ID3D11InputLayout* &inputLayout)
    {
        assert(device);
        assert(!inputLayout);
        assert(!shaderByteCode.empty());

        // Create the vertex input layout for land and screen quad
        D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 4, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1}
        };

        // Create the input layout
        const HRESULT result = device->CreateInputLayout(vertexDesc, 9, &shaderByteCode[0], 
            shaderByteCode.size(), &inputLayout);

        DxErrorChecker(result);
    }

    void buildFloorVertexLayout(ID3D11Device * const device, std::vector<char>& shaderByteCode, ID3D11InputLayout* &inputLayout)
    {
        assert(device);
        assert(!inputLayout);
        assert(!shaderByteCode.empty());

        // Create the vertex input layout for land and screen quad
        D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };

        // Create the input layout
        const HRESULT result = device->CreateInputLayout(vertexDesc, 4, &shaderByteCode[0], 
            shaderByteCode.size(), &inputLayout);

        DxErrorChecker(result);
    }

    void buildShadowMapVertexLayout(ID3D11Device * const device, std::vector<char>& shaderByteCode, ID3D11InputLayout* &inputLayout)
    {
        assert(device);
        assert(!inputLayout);
        assert(!shaderByteCode.empty());

        // Create the vertex input layout for land and screen quad
        D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},
            {"WORLD", 4, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1}
        };

        // Create the input layout
        const HRESULT result = device->CreateInputLayout(vertexDesc, 9, &shaderByteCode[0], 
            shaderByteCode.size(), &inputLayout);

        DxErrorChecker(result);
    }

    void buildFloorShadowMapVertexLayout(ID3D11Device * const device, std::vector<char>& shaderByteCode, ID3D11InputLayout* &inputLayout)
    {
        assert(device);
        assert(!inputLayout);
        assert(!shaderByteCode.empty());

        // Create the vertex input layout for land and screen quad
        D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };

        // Create the input layout
        const HRESULT result = device->CreateInputLayout(vertexDesc, 4, &shaderByteCode[0], 
            shaderByteCode.size(), &inputLayout);

        DxErrorChecker(result);
    }
}

namespace Managers
{
    ID3D11VertexShader* ShadersManager::mShapesVS = nullptr;
    ID3D11InputLayout* ShadersManager::mShapesIL = nullptr;
    ID3D11PixelShader* ShadersManager::mShapesPS = nullptr;

    ID3D11VertexShader* ShadersManager::mFloorVS = nullptr;
    ID3D11InputLayout* ShadersManager::mFloorIL = nullptr;
    ID3D11PixelShader* ShadersManager::mFloorPS = nullptr;

    ID3D11VertexShader* ShadersManager::mShadowMapVS = nullptr;
    ID3D11InputLayout* ShadersManager::mShadowMapIL = nullptr;
    ID3D11PixelShader* ShadersManager::mShadowMapPS = nullptr;

    ID3D11VertexShader* ShadersManager::mFloorShadowMapVS = nullptr;
    ID3D11InputLayout* ShadersManager::mFloorShadowMapIL = nullptr;
    ID3D11PixelShader* ShadersManager::mFloorShadowMapPS = nullptr;
    
    void ShadersManager::initAll(ID3D11Device * const device)
    {
        assert(device);

        // Store shader byte code, used to create a shader.
        std::vector<char> shaderByteCode;

        //
        // Vertex shaders
        //

        computeShaderByteCode(L"HLSL/ShapesVS.cso", shaderByteCode);
        buildShapesVertexLayout(device, shaderByteCode, mShapesIL);
        HRESULT result = device->CreateVertexShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mShapesVS);
        DxErrorChecker(result);

        computeShaderByteCode(L"HLSL/FloorVS.cso", shaderByteCode);
        buildFloorVertexLayout(device, shaderByteCode, mFloorIL);
        result = device->CreateVertexShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mFloorVS);
        DxErrorChecker(result);

        computeShaderByteCode(L"HLSL/ShadowMapVS.cso", shaderByteCode);
        buildShadowMapVertexLayout(device, shaderByteCode, mShadowMapIL);
        result = device->CreateVertexShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mShadowMapVS);
        DxErrorChecker(result);

        computeShaderByteCode(L"HLSL/FloorShadowMapVS.cso", shaderByteCode);
        buildFloorShadowMapVertexLayout(device, shaderByteCode, mFloorShadowMapIL);
        result = device->CreateVertexShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mFloorShadowMapVS);
        DxErrorChecker(result);

        //
        // Pixel shaders
        //
        computeShaderByteCode(L"HLSL/ShapesPS.cso", shaderByteCode);        
        result = device->CreatePixelShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mShapesPS);
        DxErrorChecker(result);

        computeShaderByteCode(L"HLSL/FloorPS.cso", shaderByteCode);        
        result = device->CreatePixelShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mFloorPS);
        DxErrorChecker(result);

        computeShaderByteCode(L"HLSL/ShadowMapPS.cso", shaderByteCode);        
        result = device->CreatePixelShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mShadowMapPS);
        DxErrorChecker(result);

        computeShaderByteCode(L"HLSL/FloorShadowMapPS.cso", shaderByteCode);        
        result = device->CreatePixelShader(&shaderByteCode[0], shaderByteCode.size(), nullptr, &mFloorShadowMapPS);
        DxErrorChecker(result);
    }
    
    void ShadersManager::destroyAll()
    {
        mShapesVS->Release();
        mShapesIL->Release();
        mShapesPS->Release();

        mFloorVS->Release();
        mFloorIL->Release();
        mFloorPS->Release();

        mShadowMapVS->Release();
        mShadowMapIL->Release();
        mShadowMapPS->Release();

        mFloorShadowMapVS->Release();
        mFloorShadowMapIL->Release();
        mFloorShadowMapPS->Release();
    }
}