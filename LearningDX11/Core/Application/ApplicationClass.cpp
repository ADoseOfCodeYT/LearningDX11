#include "ApplicationClass.h"

ApplicationClass::ApplicationClass()
{
    m_Direct3D = 0;
    m_Camera = 0;
    m_Model = 0;
    m_LightShader = 0;
    m_Lights = 0;
    m_TextureShader = 0;
    m_FontShader = 0;
    m_Font = 0;
    m_Fps = 0;
    m_FpsString = 0;
    m_MouseStrings = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}

ApplicationClass::~ApplicationClass()
{
}

bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    char modelFilename[128];
    char textureFilename[128];
    char fpsString[32];
    char mouseString1[32], mouseString2[32], mouseString3[32];
    bool result;

    // Create and initialize the Direct3D object.
    m_Direct3D = new D3DClass;

    result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if(!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
        return false;
    }

    // Create the camera object.
    m_Camera = new CameraClass;

    // Set the initial position of the camera.
    m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

    // Create and initialize the font shader object.
    m_FontShader = new FontShaderClass;

    result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
    if(!result)
    {
        MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
        return false;
    }

    // Create and initialize the font object.
    m_Font = new FontClass;

    result = m_Font->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), 0);
    if(!result)
    {
        return false;
    }

    // Create and initialize the fps object.
    m_Fps = new FPSClass();

    m_Fps->Initialize();

    // Set the initial fps and fps string.
    m_previousFps = -1;
    strcpy_s(fpsString, "Fps: 0");

    // Create and initialize the text object for the fps string.
    m_FpsString  = new TextClass;

    result = m_FpsString ->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, fpsString, 10, 10, 0.0f, 1.0f, 0.0f);
    if(!result)
    {
        return false;
    }

    // Set the initial mouse strings.
    strcpy_s(mouseString1, "Mouse X: 0");
    strcpy_s(mouseString2, "Mouse Y: 0");
    strcpy_s(mouseString3, "Mouse Button: No");

    // Create and initialize the text objects for the mouse strings.
    m_MouseStrings = new TextClass[3];

    result = m_MouseStrings[0].Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, mouseString1, 10, 10, 1.0f, 1.0f, 1.0f);
    if(!result)
    {
        return false;
    }

    result = m_MouseStrings[1].Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, mouseString1, 10, 35, 1.0f, 1.0f, 1.0f);
    if(!result)
    {
        return false;
    }

    result = m_MouseStrings[2].Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, mouseString1, 10, 60, 1.0f, 1.0f, 1.0f);
    if(!result)
    {
        return false;
    }
    
    // Create and initialize the texture shader object.
    m_TextureShader = new TextureShaderClass;

    result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
    if(!result)
    {
        MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
        return false;
    }
    
    // Set the file name of the model.
    strcpy_s(modelFilename, "Content/Plane.txt");

    // Set the name of the texture file that we will be loading.
    strcpy_s(textureFilename, "Content/textures/stone01.tga");
    
    // Create and initialize the model object.
    m_Model = new ModelClass;

    result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename);
    if(!result)
    {
        MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
        return false;
    }
    
    // Create and initialize the light shader object.
    m_LightShader = new LightShaderClass;

    result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
    if(!result)
    {
        MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
        return false;
    }

    // Set the number of lights we will use.
    m_numLights = 4;

    // Create and initialize the light objects array.
    m_Lights = new LightClass[m_numLights];

    // Manually set the color and position of each light.
    m_Lights[0].SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red
    m_Lights[0].SetPosition(-3.0f, 1.0f, 3.0f);

    m_Lights[1].SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);  // Green
    m_Lights[1].SetPosition(3.0f, 1.0f, 3.0f);

    m_Lights[2].SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue
    m_Lights[2].SetPosition(-3.0f, 1.0f, -3.0f);

    m_Lights[3].SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);  // White
    m_Lights[3].SetPosition(3.0f, 1.0f, -3.0f);
    
    return true;
}


void ApplicationClass::Shutdown()
{

    // Release the text objects for the mouse strings.
    if(m_MouseStrings)
    {
        m_MouseStrings[0].Shutdown();
        m_MouseStrings[1].Shutdown();
        m_MouseStrings[2].Shutdown();

        delete [] m_MouseStrings;
        m_MouseStrings = 0;
    }
    
    // Release the text object for the fps string.
    if(m_FpsString)
    {
        m_FpsString->Shutdown();
        delete m_FpsString;
        m_FpsString = 0;
    }

    // Release the fps object.
    if(m_Fps)
    {
        delete m_Fps;
        m_Fps = 0;
    }
    
    // Release the font object.
    if(m_Font)
    {
        m_Font->Shutdown();
        delete m_Font;
        m_Font = 0;
    }

    // Release the font shader object.
    if(m_FontShader)
    {
        m_FontShader->Shutdown();
        delete m_FontShader;
        m_FontShader = 0;
    }
    
    // Release the texture shader object.
    if(m_TextureShader)
    {
        m_TextureShader->Shutdown();
        delete m_TextureShader;
        m_TextureShader = 0;
    }
    
    // Release the light objects.
    if(m_Lights)
    {
        delete [] m_Lights;
        m_Lights = 0;
    }

    // Release the light shader object.
    if(m_LightShader)
    {
        m_LightShader->Shutdown();
        delete m_LightShader;
        m_LightShader = 0;
    }

    // Release the model object.
    if (m_Model)
    {
        m_Model->Shutdown();
        delete m_Model;
        m_Model = 0;
    }

    // Release the camera object.
    if (m_Camera)
    {
        delete m_Camera;
        m_Camera = 0;
    }
    
    // Release the Direct3D object.
    if(m_Direct3D)
    {
        m_Direct3D->Shutdown();
        delete m_Direct3D;
        m_Direct3D = 0;
    }
    
    return;
}

bool ApplicationClass::Frame(InputClass* Input)
{
    int mouseX, mouseY;
    bool mouseDown;
    static float rotation = 0.0f;
    float frameTime;
    bool result;

    // Update the frames per second each frame.
    result = UpdateFps();
    if(!result)
    {
        return false;
    }
    
    // Update the rotation variable each frame.
    rotation -= 0.0174532925f * 0.1f;
    if(rotation < 0.0f)
    {
        rotation += 360.0f;
    }
    
    // Render the graphics scene.
    result = Render(rotation);
    if(!result)
    {
        return false;
    }

    // Check if the user pressed escape and wants to exit the application.
    if(Input->IsEscapePressed())
    {
        return false;
    }

    // Get the location of the mouse from the input object,
    Input->GetMouseLocation(mouseX, mouseY);

    // Check if the mouse has been pressed.
    mouseDown = Input->IsMousePressed();

    // Update the mouse strings each frame.
    result = UpdateMouseStrings(mouseX, mouseY, mouseDown);
    if(!result)
    {
        return false;
    }
    
    return true;
}


bool ApplicationClass::Render(float rotation)
{
    XMMATRIX worldMatrix, viewMatrix, projectionMatrix, rotateMatrix, translateMatrix, orthoMatrix;
    XMFLOAT4 diffuseColor[4], lightPosition[4];
    int i;
    bool result;
    
    // Clear the buffers to begin the scene.
    m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

    // Generate the view matrix based on the camera's position.
    m_Camera->Render();

    // Get the world, view, and projection matrices from the camera and d3d objects.
    m_Direct3D->GetWorldMatrix(worldMatrix);
    m_Camera->GetViewMatrix(viewMatrix);
    m_Direct3D->GetProjectionMatrix(projectionMatrix);
    m_Direct3D->GetOrthoMatrix(orthoMatrix);

    rotateMatrix = XMMatrixRotationRollPitchYaw(rotation,0,rotation);  // Build the rotation matrix.
    translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);  // Build the translation matrix.

    // Multiply them together to create the final world transformation matrix.
    worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

    // Get the light properties.
    for(i=0; i<m_numLights; i++)
    {
        // Create the diffuse color array from the four light colors.
        diffuseColor[i] = m_Lights[i].GetDiffuseColor();

        // Create the light position array from the four light positions.
        lightPosition[i] = m_Lights[i].GetPosition();
    }

    // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
    m_Model->Render(m_Direct3D->GetDeviceContext());
    
    // Render the model using the light shader.
    result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(),
                                   diffuseColor, lightPosition);
    if(!result)
    {
        return false;
    }

    m_Direct3D->TurnZBufferOff();
    m_Direct3D->EnableAlphaBlending();
    
    // Remove rotation for 2D
    worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);; 

    // Render the fps text string using the font shader.
    m_FpsString->Render(m_Direct3D->GetDeviceContext());

    result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_FpsString->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, 
                                  m_Font->GetTexture(), m_FpsString->GetPixelColor());
    if(!result)
    {
        return false;
    }

    // Render the mouse text strings using the font shader.
    for(i=0; i<3; i++)
    {
        m_MouseStrings[i].Render(m_Direct3D->GetDeviceContext());

        result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_MouseStrings[i].GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, 
                                      m_Font->GetTexture(), m_MouseStrings[i].GetPixelColor());
        if(!result)
        {
            return false;
        }	
    }
    
    m_Direct3D->TurnZBufferOn();
    m_Direct3D->DisableAlphaBlending();
    
    // Present the rendered scene to the screen.
    m_Direct3D->EndScene();
    
    return true;
}

bool ApplicationClass::UpdateFps()
{
    int fps;
    char tempString[16], finalString[16];
    float red, green, blue;
    bool result;


    // Update the fps each frame.
    m_Fps->Frame();

    // Get the current fps.
    fps = m_Fps->GetFPS();

    // Check if the fps from the previous frame was the same, if so don't need to update the text string.
    if(m_previousFps == fps)
    {
        return true;
    }

    // Store the fps for checking next frame.
    m_previousFps = fps;

    // Truncate the fps to below 100,000.
    if(fps > 99999)
    {
        fps = 99999;
    }

    // Convert the fps integer to string format.
    sprintf_s(tempString, "%d", fps);

    // Setup the fps string.
    strcpy_s(finalString, "Fps: ");
    strcat_s(finalString, tempString);

    // If fps is 60 or above set the fps color to green.
    if(fps >= 60)
    {
        red = 0.0f;
        green = 1.0f;
        blue = 0.0f;
    }

    // If fps is below 60 set the fps color to yellow.
    if(fps < 60)
    {
        red = 1.0f;
        green = 1.0f;
        blue = 0.0f;
    }

    // If fps is below 30 set the fps color to red.
    if(fps < 30)
    {
        red = 1.0f;
        green = 0.0f;
        blue = 0.0f;
    }

    // Update the sentence vertex buffer with the new string information.
    result = m_FpsString->UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 10, red, green, blue);
    if(!result)
    {
        return false;
    }

    return true;
}

bool ApplicationClass::UpdateMouseStrings(int mouseX, int mouseY, bool mouseDown)
{
    char tempString[16], finalString[32];
    bool result;


    // Convert the mouse X integer to string format.
    sprintf_s(tempString, "%d", mouseX);

    // Setup the mouse X string.
    strcpy_s(finalString, "Mouse X: ");
    strcat_s(finalString, tempString);

    // Update the sentence vertex buffer with the new string information.
    result = m_MouseStrings[0].UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 30, 1.0f, 1.0f, 1.0f);
    if(!result)
    {
        return false;
    }

    // Convert the mouse Y integer to string format.
    sprintf_s(tempString, "%d", mouseY);

    // Setup the mouse Y string.
    strcpy_s(finalString, "Mouse Y: ");
    strcat_s(finalString, tempString);

    // Update the sentence vertex buffer with the new string information.
    result = m_MouseStrings[1].UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 50, 1.0f, 1.0f, 1.0f);
    if(!result)
    {
        return false;
    }

    // Setup the mouse button string.
    if(mouseDown)
    {
        strcpy_s(finalString, "Mouse Button: Yes");
    }
    else
    {
        strcpy_s(finalString, "Mouse Button: No");
    }

    // Update the sentence vertex buffer with the new string information.
    result = m_MouseStrings[2].UpdateText(m_Direct3D->GetDeviceContext(), m_Font, finalString, 10, 70, 1.0f, 1.0f, 1.0f);
    if(!result)
    {
        return false;
    }

    return true;
}
