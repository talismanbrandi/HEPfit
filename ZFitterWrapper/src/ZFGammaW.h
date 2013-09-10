/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef ZFGAMMAW_H
#define	ZFGAMMAW_H

#include <ThObservable.h>
#include "ZFitterWrapper.h"


class ZFGammaW : public ThObservable {
public:

    /**
     * @brief ZFGammaW constructor
     * @param[in] ZF_i an object of ZFitter class
     */
    ZFGammaW(const ZFitterWrapper& ZF_i) : ThObservable(ZF_i), myZF(ZF_i) {};

    /**
     * @return the total width of the W boson
     */
    double getThValue();

    
private:
    const ZFitterWrapper& myZF;
};


#endif	/* ZFGAMMAW_H */
