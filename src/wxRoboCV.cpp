#include "..\include\wxRoboCV.h"
#include "..\include\MainFrame.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler{});
    wxImage::AddHandler(new wxJPEGHandler{});

    auto frame = new MainFrame{};
    
    frame->InitializeLog();
    frame->InitializeCamera();
    //frame->SetIcon(wxICON(aaaamain));
    frame->InitializeGuiStyle();
    frame->Maximize();
    frame->Show();
    //frame->StartCameraThread();

    return true;
}