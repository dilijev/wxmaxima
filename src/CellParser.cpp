/*
 *  Copyright (C) 2005 Andrej Vodopivec <andrejv@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "CellParser.h"

#include <wx/config.h>

CellParser::CellParser(wxDC& dc) : m_dc(dc)
{
  m_scale = 1.0;
  m_top = -1;
  m_bottom = -1;
  ReadStyle();
}

CellParser::CellParser(wxDC& dc, double scale) : m_dc(dc)
{
  m_scale = scale;
  m_top = -1;
  m_bottom = -1;
  ReadStyle();
}

void CellParser::ReadStyle()
{
  wxConfigBase* config = wxConfig::Get();
  config->Read(wxT("Style/fontname"), &m_fontName);
  
  m_styles[0].color = wxT("black");
  m_styles[0].bold = false;
  m_styles[0].italic = false;
  m_styles[0].underlined = false;
  // Normal text
  config->Read(wxT("Style/NormalText/color"),
               &m_styles[0].color);
  config->Read(wxT("Style/NormalText/bold"),
               &m_styles[0].bold);
  config->Read(wxT("Style/NormalText/italic"),
               &m_styles[0].italic);
  config->Read(wxT("Style/NormalText/underlined"),
               &m_styles[0].underlined);
  
  m_styles[1].bold = false;
  m_styles[1].italic = true;
  m_styles[1].underlined = true;
  // Normal text
  config->Read(wxT("Style/HiddenText/color"),
               &m_styles[1].color);
  config->Read(wxT("Style/HiddenText/bold"),
               &m_styles[1].bold);
  config->Read(wxT("Style/HiddenText/italic"),
               &m_styles[1].italic);
  config->Read(wxT("Style/HiddenText/underlined"),
               &m_styles[1].underlined);
  
  m_styles[2].color = wxT("red");
  m_styles[2].bold = false;
  m_styles[2].italic = false;
  m_styles[2].underlined = false;
  // Main prompt
  config->Read(wxT("Style/MainPrompt/color"),
               &m_styles[2].color);
  config->Read(wxT("Style/MainPrompt/bold"),
               &m_styles[2].bold);
  config->Read(wxT("Style/MainPrompt/italic"),
               &m_styles[2].italic);
  config->Read(wxT("Style/MainPrompt/underlined"),
               &m_styles[2].underlined);

  m_styles[3].color = wxT("red");
  m_styles[3].bold = false;
  m_styles[3].italic = true;
  m_styles[3].underlined = false;
  // Other prompt
  config->Read(wxT("Style/OtherPrompt/color"),
               &m_styles[3].color);
  config->Read(wxT("Style/OtherPrompt/bold"),
               &m_styles[3].bold);
  config->Read(wxT("Style/OtherPrompt/italic"),
               &m_styles[3].italic);
  config->Read(wxT("Style/OtherPrompt/underlined"),
               &m_styles[3].underlined);
  
  m_styles[4].color = wxT("brown");
  m_styles[4].bold = false;
  m_styles[4].italic = false;
  m_styles[4].underlined = false;
  // Labels
  config->Read(wxT("Style/Label/color"),
               &m_styles[4].color);
  config->Read(wxT("Style/Label/bold"),
               &m_styles[4].bold);
  config->Read(wxT("Style/Label/italic"),
               &m_styles[4].italic);
  config->Read(wxT("Style/Label/underlined"),
               &m_styles[4].underlined);
  
  m_styles[5].color = wxT("black");
  m_styles[5].bold = false;
  m_styles[5].italic = false;
  m_styles[5].underlined = false;
  // Special
  config->Read(wxT("Style/Special/color"),
               &m_styles[5].color);
  config->Read(wxT("Style/Special/bold"),
               &m_styles[5].bold);
  config->Read(wxT("Style/Special/italic"),
               &m_styles[5].italic);
  config->Read(wxT("Style/Special/underlined"),
               &m_styles[5].underlined);
  
  m_styles[6].color = wxT("blue");
  m_styles[6].bold = false;
  m_styles[6].italic = false;
  m_styles[6].underlined = false;
  // Input
  config->Read(wxT("Style/Input/color"),
               &m_styles[6].color);
  config->Read(wxT("Style/Input/bold"),
               &m_styles[6].bold);
  config->Read(wxT("Style/Input/italic"),
               &m_styles[6].italic);
  config->Read(wxT("Style/Input/underlined"),
               &m_styles[6].underlined);
               
  m_dc.SetPen(*(wxThePenList->FindOrCreatePen(m_styles[0].color, 1, wxSOLID)));
}

CellParser::~CellParser()
{
}

int CellParser::IsBold(int st)
{
  if (m_styles[st].bold)
    return wxBOLD;
  return wxNORMAL;
}

int CellParser::IsItalic(int st)
{
  if (m_styles[st].italic)
    return wxSLANT;
  return wxNORMAL;
}

int CellParser::IsUnderlined(int st)
{
  if (m_styles[st].underlined)
    return 1;
  return 0;
}