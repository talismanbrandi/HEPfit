/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef SIN2THETAEFF_H
#define	SIN2THETAEFF_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"
#include "EW_CHMN.h"


class sin2thetaEff : public ThObservable {
public:

    /**
     * @brief sin2thetaEff constructor
     * @param[in] EW_i an object of EW class
     * @param[in] bCHMN_i true if using EW_CHMN class 
     * @param[in] bBURGESS_i true if using the formula in hep-ph/9411257 by C.P. Burgess
     */
    sin2thetaEff(const EW& EW_i, const bool bCHMN_i=false, const bool bBURGESS_i=false) : ThObservable(EW_i), 
            myEW(EW_i), myEW_CHMN(EW_i.getSM()), bCHMN(bCHMN_i), bBURGESS(bBURGESS_i) {
        if (bCHMN && bBURGESS)
            throw std::runtime_error("bCHMN and bBURGESS cannot be set to true simultaneously in sin2thetaEff()");
    };

    /**
     * @return the effective weak mixing angle for a leptonic channel
     */
    double getThValue();

    
private:
    const EW& myEW;
    const EW_CHMN myEW_CHMN;
    const bool bCHMN, bBURGESS;
};

#endif	/* SIN2THETAEFF_H */

