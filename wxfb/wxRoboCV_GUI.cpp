///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxRoboCV_GUI.h"

///////////////////////////////////////////////////////////////////////////

MainFrame_base::MainFrame_base( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,300 ), wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_ALLOW_ACTIVE_PANE|wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_DEFAULT|wxAUI_MGR_HINT_FADE|wxAUI_MGR_LIVE_RESIZE|wxAUI_MGR_NO_VENETIAN_BLINDS_FADE|wxAUI_MGR_TRANSPARENT_DRAG|wxAUI_MGR_TRANSPARENT_HINT);

	m_menubar = new wxMenuBar( 0|wxBORDER_NONE );
	m_file_menu = new wxMenu();
	wxMenuItem* m_menu_about;
	m_menu_about = new wxMenuItem( m_file_menu, ID_VIEW_ABOUT, wxString( wxT("About...") ) , wxEmptyString, wxITEM_NORMAL );
	m_file_menu->Append( m_menu_about );

	m_file_menu->AppendSeparator();

	wxMenuItem* m_menu_exit;
	m_menu_exit = new wxMenuItem( m_file_menu, ID_MENU_EXIT, wxString( wxT("E&xit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Exit the application"), wxITEM_NORMAL );
	m_file_menu->Append( m_menu_exit );

	m_menubar->Append( m_file_menu, wxT("&File") );

	m_view_menu = new wxMenu();
	wxMenuItem* m_menu_view_log;
	m_menu_view_log = new wxMenuItem( m_view_menu, ID_MENU_VIEW_LOG, wxString( wxT("Log") ) , wxT("Show log window"), wxITEM_NORMAL );
	m_view_menu->Append( m_menu_view_log );

	m_menubar->Append( m_view_menu, wxT("&View") );

	m_camera_menu = new wxMenu();
	wxMenuItem* m_menu_camera_source;
	m_menu_camera_source = new wxMenuItem( m_camera_menu, ID_MENU_CAMERA_SOURCE, wxString( wxT("Camera source") ) , wxEmptyString, wxITEM_NORMAL );
	m_camera_menu->Append( m_menu_camera_source );

	wxMenuItem* m_menu_camera_format;
	m_menu_camera_format = new wxMenuItem( m_camera_menu, ID_MENU_CAMERA_FORMAT, wxString( wxT("Camera format") ) , wxEmptyString, wxITEM_NORMAL );
	m_camera_menu->Append( m_menu_camera_format );

	m_menubar->Append( m_camera_menu, wxT("&Camera") );

	this->SetMenuBar( m_menubar );

	m_toolbar_main = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	m_tb_start_camera = m_toolbar_main->AddTool( ID_TB_START_CAMERA, wxT("Start camera"), wxICON( play_icon ), wxNullBitmap, wxITEM_NORMAL, wxT("Start camera"), wxT("Start camera"), NULL );

	m_tb_pause_camera = m_toolbar_main->AddTool( ID_TB_PAUSE_RESUME_CAMERA, wxT("Pause/resume camera"), wxICON( play_pause_icon ), wxNullBitmap, wxITEM_NORMAL, wxT("Pause/resume camera"), wxT("Pause/resume camera"), NULL );

	m_tb_stop_camera = m_toolbar_main->AddTool( ID_TB_STOP_CAMERA, wxT("Stop camera"), wxICON( stop_icon ), wxNullBitmap, wxITEM_NORMAL, wxT("Stop camera"), wxT("Stop camera"), NULL );

	m_toolbar_main->Realize();
	m_mgr.AddPane( m_toolbar_main, wxAuiPaneInfo().Top().CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( true ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).Layer( 10 ) );

	m_view_camera = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_view_camera, wxAuiPaneInfo() .Left() .Caption( wxT("Camera view") ).MaximizeButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).CentrePane() );

	m_view_log = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_view_log, wxAuiPaneInfo() .Name( wxT("Log") ).Bottom() .Caption( wxT("Log") ).MaximizeButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).MinSize( wxSize( 400,100 ) ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	m_toolbar_log = new wxAuiToolBar( m_view_log, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxAUI_TB_VERTICAL|wxBORDER_NONE );
	m_toolbar_log->SetToolBitmapSize( wxSize( 22,22 ) );
	m_toolbar_log->SetToolPacking( 2 );
	m_tb_save_log = m_toolbar_log->AddTool( ID_SAVE_LOG, wxT("Save log"), wxICON( save_icon ), wxNullBitmap, wxITEM_NORMAL, wxT("Save the log to a .txt file"), wxT("Save the log to a .txt file"), NULL );

	m_tb_clear_log = m_toolbar_log->AddTool( ID_CLEAR_LOG, wxT("Clear log"), wxICON( clear_log_icon ), wxNullBitmap, wxITEM_NORMAL, wxT("Clear the log window"), wxT("Clear the log window"), NULL );

	m_toolbar_log->Realize();

	bSizer1->Add( m_toolbar_log, 0, wxEXPAND, 5 );

	m_tc_log = new wxTextCtrl( m_view_log, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_READONLY|wxBORDER_NONE );
	bSizer1->Add( m_tc_log, 1, wxEXPAND, 5 );


	m_view_log->SetSizer( bSizer1 );
	m_view_log->Layout();
	bSizer1->Fit( m_view_log );
	m_view_about = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_view_about, wxAuiPaneInfo() .Name( wxT("About") ).Left() .Caption( wxT("About wxOpenCV") ).Hide().Float().FloatingPosition( wxPoint( 649,436 ) ).Resizable().FloatingSize( wxSize( 316,339 ) ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).MinSize( wxSize( 300,300 ) ) );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_tc_about = new wxTextCtrl( m_view_about, wxID_ANY, wxT("This is awesome!\n"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER|wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY|wxBORDER_NONE );
	bSizer2->Add( m_tc_about, 1, wxEXPAND, 5 );


	m_view_about->SetSizer( bSizer2 );
	m_view_about->Layout();
	bSizer2->Fit( m_view_about );
	m_statusbar = this->CreateStatusBar( 4, wxSTB_SIZEGRIP|wxBORDER_NONE, wxID_ANY );

	m_mgr.Update();
	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame_base::OnClose ) );
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame_base::OnUpdateUI ) );
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_base::OnViewWindows ), this, m_menu_about->GetId());
	m_file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_base::OnMenuExit ), this, m_menu_exit->GetId());
	m_view_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame_base::OnViewWindows ), this, m_menu_view_log->GetId());
	this->Connect( m_tb_start_camera->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnToolbarCamera ) );
	this->Connect( m_tb_pause_camera->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnToolbarCamera ) );
	this->Connect( m_tb_stop_camera->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnToolbarCamera ) );
	m_view_camera->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame_base::OnCameraViewPaint ), NULL, this );
	m_view_camera->Connect( wxEVT_SIZE, wxSizeEventHandler( MainFrame_base::OnCameraViewResize ), NULL, this );
	this->Connect( m_tb_save_log->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnSaveLog ) );
	this->Connect( m_tb_clear_log->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnClearLog ) );
}

MainFrame_base::~MainFrame_base()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame_base::OnClose ) );
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame_base::OnUpdateUI ) );
	this->Disconnect( m_tb_start_camera->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnToolbarCamera ) );
	this->Disconnect( m_tb_pause_camera->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnToolbarCamera ) );
	this->Disconnect( m_tb_stop_camera->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnToolbarCamera ) );
	m_view_camera->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame_base::OnCameraViewPaint ), NULL, this );
	m_view_camera->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MainFrame_base::OnCameraViewResize ), NULL, this );
	this->Disconnect( m_tb_save_log->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnSaveLog ) );
	this->Disconnect( m_tb_clear_log->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame_base::OnClearLog ) );

	m_mgr.UnInit();

}
