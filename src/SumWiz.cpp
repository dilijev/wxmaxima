/*
 *  Copyright (C) 2004-2005 Andrej Vodopivec <andrejv@users.sourceforge.net>
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



#include "SumWiz.h"

SumWiz::SumWiz(wxWindow* parent, int id, const wxString& title,
               const wxPoint& pos, const wxSize& size, long style):
  wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
  label_1 = new wxStaticText(this, -1, _("Sum"));
  label_2 = new wxStaticText(this, -1, _("Sum of:"));
  text_ctrl_1 = new BTextCtrl(this, -1, wxT(""), wxDefaultPosition,
                              wxSize(180,-1));
  label_3 = new wxStaticText(this, -1, _("by variable:"));
  text_ctrl_2 = new BTextCtrl(this, -1, wxT("k"));
  label_4 = new wxStaticText(this, -1, _("from:"));
  text_ctrl_3 = new BTextCtrl(this, -1, wxT("1"));
  label_5 = new wxStaticText(this, -1, _("to:"));
  text_ctrl_4 = new BTextCtrl(this, -1, wxT("inf"));
  checkbox_1 = new wxCheckBox(this, -1, _("Simplify"));
  checkbox_2 = new wxCheckBox(this, -1, _("Nusum"));
  static_line_1 = new wxStaticLine(this, -1);
  button_1 = new wxButton(this, wxOK, _("OK"));
  button_2 = new wxButton(this, wxCANCEL, _("Cancel"));

  button_1->SetDefault();
  ok = false;
  set_properties();
  do_layout();
}


void SumWiz::set_properties()
{
  SetTitle(_("Sum"));
  label_1->SetFont(wxFont(20, wxROMAN, wxITALIC, wxNORMAL, 0, wxT("")));
  checkbox_1->SetValue(true);
}


void SumWiz::do_layout()
{
  wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(4, 1, 3, 3);
  wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
  wxFlexGridSizer* grid_sizer_2 = new wxFlexGridSizer(6, 2, 3, 3);
  grid_sizer_1->Add(label_1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2);
  grid_sizer_2->Add(label_2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
  grid_sizer_2->Add(text_ctrl_1, 0, wxALL, 2);
  grid_sizer_2->Add(label_3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
  grid_sizer_2->Add(text_ctrl_2, 0, wxALL, 2);
  grid_sizer_2->Add(label_4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
  grid_sizer_2->Add(text_ctrl_3, 0, wxALL, 2);
  grid_sizer_2->Add(label_5, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
  grid_sizer_2->Add(text_ctrl_4, 0, wxALL, 2);
  sizer_2->Add(checkbox_1, 0, wxALL, 2);
  sizer_2->Add(checkbox_2, 0, wxALL, 2);
  grid_sizer_2->Add(20, 20, 0, 0);
  grid_sizer_2->Add(sizer_2, 1, wxALIGN_LEFT, 0);
  grid_sizer_1->Add(grid_sizer_2, 1, wxEXPAND, 0);
  grid_sizer_1->Add(static_line_1, 0, wxEXPAND, 0);
  sizer_1->Add(button_1, 0, wxALL, 2);
  sizer_1->Add(button_2, 0, wxALL, 2);
  grid_sizer_1->Add(sizer_1, 1, wxALIGN_RIGHT, 0);
  SetAutoLayout(true);
  SetSizer(grid_sizer_1);
  grid_sizer_1->Fit(this);
  grid_sizer_1->SetSizeHints(this);
  Layout();
}

wxString SumWiz::getValue()
{
  wxString s;
  if (checkbox_2->IsChecked())
    s = wxT("nusum(");
  else
    s = wxT("sum(");
  s += text_ctrl_1->GetValue();
  s += wxT(", ");
  s += text_ctrl_2->GetValue();
  s += wxT(", ");
  s += text_ctrl_3->GetValue();
  s += wxT(", ");
  s += text_ctrl_4->GetValue();
  s += wxT(")");
  if (checkbox_1->IsChecked() && !checkbox_2->IsChecked())
    s += wxT(", simpsum;");
  else
    s += wxT(";");

  return s;
}

void SumWiz::onButton(wxCommandEvent& event)
{
  if (event.GetId()==wxOK)
    ok = true;
  Close();
}

BEGIN_EVENT_TABLE(SumWiz, wxDialog)
  EVT_BUTTON(wxOK, SumWiz::onButton)
  EVT_BUTTON(wxCANCEL, SumWiz::onButton)
END_EVENT_TABLE()