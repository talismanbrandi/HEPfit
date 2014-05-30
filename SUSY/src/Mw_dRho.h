/*
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef MW_DRHO_H
#define	MW_DRHO_H

#include <ThObservable.h>


#include "SUSY.h"

/**
 * @class Mw_dRho
 * @ingroup SUSY
 * @brief A class for the W-boson mass in the delta rho approximation. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details
 */
class Mw_dRho : public ThObservable {
public:

    Mw_dRho(const ThObsType& ObsType)
    : ThObservable(ObsType)
    {
    };

    double computeThValue()
    {
        return (static_cast<const SUSY*> (&SM))->Mw_dRho();
    };

private:

};

#endif	/* MW_DRHO_H */

