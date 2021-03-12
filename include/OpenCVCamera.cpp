#include "../include/OpenCVCamera.h"
#include "../include/MainFrame.h"

#include <opencv2/imgproc.hpp>

OpenCVCamera::OpenCVCamera(MainFrame* parent)
	: m_width(0)
	, m_height(0)
	, m_parent_frame(parent)
{
}

OpenCVCamera::~OpenCVCamera()
{
	m_capture.release();
	if (!m_video_img.empty()) m_video_img.release();
}

bool OpenCVCamera::Initialize()
{
	m_capture.open(0);
	m_capture.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
	m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1280);
	if (!m_capture.isOpened()) return false;

	// Grab first frame to initialize format
	cv::Mat init_frame;
	m_capture.read(init_frame);

	m_width  = static_cast<int>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH));
	m_height = static_cast<int>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT));

	return true;
}

void OpenCVCamera::GetNextFrame()
{
	cv::Mat next_frame;
	m_capture.read(next_frame);

	if (!next_frame.empty())
	{
		if (!m_video_img.empty())
		{
			m_video_img.release();
			m_video_img = cv::Mat(cv::Size(m_width, m_height), 8, 3);
		}

		cv::cvtColor(next_frame, m_video_img, cv::COLOR_BGR2RGB);

		m_parent_frame->DrawCameraFrame(m_video_img);
	}
}

int OpenCVCamera::GetFps()
{
	return static_cast<int>(m_capture.get(cv::CAP_PROP_FPS));
}
