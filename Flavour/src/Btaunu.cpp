/*
 * Copyright (C) 2015 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "Btaunu.h"

Btaunu::Btaunu(const StandardModel& SM_i)
: ThObservable(SM_i)
{};

double Btaunu::computeThValue()
{
    vector<complex> ** allcoeff = SM.getMyFlavour()->ComputeCoeffsmumu();
    double mtau = SM.getLeptons(StandardModel::TAU).getMass();
    double mB = SM.getMesons(QCD::B_P).getMass();
    double mb = SM.getQuarks(QCD::BOTTOM).getMass();
    return 1./64. * M_PI * mtau * mtau * pow(SM.getMesons(QCD::B_P).getDecayconst(), 2.) * mB * pow(1. - mtau * mtau / mB / mB, 2.) * SM.getMesons(QCD::B_P).getLifetime() * ((*(allcoeff[LO]))(0) + mB * mB/mb/mtau * ((*(allcoeff[LO]))(1) + (*(allcoeff[LO]))(2))).abs2();
}