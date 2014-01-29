/* 
 * Copyright (C) 2012-2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef DMBS_H
#define	DMBS_H

#include <ThObservable.h>
#include "Flavour.h"
#include "AmpDB2.h"

/**
 * @class DMK
 * @ingroup Flavour
 * @brief A class for @f$\Delta M_{B_s}@f$, the difference in mass
 * of between the heavy and light mass eigenstates of the neutral
 * @f$B_d@f$ system.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the theoretical value of
 * @f$\Delta M_{B_s}@f$. The short distance contributions to this
 * parameter is calculable both in the SM and in NP models. In the SM 
 * the short distance contribution is dominated by the top loop in the
 * box diagram.
 */
class DmBs : public ThObservable, AmpDB2 {
public:
    
    /**
     * constructor
     * @param Flavour
     */
    
    DmBs(Flavour& Flavour) : ThObservable(Flavour), AmpDB2(Flavour) {};
    
    /**
     *
     * @return theoretical value of @f$\Delta M_{B_s}@f$
     */
    
    double computeThValue();
};

#endif	/* DMBS_H */

