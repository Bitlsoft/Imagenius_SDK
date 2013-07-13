// IGHistoryManager.h : Declaration of the CIGHistoryManager
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "IGPictureEditor_i.h"
#include "IGDockPanel.h"
#include <IGSmartPtr.h>
#include <IGScrollBar.h>
#include <IGFrameManager.h>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif


// CIGHistoryManager
class ATL_NO_VTABLE CIGHistoryManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IIGHistoryManager, &IID_IIGHistoryManager, &LIBID_IGPictureEditorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CIGHistoryManager>,
	public IOleControlImpl<CIGHistoryManager>,
	public IOleObjectImpl<CIGHistoryManager>,
	public IOleInPlaceActiveObjectImpl<CIGHistoryManager>,
	public IViewObjectExImpl<CIGHistoryManager>,
	public IOleInPlaceObjectWindowlessImpl<CIGHistoryManager>,
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	public IObjectSafetyImpl<CIGHistoryManager, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif
	public CComCoClass<CIGHistoryManager, &CLSID_IGHistoryManager>,
	public CComControl<CIGHistoryManager>,
	public IDispEventSimpleImpl <1, CIGHistoryManager, &__uuidof(_IIGDockPanelEvents)>
{
public:

#pragma warning(push)
#pragma warning(disable: 4355) // 'this' : used in base member initializer list


	CIGHistoryManager();
	virtual ~CIGHistoryManager();

	STDMETHODIMP  CreateFrame (OLE_HANDLE hParent, IDispatch *pDispDockPanel = NULL);
	STDMETHODIMP  DestroyFrame();	

#pragma warning(pop)

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_IGHISTORYMANAGER)


BEGIN_COM_MAP(CIGHistoryManager)
	COM_INTERFACE_ENTRY(IIGHistoryManager)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
END_COM_MAP()

BEGIN_PROP_MAP(CIGHistoryManager)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()


BEGIN_MSG_MAP(CIGHistoryManager)
	MESSAGE_HANDLER(WM_PAINT, OnBackgroundPaint)
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawListBoxItem)
	MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureListBoxItem)
	MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnMove)
	COMMAND_ID_HANDLER(LBN_SELCHANGE, OnSelChanged)
	CHAIN_MSG_MAP(CComControl<CIGHistoryManager>)
ALT_MSG_MAP(1)
	// Replace this with message map entries for superclassed ListBox
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

BEGIN_SINK_MAP(CIGHistoryManager)
	SINK_ENTRY_INFO (1, __uuidof (_IIGDockPanelEvents), 1, &CIGHistoryManager::OnPanelOpening, &EventPanelOpenInfo)
	SINK_ENTRY_INFO (1, __uuidof (_IIGDockPanelEvents), 2, &CIGHistoryManager::OnPanelOpened, &EventPanelOpenInfo)
	SINK_ENTRY_INFO (1, __uuidof (_IIGDockPanelEvents), 3, &CIGHistoryManager::OnPanelClosing, &EventPanelOpenInfo)
END_SINK_MAP()

	BOOL PreTranslateAccelerator(LPMSG pMsg, HRESULT& hRet)
	{
		if(pMsg->message == WM_KEYDOWN)
		{
			switch(pMsg->wParam)
			{
			case VK_LEFT:
			case VK_RIGHT:
			case VK_UP:
			case VK_DOWN:
			case VK_HOME:
			case VK_END:
			case VK_NEXT:
			case VK_PRIOR:
				hRet = S_FALSE;
				return TRUE;
			}
		}
		//TODO: Add your additional accelerator handling code here
		return FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IIGHistoryManager
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

protected:
	LRESULT OnMove (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnBackgroundPaint (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMeasureListBoxItem (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDrawListBoxItem (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseListBackground (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSelChanged (WPARAM wParam, LPARAM lParam, HWND hWnd, BOOL& bHandled);

private:
	static LRESULT APIENTRY StaticHookListBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
  	LRESULT HookListBoxProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// _IIGDockPanelEvents
	void __stdcall OnPanelOpening ();
	void __stdcall OnPanelOpened ();
	void __stdcall OnPanelClosing ();

	void populateListBox();

	CComQIPtr <IIGDockPanel>							m_spDockPanelOwner;
	IGLibrary::IGSingleton <IGLibrary::IGFrameManager>	m_spFrameMgr;
	IGLibrary::IGSmartPtr <IGLibrary::IGScrollBar>		m_spScrollBar;
	IGLibrary::IGSmartPtr <IGLibrary::IGFrame>			m_spFrame;	
	RECT				m_rcWnd;
	HWND				m_hListBox;
};

OBJECT_ENTRY_AUTO(__uuidof(IGHistoryManager), CIGHistoryManager)
