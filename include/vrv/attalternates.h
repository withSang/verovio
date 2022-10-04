/////////////////////////////////////////////////////////////////////////////
// Name:        attalternates.h
// Author:      Laurent Pugin
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_ATT_ALTERNATES_H__
#define __VRV_ATT_ALTERNATES_H__

#include <string>

//----------------------------------------------------------------------------

#include "atttypes.h"
#include "vrvdef.h"

namespace vrv {

//----------------------------------------------------------------------------
// Alternate data types not generated by LibMEI
//----------------------------------------------------------------------------

/**
 * MEI data.FONTSIZE
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum FontSizeType { FONTSIZE_NONE = 0, FONTSIZE_fontSizeNumeric, FONTSIZE_term, FONTSIZE_percent };

class data_FONTSIZE {
public:
    data_FONTSIZE() { Reset(FONTSIZE_NONE); }
    virtual ~data_FONTSIZE() {}

    void Reset(FontSizeType type)
    {
        m_type = type;
        m_fontSizeNumeric = VRV_UNSET;
        m_term = FONTSIZETERM_NONE;
        m_percent = 0;
    }

    FontSizeType GetType() const { return m_type; }

    data_FONTSIZENUMERIC GetFontSizeNumeric() const { return m_fontSizeNumeric; }
    void SetFontSizeNumeric(data_FONTSIZENUMERIC value)
    {
        Reset(FONTSIZE_fontSizeNumeric);
        m_fontSizeNumeric = value;
    }

    data_FONTSIZETERM GetTerm() const { return m_term; }
    void SetTerm(data_FONTSIZETERM value)
    {
        Reset(FONTSIZE_term);
        m_term = value;
    }

    data_PERCENT GetPercent() const { return m_percent; }
    void SetPercent(data_PERCENT value)
    {
        Reset(FONTSIZE_percent);
        m_percent = value;
    }

    int GetPercentForTerm() const
    {
        switch (m_term) {
            case (FONTSIZETERM_xx_large): return 200; break;
            case (FONTSIZETERM_x_large): return 150; break;
            case (FONTSIZETERM_large): return 110; break;
            case (FONTSIZETERM_larger): return 110; break;
            case (FONTSIZETERM_small): return 80; break;
            case (FONTSIZETERM_smaller): return 80; break;
            case (FONTSIZETERM_x_small): return 60; break;
            case (FONTSIZETERM_xx_small): return 50; break;
            default: return 100; break;
        }
    }

    bool HasValue() const
    {
        if (m_fontSizeNumeric != VRV_UNSET) return true;
        if (m_term != FONTSIZETERM_NONE) return true;
        if (m_percent != 0) return true;
        return false;
    }

    // comparison
    bool operator==(const data_FONTSIZE &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_fontSizeNumeric != val.GetFontSizeNumeric()) return false;
        if (m_term != val.GetTerm()) return false;
        if (m_percent != val.GetPercent()) return false;
        return true;
    }
    bool operator!=(const data_FONTSIZE &val) const { return !(*this == val); }

protected:
    FontSizeType m_type;
    data_FONTSIZENUMERIC m_fontSizeNumeric;
    data_FONTSIZETERM m_term;
    data_PERCENT m_percent;
};

/**
 * MEI data.LINEWIDTH
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum LinewidthType { LINEWIDTHTYPE_NONE = 0, LINEWIDTHTYPE_lineWidthTerm, LINEWIDTHTYPE_measurementUnsigned };

class data_LINEWIDTH {
public:
    data_LINEWIDTH() { Reset(LINEWIDTHTYPE_NONE); }
    virtual ~data_LINEWIDTH() {}

    void Reset(LinewidthType type)
    {
        m_type = type;
        m_lineWidthTerm = LINEWIDTHTERM_NONE;
        m_measurementUnsigned = VRV_UNSET;
    }

    LinewidthType GetType() const { return m_type; }

    data_LINEWIDTHTERM GetLineWithTerm() const { return m_lineWidthTerm; }
    void SetLineWidthTerm(data_LINEWIDTHTERM value)
    {
        Reset(LINEWIDTHTYPE_lineWidthTerm);
        m_lineWidthTerm = value;
    }

    data_MEASUREMENTUNSIGNED GetMeasurementUnsigned() const { return m_measurementUnsigned; }
    void SetMeasurementUnsigned(data_MEASUREMENTUNSIGNED value)
    {
        Reset(LINEWIDTHTYPE_measurementUnsigned);
        m_measurementUnsigned = value;
    }

    bool HasValue() const
    {
        if (m_lineWidthTerm != LINEWIDTHTERM_NONE) return true;
        if (m_measurementUnsigned != VRV_UNSET) return true;
        return false;
    }

    // comparison
    bool operator==(const data_LINEWIDTH &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_lineWidthTerm != val.GetLineWithTerm()) return false;
        if (m_measurementUnsigned != val.GetMeasurementUnsigned()) return false;
        return true;
    }
    bool operator!=(const data_LINEWIDTH &val) const { return !(*this == val); }

protected:
    LinewidthType m_type;
    data_LINEWIDTHTERM m_lineWidthTerm;
    data_MEASUREMENTUNSIGNED m_measurementUnsigned;
};

/**
 * MEI data.MIDIVALUE_NAME
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum MidivalueNameType { MIDIVALUENAMETYPE_NONE = 0, MIDIVALUENAMETYPE_midivalue, MIDIVALUENAMETYPE_mcname };

class data_MIDIVALUE_NAME {
public:
    data_MIDIVALUE_NAME() { Reset(MIDIVALUENAMETYPE_NONE); }
    virtual ~data_MIDIVALUE_NAME() {}

    void Reset(MidivalueNameType type)
    {
        m_type = type;
        m_midivalue = -1;
        m_ncname = "";
    }

    MidivalueNameType GetType() const { return m_type; }

    data_MIDIVALUE GetMidivalue() const { return m_midivalue; }
    void SetMidivalue(data_MIDIVALUE value)
    {
        Reset(MIDIVALUENAMETYPE_midivalue);
        m_midivalue = value;
    }

    data_NCNAME GetNcname() const { return m_ncname; }
    void SetNcname(data_NCNAME value)
    {
        Reset(MIDIVALUENAMETYPE_mcname);
        m_ncname = value;
    }

    bool HasValue() const
    {
        if (m_midivalue != -1) return true;
        if (m_ncname != "") return true;
        return false;
    }

    // comparison
    bool operator==(const data_MIDIVALUE_NAME &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_midivalue != val.GetMidivalue()) return false;
        if (m_ncname != val.GetNcname()) return false;
        return true;
    }
    bool operator!=(const data_MIDIVALUE_NAME &val) const { return !(*this == val); }

protected:
    MidivalueNameType m_type;
    data_MIDIVALUE m_midivalue;
    data_NCNAME m_ncname;
};

/**
 * MEI data.MIDIVALUE_PAN
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum MidivaluePanType { MIDIVALUEPANTYPE_NONE = 0, MIDIVALUEPANTYPE_midivalue, MIDIVALUEPANTYPE_percentLimitedSigned };

class data_MIDIVALUE_PAN {
public:
    data_MIDIVALUE_PAN() { Reset(MIDIVALUEPANTYPE_NONE); }
    virtual ~data_MIDIVALUE_PAN() {}

    void Reset(MidivaluePanType type)
    {
        m_type = type;
        m_midivalue = -1;
        m_percentLimitedSigned = VRV_UNSET;
    }

    MidivaluePanType GetType() const { return m_type; }

    data_MIDIVALUE GetMidivalue() const { return m_midivalue; }
    void SetMidivalue(data_MIDIVALUE value)
    {
        Reset(MIDIVALUEPANTYPE_midivalue);
        m_midivalue = value;
    }

    data_PERCENT_LIMITED_SIGNED GetPercentLimitedSigned() const { return m_percentLimitedSigned; }
    void SetPercentLimitedSigned(data_PERCENT_LIMITED_SIGNED value)
    {
        Reset(MIDIVALUEPANTYPE_percentLimitedSigned);
        m_percentLimitedSigned = value;
    }

    bool HasValue() const
    {
        if (m_midivalue != -1) return true;
        if (m_percentLimitedSigned != VRV_UNSET) return true;
        return false;
    }

    // comparison
    bool operator==(const data_MIDIVALUE_PAN &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_midivalue != val.GetMidivalue()) return false;
        if (m_percentLimitedSigned != val.GetPercentLimitedSigned()) return false;
        return true;
    }
    bool operator!=(const data_MIDIVALUE_PAN &val) const { return !(*this == val); }

protected:
    MidivaluePanType m_type;
    data_MIDIVALUE m_midivalue;
    data_PERCENT_LIMITED_SIGNED m_percentLimitedSigned;
};

//----------------------------------------------------------------------------
// Alternate data types unsing other alternate data types (above)
//----------------------------------------------------------------------------

/**
 * MEI data.PLACEMENT
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum PlacementType { PLACEMENT_NONE = 0, PLACEMENT_staffRel, PLACEMENT_nonStaffPlace, PLACEMENT_nmtoken };

class data_PLACEMENT {
public:
    data_PLACEMENT() { Reset(PLACEMENT_NONE); }
    virtual ~data_PLACEMENT() {}

    void Reset(PlacementType type)
    {
        m_type = type;
        m_staffRel = data_STAFFREL();
        m_nonStaffPlace = NONSTAFFPLACE_NONE;
        m_nmtoken = "";
    }

    PlacementType GetType() const { return m_type; }

    data_STAFFREL GetStaffRel() const { return m_staffRel; }
    void SetStaffRel(data_STAFFREL value)
    {
        Reset(PLACEMENT_staffRel);
        m_staffRel = value;
    }
    data_STAFFREL *GetStaffRelAtlernate() { return &m_staffRel; }

    data_NONSTAFFPLACE GetNonStaffPlace() const { return m_nonStaffPlace; }
    void SetNonStaffPlace(data_NONSTAFFPLACE value)
    {
        Reset(PLACEMENT_nonStaffPlace);
        m_nonStaffPlace = value;
    }

    std::string GetNMToken() const { return m_nmtoken; }
    void SetNMToken(std::string value)
    {
        Reset(PLACEMENT_nmtoken);
        m_nmtoken = value;
    }

    bool HasValue() const
    {
        if (m_staffRel != STAFFREL_NONE) return true;
        if (m_nonStaffPlace != NONSTAFFPLACE_NONE) return true;
        if (m_nmtoken != "") return true;
        return false;
    }

    // comparison
    bool operator==(const data_PLACEMENT &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_staffRel != val.GetStaffRel()) return false;
        if (m_nonStaffPlace != val.GetNonStaffPlace()) return false;
        if (m_nmtoken != val.GetNMToken()) return false;
        return true;
    }
    bool operator!=(const data_PLACEMENT &val) const { return !(*this == val); }

protected:
    PlacementType m_type;
    data_STAFFREL m_staffRel;
    data_NONSTAFFPLACE m_nonStaffPlace;
    std::string m_nmtoken;
};

} // namespace vrv

#endif
