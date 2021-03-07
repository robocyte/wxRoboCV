#pragma once

#include <opencv2/videoio.hpp>

class MainFrame;

class OpenCVCamera
{
public:
	OpenCVCamera(MainFrame* parent = nullptr);
	~OpenCVCamera();

	bool Initialize();
	void GetNextFrame();

	int GetWidth()  { return m_width; }
	int GetHeight() { return m_height; }

private:
	cv::Mat          m_video_img;
	cv::VideoCapture m_capture;
	int				 m_width;
	int				 m_height;
	MainFrame*		 m_parent_frame;
};