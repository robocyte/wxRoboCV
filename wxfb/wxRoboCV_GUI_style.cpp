#include "wx/dc.h"
#include "wx/dcclient.h"

#include "wxRoboCV_GUI_style.hpp"
#include "..\include\MainFrame.h"

wxString wxAuiChopText(wxDC& dc, const wxString& text, int max_size)
{
    wxCoord x, y;

    // first check if the text fits with no problems
    dc.GetTextExtent(text, &x, &y);
    if (x <= max_size)
        return text;

    size_t i, len = text.Length();
    size_t last_good_length = 0;
    for (i = 0; i < len; ++i)
    {
        wxString s = text.Left(i);
        s += wxT("...");

        dc.GetTextExtent(s, &x, &y);
        if (x > max_size)
            break;

        last_good_length = i;
    }

    wxString ret = text.Left(last_good_length);
    ret += wxT("...");
    return ret;
}

wxAuiToolBarArt* wxAuiSolidToolBarArt::Clone()
{
    return new wxAuiSolidToolBarArt{};
}

void wxAuiSolidToolBarArt::DrawBackground(wxDC& dc, wxWindow* wnd, const wxRect& rect)
{
    wxUnusedVar(wnd);
    dc.GradientFillLinear(rect, wxColour{238, 238, 242}, wxColour{238, 238, 242});
}



wxAuiSolidTabArt::wxAuiSolidTabArt()
    : wxAuiGenericTabArt()
{
    m_normalFont    = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_selectedFont  = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_selectedFont.SetWeight(wxFONTWEIGHT_NORMAL);
    m_measuringFont = m_selectedFont;

    m_baseColour      = light_theme_main_color;
    m_borderPen       = wxPen{m_baseColour};
    m_baseColourBrush = wxBrush{m_baseColour};
}

wxAuiSolidTabArt* wxAuiSolidTabArt::Clone()
{
    return new wxAuiSolidTabArt{};
}

void wxAuiSolidTabArt::DrawBackground(wxDC& dc, wxWindow* wnd, const wxRect& rect)
{
    wxUnusedVar(wnd);
    dc.GradientFillLinear(rect, wxColour{238, 238, 242}, wxColour{238, 238, 242});
}

void wxAuiSolidTabArt::DrawBorder(wxDC& dc, wxWindow* wnd, const wxRect& rect)
{
}

void wxAuiSolidTabArt::DrawTab(wxDC& dc, wxWindow* wnd, const wxAuiNotebookPage& page, const wxRect& in_rect,
                int close_button_state, wxRect* out_tab_rect, wxRect* out_button_rect, int* x_extent)
{
    wxCoord normal_textx, normal_texty;

    // If the caption is empty, measure some temporary text
    wxString caption{page.caption};
    if (caption.empty()) caption = "Xj";

    dc.SetFont(m_normalFont);
    dc.GetTextExtent(caption, &normal_textx, &normal_texty);

    // Figure out the size of the tab
    const wxSize  tab_size   = GetTabSize(dc, wnd, page.caption, page.bitmap, page.active, close_button_state, x_extent);
    const wxCoord tab_height = m_tabCtrlHeight;
    const wxCoord tab_width  = tab_size.x;
    const wxCoord tab_x      = in_rect.x;
    const wxCoord tab_y      = in_rect.y + in_rect.height - tab_height;

    caption = page.caption;

    dc.SetFont(m_normalFont);

    const int drawn_tab_height = tab_height - 2;

    if (page.active)
    {
        // draw base background color
        wxRect r{tab_x, tab_y, tab_width, tab_height};
        dc.GradientFillLinear(r, wxColour{51, 153, 255}, wxColour{51, 153, 255});
    } else
    {
        wxRect r{tab_x, tab_y, tab_width, tab_height};
        dc.GradientFillLinear(r, wxColour{204, 206, 219}, wxColour{204, 206, 219});
    }

    const int text_offset = tab_x + 8;

    // Draw tab text
    const wxString draw_text = wxAuiChopText(dc, caption, tab_width - (text_offset-tab_x));
    if (page.active)
    {
        dc.SetTextForeground(wxColour{255, 255, 255});
        dc.DrawText(draw_text, text_offset, tab_y + 2 + (drawn_tab_height) / 2 - (normal_texty / 2) - 1);
    } else
    {
        dc.SetTextForeground(wxColour{0, 0, 0});
        dc.DrawText(draw_text, text_offset, tab_y + 2 + (drawn_tab_height) / 2 - (normal_texty / 2) - 1);
    }

    *out_tab_rect = wxRect{tab_x, tab_y, tab_width, tab_height};
}

int wxAuiSolidTabArt::GetBestTabCtrlSize(wxWindow* wnd, const wxAuiNotebookPageArray& pages, const wxSize& requiredBmp_size)
{
    return 22;
}



wxAuiMyNotebook::wxAuiMyNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxAuiNotebook(parent, id, pos, size, style)
{
    SetArtProvider(new wxAuiSolidTabArt{});
    m_mgr.SetArtProvider(new wxAuiSolidDockArt{});

    m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE, 0);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BORDER_COLOUR,     light_theme_main_color);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_SASH_COLOUR,       light_theme_main_color);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, light_theme_main_color);
}



wxAuiSolidDockArt::wxAuiSolidDockArt()
{
}

void wxAuiSolidDockArt::DrawBackground(wxDC& dc, wxWindow *window, int orientation, const wxRect& rect)
{
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush{light_theme_main_color});
    dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
}

void wxAuiSolidDockArt::DrawBorder(wxDC& dc, wxWindow *window, const wxRect& rect, wxAuiPaneInfo& pane)
{
}



void MainFrame::InitializeGuiStyle()
{
    m_toolbar_main->SetArtProvider(new wxAuiSolidToolBarArt{});
    m_toolbar_log->SetArtProvider(new wxAuiSolidToolBarArt{});
    //m_toolbar_viewport->SetArtProvider(new wxAuiSolidToolBarArt{});
    //m_tb_timeline->SetArtProvider(new wxAuiSolidToolBarArt{});

    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BORDER_COLOUR, light_theme_main_color);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_SASH_COLOUR, light_theme_main_color);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR, light_theme_main_color);
    m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE, 0);

    m_mgr.GetArtProvider()->SetFont(wxAUI_DOCKART_CAPTION_FONT, wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
    m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_CAPTION_SIZE, 19);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR, wxColour{0, 122, 204});
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR, wxColour{0, 122, 204});
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR, wxColour{255, 255, 255});
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR, light_theme_main_color);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR, light_theme_main_color);
    m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR, wxColour{20, 20, 20});

    m_mgr.Update();
}
