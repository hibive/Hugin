// -*- c-basic-offset: 4 -*-

/** @file CalculateOverlap.h
 *
 *  @brief definitions of classes to calculate overlap between different images
 *
 *  @author Thomas Modes
 *
 *
 *  $Id$
 *
 */

/*  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this software; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef _ALGO_CALCULATE_OVERLAP_H
#define _ALGO_CALCULATE_OVERLAP_H

#include <hugin_shared.h>
#include <panodata/PanoramaData.h>
#include <panodata/Panorama.h>
#include <panotools/PanoToolsInterface.h>

namespace HuginBase 
{

//using namespace hugin_utils;

class IMPEX CalculateImageOverlap
{
public:
    CalculateImageOverlap(const PanoramaData * pano):m_pano(pano)
    {
        m_nrImg=pano->getNrOfImages();
        if(m_nrImg>0)
        {
            m_overlap.resize(m_nrImg);
            PanoramaOptions opts=pano->getOptions();
            m_transform.resize(m_nrImg);
            m_invTransform.resize(m_nrImg);
            for(unsigned int i=0;i<m_nrImg;i++)
            {
                m_overlap[i].resize(m_nrImg,0);
                m_transform[i]=new PTools::Transform;
                m_transform[i]->createTransform(*pano,i,opts);
                m_invTransform[i]=new PTools::Transform;
                m_invTransform[i]->createInvTransform(*pano,i,opts);
            };
        };
    };
    virtual ~CalculateImageOverlap();
    void calculate(unsigned int steps);
    double getOverlap(unsigned int i, unsigned int j);

private:
    std::vector<std::vector<double> > m_overlap;
    std::vector<PTools::Transform*> m_transform;
    std::vector<PTools::Transform*> m_invTransform;
    unsigned int m_nrImg;
    const PanoramaData* m_pano;
};

} //namespace
#endif // PANOIMAGE_H