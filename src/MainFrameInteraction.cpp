#include "../include/MainFrame.h"
#include "../include/OpenCVCamera.h"
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
        const auto filename = m_path_app.string() + R"(\Log.txt)";
        if (m_tc_log->SaveFile(filename))
        {
            wxLogMessage("Log saved to %s", filename);
        }
        else
        {
            wxLogMessage("ERROR: Couldn't save %s", filename);
        }

        break;
    }

    case ID_TB_CLEAR_LOG:
    {
        m_tc_log->Clear();
        break;
    }

    case ID_TB_SCREENSHOT:
    {
        cv::Mat output;

        {
            wxCriticalSectionLocker lock{ m_cs_current_frame };
            cv::cvtColor(m_current_frame, output, cv::COLOR_BGR2RGB);
        }

        const auto filename = m_path_screenshots.string() + R"(\screenshot.png)";
        if (cv::imwrite(filename, output))
        {
            wxLogMessage("Screenshot saved to %s", filename);
        }
        else
        {
            wxLogMessage("ERROR: Couldn't save %s", filename);
        }

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

void MainFrame::OnChangeResolution(wxCommandEvent& event)
{
    if (GetThread() && GetThread()->IsRunning()) GetThread()->Pause();
    wxLogMessage("Camera thread paused");

    {
        wxCriticalSectionLocker lock{ m_cs_camera };
        m_camera->SetResolution(event.GetSelection());
        auto resolution_string = std::to_string(m_camera->GetResolution().m_width) + "x"
            + std::to_string(m_camera->GetResolution().m_height) + " @"
            + std::to_string(m_camera->GetFps()) + "fps";
        m_statusbar->SetStatusText(wxString(resolution_string), 2);
    }

    GetThread()->Resume();
    wxLogMessage("Camera thread resumed");
}

void MainFrame::OnCameraViewKeyDown(wxKeyEvent& event)
{
    wxChar uc = event.GetUnicodeKey();
    if (uc != WXK_NONE)
    {
        // It's a "normal" character. Notice that this includes
        // control characters in 1..31 range, e.g. WXK_RETURN or
        // WXK_BACK, so check for them explicitly.
        if (uc >= 32)
        {
            wxLogMessage("You pressed '%c'", uc);
        }
        else
        {
            // It's a control character
        }
    }
    else // No Unicode equivalent.
    {
        // It's a special key, deal with all the known ones:
        switch (event.GetKeyCode())
        {
        case WXK_LEFT:
            break;
        case WXK_RIGHT:
            break;
        case WXK_F1:
            break;
        }
    }
}