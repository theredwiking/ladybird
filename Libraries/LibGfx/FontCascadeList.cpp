/*
 * Copyright (c) 2023, Aliaksandr Kalenik <kalenik.aliaksandr@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibGfx/FontCascadeList.h>

namespace Gfx {

void FontCascadeList::add(NonnullRefPtr<Font const> font)
{
    m_fonts.append({ move(font), {} });
}

void FontCascadeList::add(NonnullRefPtr<Font const> font, Vector<UnicodeRange> unicode_ranges)
{
    m_fonts.append({ move(font), move(unicode_ranges) });
}

void FontCascadeList::extend(FontCascadeList const& other)
{
    m_fonts.extend(other.m_fonts);
}

Gfx::Font const& FontCascadeList::font_for_code_point(u32 code_point) const
{
    for (auto const& entry : m_fonts) {
        if (entry.unicode_ranges.has_value()) {
            for (auto const& range : *entry.unicode_ranges) {
                if (range.contains(code_point) && entry.font->contains_glyph(code_point))
                    return entry.font;
            }
        } else if (entry.font->contains_glyph(code_point)) {
            return entry.font;
        }
    }
    return *m_last_resort_font;
}

bool FontCascadeList::equals(FontCascadeList const& other) const
{
    if (m_fonts.size() != other.m_fonts.size())
        return false;
    for (size_t i = 0; i < m_fonts.size(); ++i) {
        if (m_fonts[i].font != other.m_fonts[i].font)
            return false;
    }
    return true;
}

}
