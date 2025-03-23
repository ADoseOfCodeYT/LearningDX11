#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

#include "Renderer/D3DClass.h"

#include "Scene/CameraClass.h"
#include "Scene/ModelClass.h"
#include "Scene/LightClass.h"

#include "Shaders/LightShaderClass.h"
#include "Shaders/FontShaderClass.h"
#include "Shaders/LightMapShaderClass.h"

#include "2D/FontClass.h"
#include "2D/TextClass.h"
#include "2D/FPSClass.h"

#include "Input/InputClass.h"


class ApplicationClass
{
public:
    ApplicationClass();
    ApplicationClass(const ApplicationClass&);
    ~ApplicationClass();

    bool Initialize(int, int, HWND);
    void Shutdown();
    bool Frame(InputClass*);

private:
    bool Render(float);
    bool UpdateFps();

    FontShaderClass* m_FontShader;
    FontClass* m_Font;
    
    FPSClass* m_Fps;
    TextClass* m_FpsString;
    int m_previousFps;

    D3DClass* m_Direct3D;
    CameraClass* m_Camera;
    ModelClass* m_Model;
    
    LightShaderClass* m_LightShader;
    LightClass* m_Lights;
    int m_numLights;
    
    LightMapShaderClass* m_LightMapShader;
};

constexpr bool REALTIME_LIGHTING = true;
constexpr bool FULL_SCREEN = false;
constexpr bool VSYNC_ENABLED = true;
constexpr float SCREEN_DEPTH = 1000.0f;
constexpr float SCREEN_NEAR = 0.3f;
const LPCWSTR APPLICATION_NAME = L"Learning DX11";

#endif
