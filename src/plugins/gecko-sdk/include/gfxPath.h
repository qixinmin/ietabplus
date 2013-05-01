/* -*- Mode: C++; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is IBM Corporation code.
 *
 * The Initial Developer of the Original Code is IBM Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef GFX_PATH_H
#define GFX_PATH_H

#include "gfxTypes.h"

class gfxContext;
struct gfxPoint;
typedef struct cairo_path cairo_path_t;

/**
 * Class representing a path. Can be created by copying the current path
 * of a gfxContext.
 */
class THEBES_API gfxPath {
    THEBES_INLINE_DECL_REFCOUNTING(gfxPath)

    friend class gfxContext;

protected:
    gfxPath(cairo_path_t* aPath);

public:
    virtual ~gfxPath();

protected:
    cairo_path_t* mPath;
};

/**
 * Specialization of a path that only contains linear pieces. Can be created
 * from the existing path of a gfxContext.
 */
class THEBES_API gfxFlattenedPath : public gfxPath {
    friend class gfxContext;

protected:
    gfxFlattenedPath(cairo_path_t* aPath);

public:
    virtual ~gfxFlattenedPath();

    /**
     * Returns calculated total length of path
     */
    gfxFloat GetLength();

    /**
     * Returns a point a certain distance along the path.  Return is
     * first or last point of the path if the requested length offset
     * is outside the range for the path.
     * @param aOffset offset inpath parameter space (x=length, y=normal offset)
     * @param aAngle optional - output tangent
     */
    gfxPoint FindPoint(gfxPoint aOffset,
                       gfxFloat* aAngle = nsnull);
};

#endif
