#pragma once

#include "../wxfb/wxRoboCV_GUI.h"
#include "opencv2/opencv.hpp"

#include <filesystem>

namespace fs = std::filesystem;

extern const wxEventTypeTag<wxThreadEvent> wxEVT_CAMERA_THREAD_UPDATE;

class OpenCVCamera;

class MainFrame : public MainFrame_base, public wxThreadHelper
{
public:
	MainFrame(wxWindow* parent = nullptr);
	~MainFrame();

	void InitializeLog();
	void InitializeDirectoryStructure();
	void InitializeGuiStyle();
	void InitializeCamera();
	void StartCameraThread();
	void PauseResumeCameraThread();

protected:
	void OnClose(wxCloseEvent& event);
	void OnMenuClicked(wxCommandEvent& event);
	void OnToolClicked(wxCommandEvent& event);
	void OnChangeResolution(wxCommandEvent& event);
	void OnCameraViewPaint(wxPaintEvent& event);
	void OnCameraViewResize(wxSizeEvent& event);
	void OnCameraViewKeyDown(wxKeyEvent& event);
    void OnCameraThreadUpdate(wxThreadEvent& event);

private:
	wxThread::ExitCode  Entry();

	std::shared_ptr<OpenCVCamera> m_camera;
	cv::Mat						  m_current_frame;

	wxCriticalSection			  m_cs_camera;
	wxCriticalSection			  m_cs_current_frame;

	fs::path					  m_path_app;
	fs::path					  m_path_screenshots;
};