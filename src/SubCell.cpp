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

#include "SubCell.h"

SubCell::SubCell() : MathCell()
{
  m_baseCell = NULL;
  m_indexCell = NULL;
}
SubCell::~SubCell()
{
  if (m_baseCell != NULL)
    delete m_baseCell;
  if (m_indexCell != NULL)
    delete m_indexCell;
  if (m_next != NULL)
    delete m_next;
}

MathCell* SubCell::Copy(bool all)
{
  SubCell* tmp = new SubCell;
  tmp->SetBase(m_baseCell->Copy(true));
  tmp->SetIndex(m_indexCell->Copy(true));
  if (all && m_nextToDraw!=NULL)
    tmp->AppendCell(m_nextToDraw->Copy(all));
  return tmp;
}

void SubCell::Destroy()
{
  if (m_baseCell != NULL)
    delete m_baseCell;
  if (m_indexCell != NULL)
    delete m_indexCell;
  m_baseCell = NULL;
  m_indexCell = NULL;
  m_next = NULL;
}

void SubCell::SetIndex(MathCell *index)
{
  if (index == NULL)
    return;
  if (m_indexCell != NULL)
    delete m_indexCell;
  m_indexCell = index;
}

void SubCell::SetBase(MathCell *base)
{
  if (base == NULL)
    return;
  if (m_baseCell != NULL)
    delete m_baseCell;
  m_baseCell = base;
}

void SubCell::RecalculateWidths(CellParser& parser, int fontsize, bool all)
{
  double scale = parser.GetScale();
  m_baseCell->RecalculateWidths(parser, fontsize, true);
  m_indexCell->RecalculateWidths(parser, MAX(8, fontsize-3), true);
  m_width = m_baseCell->GetFullWidth(scale) + m_indexCell->GetFullWidth(scale) -
            SCALE_PX(2, parser.GetScale());
  MathCell::RecalculateWidths(parser, fontsize, all);
}

void SubCell::RecalculateSize(CellParser& parser, int fontsize, bool all)
{
  m_baseCell->RecalculateSize(parser, fontsize, true);
  m_indexCell->RecalculateSize(parser, MAX(8, fontsize-3), true);
  m_height = m_baseCell->GetMaxHeight() + m_indexCell->GetMaxHeight() -
             SCALE_PX(13, parser.GetScale());
  m_center = m_baseCell->GetCenter();
  MathCell::RecalculateSize(parser, fontsize, all);
}

void SubCell::Draw(CellParser& parser, wxPoint point, int fontsize, bool all)
{
  if (DrawThisCell(parser, point)) {
    double scale = parser.GetScale();
    wxPoint bs, in;
  
    bs.x = point.x;
    bs.y = point.y;
    m_baseCell->Draw(parser, bs, fontsize, true);
  
    in.x = point.x + m_baseCell->GetFullWidth(scale) - SCALE_PX(2, scale);
    in.y = point.y + m_baseCell->GetMaxDrop() +
                   + m_indexCell->GetMaxCenter() - SCALE_PX(13, scale);
    m_indexCell->Draw(parser, in, MAX(8, fontsize-3), true);
  }
  
  MathCell::Draw(parser, point, fontsize, all);
}

wxString SubCell::ToString(bool all)
{
  wxString s;
  if (m_baseCell->IsCompound())
    s += wxT("(") + m_baseCell->ToString(true) + wxT(")");
  else
    s += m_baseCell->ToString(true);
  s += wxT("[") + m_indexCell->ToString(true) + wxT("]");
  s += MathCell::ToString(all);
  return s;
}

void SubCell::SelectInner(wxRect& rect, MathCell **first, MathCell **last)
{
  *first = NULL;
  *last = NULL;
  if (m_indexCell->ContainsRect(rect))
    m_indexCell->SelectRect(rect, first, last);
  else if (m_baseCell->ContainsRect(rect))
    m_baseCell->SelectRect(rect, first, last);
  if (*first == NULL || *last == NULL) {
    *first = this;
    *last = this;
  }
}