/* 
 * File:   GammaW.h
 * Author: mishima
 */

#ifndef GAMMAW_H
#define	GAMMAW_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"


class GammaW : public ThObservable {
public:
    
    /**
     * @brief GammaW constructor
     * @param[in] EW_i an object of EW class
     * @param[in] type EWDEFAULT(default), EWCHMN, EWBURGESS or EWABC
     */
    GammaW(const EW& EW_i, const EW::EWTYPE type=EW::EWDEFAULT) : ThObservable(EW_i), 
            myEW(EW_i), myEWTYPE(type) {
    };

    /**
     * @return the total width of the W boson 
     */
    double getThValue();

    
private:
    const EW& myEW;
    const EW::EWTYPE myEWTYPE;
};

#endif	/* GAMMAW_H */

