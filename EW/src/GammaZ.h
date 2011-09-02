/* 
 * File:   GammaZ.h
 * Author: mishima
 */

#ifndef GAMMAZ_H
#define	GAMMAZ_H

#include <ThObservable.h>
#include "EW.h"

class GammaZ : public ThObservable {
public:

    /**
     * @brief GammaZ constructor
     * @param[in] EW_i an object of EW class
     */
    GammaZ(const EW& EW_i);

    /**
     * @return the total width of the Z boson
     */
    double getThValue();

private:

};

#endif	/* GAMMAZ_H */

