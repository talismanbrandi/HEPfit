/*
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef PARAMOBS_H
#define	PARAMOBS_H

#include "ThObservable.h"

class ParamObs : public ThObservable {
public:
    ParamObs(const StandardModel& SM, const std::string name);

    double computeThValue();
    
private:
    const double& param;
};

#endif	/* PARAMOBS_H */

