#ifndef _FPSCLASS_H_
#define _FPSCLASS_H_

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

class FPSClass
{
public:
    FPSClass();
    FPSClass(const FPSClass&);
    ~FPSClass();

    void Initialize();
    void Frame();
    int GetFPS();

private:
    int m_fps, m_count;
    unsigned long m_startTime;
    
};

#endif