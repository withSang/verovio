/////////////////////////////////////////////////////////////////////////////
// Name:        staffgrp.cpp
// Author:      Laurent Pugin
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "staffgrp.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "editorial.h"
#include "functorparams.h"
#include "grpsym.h"
#include "instrdef.h"
#include "label.h"
#include "labelabbr.h"
#include "vrv.h"

namespace vrv {

//----------------------------------------------------------------------------
// StaffGrp
//----------------------------------------------------------------------------

static const ClassRegistrar<StaffGrp> s_factory("staffGrp", STAFFGRP);

StaffGrp::StaffGrp()
    : Object(STAFFGRP, "staffgrp-")
    , ObjectListInterface()
    , AttBasic()
    , AttLabelled()
    , AttNNumberLike()
    , AttStaffGroupingSym()
    , AttStaffGrpVis()
    , AttTyped()
{
    this->RegisterAttClass(ATT_BASIC);
    this->RegisterAttClass(ATT_LABELLED);
    this->RegisterAttClass(ATT_NNUMBERLIKE);
    this->RegisterAttClass(ATT_STAFFGROUPINGSYM);
    this->RegisterAttClass(ATT_STAFFGRPVIS);
    this->RegisterAttClass(ATT_TYPED);

    this->Reset();
}

StaffGrp::~StaffGrp() {}

void StaffGrp::Reset()
{
    Object::Reset();
    this->ResetBasic();
    this->ResetLabelled();
    this->ResetNNumberLike();
    this->ResetStaffGroupingSym();
    this->ResetStaffGrpVis();
    this->ResetTyped();

    m_drawingVisibility = OPTIMIZATION_NONE;
    m_groupSymbol = NULL;
}

bool StaffGrp::IsSupportedChild(Object *child)
{
    if (child->Is(GRPSYM)) {
        assert(dynamic_cast<GrpSym *>(child));
    }
    else if (child->Is(INSTRDEF)) {
        assert(dynamic_cast<InstrDef *>(child));
    }
    else if (child->Is(LABEL)) {
        assert(dynamic_cast<Label *>(child));
    }
    else if (child->Is(LABELABBR)) {
        assert(dynamic_cast<LabelAbbr *>(child));
    }
    else if (child->Is(STAFFDEF)) {
        assert(dynamic_cast<StaffDef *>(child));
    }
    else if (child->Is(STAFFGRP)) {
        assert(dynamic_cast<StaffGrp *>(child));
    }
    else if (child->IsEditorialElement()) {
        assert(dynamic_cast<EditorialElement *>(child));
    }
    else {
        return false;
    }
    return true;
}

void StaffGrp::FilterList(ArrayOfObjects *childList)
{
    // We want to keep only staffDef
    ArrayOfObjects::iterator iter = childList->begin();

    while (iter != childList->end()) {
        if (!(*iter)->Is(STAFFDEF)) {
            iter = childList->erase(iter);
        }
        else {
            ++iter;
        }
    }
}

int StaffGrp::GetMaxStaffSize()
{
    this->ResetList(this);
    const ArrayOfObjects *childList = this->GetList(this);

    if (childList->empty()) return 100;

    int max = 0;

    StaffDef *staffDef = NULL;
    for (auto &child : *childList) {
        staffDef = vrv_cast<StaffDef *>(child);
        assert(staffDef);
        if (staffDef->HasScale() && staffDef->GetScale() >= max) {
            max = staffDef->GetScale();
        }
        else {
            max = 100;
        }
    }

    return max;
}

std::pair<StaffDef *, StaffDef *> StaffGrp::GetFirstLastStaffDef()
{
    const ArrayOfObjects *staffDefs = this->GetList(this);
    if (staffDefs->empty()) {
        return { NULL, NULL };
    }

    StaffDef *firstDef = NULL;
    ArrayOfObjects::const_iterator iter;
    for (iter = staffDefs->begin(); iter != staffDefs->end(); ++iter) {
        StaffDef *staffDef = vrv_cast<StaffDef *>(*iter);
        assert(staffDef);
        if (staffDef->GetDrawingVisibility() != OPTIMIZATION_HIDDEN) {
            firstDef = staffDef;
            break;
        }
    }

    StaffDef *lastDef = NULL;
    ArrayOfObjects::const_reverse_iterator riter;
    for (riter = staffDefs->rbegin(); riter != staffDefs->rend(); ++riter) {
        StaffDef *staffDef = vrv_cast<StaffDef *>(*riter);
        assert(staffDef);
        if (staffDef->GetDrawingVisibility() != OPTIMIZATION_HIDDEN) {
            lastDef = staffDef;
            break;
        }
    }

    return { firstDef, lastDef };
}

void StaffGrp::SetGroupSymbol(GrpSym *grpSym)
{
    if (grpSym) {
        m_groupSymbol = grpSym;
    }
}

bool StaffGrp::HasLabelInfo() const
{
    return (this->FindDescendantByType(LABEL, 1));
}

bool StaffGrp::HasLabelAbbrInfo() const
{
    return (this->FindDescendantByType(LABELABBR, 1));
}

Label *StaffGrp::GetLabel()
{
    return const_cast<Label *>(std::as_const(*this).GetLabel());
}

const Label *StaffGrp::GetLabel() const
{
    // Always check if HasLabelInfo() is true before asking for it
    const Label *label = vrv_cast<const Label *>(this->FindDescendantByType(LABEL, 1));
    assert(label);
    return label;
}

Label *StaffGrp::GetLabelCopy() const
{
    // Always check if HasClefInfo() is true before asking for a clone
    Label *clone = dynamic_cast<Label *>(this->GetLabel()->Clone());
    clone->CloneReset();
    assert(clone);
    return clone;
}

LabelAbbr *StaffGrp::GetLabelAbbr()
{
    return const_cast<LabelAbbr *>(std::as_const(*this).GetLabelAbbr());
}

const LabelAbbr *StaffGrp::GetLabelAbbr() const
{
    // Always check if HasLabelAbbrInfo() is true before asking for it
    const LabelAbbr *labelAbbr = vrv_cast<const LabelAbbr *>(this->FindDescendantByType(LABELABBR, 1));
    assert(labelAbbr);
    return labelAbbr;
}

LabelAbbr *StaffGrp::GetLabelAbbrCopy() const
{
    // Always check if HasClefInfo() is true before asking for a clone
    LabelAbbr *clone = dynamic_cast<LabelAbbr *>(this->GetLabelAbbr()->Clone());
    clone->CloneReset();
    assert(clone);
    return clone;
}

//----------------------------------------------------------------------------
// StaffGrp functor methods
//----------------------------------------------------------------------------

int StaffGrp::ScoreDefOptimizeEnd(FunctorParams *)
{
    this->SetDrawingVisibility(OPTIMIZATION_HIDDEN);

    for (auto &child : *this->GetChildren()) {
        if (child->Is(STAFFDEF)) {
            StaffDef *staffDef = vrv_cast<StaffDef *>(child);
            assert(staffDef);
            if (staffDef->GetDrawingVisibility() != OPTIMIZATION_HIDDEN) {
                this->SetDrawingVisibility(OPTIMIZATION_SHOW);
                break;
            }
        }
        else if (child->Is(STAFFGRP)) {
            StaffGrp *staffGrp = vrv_cast<StaffGrp *>(child);
            assert(staffGrp);
            if (staffGrp->GetDrawingVisibility() != OPTIMIZATION_HIDDEN) {
                this->SetDrawingVisibility(OPTIMIZATION_SHOW);
                break;
            }
        }
    }

    if ((this->GetSymbol() == staffGroupingSym_SYMBOL_brace) && (this->GetDrawingVisibility() != OPTIMIZATION_HIDDEN)) {
        for (auto &child : *this->GetChildren()) {
            if (child->Is(STAFFDEF)) {
                StaffDef *staffDef = vrv_cast<StaffDef *>(child);
                assert(staffDef);
                staffDef->SetDrawingVisibility(OPTIMIZATION_SHOW);
            }
        }
    }

    return FUNCTOR_CONTINUE;
}

} // namespace vrv
