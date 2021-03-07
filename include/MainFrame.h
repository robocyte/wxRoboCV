#pragma once

#include "..\wxfb\wxRoboCV_GUI.h"
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

	void DrawCameraFrame(cv::Mat& pImg);

protected:
	void OnClose(wxCloseEvent& event);
	void OnMenuExit(wxCommandEvent& event);
	void OnToolbarCamera(wxCommandEvent& event);
	void OnViewWindows(wxCommandEvent& event);
	void OnCameraViewPaint(wxPaintEvent& event);
	void OnCameraViewResize(wxSizeEvent& event);
	void OnSaveLog(wxCommandEvent& event);
	void OnClearLog(wxCommandEvent& event);

private:
	wxThread::ExitCode  Entry();

	std::shared_ptr<OpenCVCamera> m_camera;
	wxImage						  m_image;
	wxBitmap					  m_current_bitmap;
	wxMutex						  m_image_mutex;
};