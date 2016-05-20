/* 
 * Copyright (C) 2012 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "THDMcache.h"
#include <fstream>
#include "gslpp.h"
#include <sstream>
#include <string>

THDMcache::THDMcache(const StandardModel& SM_i)
        
        :br_tt(19861, 2, 0.),
        br_bb(19861, 2, 0.),
        br_tautau(19861, 2, 0.),
        br_cc(19861, 2, 0.),
        br_mumu(19861, 2, 0.),
        br_ZZ(19861, 2, 0.),
        br_WW(19861, 2, 0.),
        GammaHtotSM(19861, 2, 0.),
        log_cs_ggH_8(93, 2, 0.),
        log_cs_VBF_8(93, 2, 0.),
        log_cs_WH_8(33, 2, 0.),
        log_cs_ZH_8(33, 2, 0.),
        log_cs_ttH_8(99, 2, 0.),
        log_cs_bbH_8(99, 2, 0.),
        log_cs_ggA_8(99, 2, 0.),
        log_cs_ttA_8(99, 2, 0.),
        log_cs_bbA_8(99, 2, 0.),
        csrH_top_8(99, 2, 0.),
        csrH_bottom_8(99, 2, 0.),
        csrA_top_8(99, 2, 0.),
        csrA_bottom_8(99, 2, 0.),
        ATLAS_pp_phi_gaga(108, 2, 0.),
        ATLAS_ggF_phi_tautau(92, 2, 0.),
        ATLAS_bbF_phi_tautau(92, 2, 0.),
        ATLAS_ggF_A_hZ_tautauZ(79, 2, 0.),
        ATLAS_ggF_A_hZ_bbZ(79, 2, 0.),
        ATLAS_ggF_phi_tt(53, 2, 0.),
        ATLAS_ggF_H_WW(13,2,0.),
        ATLAS_VBF_H_WW(13,2,0.),
        ATLAS_ggF_H_ZZ(173,2,0.),
        ATLAS_VBF_H_ZZ(173,2,0.),
        ATLAS_ggF_H_hh(75,2,0.),
        ATLAS_pp_phi_gaga_e(108, 2, 0.),
        ATLAS_ggF_phi_tautau_e(92, 2, 0.),
        ATLAS_bbF_phi_tautau_e(92, 2, 0.),
        ATLAS_ggF_A_hZ_tautauZ_e(79, 2, 0.),
        ATLAS_ggF_A_hZ_bbZ_e(79, 2, 0.),
        ATLAS_ggF_phi_tt_e(53, 2, 0.),
        ATLAS_ggF_H_WW_e(13,2,0.),
        ATLAS_VBF_H_WW_e(13,2,0.),
        ATLAS_ggF_H_ZZ_e(173,2,0.),
        ATLAS_VBF_H_ZZ_e(173,2,0.),
        ATLAS_ggF_H_hh_e(75,2,0.),
        CMS_mu_pp_H_VV(172, 2, 0.),
        CMS_mu_pp_H_VV_e(172, 2, 0.),
        CMS_ggF_A_hZ_bbll(16, 2, 0.),
        CMS_pp_H_hh_gagabb(85, 2, 0.),
        CMS_pp_H_hh_bbbb(167, 2, 0.),
        CMS_bbF_phi_bb(81, 2, 0.),
        CMS_ggF_phi_tautau(92,2,0.),
        CMS_bbF_phi_tautau(92,2,0.),
        CMS_ggF_phi_gaga(141,2,0.),
        CMS_ggF_H_hh_bbtautau(10,2,0.),
        CMS_ggF_A_hZ_tautaull(14,2,0.),
        CMS_ggF_A_hZ_bbll_e(16, 2, 0.),
        CMS_pp_H_hh_gagabb_e(85, 2, 0.),
        CMS_pp_H_hh_bbbb_e(167, 2, 0.),
        CMS_bbF_phi_bb_e(81, 2, 0.),
        CMS_ggF_phi_tautau_e(92,2,0.),
        CMS_bbF_phi_tautau_e(92,2,0.),
        CMS_ggF_phi_gaga_e(141,2,0.),
        CMS_ggF_H_hh_bbtautau_e(10,2,0.),
        CMS_ggF_A_hZ_tautaull_e(14,2,0.),
        arraybsgamma(1111, 3, 0.),
        myTHDM(static_cast<const THDM*> (&SM_i)),
        PV(true)
{
    mym11_2=new m11_2(SM_i);
    mym22_2=new m22_2(SM_i);
    mylambda1=new lambda1(SM_i);
    mylambda2=new lambda2(SM_i);
    mylambda3=new lambda3(SM_i);
    mylambda4=new lambda4(SM_i);
    mylambda5=new lambda5(SM_i);
    myRunner=new Runner(SM_i);
  read();
}

THDMcache::~THDMcache()
{
  delete mym11_2;
  delete mym22_2;
  delete mylambda1;
  delete mylambda2;
  delete mylambda3;
  delete mylambda4;
  delete mylambda5;
  delete myRunner;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int THDMcache::CacheCheck(const gslpp::complex cache[][CacheSize], 
                          const int NumPar, const double params[]) const {
    bool bCache;
    for(int i=0; i<CacheSize; i++) {
        bCache = true;
        for(int j=0; j<NumPar; j++)
            bCache &= (params[j] == cache[j][i].real());
        if (bCache) return i;
    }
    return -1;
}

int THDMcache::CacheCheckReal(const double cache[][CacheSize], 
                          const int NumPar, const double params[]) const {
    bool bCache;
    for(int i=0; i<CacheSize; i++) {
        bCache = true;
        for(int j=0; j<NumPar; j++)
            bCache &= (params[j] == cache[j][i]);
        if (bCache) return i;
    }
    return -1;
}

void THDMcache::CacheShift(gslpp::complex cache[][CacheSize], const int NumPar, 
                           const double params[], const gslpp::complex newResult) const {
    // shift old parameters and result
    for(int i=CacheSize-1; i>0; i--)
        for(int j=0; j<NumPar+1; j++)
            cache[j][i] = cache[j][i-1];

    // store new parameters and result
    for(int j=0; j<NumPar; j++) {
        cache[j][0] = gslpp::complex(params[j], 0.0, false);
        cache[NumPar][0] = newResult;
    }
}

void THDMcache::CacheShiftReal(double cache[][CacheSize], const int NumPar,
                           const double params[], const double newResult) const {
    // shift old parameters and result
    for(int i=CacheSize-1; i>0; i--)
        for(int j=0; j<NumPar+1; j++)
            cache[j][i] = cache[j][i-1];

    // store new parameters and result
    for(int j=0; j<NumPar; j++) {
        cache[j][0] = params[j];
        cache[NumPar][0] = newResult;
    }
}

////////////////////////////////////////////////////////////////////////////////
/*One-loop functions*/
////////////////////////////////////////////////////////////////////////////////

gslpp::complex THDMcache::B0_MZ2_0_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHh2};

    int i = CacheCheck(B0_MZ2_0_MW2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_MW2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0., MW2, mHh2);
        CacheShift(B0_MZ2_0_MW2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_0_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHl2};

    int i = CacheCheck(B0_MZ2_0_MW2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_MW2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0., MW2, mHl2);
        CacheShift(B0_MZ2_0_MW2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::B0_MZ2_0_MZ2_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0_MZ2_0_MZ2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_MZ2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0., MZ2, mHh2);
        CacheShift(B0_MZ2_0_MZ2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::B0_MZ2_0_MZ2_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0_MZ2_0_MZ2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_MZ2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0., MZ2, mHl2);
        CacheShift(B0_MZ2_0_MZ2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::B0_MZ2_MW2_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHh2};

    int i = CacheCheck(B0_MZ2_MW2_MW2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_MW2_MW2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, MW2, MW2, mHh2);
        CacheShift(B0_MZ2_MW2_MW2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_MW2_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHl2};

    int i = CacheCheck(B0_MZ2_MW2_MW2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_MW2_MW2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, MW2, MW2, mHl2);
        CacheShift(B0_MZ2_MW2_MW2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_MZ2_MZ2_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0_MZ2_MZ2_MZ2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_MZ2_MZ2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, MZ2, MZ2, mHh2);
        CacheShift(B0_MZ2_MZ2_MZ2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_MZ2_MZ2_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0_MZ2_MZ2_MZ2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_MZ2_MZ2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, MZ2, MZ2, mHl2);
        CacheShift(B0_MZ2_MZ2_MZ2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_0_0_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0_MZ2_0_0_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_0_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0.0, 0.0, mHl2);
        CacheShift(B0_MZ2_0_0_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_0_0_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0_MZ2_0_0_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_0_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0.0, 0.0, mHh2);
        CacheShift(B0_MZ2_0_0_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_0_mHp2_mHl2(const double MZ2, const double mHp2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHl2};

    int i = CacheCheck(B0_MZ2_0_mHp2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_mHp2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0.0, mHp2, mHl2);
        CacheShift(B0_MZ2_0_mHp2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_0_mHp2_mHh2(const double MZ2, const double mHp2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHh2};

    int i = CacheCheck(B0_MZ2_0_mHp2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_mHp2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0.0, mHp2, mHh2);
        CacheShift(B0_MZ2_0_mHp2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_0_mA2_mHl2(const double MZ2, const double mA2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHl2};

    int i = CacheCheck(B0_MZ2_0_mA2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_mA2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0.0, mA2, mHl2);
        CacheShift(B0_MZ2_0_mA2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_0_mA2_mHh2(const double MZ2, const double mA2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHh2};

    int i = CacheCheck(B0_MZ2_0_mA2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_0_mA2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, 0.0, mA2, mHh2);
        CacheShift(B0_MZ2_0_mA2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_0_0(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0_MZ2_mHl2_0_0_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_0_0_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, 0.0, 0.0);
        CacheShift(B0_MZ2_mHl2_0_0_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_0_mHp2(const double MZ2, const double mHl2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHp2};

    int i = CacheCheck(B0_MZ2_mHl2_0_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_0_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, 0.0, mHp2);
        CacheShift(B0_MZ2_mHl2_0_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_0_mA2(const double MZ2, const double mHl2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mA2};

    int i = CacheCheck(B0_MZ2_mHl2_0_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_0_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, 0.0, mA2);
        CacheShift(B0_MZ2_mHl2_0_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_mHl2_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0_MZ2_mHl2_mHl2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_mHl2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, mHl2, mHl2);
        CacheShift(B0_MZ2_mHl2_mHl2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_mHh2_mHl2(const double MZ2, const double mHl2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHh2};

    int i = CacheCheck(B0_MZ2_mHl2_mHh2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_mHh2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, mHh2, mHl2);
        CacheShift(B0_MZ2_mHl2_mHh2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_mHh2_mHh2(const double MZ2, const double mHl2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHh2};

    int i = CacheCheck(B0_MZ2_mHl2_mHh2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_mHh2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, mHh2, mHh2);
        CacheShift(B0_MZ2_mHl2_mHh2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_mHp2_mHp2(const double MZ2, const double mHl2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHp2};

    int i = CacheCheck(B0_MZ2_mHl2_mHp2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_mHp2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, mHp2, mHp2);
        CacheShift(B0_MZ2_mHl2_mHp2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHl2_mA2_mA2(const double MZ2, const double mHl2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mA2};

    int i = CacheCheck(B0_MZ2_mHl2_mA2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHl2_mA2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHl2, mA2, mA2);
        CacheShift(B0_MZ2_mHl2_mA2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_0_0(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0_MZ2_mHh2_0_0_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_0_0_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, 0.0, 0.0);
        CacheShift(B0_MZ2_mHh2_0_0_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_0_mHp2(const double MZ2, const double mHh2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHp2};

    int i = CacheCheck(B0_MZ2_mHh2_0_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_0_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, 0.0, mHp2);
        CacheShift(B0_MZ2_mHh2_0_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_0_mA2(const double MZ2, const double mHh2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mA2};

    int i = CacheCheck(B0_MZ2_mHh2_0_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_0_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, 0.0, mA2);
        CacheShift(B0_MZ2_mHh2_0_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_mHl2_mHl2(const double MZ2, const double mHh2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHl2};

    int i = CacheCheck(B0_MZ2_mHh2_mHl2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_mHl2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, mHl2, mHl2);
        CacheShift(B0_MZ2_mHh2_mHl2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_mHh2_mHl2(const double MZ2, const double mHh2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHl2};

    int i = CacheCheck(B0_MZ2_mHh2_mHh2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_mHh2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, mHh2, mHl2);
        CacheShift(B0_MZ2_mHh2_mHh2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_mHh2_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0_MZ2_mHh2_mHh2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_mHh2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, mHh2, mHh2);
        CacheShift(B0_MZ2_mHh2_mHh2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_mHp2_mHp2(const double MZ2, const double mHh2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHp2};

    int i = CacheCheck(B0_MZ2_mHh2_mHp2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_mHp2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, mHp2, mHp2);
        CacheShift(B0_MZ2_mHh2_mHp2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHh2_mA2_mA2(const double MZ2, const double mHh2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mA2};

    int i = CacheCheck(B0_MZ2_mHh2_mA2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHh2_mA2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHh2, mA2, mA2);
        CacheShift(B0_MZ2_mHh2_mA2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHp2_0_mHl2(const double MZ2, const double mHp2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHl2};

    int i = CacheCheck(B0_MZ2_mHp2_0_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHp2_0_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHp2, 0.0, mHl2);
        CacheShift(B0_MZ2_mHp2_0_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHp2_0_mHh2(const double MZ2, const double mHp2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHh2};

    int i = CacheCheck(B0_MZ2_mHp2_0_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHp2_0_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHp2, 0.0, mHh2);
        CacheShift(B0_MZ2_mHp2_0_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHp2_mHp2_mHl2(const double MZ2, const double mHp2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHl2};

    int i = CacheCheck(B0_MZ2_mHp2_mHp2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHp2_mHp2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHp2, mHp2, mHl2);
        CacheShift(B0_MZ2_mHp2_mHp2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mHp2_mHp2_mHh2(const double MZ2, const double mHp2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHh2};

    int i = CacheCheck(B0_MZ2_mHp2_mHp2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mHp2_mHp2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mHp2, mHp2, mHh2);
        CacheShift(B0_MZ2_mHp2_mHp2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mA2_0_mHl2(const double MZ2, const double mA2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHl2};

    int i = CacheCheck(B0_MZ2_mA2_0_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mA2_0_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mA2, 0.0, mHl2);
        CacheShift(B0_MZ2_mA2_0_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mA2_0_mHh2(const double MZ2, const double mA2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHh2};

    int i = CacheCheck(B0_MZ2_mA2_0_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mA2_0_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mA2, 0.0, mHh2);
        CacheShift(B0_MZ2_mA2_0_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mA2_mA2_mHl2(const double MZ2, const double mA2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHl2};

    int i = CacheCheck(B0_MZ2_mA2_mA2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mA2_mA2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mA2, mA2, mHl2);
        CacheShift(B0_MZ2_mA2_mA2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0_MZ2_mA2_mA2_mHh2(const double MZ2, const double mA2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHh2};

    int i = CacheCheck(B0_MZ2_mA2_mA2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0_MZ2_mA2_mA2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0(MZ2, mA2, mA2, mHh2);
        CacheShift(B0_MZ2_mA2_mA2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

///////////////////////////////////////////////////////////////////////////////////////////

gslpp::complex THDMcache::B0p_MZ2_0_0_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0p_MZ2_0_0_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_0_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, 0.0, 0.0, mHl2);
        CacheShift(B0p_MZ2_0_0_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_0_0_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0p_MZ2_0_0_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_0_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, 0.0, 0.0, mHh2);
        CacheShift(B0p_MZ2_0_0_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_0_mHp2_mHl2(const double MZ2, const double mHp2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHl2};

    int i = CacheCheck(B0p_MZ2_0_mHp2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_mHp2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, 0.0, mHp2, mHl2);
        CacheShift(B0p_MZ2_0_mHp2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_0_mHp2_mHh2(const double MZ2, const double mHp2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHh2};

    int i = CacheCheck(B0p_MZ2_0_mHp2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_mHp2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, 0.0, mHp2, mHh2);
        CacheShift(B0p_MZ2_0_mHp2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_0_mHp2_mA2(const double MZ2, const double mHp2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mA2};

    int i = CacheCheck(B0p_MZ2_0_mHp2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_mHp2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, 0.0, mHp2, mA2);
        CacheShift(B0p_MZ2_0_mHp2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_0_mA2_mHl2(const double MZ2, const double mA2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHl2};

    int i = CacheCheck(B0p_MZ2_0_mA2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_mA2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, 0.0, mA2, mHl2);
        CacheShift(B0p_MZ2_0_mA2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_0_mA2_mHh2(const double MZ2, const double mA2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHh2};

    int i = CacheCheck(B0p_MZ2_0_mA2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_mA2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, 0.0, mA2, mHh2);
        CacheShift(B0p_MZ2_0_mA2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_0_0(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0p_MZ2_0_0_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_0_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, 0.0, 0.0);
        CacheShift(B0p_MZ2_0_0_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_0_mHp2(const double MZ2, const double mHl2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHp2};

    int i = CacheCheck(B0p_MZ2_mHl2_0_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHl2_0_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, 0.0, mHp2);
        CacheShift(B0p_MZ2_mHl2_0_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_0_mA2(const double MZ2, const double mHl2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mA2};

    int i = CacheCheck(B0p_MZ2_mHl2_0_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHl2_0_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, 0.0, mA2);
        CacheShift(B0p_MZ2_mHl2_0_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_mHl2_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B0p_MZ2_mHl2_mHl2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHl2_mHl2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, mHl2, mHl2);
        CacheShift(B0p_MZ2_mHl2_mHl2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_mHh2_mHl2(const double MZ2, const double mHl2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHh2};

    int i = CacheCheck(B0p_MZ2_mHl2_mHh2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHl2_mHh2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, mHh2, mHl2);
        CacheShift(B0p_MZ2_mHl2_mHh2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_mHh2_mHh2(const double MZ2, const double mHl2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHh2};

    int i = CacheCheck(B0p_MZ2_mHl2_mHh2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHl2_mHh2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, mHh2, mHh2);
        CacheShift(B0p_MZ2_mHl2_mHh2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_mHp2_mHp2(const double MZ2, const double mHl2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHp2};

    int i = CacheCheck(B0p_MZ2_mHl2_mHp2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHl2_mHp2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, mHp2, mHp2);
        CacheShift(B0p_MZ2_mHl2_mHp2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHl2_mA2_mA2(const double MZ2, const double mHl2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mA2};

    int i = CacheCheck(B0p_MZ2_mHl2_mA2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHl2_mA2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHl2, mA2, mA2);
        CacheShift(B0p_MZ2_mHl2_mA2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_0_0(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0p_MZ2_0_0_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_0_0_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, 0.0, 0.0);
        CacheShift(B0p_MZ2_0_0_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_0_mHp2(const double MZ2, const double mHh2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHp2};

    int i = CacheCheck(B0p_MZ2_mHh2_0_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHh2_0_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, 0.0, mHp2);
        CacheShift(B0p_MZ2_mHh2_0_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_0_mA2(const double MZ2, const double mHh2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mA2};

    int i = CacheCheck(B0p_MZ2_mHh2_0_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHh2_0_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, 0.0, mA2);
        CacheShift(B0p_MZ2_mHh2_0_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_mHl2_mHl2(const double MZ2, const double mHh2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHl2};

    int i = CacheCheck(B0p_MZ2_mHh2_mHl2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHh2_mHl2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, mHl2, mHl2);
        CacheShift(B0p_MZ2_mHh2_mHl2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_mHh2_mHl2(const double MZ2, const double mHh2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHl2};

    int i = CacheCheck(B0p_MZ2_mHh2_mHh2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHh2_mHh2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, mHh2, mHl2);
        CacheShift(B0p_MZ2_mHh2_mHh2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_mHh2_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B0p_MZ2_mHh2_mHh2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHh2_mHh2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, mHh2, mHh2);
        CacheShift(B0p_MZ2_mHh2_mHh2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_mHp2_mHp2(const double MZ2, const double mHh2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHp2};

    int i = CacheCheck(B0p_MZ2_mHh2_mHp2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHh2_mHp2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, mHp2, mHp2);
        CacheShift(B0p_MZ2_mHh2_mHp2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHh2_mA2_mA2(const double MZ2, const double mHh2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mA2};

    int i = CacheCheck(B0p_MZ2_mHh2_mA2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHh2_mA2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHh2, mA2, mA2);
        CacheShift(B0p_MZ2_mHh2_mA2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHp2_0_mHl2(const double MZ2, const double mHp2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHl2};

    int i = CacheCheck(B0p_MZ2_mHp2_0_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHp2_0_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHp2, 0.0, mHl2);
        CacheShift(B0p_MZ2_mHp2_0_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHp2_0_mHh2(const double MZ2, const double mHp2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHh2};

    int i = CacheCheck(B0p_MZ2_mHp2_0_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHp2_0_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHp2, 0.0, mHh2);
        CacheShift(B0p_MZ2_mHp2_0_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHp2_0_mA2(const double MZ2, const double mHp2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mA2};

    int i = CacheCheck(B0p_MZ2_mHp2_0_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHp2_0_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHp2, 0.0, mA2);
        CacheShift(B0p_MZ2_mHp2_0_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHp2_mHp2_mHl2(const double MZ2, const double mHp2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHl2};

    int i = CacheCheck(B0p_MZ2_mHp2_mHp2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHp2_mHp2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHp2, mHp2, mHl2);
        CacheShift(B0p_MZ2_mHp2_mHp2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mHp2_mHp2_mHh2(const double MZ2, const double mHp2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHp2, mHh2};

    int i = CacheCheck(B0p_MZ2_mHp2_mHp2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mHp2_mHp2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mHp2, mHp2, mHh2);
        CacheShift(B0p_MZ2_mHp2_mHp2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mA2_0_mHl2(const double MZ2, const double mA2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHl2};

    int i = CacheCheck(B0p_MZ2_mA2_0_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mA2_0_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mA2, 0.0, mHl2);
        CacheShift(B0p_MZ2_mA2_0_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mA2_0_mHh2(const double MZ2, const double mA2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHh2};

    int i = CacheCheck(B0p_MZ2_mA2_0_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mA2_0_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mA2, 0.0, mHh2);
        CacheShift(B0p_MZ2_mA2_0_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mA2_0_mHp2(const double MZ2, const double mA2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHp2};

    int i = CacheCheck(B0p_MZ2_mA2_0_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mA2_0_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mA2, 0.0, mHp2);
        CacheShift(B0p_MZ2_mA2_0_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mA2_mA2_mHl2(const double MZ2, const double mA2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHl2};

    int i = CacheCheck(B0p_MZ2_mA2_mA2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mA2_mA2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mA2, mA2, mHl2);
        CacheShift(B0p_MZ2_mA2_mA2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B0p_MZ2_mA2_mA2_mHh2(const double MZ2, const double mA2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHh2};

    int i = CacheCheck(B0p_MZ2_mA2_mA2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B0p_MZ2_mA2_mA2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B0p(MZ2, mA2, mA2, mHh2);
        CacheShift(B0p_MZ2_mA2_mA2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

///////////////////////////////////////////////////////////////////////////////////////////

gslpp::complex THDMcache::B00_MZ2_0_mA2_mHp2(const double MZ2, const double mA2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mA2, mHp2};

    int i = CacheCheck(B00_MZ2_0_mA2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_mA2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., mA2, mHp2);
        CacheShift(B00_MZ2_0_mA2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_mHh2_mA2(const double MZ2, const double mHh2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mA2};

    int i = CacheCheck(B00_MZ2_0_mHh2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_mHh2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., mHh2, mA2);
        CacheShift(B00_MZ2_0_mHh2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_mHh2_mHp2(const double MZ2, const double mHh2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mHp2};

    int i = CacheCheck(B00_MZ2_0_mHh2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_mHh2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., mHh2, mHp2);
        CacheShift(B00_MZ2_0_mHh2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_mHl2_mA2(const double MZ2, const double mHl2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mA2};

    int i = CacheCheck(B00_MZ2_0_mHl2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_mHl2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., mHl2, mA2);
        CacheShift(B00_MZ2_0_mHl2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_mHl2_mHp2(const double MZ2, const double mHl2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mHp2};

    int i = CacheCheck(B00_MZ2_0_mHl2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_mHl2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., mHl2, mHp2);
        CacheShift(B00_MZ2_0_mHl2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::B00_MZ2_0_mHp2_mHp2(const double MZ2, const double mHp2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHp2};

    int i = CacheCheck(B00_MZ2_0_mHp2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_mHp2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., mHp2, mHp2);
        CacheShift(B00_MZ2_0_mHp2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHh2};

    int i = CacheCheck(B00_MZ2_0_MW2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_MW2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MW2, MW2, mHh2);
        CacheShift(B00_MZ2_0_MW2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHl2};

    int i = CacheCheck(B00_MZ2_0_MW2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_MW2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., MW2, mHl2);
        CacheShift(B00_MZ2_0_MW2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_MZ2_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B00_MZ2_0_MZ2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_MZ2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., MZ2, mHh2);
        CacheShift(B00_MZ2_0_MZ2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_0_MZ2_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B00_MZ2_0_MZ2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_0_MZ2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, 0., MZ2, mHl2);
        CacheShift(B00_MZ2_0_MZ2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MW2_mA2_mHp2(const double MZ2, const double MW2, const double mA2, const double mHp2) const {
    int NumPar = 4;
    double params[] = {MZ2, MW2, mA2, mHp2};

    int i = CacheCheck(B00_MZ2_MW2_mA2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MW2_mA2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MW2, mA2, mHp2);
        CacheShift(B00_MZ2_MW2_mA2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MW2_mHh2_mHp2(const double MZ2, const double MW2, const double mHh2, const double mHp2) const {
    int NumPar = 4;
    double params[] = {MZ2, MW2, mHh2, mHp2};

    int i = CacheCheck(B00_MZ2_MW2_mHh2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MW2_mHh2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MW2, mHh2, mHp2);
        CacheShift(B00_MZ2_MW2_mHh2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MW2_mHl2_mHp2(const double MZ2, const double MW2, const double mHl2, const double mHp2) const {
    int NumPar = 4;
    double params[] = {MZ2, MW2, mHl2, mHp2};

    int i = CacheCheck(B00_MZ2_MW2_mHl2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MW2_mHl2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MW2, mHl2, mHp2);
        CacheShift(B00_MZ2_MW2_mHl2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MW2_mHp2_mHp2(const double MZ2, const double MW2, const double mHp2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHp2};

    int i = CacheCheck(B00_MZ2_MW2_mHp2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MW2_mHp2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MW2, mHp2, mHp2);
        CacheShift(B00_MZ2_MW2_mHp2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MW2_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHh2};

    int i = CacheCheck(B00_MZ2_MW2_MW2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MW2_MW2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MW2, MW2, mHh2);
        CacheShift(B00_MZ2_MW2_MW2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MW2_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const {
    int NumPar = 3;
    double params[] = {MZ2, MW2, mHl2};

    int i = CacheCheck(B00_MZ2_MW2_MW2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MW2_MW2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MW2, MW2, mHl2);
        CacheShift(B00_MZ2_MW2_MW2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MZ2_mHh2_mA2(const double MZ2, const double mHh2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHh2, mA2};

    int i = CacheCheck(B00_MZ2_MZ2_mHh2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MZ2_mHh2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MZ2, mHh2, mA2);
        CacheShift(B00_MZ2_MZ2_mHh2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MZ2_mHl2_mA2(const double MZ2, const double mHl2, const double mA2) const {
    int NumPar = 3;
    double params[] = {MZ2, mHl2, mA2};

    int i = CacheCheck(B00_MZ2_MZ2_mHl2_mA2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MZ2_mHl2_mA2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MZ2, mHl2, mA2);
        CacheShift(B00_MZ2_MZ2_mHl2_mA2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MZ2_mHp2_mHp2(const double MZ2, const double mHp2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHp2};

    int i = CacheCheck(B00_MZ2_MZ2_mHp2_mHp2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MZ2_mHp2_mHp2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MZ2, mHp2, mHp2);
        CacheShift(B00_MZ2_MZ2_mHp2_mHp2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MZ2_MZ2_mHh2(const double MZ2, const double mHh2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHh2};

    int i = CacheCheck(B00_MZ2_MZ2_MZ2_mHh2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MZ2_MZ2_mHh2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MZ2, MZ2, mHh2);
        CacheShift(B00_MZ2_MZ2_MZ2_mHh2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

gslpp::complex THDMcache::B00_MZ2_MZ2_MZ2_mHl2(const double MZ2, const double mHl2) const {
    int NumPar = 2;
    double params[] = {MZ2, mHl2};

    int i = CacheCheck(B00_MZ2_MZ2_MZ2_mHl2_cache, NumPar, params);
    if (i>=0) {
        return ( B00_MZ2_MZ2_MZ2_mHl2_cache[NumPar][i] );
    } else {
        gslpp::complex newResult = PV.B00(MZ2, MZ2, MZ2, mHl2);
        CacheShift(B00_MZ2_MZ2_MZ2_mHl2_cache, NumPar, params, newResult);
        return newResult;
    } 
}

void THDMcache::read(){

    std::stringstream br1,br2,br3,br4,br5,br6,br7;
    std::stringstream dw1;
    std::stringstream cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8,cs9;
    std::stringstream csr1,csr2,csr3,csr4;
    std::stringstream ex1,ex2,ex3,ex4,ex5,ex6,ex7,ex8,ex9,ex10,ex11,ex12,ex13,ex14,ex15,ex16,ex17,ex18,ex19,ex20,ex21;
    std::stringstream ex1e,ex2e,ex3e,ex4e,ex5e,ex6e,ex7e,ex8e,ex9e,ex10e,ex11e,ex12e,ex13e,ex14e,ex15e,ex16e,ex17e,ex18e,ex19e,ex20e,ex21e;
    std::stringstream bsg1;

    std::cout<<"reading tables"<<std::endl;

//    std::cout << "HEPFITPATH = " << getenv("HEPFITPATH") << std::endl;
    std::stringstream path;
    path << getenv("HEPFITPATH") << "/THDM/tabs/";
    std::string tablepath=path.str();

    br1 << tablepath << "br1.dat";
    br_tt = readTable(br1.str(),19861,2);
    br2 << tablepath << "br2.dat";
    br_bb = readTable(br2.str(),19861,2);
    br3 << tablepath << "br3.dat";
    br_tautau = readTable(br3.str(),19861,2); 
    br4 << tablepath << "br4.dat";
    br_cc = readTable(br4.str(),19861,2);
    br5 << tablepath << "br5.dat";
    br_mumu = readTable(br5.str(),19861,2);
    br6 << tablepath << "br6.dat";
    br_ZZ = readTable(br6.str(),19861,2);
    br7 << tablepath << "br7.dat";
    br_WW = readTable(br7.str(),19861,2);
    dw1 << tablepath << "dw1.dat";
    GammaHtotSM = readTable(dw1.str(),19861,2);
    cs1 << tablepath << "log_cs_ggH_8.dat";
    log_cs_ggH_8 = readTable(cs1.str(),93,2);
    cs2 << tablepath << "log_cs_VBF_8.dat";
    log_cs_VBF_8 = readTable(cs2.str(),93,2);
    cs3 << tablepath << "log_cs_WH_8.dat";
    log_cs_WH_8 = readTable(cs3.str(),33,2);
    cs4 << tablepath << "log_cs_ZH_8.dat";
    log_cs_ZH_8 = readTable(cs4.str(),33,2);
    cs5 << tablepath << "log_cs_ttH_8.dat";
    log_cs_ttH_8 = readTable(cs5.str(),99,2);
    cs6 << tablepath << "log_cs_bbH_8.dat";
    log_cs_bbH_8 = readTable(cs6.str(),99,2);
    cs7 << tablepath << "log_cs_ggA_8.dat";
    log_cs_ggA_8 = readTable(cs7.str(),99,2);
    cs8 << tablepath << "log_cs_ttA_8.dat";
    log_cs_ttA_8 = readTable(cs8.str(),99,2);
    cs9 << tablepath << "log_cs_bbA_8.dat";
    log_cs_bbA_8 = readTable(cs9.str(),99,2);
    csr1 << tablepath << "csrH_top_8.dat";
    csrH_top_8 = readTable(csr1.str(),99,2);
    csr2 << tablepath << "csrH_bottom_8.dat";
    csrH_bottom_8 = readTable(csr2.str(),99,2);
    csr3 << tablepath << "csrA_top_8.dat";
    csrA_top_8 = readTable(csr3.str(),99,2);
    csr4 << tablepath << "csrA_bottom_8.dat";
    csrA_bottom_8 = readTable(csr4.str(),99,2);
    ex1 << tablepath << "150400936.dat";
    CMS_mu_pp_H_VV = readTable(ex1.str(),172,2);
    ex1e << tablepath << "150400936_e.dat";
    CMS_mu_pp_H_VV_e = readTable(ex1e.str(),172,2);
    ex2 << tablepath << "150404710.dat";
    CMS_ggF_A_hZ_bbll = readTable(ex2.str(),16,2);
    ex2e << tablepath << "150404710_e.dat";
    CMS_ggF_A_hZ_bbll_e = readTable(ex2e.str(),16,2);
    ex3 << tablepath << "CMS-PAS-HIG-13-032.dat";
    CMS_pp_H_hh_gagabb = readTable(ex3.str(),85,2);
    ex3e << tablepath << "CMS-PAS-HIG-13-032_e.dat";
    CMS_pp_H_hh_gagabb_e = readTable(ex3e.str(),85,2);
    ex4 << tablepath << "150304114.dat";
    CMS_pp_H_hh_bbbb = readTable(ex4.str(),167,2);
    ex4e << tablepath << "150304114_e.dat";
    CMS_pp_H_hh_bbbb_e = readTable(ex4e.str(),167,2);
    ex5 << tablepath << "14076583.dat";
    ATLAS_pp_phi_gaga = readTable(ex5.str(),108,2);
    ex5e << tablepath << "14076583_e.dat";
    ATLAS_pp_phi_gaga_e = readTable(ex5e.str(),108,2);
    ex6 << tablepath << "14096064_a.dat";
    ATLAS_ggF_phi_tautau = readTable(ex6.str(),92,2);
    ex6e << tablepath << "14096064_a_e.dat";
    ATLAS_ggF_phi_tautau_e = readTable(ex6e.str(),92,2);
    ex7 << tablepath << "14096064_b.dat";
    ATLAS_bbF_phi_tautau = readTable(ex7.str(),92,2);
    ex7e << tablepath << "14096064_b_e.dat";
    ATLAS_bbF_phi_tautau_e = readTable(ex7e.str(),92,2);
    ex8 << tablepath << "150204478_a.dat";
    ATLAS_ggF_A_hZ_tautauZ = readTable(ex8.str(),79,2);
    ex8e << tablepath << "150204478_a_e.dat";
    ATLAS_ggF_A_hZ_tautauZ_e = readTable(ex8e.str(),79,2);
    ex9 << tablepath << "150204478_b.dat";
    ATLAS_ggF_A_hZ_bbZ = readTable(ex9.str(),79,2);
    ex9e << tablepath << "150204478_b_e.dat";
    ATLAS_ggF_A_hZ_bbZ_e = readTable(ex9e.str(),79,2);
    ex10 << tablepath << "150608329.dat";
    CMS_bbF_phi_bb = readTable(ex10.str(),81,2);
    ex10e << tablepath << "150608329_e.dat";
    CMS_bbF_phi_bb_e = readTable(ex10e.str(),81,2);
    ex11 << tablepath << "150507018.dat";
    ATLAS_ggF_phi_tt = readTable(ex11.str(),53,2);
    ex11e << tablepath << "150507018_e.dat";
    ATLAS_ggF_phi_tt_e = readTable(ex11e.str(),53,2);
    ex12 << tablepath << "CMS-PAS-HIG-14-029_a.dat";
    CMS_ggF_phi_tautau = readTable(ex12.str(),92,2);
    ex12e << tablepath << "CMS-PAS-HIG-14-029_a_e.dat";
    CMS_ggF_phi_tautau_e = readTable(ex12e.str(),92,2);
    ex13 << tablepath << "CMS-PAS-HIG-14-029_b.dat";
    CMS_bbF_phi_tautau = readTable(ex13.str(),92,2);
    ex13e << tablepath << "CMS-PAS-HIG-14-029_b_e.dat";
    CMS_bbF_phi_tautau_e = readTable(ex13e.str(),92,2);
    ex14 << tablepath << "150602301.dat";
    CMS_ggF_phi_gaga = readTable(ex14.str(),141,2);
    ex14e << tablepath << "150602301_e.dat";
    CMS_ggF_phi_gaga_e = readTable(ex14e.str(),141,2);
    ex15 << tablepath << "150900389_a.dat";
    ATLAS_ggF_H_WW = readTable(ex15.str(),13,2);
    ex15e << tablepath << "150900389_a_e.dat";
    ATLAS_ggF_H_WW_e = readTable(ex15e.str(),13,2);
    ex16 << tablepath << "150900389_b.dat";
    ATLAS_VBF_H_WW = readTable(ex16.str(),13,2);
    ex16e << tablepath << "150900389_b_e.dat";
    ATLAS_VBF_H_WW_e = readTable(ex16e.str(),13,2);
    ex17 << tablepath << "150904670.dat";
    ATLAS_ggF_H_hh = readTable(ex17.str(),75,2);
    ex17e << tablepath << "150904670_e.dat";
    ATLAS_ggF_H_hh_e = readTable(ex17e.str(),75,2);
    ex18 << tablepath << "151001181_a.dat";
    CMS_ggF_H_hh_bbtautau = readTable(ex18.str(),10,2);
    ex18e << tablepath << "151001181_a_e.dat";
    CMS_ggF_H_hh_bbtautau_e = readTable(ex18e.str(),10,2);
    ex19 << tablepath << "151001181_b.dat";
    CMS_ggF_A_hZ_tautaull = readTable(ex19.str(),14,2);
    ex19e << tablepath << "151001181_b_e.dat";
    CMS_ggF_A_hZ_tautaull_e = readTable(ex19e.str(),14,2);
    ex20 << tablepath << "150705930_a.dat";
    ATLAS_ggF_H_ZZ = readTable(ex20.str(),173,2);
    ex20e << tablepath << "150705930_a_e.dat";
    ATLAS_ggF_H_ZZ_e = readTable(ex20e.str(),173,2);
    ex21 << tablepath << "150705930_b.dat";
    ATLAS_VBF_H_ZZ = readTable(ex21.str(),173,2);
    ex21e << tablepath << "150705930_b_e.dat";
    ATLAS_VBF_H_ZZ_e = readTable(ex21e.str(),173,2);
    bsg1 << tablepath << "bsgammatable.dat";
    arraybsgamma = readTable(bsg1.str(),1111,3);
}    
    


double THDMcache::ip_Br_HPtott(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_Br_HPtott_cache, NumPar, params);
    if (i>=0) {
        return ( ip_Br_HPtott_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(br_tt,mass));
        CacheShiftReal(ip_Br_HPtott_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_Br_HPtobb(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_Br_HPtobb_cache, NumPar, params);
    if (i>=0) {
        return ( ip_Br_HPtobb_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(br_bb,mass));
        CacheShiftReal(ip_Br_HPtobb_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_Br_HPtotautau(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_Br_HPtotautau_cache, NumPar, params);
    if (i>=0) {
        return ( ip_Br_HPtotautau_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(br_tautau,mass));
        CacheShiftReal(ip_Br_HPtotautau_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_Br_HPtocc(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_Br_HPtocc_cache, NumPar, params);
    if (i>=0) {
        return ( ip_Br_HPtocc_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(br_cc,mass));
        CacheShiftReal(ip_Br_HPtocc_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_Br_HPtomumu(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_Br_HPtomumu_cache, NumPar, params);
    if (i>=0) {
        return ( ip_Br_HPtomumu_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(br_mumu,mass));
        CacheShiftReal(ip_Br_HPtomumu_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_Br_HPtoZZ(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_Br_HPtoZZ_cache, NumPar, params);
    if (i>=0) {
        return ( ip_Br_HPtoZZ_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(br_ZZ,mass));
        CacheShiftReal(ip_Br_HPtoZZ_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_Br_HPtoWW(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_Br_HPtoWW_cache, NumPar, params);
    if (i>=0) {
        return ( ip_Br_HPtoWW_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(br_WW,mass));
        CacheShiftReal(ip_Br_HPtoWW_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_GammaHPtotSM(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_GammaHPtotSM_cache, NumPar, params);
    if (i>=0) {
        return ( ip_GammaHPtotSM_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(GammaHtotSM,mass));
        CacheShiftReal(ip_GammaHPtotSM_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_ggtoH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ggtoH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=80. && mass <=1000.) {
            newResult = pow(10.0,interpolate (log_cs_ggH_8,mass));
        }
        CacheShiftReal(ip_cs_ggtoH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_VBFtoH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_VBFtoH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_VBFtoH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=80. && mass <=1000.) {
            newResult = pow(10.0,interpolate (log_cs_VBF_8,mass));
        }
        CacheShiftReal(ip_cs_VBFtoH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_WtoWH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_WtoWH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_WtoWH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=80. && mass <=400.) {
            newResult = pow(10.0,interpolate (log_cs_WH_8,mass));
        }
        CacheShiftReal(ip_cs_WtoWH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_ZtoZH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ZtoZH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ZtoZH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=80. && mass <=400.) {
            newResult = pow(10.0,interpolate (log_cs_ZH_8,mass));
        }
        CacheShiftReal(ip_cs_ZtoZH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_pptottH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptottH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptottH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=1000.) {
            newResult = pow(10.0,interpolate (log_cs_ttH_8,mass));
        }
        CacheShiftReal(ip_cs_pptottH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_pptobbH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptobbH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptobbH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=1000.) {
            newResult = pow(10.0,interpolate (log_cs_bbH_8,mass));
        }
        CacheShiftReal(ip_cs_pptobbH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_ggtoA_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ggtoA_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoA_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=1000.) {
            newResult = pow(10.0,interpolate (log_cs_ggA_8,mass));
        }
        CacheShiftReal(ip_cs_ggtoA_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_pptottA_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptottA_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptottA_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=1000.) {
            newResult = pow(10.0,interpolate (log_cs_ttA_8,mass));
        }
        CacheShiftReal(ip_cs_pptottA_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_cs_pptobbA_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptobbA_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptobbA_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=1000.) {
            newResult = pow(10.0,interpolate (log_cs_bbA_8,mass));
        }
        CacheShiftReal(ip_cs_pptobbA_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_csr_ggH_t(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggH_t_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggH_t_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrH_top_8,mass);
        CacheShiftReal(ip_csr_ggH_t_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_csr_ggH_b(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggH_b_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggH_b_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrH_bottom_8,mass);
        CacheShiftReal(ip_csr_ggH_b_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_csr_ggA_t(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggA_t_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggA_t_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrA_top_8,mass);
        CacheShiftReal(ip_csr_ggA_t_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_csr_ggA_b(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggA_b_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggA_b_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrA_bottom_8,mass);
        CacheShiftReal(ip_csr_ggA_b_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_pp_phi_gaga_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_gaga_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_gaga_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_pp_phi_gaga,mass);
        CacheShiftReal(ip_ex_pp_phi_gaga_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_pp_phi_gaga_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_gaga_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_gaga_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_pp_phi_gaga_e,mass);
        CacheShiftReal(ip_ex_pp_phi_gaga_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_tautau_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_tautau_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_tautau_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_ggF_phi_tautau,mass);
        CacheShiftReal(ip_ex_ggF_phi_tautau_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_tautau_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_tautau_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_tautau_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_ggF_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_ggF_phi_tautau_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_bbF_phi_tautau_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bbF_phi_tautau_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bbF_phi_tautau_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_bbF_phi_tautau,mass);
        CacheShiftReal(ip_ex_bbF_phi_tautau_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_bbF_phi_tautau_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bbF_phi_tautau_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bbF_phi_tautau_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_bbF_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_bbF_phi_tautau_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_A_hZ_tautauZ_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_tautauZ_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_tautauZ_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_ggF_A_hZ_tautauZ,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_tautauZ_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_tautauZ_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_tautauZ_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_ggF_A_hZ_tautauZ_e,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_tautauZ_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_A_hZ_bbZ_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_bbZ_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_bbZ_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_ggF_A_hZ_bbZ,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_bbZ_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}





double THDMcache::ip_ex_ggF_A_hZ_bbZ_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_bbZ_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_bbZ_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS_ggF_A_hZ_bbZ_e,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_bbZ_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_tt_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_tt_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_tt_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_phi_tt,mass);
        CacheShiftReal(ip_ex_ggF_phi_tt_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_tt_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_tt_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_tt_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_phi_tt_e,mass);
        CacheShiftReal(ip_ex_ggF_phi_tt_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_WW_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_WW_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_WW_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_H_WW,mass);
        CacheShiftReal(ip_ex_ggF_H_WW_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_WW_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_WW_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_WW_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_H_WW_e,mass);
        CacheShiftReal(ip_ex_ggF_H_WW_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_VBF_H_WW_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_WW_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_VBF_H_WW,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_VBF_H_WW_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_WW_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_VBF_H_WW_e,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_ZZ_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_ZZ_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_ZZ_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_H_ZZ,mass);
        CacheShiftReal(ip_ex_ggF_H_ZZ_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_ZZ_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_ZZ_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_ZZ_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_H_ZZ_e,mass);
        CacheShiftReal(ip_ex_ggF_H_ZZ_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_VBF_H_ZZ_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_ZZ_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_VBF_H_ZZ,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_VBF_H_ZZ_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_ZZ_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_VBF_H_ZZ_e,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_hh_ATLAS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_hh_ATLAS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_hh_ATLAS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_H_hh,mass);
        CacheShiftReal(ip_ex_ggF_H_hh_ATLAS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_hh_ATLAS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_hh_ATLAS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_hh_ATLAS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS_ggF_H_hh_e,mass);
        CacheShiftReal(ip_ex_ggF_H_hh_ATLAS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_mu_pp_H_VV_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_mu_pp_H_VV_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_mu_pp_H_VV_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_mu_pp_H_VV,mass);
        CacheShiftReal(ip_ex_mu_pp_H_VV_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_mu_pp_H_VV_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_mu_pp_H_VV_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_mu_pp_H_VV_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_mu_pp_H_VV_e,mass);
        CacheShiftReal(ip_ex_mu_pp_H_VV_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_A_hZ_bbll_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_bbll_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_bbll_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_ggF_A_hZ_bbll,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_bbll_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_A_hZ_bbll_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_bbll_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_bbll_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_ggF_A_hZ_bbll_e,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_bbll_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_pp_phi_hh_gagabb_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_gagabb_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_gagabb_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_pp_H_hh_gagabb,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_gagabb_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_pp_phi_hh_gagabb_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_gagabb_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_gagabb_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_pp_H_hh_gagabb_e,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_gagabb_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_pp_phi_hh_bbbb_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_bbbb_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_bbbb_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_pp_H_hh_bbbb,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_bbbb_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_pp_phi_hh_bbbb_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_bbbb_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_bbbb_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS_pp_H_hh_bbbb_e,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_bbbb_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_bbF_phi_bb_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bbF_phi_bb_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bbF_phi_bb_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_bbF_phi_bb,mass);
        CacheShiftReal(ip_ex_bbF_phi_bb_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_bbF_phi_bb_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bbF_phi_bb_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bbF_phi_bb_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_bbF_phi_bb_e,mass);
        CacheShiftReal(ip_ex_bbF_phi_bb_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_tautau_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_tautau_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_tautau_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_phi_tautau,mass);
        CacheShiftReal(ip_ex_ggF_phi_tautau_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_tautau_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_tautau_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_tautau_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_ggF_phi_tautau_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_bbF_phi_tautau_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bbF_phi_tautau_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bbF_phi_tautau_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_bbF_phi_tautau,mass);
        CacheShiftReal(ip_ex_bbF_phi_tautau_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_bbF_phi_tautau_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bbF_phi_tautau_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bbF_phi_tautau_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_bbF_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_bbF_phi_tautau_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_gaga_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_gaga_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_gaga_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_phi_gaga,mass);
        CacheShiftReal(ip_ex_ggF_phi_gaga_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_phi_gaga_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_gaga_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_phi_gaga_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_phi_gaga_e,mass);
        CacheShiftReal(ip_ex_ggF_phi_gaga_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_hh_bbtautau_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_hh_bbtautau_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_hh_bbtautau_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_H_hh_bbtautau,mass);
        CacheShiftReal(ip_ex_ggF_H_hh_bbtautau_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_H_hh_bbtautau_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_hh_bbtautau_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_H_hh_bbtautau_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_H_hh_bbtautau_e,mass);
        CacheShiftReal(ip_ex_ggF_H_hh_bbtautau_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_A_hZ_tautaull_CMS(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_tautaull_CMS_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_tautaull_CMS_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_A_hZ_tautaull,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_tautaull_CMS_cache, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_ggF_A_hZ_tautaull_CMS_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_A_hZ_tautaull_CMS_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_ggF_A_hZ_tautaull_CMS_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS_ggF_A_hZ_tautaull_e,mass);
        CacheShiftReal(ip_ex_ggF_A_hZ_tautaull_CMS_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double THDMcache::ip_ex_bsgamma(double logtb, double logmHp){
    int NumPar = 2;
    double params[] = {logtb, logmHp};

    int i = CacheCheckReal(ip_ex_bsgamma_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bsgamma_cache[NumPar][i] );
    } else {
        double newResult = interpolate2D(arraybsgamma, logtb, logmHp);
        CacheShiftReal(ip_ex_bsgamma_cache, NumPar, params, newResult);
        return newResult;
    }
}



gslpp::matrix<double> THDMcache::readTable(std::string filename, int rowN, int colN){

    std::ifstream INfile;
    std::string lineTab;
    INfile.open( filename.c_str() );
    if(INfile.fail()){
        std::cout<<"error: in HEAVY"<<" doesn't exist!"<<std::endl;
    }

    gslpp::matrix<double> arrayTab(rowN, colN, 0.);
    int a =0;
    int b=0;
    double v;

    while(INfile.good()){
        while(getline(INfile, lineTab)){
            if( lineTab[0]=='#' )continue;
            else{
            std::istringstream streamTab(lineTab);
            b=0;
            while(streamTab >>v){
                arrayTab.assign(a,b,v);
                b++;
            }
            a++;
            }
        }
    }
    
    INfile.close();
    
    return arrayTab;
}

//1D interpolation

double THDMcache::interpolate(gslpp::matrix<double> arrayTab, double x){

    int rowN=arrayTab.size_i();
    
    double xmin = arrayTab(0,0);
    double xmax = arrayTab(rowN-1,0);
    double interval = arrayTab(1,0)-arrayTab(0,0);
    int Nintervals = (x-xmin)/interval;
    double y = 0.0;
       
    if(x<xmin){
//        std::cout<<"warning: your table parameter value is smaller than the minimum allowed value"<<std::endl;
        return 0.;
    }
    else if(x>xmax){
//        std::cout<<"warning: your table parameter value is greater than the maximum allowed value"<<std::endl;
        return 0.;
    }
    else{
        y =(arrayTab(Nintervals+1,1)-arrayTab(Nintervals,1))/(arrayTab(Nintervals+1,0)
                   -arrayTab(Nintervals,0))*(x-arrayTab(Nintervals,0))+arrayTab(Nintervals,1);
        return y;
    }
}

//2D interpolation

double THDMcache::interpolate2D(gslpp::matrix<double> arrayTab, double x, double y){

    int rowN=arrayTab.size_i();
    
    double xmin = arrayTab(0,0);
    double xmax = arrayTab(rowN-1,0);
    double ymin = arrayTab(0,1);
    double ymax = arrayTab(rowN-1,1);
    double intervalx = arrayTab(1,0)-arrayTab(0,0);
    int i=1;
    do i++;
    while(arrayTab(i,1)-arrayTab(i-1,1)==0&&i<10000);
    double intervaly = arrayTab(i,1)-arrayTab(i-1,1);
    int Nintervalsx = (x-xmin)/intervalx;
    int Nintervalsy = (y-ymin)/intervaly;
    if(x<xmin||x>xmax||y<ymin||y>ymax){
//        std::cout<<"warning: the parameter point lies outside the table"<<std::endl;
        return 0.;
    }
    else{
    double x1=arrayTab(i*Nintervalsy+Nintervalsx,0);
    double x2=arrayTab(i*Nintervalsy+Nintervalsx+1,0);
    double y1=arrayTab(i*Nintervalsy+Nintervalsx,1);
    double y2=arrayTab(i*(Nintervalsy+1)+Nintervalsx,1);
    return (arrayTab(i*Nintervalsy+Nintervalsx,2) * (x2-x) * (y2-y)
            +arrayTab(i*Nintervalsy+Nintervalsx+1,2) * (x-x1) * (y2-y)
            +arrayTab(i*(Nintervalsy+1)+Nintervalsx,2) * (x2-x) * (y-y1)
            +arrayTab(i*(Nintervalsy+1)+Nintervalsx+1,2) * (x-x1) * (y-y1))
           /((x2-x1)*(y2-y1));
    }
}

double THDMcache::ghHpHm(const double mHp2, const double tanb, const double m12_2, const double bma, const double mHl, const double vev) const {
    int NumPar = 6;
    double params[] = {mHp2, tanb, m12_2, bma, mHl, vev};

    int i = CacheCheckReal(ghHpHm_cache, NumPar, params);
    if (i>=0) {
        return ( ghHpHm_cache[NumPar][i] );
    } else {
        double newResult = ((cos(bma)*mHl*mHl*(tanb*tanb-1.0))/tanb 
                                    -(mHl*mHl+2.0*mHp2)*sin(bma) 
                                    +(m12_2*(cos(bma)*(1.0-tanb*tanb)+2.0*sin(bma)*tanb)*(1.0+tanb*tanb))/(tanb*tanb))/vev;
        CacheShiftReal(ghHpHm_cache, NumPar, params, newResult);
        return newResult;
    }
}

double THDMcache::g_HH_HpHm(const double mHp2, const double mHh2, const double tanb, const double m12_2, const double bma, const double vev) const {
    int NumPar = 6;
    double params[] = {mHp2, mHh2, tanb, m12_2, bma, vev};

    int i = CacheCheckReal(g_HH_HpHm_cache, NumPar, params);
    if (i>=0) {
        return ( g_HH_HpHm_cache[NumPar][i] );
    } else {
        double newResult = (cos(bma)*(mHh2-2.0*mHp2)
                                    +((m12_2-mHh2*tanb+m12_2*tanb*tanb)
                                      *(2.0*cos(bma)*tanb+sin(bma)*(tanb*tanb-1.0)))/(tanb*tanb))/vev;
        CacheShiftReal(g_HH_HpHm_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_h_U(const double mHl, const double Mu, const double Mc, const double Mt) const {
    int NumPar = 4;
    double params[] = {mHl, Mu, Mc, Mt};

    int i = CacheCheck(I_h_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_U_cache[NumPar][i] );
    } else {
    	double TAUu=4.0*Mu*Mu/(mHl*mHl);
    	double TAUc=4.0*Mc*Mc/(mHl*mHl);
    	double TAUt=4.0*Mt*Mt/(mHl*mHl);
        gslpp::complex newResult = -(8./3.)*(TAUu*(1+(1-TAUu)*f_func(TAUu))
                         +TAUc*(1+(1-TAUc)*f_func(TAUc))+TAUt*(1+(1-TAUt)*f_func(TAUt)));
        CacheShift(I_h_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_HH_U(const double mHh2, const double Mc, const double Mt) const {
    int NumPar = 3;
    double params[] = {mHh2, Mc, Mt};

    int i = CacheCheck(I_HH_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mHh2;
    	double TAUt=4.0*Mt*Mt/mHh2;
        gslpp::complex newResult = -(8./3.)*(TAUc*(1+(1-TAUc)*f_func(TAUc))
                      +TAUt*(1+(1-TAUt)*f_func(TAUt)));
        CacheShift(I_HH_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_A_U(const double mA2, const double Mc, const double Mt) const {
    int NumPar = 3;
    double params[] = {mA2, Mc, Mt};

    int i = CacheCheck(I_A_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_A_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mA2;
    	double TAUt=4.0*Mt*Mt/mA2;
        gslpp::complex newResult = -(8./3.)*(TAUc*f_func(TAUc)+TAUt*f_func(TAUt));
        CacheShift(I_A_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_h_D(const double mHl, const double Md, const double Ms, const double Mb) const {
    int NumPar = 4;
    double params[] = {mHl, Md, Ms, Mb};

    int i = CacheCheck(I_h_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_D_cache[NumPar][i] );
    } else {
    	double TAUd=4.0*Md*Md/(mHl*mHl);
    	double TAUs=4.0*Ms*Ms/(mHl*mHl);
    	double TAUb=4.0*Mb*Mb/(mHl*mHl);
        gslpp::complex newResult = -(2./3.)*(TAUd*(1+(1-TAUd)*f_func(TAUd))
                         +TAUs*(1+(1-TAUs)*f_func(TAUs))+TAUb*(1+(1-TAUb)*f_func(TAUb)));
        CacheShift(I_h_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_HH_D(const double mHh2, const double Ms, const double Mb) const {
    int NumPar = 3;
    double params[] = {mHh2, Ms, Mb};

    int i = CacheCheck(I_HH_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mHh2;
    	double TAUb=4.0*Mb*Mb/mHh2;
        gslpp::complex newResult = -(2./3.)*(TAUs*(1+(1-TAUs)*f_func(TAUs))
                      +TAUb*(1+(1-TAUb)*f_func(TAUb)));
        CacheShift(I_HH_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_A_D(const double mA2, const double Ms, const double Mb) const {
    int NumPar = 3;
    double params[] = {mA2, Ms, Mb};

    int i = CacheCheck(I_A_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_A_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mA2;
    	double TAUb=4.0*Mb*Mb/mA2;
        gslpp::complex newResult = -(2./3.)*(TAUs*f_func(TAUs)+TAUb*f_func(TAUb));
        CacheShift(I_A_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_h_L(const double mHl, const double Me, const double Mmu, const double Mtau) const {
    int NumPar = 4;
    double params[] = {mHl, Me, Mmu, Mtau};

    int i = CacheCheck(I_h_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_L_cache[NumPar][i] );
    } else {
    	double TAUe=4.0*Me*Me/(mHl*mHl);
    	double TAUmu=4.0*Mmu*Mmu/(mHl*mHl);
    	double TAUtau=4.0*Mtau*Mtau/(mHl*mHl);
        gslpp::complex newResult = -2.0*(TAUe*(1+(1-TAUe)*f_func(TAUe))
                         +TAUmu*(1+(1-TAUmu)*f_func(TAUmu))
                         +TAUtau*(1+(1-TAUtau)*f_func(TAUtau)));
        CacheShift(I_h_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_HH_L(const double mHh2, const double Mmu, const double Mtau) const {
    int NumPar = 3;
    double params[] = {mHh2, Mmu, Mtau};

    int i = CacheCheck(I_HH_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mHh2;
    	double TAUtau=4.0*Mtau*Mtau/mHh2;
        gslpp::complex newResult = -2.0*(TAUmu*(1+(1-TAUmu)*f_func(TAUmu))+
                           TAUtau*(1+(1-TAUtau)*f_func(TAUtau)));
        CacheShift(I_HH_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_A_L(const double mA2, const double Mmu, const double Mtau) const {
    int NumPar = 3;
    double params[] = {mA2, Mmu, Mtau};

    int i = CacheCheck(I_A_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_A_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mA2;
    	double TAUtau=4.0*Mtau*Mtau/mA2;
        gslpp::complex newResult = -2.0*(TAUmu*f_func(TAUmu)+TAUtau*f_func(TAUtau));
        CacheShift(I_A_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_H_W(const double mH, const double MW) const {
    int NumPar = 2;
    double params[] = {mH, MW};

    int i = CacheCheck(I_H_W_cache, NumPar, params);
    if (i>=0) {
        return ( I_H_W_cache[NumPar][i] );
    } else {
        double TAUw=4.0*MW*MW/(mH*mH);
        gslpp::complex newResult = 2.0 + 3.0*TAUw + 3.0*TAUw*(2.0-TAUw)*f_func(TAUw);
        CacheShift(I_H_W_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::I_H_Hp(const double mHp2, const double mH) const {
    int NumPar = 2;
    double params[] = {mHp2, mH};

    int i = CacheCheck(I_H_Hp_cache, NumPar, params);
    if (i>=0) {
        return ( I_H_Hp_cache[NumPar][i] );
    } else {
        double TAUhp=4.0*mHp2/(mH*mH);
        gslpp::complex newResult = -TAUhp*(1.0-TAUhp*f_func(TAUhp));
        CacheShift(I_H_Hp_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_h_U(const double mHl, const double cW2, const double Mu, const double Mc, const double Mt, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl, cW2, Mu, Mc, Mt, MZ};

    int i = CacheCheck(A_h_U_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_U_cache[NumPar][i] );
    } else {
    	double TAUu=4.0*Mu*Mu/(mHl*mHl);
    	double TAUc=4.0*Mc*Mc/(mHl*mHl);
    	double TAUt=4.0*Mt*Mt/(mHl*mHl);
    	double LAMu=4.0*Mu*Mu/(MZ*MZ);
    	double LAMc=4.0*Mc*Mc/(MZ*MZ);
    	double LAMt=4.0*Mt*Mt/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -4.0*(1.0/2.0-4.0/3.0*sW2)*(Int1(TAUu,LAMu)+Int1(TAUc,LAMc)
                           +Int1(TAUt,LAMt)-Int2(TAUu,LAMu)-Int2(TAUc,LAMc)-Int2(TAUt,LAMt));
        CacheShift(A_h_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_HH_U(const double mHh2, const double cW2, const double Mc, const double Mt, const double MZ) const {
    int NumPar = 5;
    double params[] = {mHh2, cW2, Mc, Mt, MZ};

    int i = CacheCheck(A_HH_U_cache, NumPar, params);
    if (i>=0) {
        return ( A_HH_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mHh2;
    	double TAUt=4.0*Mt*Mt/mHh2;
    	double LAMc=4.0*Mc*Mc/(MZ*MZ);
    	double LAMt=4.0*Mt*Mt/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -4.0*(1.0/2.0-4.0/3.0*sW2)*(Int1(TAUc,LAMc)-Int2(TAUc,LAMc)
                                         +Int1(TAUt,LAMt)-Int2(TAUt,LAMt));
        CacheShift(A_HH_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_A_U(const double mA2, const double cW2, const double Mc, const double Mt, const double MZ) const {
    int NumPar = 5;
    double params[] = {mA2, cW2, Mc, Mt, MZ};

    int i = CacheCheck(A_A_U_cache, NumPar, params);
    if (i>=0) {
        return ( A_A_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mA2;
    	double TAUt=4.0*Mt*Mt/mA2;
    	double LAMc=4.0*Mc*Mc/(MZ*MZ);
    	double LAMt=4.0*Mt*Mt/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -4.0*(1.0/2.0-4.0/3.0*sW2)*(-Int2(TAUc,LAMc)-Int2(TAUt,LAMt))/sqrt(sW2*cW2);
        CacheShift(A_A_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_h_D(const double mHl, const double cW2, const double Md, const double Ms, const double Mb, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl, cW2, Md, Ms, Mb, MZ};

    int i = CacheCheck(A_h_D_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_D_cache[NumPar][i] );
    } else {
    	double TAUd=4.0*Md*Md/(mHl*mHl);
    	double TAUs=4.0*Ms*Ms/(mHl*mHl);
    	double TAUb=4.0*Mb*Mb/(mHl*mHl);
    	double LAMd=4.0*Md*Md/(MZ*MZ);
    	double LAMs=4.0*Ms*Ms/(MZ*MZ);
	double LAMb=4.0*Mb*Mb/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0/3.0*sW2)*(Int1(TAUd,LAMd)+Int1(TAUs,LAMs)
                           +Int1(TAUb,LAMb)-Int2(TAUd,LAMd)-Int2(TAUs,LAMs)-Int2(TAUb,LAMb));
        CacheShift(A_h_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_HH_D(const double mHh2, const double cW2, const double Ms, const double Mb, const double MZ) const {
    int NumPar = 5;
    double params[] = {mHh2, cW2, Ms, Mb, MZ};

    int i = CacheCheck(A_HH_D_cache, NumPar, params);
    if (i>=0) {
        return ( A_HH_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mHh2;
    	double TAUb=4.0*Mb*Mb/mHh2;
    	double LAMs=4.0*Ms*Ms/(MZ*MZ);
	double LAMb=4.0*Mb*Mb/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0/3.0*sW2)*(Int1(TAUs,LAMs)-Int2(TAUs,LAMs)
                                          +Int1(TAUb,LAMb)-Int2(TAUb,LAMb));
        CacheShift(A_HH_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_A_D(const double mA2, const double cW2, const double Ms, const double Mb, const double MZ) const {
    int NumPar = 5;
    double params[] = {mA2, cW2, Ms, Mb, MZ};

    int i = CacheCheck(A_A_D_cache, NumPar, params);
    if (i>=0) {
        return ( A_A_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mA2;
    	double TAUb=4.0*Mb*Mb/mA2;
    	double LAMs=4.0*Ms*Ms/(MZ*MZ);
	double LAMb=4.0*Mb*Mb/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0/3.0*sW2)*(-Int2(TAUs,LAMs)-Int2(TAUb,LAMb))/sqrt(sW2*cW2);
        CacheShift(A_A_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_h_L(const double mHl, const double cW2, const double Me, const double Mmu, const double Mtau, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl, cW2, Me, Mmu, Mtau, MZ};

    int i = CacheCheck(A_h_L_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_L_cache[NumPar][i] );
    } else {
    	double TAUe=4.0*Me*Me/(mHl*mHl);
    	double TAUmu=4.0*Mmu*Mmu/(mHl*mHl);
    	double TAUtau=4.0*Mtau*Mtau/(mHl*mHl);
    	double LAMe=4.0*Me*Me/(MZ*MZ);
    	double LAMmu=4.0*Mmu*Mmu/(MZ*MZ);
	double LAMtau=4.0*Mtau*Mtau/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0*sW2)*(Int1(TAUe,LAMe)+Int1(TAUmu,LAMmu)
                            +Int1(TAUtau,LAMtau)-Int2(TAUe,LAMe)-Int2(TAUmu,LAMmu)
                            -Int2(TAUtau,LAMtau));
        CacheShift(A_h_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_HH_L(const double mHh2, const double cW2, const double Mmu, const double Mtau, const double MZ) const {
    int NumPar = 5;
    double params[] = {mHh2, cW2, Mmu, Mtau, MZ};

    int i = CacheCheck(A_HH_L_cache, NumPar, params);
    if (i>=0) {
        return ( A_HH_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mHh2;
    	double TAUtau=4.0*Mtau*Mtau/mHh2;
    	double LAMmu=4.0*Mmu*Mmu/(MZ*MZ);
	double LAMtau=4.0*Mtau*Mtau/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0*sW2)*(Int1(TAUmu,LAMmu)-Int2(TAUmu,LAMmu)
                                      +Int1(TAUtau,LAMtau)-Int2(TAUtau,LAMtau));
        CacheShift(A_HH_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_A_L(const double mA2, const double cW2, const double Mmu, const double Mtau, const double MZ) const {
    int NumPar = 5;
    double params[] = {mA2, cW2, Mmu, Mtau, MZ};

    int i = CacheCheck(A_A_L_cache, NumPar, params);
    if (i>=0) {
        return ( A_A_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mA2;
    	double TAUtau=4.0*Mtau*Mtau/mA2;
    	double LAMmu=4.0*Mmu*Mmu/(MZ*MZ);
	double LAMtau=4.0*Mtau*Mtau/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = 2.0*(-1.0/2.0+2.0*sW2)*(-Int2(TAUmu,LAMmu)-Int2(TAUtau,LAMtau))/sqrt(sW2*cW2);
        CacheShift(A_A_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_H_W(const double mH, const double cW2, const double MW, const double MZ) const {
    int NumPar = 4;
    double params[] = {mH, cW2, MW, MZ};

    int i = CacheCheck(A_H_W_cache, NumPar, params);
    if (i>=0) {
        return ( A_H_W_cache[NumPar][i] );
    } else {
        double TAUw=4.0*MW*MW/(mH*mH);
        double LAMw=4.0*MW*MW/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -sqrt(cW2/sW2)*(4*(3-sW2/cW2)*Int2(TAUw,LAMw)
                            +((1.0+2.0/TAUw)*sW2/cW2-(5.0+2.0/TAUw))*Int1(TAUw,LAMw));
        CacheShift(A_H_W_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::A_H_Hp(const double mHp2, const double mH, const double cW2, const double MZ) const {
    int NumPar = 4;
    double params[] = {mHp2, mH, cW2, MZ};

    int i = CacheCheck(A_H_Hp_cache, NumPar, params);
    if (i>=0) {
        return ( A_H_Hp_cache[NumPar][i] );
    } else {
        double TAUhp=4.0*mHp2/(mH*mH);
        double LAMhp=4.0*mHp2/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = (1-2.0*sW2)/sqrt(cW2*sW2)*Int1(TAUhp,LAMhp);
        CacheShift(A_H_Hp_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex THDMcache::f_func(const double x) const{
    if(x<1) {
    gslpp::complex z = -gslpp::complex::i()*M_PI;
    return -pow(log((1+sqrt(1-x))/(1-sqrt(1-x)))+z,2)/4.0;
    }
    else {
        return pow(asin(sqrt(1.0/x)),2);
    }
}



gslpp::complex THDMcache::g_func(const double x) const{
    if(x<1) {
    gslpp::complex z = -gslpp::complex::i()*M_PI;
    gslpp::complex gs1 = sqrt(1-x)*(log((1+sqrt(1-x))/(1-sqrt(1-x)))+z)/2.0;
    return gs1;
    }
    else {
        gslpp::complex gg1 = sqrt(x-1)*asin(sqrt(1.0/x));
        return gg1;
    }
}



gslpp::complex THDMcache::Int1(const double tau, const double lambda) const{
    return tau*lambda/(tau-lambda)/2.0+tau*tau*lambda*lambda/((tau-lambda)
           *(tau-lambda))/2.0*(f_func(tau)-f_func(lambda))+tau*tau*lambda/((tau-lambda)
           *(tau-lambda))*(g_func(tau)-g_func(lambda));
    }



gslpp::complex THDMcache::Int2(const double tau, const double lambda) const{
    return -tau*lambda/(tau-lambda)/2.0*(f_func(tau)-f_func(lambda));
    }


int THDMcache::HSTheta (const double x) const{
    if(x<0) return 0.0;
    else return 1.0;
}


double THDMcache::KaellenFunction(const double a2, const double b2, const double c2) const{
    int NumPar = 3;
    double params[] = {a2, b2, c2};

    int i = CacheCheckReal(KaellenFunction_cache, NumPar, params);
    if (i>=0) {
        return ( KaellenFunction_cache[NumPar][i] );
    }
    else {
        double newResult = 0.0;
        double x = (a2-b2-c2)*(a2-b2-c2)-4.0*b2*c2;
        if(x>0) newResult = sqrt(std::fabs(x/a2))/2.0;        
        CacheShiftReal(KaellenFunction_cache, NumPar, params, newResult);
        return newResult;
    }
}


double THDMcache::cW2THDM(const double c02) const{
    return c02;
}



double THDMcache::MWTHDM(const double MW) const{
    return MW;
}



void THDMcache::computeSignalStrengthQuantities()
{
    double sW2=1.0-cW2;
    double sin_ba=sin(bma);
    double sinb=tanb/sqrt(1.0+tanb*tanb);
    double cosb=1.0/sqrt(1.0+tanb*tanb);
    double sina=sinb*cos(bma)-cosb*sin(bma);
    double cosa=cosb*cos(bma)+sinb*sin(bma);

    //The Standard Model h branching ratios

    BrSM_htobb = 5.77e-1;
    BrSM_htotautau = 6.32e-2;
    BrSM_htogaga = 2.28e-3;
    double BrSM_htoWW = 2.15e-1;
    double BrSM_htoZZ = 2.64e-2;
    double BrSM_htogg = 8.57e-2;
    double BrSM_htoZga = 1.54e-3;
    double BrSM_htocc = 2.91e-2;

    //The ggH cross section in the SM.
    double SigmaggF = myTHDM->computeSigmaggH(8.0);
    //The square of the top-quark contribution to the ggH cross section in the SM
    double Sigmaggh_tt = myTHDM->computeSigmaggH_tt(8.0);
    //The square of the bottom-quark contribution to the ggH cross section in the SM
    double Sigmaggh_bb = myTHDM->computeSigmaggH_bb(8.0);
    //The ttH production cross section in the SM
    double Sigmatth = myTHDM->computeSigmattH(8.0);

    /* r_ii is the ratio of the squared 2HDM vertex coupling of h to
     * the particle i and the respective squared SM coupling.*/
    rh_QuQu=cosa*cosa/(sinb*sinb);
    rh_VV=sin_ba*sin_ba;
    rh_QdQd=0.0;//It depends on the modelType
    rh_ll=0.0;//It depends on the modelType
    rh_gg=0.0;//It depends on the modelType 

    //Calulation of rh_gg, rh_QdQd, rh_ll, rh_gaga, rh_Zga (depending on the model type): START

    //rh_gaga formula = abs(I_h_F+I_h_W+I_h_Hp)^2 / abs(I_hSM_F+I_hSM_W)^2

    gslpp::complex I_h_F=0.0;//It depends on the modelType
    gslpp::complex fermU=I_h_U(mHl,Mu,Mc,Mt);
    gslpp::complex fermD=I_h_D(mHl,Md,Ms,Mb);
    gslpp::complex fermL=I_h_L(mHl,Me,Mmu,Mtau);
    gslpp::complex I_hSM_W=I_H_W(mHl,MW);
    gslpp::complex I_h_W=sin_ba*I_hSM_W;
    gslpp::complex I_h_Hp=I_H_Hp(mHp2,mHl)*ghHpHm(mHp2,tanb,m12_2,bma,mHl,vev)*vev/(2.0*mHp2);

    double ABSgagaTHDM=0.0;
    double ABSgagaSM=0.0;

    //rh_Zga formula = abs(A_h_F+A_h_W+A_h_Hp)^2 / abs(A_hSM_F+A_hSM_W)^2

    gslpp::complex A_h_F = 0.0;//It depends on the modelType
    gslpp::complex A_h_Ux = A_h_U(mHl,cW2,Mu,Mc,Mt,MZ);
    gslpp::complex A_h_Dx = A_h_D(mHl,cW2,Md,Ms,Mb,MZ);
    gslpp::complex A_h_Lx  = A_h_L(mHl,cW2,Me,Mmu,Mtau,MZ);
    gslpp::complex A_hSM_W = A_H_W(mHl,cW2,MW,MZ);
    gslpp::complex A_h_W = sin_ba*A_hSM_W;
    gslpp::complex A_h_Hp = A_H_Hp(mHp2,mHl,cW2,MZ)*ghHpHm(mHp2,tanb,m12_2,bma,mHl,vev)*vev/(2.0*mHp2);

    double ABSZgaTHDM=0.0;
    double ABSZgaSM=0.0;

    if( modelflag == "type1" ) {
        rh_gg=cosa/sinb*cosa/sinb;
        rh_QdQd=cosa/sinb*cosa/sinb;
        rh_ll=cosa/sinb*cosa/sinb;
        I_h_F=cosa/sinb*(fermU+fermD+fermL);
        A_h_F = cosa/sinb*(A_h_Ux+A_h_Dx+A_h_Lx)/sqrt(sW2*cW2);
    }
    else if( modelflag == "type2" ) {
        rh_gg=-cosa/sinb*sina/cosb+(cosa/sinb+sina/cosb)
             *(Sigmaggh_tt*cosa/sinb+Sigmaggh_bb*sina/cosb)/SigmaggF;
        rh_QdQd=sina/cosb*sina/cosb;
        rh_ll=sina/cosb*sina/cosb;
        I_h_F=cosa/sinb*fermU -sina/cosb*(fermD+fermL);
        A_h_F = (cosa/sinb*A_h_Ux-sina/cosb*(A_h_Dx+A_h_Lx))/sqrt(sW2*cW2);
    }
    else if( modelflag == "typeX" ) {
        rh_gg=cosa/sinb*cosa/sinb;
        rh_QdQd=cosa/sinb*cosa/sinb;
        rh_ll=sina/cosb*sina/cosb;
        I_h_F = cosa/sinb*(fermU+fermD) -sina/cosb*fermL;
        A_h_F = (cosa/sinb*(A_h_Ux+A_h_Dx)-sina/cosb*A_h_Lx)/sqrt(sW2*cW2);
    }
    else if( modelflag == "typeY" ) {
        rh_gg=-cosa/sinb*sina/cosb+(cosa/sinb+sina/cosb)
             *(Sigmaggh_tt*cosa/sinb+Sigmaggh_bb*sina/cosb)/SigmaggF;
        rh_QdQd=sina/cosb*sina/cosb;
        rh_ll=cosa/sinb*cosa/sinb;
        I_h_F = cosa/sinb*(fermU+fermL) -sina/cosb*fermD;
        A_h_F = (cosa/sinb*(A_h_Ux+A_h_Lx)-sina/cosb*A_h_Dx)/sqrt(sW2*cW2);
    }
    else {
        throw std::runtime_error("modelflag can be only any of \"type1\", \"type2\", \"typeX\" or \"typeY\"");
    }

    ABSgagaTHDM=(I_h_F+I_h_W+I_h_Hp).abs2();
    ABSgagaSM=(fermU+fermL+fermD+I_hSM_W).abs2();
    rh_gaga=ABSgagaTHDM/ABSgagaSM;

    ABSZgaTHDM=(A_h_F+A_h_W+A_h_Hp).abs2();
    ABSZgaSM=((A_h_Ux+A_h_Lx+A_h_Dx)/sqrt(sW2*cW2)+A_hSM_W).abs2();
    rh_Zga=ABSZgaTHDM/ABSZgaSM;
    //Calulation of rh_gg, rh_QdQd, rh_ll, rh_gaga, rh_Zga (they depend on the model type): END

    /* ggF_tth is the ratio of the THDM and SM cross sections for ggF or tth production */
    ggF_tth = (SigmaggF*rh_gg + Sigmatth*rh_QuQu)/(SigmaggF + Sigmatth);
    /* VBF_Vh is the ratio of the THDM and SM cross sections for VBF or Vh production */
    VBF_Vh = rh_VV;

    sumModBRs = rh_QdQd*BrSM_htobb + rh_VV*(BrSM_htoWW+BrSM_htoZZ) + rh_ll*BrSM_htotautau +
          rh_gaga*BrSM_htogaga + rh_gg*BrSM_htogg + rh_Zga*BrSM_htoZga + rh_QuQu*BrSM_htocc;

    Gamma_h = sumModBRs*myTHDM->computeGammaHTotal();
    
    THDM_BR_h_bb = rh_QdQd*BrSM_htobb/sumModBRs;
    THDM_BR_h_gaga = rh_gaga*BrSM_htogaga/sumModBRs;
    THDM_BR_h_tautau = rh_ll*BrSM_htotautau/sumModBRs;
}

void THDMcache::computeHHquantities()
{
    double GF=1/(sqrt(2.0)*vev*vev);
    double sW2=1.0-cW2;
    double mHh=sqrt(mHh2);
    double sin_ba=sin(bma);
    double sinb=tanb/sqrt(1.0+tanb*tanb);
    double cosb=1.0/sqrt(1.0+tanb*tanb);
    double sina=sinb*cos(bma)-cosb*sin(bma);
    double cosa=cosb*cos(bma)+sinb*sin(bma);
    double cos_2b=cosb*cosb-sinb*sinb;
    double cos_ba=cos(bma);

    //These cross sections ratios are necessary for rHH_gg
    //SM gg -> H production cross section ratio at 8 TeV, top loop only over total
    double rSigmaggH_t = ip_csr_ggH_t(mHh);
    //SM gg -> H production cross section ratio at 8 TeV, bottom loop only over total
    double rSigmaggH_b = ip_csr_ggH_b(mHh);

    /* r_ii is the ratio between the squared 2HDM vertex coupling of the heavy Higgs to
     * the particle i and the corresponding coupling of the SM Higgs boson.*/
    double rHH_QuQu=sina/sinb*sina/sinb;
    double rHH_QdQd=0.0;//It depends on the modelType
    double rHH_ll=0.0;//It depends on the modelType
    rHH_gg=0.0;//It depends on the modelType
    double rHH_VV=cos_ba*cos_ba;

    /*Calulation of rHH_QdQd, rHH_ll, rHH_gg, Gamma_Hgaga, Gamma_HZga, Gamma_Hgg
     * (they depend on the model type): START*/

    /*Gamma_Hgaga and Gamma_HZga expressions can be found in
     "The Higgs Hunter's Guide", Appendix C and in arXiv:0902.4665v3, Appendix A;
     *Gamma_Hgg expression can be found in arXiv:0902.4665v3, Appendix A*/

    /*I_HH_F, I_HH_W and I_HH_Hp are needed for Gamma_Hgaga;
     * their expressions can be found in "The Higgs Hunter's Guide", Appendix C, C.4*/
    gslpp::complex I_HH_F=0.0;//It depends on the modelType
    gslpp::complex I_HH_Ux=I_HH_U(mHh2,Mc,Mt);
    gslpp::complex I_HH_Dx=I_HH_D(mHh2,Ms,Mb);
    gslpp::complex I_HH_Lx=I_HH_L(mHh2,Mmu,Mtau);
    gslpp::complex I_HH_W=cos_ba*I_H_W(mHh,MW);
    /* g_HH_HpHm is the coupling of the heavy Higgs boson to Hp and Hm; its
     * expression can be found in arXiv:1403.1264v2, formula 5*/
    gslpp::complex I_HH_Hp=I_H_Hp(mHp2,mHh)*g_HH_HpHm(mHp2,mHh2,tanb,m12_2,bma,vev)*vev/(2.0*mHp2);

    /*A_HH_F, A_HH_W and A_HH_Hp are needed for Gamma_HZga;
     * their expressions can be found in "The Higgs Hunter's Guide", Appendix C, C.12*/
    gslpp::complex A_HH_F = 0.0;//It depends on the modelType
    gslpp::complex A_HH_Ux = A_HH_U(mHh2,cW2,Mc,Mt,MZ);
    gslpp::complex A_HH_Dx = A_HH_D(mHh2,cW2,Ms,Mb,MZ);
    gslpp::complex A_HH_Lx = A_HH_L(mHh2,cW2,Mmu,Mtau,MZ);
    /*A_HH_W expression can be found in "The Higgs Hunter's Guide", Appendix C, C.13*/
    gslpp::complex A_HH_W = cos_ba*A_H_W(mHh,cW2,MW,MZ);
    /*A_HH_Hp expression can be found in "The Higgs Hunter's Guide", Appendix C, C.14*/
    gslpp::complex A_HH_Hp= A_H_Hp(mHp2,mHh,cW2,MZ)*g_HH_HpHm(mHp2,mHh2,tanb,m12_2,bma,vev)*vev/(2.0*mHp2);
    
    if( modelflag == "type1" ) {
        rHH_gg=sina/sinb*sina/sinb;
        rHH_QdQd=sina/sinb*sina/sinb;
        rHH_ll=sina/sinb*sina/sinb;
        I_HH_F=sina/sinb*(I_HH_Ux+I_HH_Dx+I_HH_Lx);
        A_HH_F = sina/sinb*(A_HH_Ux+A_HH_Dx+A_HH_Lx)/sqrt(sW2*cW2);
    }
    else if( modelflag == "type2" ) {
        rHH_gg=sina/sinb*cosa/cosb+rSigmaggH_t*sina/sinb*(sina/sinb-cosa/cosb)
             +rSigmaggH_b*cosa/cosb*(cosa/cosb-sina/sinb);
        rHH_QdQd=cosa/cosb*cosa/cosb;
        rHH_ll=cosa/cosb*cosa/cosb;
        I_HH_F=sina/sinb*I_HH_Ux+cosa/cosb*(I_HH_Dx+I_HH_Lx);
        A_HH_F = (sina/sinb*A_HH_Ux+cosa/cosb*(A_HH_Dx+A_HH_Lx))/sqrt(sW2*cW2);
    }
    else if( modelflag == "typeX" ) {
        rHH_gg=sina/sinb*sina/sinb;
        rHH_QdQd=sina/sinb*sina/sinb;
        rHH_ll=cosa/cosb*cosa/cosb;
        I_HH_F=sina/sinb*(I_HH_Ux+I_HH_Dx)+cosa/cosb*I_HH_Lx;
        A_HH_F = (sina/sinb*(A_HH_Ux+A_HH_Dx)+cosa/cosb*A_HH_Lx)/sqrt(sW2*cW2);
    }
    else if( modelflag == "typeY" ) {
        rHH_gg=sina/sinb*cosa/cosb+rSigmaggH_t*sina/sinb*(sina/sinb-cosa/cosb)
             +rSigmaggH_b*cosa/cosb*(cosa/cosb-sina/sinb);
        rHH_QdQd=cosa/cosb*cosa/cosb;
        rHH_ll=sina/sinb*sina/sinb;
        I_HH_F=sina/sinb*(I_HH_Ux+I_HH_Lx)+cosa/cosb*I_HH_Dx;
        A_HH_F = (sina/sinb*(A_HH_Ux+A_HH_Lx)+cosa/cosb*A_HH_Dx)/sqrt(sW2*cW2);
    }
    else {
        throw std::runtime_error("modelflag can be only any of \"type1\", \"type2\", \"typeX\" or \"typeY\"");
    }

    /*Gamma_Hgaga expression can be found in arXiv:0902.4665v3, Appendix A, A.8*/
    double Gamma_Hgaga=GF*Ale*Ale*mHh*mHh*mHh/(sqrt(2)*128.0*M_PI*M_PI*M_PI)
                *(I_HH_F+I_HH_W+I_HH_Hp).abs()*(I_HH_F+I_HH_W+I_HH_Hp).abs();

    /*Gamma_HZga expression can be found in arXiv:0902.4665v3, Appendix A, A.9*/
    double Gamma_HZga=GF*Ale*Ale*mHh*mHh*mHh/(sqrt(2)*64.0*M_PI*M_PI*M_PI)
               *(1.0-MZ*MZ/(mHh*mHh))*(1.0-MZ*MZ/(mHh*mHh))*(1.0-MZ*MZ/(mHh*mHh))
               *(A_HH_F+A_HH_W+A_HH_Hp).abs()*(A_HH_F+A_HH_W+A_HH_Hp).abs();

    /*Gamma_Hgg expression can be found in arXiv:0902.4665v3, Appendix A, A.10 or in the Higgs Hunter's Guide (2.30); relative coupling see above*/
    double Gamma_Hgg=rHH_gg*GF*Als*Als*mHh*mHh*mHh/(sqrt(2)*16.0*M_PI*M_PI*M_PI)
                     *(9.0/4.0)*(I_HH_Ux/4.0+I_HH_Dx).abs2();

    /*Calulation of rHH_QdQd, rHH_ll, rHH_gg, Gamma_Hgaga, Gamma_HZga, Gamma_Hgg: END*/

    double SigmaggF_H=ip_cs_ggtoH_8(mHh)*rHH_gg;
    double SigmabbF_H=ip_cs_pptobbH_8(mHh)*rHH_QdQd;
    double SigmaVBF_H=ip_cs_VBFtoH_8(mHh)*rHH_VV;
    double SigmattF_H=ip_cs_pptottH_8(mHh)*rHH_QuQu;
    double SigmaVH_H=(ip_cs_WtoWH_8(mHh)+ip_cs_ZtoZH_8(mHh))*rHH_VV;
    double SigmaTotSM_H = 0.000000001;
    if (mHh>=20. && mHh <=1000.) {
            SigmaTotSM_H=ip_cs_ggtoH_8(mHh)+ip_cs_VBFtoH_8(mHh)+ip_cs_WtoWH_8(mHh)+ip_cs_ZtoZH_8(mHh)+ip_cs_pptottH_8(mHh)+ip_cs_pptobbH_8(mHh);
    }

    double SigmaSum = SigmaggF_H + SigmaVBF_H + SigmaVH_H + SigmattF_H + SigmabbF_H;

    double BrSM_Htott=ip_Br_HPtott(mHh);
    double BrSM_Htocc=ip_Br_HPtocc(mHh);
    double BrSM_Htobb=ip_Br_HPtobb(mHh);
    double BrSM_Htotautau=ip_Br_HPtotautau(mHh);
    double BrSM_Htomumu=ip_Br_HPtomumu(mHh);
    double BrSM_HtoWW =ip_Br_HPtoWW(mHh);
    double BrSM_HtoZZ =ip_Br_HPtoZZ(mHh);

    double GammaHtotSM=ip_GammaHPtotSM(mHh);

    double GammaHhh=HSTheta(mHh - 2.0*mHl)*sqrt(std::fabs(1.0 - (4.0*mHl*mHl)/mHh2))
                    *std::fabs((cos_ba*cos_ba/(4.0*sinb*cosb*sinb*cosb)
                    *pow(m12_2 + mHh2*cosa*sina + (2.0*mHl*mHl - 3.0*m12_2/(sinb*cosb))
                    *sina*cosa,2))/(vev*vev))/(8.0*mHh*M_PI);

    double GammaHHpHm=HSTheta(mHh - 2.0*sqrt(mHp2))*sqrt(std::fabs(1.0 - (4.0*mHp2)/mHh2))
                      *std::fabs(pow(cos_ba*(mHh2 + 2.0*mHp2 - 2.0*m12_2/sinb/cosb)
                                -cos_2b/(sinb*cosb)*(mHh2 - m12_2/sinb/cosb)*sin_ba,2)/(vev*vev))
                      /(16.0*mHh*M_PI);

    double GammaHAA=HSTheta(mHh-2.0*sqrt(mA2))*sqrt(std::fabs(1.0 - (4.0*mA2)/mHh2))
                    *std::fabs(pow(cos_ba*(2.0*mA2 + mHh2 - 2.0*m12_2/sinb/cosb)
                    - cos_2b/(sinb*cosb)*(mHh2 - m12_2/sinb/cosb)*sin_ba,2)/(vev*vev))
                    /(32.0*mHh*M_PI);

    double GammaHAZ=HSTheta(mHh-sqrt(mA2)-MZ)*pow(KaellenFunction(mHh2,MZ*MZ,mA2),3)
                    *sin_ba*sin_ba/(2.0*M_PI*vev*vev);

    double GammaHHpW=HSTheta(mHh-sqrt(mHp2)-MW)*pow(KaellenFunction(mHh2,MW*MW,mHp2),3)*sin_ba*sin_ba/(M_PI*vev*vev);

    GammaHtot= ((BrSM_Htott+BrSM_Htocc)*rHH_QuQu
                    +BrSM_Htobb*rHH_QdQd
                    +(BrSM_Htotautau+BrSM_Htomumu)*rHH_ll
                    +(BrSM_HtoWW+BrSM_HtoZZ)*rHH_VV)*GammaHtotSM
               +Gamma_Hgaga+Gamma_HZga+Gamma_Hgg
               +GammaHhh+GammaHHpHm+GammaHAA+GammaHAZ+GammaHHpW;
    
    double Br_Htott=BrSM_Htott*rHH_QuQu*GammaHtotSM/GammaHtot;
    double Br_Htobb=BrSM_Htobb*rHH_QdQd*GammaHtotSM/GammaHtot;
    double Br_Htotautau=BrSM_Htotautau*rHH_ll*GammaHtotSM/GammaHtot;
    double Br_HtoWW=BrSM_HtoWW*rHH_VV*GammaHtotSM/GammaHtot;
    double Br_HtoZZ=BrSM_HtoZZ*rHH_VV*GammaHtotSM/GammaHtot;
    double Br_Htogaga=Gamma_Hgaga/GammaHtot;
    Br_Htohh=GammaHhh/GammaHtot;
    Br_HtoAA=GammaHAA/GammaHtot;
    Br_HtoHpHm=GammaHHpHm/GammaHtot;
    Br_HtoAZ=GammaHAZ/GammaHtot;
    Br_HtoHpW=GammaHHpW/GammaHtot;

    //Theoretical expressions for the Heavy Higgs cross sections times branching ratios

    ggF_H_tautau_TH=SigmaggF_H*Br_Htotautau;
    bbF_H_tautau_TH=SigmabbF_H*Br_Htotautau;
    pp_H_gaga_TH=SigmaSum*Br_Htogaga;
    ggF_H_gaga_TH=SigmaggF_H*Br_Htogaga;
    mu_pp_H_VV_TH=SigmaSum/SigmaTotSM_H*rHH_VV*GammaHtotSM/GammaHtot;
    ggF_H_ZZ_TH=SigmaggF_H*Br_HtoZZ;
    VBF_H_ZZ_TH=SigmaVBF_H*Br_HtoZZ;
    ggF_H_WW_TH=SigmaggF_H*Br_HtoWW;
    VBF_H_WW_TH=SigmaVBF_H*Br_HtoWW;
    ggF_H_hh_TH=SigmaggF_H*Br_Htohh;
    pp_H_hh_TH=SigmaSum*Br_Htohh;
    ggF_H_hh_bbtautau_TH=SigmaggF_H*Br_Htohh*THDM_BR_h_bb*THDM_BR_h_tautau;
    pp_H_hh_bbbb_TH=SigmaSum*Br_Htohh*THDM_BR_h_bb*THDM_BR_h_bb;
    pp_H_hh_gagabb_TH=SigmaSum*Br_Htohh*THDM_BR_h_gaga*THDM_BR_h_bb;
    ggF_H_tt_TH=SigmaggF_H*Br_Htott;
    bbF_H_bb_TH=SigmabbF_H*Br_Htobb;
    
    //Ratios of theoretical Heavy Higgs cross sections and experimental upper limits

    THoEX_ggF_H_tautau_ATLAS=0.0;
    R_ggF_H_tautau_ATLAS=0.0;
    THoEX_ggF_H_tautau_CMS=0.0;
    R_ggF_H_tautau_CMS=0.0;
    THoEX_bbF_H_tautau_ATLAS=0.0;
    R_bbF_H_tautau_ATLAS=0.0;
    THoEX_bbF_H_tautau_CMS=0.0;
    R_bbF_H_tautau_CMS=0.0;
    THoEX_pp_H_gaga_ATLAS=0.0;
    R_pp_H_gaga_ATLAS=0.0;
    THoEX_ggF_H_gaga_CMS=0.0;
    R_ggF_H_gaga_CMS=0.0;
    THoEX_mu_pp_H_VV_CMS=0.0;
    R_mu_pp_H_VV_CMS=0.0;
    THoEX_ggF_H_WW_ATLAS=0.0;
    R_ggF_H_WW_ATLAS=0.0;
    THoEX_VBF_H_WW_ATLAS=0.0;
    R_VBF_H_WW_ATLAS=0.0;
    THoEX_ggF_H_ZZ_ATLAS=0.0;
    R_ggF_H_ZZ_ATLAS=0.0;
    THoEX_VBF_H_ZZ_ATLAS=0.0;
    R_VBF_H_ZZ_ATLAS=0.0;
    THoEX_ggF_H_hh_ATLAS=0.0;
    R_ggF_H_hh_ATLAS=0.0;
    THoEX_ggF_H_hh_bbtautau_CMS=0.0;
    R_ggF_H_hh_bbtautau_CMS=0.0;
    THoEX_pp_H_hh_bbbb_CMS=0.0;
    R_pp_H_hh_bbbb_CMS=0.0;
    THoEX_pp_H_hh_gagabb_CMS=0.0;
    R_pp_H_hh_gagabb_CMS=0.0;
    THoEX_ggF_H_tt_ATLAS=0.0;
    R_ggF_H_tt_ATLAS=0.0;
    THoEX_bbF_H_bb_CMS=0.0;
    R_bbF_H_bb_CMS=0.0;

    //95% to 1 sigma conversion factor, roughly sqrt(3.84)
    double nftos=1.95996398454;

    if(mHh>=65.0 && mHh<90.0)
    {
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
    }
    else if(mHh>=90.0 && mHh<100.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
    }
    else if(mHh>=100.0 && mHh<140.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=140.0 && mHh<145.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=145.0 && mHh<150.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=150.0 && mHh<260.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_gaga_CMS=ggF_H_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mHh);
        R_ggF_H_gaga_CMS=(1+(ggF_H_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mHh))/ip_ex_ggF_phi_gaga_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=260.0 && mHh<270.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_gaga_CMS=ggF_H_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mHh);
        R_ggF_H_gaga_CMS=(1+(ggF_H_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mHh))/ip_ex_ggF_phi_gaga_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_bbtautau_CMS=ggF_H_hh_bbtautau_TH/ip_ex_ggF_H_hh_bbtautau_CMS(mHh);
        R_ggF_H_hh_bbtautau_CMS=(1+(ggF_H_hh_bbtautau_TH-ip_ex_ggF_H_hh_bbtautau_CMS(mHh))/ip_ex_ggF_H_hh_bbtautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=270.0 && mHh<300.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_gaga_CMS=ggF_H_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mHh);
        R_ggF_H_gaga_CMS=(1+(ggF_H_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mHh))/ip_ex_ggF_phi_gaga_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_bbtautau_CMS=ggF_H_hh_bbtautau_TH/ip_ex_ggF_H_hh_bbtautau_CMS(mHh);
        R_ggF_H_hh_bbtautau_CMS=(1+(ggF_H_hh_bbtautau_TH-ip_ex_ggF_H_hh_bbtautau_CMS(mHh))/ip_ex_ggF_H_hh_bbtautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=300.0 && mHh<350.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_gaga_CMS=ggF_H_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mHh);
        R_ggF_H_gaga_CMS=(1+(ggF_H_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mHh))/ip_ex_ggF_phi_gaga_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_bbtautau_CMS=ggF_H_hh_bbtautau_TH/ip_ex_ggF_H_hh_bbtautau_CMS(mHh);
        R_ggF_H_hh_bbtautau_CMS=(1+(ggF_H_hh_bbtautau_TH-ip_ex_ggF_H_hh_bbtautau_CMS(mHh))/ip_ex_ggF_H_hh_bbtautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=350.0 && mHh<400.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_gaga_CMS=ggF_H_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mHh);
        R_ggF_H_gaga_CMS=(1+(ggF_H_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mHh))/ip_ex_ggF_phi_gaga_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=400.0 && mHh<600.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_gaga_ATLAS=pp_H_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mHh);
        R_pp_H_gaga_ATLAS=(1+(pp_H_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mHh))/ip_ex_pp_phi_gaga_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_gaga_CMS=ggF_H_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mHh);
        R_ggF_H_gaga_CMS=(1+(ggF_H_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mHh))/ip_ex_ggF_phi_gaga_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_tt_ATLAS=ggF_H_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mHh);
        R_ggF_H_tt_ATLAS=(1+(ggF_H_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mHh))/ip_ex_ggF_phi_tt_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=600.0 && mHh<850.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_gaga_CMS=ggF_H_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mHh);
        R_ggF_H_gaga_CMS=(1+(ggF_H_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mHh))/ip_ex_ggF_phi_gaga_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_tt_ATLAS=ggF_H_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mHh);
        R_ggF_H_tt_ATLAS=(1+(ggF_H_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mHh))/ip_ex_ggF_phi_tt_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=850.0 && mHh<900.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_tt_ATLAS=ggF_H_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mHh);
        R_ggF_H_tt_ATLAS=(1+(ggF_H_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mHh))/ip_ex_ggF_phi_tt_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_bb_CMS=bbF_H_bb_TH/ip_ex_bbF_phi_bb_CMS(mHh);
        R_bbF_H_bb_CMS=(1+(bbF_H_bb_TH-ip_ex_bbF_phi_bb_CMS(mHh))/ip_ex_bbF_phi_bb_CMS_e(mHh) ) * nftos;
    }
    else if(mHh>=900.0 && mHh<1000.0)
    {
        THoEX_ggF_H_tautau_ATLAS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mHh);
        R_ggF_H_tautau_ATLAS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mHh))/ip_ex_ggF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tautau_CMS=ggF_H_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mHh);
        R_ggF_H_tautau_CMS=(1+(ggF_H_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mHh))/ip_ex_ggF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_ATLAS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mHh);
        R_bbF_H_tautau_ATLAS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mHh))/ip_ex_bbF_phi_tautau_ATLAS_e(mHh) ) * nftos;
        THoEX_bbF_H_tautau_CMS=bbF_H_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mHh);
        R_bbF_H_tautau_CMS=(1+(bbF_H_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mHh))/ip_ex_bbF_phi_tautau_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_ZZ_ATLAS=ggF_H_ZZ_TH/ip_ex_ggF_H_ZZ_ATLAS(mHh);
        R_ggF_H_ZZ_ATLAS=(1+(ggF_H_ZZ_TH-ip_ex_ggF_H_ZZ_ATLAS(mHh))/ip_ex_ggF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_ZZ_ATLAS=VBF_H_ZZ_TH/ip_ex_VBF_H_ZZ_ATLAS(mHh);
        R_VBF_H_ZZ_ATLAS=(1+(VBF_H_ZZ_TH-ip_ex_VBF_H_ZZ_ATLAS(mHh))/ip_ex_VBF_H_ZZ_ATLAS_e(mHh) ) * nftos;
        THoEX_mu_pp_H_VV_CMS=mu_pp_H_VV_TH/ip_ex_mu_pp_H_VV_CMS(mHh);
        R_mu_pp_H_VV_CMS=(1+(mu_pp_H_VV_TH-ip_ex_mu_pp_H_VV_CMS(mHh))/ip_ex_mu_pp_H_VV_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_hh_ATLAS=ggF_H_hh_TH/ip_ex_ggF_H_hh_ATLAS(mHh);
        R_ggF_H_hh_ATLAS=(1+(ggF_H_hh_TH-ip_ex_ggF_H_hh_ATLAS(mHh))/ip_ex_ggF_H_hh_ATLAS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_tt_ATLAS=ggF_H_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mHh);
        R_ggF_H_tt_ATLAS=(1+(ggF_H_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mHh))/ip_ex_ggF_phi_tt_ATLAS_e(mHh) ) * nftos;
    }
    else if(mHh>=1000.0 && mHh<1100.0)
    {
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_bbbb_CMS=pp_H_hh_bbbb_TH/ip_ex_pp_phi_hh_bbbb_CMS(mHh);
        R_pp_H_hh_bbbb_CMS=(1+(pp_H_hh_bbbb_TH-ip_ex_pp_phi_hh_bbbb_CMS(mHh))/ip_ex_pp_phi_hh_bbbb_CMS_e(mHh) ) * nftos;
        THoEX_pp_H_hh_gagabb_CMS=pp_H_hh_gagabb_TH/ip_ex_pp_phi_hh_gagabb_CMS(mHh);
        R_pp_H_hh_gagabb_CMS=(1+(pp_H_hh_gagabb_TH-ip_ex_pp_phi_hh_gagabb_CMS(mHh))/ip_ex_pp_phi_hh_gagabb_CMS_e(mHh) ) * nftos;
        THoEX_ggF_H_tt_ATLAS=ggF_H_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mHh);
        R_ggF_H_tt_ATLAS=(1+(ggF_H_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mHh))/ip_ex_ggF_phi_tt_ATLAS_e(mHh) ) * nftos;
    }
    else if(mHh>=1100.0 && mHh<1500.0)
    {
        THoEX_ggF_H_WW_ATLAS=ggF_H_WW_TH/ip_ex_ggF_H_WW_ATLAS(mHh);
        R_ggF_H_WW_ATLAS=(1+(ggF_H_WW_TH-ip_ex_ggF_H_WW_ATLAS(mHh))/ip_ex_ggF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_VBF_H_WW_ATLAS=VBF_H_WW_TH/ip_ex_VBF_H_WW_ATLAS(mHh);
        R_VBF_H_WW_ATLAS=(1+(VBF_H_WW_TH-ip_ex_VBF_H_WW_ATLAS(mHh))/ip_ex_VBF_H_WW_ATLAS_e(mHh) ) * nftos;
        THoEX_ggF_H_tt_ATLAS=ggF_H_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mHh);
        R_ggF_H_tt_ATLAS=(1+(ggF_H_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mHh))/ip_ex_ggF_phi_tt_ATLAS_e(mHh) ) * nftos;
    }
    else if(mHh>=1500.0 && mHh<3000.0)
    {
        THoEX_ggF_H_tt_ATLAS=ggF_H_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mHh);
        R_ggF_H_tt_ATLAS=(1+(ggF_H_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mHh))/ip_ex_ggF_phi_tt_ATLAS_e(mHh) ) * nftos;
    }
}

void THDMcache::computeAquantities()
{
    double GF=1/(sqrt(2.0)*vev*vev);
    double mHh=sqrt(mHh2);
    double mA=sqrt(mA2);
    double sinb=tanb/sqrt(1.0+tanb*tanb);
    double cosb=1.0/sqrt(1.0+tanb*tanb);
    double mHp=sqrt(mHp2);
    double sin_ba=sin(bma);
    double cos_ba=cos(bma);

    //These cross sections ratios are necessary for rA_gg
    //gg -> A production cross section ratio at 8 TeV, top loop only over total
    double rSigmaggA_t = ip_csr_ggA_t(mA);
    //gg -> A production cross section ratio at 8 TeV, bottom loop only over total
    double rSigmaggA_b = ip_csr_ggA_b(mA);

    /* r_ii is the ratio between the squared 2HDM vertex coupling of the CP-odd
     * Higgs to the particle i and the corresponding coupling of the SM Higgs boson.*/
    double rA_QuQu=(cosb*cosb)/(sinb*sinb);
    double rA_QdQd=0.0;//It depends on the modelType
    double rA_ll=0.0;//It depends on the modelType
    rA_gg=0.0;//It depends on the modelType

    /*Calulation of rA_QdQd, rA_ll, rA_gg, Gamma_Agaga, Gamma_AZga, Gamma_Agg
     * (they depend on the model type): START*/

    /*Gamma_Agaga and Gamma_AZga expressions can be found in
     "The Higgs Hunter's Guide", Appendix C and in arXiv:0902.4665v3, Appendix A;
     *Gamma_Agg expression can be found in arXiv:0902.4665v3, Appendix A*/

    /*I_A_F is needed for Gamma_Agaga;
     * The expression can be found in "The Higgs Hunter's Guide", Appendix C, C.4*/
    gslpp::complex I_A_F=0.0;//It depends on the modelType
    gslpp::complex I_A_Ux=I_A_U(mA2,Mc,Mt);
    gslpp::complex I_A_Dx=I_A_D(mA2,Ms,Mb);
    gslpp::complex I_A_Lx=I_A_L(mA2,Mmu,Mtau);

    /*A_A_F is needed for Gamma_AZga*/
    /*The expression can be found in "The Higgs Hunter's Guide", Appendix C, C.12*/
    gslpp::complex A_A_F = 0.0;//It depends on the modelType
    gslpp::complex A_A_Ux = A_A_U(mA2,cW2,Mc,Mt,MZ);
    gslpp::complex A_A_Dx = A_A_D(mA2,cW2,Ms,Mb,MZ);
    gslpp::complex A_A_Lx = A_A_L(mA2,cW2,Mmu,Mtau,MZ);

    if( modelflag == "type1" ) {
        rA_gg=-cosb/sinb*cosb/sinb+2.0*cosb/sinb*cosb/sinb*(rSigmaggA_t+rSigmaggA_b);
        rA_QdQd=cosb/sinb*cosb/sinb;
        rA_ll=cosb/sinb*cosb/sinb;
        I_A_F=cosb/sinb*(I_A_Ux-I_A_Dx-I_A_Lx);
        A_A_F=cosb/sinb*(A_A_Ux-A_A_Dx-A_A_Lx);
    }
    else if( modelflag == "type2" ) {
        rA_gg= 1.0+(cosb/sinb-sinb/cosb)*(rSigmaggA_t*cosb/sinb-rSigmaggA_b*sinb/cosb);
        rA_QdQd=sinb/cosb*sinb/cosb;
        rA_ll=sinb/cosb*sinb/cosb;
        I_A_F=cosb/sinb*I_A_Ux+sinb/cosb*(I_A_Dx+I_A_Lx);
        A_A_F=cosb/sinb*A_A_Ux+sinb/cosb*(A_A_Dx+A_A_Lx);
    }
    else if( modelflag == "typeX" ) {
        rA_gg=-cosb/sinb*cosb/sinb+2.0*cosb/sinb*cosb/sinb*(rSigmaggA_t+rSigmaggA_b);
        rA_QdQd=cosb/sinb*cosb/sinb;
        rA_ll=sinb/cosb*sinb/cosb;
        I_A_F=cosb/sinb*(I_A_Ux-I_A_Dx)+sinb/cosb*I_A_Lx;
        A_A_F=cosb/sinb*(A_A_Ux-A_A_Dx)+sinb/cosb*A_A_Lx;
    }
    else if( modelflag == "typeY" ) {
        rA_gg=1.0+(cosb/sinb-sinb/cosb)*(rSigmaggA_t*cosb/sinb-rSigmaggA_b*sinb/cosb);
        rA_QdQd=sinb/cosb*sinb/cosb;
        rA_ll=cosb/sinb*cosb/sinb;
        I_A_F=cosb/sinb*(I_A_Ux-I_A_Lx)+sinb/cosb*I_A_Dx;
        A_A_F=cosb/sinb*(A_A_Ux-A_A_Lx)+sinb/cosb*A_A_Dx;
    }
    else {
        throw std::runtime_error("modelflag can be only any of \"type1\", \"type2\", \"typeX\" or \"typeY\"");
    }

    /*Gamma_Agaga expression can be found in in arXiv:0902.4665v3, Appendix A, A.8*/
    double Gamma_Agaga=GF*Ale*Ale*mA*mA*mA/(sqrt(2)*128.0*M_PI*M_PI*M_PI)
                *(I_A_F).abs2();
    /*Gamma_AZga expression can be found in in arXiv:0902.4665v3, Appendix A, A.9*/
    double Gamma_AZga=GF*Ale*Ale*mA*mA*mA/(sqrt(2)*64.0*M_PI*M_PI*M_PI)
               *(1.0-MZ*MZ/(mA*mA))*(1.0-MZ*MZ/(mA*mA))*(1.0-MZ*MZ/(mA*mA))
               *(A_A_F).abs2();
    /*Gamma_Agg expression can be found in in arXiv:0902.4665v3, Appendix A, A.10*/
    double Gamma_Agg=rA_gg*GF*Als*Als*mA*mA*mA/(sqrt(2)*16.0*M_PI*M_PI*M_PI)
                     *(9.0/4.0)*(I_A_Ux/4.0+I_A_Dx).abs2();

    /*Calulation of rA_QdQd, rA_ll, rA_gg, Gamma_Agaga, Gamma_AZga, Gamma_Agg: END*/

    double SigmaggF_A=ip_cs_ggtoA_8(mA)*rA_gg;
    double SigmattF_A=ip_cs_pptottA_8(mA)*rA_QuQu;
    double SigmabbF_A=ip_cs_pptobbA_8(mA)*rA_QdQd;
    double SigmaSum = SigmaggF_A + SigmattF_A + SigmabbF_A;

    double BrSM_Atocc=ip_Br_HPtocc(mA);
    double BrSM_Atobb=ip_Br_HPtobb(mA);
    double BrSM_Atott=ip_Br_HPtott(mA)/(1.0-4.0*Mt*Mt/mA2);
    double BrSM_Atomumu=ip_Br_HPtomumu(mA);
    double BrSM_Atotautau=ip_Br_HPtotautau(mA);

    double GammaAtotSM=ip_GammaHPtotSM(mA);

    double GammaAHZ=HSTheta(mA-MZ-mHh)*pow(KaellenFunction(mA2,MZ*MZ,mHh*mHh),3)
                    *sin_ba*sin_ba/(2.0*M_PI*vev*vev);

    double GammaAhZ=HSTheta(mA-MZ-mHl)*pow(KaellenFunction(mA2,MZ*MZ,mHl*mHl),3)
                    *cos_ba*cos_ba/(2.0*M_PI*vev*vev);

    double GammaAHpW=2.*HSTheta(mA-MW-mHp)*pow(KaellenFunction(mA2,MW*MW,mHp*mHp),3)
                     /(2.0*M_PI*vev*vev);

    GammaAtot= ((BrSM_Atott+BrSM_Atocc)*rA_QuQu
                    +BrSM_Atobb*rA_QdQd
                    +(BrSM_Atotautau+BrSM_Atomumu)*rA_ll)*GammaAtotSM
               +Gamma_Agaga+Gamma_AZga+Gamma_Agg+GammaAHZ+GammaAhZ+GammaAHpW;

    double Br_Atott=BrSM_Atott*rA_QuQu*GammaAtotSM/GammaAtot;
    double Br_Atobb=BrSM_Atobb*rA_QdQd*GammaAtotSM/GammaAtot;
    double Br_Atotautau=BrSM_Atotautau*rA_ll*GammaAtotSM/GammaAtot;
    double Br_Atogaga=Gamma_Agaga/GammaAtot;
    Br_AtoHZ=GammaAHZ/GammaAtot;
    Br_AtohZ=GammaAhZ/GammaAtot;
    Br_AtoHpW=GammaAHpW/GammaAtot;

    //Theoretical expressions for the CP-odd Higgs cross sections times branching ratios

    double Br_Ztoee=0.03363; //K.A. Olive et al. (Particle Data Group), Chin. Phys. C38, 090001 (2014)
    double Br_Ztomumu=0.03366; //K.A. Olive et al. (Particle Data Group), Chin. Phys. C38, 090001 (2014)

    ggF_A_tautau_TH=SigmaggF_A*Br_Atotautau;
    bbF_A_tautau_TH=SigmabbF_A*Br_Atotautau;
    pp_A_gaga_TH=SigmaSum*Br_Atogaga;
    ggF_A_gaga_TH=SigmaggF_A*Br_Atogaga;
    ggF_A_hZ_bbll_TH=SigmaggF_A*Br_AtohZ*THDM_BR_h_bb*(Br_Ztoee+Br_Ztomumu);
    ggF_A_hZ_bbZ_TH=SigmaggF_A*Br_AtohZ*THDM_BR_h_bb;
    ggF_A_hZ_tautaull_TH=SigmaggF_A*Br_AtohZ*THDM_BR_h_tautau*(Br_Ztoee+Br_Ztomumu);
    ggF_A_hZ_tautauZ_TH=SigmaggF_A*Br_AtohZ*THDM_BR_h_tautau;
    ggF_A_tt_TH=SigmaggF_A*Br_Atott;
    bbF_A_bb_TH=SigmabbF_A*Br_Atobb;

    //Ratios of theoretical CP-odd Higgs cross sections and experimental upper limits

    THoEX_ggF_A_tautau_ATLAS=0.0;
    R_ggF_A_tautau_ATLAS=0.0;
    THoEX_ggF_A_tautau_CMS=0.0;
    R_ggF_A_tautau_CMS=0.0;
    THoEX_bbF_A_tautau_ATLAS=0.0;
    R_bbF_A_tautau_ATLAS=0.0;
    THoEX_bbF_A_tautau_CMS=0.0;
    R_bbF_A_tautau_CMS=0.0;
    THoEX_pp_A_gaga_ATLAS=0.0;
    R_pp_A_gaga_ATLAS=0.0;
    THoEX_ggF_A_gaga_CMS=0.0;
    R_ggF_A_gaga_CMS=0.0;
    THoEX_ggF_A_hZ_bbll_CMS=0.0;
    R_ggF_A_hZ_bbll_CMS=0.0;
    THoEX_ggF_A_hZ_bbZ_ATLAS=0.0;
    R_ggF_A_hZ_bbZ_ATLAS=0.0;
    THoEX_ggF_A_hZ_tautaull_CMS=0.0;
    R_ggF_A_hZ_tautaull_CMS=0.0;
    THoEX_ggF_A_hZ_tautauZ_ATLAS=0.0;
    R_ggF_A_hZ_tautauZ_ATLAS=0.0;
    THoEX_ggF_A_tt_ATLAS=0.0;
    R_ggF_A_tt_ATLAS=0.0;
    THoEX_bbF_A_bb_CMS=0.0;
    R_bbF_A_bb_CMS=0.0;

    //95% to 1 sigma conversion factor, roughly sqrt(3.84)
    double nftos=1.95996398454;

    if(mA>=65.0 && mA<90.0)
    {
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
    }
    if(mA>=90.0 && mA<100.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
    }
    else if(mA>=100.0 && mA<150.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=150.0 && mA<220.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_gaga_CMS=ggF_A_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mA);
        R_ggF_A_gaga_CMS=(1+(ggF_A_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mA))/ip_ex_ggF_phi_gaga_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=220.0 && mA<225.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_gaga_CMS=ggF_A_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mA);
        R_ggF_A_gaga_CMS=(1+(ggF_A_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mA))/ip_ex_ggF_phi_gaga_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbZ_ATLAS=ggF_A_hZ_bbZ_TH/ip_ex_ggF_A_hZ_bbZ_ATLAS(mA);
        R_ggF_A_hZ_bbZ_ATLAS=(1+(ggF_A_hZ_bbZ_TH-ip_ex_ggF_A_hZ_bbZ_ATLAS(mA))/ip_ex_ggF_A_hZ_bbZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautaull_CMS=ggF_A_hZ_tautaull_TH/ip_ex_ggF_A_hZ_tautaull_CMS(mA);
        R_ggF_A_hZ_tautaull_CMS=(1+(ggF_A_hZ_tautaull_TH-ip_ex_ggF_A_hZ_tautaull_CMS(mA))/ip_ex_ggF_A_hZ_tautaull_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautauZ_ATLAS=ggF_A_hZ_tautauZ_TH/ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA);
        R_ggF_A_hZ_tautauZ_ATLAS=(1+(ggF_A_hZ_tautauZ_TH-ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA))/ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=225.0 && mA<350.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_gaga_CMS=ggF_A_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mA);
        R_ggF_A_gaga_CMS=(1+(ggF_A_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mA))/ip_ex_ggF_phi_gaga_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbll_CMS=ggF_A_hZ_bbll_TH/ip_ex_ggF_A_hZ_bbll_CMS(mA);
        R_ggF_A_hZ_bbll_CMS=(1+(ggF_A_hZ_bbll_TH-ip_ex_ggF_A_hZ_bbll_CMS(mA))/ip_ex_ggF_A_hZ_bbll_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbZ_ATLAS=ggF_A_hZ_bbZ_TH/ip_ex_ggF_A_hZ_bbZ_ATLAS(mA);
        R_ggF_A_hZ_bbZ_ATLAS=(1+(ggF_A_hZ_bbZ_TH-ip_ex_ggF_A_hZ_bbZ_ATLAS(mA))/ip_ex_ggF_A_hZ_bbZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautaull_CMS=ggF_A_hZ_tautaull_TH/ip_ex_ggF_A_hZ_tautaull_CMS(mA);
        R_ggF_A_hZ_tautaull_CMS=(1+(ggF_A_hZ_tautaull_TH-ip_ex_ggF_A_hZ_tautaull_CMS(mA))/ip_ex_ggF_A_hZ_tautaull_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautauZ_ATLAS=ggF_A_hZ_tautauZ_TH/ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA);
        R_ggF_A_hZ_tautauZ_ATLAS=(1+(ggF_A_hZ_tautauZ_TH-ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA))/ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=350.0 && mA<400.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_gaga_CMS=ggF_A_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mA);
        R_ggF_A_gaga_CMS=(1+(ggF_A_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mA))/ip_ex_ggF_phi_gaga_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbll_CMS=ggF_A_hZ_bbll_TH/ip_ex_ggF_A_hZ_bbll_CMS(mA);
        R_ggF_A_hZ_bbll_CMS=(1+(ggF_A_hZ_bbll_TH-ip_ex_ggF_A_hZ_bbll_CMS(mA))/ip_ex_ggF_A_hZ_bbll_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbZ_ATLAS=ggF_A_hZ_bbZ_TH/ip_ex_ggF_A_hZ_bbZ_ATLAS(mA);
        R_ggF_A_hZ_bbZ_ATLAS=(1+(ggF_A_hZ_bbZ_TH-ip_ex_ggF_A_hZ_bbZ_ATLAS(mA))/ip_ex_ggF_A_hZ_bbZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautauZ_ATLAS=ggF_A_hZ_tautauZ_TH/ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA);
        R_ggF_A_hZ_tautauZ_ATLAS=(1+(ggF_A_hZ_tautauZ_TH-ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA))/ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=400.0 && mA<600.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_pp_A_gaga_ATLAS=pp_A_gaga_TH/ip_ex_pp_phi_gaga_ATLAS(mA);
        R_pp_A_gaga_ATLAS=(1+(pp_A_gaga_TH-ip_ex_pp_phi_gaga_ATLAS(mA))/ip_ex_pp_phi_gaga_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_gaga_CMS=ggF_A_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mA);
        R_ggF_A_gaga_CMS=(1+(ggF_A_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mA))/ip_ex_ggF_phi_gaga_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbll_CMS=ggF_A_hZ_bbll_TH/ip_ex_ggF_A_hZ_bbll_CMS(mA);
        R_ggF_A_hZ_bbll_CMS=(1+(ggF_A_hZ_bbll_TH-ip_ex_ggF_A_hZ_bbll_CMS(mA))/ip_ex_ggF_A_hZ_bbll_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbZ_ATLAS=ggF_A_hZ_bbZ_TH/ip_ex_ggF_A_hZ_bbZ_ATLAS(mA);
        R_ggF_A_hZ_bbZ_ATLAS=(1+(ggF_A_hZ_bbZ_TH-ip_ex_ggF_A_hZ_bbZ_ATLAS(mA))/ip_ex_ggF_A_hZ_bbZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautauZ_ATLAS=ggF_A_hZ_tautauZ_TH/ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA);
        R_ggF_A_hZ_tautauZ_ATLAS=(1+(ggF_A_hZ_tautauZ_TH-ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA))/ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tt_ATLAS=ggF_A_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mA);
        R_ggF_A_tt_ATLAS=(1+(ggF_A_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mA))/ip_ex_ggF_phi_tt_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=600.0 && mA<850.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_gaga_CMS=ggF_A_gaga_TH/ip_ex_ggF_phi_gaga_CMS(mA);
        R_ggF_A_gaga_CMS=(1+(ggF_A_gaga_TH-ip_ex_ggF_phi_gaga_CMS(mA))/ip_ex_ggF_phi_gaga_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbZ_ATLAS=ggF_A_hZ_bbZ_TH/ip_ex_ggF_A_hZ_bbZ_ATLAS(mA);
        R_ggF_A_hZ_bbZ_ATLAS=(1+(ggF_A_hZ_bbZ_TH-ip_ex_ggF_A_hZ_bbZ_ATLAS(mA))/ip_ex_ggF_A_hZ_bbZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautauZ_ATLAS=ggF_A_hZ_tautauZ_TH/ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA);
        R_ggF_A_hZ_tautauZ_ATLAS=(1+(ggF_A_hZ_tautauZ_TH-ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA))/ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tt_ATLAS=ggF_A_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mA);
        R_ggF_A_tt_ATLAS=(1+(ggF_A_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mA))/ip_ex_ggF_phi_tt_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=850.0 && mA<900.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbZ_ATLAS=ggF_A_hZ_bbZ_TH/ip_ex_ggF_A_hZ_bbZ_ATLAS(mA);
        R_ggF_A_hZ_bbZ_ATLAS=(1+(ggF_A_hZ_bbZ_TH-ip_ex_ggF_A_hZ_bbZ_ATLAS(mA))/ip_ex_ggF_A_hZ_bbZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautauZ_ATLAS=ggF_A_hZ_tautauZ_TH/ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA);
        R_ggF_A_hZ_tautauZ_ATLAS=(1+(ggF_A_hZ_tautauZ_TH-ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA))/ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tt_ATLAS=ggF_A_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mA);
        R_ggF_A_tt_ATLAS=(1+(ggF_A_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mA))/ip_ex_ggF_phi_tt_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_bb_CMS=bbF_A_bb_TH/ip_ex_bbF_phi_bb_CMS(mA);
        R_bbF_A_bb_CMS=(1+(bbF_A_bb_TH-ip_ex_bbF_phi_bb_CMS(mA))/ip_ex_bbF_phi_bb_CMS_e(mA) ) * nftos;
    }
    else if(mA>=900.0 && mA<1000.0)
    {
        THoEX_ggF_A_tautau_ATLAS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_ATLAS(mA);
        R_ggF_A_tautau_ATLAS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_ATLAS(mA))/ip_ex_ggF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tautau_CMS=ggF_A_tautau_TH/ip_ex_ggF_phi_tautau_CMS(mA);
        R_ggF_A_tautau_CMS=(1+(ggF_A_tautau_TH-ip_ex_ggF_phi_tautau_CMS(mA))/ip_ex_ggF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_ATLAS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_ATLAS(mA);
        R_bbF_A_tautau_ATLAS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_ATLAS(mA))/ip_ex_bbF_phi_tautau_ATLAS_e(mA) ) * nftos;
        THoEX_bbF_A_tautau_CMS=bbF_A_tautau_TH/ip_ex_bbF_phi_tautau_CMS(mA);
        R_bbF_A_tautau_CMS=(1+(bbF_A_tautau_TH-ip_ex_bbF_phi_tautau_CMS(mA))/ip_ex_bbF_phi_tautau_CMS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_bbZ_ATLAS=ggF_A_hZ_bbZ_TH/ip_ex_ggF_A_hZ_bbZ_ATLAS(mA);
        R_ggF_A_hZ_bbZ_ATLAS=(1+(ggF_A_hZ_bbZ_TH-ip_ex_ggF_A_hZ_bbZ_ATLAS(mA))/ip_ex_ggF_A_hZ_bbZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_hZ_tautauZ_ATLAS=ggF_A_hZ_tautauZ_TH/ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA);
        R_ggF_A_hZ_tautauZ_ATLAS=(1+(ggF_A_hZ_tautauZ_TH-ip_ex_ggF_A_hZ_tautauZ_ATLAS(mA))/ip_ex_ggF_A_hZ_tautauZ_ATLAS_e(mA) ) * nftos;
        THoEX_ggF_A_tt_ATLAS=ggF_A_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mA);
        R_ggF_A_tt_ATLAS=(1+(ggF_A_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mA))/ip_ex_ggF_phi_tt_ATLAS_e(mA) ) * nftos;
    }
    else if(mA>=1000.0 && mA<3000.0)
    {
        THoEX_ggF_A_tt_ATLAS=ggF_A_tt_TH/ip_ex_ggF_phi_tt_ATLAS(mA);
        R_ggF_A_tt_ATLAS=(1+(ggF_A_tt_TH-ip_ex_ggF_phi_tt_ATLAS(mA))/ip_ex_ggF_phi_tt_ATLAS_e(mA) ) * nftos;
    }
}

void THDMcache::runTHDMparameters()
{
    vev=myTHDM->v();
    double cosb=myTHDM->getcosb();
    double sinb=myTHDM->getsinb();
    modelflag=myTHDM->getModelTypeflag();
    std::string RGEorder=myTHDM->getRGEorderflag();
    //flag will be used to transport information about model and RGEorder to the Runner:
    //flag=3*(0 for type I, 1 for type II, 2 for type X and 3 for type Y) + (0 for LO, 1 for approxNLO and 2 for NLO)
    int flag;
    if( RGEorder == "LO" ) flag=0;
    else if( RGEorder == "approxNLO" ) flag=1;
    else if( RGEorder == "NLO" ) flag=2;
    else {
        throw std::runtime_error("RGEorder can be only any of \"LO\", \"approxNLO\" or \"NLO\"");
    }

    double g1_at_MZ=sqrt(4.0*M_PI*Ale/cW2);
    double g2_at_MZ=sqrt(4.0*M_PI*Ale/(1-cW2));
    double g3_at_MZ=sqrt(4.0*M_PI*Als);

    double Ytop_at_MZ=(sqrt(2.0)*myTHDM->getQuarks(QCD::TOP).getMass())/(vev*sinb);
    double Ybottom1_at_MZ=0.0;
    double Ybottom2_at_MZ=0.0;
    double Ytau1_at_MZ=0.0;
    double Ytau2_at_MZ=0.0;

    /*link these to the SM values*/
    double Mb_at_MZ=2.96;//GeV
    double Mtau_at_MZ=1.75;//GeV

    if( modelflag == "type1" ) {
        Ybottom2_at_MZ=(sqrt(2.0)*Mb_at_MZ)/(vev*sinb);
        Ytau2_at_MZ=(sqrt(2.0)*Mtau_at_MZ)/(vev*sinb);
    }
    else if( modelflag == "type2" ) {
        Ybottom1_at_MZ=(sqrt(2.0)*Mb_at_MZ)/(vev*cosb);
        Ytau1_at_MZ=(sqrt(2.0)*Mtau_at_MZ)/(vev*cosb);
        flag +=3;
    }
    else if( modelflag == "typeX" ) {
        Ybottom2_at_MZ=(sqrt(2.0)*Mb_at_MZ)/(vev*sinb);
        Ytau1_at_MZ=(sqrt(2.0)*Mtau_at_MZ)/(vev*cosb);
        flag +=6;
    }
    else if( modelflag == "typeY" ) {
        Ybottom1_at_MZ=(sqrt(2.0)*Mb_at_MZ)/(vev*cosb);
        Ytau2_at_MZ=(sqrt(2.0)*Mtau_at_MZ)/(vev*sinb);
        flag +=9;
    }
    else {
        throw std::runtime_error("modelflag can be only any of \"type1\", \"type2\", \"typeX\" or \"typeY\"");
    }

    double m11_2_at_MZ=mym11_2->computeThValue();
    double m22_2_at_MZ=mym22_2->computeThValue();
    double m12_2_at_MZ=myTHDM->getm12_2();
    double lambda1_at_MZ=mylambda1->computeThValue();
    double lambda2_at_MZ=mylambda2->computeThValue();
    double lambda3_at_MZ=mylambda3->computeThValue();
    double lambda4_at_MZ=mylambda4->computeThValue();
    double lambda5_at_MZ=mylambda5->computeThValue();

    if(fabs(Q_THDM-log10(MZ))<0.005)   //at MZ scale
    {
        Q_cutoff=log10(MZ);

        g1_at_Q = g1_at_MZ;
        g2_at_Q = g2_at_MZ;
        g3_at_Q = g3_at_MZ;
        Ytop_at_Q = Ytop_at_MZ;
        Ybottom1_at_Q = Ybottom1_at_MZ;
        Ybottom2_at_Q = Ybottom2_at_MZ;
        Ytau1_at_Q = Ytau1_at_MZ;
        Ytau2_at_Q = Ytau2_at_MZ;
        m11_2_at_Q = m11_2_at_MZ;
        m22_2_at_Q = m22_2_at_MZ;
        m12_2_at_Q = m12_2_at_MZ;
        lambda1_at_Q = lambda1_at_MZ;
        lambda2_at_Q = lambda2_at_MZ;
        lambda3_at_Q = lambda3_at_MZ;
        lambda4_at_Q = lambda4_at_MZ;
        lambda5_at_Q = lambda5_at_MZ;
    }
    else   //at some other scale
    {
        double InitVals[14];
        InitVals[0]=g1_at_MZ;
        InitVals[1]=g2_at_MZ;
        InitVals[2]=g3_at_MZ;
        InitVals[3]=Ytop_at_MZ;
        InitVals[4]=Ybottom1_at_MZ+Ybottom2_at_MZ;
        InitVals[5]=Ytau1_at_MZ+Ytau2_at_MZ;
        InitVals[6]=m11_2_at_MZ;
        InitVals[7]=m22_2_at_MZ;
        InitVals[8]=m12_2_at_MZ;
        InitVals[9]=lambda1_at_MZ;
        InitVals[10]=lambda2_at_MZ;
        InitVals[11]=lambda3_at_MZ;
        InitVals[12]=lambda4_at_MZ;
        InitVals[13]=lambda5_at_MZ;

        Q_cutoff=myRunner->RGERunner(InitVals, 14, log10(MZ), Q_THDM, flag);  //Running up to Q_cutoff<=Q_THDM

        g1_at_Q = InitVals[0];
        g2_at_Q = InitVals[1];
        g3_at_Q = InitVals[2];
        Ytop_at_Q = InitVals[3];
        Ybottom1_at_Q = 0.0;
        Ybottom2_at_Q = 0.0;
        Ytau1_at_Q = 0.0;
        Ytau2_at_Q = 0.0;
        if( modelflag == "type1" ) {
            Ybottom2_at_Q=InitVals[4];
            Ytau2_at_Q=InitVals[5];
        }
        else if( modelflag == "type2" ) {
            Ybottom1_at_Q=InitVals[4];
            Ytau1_at_Q=InitVals[5];
        }
        else if( modelflag == "typeX" ) {
            Ybottom2_at_Q=InitVals[4];
            Ytau1_at_Q=InitVals[5];
        }
        else if( modelflag == "typeY" ) {
            Ybottom1_at_Q=InitVals[4];
            Ytau2_at_Q=InitVals[5];
        }
        else {
            throw std::runtime_error("modelflag can be only any of \"type1\", \"type2\", \"typeX\" or \"typeY\"");
        }
        m11_2_at_Q = InitVals[6];
        m22_2_at_Q = InitVals[7];
        m12_2_at_Q = InitVals[8];
        lambda1_at_Q = InitVals[9];
        lambda2_at_Q = InitVals[10];
        lambda3_at_Q = InitVals[11];
        lambda4_at_Q = InitVals[12];
        lambda5_at_Q = InitVals[13];
//    std::cout<<"Ytop_at_Q = "<<Ytop_at_Q<<std::endl;
//    std::cout<<"Ybottom1_at_Q = "<<Ybottom1_at_Q<<std::endl;
//    std::cout<<"Ybottom2_at_Q = "<<Ybottom2_at_Q<<std::endl;
//    std::cout<<"Ytau1_at_Q = "<<Ytau1_at_Q<<std::endl;
//    std::cout<<"Ytau2_at_Q = "<<Ytau2_at_Q<<std::endl;
//    std::cout<<"lambda1_at_Q = "<<lambda1_at_Q<<std::endl;
//    std::cout<<"lambda2_at_Q = "<<lambda2_at_Q<<std::endl;
//    std::cout<<"lambda3_at_Q = "<<lambda3_at_Q<<std::endl;
//    std::cout<<"lambda4_at_Q = "<<lambda4_at_Q<<std::endl;
//    std::cout<<"lambda5_at_Q = "<<lambda5_at_Q<<std::endl;
    }

}

void THDMcache::computeWFRcombinations()
{
    double WFRcomb1a = 0.0;
    double WFRcomb1b = 0.0;
    double WFRcomb2a = 0.0;
    double WFRcomb3a = 0.0;
    double WFRcomb3b = 0.0;
    double WFRcomb4a = 0.0;

    if(WFRflag)
    {    
//    bma=myTHDM->getbma();
//    tanb=myTHDM->gettanb();
    double sinb=myTHDM->getsinb();
    double cosb=myTHDM->getcosb();
    double beta=atan(tanb);
    double alpha=beta-bma;
//    m12_2=myTHDM->getm12_2();
//    mHh2=myTHDM->getmHh2();
//    mA2=myTHDM->getmA2();
//    mHp2=myTHDM->getmHp2();
//    mHl=myTHDM->getMHl();
    double mHl2=mHl*mHl;
    double MZ2=MZ*MZ;

    double B000mh = B0_MZ2_0_0_mHl2(MZ2,mHl2).real();
    double B000mH = B0_MZ2_0_0_mHh2(MZ2,mHh2).real();
    double B00mHpmh = B0_MZ2_0_mHp2_mHl2(MZ2,mHp2,mHl2).real();
    double B00mHpmH = B0_MZ2_0_mHp2_mHh2(MZ2,mHp2,mHh2).real();
    double B00mAmh = B0_MZ2_0_mA2_mHl2(MZ2,mA2,mHl2).real();
    double B00mAmH = B0_MZ2_0_mA2_mHh2(MZ2,mA2,mHh2).real();
    double B0mh00 = B0_MZ2_mHl2_0_0(MZ2,mHl2).real();
    double B0mh0mHp = B0_MZ2_mHl2_0_mHp2(MZ2,mHl2,mHp2).real();
    double B0mh0mA = B0_MZ2_mHl2_0_mA2(MZ2,mHl2,mA2).real();
    double B0mhmhmh = B0_MZ2_mHl2_mHl2_mHl2(MZ2,mHl2).real();
    double B0mhmHmh = B0_MZ2_mHl2_mHh2_mHl2(MZ2,mHl2,mHh2).real();
    double B0mhmHmH = B0_MZ2_mHl2_mHh2_mHh2(MZ2,mHl2,mHh2).real();
    double B0mhmHpmHp = B0_MZ2_mHl2_mHp2_mHp2(MZ2,mHl2,mHp2).real();
    double B0mhmAmA = B0_MZ2_mHl2_mA2_mA2(MZ2,mHl2,mA2).real();
    double B0mH00 = B0_MZ2_mHh2_0_0(MZ2,mHh2).real();
    double B0mH0mHp = B0_MZ2_mHh2_0_mHp2(MZ2,mHh2,mHp2).real();
    double B0mH0mA = B0_MZ2_mHh2_0_mA2(MZ2,mHh2,mA2).real();
    double B0mHmhmh = B0_MZ2_mHh2_mHl2_mHl2(MZ2,mHh2,mHl2).real();
    double B0mHmHmh = B0_MZ2_mHh2_mHh2_mHl2(MZ2,mHh2,mHl2).real();
    double B0mHmHmH = B0_MZ2_mHh2_mHh2_mHh2(MZ2,mHh2).real();
    double B0mHmHpmHp = B0_MZ2_mHh2_mHp2_mHp2(MZ2,mHh2,mHp2).real();
    double B0mHmAmA = B0_MZ2_mHh2_mA2_mA2(MZ2,mHh2,mA2).real();
    double B0mHp0mh = B0_MZ2_mHp2_0_mHl2(MZ2,mHp2,mHl2).real();
    double B0mHp0mH = B0_MZ2_mHp2_0_mHh2(MZ2,mHp2,mHh2).real();
    double B0mHpmHpmh = B0_MZ2_mHp2_mHp2_mHl2(MZ2,mHp2,mHl2).real();
    double B0mHpmHpmH = B0_MZ2_mHp2_mHp2_mHh2(MZ2,mHp2,mHh2).real();
    double B0mA0mh = B0_MZ2_mA2_0_mHl2(MZ2,mA2,mHl2).real();
    double B0mA0mH = B0_MZ2_mA2_0_mHh2(MZ2,mA2,mHh2).real();
    double B0mAmAmh = B0_MZ2_mA2_mA2_mHl2(MZ2,mA2,mHl2).real();
    double B0mAmAmH = B0_MZ2_mA2_mA2_mHh2(MZ2,mA2,mHh2).real();

    double ddpB000mh = B0p_MZ2_0_0_mHl2(MZ2,mHl2).real();
    double ddpB000mH = B0p_MZ2_0_0_mHh2(MZ2,mHh2).real();
    double ddpB00mHpmh = B0p_MZ2_0_mHp2_mHl2(MZ2,mHp2,mHl2).real();
    double ddpB00mHpmH = B0p_MZ2_0_mHp2_mHh2(MZ2,mHp2,mHh2).real();
    double ddpB00mHpmA = B0p_MZ2_0_mHp2_mA2(MZ2,mHp2,mA2).real();
    double ddpB00mAmh = B0p_MZ2_0_mA2_mHl2(MZ2,mA2,mHl2).real();
    double ddpB00mAmH = B0p_MZ2_0_mA2_mHh2(MZ2,mA2,mHh2).real();
    double ddpB0mh00 = B0p_MZ2_mHl2_0_0(MZ2,mHl2).real();
    double ddpB0mh0mHp = B0p_MZ2_mHl2_0_mHp2(MZ2,mHl2,mHp2).real();
    double ddpB0mh0mA = B0p_MZ2_mHl2_0_mA2(MZ2,mHl2,mA2).real();
    double ddpB0mhmhmh = B0p_MZ2_mHl2_mHl2_mHl2(MZ2,mHl2).real();
    double ddpB0mhmHmh = B0p_MZ2_mHl2_mHh2_mHl2(MZ2,mHl2,mHh2).real();
    double ddpB0mhmHmH = B0p_MZ2_mHl2_mHh2_mHh2(MZ2,mHl2,mHh2).real();
    double ddpB0mhmHpmHp = B0p_MZ2_mHl2_mHp2_mHp2(MZ2,mHl2,mHp2).real();
    double ddpB0mhmAmA = B0p_MZ2_mHl2_mA2_mA2(MZ2,mHl2,mA2).real();
    double ddpB0mH00 = B0p_MZ2_mHh2_0_0(MZ2,mHh2).real();
    double ddpB0mH0mHp = B0p_MZ2_mHh2_0_mHp2(MZ2,mHh2,mHp2).real();
    double ddpB0mH0mA = B0p_MZ2_mHh2_0_mA2(MZ2,mHh2,mA2).real();
    double ddpB0mHmhmh = B0p_MZ2_mHh2_mHl2_mHl2(MZ2,mHh2,mHl2).real();
    double ddpB0mHmHmh = B0p_MZ2_mHh2_mHh2_mHl2(MZ2,mHh2,mHl2).real();
    double ddpB0mHmHmH = B0p_MZ2_mHh2_mHh2_mHh2(MZ2,mHh2).real();
    double ddpB0mHmHpmHp = B0p_MZ2_mHh2_mHp2_mHp2(MZ2,mHh2,mHp2).real();
    double ddpB0mHmAmA = B0p_MZ2_mHh2_mA2_mA2(MZ2,mHh2,mA2).real();
    double ddpB0mHp0mh = B0p_MZ2_mHp2_0_mHl2(MZ2,mHp2,mHl2).real();
    double ddpB0mHp0mH = B0p_MZ2_mHp2_0_mHh2(MZ2,mHp2,mHh2).real();
    double ddpB0mHp0mA = B0p_MZ2_mHp2_0_mA2(MZ2,mHp2,mA2).real();
    double ddpB0mHpmHpmh = B0p_MZ2_mHp2_mHp2_mHl2(MZ2,mHp2,mHl2).real();
    double ddpB0mHpmHpmH = B0p_MZ2_mHp2_mHp2_mHh2(MZ2,mHp2,mHh2).real();
    double ddpB0mA0mh = B0p_MZ2_mA2_0_mHl2(MZ2,mA2,mHl2).real();
    double ddpB0mA0mH = B0p_MZ2_mA2_0_mHh2(MZ2,mA2,mHh2).real();
    double ddpB0mA0mHp = B0p_MZ2_mA2_0_mHp2(MZ2,mA2,mHp2).real();
    double ddpB0mAmAmh = B0p_MZ2_mA2_mA2_mHl2(MZ2,mA2,mHl2).real();
    double ddpB0mAmAmH = B0p_MZ2_mA2_mA2_mHh2(MZ2,mA2,mHh2).real();

    WFRcomb1a = 3.0*mHl2*mHl2*cosb*cosb*sin(bma)*sin(bma) * ddpB000mh
        + 3.0*mHh2*mHh2*cos(bma)*cos(bma)*cosb*cosb * ddpB000mH
        + 2.0*(mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma)*cosb*cosb * ddpB00mHpmh
        + 2.0*(mHh2-mHp2)*(mHh2-mHp2)*sin(bma)*sin(bma)*cosb*cosb * ddpB00mHpmH
        + 2.0*(mA2-mHp2)*(mA2-mHp2)*cosb*cosb * ddpB00mHpmA
        + (mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma)*cosb*cosb * ddpB00mAmh
        + (mA2-mHh2)*(mA2-mHh2)*cosb*cosb*sin(bma)*sin(bma) * ddpB00mAmH
        + 1.5*mHl2*mHl2*sin(alpha)*sin(alpha)*sin(bma)*sin(bma) * ddpB0mh00
        + 2.0*(mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma)*sin(alpha)*sin(alpha) * ddpB0mh0mHp
        + (mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma)*sin(alpha)*sin(alpha) * ddpB0mh0mA
        + 9.0*sin(alpha)*sin(alpha)*pow(-mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta))
                                        +16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta),2)/(512.0*pow(cosb*sinb,4)) * ddpB0mhmhmh
        + sin(alpha)*sin(alpha)*pow((cos(alpha)/sinb+sin(alpha)/cosb)*(m12_2+cos(alpha)*sin(alpha)*(mHh2+2.0*mHl2-(3.0*m12_2)/(cosb*sinb))),2) * ddpB0mhmHmh
        + sin(alpha)*sin(alpha)*sin(bma)*sin(bma)*pow(-2.0*m12_2+(2.0*mHh2+mHl2-(3.0*m12_2)/(cosb*sinb))*sin(2.0*alpha),2)/(8.0*cosb*cosb*sinb*sinb) * ddpB0mhmHmH
        + (sin(alpha)*sin(alpha)*pow((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                     +cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb),2))/(64.0*pow(cosb*sinb,4)) * ddpB0mhmHpmHp
        + (sin(alpha)*sin(alpha)*pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(8.0*m12_2-(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb),2))/(128.0*pow(cosb*sinb,4)) * ddpB0mhmAmA
        + 1.5*mHh2*mHh2*cos(alpha)*cos(alpha)*cos(bma)*cos(bma) * ddpB0mH00
        + 2.0*(mHh2-mHp2)*(mHh2-mHp2)*cos(alpha)*cos(alpha)*sin(bma)*sin(bma) * ddpB0mH0mHp
        + (mA2-mHh2)*(mA2-mHh2)*cos(alpha)*cos(alpha)*sin(bma)*sin(bma) * ddpB0mH0mA
        + cos(alpha)*cos(alpha)*cos(bma)*cos(bma)*pow(m12_2+cos(alpha)*sin(alpha)*(mHh2-3.0*m12_2/(cosb*sinb))+mHl2*sin(2.0*alpha),2)/(2.0*cosb*cosb*sinb*sinb) * ddpB0mHmhmh
        + cos(alpha)*cos(alpha)*sin(bma)*sin(bma)*pow(m12_2*cosb*sinb+0.5*sin(2.0*alpha)*(3.0*m12_2-(2.0*mHh2+mHl2)*cosb*sinb),2)/pow(cosb*sinb,4) * ddpB0mHmHmh
        + 9.0*cos(alpha)*cos(alpha)*pow(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
                                        +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta),2)/(512.0*pow(cosb*sinb,4)) * ddpB0mHmHmH
        + (cos(alpha)*cos(alpha)*pow((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)
                                     +2.0*(mHh2+2.0*mHp2)*cos(bma)-(3.0*mHh2+2.0*mHp2)*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta),2))/(256.0*pow(cosb*sinb,4)) * ddpB0mHmHpmHp
        + (cos(alpha)*cos(alpha)*pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)
                                     -2.0*(2.0*mA2+mHh2)*cos(bma)+(2.0*mA2+3.0*mHh2)*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta),2))/(512.0*pow(cosb*sinb,4)) * ddpB0mHmAmA
        + 2.0*(mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma)*sinb*sinb * ddpB0mHp0mh
        + 2.0*(mHh2-mHp2)*(mHh2-mHp2)*sin(bma)*sin(bma)*sinb*sinb * ddpB0mHp0mH
        + 2.0*(mA2-mHp2)*(mA2-mHp2)*sinb*sinb * ddpB0mHp0mA
        + 2.0*pow((m12_2*cos(alpha+beta))/(sinb*sinb*cosb*cosb)-(mHl2*cos(bma)*cos(2.0*beta))/(cosb*sinb)-(mHl2+2.0*mHp2)*sin(bma),2)*sinb*sinb * ddpB0mHpmHpmh
        + 2.0*pow(sinb*((mHh2+2.0*mHp2)*cos(bma)-mHh2*cos(2.0*beta)*sin(bma)/(cosb*sinb)-m12_2*sin(alpha+beta)/(sinb*sinb*cosb*cosb)),2) * ddpB0mHpmHpmH
        + (mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma)*sinb*sinb * ddpB0mA0mh
        + (mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma)*sinb*sinb * ddpB0mA0mH
        + 2.0*(mA2-mHp2)*(mA2-mHp2)*sinb*sinb * ddpB0mA0mHp
        + pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(8.0*m12_2-(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb),2)/(64.0*pow(cosb,4)*sinb*sinb) * ddpB0mAmAmh
        + pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+2.0*mA2*cos(alpha+3.0*beta) 
               + 3.0*mHh2*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta),2)/(256.0*pow(cosb,4)*sinb*sinb) * ddpB0mAmAmH;

    WFRcomb1b = (mHl2*(mA2*(2.0*mHl2-3.0*mHp2)+mHl2*mHp2)*sin(2.0*bma)*2.0*sinb*cosb)/(2.0*mA2*mHp2) * B000mh
        - (mHh2*(mA2*(2.0*mHh2-3.0*mHp2)+mHh2*mHp2)*sin(2.0*bma)*2.0*sinb*cosb)/(2.0*mA2*mHp2) * B000mH
        + ((mHl2-mHp2)*cos(bma)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                 +cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb)))/(2.0*mHp2*sinb*cosb) * B00mHpmh
        + ((mHp2-mHh2)*sin(bma)*((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
                                 -2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta)))/(4.0*mHp2*sinb*cosb) * B00mHpmH
        + ((mHl2-mA2)*cos(bma)*((mHl2-2.0*mA2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                +cos(alpha+beta)*(-8.0*m12_2+(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb)))/(4.0*mA2*sinb*cosb) * B00mAmh
        + ((mHh2-mA2)*sin(bma)*((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+2.0*mA2*cos(alpha+3.0*beta)
                                +3.0*mHh2*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta)))/(8.0*mA2*sinb*cosb) * B00mAmH
        + (3.0*mHh2*mHl2*sin(2.0*alpha)*sin(2.0*bma))/(4.0*(mHh2-mHl2)) * B0mh00
        + ((mHl2-mHp2)*(mHp2-mHh2)*sin(2.0*alpha)*sin(2.0*bma))/(mHh2-mHl2) * B0mh0mHp
        - ((mA2-mHh2)*(mA2-mHl2)*sin(2.0*alpha)*sin(2.0*bma))/(2.0*(mHh2-mHl2)) * B0mh0mA
        + 3.0*cos(bma)*sin(2.0*alpha)*(m12_2+cos(alpha)*sin(alpha)*(mHh2-(3.0*m12_2)/(sinb*cosb))+mHl2*sin(2.0*alpha))
          *(-mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta))
            +16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta))/(32.0*(mHl2-mHh2)*pow(sinb*cosb,3)) * B0mhmhmh
        + (sin(2.0*bma)*sin(2.0*alpha)
           *(4.0*m12_2*m12_2+2.0*m12_2*(mHl2-mHh2)*sin(2.0*alpha)
             -(2.0*mHh2*mHh2+5.0*mHh2*mHl2+2.0*mHl2*mHl2-(9.0*m12_2*(mHh2+mHl2))/(sinb*cosb)
               +(9.0*m12_2*m12_2)/(sinb*sinb*cosb*cosb))*sin(2.0*alpha)*sin(2.0*alpha)))/(8.0*(mHh2-mHl2)*sinb*sinb*cosb*cosb) * B0mhmHmh
        - 3.0*sin(2.0*alpha)*sin(bma)*(m12_2-cos(alpha)*sin(alpha)*(2.0*mHh2+mHl2-(3.0*m12_2)/(sinb*cosb)))
          *(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
            +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta))/(32.0*(mHh2-mHl2)*pow(sinb*cosb,3)) * B0mhmHmH
        + sin(2.0*alpha)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb))
          *((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
             -2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(128.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mhmHpmHp
        + sin(2.0*alpha)*((mHl2-2.0*mA2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb))
          *((mHh2-2.0*mA2)*cos(alpha-5.0*beta)+2.0*(2.0*mA2+mHh2)*cos(bma)-2.0*mA2*cos(alpha+3.0*beta)
             -3.0*mHh2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(256.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mhmAmA
        - (3.0*mHh2*mHl2*sin(2.0*alpha)*sin(2.0*bma))/(4.0*(mHh2-mHl2)) * B0mH00
        + ((mHh2-mHp2)*(mHl2-mHp2)*sin(2.0*alpha)*sin(2.0*bma))/(mHh2-mHl2) * B0mH0mHp
        + ((mA2-mHh2)*(mA2-mHl2)*sin(2.0*alpha)*sin(2.0*bma))/(2.0*(mHh2-mHl2)) * B0mH0mA
        + 3.0*cos(bma)*sin(2.0*alpha)*(m12_2+cos(alpha)*sin(alpha)*(mHh2-(3.0*m12_2)/(sinb*cosb))+mHl2*sin(2.0*alpha))
          *(-mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta))
            +16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta))/(32.0*(mHh2-mHl2)*pow(sinb*cosb,3)) * B0mHmhmh
        + (sin(2.0*bma)*sin(2.0*alpha)*(-4.0*m12_2*m12_2+2.0*m12_2*(mHh2-mHl2)*sin(2.0*alpha)
                                        +(2.0*mHh2*mHh2+5.0*mHh2*mHl2+2.0*mHl2*mHl2
                                          -(9.0*m12_2*(mHh2+mHl2))/(sinb*cosb)
                                          +(9.0*m12_2*m12_2)/(sinb*sinb*cosb*cosb))*sin(2.0*alpha)*sin(2.0*alpha)))
          /(8.0*(mHh2-mHl2)*sinb*sinb*cosb*cosb) * B0mHmHmh
        + 3.0*sin(bma)*sin(2.0*alpha)*(m12_2-cos(alpha)*sin(alpha)*(2.0*mHh2+mHl2-(3.0*m12_2)/(sinb*cosb)))
          *(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
            +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta))/(32.0*(mHh2-mHl2)*pow(sinb*cosb,3)) * B0mHmHmH
        - sin(2.0*alpha)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb))
          *((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
            -2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(128.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mHmHpmHp
        - sin(2.0*alpha)*((mHl2-2.0*mA2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mA2)*2.0*sinb*cosb))
          *((mHh2-2.0*mA2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mA2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
            -2.0*mA2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(256.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mHmAmA
        - (mHl2*(mHl2-mHp2)*sin(2.0*bma)*2.0*sinb*cosb)/mHp2 * B0mHp0mh
        + (mHh2*(mHh2-mHp2)*sin(2.0*bma)*2.0*sinb*cosb)/mHp2 * B0mHp0mH
        + ((mHp2-mHl2)*cos(bma)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                 +cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb)))/(2.0*mHp2*sinb*cosb) * B0mHpmHpmh
        + ((mHh2-mHp2)*sin(bma)*((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
                                 -2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta)))/(4.0*mHp2*sinb*cosb) * B0mHpmHpmH
        + (mHl2*(mA2-mHl2)*sin(bma)*cos(bma)*2.0*sinb*cosb)/mA2 * B0mA0mh
        + ((mHh2-mA2)*mHh2*sin(bma)*cos(bma)*2.0*sinb*cosb)/mA2 * B0mA0mH
        + ((mA2-mHl2)*cos(bma)*((-2.0*mA2+mHl2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                +cos(alpha+beta)*(-8.0*m12_2+(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb)))/(4.0*mA2*sinb*cosb) * B0mAmAmh
        +((mA2-mHh2)*sin(bma)*((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+2.0*mA2*cos(alpha+3.0*beta)
                               +3.0*mHh2*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta)))/(8.0*mA2*sinb*cosb) * B0mAmAmH;

    WFRcomb2a = 1.5*mHl2*mHl2*sin(bma)*sin(bma) * ddpB000mh
        + 1.5*mHh2*mHh2*cos(bma)*cos(bma) * ddpB000mH
        + (mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma) * ddpB00mHpmh
        + (mHh2-mHp2)*(mHh2-mHp2)*sin(bma)*sin(bma) * ddpB00mHpmH
        + (mA2-mHp2)*(mA2-mHp2) * ddpB00mHpmA
        + 0.5*(mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma) * ddpB00mAmh
        + 0.5*(mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma) * ddpB00mAmH
        + 0.75*mHl2*mHl2*sin(bma)*sin(bma) * ddpB0mh00
        + (mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma) * ddpB0mh0mHp
        + 0.5*(mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma) * ddpB0mh0mA
        + 9.0*pow(16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta)
                  -mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta)),2)/(1024.0*pow(cosb*sinb,4)) * ddpB0mhmhmh
        + 0.5*pow(cos(alpha)/sinb + sin(alpha)/cosb,2)
          *pow(m12_2+cos(alpha)*sin(alpha)*(mHh2+2.0*mHl2-3.0*m12_2/(cosb*sinb)),2) * ddpB0mhmHmh
        + (pow(-2.0*m12_2+(2.0*mHh2+mHl2-3.0*m12_2/(cosb*sinb))*sin(2.0*alpha),2)
           *sin(bma)*sin(bma))/(16.0*cosb*cosb*sinb*sinb) * ddpB0mhmHmH
        + pow((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*cosb*sinb
              +cos(alpha+beta)*(-4.0*m12_2+(3.0*mHl2+2.0*mHp2)*cosb*sinb),2)/(32.0*pow(cosb*sinb,4)) * ddpB0mhmHpmHp
        + pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*cosb*sinb
              +cos(alpha+beta)*(4.0*m12_2-(2.0*mA2+3.0*mHl2)*cosb*sinb),2)/(64.0*pow(cosb*sinb,4)) * ddpB0mhmAmA
        + 0.75*mHh2*mHh2*cos(bma)*cos(bma) * ddpB0mH00
        + (mHh2 - mHp2)*(mHh2 - mHp2)*sin(bma)*sin(bma) * ddpB0mH0mHp
        + 0.5*(mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma) * ddpB0mH0mA
        + 0.25*pow(cos(alpha)/sinb + sin(alpha)/cosb,2)
          *pow(m12_2+cos(alpha)*sin(alpha)*(mHh2+2.0*mHl2-3.0*m12_2/(cosb*sinb)),2) * ddpB0mHmhmh
        + (pow(-2.0*m12_2+(2.0*mHh2+mHl2-3.0*m12_2/(cosb*sinb))*sin(2.0*alpha),2)
           *sin(bma)*sin(bma))/(8.0*cosb*cosb*sinb*sinb) * ddpB0mHmHmh
        + 9.0*pow(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
                  +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta),2)/(1024.0*pow(cosb*sinb,4)) * ddpB0mHmHmH
        + pow((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-(3.0*mHh2+2.0*mHp2)*cos(alpha+3.0*beta)
           -16.0*m12_2*sin(alpha+beta),2)/(512*pow(cosb*sinb,4)) * ddpB0mHmHpmHp
        + pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+(2.0*mA2+3.0*mHh2)*cos(alpha+3.0*beta)
           +16.0*m12_2*sin(alpha+beta),2)/(1024*pow(cosb*sinb,4)) * ddpB0mHmAmA
        + (mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma) * ddpB0mHp0mh
        + (mHh2-mHp2)*(mHh2-mHp2)*sin(bma)*sin(bma) * ddpB0mHp0mH
        + (mA2-mHp2)*(mA2-mHp2) * ddpB0mHp0mA
        + pow((m12_2*cos(alpha+beta))/(cosb*cosb*sinb*sinb)-(mHl2*cos(bma)*cos(2.0*beta))/(cosb*sinb)
              -(mHl2+2.0*mHp2)*sin(bma),2) * ddpB0mHpmHpmh
        + pow((mHh2+2.0*mHp2)*cos(bma)-(mHh2*cos(2.0*beta)*sin(bma))/(cosb*sinb)
              -(m12_2*sin(alpha+beta))/(cosb*cosb*sinb*sinb),2) * ddpB0mHpmHpmH
        + 0.5*(mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma) * ddpB0mA0mh
        + 0.5*(mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma) * ddpB0mA0mH
        + (mA2-mHp2)*(mA2-mHp2) * ddpB0mA0mHp
        + pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*2.0*cosb*sinb
              +cos(alpha+beta)*(8.0*m12_2-(2.0*mA2+3.0*mHl2)*2.0*cosb*sinb),2)/(128.0*pow(cosb*sinb,4)) * ddpB0mAmAmh
        + pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+(2.0*mA2+3.0*mHh2)*cos(alpha+3.0*beta)
              +16.0*m12_2*sin(alpha+beta),2)/(512.0*pow(cosb*sinb,4)) * ddpB0mAmAmH;

    WFRcomb3a = 0.5*mHl2*mHl2*(3.0-cos(2.0*beta))*sin(bma)*sin(bma) * ddpB000mh
        + 0.5*mHh2*mHh2*(3.0-cos(2.0*beta))*cos(bma)*cos(bma) * ddpB000mH
        + 2.0*(mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma)*sinb*sinb * ddpB00mHpmh
        + 2.0*(mHh2-mHp2)*(mHh2-mHp2)*sin(bma)*sin(bma)*sinb*sinb * ddpB00mHpmH
        + 2.0*(mA2-mHp2)*(mA2-mHp2)*sinb*sinb * ddpB00mHpmA
        + (mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma)*cosb*cosb * ddpB00mAmh
        + (mA2-mHh2)*(mA2-mHh2)*cosb*cosb*sin(bma)*sin(bma) * ddpB00mAmH
        + 1.5*mHl2*mHl2*sin(alpha)*sin(alpha)*sin(bma)*sin(bma) * ddpB0mh00
        + 2.0*(mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma)*sin(alpha)*sin(alpha) * ddpB0mh0mHp
        + (mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma)*sin(alpha)*sin(alpha) * ddpB0mh0mA
        + 9.0*sin(alpha)*sin(alpha)*pow(-mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta))
                                        +16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta),2)/(512.0*pow(cosb*sinb,4)) * ddpB0mhmhmh
        + sin(alpha)*sin(alpha)*pow((cos(alpha)/sinb+sin(alpha)/cosb)*(m12_2+cos(alpha)*sin(alpha)*(mHh2+2.0*mHl2-(3.0*m12_2)/(cosb*sinb))),2) * ddpB0mhmHmh
        + sin(alpha)*sin(alpha)*sin(bma)*sin(bma)*pow(-2.0*m12_2+(2.0*mHh2+mHl2-(3.0*m12_2)/(cosb*sinb))*sin(2.0*alpha),2)/(8.0*cosb*cosb*sinb*sinb) * ddpB0mhmHmH
        + (sin(alpha)*sin(alpha)*pow((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                     +cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb),2))/(64.0*pow(cosb*sinb,4)) * ddpB0mhmHpmHp
        + (sin(alpha)*sin(alpha)*pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(8.0*m12_2-(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb),2))/(128.0*pow(cosb*sinb,4)) * ddpB0mhmAmA
        + 1.5*mHh2*mHh2*cos(alpha)*cos(alpha)*cos(bma)*cos(bma) * ddpB0mH00
        + 2.0*(mHh2-mHp2)*(mHh2-mHp2)*cos(alpha)*cos(alpha)*sin(bma)*sin(bma) * ddpB0mH0mHp
        + (mA2-mHh2)*(mA2-mHh2)*cos(alpha)*cos(alpha)*sin(bma)*sin(bma) * ddpB0mH0mA
        + cos(alpha)*cos(alpha)*cos(bma)*cos(bma)*pow(m12_2+cos(alpha)*sin(alpha)*(mHh2-3.0*m12_2/(cosb*sinb))+mHl2*sin(2.0*alpha),2)/(2.0*cosb*cosb*sinb*sinb) * ddpB0mHmhmh
        + cos(alpha)*cos(alpha)*sin(bma)*sin(bma)*pow(m12_2*cosb*sinb+0.5*sin(2.0*alpha)*(3.0*m12_2-(2.0*mHh2+mHl2)*cosb*sinb),2)/pow(cosb*sinb,4) * ddpB0mHmHmh
        + 9.0*cos(alpha)*cos(alpha)*pow(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
                                        +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta),2)/(512.0*pow(cosb*sinb,4)) * ddpB0mHmHmH
        + (cos(alpha)*cos(alpha)*pow((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)
                                     +2.0*(mHh2+2.0*mHp2)*cos(bma)-(3.0*mHh2+2.0*mHp2)*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta),2))/(256.0*pow(cosb*sinb,4)) * ddpB0mHmHpmHp
        + (cos(alpha)*cos(alpha)*pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)
                                     -2.0*(2.0*mA2+mHh2)*cos(bma)+(2.0*mA2+3.0*mHh2)*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta),2))/(512.0*pow(cosb*sinb,4)) * ddpB0mHmAmA
        + 2.0*(mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma)*cosb*cosb * ddpB0mHp0mh
        + 2.0*(mHh2-mHp2)*(mHh2-mHp2)*sin(bma)*sin(bma)*cosb*cosb * ddpB0mHp0mH
        + 2.0*(mA2-mHp2)*(mA2-mHp2)*cosb*cosb * ddpB0mHp0mA
        + 2.0*cosb*cosb*pow((m12_2*cos(alpha+beta))/(cosb*cosb*sinb*sinb)-(mHl2*cos(bma)*cos(2.0*beta))/(cosb*sinb)-(mHl2+2.0*mHp2)*sin(bma),2) * ddpB0mHpmHpmh
        + 2.0*cosb*cosb*pow((mHh2+2.0*mHp2)*cos(bma)-(mHh2*cos(2.0*beta)*sin(bma))/(cosb*sinb)-(m12_2*sin(alpha+beta))/(cosb*cosb*sinb*sinb),2) * ddpB0mHpmHpmH
        + (mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma)*sinb*sinb * ddpB0mA0mh
        + (mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma)*sinb*sinb * ddpB0mA0mH
        + 2.0*(mA2-mHp2)*(mA2-mHp2)*sinb*sinb * ddpB0mA0mHp
        + pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(8.0*m12_2-(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb),2)/(64.0*pow(cosb,4)*sinb*sinb) * ddpB0mAmAmh
        + pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+2.0*mA2*cos(alpha+3.0*beta) 
               + 3.0*mHh2*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta),2)/(256.0*pow(cosb,4)*sinb*sinb) * ddpB0mAmAmH;

    WFRcomb3b = ((mHl2*mHl2*mHp2+mA2*(-2.0*mHl2*mHl2+mHl2*mHp2))*sin(2.0*bma)*sinb*cosb)/(mA2*mHp2) * B000mh
        + ((-mHh2*mHh2*mHp2+mA2*(2.0*mHh2*mHh2-mHh2*mHp2))*sin(2.0*bma)*sinb*cosb)/(mA2*mHp2) * B000mH
        + ((mHp2-mHl2)*cos(bma)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                 +cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb)))/(2.0*mHp2*sinb*cosb) * B00mHpmh
        + ((mHh2-mHp2)*sin(bma)*((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
                                 -2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta)))/(4.0*mHp2*sinb*cosb) * B00mHpmH
        + ((mHl2-mA2)*cos(bma)*((mHl2-2.0*mA2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                +cos(alpha+beta)*(-8.0*m12_2+(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb)))/(4.0*mA2*sinb*cosb) * B00mAmh
        + ((mHh2-mA2)*sin(bma)*((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+2.0*mA2*cos(alpha+3.0*beta)
                                +3.0*mHh2*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta)))/(8.0*mA2*sinb*cosb) * B00mAmH
        + (3.0*mHh2*mHl2*sin(2.0*alpha)*sin(2.0*bma))/(4.0*(mHh2-mHl2)) * B0mh00
        + ((mHl2-mHp2)*(mHp2-mHh2)*sin(2.0*alpha)*sin(2.0*bma))/(mHh2-mHl2) * B0mh0mHp
        - ((mA2-mHh2)*(mA2-mHl2)*sin(2.0*alpha)*sin(2.0*bma))/(2.0*(mHh2-mHl2)) * B0mh0mA
        + 3.0*cos(bma)*sin(2.0*alpha)*(m12_2+cos(alpha)*sin(alpha)*(mHh2-(3.0*m12_2)/(sinb*cosb))+mHl2*sin(2.0*alpha))
          *(-mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta))
            +16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta))/(32.0*(mHl2-mHh2)*pow(sinb*cosb,3)) * B0mhmhmh
        + (sin(2.0*bma)*sin(2.0*alpha)
           *(4.0*m12_2*m12_2+2.0*m12_2*(mHl2-mHh2)*sin(2.0*alpha)
             -(2.0*mHh2*mHh2+5.0*mHh2*mHl2+2.0*mHl2*mHl2-(9.0*m12_2*(mHh2+mHl2))/(sinb*cosb)
               +(9.0*m12_2*m12_2)/(sinb*sinb*cosb*cosb))*sin(2.0*alpha)*sin(2.0*alpha)))/(8.0*(mHh2-mHl2)*sinb*sinb*cosb*cosb) * B0mhmHmh
        - 3.0*sin(2.0*alpha)*sin(bma)*(m12_2-cos(alpha)*sin(alpha)*(2.0*mHh2+mHl2-(3.0*m12_2)/(sinb*cosb)))
          *(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
            +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta))/(32.0*(mHh2-mHl2)*pow(sinb*cosb,3)) * B0mhmHmH
        + sin(2.0*alpha)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb))
          *((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
             -2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(128.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mhmHpmHp
        + sin(2.0*alpha)*((mHl2-2.0*mA2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb))
          *((mHh2-2.0*mA2)*cos(alpha-5.0*beta)+2.0*(2.0*mA2+mHh2)*cos(bma)-2.0*mA2*cos(alpha+3.0*beta)
             -3.0*mHh2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(256.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mhmAmA
        - (3.0*mHh2*mHl2*sin(2.0*alpha)*sin(2.0*bma))/(4.0*(mHh2-mHl2)) * B0mH00
        + ((mHh2-mHp2)*(mHl2-mHp2)*sin(2.0*alpha)*sin(2.0*bma))/(mHh2-mHl2) * B0mH0mHp
        + ((mA2-mHh2)*(mA2-mHl2)*sin(2.0*alpha)*sin(2.0*bma))/(2.0*(mHh2-mHl2)) * B0mH0mA
        + 3.0*cos(bma)*sin(2.0*alpha)*(m12_2+cos(alpha)*sin(alpha)*(mHh2-(3.0*m12_2)/(sinb*cosb))+mHl2*sin(2.0*alpha))
          *(-mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta))
            +16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta))/(32.0*(mHh2-mHl2)*pow(sinb*cosb,3)) * B0mHmhmh
        + (sin(2.0*bma)*sin(2.0*alpha)*(-4.0*m12_2*m12_2+2.0*m12_2*(mHh2-mHl2)*sin(2.0*alpha)
                                        +(2.0*mHh2*mHh2+5.0*mHh2*mHl2+2.0*mHl2*mHl2
                                          -(9.0*m12_2*(mHh2+mHl2))/(sinb*cosb)
                                          +(9.0*m12_2*m12_2)/(sinb*sinb*cosb*cosb))*sin(2.0*alpha)*sin(2.0*alpha)))
          /(8.0*(mHh2-mHl2)*sinb*sinb*cosb*cosb) * B0mHmHmh
        + 3.0*sin(bma)*sin(2.0*alpha)*(m12_2-cos(alpha)*sin(alpha)*(2.0*mHh2+mHl2-(3.0*m12_2)/(sinb*cosb)))
          *(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
            +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta))/(32.0*(mHh2-mHl2)*pow(sinb*cosb,3)) * B0mHmHmH
        - sin(2.0*alpha)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb))
          *((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
            -2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(128.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mHmHpmHp
        - sin(2.0*alpha)*((mHl2-2.0*mA2)*cos(alpha-3.0*beta)*2.0*sinb*cosb+cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mA2)*2.0*sinb*cosb))
          *((mHh2-2.0*mA2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mA2)*cos(bma)-3.0*mHh2*cos(alpha+3.0*beta)
            -2.0*mA2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(256.0*(mHh2-mHl2)*pow(cosb*sinb,4)) * B0mHmAmA
        + (mHl2*(mHl2-mHp2)*sin(2.0*bma)*2.0*sinb*cosb)/mHp2 * B0mHp0mh
        - (mHh2*(mHh2-mHp2)*sin(2.0*bma)*2.0*sinb*cosb)/mHp2 * B0mHp0mH
        + (mHl2-mHp2)*cos(bma)*((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                +cos(alpha+beta)*(-8.0*m12_2+(3.0*mHl2+2.0*mHp2)*2.0*sinb*cosb))/(2.0*mHp2*sinb*cosb) * B0mHpmHpmh
        - (mHh2-mHp2)*sin(bma)*((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)
                                -3.0*mHh2*cos(alpha+3.0*beta)-2.0*mHp2*cos(alpha+3.0*beta)-16.0*m12_2*sin(alpha+beta))/(4.0*mHp2*sinb*cosb) * B0mHpmHpmH
        + (mHl2*(mA2-mHl2)*sin(bma)*cos(bma)*2.0*sinb*cosb)/mA2 * B0mA0mh
        + ((mHh2-mA2)*mHh2*sin(bma)*cos(bma)*2.0*sinb*cosb)/mA2 * B0mA0mH
        + ((mA2-mHl2)*cos(bma)*((-2.0*mA2+mHl2)*cos(alpha-3.0*beta)*2.0*sinb*cosb
                                +cos(alpha+beta)*(-8.0*m12_2+(2.0*mA2+3.0*mHl2)*2.0*sinb*cosb)))/(4.0*mA2*sinb*cosb) * B0mAmAmh
        +((mA2-mHh2)*sin(bma)*((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+2.0*mA2*cos(alpha+3.0*beta)
                               +3.0*mHh2*cos(alpha+3.0*beta)+16.0*m12_2*sin(alpha+beta)))/(8.0*mA2*sinb*cosb) * B0mAmAmH;

    WFRcomb4a = 0.5*mHl2*mHl2*sin(bma)*sin(bma) * ddpB000mh
        + 0.5*mHh2*mHh2*cos(bma)*cos(bma) * ddpB000mH
        + 0.5*(mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma) * ddpB00mAmh
        + 0.5*(mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma) * ddpB00mAmH
        + 0.75*mHl2*mHl2*sin(bma)*sin(bma) * ddpB0mh00
        + (mHl2-mHp2)*(mHl2-mHp2)*cos(bma)*cos(bma) * ddpB0mh0mHp
        + 0.5*(mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma) * ddpB0mh0mA
        + 9.0*pow(16.0*m12_2*cos(bma)*cos(bma)*cos(alpha+beta)
                  -mHl2*(3.0*sin(bma)+sin(3.0*bma)+sin(3.0*alpha+beta)+3.0*sin(alpha+3.0*beta)),2)/(1024.0*pow(cosb*sinb,4)) * ddpB0mhmhmh
        + 0.5*pow(cos(alpha)/sinb + sin(alpha)/cosb,2)
          *pow(m12_2+cos(alpha)*sin(alpha)*(mHh2+2.0*mHl2-3.0*m12_2/(cosb*sinb)),2) * ddpB0mhmHmh
        + (pow(-2.0*m12_2+(2.0*mHh2+mHl2-3.0*m12_2/(cosb*sinb))*sin(2.0*alpha),2)
           *sin(bma)*sin(bma))/(16.0*cosb*cosb*sinb*sinb) * ddpB0mhmHmH
        + pow((mHl2-2.0*mHp2)*cos(alpha-3.0*beta)*cosb*sinb
              +cos(alpha+beta)*(-4.0*m12_2+(3.0*mHl2+2.0*mHp2)*cosb*sinb),2)/(32.0*pow(cosb*sinb,4)) * ddpB0mhmHpmHp
        + pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*cosb*sinb
              +cos(alpha+beta)*(4.0*m12_2-(2.0*mA2+3.0*mHl2)*cosb*sinb),2)/(64.0*pow(cosb*sinb,4)) * ddpB0mhmAmA
        + 0.75*mHh2*mHh2*cos(bma)*cos(bma) * ddpB0mH00
        + (mHh2 - mHp2)*(mHh2 - mHp2)*sin(bma)*sin(bma) * ddpB0mH0mHp
        + 0.5*(mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma) * ddpB0mH0mA
        + 0.25*pow(cos(alpha)/sinb + sin(alpha)/cosb,2)
          *pow(m12_2+cos(alpha)*sin(alpha)*(mHh2+2.0*mHl2-3.0*m12_2/(cosb*sinb)),2) * ddpB0mHmhmh
        + (pow(-2.0*m12_2+(2.0*mHh2+mHl2-3.0*m12_2/(cosb*sinb))*sin(2.0*alpha),2)
           *sin(bma)*sin(bma))/(8.0*cosb*cosb*sinb*sinb) * ddpB0mHmHmh
        + 9.0*pow(mHh2*(-3.0*cos(bma)+cos(3.0*bma)-cos(3.0*alpha+beta)+3.0*cos(alpha+3.0*beta))
                  +16.0*m12_2*sin(bma)*sin(bma)*sin(alpha+beta),2)/(1024.0*pow(cosb*sinb,4)) * ddpB0mHmHmH
        + pow((mHh2-2.0*mHp2)*cos(alpha-5.0*beta)+2.0*(mHh2+2.0*mHp2)*cos(bma)-(3.0*mHh2+2.0*mHp2)*cos(alpha+3.0*beta)
           -16.0*m12_2*sin(alpha+beta),2)/(512*pow(cosb*sinb,4)) * ddpB0mHmHpmHp
        + pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+(2.0*mA2+3.0*mHh2)*cos(alpha+3.0*beta)
           +16.0*m12_2*sin(alpha+beta),2)/(1024*pow(cosb*sinb,4)) * ddpB0mHmAmA
        + 0.5*(mA2-mHl2)*(mA2-mHl2)*cos(bma)*cos(bma) * ddpB0mA0mh
        + 0.5*(mA2-mHh2)*(mA2-mHh2)*sin(bma)*sin(bma) * ddpB0mA0mH
        + (mA2-mHp2)*(mA2-mHp2) * ddpB0mA0mHp
        + pow((2.0*mA2-mHl2)*cos(alpha-3.0*beta)*2.0*cosb*sinb
              +cos(alpha+beta)*(8.0*m12_2-(2.0*mA2+3.0*mHl2)*2.0*cosb*sinb),2)/(128.0*pow(cosb*sinb,4)) * ddpB0mAmAmh
        + pow((2.0*mA2-mHh2)*cos(alpha-5.0*beta)-2.0*(2.0*mA2+mHh2)*cos(bma)+(2.0*mA2+3.0*mHh2)*cos(alpha+3.0*beta)
              +16.0*m12_2*sin(alpha+beta),2)/(512.0*pow(cosb*sinb,4)) * ddpB0mAmAmH;
//    std::cout<<"B00mHpmH = "<<B00mHpmH<<std::endl;
//    std::cout<<"B00mHpmh = "<<B00mHpmh<<std::endl;
//    std::cout<<"B0mh0mHp = "<<B0mh0mHp<<std::endl;
//    std::cout<<"B00mAmh = "<<B00mAmh<<std::endl;
//    std::cout<<"B00mAmH = "<<B00mAmH<<std::endl;
//    std::cout<<"B000mh = "<<B000mh<<std::endl;
//    std::cout<<"B000mH = "<<B000mH<<std::endl;
//    std::cout<<"B0mA0mh = "<<B0mA0mh<<std::endl;
//    std::cout<<"B0mA0mH = "<<B0mA0mH<<std::endl;
//    std::cout<<"B0mHmAmA = "<<B0mHmAmA<<std::endl;
//    std::cout<<"B0mhmAmA = "<<B0mhmAmA<<std::endl;
//    std::cout<<"B0mH0mHp = "<<B0mH0mHp<<std::endl;
//    std::cout<<"B0mh00 = "<<B0mh00<<std::endl;
//    std::cout<<"B0mH00 = "<<B0mH00<<std::endl;
//    std::cout<<"B0mh0mA = "<<B0mh0mA<<std::endl;
//    std::cout<<"B0mH0mA = "<<B0mH0mA<<std::endl;
//    std::cout<<"B0mAmAmh = "<<B0mAmAmh<<std::endl;
//    std::cout<<"B0mAmAmH = "<<B0mAmAmH<<std::endl;
//    std::cout<<"B0mHp0mh = "<<B0mHp0mh<<std::endl;
//    std::cout<<"B0mHp0mH = "<<B0mHp0mH<<std::endl;
//    std::cout<<"B0mHpmHpmH = "<<B0mHpmHpmH<<std::endl;
//    std::cout<<"B0mHpmHpmh = "<<B0mHpmHpmh<<std::endl;
//    std::cout<<"B0mhmhmh = "<<B0mhmhmh<<std::endl;
//    std::cout<<"B0mhmHmh = "<<B0mhmHmh<<std::endl;
//    std::cout<<"B0mhmHmH = "<<B0mhmHmH<<std::endl;
//    std::cout<<"B0mHmHmH = "<<B0mHmHmH<<std::endl;
//    std::cout<<"B0mhmHpmHp = "<<B0mhmHpmHp<<std::endl;
//    std::cout<<"B0mHmHpmHp = "<<B0mHmHpmHp<<std::endl;
//    std::cout<<"B0mHmhmh = "<<B0mHmhmh<<std::endl;
//    std::cout<<"B0mHmHmh = "<<B0mHmHmh<<std::endl;
//    std::cout<<"ddpB00mHpmA = "<<ddpB00mHpmA<<std::endl;
//    std::cout<<"ddpB000mh = "<<ddpB000mh<<std::endl;
//    std::cout<<"ddpB000mH = "<<ddpB000mH<<std::endl;
//    std::cout<<"ddpB00mAmh = "<<ddpB00mAmh<<std::endl;
//    std::cout<<"ddpB00mAmH = "<<ddpB00mAmH<<std::endl;
//    std::cout<<"ddpB00mHpmh = "<<ddpB00mHpmh<<std::endl;
//    std::cout<<"ddpB00mHpmH = "<<ddpB00mHpmH<<std::endl;
//    std::cout<<"ddpB0mA0mh = "<<ddpB0mA0mh<<std::endl;
//    std::cout<<"ddpB0mA0mH = "<<ddpB0mA0mH<<std::endl;
//    std::cout<<"ddpB0mA0mHp = "<<ddpB0mA0mHp<<std::endl;
//    std::cout<<"ddpB0mAmAmh = "<<ddpB0mAmAmh<<std::endl;
//    std::cout<<"ddpB0mAmAmH = "<<ddpB0mAmAmH<<std::endl;
//    std::cout<<"ddpB0mh00 = "<<ddpB0mh00<<std::endl;
//    std::cout<<"ddpB0mH00 = "<<ddpB0mH00<<std::endl;
//    std::cout<<"ddpB0mh0mA = "<<ddpB0mh0mA<<std::endl;
//    std::cout<<"ddpB0mH0mA = "<<ddpB0mH0mA<<std::endl;
//    std::cout<<"ddpB0mh0mHp = "<<ddpB0mh0mHp<<std::endl;
//    std::cout<<"ddpB0mH0mHp = "<<ddpB0mH0mHp<<std::endl;
//    std::cout<<"ddpB0mhmAmA = "<<ddpB0mhmAmA<<std::endl;
//    std::cout<<"ddpB0mHmAmA = "<<ddpB0mHmAmA<<std::endl;
//    std::cout<<"ddpB0mhmhmh = "<<ddpB0mhmhmh<<std::endl;
//    std::cout<<"ddpB0mhmHmh = "<<ddpB0mhmHmh<<std::endl;
//    std::cout<<"ddpB0mhmHmH = "<<ddpB0mhmHmH<<std::endl;
//    std::cout<<"ddpB0mHmhmh = "<<ddpB0mHmhmh<<std::endl;
//    std::cout<<"ddpB0mHmHmh = "<<ddpB0mHmHmh<<std::endl;
//    std::cout<<"ddpB0mHmHmH = "<<ddpB0mHmHmH<<std::endl;
//    std::cout<<"ddpB0mhmHpmHp = "<<ddpB0mhmHpmHp<<std::endl;
//    std::cout<<"ddpB0mHmHpmHp = "<<ddpB0mHmHpmHp<<std::endl;
//    std::cout<<"ddpB0mHp0mA = "<<ddpB0mHp0mA<<std::endl;
//    std::cout<<"ddpB0mHp0mh = "<<ddpB0mHp0mh<<std::endl;
//    std::cout<<"ddpB0mHp0mH = "<<ddpB0mHp0mH<<std::endl;
//    std::cout<<"ddpB0mHpmHpmh = "<<ddpB0mHpmHpmh<<std::endl;
//    std::cout<<"ddpB0mHpmHpmH = "<<ddpB0mHpmHpmH<<std::endl;
//    std::cout<<"WFRcomb1a = "<<WFRcomb1a<<std::endl;
//    std::cout<<"WFRcomb1b = "<<WFRcomb1b<<std::endl;
//    std::cout<<"WFRcomb2a = "<<WFRcomb2a<<std::endl;
//    std::cout<<"WFRcomb3a = "<<WFRcomb3a<<std::endl;
//    std::cout<<"WFRcomb3b = "<<WFRcomb3b<<std::endl;
//    std::cout<<"WFRcomb4a = "<<WFRcomb4a<<std::endl;
    }
    WFRcomb1=-(WFRcomb1a+WFRcomb1b)/(vev*vev);
    WFRcomb2=-WFRcomb2a/(vev*vev);
    WFRcomb3=-(WFRcomb3a+WFRcomb3b)/(vev*vev);
    WFRcomb4=-WFRcomb4a/(vev*vev);
}

void THDMcache::updateCache()
{
    Q_THDM=myTHDM->getQ_THDM();
    bma=myTHDM->getbma();
    tanb=myTHDM->gettanb();
    m12_2=myTHDM->getm12_2();
    mHh2=myTHDM->getmHh2();
    mA2=myTHDM->getmA2();
    mHp2=myTHDM->getmHp2();
    Rpeps=myTHDM->getRpeps();
    MW=MWTHDM(myTHDM->Mw_tree());
    cW2=cW2THDM(myTHDM->c02());
    mHl=myTHDM->getMHl();
    vev=myTHDM->v();
    Ale=myTHDM->getAle();
    Als=myTHDM->getAlsMz();
    Mt=myTHDM->getQuarks(QCD::TOP).getMass();
    Mb=myTHDM->getQuarks(QCD::BOTTOM).getMass();   
    Mtau=myTHDM->getLeptons(StandardModel::TAU).getMass();
    Mc=myTHDM->getQuarks(QCD::CHARM).getMass();
    Ms=myTHDM->getQuarks(QCD::STRANGE).getMass();
    Mmu=myTHDM->getLeptons(StandardModel::MU).getMass();
    Mu=myTHDM->getQuarks(QCD::UP).getMass();
    Md=myTHDM->getQuarks(QCD::DOWN).getMass();
    Me=myTHDM->getLeptons(StandardModel::ELECTRON).getMass();
    MZ=myTHDM->getMz();
    modelflag=myTHDM->getModelTypeflag();
    WFRflag=myTHDM->getWFRflag();

    computeSignalStrengthQuantities();
    computeHHquantities();
    computeAquantities();
    runTHDMparameters();
    computeWFRcombinations();
}
