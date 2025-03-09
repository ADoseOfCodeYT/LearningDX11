#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

#include "Renderer/D3DClass.h"
#include "Shaders/ColorShaderClass.h"
#include "Scene/CameraClass.h"
#include "Scene/ModelClass.h"
#include "Scene/LightClass.h"
#include "Shaders/LightShaderClass.h"
#include "Shaders/TextureShaderClass.h"
#include "2D/BitmapClass.h"

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
    BitmapClass* m_Bitmap;
    LightClass* m_Lights;
    int m_numLights;
};

constexpr bool FULL_SCREEN = true;
constexpr bool VSYNC_ENABLED = true;
constexpr float SCREEN_DEPTH = 1000.0f;
constexpr float SCREEN_NEAR = 0.3f;
const LPCWSTR APPLICATION_NAME = L"Learning DX11";

#endif
