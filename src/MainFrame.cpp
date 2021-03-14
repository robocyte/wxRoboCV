#include "wx/log.h"
#include "wx/dcclient.h"

#include "opencv2/imgproc.hpp"

#include "../include/MainFrame.h"
#include "../include/OpenCVCamera.h"

#include <string>

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

wxThread::ExitCode MainFrame::Entry()
{
    InitializeCamera();
    while (true)
    {
        if (GetThread()->TestDestroy()) break;

        cv::Mat new_frame;

        // GRAB...
        {
            wxCriticalSectionLocker lock{ m_cs_camera };
            new_frame = m_camera->GetNextFrame();
        }

        // ...PROCESS...


        // ...AND DRAW FRAME
        {
            wxCriticalSectionLocker lock{ m_cs_current_frame };
            m_current_frame = new_frame;
        }

        m_view_camera->Refresh(false);
    }

    return wxThread::ExitCode();
}

void MainFrame::InitializeCamera()
{
    wxCriticalSectionLocker lock{ m_cs_camera };
    m_camera = std::make_shared<OpenCVCamera>();
    wxLogMessage("Initializing camera...");
    if (m_camera->Initialize())
    {
        wxLogMessage("Camera successfully initialized");
        auto resolution_string = std::to_string(m_camera->GetResolution().m_width)  + "x"
                               + std::to_string(m_camera->GetResolution().m_height) + " @"
                               + std::to_string(m_camera->GetFps())                 + "fps";
        m_statusbar->SetStatusText(wxString(resolution_string), 2);
        wxLogMessage("Resolution: %s", resolution_string);
        
        //wxLogMessage("Supported resolutions:");
        //auto resolutions = m_camera->GetSupportedResolutions();
        //for (const auto res : resolutions)
        //{
        //    wxLogMessage("%ix%i", res.m_width, res.m_height);
        //    m_tb_choice_resolution->Append(std::to_string(res.m_width) + "x" + std::to_string(res.m_height));
        //}
        //m_tb_choice_resolution->SetSelection(0);
    }
    else
    {
        wxLogMessage("Camera not initialized");
        return;
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

void MainFrame::OnCameraViewPaint(wxPaintEvent& event)
{
    wxPaintDC dc(m_view_camera);
    if (!dc.IsOk()) return;

    dc.SetPen(*wxMEDIUM_GREY_PEN);
    dc.SetBrush(*wxMEDIUM_GREY_BRUSH);

    wxCriticalSectionLocker lock{ m_cs_current_frame };
    if (!m_current_frame.empty())
    {
        int win_width, win_height;
        m_view_camera->GetClientSize(&win_width, &win_height);

        const int new_img_width  = (m_current_frame.cols * win_height) / m_current_frame.rows;
        const int new_img_height = (m_current_frame.rows * win_width)  / m_current_frame.cols;
        const int width_diff  = (win_width  - new_img_width)  / 2;
        const int height_diff = (win_height - new_img_height) / 2;
        
        if (height_diff >= 0)
        {
            cv::Mat dstImg;
            cv::resize(m_current_frame, dstImg, cv::Size(win_width, new_img_height), 0, 0, cv::INTER_AREA);
            cv::rectangle(dstImg, cv::Point(10, 10), cv::Point(win_width - 10, new_img_height - 10), CV_RGB(0, 255, 0), 1);

            wxImage tmpImage(win_width, new_img_height, dstImg.data, true);
            
            dc.DrawRectangle(0, 0, win_width, height_diff);
            dc.DrawBitmap(wxBitmap{ tmpImage }, 0, height_diff);
            dc.DrawRectangle(0, m_current_frame.rows + height_diff, win_width, height_diff);
        }
        else
        {
            cv::Mat dstImg;
            cv::resize(m_current_frame, dstImg, cv::Size(new_img_width, win_height), 0, 0, cv::INTER_AREA);
            cv::rectangle(dstImg, cv::Point(10, 10), cv::Point(new_img_width - 10, win_height - 10), CV_RGB(0, 255, 0), 1);

            wxImage tmpImage(new_img_width, win_height, dstImg.data, true);

            dc.DrawRectangle(0, 0, width_diff, win_height);
            dc.DrawBitmap(wxBitmap{ tmpImage }, width_diff, 0);
            dc.DrawRectangle(m_current_frame.cols + width_diff, 0, width_diff, win_height);
        }
    }
}

void MainFrame::OnCameraViewResize(wxSizeEvent& event)
{
    m_view_camera->Refresh();
    event.Skip();
}

void MainFrame::OnClose(wxCloseEvent& event)
{
    if (GetThread() && GetThread()->IsRunning()) GetThread()->Delete();

    Destroy();
}

MainFrame::~MainFrame()
{
}
