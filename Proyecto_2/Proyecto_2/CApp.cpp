#pragma once
#include "CApp.h"


CApp::CApp()
{
    m_ptrRenderer = new COpenGLRenderer();
    m_ptrWindow = new CGameWindow(m_ptrRenderer, 1080, 720);
}
CApp::~CApp() {
    if (m_ptrRenderer != nullptr) {
        delete m_ptrWindow;
        m_ptrRenderer = nullptr;
    }
    if (m_ptrWindow != nullptr) {
        delete m_ptrRenderer;
        m_ptrRenderer = nullptr;
    }
}

bool CApp::isWindowInitialized() const
{
    if (m_ptrWindow != NULL)
    {
        return m_ptrWindow->isLibraryInitialized();
    }

    return false;
}

/* */

bool CApp::canRun() const
{
    return isWindowInitialized();
}
