/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef SYNOPSISDEFINES_H
#define SYNOPSISDEFINES_H

#define EXPORT __attribute__ ((visibility("default")))

#define SYNOPSIS_CONTENT 1
#define SYNOPSIS_NOTE 2
#define SYNOPSIS_BOOKMARK 4
#define SYNOPSIS_PEN 16
#define SYNOPSIS_MARKER 32
#define SYNOPSIS_COMMENT 64
#define SYNOPSIS_SNAPSHOT 128

#define title_height 70
#define FreeMargin (PBSynopsisResource::GetImgPlus()->width)
#define BorderMargin 10
#define TopMargin 10

#define StringPoints ".........................................................................................................................................................................................................................................."

#define UPFLAGDEF (keyflag ? tmp->GetAbove() : tmp->GetBelow())
#define DOWNFLAGDEF (keyflag ? tmp->GetBelow() : tmp->GetAbove())

#define SelectStepDef 10
//#define FromWordDef (cnotepage == 1 ? from : FromWord)

#define SYNOPSIS_ALIGN ALIGN_LEFT | ALIGN_FIT | VALIGN_MIDDLE | DOTS | (IsBookRTL() ? RTLAUTO : 0)

#define SynopsisMenuItemHeight 30
#define SynopsisMenuWidth 320

#define MINNOTETEXTLENGTH 20

#define MINSNAPSHOTSIZE 30

#endif
