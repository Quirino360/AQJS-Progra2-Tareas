#pragma once 
#include "CGameWindow.h"
#include "COpenGLRenderer.h"

#define KEY_MOD_SHIFT     0x0001
#define KEY_MOD_CONTROL   0x0002
#define KEY_MOD_ALT       0x0004
#define KEY_MOD_UNUSED    0x0008

class CApp {

protected:
    CGameWindow* m_ptrWindow;
    COpenGLRenderer* m_ptrRenderer;
    virtual bool initialize() = 0;

public:
    CApp();
    ~CApp();
    bool isWindowInitialized()const;
    bool canRun()const;
    virtual void  update(float dt) = 0;
    virtual void render() = 0;
    virtual void onF2(int mods) {}                       // F2
    virtual void onF3(int mods) {}                       // F3
    virtual void onF4(int mods) {}                       // F4
    virtual void onF5(int mods) {}                       // F5
    virtual void onF6(int mods) {}                       // F6
    virtual void onF7(int mods) {}                       // F7
    virtual void onF8(int mods) {}                       // F8
    virtual void onF9(int mods) {}                       // F9
    virtual void onF10(int mods) {}                       // F10
    virtual void onF11(int mods) {}                       // F11

    virtual void onArrowUp(int mods) {}
    virtual void onArrowDown(int mods) {}
    virtual void onArrowLeft(int mods) {}
    virtual void onArrowRight(int mods) {}

    virtual void onMouseMove(float deltaX, float deltaY) {}
    virtual void Run() = 0;

    COpenGLRenderer* getOpenGLRenderer() { return m_ptrRenderer; }
private:

};