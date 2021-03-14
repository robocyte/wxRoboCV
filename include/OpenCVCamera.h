#pragma once

#include <opencv2/videoio.hpp>

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
	OpenCVCamera();
	~OpenCVCamera();

	bool Initialize();
	cv::Mat GetNextFrame();

	const Resolution				GetResolution()				{ return m_current_resolution; }
	const std::vector<Resolution>&  GetSupportedResolutions()	{ return m_supported_resolutions; }

	void SetResolution(std::size_t resolution_index);

	int GetFps();

private:

	void CheckSupportedResolutions();

	cv::VideoCapture		m_capture;
	Resolution				m_current_resolution;
	std::vector<Resolution> m_supported_resolutions;
};