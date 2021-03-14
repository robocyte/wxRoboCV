#pragma once

#include <opencv2/videoio.hpp>

class MainFrame;

struct Resolution
{
	Resolution(int width, int height)
	: m_width(width)
	, m_height(height)
	{}
	
	int m_width;
	int m_height;
};

class OpenCVCamera
{
public:
	OpenCVCamera(MainFrame* parent = nullptr);
	~OpenCVCamera();

	bool Initialize();
	void GetNextFrame();

	const Resolution				GetResolution()				{ return m_current_resolution; }
	const std::vector<Resolution>&  GetSupportedResolutions()	{ return m_supported_resolutions; }

	void SetResolution(std::size_t resolution_index);

	int GetFps();

private:

	void CheckSupportedResolutions();

	MainFrame*				m_parent_frame;
	cv::Mat					m_video_img;
	cv::VideoCapture		m_capture;
	Resolution				m_current_resolution;
	std::vector<Resolution> m_supported_resolutions;
};