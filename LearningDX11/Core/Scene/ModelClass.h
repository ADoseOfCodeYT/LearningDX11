﻿#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
using namespace std;
using namespace DirectX;

#include "TextureClass.h"

class ModelClass
{

public:
    ModelClass();
    ModelClass(const ModelClass&);
    ~ModelClass();

    bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*, char*);
    void Shutdown();
    void Render(ID3D11DeviceContext*);

    int GetIndexCount();
    ID3D11ShaderResourceView* GetTexture(int);
    
private:
    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT2 texture;
        XMFLOAT3 normal;
    };

    struct ModelType
    {
        float x, y, z;
        float tu, tv;
        float nx, ny, nz;
    };
public:
    
    bool InitializeBuffers(ID3D11Device* device);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext*);

    bool LoadTextures(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*);
    void ReleaseTextures();

    bool LoadModel(char*);
    void ReleaseModel();

private:
    
    ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
    int m_vertexCount, m_indexCount;

    TextureClass* m_Textures;
    ModelType* m_model;
};

#endif