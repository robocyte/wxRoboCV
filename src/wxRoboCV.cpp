#include "../include/wxRoboCV.h"
#include "../include/MainFrame.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler{});
    wxImage::AddHandler(new wxJPEGHandler{});

    auto frame = new MainFrame{};
    
    frame->InitializeLog();
    frame->InitializeDirectoryStructure();
    frame->SetIcon(wxICON(aaaamain));
    frame->InitializeGuiStyle();
    frame->Show();
    frame->StartCameraThread();

    return true;
}