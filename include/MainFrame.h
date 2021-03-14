#pragma once

#include "../wxfb/wxRoboCV_GUI.h"
#include "opencv2/opencv.hpp"

class OpenCVCamera;

class MainFrame : public MainFrame_base, public wxThreadHelper
{
public:
	MainFrame(wxWindow* parent = nullptr);
	~MainFrame();

	void InitializeLog();
	void InitializeGuiStyle();
	void InitializeCamera();
	void StartCameraThread();
	void PauseResumeCameraThread();
	void DrawCameraFrame(cv::Mat& image);

protected:
	void OnClose(wxCloseEvent& event);
	void OnMenuClicked(wxCommandEvent& event);
	void OnToolClicked(wxCommandEvent& event);
	void OnChangeResolution(wxCommandEvent& event);
	void OnCameraViewPaint(wxPaintEvent& event);
	void OnCameraViewResize(wxSizeEvent& event);

private:
	wxThread::ExitCode  Entry();

	std::shared_ptr<OpenCVCamera> m_camera;
	wxImage						  m_image;
	wxMutex						  m_image_mutex;
	wxCriticalSection			  m_cs_camera;
};