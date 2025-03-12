﻿#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

#include "Renderer/D3DClass.h"
#include "Shaders/ColorShaderClass.h"
#include "Scene/CameraClass.h"
#include "Scene/ModelClass.h"
#include "Scene/LightClass.h"
#include "Shaders/LightShaderClass.h"
#include "Shaders/TextureShaderClass.h"
#include "2D/SpriteClass.h"
#include "Helpers/TImerClass.h"
#include "2D/FontClass.h"
#include "2D/TextClass.h"
#include "Shaders/FontShaderClass.h"


class ApplicationClass
{
public:
    ApplicationClass();
    ApplicationClass(const ApplicationClass&);
    ~ApplicationClass();

    bool Initialize(int, int, HWND);
    void Shutdown();
    bool Frame();

private:
    bool Render(float);

    D3DClass* m_Direct3D;
    CameraClass* m_Camera;
    ModelClass* m_Model;
    LightShaderClass* m_LightShader;
    TextureShaderClass* m_TextureShader;
    LightClass* m_Lights;
    int m_numLights;
    SpriteClass* m_Sprite;
    TimerClass* m_Timer;
    FontShaderClass* m_FontShader;
    FontClass* m_Font;
    TextClass *m_TextString1, *m_TextString2, * m_TextString3;
};

constexpr bool FULL_SCREEN = false;
constexpr bool VSYNC_ENABLED = true;
constexpr float SCREEN_DEPTH = 1000.0f;
constexpr float SCREEN_NEAR = 0.3f;
const LPCWSTR APPLICATION_NAME = L"Learning DX11";

#endif
