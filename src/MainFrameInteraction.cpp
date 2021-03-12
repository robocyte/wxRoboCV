#include "../include/MainFrame.h"
#include "wx/stdpaths.h"
#include "wx/log.h"

void MainFrame::OnToolClicked(wxCommandEvent& event)
{
    switch (event.GetId())
    {

    case ID_TB_PAUSE_RESUME_CAMERA:
    {
        PauseResumeCameraThread();
        break;
    }

    case ID_TB_SAVE_LOG:
    {
        wxFileName f(wxStandardPaths::Get().GetExecutablePath());
        wxString appPath(f.GetPath());
        const auto target = appPath + R"(\Log.txt)";
        if (m_tc_log->SaveFile(target)) wxLogMessage("Log saved to %s", target);
        break;
    }

    case ID_TB_CLEAR_LOG:
    {
        m_tc_log->Clear();
        break;
    }

    default: event.Skip();
    }
}

void MainFrame::OnMenuClicked(wxCommandEvent& event)
{
    switch (event.GetId())
    {

    case ID_MENU_EXIT:
    {
        Close();
        break;
    }

    case ID_MENU_VIEW_LOG:
    {
        m_mgr.GetPane("Log").Show();
        m_mgr.Update();
        break;
    }

    case ID_MENU_VIEW_ABOUT:
    {
        m_mgr.GetPane("About").Show();
        m_mgr.Update();
        break;
    }

    default: event.Skip();
    }
}
