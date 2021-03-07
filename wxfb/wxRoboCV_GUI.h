///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame_base
///////////////////////////////////////////////////////////////////////////////
class MainFrame_base : public wxFrame
{
	private:

	protected:
		enum
		{
			ID_VIEW_ABOUT = 1000,
			ID_MENU_EXIT,
			ID_MENU_VIEW_LOG,
			ID_MENU_CAMERA_SOURCE,
			ID_MENU_CAMERA_FORMAT,
			ID_TB_START_CAMERA,
			ID_TB_PAUSE_RESUME_CAMERA,
			ID_TB_STOP_CAMERA,
			ID_SAVE_LOG,
			ID_CLEAR_LOG
		};

		wxMenuBar* m_menubar;
		wxMenu* m_file_menu;
		wxMenu* m_view_menu;
		wxMenu* m_camera_menu;
		wxAuiToolBar* m_toolbar_main;
		wxAuiToolBarItem* m_tb_start_camera;
		wxAuiToolBarItem* m_tb_pause_camera;
		wxAuiToolBarItem* m_tb_stop_camera;
		wxPanel* m_view_camera;
		wxPanel* m_view_log;
		wxAuiToolBar* m_toolbar_log;
		wxAuiToolBarItem* m_tb_save_log;
		wxAuiToolBarItem* m_tb_clear_log;
		wxTextCtrl* m_tc_log;
		wxPanel* m_view_about;
		wxTextCtrl* m_tc_about;
		wxStatusBar* m_statusbar;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnViewWindows( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolbarCamera( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCameraViewPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnCameraViewResize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnSaveLog( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearLog( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrame_base( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxRoboCV"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 842,600 ), long style = wxDEFAULT_FRAME_STYLE|wxBORDER_NONE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;

		~MainFrame_base();

};

