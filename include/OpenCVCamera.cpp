#include "../include/OpenCVCamera.h"

#include <opencv2/imgproc.hpp>

OpenCVCamera::OpenCVCamera()
	: m_current_resolution(0, 0)
{
}

OpenCVCamera::~OpenCVCamera()
{
	m_capture.release();
}

bool OpenCVCamera::Initialize()
{
	m_capture.open(0);

	//CheckSupportedResolutions();
	m_capture.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
	m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1280);
	if (!m_capture.isOpened()) return false;

	// Grab first frame to initialize format
	cv::Mat init_frame;
	m_capture.read(init_frame);

	m_current_resolution.m_width  = static_cast<int>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH));
	m_current_resolution.m_height = static_cast<int>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT));

	return true;
}

void OpenCVCamera::SetResolution(std::size_t resolution_index)
{
	m_capture.open(0);
	m_current_resolution = m_supported_resolutions[resolution_index];
	m_capture.set(cv::CAP_PROP_FRAME_WIDTH,  m_current_resolution.m_width);
	m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, m_current_resolution.m_height);
}

void OpenCVCamera::CheckSupportedResolutions()
{
	const std::vector<Resolution> resolutions = {   {1920, 1080},	// 16:9		2.073MP
													{1280, 720},	// 16:9		0.921MP
													{1024, 576},	// 16:9		0.589MP
													{800, 600},		// 4:3		0.480MP
													{640, 480} };	// 4:3		0.307MP

	for (const auto res : resolutions)
	{
		m_capture.set(cv::CAP_PROP_FRAME_WIDTH,  res.m_width);
		m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, res.m_height);

		int width  = static_cast<int>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH));
		int height = static_cast<int>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT));

		if (width == res.m_width && height == res.m_height)
			m_supported_resolutions.push_back(res);
	}
}

cv::Mat OpenCVCamera::GetNextFrame()
{
	cv::Mat next_frame, result;
	m_capture.read(next_frame);

	if (!next_frame.empty())
		cv::cvtColor(next_frame, result, cv::COLOR_BGR2RGB);

	return result;
}

int OpenCVCamera::GetFps()
{
	return static_cast<int>(m_capture.get(cv::CAP_PROP_FPS));
}
