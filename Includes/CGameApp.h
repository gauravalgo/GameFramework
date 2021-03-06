//-----------------------------------------------------------------------------
// File: CGameApp.h
//
// Desc: Game Application class, this is the central hub for all app processing
//
// Original design by Adam Hoult & Gary Simmons. Modified by Mihai Popescu.
//-----------------------------------------------------------------------------

#ifndef _CGAMEAPP_H_
#define _CGAMEAPP_H_

//-----------------------------------------------------------------------------
// CGameApp Specific Includes
//-----------------------------------------------------------------------------
#include "Main.h"
#include "CTimer.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include "BackBuffer.h"
#include "ResizableImage.h"
#include "ParallaxLayer.h"
#include "Singleton.h"
#include <vector>
#include <memory>

//-----------------------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name : CGameApp (Class)
// Desc : Central game engine, initializes the game and handles core processes.
//-----------------------------------------------------------------------------
class CGameApp : public Singleton<CGameApp>
{
    SINGLETON_DECL(CGameApp);
public:
	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	virtual ~CGameApp();

	//-------------------------------------------------------------------------
	// Public Functions for This Class
	//-------------------------------------------------------------------------
	LRESULT     DisplayWndProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam );
	bool        InitInstance( LPCTSTR lpCmdLine, int iCmdShow );
	int         BeginGame( );
	bool        ShutDown( );
    HDC         GetBackBufferDC() const { return m_pBBuffer ? m_pBBuffer->getDC() : NULL; }

	ULONG       GetViewWidth() const { return m_nViewWidth; }
	ULONG       GetViewHeight() const { return m_nViewHeight; }

	CGameObject* GetParalaxLayer() { return m_pParallax; }
	
private:
	//-------------------------------------------------------------------------
	// Private Functions for This Class
	//-------------------------------------------------------------------------
	bool        BuildObjects	( );
	void        ReleaseObjects	( );
	void        FrameAdvance	( );
	bool        CreateDisplay	( );
	void        ChangeDevice	( );
	void        SetupGameState	( );
	void        AnimateObjects	( );
	void        DrawObjects		( );
	void        ProcessInput	( );
	void        CollisionDetection();
	void		DoGameLogic		();
	
	//-------------------------------------------------------------------------
	// Private Static Functions For This Class
	//-------------------------------------------------------------------------
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

	//-------------------------------------------------------------------------
	// Private Variables For This Class
	//-------------------------------------------------------------------------
	CTimer              m_Timer;            // Game timer
	ULONG               m_LastFrameRate;    // Used for making sure we update only when fps changes.
	
	HWND                m_hWnd;             // Main window HWND
	HICON               m_hIcon;            // Window Icon
	HMENU               m_hMenu;            // Window Menu
	
	bool                m_bActive;          // Is the application active ?

	ULONG               m_nViewX;           // X Position of render viewport
	ULONG               m_nViewY;           // Y Position of render viewport
	ULONG               m_nViewWidth;       // Width of render viewport
	ULONG               m_nViewHeight;      // Height of render viewport

	POINT               m_OldCursorPos;     // Old cursor position for tracking
	HINSTANCE		    m_hInstance;		// Window instance

	BackBuffer*         m_pBBuffer;
    ParallaxLayer*      m_pParallax;

	std::vector<std::shared_ptr<CGameObject>>   m_vGameObjects; // Vector with all game objects
	std::weak_ptr<CPlayer>                      m_pPlayer;      // a weak pointer to player
};

#endif // _CGAMEAPP_H_