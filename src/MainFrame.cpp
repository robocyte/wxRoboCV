#include "wx/log.h"
#include "wx/dcclient.h"
#include "wx/stdpaths.h"

#include "opencv2/imgproc.hpp"

#include "..\include\MainFrame.h"
#include "..\include\OpenCVCamera.h"

MainFrame::MainFrame(wxWindow* parent)
    : MainFrame_base(parent)
{
}

void MainFrame::InitializeLog()
{
    // Redirect log messages
    wxLog::SetActiveTarget(new wxLogTextCtrl(m_tc_log));
    wxLogMessage("Log initialized");
    wxLogMessage("OS: %s", wxPlatformInfo::Get().GetOperatingSystemDescription());

    const auto font = new wxFont{ 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "consolas" };
    m_tc_log->SetFont(*font);
}

void MainFrame::InitializeCamera()
{
    m_camera = std::make_shared<OpenCVCamera>(this);
    if (m_camera->Initialize())
    {
        wxLogMessage("Camera successfully initialized");
    }
    else
    {
        wxLogMessage("Camera not initialized");
        return;
    }
}

void MainFrame::StartCameraThread()
{
    if (!GetThread())
    {
        if (CreateThread(wxTHREAD_DETACHED) != wxTHREAD_NO_ERROR)
        {
            wxLogError("Error: Could not create the camera thread!");
            return;
        }

        if (GetThread()->Run() != wxTHREAD_NO_ERROR)
        {
            wxLogError("Error: Could not run the camera thread!");
            return;
        }
        else
        {
            wxLogMessage("Camera thread started");
        }
    }
    else
    {
        wxLogMessage("Camera thread already running");
    }
}

void MainFrame::PauseResumeCameraThread()
{
    if (!GetThread()) return;

    if (GetThread()->IsRunning())
    {
        GetThread()->Pause();
        wxLogMessage("Camera thread paused");
    }
    else if (GetThread()->IsPaused())
    {
        GetThread()->Resume();
        wxLogMessage("Camera thread resumed");
    }
}

void MainFrame::DrawCameraFrame(cv::Mat& pImg)
{
    if (pImg.empty()) return;

    int img_width  = m_camera->GetWidth();
    int img_height = m_camera->GetHeight();
    
    int win_width, win_height, new_width, new_height;
    m_view_camera->GetClientSize(&win_width, &win_height);

    const int new_img_width = (img_width * win_height) / img_height;
    const int new_img_height = (img_height * win_width) / img_width;
    const int width_diff = (win_width - new_img_width) / 2;
    const int height_diff = (win_height - new_img_height) / 2;

    if (height_diff >= 0)
    {
        new_width  = win_width;
        new_height = new_img_height;
    }
    else
    {
        new_width  = new_img_width;
        new_height = win_height;
    }

    cv::Mat dstImg;
    cv::resize(pImg, dstImg, cv::Size(new_width, new_height), 0, 0, cv::INTER_AREA);
    cv::rectangle(dstImg, cv::Point(10, 10), cv::Point(new_width - 10, new_height - 10), CV_RGB(0, 255, 0), 1);

    wxImage tmpImage(new_width, new_height, dstImg.data, true);

    m_image_mutex.Lock();
    m_image = tmpImage.Copy();
    m_image_mutex.Unlock();

    m_view_camera->Refresh(false);
}

void MainFrame::OnCameraViewPaint(wxPaintEvent& event)
{
    wxPaintDC dc(m_view_camera);
    if (!dc.IsOk()) return;

    m_image_mutex.Lock();
    if (m_image.IsOk())
    {
        int img_width  = m_image.GetWidth();
        int img_height = m_image.GetHeight();
        
        int win_width, win_height;
        m_view_camera->GetClientSize(&win_width, &win_height);

        const int width_diff  = (win_width - img_width) / 2;
        const int height_diff = (win_height - img_height) / 2;
        
        dc.SetPen(*wxMEDIUM_GREY_PEN);
        dc.SetBrush(*wxMEDIUM_GREY_BRUSH);
        if (height_diff > 0)
        {
            dc.DrawRectangle(0, 0, win_width, height_diff);
            dc.DrawBitmap(wxBitmap{ m_image }, 0, height_diff);
            dc.DrawRectangle(0, img_height + height_diff, win_width, height_diff);
        }
        else
        {
            dc.DrawRectangle(0, 0, width_diff, win_height);
            dc.DrawBitmap(wxBitmap{ m_image }, width_diff, 0);
            dc.DrawRectangle(img_width + width_diff, 0, width_diff, win_height);
        }
    }
    else if (!m_current_bitmap.IsOk())
    {
        m_image_mutex.Unlock();
        return;
    }
    m_image_mutex.Unlock();
}

void MainFrame::OnCameraViewResize(wxSizeEvent& event)
{
    m_view_camera->Refresh();
    event.Skip();
}

void MainFrame::OnSaveLog(wxCommandEvent& event)
{
    wxFileName f(wxStandardPaths::Get().GetExecutablePath());
    wxString appPath(f.GetPath());
    const auto target = appPath + R"(\Log.txt)";
    if (m_tc_log->SaveFile(target)) wxLogMessage("Log saved to %s", target);
}

void MainFrame::OnClearLog(wxCommandEvent& event)
{
    m_tc_log->Clear();
}

wxThread::ExitCode MainFrame::Entry()
{
    while (true)
    {
        if (GetThread()->TestDestroy()) break;

        m_camera->GetNextFrame();

        wxThread::Sleep(5);
    }

    return wxThread::ExitCode();
}

void MainFrame::OnToolbarCamera(wxCommandEvent& event)
{
    switch (event.GetId())
    {
    case ID_TB_START_CAMERA:
        StartCameraThread();
        break;
    case ID_TB_PAUSE_RESUME_CAMERA:
        PauseResumeCameraThread();
        break;
    default: event.Skip();
    }
}

void MainFrame::OnViewWindows(wxCommandEvent& event)
{
    switch (event.GetId())
    {
    //case ID_VIEW_BROWSER:
    //    m_mgr.GetPane("Scene browser").Show();
    //    m_mgr.Update();
    //    break;
    case ID_MENU_VIEW_LOG:
        m_mgr.GetPane("Log").Show();
        m_mgr.Update();
        break;
    case ID_VIEW_ABOUT:
        m_mgr.GetPane("About").Show();
        m_mgr.Update();
        break;
    default: event.Skip();
    }
}

void MainFrame::OnMenuExit(wxCommandEvent& event)
{
    Close();
}

void MainFrame::OnClose(wxCloseEvent& event)
{
    if (GetThread() && GetThread()->IsRunning()) GetThread()->Wait();

    Destroy();
}

MainFrame::~MainFrame()
{
}
