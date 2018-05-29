/* 
 * Copyright (C) 2016 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "GeneralTHDMcache.h"
#include <fstream>
#include "gslpp.h"
#include <sstream>
#include <string>

//#include "log_cs_ggH_13.h"



GeneralTHDMcache::GeneralTHDMcache(const StandardModel& SM_i)
:   Mu_GTHDM(3,3,0.), Md_GTHDM(3,3,0.), Ml_GTHDM(3,3,0.),
    Nu_GTHDM(3,3,0.), Nd_GTHDM(3,3,0.), Nl_GTHDM(3,3,0.),
    Yu1_GTHDM(3,3,0.), Yu2_GTHDM(3,3,0.), Yd1_GTHDM(3,3,0.), Yd2_GTHDM(3,3,0.),
    Yl1_GTHDM(3,3,0.), Yl2_GTHDM(3,3,0.),
        br_tt(19961, 2, 0.),
        br_bb(19961, 2, 0.),
        br_tautau(19961, 2, 0.),
        br_cc(19961, 2, 0.),
        br_mumu(19961, 2, 0.),
        br_ZZ(19961, 2, 0.),
        br_WW(19961, 2, 0.),
        GammaHtot_SM(19961, 2, 0.),
        log_cs_ggH_8(199, 2, 0.),
        log_cs_VBF_8(199, 2, 0.),
        log_cs_WH_8(199, 2, 0.),
        log_cs_ZH_8(199, 2, 0.),
        log_cs_ggH_13(199, 2, 0.),
        log_cs_VBF_13(199, 2, 0.),
        log_cs_WH_13(199, 2, 0.),
        log_cs_ZH_13(199, 2, 0.),
        log_cs_ttH_8(199, 2, 0.),
        log_cs_ttH_13(199, 2, 0.),
        log_cs_bbH_8(199, 2, 0.),
        log_cs_bbH_13(199, 2, 0.),
        log_cs_ggA_8(199, 2, 0.),
        log_cs_ttA_8(199, 2, 0.),
        log_cs_bbA_8(199, 2, 0.),
        log_cs_ggA_13(199, 2, 0.),
        log_cs_ttA_13(199, 2, 0.),
        log_cs_bbA_13(199, 2, 0.),
        log_cs_ggHp_8(744, 3, 0.),
        log_cs_ggHp_13(1104, 3, 0.),
        csrH_top_8(199, 2, 0.),
        csrH_bottom_8(199, 2, 0.),
        csrA_top_8(199, 2, 0.),
        csrA_bottom_8(199, 2, 0.),
        csrH_top_13(199, 2, 0.),
        csrH_bottom_13(199, 2, 0.),
        csrA_top_13(199, 2, 0.),
        csrA_bottom_13(199, 2, 0.),
        ATLAS8_pp_phi_gaga(108, 2, 0.),
        ATLAS8_pp_phi_Zga_llga(141, 2, 0.),
        ATLAS8_gg_phi_tautau(92, 2, 0.),
        ATLAS8_bb_phi_tautau(92, 2, 0.),
        ATLAS8_gg_A_hZ_tautauZ(79, 2, 0.),
        ATLAS8_gg_A_hZ_bbZ(79, 2, 0.),
        ATLAS8_gg_phi_tt(53, 2, 0.),
        ATLAS8_gg_H_WW(13,2,0.),
        ATLAS8_VBF_H_WW(13,2,0.),
        ATLAS8_gg_H_ZZ(173,2,0.),
        ATLAS8_VBF_H_ZZ(173,2,0.),
        ATLAS8_gg_H_hh(75,2,0.),
        ATLAS8_pp_phi_gaga_e(108, 2, 0.),
        ATLAS8_pp_phi_Zga_llga_e(141, 2, 0.),
        ATLAS8_gg_phi_tautau_e(92, 2, 0.),
        ATLAS8_bb_phi_tautau_e(92, 2, 0.),
        ATLAS8_gg_A_hZ_tautauZ_e(79, 2, 0.),
        ATLAS8_gg_A_hZ_bbZ_e(79, 2, 0.),
        ATLAS8_gg_phi_tt_e(53, 2, 0.),
        ATLAS8_gg_H_WW_e(13,2,0.),
        ATLAS8_VBF_H_WW_e(13,2,0.),
        ATLAS8_gg_H_ZZ_e(173,2,0.),
        ATLAS8_VBF_H_ZZ_e(173,2,0.),
        ATLAS8_gg_H_hh_e(75,2,0.),
        CMS8_mu_pp_H_VV(172, 2, 0.),
        CMS8_mu_pp_H_VV_e(172, 2, 0.),
        CMS8_gg_A_hZ_bbll(16, 2, 0.),
        CMS8_pp_H_hh(71, 2, 0.),
        CMS8_pp_H_hh_gagabb(85, 2, 0.),
        CMS8_pp_H_hh_bbbb(167, 2, 0.),
        CMS8_bb_phi_bb(81, 2, 0.),
        CMS8_gg_phi_tautau(92,2,0.),
        CMS8_bb_phi_tautau(92,2,0.),
        CMS8_gg_phi_gaga(141,2,0.),
        CMS8_pp_A_Zga_llga(101,2,0.),
        CMS8_pp_phi_Zga(101,2,0.),
        CMS8_gg_H_hh_bbtautau(10,2,0.),
        CMS8_gg_A_hZ_tautaull(14,2,0.),
        CMS8_pp_A_HZ_bbll(28718, 3, 0.),
        CMS8_pp_H_AZ_bbll(29050, 3, 0.),
        CMS8_pp_A_HZ_tautaull(400, 3, 0.),
        CMS8_pp_H_AZ_tautaull(400, 3, 0.),
        CMS8_gg_A_hZ_bbll_e(16, 2, 0.),
        CMS8_pp_H_hh_e(71, 2, 0.),
        CMS8_pp_H_hh_gagabb_e(85, 2, 0.),
        CMS8_pp_H_hh_bbbb_e(167, 2, 0.),
        CMS8_bb_phi_bb_e(81, 2, 0.),
        CMS8_gg_phi_tautau_e(92,2,0.),
        CMS8_bb_phi_tautau_e(92,2,0.),
        CMS8_gg_phi_gaga_e(141,2,0.),
        CMS8_pp_A_Zga_llga_e(101,2,0.),
        CMS8_gg_H_hh_bbtautau_e(10,2,0.),
        CMS8_gg_A_hZ_tautaull_e(14,2,0.),
//        CMS_ggF_phi_gaga_ep1(141,2,0.),
//        CMS_gg_phi_gaga_ep2(141,2,0.),
//        CMS_ggF_phi_gaga_em1(141,2,0.),
//        CMS_ggF_phi_gaga_em2(141,2,0.),
        ATLAS13_bb_phi_tt(61,2,0.),
        ATLAS13_tt_phi_tt(61,2,0.),
        ATLAS13_gg_phi_tautau(206,2,0.),
        ATLAS13_bb_phi_tautau(206,2,0.),
        ATLAS13_pp_phi_gaga(251,2,0.),
        ATLAS13_pp_phi_Zga(216,2,0.),
        ATLAS13_gg_phi_Zga_llga(216,2,0.),
        ATLAS13_gg_H_ZZ_llllnunu(101,2,0.),
        ATLAS13_VBF_H_ZZ_llllnunu(101,2,0.),
        ATLAS13_gg_H_ZZ_llnunu(71,2,0.),
        ATLAS13_gg_H_ZZ_llll(81,2,0.),
        ATLAS13_VBF_H_ZZ_llll(81,2,0.),
        ATLAS13_gg_H_ZZ_qqllnunu(271,2,0.),
        ATLAS13_VBF_H_ZZ_qqllnunu(271,2,0.),
        ATLAS13_gg_H_ZZ_llqq(271,2,0.),
        ATLAS13_VBF_H_ZZ_llqq(271,2,0.),
        ATLAS13_gg_H_ZZ_nunuqq(251,2,0.),
        ATLAS13_gg_H_WW_enumumu(381,2,0.),
        ATLAS13_VBF_H_WW_enumumu(281,2,0.),
        ATLAS13_gg_H_WW_lnuqq(271,2,0.),
        ATLAS13_VBF_H_WW_lnuqq(271,2,0.),
        ATLAS13_pp_H_VV_qqqq(181,2,0.),
        ATLAS13_pp_H_hh_bbbb(271,2,0.),
        ATLAS13_pp_H_hh_gagabb(26,2,0.),
        ATLAS13_pp_H_hh_gagaWW(25,2,0.),
        ATLAS13_gg_A_Zh_Zbb(181,2,0.),
        ATLAS13_bb_A_Zh_Zbb(181,2,0.),
        ATLAS13_bb_phi_tt_e(61,2,0.),
        ATLAS13_tt_phi_tt_e(61,2,0.),
        ATLAS13_gg_phi_tautau_e(206,2,0.),
        ATLAS13_bb_phi_tautau_e(206,2,0.),
        ATLAS13_pp_phi_gaga_e(251,2,0.),
        ATLAS13_pp_phi_Zga_e(216,2,0.),
        ATLAS13_gg_phi_Zga_llga_e(216,2,0.),
        ATLAS13_gg_H_ZZ_llllnunu_e(101,2,0.),
        ATLAS13_VBF_H_ZZ_llllnunu_e(101,2,0.),
        ATLAS13_gg_H_ZZ_llnunu_e(71,2,0.),
        ATLAS13_gg_H_ZZ_llll_e(81,2,0.),
        ATLAS13_VBF_H_ZZ_llll_e(81,2,0.),
        ATLAS13_gg_H_ZZ_qqllnunu_e(271,2,0.),
        ATLAS13_VBF_H_ZZ_qqllnunu_e(271,2,0.),
        ATLAS13_gg_H_ZZ_llqq_e(271,2,0.),
        ATLAS13_VBF_H_ZZ_llqq_e(271,2,0.),
        ATLAS13_gg_H_ZZ_nunuqq_e(251,2,0.),
        ATLAS13_gg_H_WW_enumumu_e(381,2,0.),
        ATLAS13_VBF_H_WW_enumumu_e(281,2,0.),
        ATLAS13_gg_H_WW_lnuqq_e(271,2,0.),
        ATLAS13_VBF_H_WW_lnuqq_e(271,2,0.),
        ATLAS13_pp_H_VV_qqqq_e(181,2,0.),
        ATLAS13_pp_H_hh_bbbb_e(271,2,0.),
        ATLAS13_pp_H_hh_gagabb_e(26,2,0.),
        ATLAS13_pp_H_hh_gagaWW_e(25,2,0.),
        ATLAS13_gg_A_Zh_Zbb_e(181,2,0.),
        ATLAS13_bb_A_Zh_Zbb_e(181,2,0.),
        CMS13_pp_phi_bb(66,2,0.),
        CMS13_gg_phi_tautau(312,2,0.),
        CMS13_bb_phi_tautau(312,2,0.),
        CMS13_gg_phi_gaga(351,2,0.),
        CMS13_pp_phi_Zga_llga(171,2,0.),
        CMS13_pp_phi_Zga_qqga(236,2,0.),
        CMS13_ggF_phi_Zga(366,2,0.),
        CMS13_pp_H_ZZ_llnunu(191,2,0.),
        CMS13_gg_H_ZZ_llnunu(131,2,0.),
        CMS13_VBF_H_ZZ_llnunu(131,2,0.),
        CMS13_pp_H_ZZ_llll(241,2,0.),
        CMS13_VBFVH_H_ZZ_llll(241,2,0.),
        CMS13_pp_H_ZZ_llqq(151,2,0.),
        CMS13_ggFVBF_H_WW_lnulnu(81,2,0.),
        CMS13_pp_H_hh_bbbb(95,2,0.),
        CMS13_ggF_H_hh_bbbb(226,2,0.),
        CMS13_pp_H_hh_gagabb(66,2,0.),
        CMS13_pp_H_hh_bbtautau(66,2,0.),
        CMS13_pp_H_hh_bbtautau1(66,2,0.),
        CMS13_pp_H_hh_bblnulnu(65,2,0.),
        CMS13_pp_H_hh_bbVV(65,2,0.),
        CMS13_pp_phi_bb_e(66,2,0.),
        CMS13_gg_phi_tautau_e(312,2,0.),
        CMS13_bb_phi_tautau_e(312,2,0.),
        CMS13_gg_phi_gaga_e(351,2,0.),
        CMS13_pp_phi_Zga_llga_e(171,2,0.),
        CMS13_pp_phi_Zga_qqga_e(236,2,0.),
        CMS13_ggF_phi_Zga_e(366,2,0.),
        CMS13_pp_H_ZZ_llnunu_e(191,2,0.),
        CMS13_gg_H_ZZ_llnunu_e(131,2,0.),
        CMS13_VBF_H_ZZ_llnunu_e(131,2,0.),
        CMS13_pp_H_ZZ_llll_e(241,2,0.),
        CMS13_VBFVH_H_ZZ_llll_e(241,2,0.),
        CMS13_pp_H_ZZ_llqq_e(151,2,0.),
        CMS13_ggFVBF_H_WW_lnulnu_e(81,2,0.),
        CMS13_pp_H_hh_bbbb_e(95,2,0.),
        CMS13_ggF_H_hh_bbbb_e(226,2,0.),
        CMS13_pp_H_hh_gagabb_e(66,2,0.),
        CMS13_pp_H_hh_bbtautau_e(66,2,0.),
        CMS13_pp_H_hh_bbtautau1_e(66,2,0.),
        CMS13_pp_H_hh_bblnulnu_e(65,2,0.),
        CMS13_pp_H_hh_bbVV_e(65,2,0.),
        temp1(1,2,0.), temp2(1,2,0.), temp3(1,2,0.), temp4(1,2,0.), temp5(1,2,0.), temp6(1,2,0.), temp7(1,2,0.), temp8(1,2,0.), temp9(1,2,0.), temp10(1,2,0.),
        temp11(1,2,0.), temp12(1,2,0.), temp13(1,2,0.), temp14(1,2,0.), temp15(1,2,0.), temp16(1,2,0.), temp17(1,2,0.), temp18(1,2,0.), temp19(1,2,0.), temp20(1,2,0.),
        temp21(1,2,0.), temp22(1,2,0.), temp23(1,2,0.), temp24(1,2,0.), temp25(1,2,0.), temp26(1,2,0.), temp27(1,2,0.), temp28(1,2,0.), temp29(1,2,0.), temp30(1,2,0.),
        temp31(1,2,0.), temp32(1,2,0.), temp33(1,2,0.), temp34(1,2,0.), temp35(1,2,0.), temp36(1,2,0.), temp37(1,2,0.), temp38(1,2,0.), temp39(1,2,0.), temp40(1,2,0.),
        temp1e(1,2,0.), temp2e(1,2,0.), temp3e(1,2,0.), temp4e(1,2,0.), temp5e(1,2,0.), temp6e(1,2,0.), temp7e(1,2,0.), temp8e(1,2,0.), temp9e(1,2,0.), temp10e(1,2,0.),
        temp11e(1,2,0.), temp12e(1,2,0.), temp13e(1,2,0.), temp14e(1,2,0.), temp15e(1,2,0.), temp16e(1,2,0.), temp17e(1,2,0.), temp18e(1,2,0.), temp19e(1,2,0.), temp20e(1,2,0.),
        temp21e(1,2,0.), temp22e(1,2,0.), temp23e(1,2,0.), temp24e(1,2,0.), temp25e(1,2,0.), temp26e(1,2,0.), temp27e(1,2,0.), temp28e(1,2,0.), temp29e(1,2,0.), temp30e(1,2,0.),
        temp31e(1,2,0.), temp32e(1,2,0.), temp33e(1,2,0.), temp34e(1,2,0.), temp35e(1,2,0.), temp36e(1,2,0.), temp37e(1,2,0.), temp38e(1,2,0.), temp39e(1,2,0.), temp40e(1,2,0.),
        ATLAS8_pp_Hpm_taunu(83,2,0.),
        ATLAS8_pp_Hpm_tb(41,2,0.),
        ATLAS8_pp_Hpm_taunu_e(83,2,0.),
        ATLAS8_pp_Hpm_tb_e(41,2,0.),
        CMS8_pp_Hp_taunu(43,2,0.),
        CMS8_pp_Hp_tb(43,2,0.),
        CMS8_pp_Hp_taunu_e(43,2,0.),
        CMS8_pp_Hp_tb_e(43,2,0.),
        ATLAS13_pp_Hpm_taunu(181,2,0.),
        ATLAS13_pp_Hp_tb1(71,2,0.),
        ATLAS13_pp_Hp_tb2(181,2,0.),
        ATLAS13_pp_Hpm_taunu_e(181,2,0.),
        ATLAS13_pp_Hp_tb1_e(71,2,0.),
        ATLAS13_pp_Hp_tb2_e(181,2,0.),
        CMS13_pp_Hpm_taunu(283,2,0.),
        CMS13_pp_Hpm_taunu_e(283,2,0.),
        arraybsgamma(1111, 3, 0.),
    myGTHDM(static_cast<const GeneralTHDM*> (&SM_i))
{
    read();
}
GeneralTHDMcache::~GeneralTHDMcache()
{}

/////////////////////////////////////////////////////////////////////////////////////////////////

int GeneralTHDMcache::CacheCheck(const gslpp::complex cache[][CacheSize], 
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

int GeneralTHDMcache::CacheCheckReal(const double cache[][CacheSize], 
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


void GeneralTHDMcache::CacheShift(gslpp::complex cache[][CacheSize], const int NumPar, 
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

void GeneralTHDMcache::CacheShiftReal(double cache[][CacheSize], const int NumPar,
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

gslpp::matrix<double> GeneralTHDMcache::readTable(std::string filename, int rowN, int colN){

    std::ifstream INfile;
    std::string lineTab;
    INfile.open( filename.c_str() );
    if(INfile.fail()){
        std::cout<<"error: in GeneralTHDMcache, table doesn't exist!"<<std::endl;
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

double GeneralTHDMcache::interpolate(gslpp::matrix<double> arrayTab, double x){

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

double GeneralTHDMcache::interpolate2D(gslpp::matrix<double> arrayTab, double x, double y){

    int rowN=arrayTab.size_i();

    double xmin = arrayTab(0,0);
    double xmax = arrayTab(rowN-1,0);
    double ymin = arrayTab(0,1);
    double ymax = arrayTab(rowN-1,1);
    double intervalx = arrayTab(1,0)-arrayTab(0,0);
    int i=1;
    do i++;
    while(arrayTab(i,1)-arrayTab(i-1,1)==0&&i<30000);
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

void GeneralTHDMcache::read(){
  std::stringstream br1,br2,br3,br4,br5,br6,br7;
    std::stringstream dw1;
    std::stringstream cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8,cs9;
    std::stringstream cs11,cs12,cs13,cs14,cs15,cs16,cs17,cs18,cs19;
    std::stringstream cs20,cs21;
    std::stringstream csr1,csr2,csr3,csr4;
    std::stringstream csr11,csr12,csr13,csr14;
    std::stringstream ex1,ex2,ex3,ex4,ex5,ex6,ex7,ex8,ex9,ex10,ex11,ex12,ex13,ex14,ex15,ex16,ex17,ex18,ex19,ex20,ex21,ex22,ex23;
    std::stringstream ex1e,ex2e,ex3e,ex4e,ex5e,ex6e,ex7e,ex8e,ex9e,ex10e,ex11e,ex12e,ex13e,ex14e,ex15e,ex16e,ex17e,ex18e,ex19e,ex20e,ex21e,ex22e,ex23e;
//    std::stringstream ex14ep2,ex14em2;
    std::stringstream ex24,ex25,ex26,ex27,ex28,ex29,ex30,ex31,ex32,ex33,ex34,ex35,ex36,ex37,ex38,ex39,ex40,ex41,ex42,ex43,ex44,\
            ex45,ex46,ex47,ex48,ex49,ex50,ex51,ex52,ex53,ex54,ex55,ex56;
    std::stringstream ex24e,ex25e,ex26e,ex27e,ex28e,ex29e,ex30e,ex31e,ex32e,ex33e,ex34e,ex35e,ex36e,ex37e,ex38e,ex39e,ex40e,ex41e,ex42e,ex43e,ex44e,\
            ex45e,ex46e,ex47e,ex48e,ex49e,ex50e,ex51e,ex52e,ex53e,ex54e,ex55e,ex56e;
    std::stringstream ex57,ex58,ex59,ex60,ex61,ex62,ex63,ex64,ex65,ex66,ex67,ex68,ex69,ex70,ex71,ex72,ex73,ex74,ex75,ex76,ex77,\
            ex78,ex79,ex80,ex81,ex82,ex83,ex84,ex85,ex86,ex87,ex88,ex89,ex90,ex91,ex92,ex93,ex94,ex95,ex96,ex97,ex98;
    std::stringstream ex57e,ex58e,ex59e,ex60e,ex61e,ex62e,ex63e,ex64e,ex65e,ex66e,ex67e,ex68e,ex69e,ex70e,ex71e,ex72e,ex73e,ex74e,ex75e,ex76e,ex77e,\
            ex78e,ex79e,ex80e,ex81e,ex82e,ex83e,ex84e,ex85e,ex86e,ex87e,ex88e,ex89e,ex90e,ex91e,ex92e,ex93e,ex94e,ex95e,ex96e,ex97e,ex98e;
    std::stringstream ex99,ex100,ex101,ex102,ex103,ex104,ex105,ex106,ex107,ex108,ex109,ex110,ex111,ex112,ex113,ex114,ex115,ex116,ex117,ex118,ex119,ex120;
    std::stringstream ex99e,ex100e,ex101e,ex102e,ex103e,ex104e,ex105e,ex106e,ex107e,ex108e,ex109e,ex110e,ex111e,ex112e,ex113e,ex114e,ex115e,ex116e,ex117e,ex118e,ex119e,ex120e;
    std::stringstream ex121,ex122,ex123,ex124;
    std::stringstream bsg1;

       std::cout<<"reading tables"<<std::endl;

//    std::cout << "HEPFITTABS = " << getenv("HEPFITPATH") << std::endl;
    std::stringstream path;
    path << getenv("HEPFITTABS") << "/THDM/tabs/";
    std::string tablepath=path.str();

    br1 << tablepath << "br1.dat";
    br_tt = readTable(br1.str(),19961,2);
    
//// THIS IS FOR THE FUTURE IMPLEMENTATION INTO HEADERS:
//    std::cout<<"br_tt="<<br_tt<<std::endl;
//    double brtt1[4][2];
//    brtt1[0][1]=1;
//        gslpp::matrix<double> brtt1(19861,2,0.);
//    std::stringstream br1x;
//    br1x << "log_cs_ggH_13.h";
//      //brtt1(2)=(3.,4.);
//      brtt1=readTable(br1x.str(),20,2);
//    std::cout<<"brtt1="<<bla1<<std::endl;


    br2 << tablepath << "br2.dat";
    br_bb = readTable(br2.str(),19961,2);
    br3 << tablepath << "br3.dat";
    br_tautau = readTable(br3.str(),19961,2); 
    br4 << tablepath << "br4.dat";
    br_cc = readTable(br4.str(),19961,2);
    br5 << tablepath << "br5.dat";
    br_mumu = readTable(br5.str(),19961,2);
    br6 << tablepath << "br6.dat";
    br_ZZ = readTable(br6.str(),19961,2);
    br7 << tablepath << "br7.dat";
    br_WW = readTable(br7.str(),19961,2);
    dw1 << tablepath << "dw1.dat";
    GammaHtot_SM = readTable(dw1.str(),19961,2);
   // std::cout << "GammaHtot_SM = " << GammaHtot_SM << std::endl;
    cs1 << tablepath << "log_cs_ggH_8.dat";
    log_cs_ggH_8 = readTable(cs1.str(),199,2);
    cs11 << tablepath << "log_cs_ggH_13.dat";
    log_cs_ggH_13 = readTable(cs11.str(),199,2);
    cs2 << tablepath << "log_cs_VBF_8.dat";
    log_cs_VBF_8 = readTable(cs2.str(),199,2);
    cs12 << tablepath << "log_cs_VBF_13.dat";
    log_cs_VBF_13 = readTable(cs12.str(),199,2);
    cs3 << tablepath << "log_cs_WH_8.dat";
    log_cs_WH_8 = readTable(cs3.str(),199,2);
    cs13 << tablepath << "log_cs_WH_13.dat";
    log_cs_WH_13 = readTable(cs13.str(),199,2);
    cs4 << tablepath << "log_cs_ZH_8.dat";
    log_cs_ZH_8 = readTable(cs4.str(),199,2);
    cs14 << tablepath << "log_cs_ZH_13.dat";
    log_cs_ZH_13 = readTable(cs14.str(),199,2);
    cs5 << tablepath << "log_cs_ttH_8.dat";
    log_cs_ttH_8 = readTable(cs5.str(),199,2);
    cs15 << tablepath << "log_cs_ttH_13.dat";
    log_cs_ttH_13 = readTable(cs15.str(),199,2);
    cs6 << tablepath << "log_cs_bbH_8.dat";
    log_cs_bbH_8 = readTable(cs6.str(),199,2);
    cs16 << tablepath << "log_cs_bbH_13.dat";
    log_cs_bbH_13 = readTable(cs16.str(),199,2);
    cs7 << tablepath << "log_cs_ggA_8.dat";
    log_cs_ggA_8 = readTable(cs7.str(),199,2);
    cs17 << tablepath << "log_cs_ggA_13.dat";
    log_cs_ggA_13 = readTable(cs17.str(),199,2);
    cs8 << tablepath << "log_cs_ttA_8.dat";
    log_cs_ttA_8 = readTable(cs8.str(),199,2);
    cs18 << tablepath << "log_cs_ttA_13.dat";
    log_cs_ttA_13 = readTable(cs18.str(),199,2);
    cs9 << tablepath << "log_cs_bbA_8.dat";
    log_cs_bbA_8 = readTable(cs9.str(),199,2);
    cs19 << tablepath << "log_cs_bbA_13.dat";
    log_cs_bbA_13 = readTable(cs19.str(),199,2);
    cs20 << tablepath << "log_cs_ggHp_8.dat";
    log_cs_ggHp_8 = readTable(cs20.str(),744,3);
    cs21 << tablepath << "log_cs_ggHp_13.dat";
    log_cs_ggHp_13 = readTable(cs21.str(),1104,3);
    csr1 << tablepath << "csrH_top_8.dat";
    csrH_top_8 = readTable(csr1.str(),199,2);
    csr11 << tablepath << "csrH_top_13.dat";
    csrH_top_13 = readTable(csr11.str(),199,2);
    csr2 << tablepath << "csrH_bottom_8.dat";
    csrH_bottom_8 = readTable(csr2.str(),199,2);
    csr12 << tablepath << "csrH_bottom_13.dat";
    csrH_bottom_13 = readTable(csr12.str(),199,2);
    csr3 << tablepath << "csrA_top_8.dat";
    csrA_top_8 = readTable(csr3.str(),199,2);
    csr13 << tablepath << "csrA_top_13.dat";
    csrA_top_13 = readTable(csr13.str(),199,2);
    csr4 << tablepath << "csrA_bottom_8.dat";
    csrA_bottom_8 = readTable(csr4.str(),199,2);
    csr14 << tablepath << "csrA_bottom_13.dat";
    csrA_bottom_13 = readTable(csr14.str(),199,2);
    ex1 << tablepath << "150400936.dat";
    CMS8_mu_pp_H_VV = readTable(ex1.str(),172,2);
    ex1e << tablepath << "150400936_e.dat";
    CMS8_mu_pp_H_VV_e = readTable(ex1e.str(),172,2);
    ex2 << tablepath << "150404710.dat";
    CMS8_gg_A_hZ_bbll = readTable(ex2.str(),16,2);
    ex2e << tablepath << "150404710_e.dat";
    CMS8_gg_A_hZ_bbll_e = readTable(ex2e.str(),16,2);
    ex3 << tablepath << "160306896.dat";
    CMS8_pp_H_hh_gagabb = readTable(ex3.str(),85,2);
    ex3e << tablepath << "160306896_e.dat";
    CMS8_pp_H_hh_gagabb_e = readTable(ex3e.str(),85,2);
    ex4 << tablepath << "150304114.dat";
    CMS8_pp_H_hh_bbbb = readTable(ex4.str(),167,2);
    ex4e << tablepath << "150304114_e.dat";
    CMS8_pp_H_hh_bbbb_e = readTable(ex4e.str(),167,2);
    ex5 << tablepath << "14076583.dat";
    ATLAS8_pp_phi_gaga = readTable(ex5.str(),108,2);
    ex5e << tablepath << "14076583_e.dat";
    ATLAS8_pp_phi_gaga_e = readTable(ex5e.str(),108,2);
    ex6 << tablepath << "14096064_a.dat";
    ATLAS8_gg_phi_tautau = readTable(ex6.str(),92,2);
    ex6e << tablepath << "14096064_a_e.dat";
    ATLAS8_gg_phi_tautau_e = readTable(ex6e.str(),92,2);
    ex7 << tablepath << "14096064_b.dat";
    ATLAS8_bb_phi_tautau = readTable(ex7.str(),92,2);
    ex7e << tablepath << "14096064_b_e.dat";
    ATLAS8_bb_phi_tautau_e = readTable(ex7e.str(),92,2);
    ex8 << tablepath << "150204478_a.dat";
    ATLAS8_gg_A_hZ_tautauZ = readTable(ex8.str(),79,2);
    ex8e << tablepath << "150204478_a_e.dat";
    ATLAS8_gg_A_hZ_tautauZ_e = readTable(ex8e.str(),79,2);
    ex9 << tablepath << "150204478_b.dat";
    ATLAS8_gg_A_hZ_bbZ = readTable(ex9.str(),79,2);
    ex9e << tablepath << "150204478_b_e.dat";
    ATLAS8_gg_A_hZ_bbZ_e = readTable(ex9e.str(),79,2);
    ex10 << tablepath << "150608329.dat";
    CMS8_bb_phi_bb = readTable(ex10.str(),81,2);
    ex10e << tablepath << "150608329_e.dat";
    CMS8_bb_phi_bb_e = readTable(ex10e.str(),81,2);
    ex11 << tablepath << "150507018.dat";
    ATLAS8_gg_phi_tt = readTable(ex11.str(),53,2);
    ex11e << tablepath << "150507018_e.dat";
    ATLAS8_gg_phi_tt_e = readTable(ex11e.str(),53,2);
    ex12 << tablepath << "CMS-PAS-HIG-14-029_a.dat";
    CMS8_gg_phi_tautau = readTable(ex12.str(),92,2);
    ex12e << tablepath << "CMS-PAS-HIG-14-029_a_e.dat";
    CMS8_gg_phi_tautau_e = readTable(ex12e.str(),92,2);
    ex13 << tablepath << "CMS-PAS-HIG-14-029_b.dat";
    CMS8_bb_phi_tautau = readTable(ex13.str(),92,2);
    ex13e << tablepath << "CMS-PAS-HIG-14-029_b_e.dat";
    CMS8_bb_phi_tautau_e = readTable(ex13e.str(),92,2);
    ex14 << tablepath << "150602301.dat";
    CMS8_gg_phi_gaga = readTable(ex14.str(),141,2);
    ex14e << tablepath << "150602301_e.dat";
    CMS8_gg_phi_gaga_e = readTable(ex14e.str(),141,2);

//    ex14ep1 << tablepath << "150602301_ep1.dat";
//    CMS_ggF_phi_gaga_ep1 = readTable(ex14ep1.str(),141,2);
    //CHANGE THIS DEFINITION!
//    ex14ep2 << tablepath << "150602301_e.dat";
//    CMS_ggF_phi_gaga_ep2 = readTable(ex14ep2.str(),141,2);
//    ex14em1 << tablepath << "150602301_em1.dat";
//    CMS_ggF_phi_gaga_em1 = readTable(ex14em1.str(),141,2);
    //CHANGE THIS DEFINITION!
//    ex14em2 << tablepath << "150602301_e.dat";
//    CMS_ggF_phi_gaga_em2 = readTable(ex14em2.str(),141,2);

    ex15 << tablepath << "150900389_a.dat";
    ATLAS8_gg_H_WW = readTable(ex15.str(),13,2);
    ex15e << tablepath << "150900389_a_e.dat";
    ATLAS8_gg_H_WW_e = readTable(ex15e.str(),13,2);
    ex16 << tablepath << "150900389_b.dat";
    ATLAS8_VBF_H_WW = readTable(ex16.str(),13,2);
    ex16e << tablepath << "150900389_b_e.dat";
    ATLAS8_VBF_H_WW_e = readTable(ex16e.str(),13,2);
    ex17 << tablepath << "150904670.dat";
    ATLAS8_gg_H_hh = readTable(ex17.str(),75,2);
    ex17e << tablepath << "150904670_e.dat";
    ATLAS8_gg_H_hh_e = readTable(ex17e.str(),75,2);
    ex18 << tablepath << "151001181_a.dat";
    CMS8_gg_H_hh_bbtautau = readTable(ex18.str(),10,2);
    ex18e << tablepath << "151001181_a_e.dat";
    CMS8_gg_H_hh_bbtautau_e = readTable(ex18e.str(),10,2);
    ex19 << tablepath << "151001181_b.dat";
    CMS8_gg_A_hZ_tautaull = readTable(ex19.str(),14,2);
    ex19e << tablepath << "151001181_b_e.dat";
    CMS8_gg_A_hZ_tautaull_e = readTable(ex19e.str(),14,2);
    ex20 << tablepath << "150705930_a.dat";
    ATLAS8_gg_H_ZZ = readTable(ex20.str(),173,2);
    ex20e << tablepath << "150705930_a_e.dat";
    ATLAS8_gg_H_ZZ_e = readTable(ex20e.str(),173,2);
    ex21 << tablepath << "150705930_b.dat";
    ATLAS8_VBF_H_ZZ = readTable(ex21.str(),173,2);
    ex21e << tablepath << "150705930_b_e.dat";
    ATLAS8_VBF_H_ZZ_e = readTable(ex21e.str(),173,2);
    ex22 << tablepath << "CMS-PAS-HIG-15-013.dat";
    CMS8_pp_H_hh = readTable(ex22.str(),71,2);
    ex22e << tablepath << "CMS-PAS-HIG-15-013_e.dat";
    CMS8_pp_H_hh_e = readTable(ex22e.str(),71,2);
    ex23 << tablepath << "CMS-PAS-HIG-16-014.dat";
    CMS8_pp_A_Zga_llga = readTable(ex23.str(),101,2);
    ex23e << tablepath << "CMS-PAS-HIG-16-014_e.dat";
    CMS8_pp_A_Zga_llga_e = readTable(ex23e.str(),101,2);
    
    ex24 << tablepath << "ATLAS-CONF-2016-104_b.dat";
    ATLAS13_bb_phi_tt = readTable(ex24.str(),61,2);
    ex24e << tablepath << "ATLAS-CONF-2016-104_b_e.dat";
    ATLAS13_bb_phi_tt_e = readTable(ex24e.str(),61,2);
    ex25 << tablepath << "ATLAS-CONF-2016-104_a.dat";
    ATLAS13_tt_phi_tt = readTable(ex25.str(),61,2);
    ex25e << tablepath << "ATLAS-CONF-2016-104_a_e.dat";
    ATLAS13_tt_phi_tt_e = readTable(ex25e.str(),61,2);
    ex26 << tablepath << "ATLAS-CONF-2017-050_a.dat";
    ATLAS13_gg_phi_tautau = readTable(ex26.str(),206,2);
    ex26e << tablepath << "ATLAS-CONF-2017-050_a_e.dat";
    ATLAS13_gg_phi_tautau_e = readTable(ex26e.str(),206,2);
    ex27 << tablepath << "ATLAS-CONF-2017-050_b.dat";
    ATLAS13_bb_phi_tautau = readTable(ex27.str(),206,2);
    ex27e << tablepath << "ATLAS-CONF-2017-050_b_e.dat";
    ATLAS13_bb_phi_tautau_e = readTable(ex27e.str(),206,2);
    ex28 << tablepath << "170704147.dat";
    ATLAS13_pp_phi_gaga = readTable(ex28.str(),251,2);
    ex28e << tablepath << "170704147_e.dat";
    ATLAS13_pp_phi_gaga_e = readTable(ex28e.str(),251,2);
    ex29 << tablepath << "ATLAS-CONF-2016-044.dat";
    ATLAS13_pp_phi_Zga = readTable(ex29.str(),216,2);
    ex29e << tablepath << "ATLAS-CONF-2016-044_e.dat";
    ATLAS13_pp_phi_Zga_e = readTable(ex29e.str(),216,2);
    ex30 << tablepath << "ATLAS-CONF-2016-056.dat";
    ATLAS13_gg_H_ZZ_llnunu = readTable(ex30.str(),71,2);
    ex30e << tablepath << "ATLAS-CONF-2016-056_e.dat";
    ATLAS13_gg_H_ZZ_llnunu_e = readTable(ex30e.str(),71,2);
    ex31 << tablepath << "ATLAS-CONF-2016-079_a.dat";
    ATLAS13_gg_H_ZZ_llll = readTable(ex31.str(),81,2);
    ex31e << tablepath << "ATLAS-CONF-2016-079_a_e.dat";
    ATLAS13_gg_H_ZZ_llll_e = readTable(ex31e.str(),81,2);
    ex32 << tablepath << "ATLAS-CONF-2016-079_b.dat";
    ATLAS13_VBF_H_ZZ_llll = readTable(ex32.str(),81,2);
    ex32e << tablepath << "ATLAS-CONF-2016-079_b_e.dat";
    ATLAS13_VBF_H_ZZ_llll_e = readTable(ex32e.str(),81,2);
    ex33 << tablepath << "ATLAS-CONF-2016-082_a.dat";
    ATLAS13_gg_H_ZZ_llqq = readTable(ex33.str(),271,2);
    ex33e << tablepath << "ATLAS-CONF-2016-082_a_e.dat";
    ATLAS13_gg_H_ZZ_llqq_e = readTable(ex33e.str(),271,2);
    ex34 << tablepath << "ATLAS-CONF-2016-082_b.dat";
    ATLAS13_VBF_H_ZZ_llqq = readTable(ex34.str(),271,2);
    ex34e << tablepath << "ATLAS-CONF-2016-082_b_e.dat";
    ATLAS13_VBF_H_ZZ_llqq_e = readTable(ex34e.str(),271,2);
    ex35 << tablepath << "ATLAS-CONF-2016-082_c.dat";
    ATLAS13_gg_H_ZZ_nunuqq = readTable(ex35.str(),251,2);
    ex35e << tablepath << "ATLAS-CONF-2016-082_c_e.dat";
    ATLAS13_gg_H_ZZ_nunuqq_e = readTable(ex35e.str(),251,2);
    ex36 << tablepath << "171001123_a.dat";
    ATLAS13_gg_H_WW_enumumu = readTable(ex36.str(),381,2);
    ex36e << tablepath << "171001123_a_e.dat";
    ATLAS13_gg_H_WW_enumumu_e = readTable(ex36e.str(),381,2);
    ex37 << tablepath << "171001123_b.dat";
    ATLAS13_VBF_H_WW_enumumu = readTable(ex37.str(),281,2);
    ex37e << tablepath << "171001123_b_e.dat";
    ATLAS13_VBF_H_WW_enumumu_e = readTable(ex37e.str(),281,2);
    ex38 << tablepath << "171007235_a.dat";
    ATLAS13_gg_H_WW_lnuqq = readTable(ex38.str(),271,2);
    ex38e << tablepath << "171007235_a_e.dat";
    ATLAS13_gg_H_WW_lnuqq_e = readTable(ex38e.str(),271,2);
    ex39 << tablepath << "ATLAS-CONF-2016-049.dat";
    ATLAS13_pp_H_hh_bbbb = readTable(ex39.str(),271,2);
    ex39e << tablepath << "ATLAS-CONF-2016-049_e.dat";
    ATLAS13_pp_H_hh_bbbb_e = readTable(ex39e.str(),271,2);
    ex40 << tablepath << "ATLAS-CONF-2016-004.dat";
    ATLAS13_pp_H_hh_gagabb = readTable(ex40.str(),26,2);
    ex40e << tablepath << "ATLAS-CONF-2016-004_e.dat";
    ATLAS13_pp_H_hh_gagabb_e = readTable(ex40e.str(),26,2);
    ex41 << tablepath << "ATLAS-CONF-2016-071.dat";
    ATLAS13_pp_H_hh_gagaWW = readTable(ex41.str(),25,2);
    ex41e << tablepath << "ATLAS-CONF-2016-071_e.dat";
    ATLAS13_pp_H_hh_gagaWW_e = readTable(ex41e.str(),25,2);
    ex42 << tablepath << "ATLAS-CONF-2017-055_a.dat";
    ATLAS13_gg_A_Zh_Zbb = readTable(ex42.str(),181,2);
    ex42e << tablepath << "ATLAS-CONF-2017-055_a_e.dat";
    ATLAS13_gg_A_Zh_Zbb_e = readTable(ex42e.str(),181,2);
    ex43 << tablepath << "ATLAS-CONF-2017-055_b.dat";
    ATLAS13_bb_A_Zh_Zbb = readTable(ex43.str(),181,2);
    ex43e << tablepath << "ATLAS-CONF-2017-055_b_e.dat";
    ATLAS13_bb_A_Zh_Zbb_e = readTable(ex43e.str(),181,2);
    ex44 << tablepath << "CMS-PAS-HIG-16-025.dat";
    CMS13_pp_phi_bb = readTable(ex44.str(),66,2);
    ex44e << tablepath << "CMS-PAS-HIG-16-025_e.dat";
    CMS13_pp_phi_bb_e = readTable(ex44e.str(),66,2);
    ex45 << tablepath << "CMS-PAS-HIG-16-037_a.dat";
    CMS13_gg_phi_tautau = readTable(ex45.str(),312,2);
    ex45e << tablepath << "CMS-PAS-HIG-16-037_a_e.dat";
    CMS13_gg_phi_tautau_e = readTable(ex45e.str(),312,2);
    ex46 << tablepath << "CMS-PAS-HIG-16-037_b.dat";
    CMS13_bb_phi_tautau = readTable(ex46.str(),312,2);
    ex46e << tablepath << "CMS-PAS-HIG-16-037_b_e.dat";
    CMS13_bb_phi_tautau_e = readTable(ex46e.str(),312,2);
    ex47 << tablepath << "CMS-PAS-EXO-16-027.dat";
    CMS13_gg_phi_gaga = readTable(ex47.str(),351,2);
    ex47e << tablepath << "CMS-PAS-EXO-16-027_e.dat";
    CMS13_gg_phi_gaga_e = readTable(ex47e.str(),351,2);
    ex48 << tablepath << "CMS-PAS-EXO-16-034.dat";
    CMS13_pp_phi_Zga_llga = readTable(ex48.str(),171,2);
    ex48e << tablepath << "CMS-PAS-EXO-16-034_e.dat";
    CMS13_pp_phi_Zga_llga_e = readTable(ex48e.str(),171,2);
    ex49 << tablepath << "CMS-PAS-EXO-16-035.dat";
    CMS13_pp_phi_Zga_qqga = readTable(ex49.str(),236,2);
    ex49e << tablepath << "CMS-PAS-EXO-16-035_e.dat";
    CMS13_pp_phi_Zga_qqga_e = readTable(ex49e.str(),236,2);
    ex50 << tablepath << "CMS-PAS-HIG-16-033_a.dat";
    CMS13_pp_H_ZZ_llll = readTable(ex50.str(),241,2);
    ex50e << tablepath << "CMS-PAS-HIG-16-033_a_e.dat";
    CMS13_pp_H_ZZ_llll_e = readTable(ex50e.str(),241,2);
    ex51 << tablepath << "CMS-PAS-HIG-16-033_b.dat";
    CMS13_VBFVH_H_ZZ_llll = readTable(ex51.str(),241,2);
    ex51e << tablepath << "CMS-PAS-HIG-16-033_b_e.dat";
    CMS13_VBFVH_H_ZZ_llll_e = readTable(ex51e.str(),241,2);
    ex52 << tablepath << "CMS-PAS-HIG-16-023.dat";
    CMS13_ggFVBF_H_WW_lnulnu = readTable(ex52.str(),81,2);
    ex52e << tablepath << "CMS-PAS-HIG-16-023_e.dat";
    CMS13_ggFVBF_H_WW_lnulnu_e = readTable(ex52e.str(),81,2);
    ex53 << tablepath << "CMS-PAS-HIG-17-009.dat";
    CMS13_pp_H_hh_bbbb = readTable(ex53.str(),95,2);
    ex53e << tablepath << "CMS-PAS-HIG-17-009_e.dat";
    CMS13_pp_H_hh_bbbb_e = readTable(ex53e.str(),95,2);
    ex54 << tablepath << "CMS-PAS-HIG-17-008.dat";
    CMS13_pp_H_hh_gagabb = readTable(ex54.str(),66,2);
    ex54e << tablepath << "CMS-PAS-HIG-17-008_e.dat";
    CMS13_pp_H_hh_gagabb_e = readTable(ex54e.str(),66,2);
    ex55 << tablepath << "CMS-PAS-HIG-16-029.dat";
    CMS13_pp_H_hh_bbtautau = readTable(ex55.str(),66,2);
    ex55e << tablepath << "CMS-PAS-HIG-16-029_e.dat";
    CMS13_pp_H_hh_bbtautau_e = readTable(ex55e.str(),66,2);
    ex56 << tablepath << "CMS-PAS-HIG-16-011.dat";
    CMS13_pp_H_hh_bblnulnu = readTable(ex56.str(),65,2);
    ex56e << tablepath << "CMS-PAS-HIG-16-011_e.dat";
    CMS13_pp_H_hh_bblnulnu_e = readTable(ex56e.str(),65,2);

    ex57 << tablepath << "t1.dat";
    temp1 = readTable(ex57.str(),1,2);
    ex57e << tablepath << "t1_e.dat";
    temp1 = readTable(ex57e.str(),1,2);
    ex58 << tablepath << "t2.dat";
    temp2 = readTable(ex58.str(),1,2);
    ex58e << tablepath << "t2_e.dat";
    temp2 = readTable(ex58e.str(),1,2);
    ex59 << tablepath << "t3.dat";
    temp3 = readTable(ex59.str(),1,2);
    ex59e << tablepath << "t3_e.dat";
    temp3 = readTable(ex59e.str(),1,2);
    ex60 << tablepath << "t4.dat";
    temp4 = readTable(ex60.str(),1,2);
    ex60e << tablepath << "t4_e.dat";
    temp4 = readTable(ex60e.str(),1,2);
    ex61 << tablepath << "t5.dat";
    temp5 = readTable(ex61.str(),1,2);
    ex61e << tablepath << "t5_e.dat";
    temp5 = readTable(ex61e.str(),1,2);
    ex62 << tablepath << "t6.dat";
    temp6 = readTable(ex62.str(),1,2);
    ex62e << tablepath << "t6_e.dat";
    temp6 = readTable(ex62e.str(),1,2);
    ex63 << tablepath << "t7.dat";
    temp7 = readTable(ex63.str(),1,2);
    ex63e << tablepath << "t7_e.dat";
    temp7 = readTable(ex63e.str(),1,2);
    ex64 << tablepath << "t8.dat";
    temp8 = readTable(ex64.str(),1,2);
    ex64e << tablepath << "t8_e.dat";
    temp8 = readTable(ex64e.str(),1,2);
    ex65 << tablepath << "t9.dat";
    temp9 = readTable(ex65.str(),1,2);
    ex65e << tablepath << "t9_e.dat";
    temp9 = readTable(ex65e.str(),1,2);
    ex66 << tablepath << "t10.dat";
    temp10 = readTable(ex66.str(),1,2);
    ex66e << tablepath << "t10_e.dat";
    temp10 = readTable(ex66e.str(),1,2);
    ex67 << tablepath << "t11.dat";
    temp11 = readTable(ex67.str(),1,2);
    ex67e << tablepath << "t11_e.dat";
    temp11 = readTable(ex67e.str(),1,2);
    ex68 << tablepath << "t12.dat";
    temp12 = readTable(ex68.str(),1,2);
    ex68e << tablepath << "t12_e.dat";
    temp12 = readTable(ex68e.str(),1,2);
    ex69 << tablepath << "t13.dat";
    temp13 = readTable(ex69.str(),1,2);
    ex69e << tablepath << "t13_e.dat";
    temp13 = readTable(ex69e.str(),1,2);
    ex70 << tablepath << "t14.dat";
    temp14 = readTable(ex70.str(),1,2);
    ex70e << tablepath << "t14_e.dat";
    temp14 = readTable(ex70e.str(),1,2);
    ex71 << tablepath << "t15.dat";
    temp15 = readTable(ex71.str(),1,2);
    ex71e << tablepath << "t15_e.dat";
    temp15 = readTable(ex71e.str(),1,2);
    ex72 << tablepath << "t16.dat";
    temp16 = readTable(ex72.str(),1,2);
    ex72e << tablepath << "t16_e.dat";
    temp16 = readTable(ex72e.str(),1,2);
    ex73 << tablepath << "t17.dat";
    temp17 = readTable(ex73.str(),1,2);
    ex73e << tablepath << "t17_e.dat";
    temp17 = readTable(ex73e.str(),1,2);
    ex74 << tablepath << "t18.dat";
    temp18 = readTable(ex74.str(),1,2);
    ex74e << tablepath << "t18_e.dat";
    temp18 = readTable(ex74e.str(),1,2);
    ex75 << tablepath << "t19.dat";
    temp19 = readTable(ex75.str(),1,2);
    ex75e << tablepath << "t19_e.dat";
    temp19 = readTable(ex75e.str(),1,2);
    ex76 << tablepath << "t20.dat";
    temp20 = readTable(ex76.str(),1,2);
    ex76e << tablepath << "t20_e.dat";
    temp20 = readTable(ex76e.str(),1,2);
    ex77 << tablepath << "t21.dat";
    temp21 = readTable(ex77.str(),1,2);
    ex77e << tablepath << "t21_e.dat";
    temp21 = readTable(ex77e.str(),1,2);
    ex78 << tablepath << "t22.dat";
    temp22 = readTable(ex78.str(),1,2);
    ex78e << tablepath << "t22_e.dat";
    temp22 = readTable(ex78e.str(),1,2);
    ex79 << tablepath << "t23.dat";
    temp23 = readTable(ex79.str(),1,2);
    ex79e << tablepath << "t23_e.dat";
    temp23 = readTable(ex79e.str(),1,2);
    ex80 << tablepath << "t24.dat";
    temp24 = readTable(ex80.str(),1,2);
    ex80e << tablepath << "t24_e.dat";
    temp24 = readTable(ex80e.str(),1,2);
    ex81 << tablepath << "t25.dat";
    temp25 = readTable(ex81.str(),1,2);
    ex81e << tablepath << "t25_e.dat";
    temp25 = readTable(ex81e.str(),1,2);
    ex82 << tablepath << "t26.dat";
    temp26 = readTable(ex82.str(),1,2);
    ex82e << tablepath << "t26_e.dat";
    temp26 = readTable(ex82e.str(),1,2);
    ex83 << tablepath << "t27.dat";
    temp27 = readTable(ex83.str(),1,2);
    ex83e << tablepath << "t27_e.dat";
    temp27 = readTable(ex83e.str(),1,2);
    ex84 << tablepath << "t28.dat";
    temp28 = readTable(ex84.str(),1,2);
    ex84e << tablepath << "t28_e.dat";
    temp28 = readTable(ex84e.str(),1,2);
    ex85 << tablepath << "t29.dat";
    temp29 = readTable(ex85.str(),1,2);
    ex85e << tablepath << "t29_e.dat";
    temp29 = readTable(ex85e.str(),1,2);
    ex86 << tablepath << "t30.dat";
    temp30 = readTable(ex86.str(),1,2);
    ex86e << tablepath << "t30_e.dat";
    temp30e = readTable(ex86e.str(),1,2);
    ex87 << tablepath << "t31.dat";
    temp31 = readTable(ex87.str(),1,2);
    ex87e << tablepath << "t31_e.dat";
    temp31e = readTable(ex87e.str(),1,2);
    ex88 << tablepath << "t32.dat";
    temp32 = readTable(ex88.str(),1,2);
    ex88e << tablepath << "t32_e.dat";
    temp32e = readTable(ex88e.str(),1,2);
    ex89 << tablepath << "t33.dat";
    temp33 = readTable(ex89.str(),1,2);
    ex89e << tablepath << "t33_e.dat";
    temp33e = readTable(ex89e.str(),1,2);
    ex90 << tablepath << "t34.dat";
    temp34 = readTable(ex90.str(),1,2);
    ex90e << tablepath << "t34_e.dat";
    temp34e = readTable(ex90e.str(),1,2);
    ex91 << tablepath << "t35.dat";
    temp35 = readTable(ex91.str(),1,2);
    ex91e << tablepath << "t35_e.dat";
    temp35e = readTable(ex91e.str(),1,2);
    ex92 << tablepath << "t36.dat";
    temp36 = readTable(ex92.str(),1,2);
    ex92e << tablepath << "t36_e.dat";
    temp36e = readTable(ex92e.str(),1,2);
    ex93 << tablepath << "t37.dat";
    temp37 = readTable(ex93.str(),1,2);
    ex93e << tablepath << "t37_e.dat";
    temp37e = readTable(ex93e.str(),1,2);
    ex94 << tablepath << "t38.dat";
    temp38 = readTable(ex94.str(),1,2);
    ex94e << tablepath << "t38_e.dat";
    temp38e = readTable(ex94e.str(),1,2);
    ex95 << tablepath << "t39.dat";
    temp39 = readTable(ex95.str(),1,2);
    ex95e << tablepath << "t39_e.dat";
    temp39e = readTable(ex95e.str(),1,2);
    ex96 << tablepath << "t40.dat";
    temp40 = readTable(ex96.str(),1,2);
    ex96e << tablepath << "t40_e.dat";
    temp40e = readTable(ex96e.str(),1,2);

    ex97 << tablepath << "CMS-PAS-HIG-16-034.dat";
    CMS13_pp_H_ZZ_llqq = readTable(ex97.str(),151,2);
    ex97e << tablepath << "CMS-PAS-HIG-16-034_e.dat";
    CMS13_pp_H_ZZ_llqq_e = readTable(ex97e.str(),151,2);
    ex98 << tablepath << "14078150.dat";
    ATLAS8_pp_phi_Zga_llga = readTable(ex98.str(),141,2);
    ex98e << tablepath << "14078150.dat";
    ATLAS8_pp_phi_Zga_llga_e = readTable(ex98e.str(),141,2);

    ex99 << tablepath << "14126663.dat";
    ATLAS8_pp_Hpm_taunu = readTable(ex99.str(),83,2);
    ex99e << tablepath << "14126663_e.dat";
    ATLAS8_pp_Hpm_taunu_e = readTable(ex99e.str(),83,2);
    ex100 << tablepath << "151203704.dat";
    ATLAS8_pp_Hpm_tb = readTable(ex100.str(),41,2);
    ex100e << tablepath << "151203704_e.dat";
    ATLAS8_pp_Hpm_tb_e = readTable(ex100e.str(),41,2);
    ex101 << tablepath << "150807774_a.dat";
    CMS8_pp_Hp_taunu = readTable(ex101.str(),43,2);
    ex101e << tablepath << "150807774_a_e.dat";
    CMS8_pp_Hp_taunu_e = readTable(ex101e.str(),43,2);
    ex102 << tablepath << "150807774_b.dat";
    CMS8_pp_Hp_tb = readTable(ex102.str(),43,2);
    ex102e << tablepath << "150807774_b_e.dat";
    CMS8_pp_Hp_tb_e = readTable(ex102e.str(),43,2);
    ex103 << tablepath << "ATLAS-CONF-2016-088.dat";
    ATLAS13_pp_Hpm_taunu = readTable(ex103.str(),181,2);
    ex103e << tablepath << "ATLAS-CONF-2016-088_e.dat";
    ATLAS13_pp_Hpm_taunu_e = readTable(ex103e.str(),181,2);
    ex104 << tablepath << "ATLAS-CONF-2016-089.dat";
    ATLAS13_pp_Hp_tb1 = readTable(ex104.str(),71,2);
    ex104e << tablepath << "ATLAS-CONF-2016-089_e.dat";
    ATLAS13_pp_Hp_tb1_e = readTable(ex104e.str(),71,2);
    ex105 << tablepath << "ATLAS-CONF-2016-104_c.dat";
    ATLAS13_pp_Hp_tb2 = readTable(ex105.str(),181,2);
    ex105e << tablepath << "ATLAS-CONF-2016-104_c_e.dat";
    ATLAS13_pp_Hp_tb2_e = readTable(ex105e.str(),181,2);
    ex106 << tablepath << "CMS-PAS-HIG-16-031.dat";
    CMS13_pp_Hpm_taunu = readTable(ex106.str(),283,2);
    ex106e << tablepath << "CMS-PAS-HIG-16-031_e.dat";
    CMS13_pp_Hpm_taunu_e = readTable(ex106e.str(),283,2);

    ex107 << tablepath << "CMS-PAS-HIG-17-002.dat";
    CMS13_pp_H_hh_bbtautau1 = readTable(ex107.str(),66,2);
    ex107e << tablepath << "CMS-PAS-HIG-17-002_e.dat";
    CMS13_pp_H_hh_bbtautau1_e = readTable(ex107e.str(),66,2);
    ex108 << tablepath << "170804188.dat";
    CMS13_pp_H_hh_bbVV = readTable(ex108.str(),65,2);
    ex108e << tablepath << "170804188_e.dat";
    CMS13_pp_H_hh_bbVV_e = readTable(ex108e.str(),65,2);
    ex109 << tablepath << "CMS-PAS-EXO-17-005.dat";
    CMS13_ggF_phi_Zga = readTable(ex109.str(),366,2);
    ex109e << tablepath << "CMS-PAS-EXO-17-005_e.dat";
    CMS13_ggF_phi_Zga_e = readTable(ex109e.str(),366,2);
    ex110 << tablepath << "171004960.dat";
    CMS13_ggF_H_hh_bbbb = readTable(ex110.str(),226,2);
    ex110e << tablepath << "171004960_e.dat";
    CMS13_ggF_H_hh_bbbb_e = readTable(ex110e.str(),226,2);

    ex111 << tablepath << "171007235_b.dat";
    ATLAS13_VBF_H_WW_lnuqq = readTable(ex111.str(),271,2);
    ex111e << tablepath << "171007235_b_e.dat";
    ATLAS13_VBF_H_WW_lnuqq_e = readTable(ex111e.str(),271,2);
    ex112 << tablepath << "170800212.dat";
    ATLAS13_gg_phi_Zga_llga = readTable(ex112.str(),216,2);
    ex112e << tablepath << "170800212_e.dat";
    ATLAS13_gg_phi_Zga_llga_e = readTable(ex112e.str(),216,2);
    ex113 << tablepath << "ATLAS-CONF-2017-058_a.dat";
    ATLAS13_gg_H_ZZ_llllnunu = readTable(ex113.str(),101,2);
    ex113e << tablepath << "ATLAS-CONF-2017-058_a_e.dat";
    ATLAS13_gg_H_ZZ_llllnunu_e = readTable(ex113e.str(),101,2);
    ex114 << tablepath << "ATLAS-CONF-2017-058_b.dat";
    ATLAS13_VBF_H_ZZ_llllnunu = readTable(ex114.str(),101,2);
    ex114e << tablepath << "ATLAS-CONF-2017-058_b_e.dat";
    ATLAS13_VBF_H_ZZ_llllnunu_e = readTable(ex114e.str(),101,2);
    ex115 << tablepath << "170809638_a.dat";
    ATLAS13_gg_H_ZZ_qqllnunu = readTable(ex115.str(),271,2);
    ex115e << tablepath << "170809638_a_e.dat";
    ATLAS13_gg_H_ZZ_qqllnunu_e = readTable(ex115e.str(),271,2);
    ex116 << tablepath << "170809638_b.dat";
    ATLAS13_VBF_H_ZZ_qqllnunu = readTable(ex116.str(),271,2);
    ex116e << tablepath << "170809638_b_e.dat";
    ATLAS13_VBF_H_ZZ_qqllnunu_e = readTable(ex116e.str(),271,2);
    ex117 << tablepath << "170804445.dat";
    ATLAS13_pp_H_VV_qqqq = readTable(ex117.str(),181,2);
    ex117e << tablepath << "170804445_e.dat";
    ATLAS13_pp_H_VV_qqqq_e = readTable(ex117e.str(),181,2);
    ex118 << tablepath << "CMS-PAS-B2G-16-023.dat";
    CMS13_pp_H_ZZ_llnunu = readTable(ex118.str(),191,2);
    ex118e << tablepath << "CMS-PAS-B2G-16-023_e.dat";
    CMS13_pp_H_ZZ_llnunu_e = readTable(ex118e.str(),191,2);
    ex119 << tablepath << "CMS-PAS-HIG-16-001_a.dat";
    CMS13_gg_H_ZZ_llnunu = readTable(ex119.str(),131,2);
    ex119e << tablepath << "CMS-PAS-HIG-16-001_a_e.dat";
    CMS13_gg_H_ZZ_llnunu_e = readTable(ex119e.str(),131,2);
    ex120 << tablepath << "CMS-PAS-HIG-16-001_b.dat";
    CMS13_VBF_H_ZZ_llnunu = readTable(ex120.str(),131,2);
    ex120e << tablepath << "CMS-PAS-HIG-16-001_b_e.dat";
    CMS13_VBF_H_ZZ_llnunu_e = readTable(ex120e.str(),131,2);

    ex121 << tablepath << "160302991_a.dat";
    CMS8_pp_A_HZ_bbll = readTable(ex121.str(),28718,3);
    ex122 << tablepath << "160302991_b.dat";
    CMS8_pp_H_AZ_bbll = readTable(ex122.str(),29050,3);
    ex123 << tablepath << "160302991_c.dat";
    CMS8_pp_A_HZ_tautaull = readTable(ex123.str(),400,3);
    ex124 << tablepath << "160302991_d.dat";
    CMS8_pp_H_AZ_tautaull = readTable(ex124.str(),400,3);

    bsg1 << tablepath << "bsgammatable.dat";
    arraybsgamma = readTable(bsg1.str(),1111,3);
}



double GeneralTHDMcache::ip_Br_HPtott(double mass){
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



double GeneralTHDMcache::ip_Br_HPtobb(double mass){
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



double GeneralTHDMcache::ip_Br_HPtotautau(double mass){
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



double GeneralTHDMcache::ip_Br_HPtocc(double mass){
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



double GeneralTHDMcache::ip_Br_HPtomumu(double mass){
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



double GeneralTHDMcache::ip_Br_HPtoZZ(double mass){
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



double GeneralTHDMcache::ip_Br_HPtoWW(double mass){
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



double GeneralTHDMcache::ip_GammaHPtotSM(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_GammaHPtotSM_cache, NumPar, params);
    if (i>=0) {
        return ( ip_GammaHPtotSM_cache[NumPar][i] );
    } else {
        double newResult = pow(10.0,interpolate(GammaHtot_SM,mass));
        CacheShiftReal(ip_GammaHPtotSM_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ggtoH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ggtoH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ggH_8,mass));
        }
        CacheShiftReal(ip_cs_ggtoH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ggtoH_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ggtoH_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoH_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ggH_13,mass));
        }
        CacheShiftReal(ip_cs_ggtoH_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_VBFtoH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_VBFtoH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_VBFtoH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_VBF_8,mass));
        }
        CacheShiftReal(ip_cs_VBFtoH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_VBFtoH_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_VBFtoH_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_VBFtoH_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_VBF_13,mass));
        }
        CacheShiftReal(ip_cs_VBFtoH_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_WtoWH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_WtoWH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_WtoWH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_WH_8,mass));
        }
        CacheShiftReal(ip_cs_WtoWH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_WtoWH_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_WtoWH_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_WtoWH_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_WH_13,mass));
        }
        CacheShiftReal(ip_cs_WtoWH_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ZtoZH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ZtoZH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ZtoZH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ZH_8,mass));
        }
        CacheShiftReal(ip_cs_ZtoZH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ZtoZH_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ZtoZH_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ZtoZH_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ZH_13,mass));
        }
        CacheShiftReal(ip_cs_ZtoZH_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptottH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptottH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptottH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ttH_8,mass));
        }
        CacheShiftReal(ip_cs_pptottH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptottH_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptottH_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptottH_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ttH_13,mass));
        }
        CacheShiftReal(ip_cs_pptottH_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptobbH_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptobbH_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptobbH_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_bbH_8,mass));
        }
        CacheShiftReal(ip_cs_pptobbH_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptobbH_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptobbH_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptobbH_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_bbH_13,mass));
        }
        CacheShiftReal(ip_cs_pptobbH_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ggtoA_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ggtoA_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoA_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ggA_8,mass));
        }
        CacheShiftReal(ip_cs_ggtoA_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ggtoA_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_ggtoA_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoA_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ggA_13,mass));
        }
        CacheShiftReal(ip_cs_ggtoA_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptottA_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptottA_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptottA_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ttA_8,mass));
        }
        CacheShiftReal(ip_cs_pptottA_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptottA_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptottA_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptottA_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_ttA_13,mass));
        }
        CacheShiftReal(ip_cs_pptottA_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptobbA_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptobbA_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptobbA_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_bbA_8,mass));
        }
        CacheShiftReal(ip_cs_pptobbA_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_pptobbA_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_cs_pptobbA_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_pptobbA_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mass>=20. && mass <=2000.) {
            newResult = pow(10.0,interpolate (log_cs_bbA_13,mass));
        }
        CacheShiftReal(ip_cs_pptobbA_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ggtoHp_8(double mHp, double logtb){
    int NumPar = 2;
    double params[] = {mHp, logtb};

    int i = CacheCheckReal(ip_cs_ggtoHp_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoHp_8_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mHp>=180. && mHp <=1400. && logtb>=-1. && logtb<=1.75) {
            newResult = pow(10.0,interpolate2D(log_cs_ggHp_8, logtb, mHp));
        }
        CacheShiftReal(ip_cs_ggtoHp_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_cs_ggtoHp_13(double mHp, double logtb){
    int NumPar = 2;
    double params[] = {mHp, logtb};

    int i = CacheCheckReal(ip_cs_ggtoHp_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_cs_ggtoHp_13_cache[NumPar][i] );
    } else {
        double newResult = 0.0;
        if (mHp>=180. && mHp <=2000. && logtb>=-1. && logtb<=1.75) {
            newResult = pow(10.0,interpolate2D(log_cs_ggHp_13, logtb, mHp));
        }
        CacheShiftReal(ip_cs_ggtoHp_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggH_t_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggH_t_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggH_t_8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrH_top_8,mass);
        CacheShiftReal(ip_csr_ggH_t_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggH_t_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggH_t_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggH_t_13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrH_top_13,mass);
        CacheShiftReal(ip_csr_ggH_t_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggH_b_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggH_b_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggH_b_8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrH_bottom_8,mass);
        CacheShiftReal(ip_csr_ggH_b_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggH_b_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggH_b_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggH_b_13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrH_bottom_13,mass);
        CacheShiftReal(ip_csr_ggH_b_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggA_t_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggA_t_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggA_t_8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrA_top_8,mass);
        CacheShiftReal(ip_csr_ggA_t_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggA_t_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggA_t_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggA_t_13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrA_top_13,mass);
        CacheShiftReal(ip_csr_ggA_t_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggA_b_8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggA_b_8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggA_b_8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrA_bottom_8,mass);
        CacheShiftReal(ip_csr_ggA_b_8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_csr_ggA_b_13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_csr_ggA_b_13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_csr_ggA_b_13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (csrA_bottom_13,mass);
        CacheShiftReal(ip_csr_ggA_b_13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_gaga_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_gaga_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_gaga_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_pp_phi_gaga,mass);
        CacheShiftReal(ip_ex_pp_phi_gaga_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_gaga_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_gaga_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_gaga_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_pp_phi_gaga_e,mass);
        CacheShiftReal(ip_ex_pp_phi_gaga_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_llga_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_llga_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_Zga_llga_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_pp_phi_Zga_llga,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_llga_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_llga_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_llga_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_Zga_llga_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_pp_phi_Zga_llga_e,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_llga_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_tautau_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_gg_phi_tautau,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_tautau_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_gg_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_tautau_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_bb_phi_tautau,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_tautau_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_bb_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_hZ_tautauZ_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_tautauZ_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_tautauZ_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_gg_A_hZ_tautauZ,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_tautauZ_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_hZ_tautauZ_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_tautauZ_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_tautauZ_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_gg_A_hZ_tautauZ_e,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_tautauZ_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_hZ_bbZ_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_bbZ_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_bbZ_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_gg_A_hZ_bbZ,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_bbZ_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}





double GeneralTHDMcache::ip_ex_gg_A_hZ_bbZ_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_bbZ_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_bbZ_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(ATLAS8_gg_A_hZ_bbZ_e,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_bbZ_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tt_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tt_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_tt_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_phi_tt,mass);
        CacheShiftReal(ip_ex_gg_phi_tt_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tt_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tt_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_tt_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_phi_tt_e,mass);
        CacheShiftReal(ip_ex_gg_phi_tt_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_WW_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_WW_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_WW_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_H_WW,mass);
        CacheShiftReal(ip_ex_gg_H_WW_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_WW_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_WW_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_WW_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_H_WW_e,mass);
        CacheShiftReal(ip_ex_gg_H_WW_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_WW_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_WW_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_VBF_H_WW,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_WW_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_WW_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_VBF_H_WW_e,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_ZZ_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_H_ZZ,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_ZZ_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_H_ZZ_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_ZZ_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_VBF_H_ZZ,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_VBF_H_ZZ_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_VBF_H_ZZ_e,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_hh_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_hh_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_hh_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_H_hh,mass);
        CacheShiftReal(ip_ex_gg_H_hh_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_hh_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_hh_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_hh_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_gg_H_hh_e,mass);
        CacheShiftReal(ip_ex_gg_H_hh_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_mu_pp_H_VV_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_mu_pp_H_VV_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_mu_pp_H_VV_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_mu_pp_H_VV,mass);
        CacheShiftReal(ip_ex_mu_pp_H_VV_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_mu_pp_H_VV_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_mu_pp_H_VV_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_mu_pp_H_VV_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_mu_pp_H_VV_e,mass);
        CacheShiftReal(ip_ex_mu_pp_H_VV_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_hZ_bbll_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_bbll_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_bbll_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_gg_A_hZ_bbll,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_bbll_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_hZ_bbll_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_bbll_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_bbll_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_gg_A_hZ_bbll_e,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_bbll_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_H_hh_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_pp_H_hh,mass);
        CacheShiftReal(ip_ex_pp_H_hh_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_H_hh_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_pp_H_hh_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_hh_gagabb_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_gagabb_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_gagabb_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_pp_H_hh_gagabb,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_gagabb_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_hh_gagabb_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_gagabb_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_gagabb_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_pp_H_hh_gagabb_e,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_gagabb_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_hh_bbbb_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_bbbb_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_bbbb_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_pp_H_hh_bbbb,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_bbbb_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_hh_bbbb_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_hh_bbbb_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_phi_hh_bbbb_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate(CMS8_pp_H_hh_bbbb_e,mass);
        CacheShiftReal(ip_ex_pp_phi_hh_bbbb_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_bb_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_bb_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_bb_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_bb_phi_bb,mass);
        CacheShiftReal(ip_ex_bb_phi_bb_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_bb_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_bb_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_bb_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_bb_phi_bb_e,mass);
        CacheShiftReal(ip_ex_bb_phi_bb_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_tautau_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_phi_tautau,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_tautau_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_tautau_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_bb_phi_tautau,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_tautau_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_bb_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_gaga_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_phi_gaga,mass);
        CacheShiftReal(ip_ex_gg_phi_gaga_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_phi_gaga_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_phi_gaga_e,mass);
        CacheShiftReal(ip_ex_gg_phi_gaga_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



//
//double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS_ep1(double mass){
//    int NumPar = 1;
//    double params[] = {mass};
//
//    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS_cache_ep1, NumPar, params);
//    if (i>=0) {
//        return ( ip_ex_gg_phi_gaga_CMS_cache_ep1[NumPar][i] );
//    } else {
//        double newResult = interpolate (CMS_ggF_phi_gaga_ep1,mass);
//        CacheShiftReal(ip_ex_gg_phi_gaga_CMS_cache_ep1, NumPar, params, newResult);
//        return newResult;
//    }
//}

//double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS_ep2(double mass){
//    int NumPar = 1;
//    double params[] = {mass};
//
//    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS_cache_ep2, NumPar, params);
//    if (i>=0) {
//        return ( ip_ex_gg_phi_gaga_CMS_cache_ep2[NumPar][i] );
//    } else {
//        double newResult = interpolate (CMS_ggF_phi_gaga_ep2,mass);
//        CacheShiftReal(ip_ex_gg_phi_gaga_CMS_cache_ep2, NumPar, params, newResult);
//        return newResult;
//    }
//}
//
//double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS_em1(double mass){
//    int NumPar = 1;
//    double params[] = {mass};
//
//    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS_cache_em1, NumPar, params);
//    if (i>=0) {
//        return ( ip_ex_gg_phi_gaga_CMS_cache_em1[NumPar][i] );
//    } else {
//        double newResult = interpolate (CMS_ggF_phi_gaga_em1,mass);
//        CacheShiftReal(ip_ex_gg_phi_gaga_CMS_cache_em1, NumPar, params, newResult);
//        return newResult;
//    }
//}
//
//double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS_em2(double mass){
//    int NumPar = 1;
//    double params[] = {mass};
//
//    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS_cache_em2, NumPar, params);
//    if (i>=0) {
//        return ( ip_ex_gg_phi_gaga_CMS_cache_em2[NumPar][i] );
//    } else {
//        double newResult = interpolate (CMS_ggF_phi_gaga_em2,mass);
//        CacheShiftReal(ip_ex_gg_phi_gaga_CMS_cache_em2, NumPar, params, newResult);
//        return newResult;
//    }
//}
//


double GeneralTHDMcache::ip_ex_pp_A_Zga_llga_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_A_Zga_llga_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_A_Zga_llga_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_pp_A_Zga_llga,mass);
        CacheShiftReal(ip_ex_pp_A_Zga_llga_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_A_Zga_llga_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_A_Zga_llga_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_A_Zga_llga_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_pp_A_Zga_llga_e,mass);
        CacheShiftReal(ip_ex_pp_A_Zga_llga_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_hh_bbtautau_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_hh_bbtautau_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_hh_bbtautau_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_H_hh_bbtautau,mass);
        CacheShiftReal(ip_ex_gg_H_hh_bbtautau_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_hh_bbtautau_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_hh_bbtautau_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_H_hh_bbtautau_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_H_hh_bbtautau_e,mass);
        CacheShiftReal(ip_ex_gg_H_hh_bbtautau_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_hZ_tautaull_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_tautaull_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_tautaull_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_A_hZ_tautaull,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_tautaull_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_hZ_tautaull_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_hZ_tautaull_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_gg_A_hZ_tautaull_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_gg_A_hZ_tautaull_e,mass);
        CacheShiftReal(ip_ex_gg_A_hZ_tautaull_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_A_HZ_bbll_CMS8(double m1, double m2){
    int NumPar = 2;
    double params[] = {m1, m2};
    int i = CacheCheckReal(ip_ex_pp_A_HZ_bbll_CMS8_cache, NumPar, params);
   
    if (i>=0) {
        
        return ( ip_ex_pp_A_HZ_bbll_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate2D(CMS8_pp_A_HZ_bbll, m1, m2);
        
        
        CacheShiftReal(ip_ex_pp_A_HZ_bbll_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_AZ_bbll_CMS8(double mA, double mH){
    int NumPar = 2;
    double params[] = {mA, mH};

    int i = CacheCheckReal(ip_ex_pp_H_AZ_bbll_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_H_AZ_bbll_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate2D(CMS8_pp_H_AZ_bbll, mA, mH);
        CacheShiftReal(ip_ex_pp_H_AZ_bbll_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}


double GeneralTHDMcache::ip_ex_pp_A_HZ_tautaull_CMS8(double mA, double mH){
    int NumPar = 2;
    double params[] = {mA, mH};

    int i = CacheCheckReal(ip_ex_pp_A_HZ_tautaull_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_A_HZ_tautaull_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate2D(CMS8_pp_A_HZ_tautaull, mA, mH);
        CacheShiftReal(ip_ex_pp_A_HZ_tautaull_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_AZ_tautaull_CMS8(double mA, double mH){
    int NumPar = 2;
    double params[] = {mA, mH};

    int i = CacheCheckReal(ip_ex_pp_H_AZ_tautaull_CMS8_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_pp_H_AZ_tautaull_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate2D(CMS8_pp_H_AZ_tautaull, mA, mH);
        CacheShiftReal(ip_ex_pp_H_AZ_tautaull_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tt_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tt_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_tt_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_bb_phi_tt,mass);
        CacheShiftReal(ip_ex_bb_phi_tt_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tt_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tt_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return ( ip_ex_bb_phi_tt_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_bb_phi_tt_e,mass);
        CacheShiftReal(ip_ex_bb_phi_tt_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_tt_phi_tt_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_tt_phi_tt_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_tt_phi_tt_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_tt_phi_tt,mass);
        CacheShiftReal(ip_ex_tt_phi_tt_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_tt_phi_tt_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_tt_phi_tt_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_tt_phi_tt_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_tt_phi_tt_e,mass);
        CacheShiftReal(ip_ex_tt_phi_tt_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_tautau_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_phi_tautau,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_tautau_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_bb_phi_tautau_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_bb_phi_tautau,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_bb_phi_tautau_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_bb_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_gaga_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_gaga_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_gaga_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_phi_gaga,mass);
        CacheShiftReal(ip_ex_pp_phi_gaga_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_gaga_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_gaga_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_gaga_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_phi_gaga_e,mass);
        CacheShiftReal(ip_ex_pp_phi_gaga_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_llga_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_llga_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_Zga_llga_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_phi_Zga,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_llga_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_llga_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_llga_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_Zga_llga_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_phi_Zga_e,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_llga_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_Zga_llga_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_Zga_llga_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_Zga_llga_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_phi_Zga_llga,mass);
        CacheShiftReal(ip_ex_gg_phi_Zga_llga_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_Zga_llga_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_Zga_llga_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_Zga_llga_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_phi_Zga_llga_e,mass);
        CacheShiftReal(ip_ex_gg_phi_Zga_llga_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llllnunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llllnunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llllnunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llllnunu,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llllnunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llllnunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llllnunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llllnunu_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llllnunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_llllnunu,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_llllnunu_e,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llnunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llnunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llnunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llnunu,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llnunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llnunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llnunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llnunu_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llnunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llll_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llll_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llll_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llll,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llll_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llll_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llll_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llll_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llll_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llll_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llll_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llll_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llll_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_llll,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llll_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llll_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llll_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llll_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_llll_e,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llll_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_qqllnunu,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_qqllnunu_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_qqllnunu,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_qqllnunu_e,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llqq_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llqq_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llqq_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llqq,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llqq_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llqq_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llqq_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llqq_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_llqq_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llqq_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llqq_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llqq_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llqq_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_llqq,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llqq_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llqq_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llqq_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_ZZ_llqq_e,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llqq_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_nunuqq_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_nunuqq_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_nunuqq_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_nunuqq,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_nunuqq_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_nunuqq_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_nunuqq_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_ZZ_nunuqq_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_nunuqq_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_WW_enumunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_WW_enumunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_WW_enumunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_WW_enumumu,mass);
        CacheShiftReal(ip_ex_gg_H_WW_enumunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_WW_enumunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_WW_enumunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_WW_enumunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_WW_enumumu_e,mass);
        CacheShiftReal(ip_ex_gg_H_WW_enumunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_WW_enumunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_enumunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_WW_enumunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_WW_enumumu,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_enumunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_WW_enumunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_enumunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_WW_enumunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_WW_enumumu_e,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_enumunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_WW_lnuqq_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_WW_lnuqq_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_WW_lnuqq_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_WW_lnuqq,mass);
        CacheShiftReal(ip_ex_gg_H_WW_lnuqq_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_WW_lnuqq_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_WW_lnuqq_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_WW_lnuqq_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_H_WW_lnuqq_e,mass);
        CacheShiftReal(ip_ex_gg_H_WW_lnuqq_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_WW_lnuqq_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_lnuqq_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_WW_lnuqq_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_WW_lnuqq,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_lnuqq_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_WW_lnuqq_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_WW_lnuqq_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_VBF_H_WW_lnuqq_e,mass);
        CacheShiftReal(ip_ex_VBF_H_WW_lnuqq_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_VV_qqqq_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_VV_qqqq_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_VV_qqqq_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_VV_qqqq,mass);
        CacheShiftReal(ip_ex_pp_H_VV_qqqq_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_VV_qqqq_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_VV_qqqq_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_VV_qqqq_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_VV_qqqq_e,mass);
        CacheShiftReal(ip_ex_pp_H_VV_qqqq_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbbb_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbbb_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbbb_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_hh_bbbb,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbbb_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbbb_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbbb_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbbb_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_hh_bbbb_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbbb_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_gagabb_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_gagabb_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_gagabb_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_hh_gagabb,mass);
        CacheShiftReal(ip_ex_pp_H_hh_gagabb_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_gagabb_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_gagabb_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_gagabb_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_hh_gagabb_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_gagabb_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_gagaWW_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_gagaWW_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_gagaWW_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_hh_gagaWW,mass);
        CacheShiftReal(ip_ex_pp_H_hh_gagaWW_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_gagaWW_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_gagaWW_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_gagaWW_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_H_hh_gagaWW_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_gagaWW_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_Zh_Zbb_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_Zh_Zbb_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_A_Zh_Zbb_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_A_Zh_Zbb,mass);
        CacheShiftReal(ip_ex_gg_A_Zh_Zbb_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_A_Zh_Zbb_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_A_Zh_Zbb_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_A_Zh_Zbb_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_gg_A_Zh_Zbb_e,mass);
        CacheShiftReal(ip_ex_gg_A_Zh_Zbb_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_A_Zh_Zbb_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_A_Zh_Zbb_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_bb_A_Zh_Zbb_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_bb_A_Zh_Zbb,mass);
        CacheShiftReal(ip_ex_bb_A_Zh_Zbb_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_A_Zh_Zbb_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_A_Zh_Zbb_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_bb_A_Zh_Zbb_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_bb_A_Zh_Zbb_e,mass);
        CacheShiftReal(ip_ex_bb_A_Zh_Zbb_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_bb_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_bb_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_bb_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_phi_bb,mass);
        CacheShiftReal(ip_ex_pp_phi_bb_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_bb_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_bb_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_bb_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_phi_bb_e,mass);
        CacheShiftReal(ip_ex_pp_phi_bb_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_tautau_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_gg_phi_tautau,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_tautau_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_tautau_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_tautau_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_gg_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_gg_phi_tautau_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_bb_phi_tautau_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_bb_phi_tautau,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bb_phi_tautau_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_bb_phi_tautau_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_bb_phi_tautau_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_bb_phi_tautau_e,mass);
        CacheShiftReal(ip_ex_bb_phi_tautau_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_gaga_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_gg_phi_gaga,mass);
        CacheShiftReal(ip_ex_gg_phi_gaga_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_phi_gaga_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_phi_gaga_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_phi_gaga_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_gg_phi_gaga_e,mass);
        CacheShiftReal(ip_ex_gg_phi_gaga_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_llga_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_llga_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_Zga_llga_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_phi_Zga_llga,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_llga_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_llga_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_llga_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_Zga_llga_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_phi_Zga_llga_e,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_llga_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_qqga_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_qqga_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_Zga_qqga_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_phi_Zga_qqga,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_qqga_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_phi_Zga_qqga_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_phi_Zga_qqga_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_phi_Zga_qqga_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_phi_Zga_qqga_e,mass);
        CacheShiftReal(ip_ex_pp_phi_Zga_qqga_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_ggF_phi_Zga_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_Zga_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_ggF_phi_Zga_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_ggF_phi_Zga,mass);
        CacheShiftReal(ip_ex_ggF_phi_Zga_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_ggF_phi_Zga_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_phi_Zga_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_ggF_phi_Zga_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_ggF_phi_Zga_e,mass);
        CacheShiftReal(ip_ex_ggF_phi_Zga_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_ZZ_llnunu_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_ZZ_llnunu_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_ZZ_llnunu_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_ZZ_llnunu,mass);
        CacheShiftReal(ip_ex_pp_H_ZZ_llnunu_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_ZZ_llnunu_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_ZZ_llnunu_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_ZZ_llnunu_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_ZZ_llnunu_e,mass);
        CacheShiftReal(ip_ex_pp_H_ZZ_llnunu_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llnunu_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llnunu_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llnunu_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_gg_H_ZZ_llnunu,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llnunu_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_gg_H_ZZ_llnunu_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_gg_H_ZZ_llnunu_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_gg_H_ZZ_llnunu_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_gg_H_ZZ_llnunu_e,mass);
        CacheShiftReal(ip_ex_gg_H_ZZ_llnunu_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llnunu_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llnunu_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llnunu_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_VBF_H_ZZ_llnunu,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llnunu_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_H_ZZ_llnunu_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_H_ZZ_llnunu_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_H_ZZ_llnunu_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_VBF_H_ZZ_llnunu_e,mass);
        CacheShiftReal(ip_ex_VBF_H_ZZ_llnunu_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_ZZ_llll_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_ZZ_llll_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_ZZ_llll_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_ZZ_llll,mass);
        CacheShiftReal(ip_ex_pp_H_ZZ_llll_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_ZZ_llll_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_ZZ_llll_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_ZZ_llll_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_ZZ_llll_e,mass);
        CacheShiftReal(ip_ex_pp_H_ZZ_llll_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_VH_H_ZZ_llll_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_VH_H_ZZ_llll_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_VH_H_ZZ_llll_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_VBFVH_H_ZZ_llll,mass);
        CacheShiftReal(ip_ex_VBF_VH_H_ZZ_llll_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_VBF_VH_H_ZZ_llll_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_VBF_VH_H_ZZ_llll_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_VBFVH_H_ZZ_llll_e,mass);
        CacheShiftReal(ip_ex_VBF_VH_H_ZZ_llll_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_ZZ_llqq_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_ZZ_llqq_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_ZZ_llqq_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_ZZ_llqq,mass);
        CacheShiftReal(ip_ex_pp_H_ZZ_llqq_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_ZZ_llqq_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_ZZ_llqq_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_ZZ_llqq_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_ZZ_llqq_e,mass);
        CacheShiftReal(ip_ex_pp_H_ZZ_llqq_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_ggVV_H_WW_lnulnu_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggVV_H_WW_lnulnu_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_ggVV_H_WW_lnulnu_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_ggFVBF_H_WW_lnulnu,mass);
        CacheShiftReal(ip_ex_ggVV_H_WW_lnulnu_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_ggVV_H_WW_lnulnu_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggVV_H_WW_lnulnu_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_ggVV_H_WW_lnulnu_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_ggFVBF_H_WW_lnulnu_e,mass);
        CacheShiftReal(ip_ex_ggVV_H_WW_lnulnu_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbbb_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbbb_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbbb_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbbb,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbbb_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbbb_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbbb_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbbb_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbbb_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbbb_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_ggF_H_hh_bbbb_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_hh_bbbb_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_ggF_H_hh_bbbb_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_ggF_H_hh_bbbb,mass);
        CacheShiftReal(ip_ex_ggF_H_hh_bbbb_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_ggF_H_hh_bbbb_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_ggF_H_hh_bbbb_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_ggF_H_hh_bbbb_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_ggF_H_hh_bbbb_e,mass);
        CacheShiftReal(ip_ex_ggF_H_hh_bbbb_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_gagabb_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_gagabb_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_gagabb_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_gagabb,mass);
        CacheShiftReal(ip_ex_pp_H_hh_gagabb_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_gagabb_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_gagabb_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_gagabb_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_gagabb_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_gagabb_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbtautau_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbtautau_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbtautau_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbtautau,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbtautau_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbtautau_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbtautau_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbtautau_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbtautau_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbtautau_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbtautau1_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbtautau1_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbtautau1_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbtautau1,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbtautau1_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbtautau1_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbtautau1_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbtautau1_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbtautau1_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbtautau1_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bblnulnu_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bblnulnu_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bblnulnu_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bblnulnu,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bblnulnu_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bblnulnu_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bblnulnu_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bblnulnu_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bblnulnu_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bblnulnu_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbVV_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbVV_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbVV_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbVV,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbVV_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_H_hh_bbVV_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_H_hh_bbVV_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_H_hh_bbVV_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_H_hh_bbVV_e,mass);
        CacheShiftReal(ip_ex_pp_H_hh_bbVV_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie1(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie1c, NumPar, params);
    if (i>=0) {
        return(ie1c[NumPar][i] );
    } else {
        double newResult = interpolate (temp1,mass);
        CacheShiftReal(ie1c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie1e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie1ec, NumPar, params);
    if (i>=0) {
        return(ie1ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp1e,mass);
        CacheShiftReal(ie1ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie2(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie2c, NumPar, params);
    if (i>=0) {
        return(ie2c[NumPar][i] );
    } else {
        double newResult = interpolate (temp2,mass);
        CacheShiftReal(ie2c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie2e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie2ec, NumPar, params);
    if (i>=0) {
        return(ie2ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp2e,mass);
        CacheShiftReal(ie2ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie3(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie3c, NumPar, params);
    if (i>=0) {
        return(ie3c[NumPar][i] );
    } else {
        double newResult = interpolate (temp3,mass);
        CacheShiftReal(ie3c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie3e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie3ec, NumPar, params);
    if (i>=0) {
        return(ie3ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp3e,mass);
        CacheShiftReal(ie3ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie4(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie4c, NumPar, params);
    if (i>=0) {
        return(ie4c[NumPar][i] );
    } else {
        double newResult = interpolate (temp4,mass);
        CacheShiftReal(ie4c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie4e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie4ec, NumPar, params);
    if (i>=0) {
        return(ie4ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp4e,mass);
        CacheShiftReal(ie4ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie5(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie5c, NumPar, params);
    if (i>=0) {
        return(ie5c[NumPar][i] );
    } else {
        double newResult = interpolate (temp5,mass);
        CacheShiftReal(ie5c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie5e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie5ec, NumPar, params);
    if (i>=0) {
        return(ie5ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp5e,mass);
        CacheShiftReal(ie5ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie6(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie6c, NumPar, params);
    if (i>=0) {
        return(ie6c[NumPar][i] );
    } else {
        double newResult = interpolate (temp6,mass);
        CacheShiftReal(ie6c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie6e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie6ec, NumPar, params);
    if (i>=0) {
        return(ie6ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp6e,mass);
        CacheShiftReal(ie6ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie7(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie7c, NumPar, params);
    if (i>=0) {
        return(ie7c[NumPar][i] );
    } else {
        double newResult = interpolate (temp7,mass);
        CacheShiftReal(ie7c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie7e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie7ec, NumPar, params);
    if (i>=0) {
        return(ie7ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp7e,mass);
        CacheShiftReal(ie7ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie8c, NumPar, params);
    if (i>=0) {
        return(ie8c[NumPar][i] );
    } else {
        double newResult = interpolate (temp8,mass);
        CacheShiftReal(ie8c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie8e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie8ec, NumPar, params);
    if (i>=0) {
        return(ie8ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp8e,mass);
        CacheShiftReal(ie8ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie9(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie9c, NumPar, params);
    if (i>=0) {
        return(ie9c[NumPar][i] );
    } else {
        double newResult = interpolate (temp9,mass);
        CacheShiftReal(ie9c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie9e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie9ec, NumPar, params);
    if (i>=0) {
        return(ie9ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp9e,mass);
        CacheShiftReal(ie9ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie10(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie10c, NumPar, params);
    if (i>=0) {
        return(ie10c[NumPar][i] );
    } else {
        double newResult = interpolate (temp10,mass);
        CacheShiftReal(ie10c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie10e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie10ec, NumPar, params);
    if (i>=0) {
        return(ie10ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp10e,mass);
        CacheShiftReal(ie10ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie11(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie11c, NumPar, params);
    if (i>=0) {
        return(ie11c[NumPar][i] );
    } else {
        double newResult = interpolate (temp11,mass);
        CacheShiftReal(ie11c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie11e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie11ec, NumPar, params);
    if (i>=0) {
        return(ie11ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp11e,mass);
        CacheShiftReal(ie11ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie12(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie12c, NumPar, params);
    if (i>=0) {
        return(ie12c[NumPar][i] );
    } else {
        double newResult = interpolate (temp12,mass);
        CacheShiftReal(ie12c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie12e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie12ec, NumPar, params);
    if (i>=0) {
        return(ie12ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp12e,mass);
        CacheShiftReal(ie12ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie13c, NumPar, params);
    if (i>=0) {
        return(ie13c[NumPar][i] );
    } else {
        double newResult = interpolate (temp13,mass);
        CacheShiftReal(ie13c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie13e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie13ec, NumPar, params);
    if (i>=0) {
        return(ie13ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp13e,mass);
        CacheShiftReal(ie13ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie14(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie14c, NumPar, params);
    if (i>=0) {
        return(ie14c[NumPar][i] );
    } else {
        double newResult = interpolate (temp14,mass);
        CacheShiftReal(ie14c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie14e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie14ec, NumPar, params);
    if (i>=0) {
        return(ie14ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp14e,mass);
        CacheShiftReal(ie14ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie15(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie15c, NumPar, params);
    if (i>=0) {
        return(ie15c[NumPar][i] );
    } else {
        double newResult = interpolate (temp15,mass);
        CacheShiftReal(ie15c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie15e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie15ec, NumPar, params);
    if (i>=0) {
        return(ie15ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp15e,mass);
        CacheShiftReal(ie15ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie16(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie16c, NumPar, params);
    if (i>=0) {
        return(ie16c[NumPar][i] );
    } else {
        double newResult = interpolate (temp16,mass);
        CacheShiftReal(ie16c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie16e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie16ec, NumPar, params);
    if (i>=0) {
        return(ie16ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp16e,mass);
        CacheShiftReal(ie16ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie17(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie17c, NumPar, params);
    if (i>=0) {
        return(ie17c[NumPar][i] );
    } else {
        double newResult = interpolate (temp17,mass);
        CacheShiftReal(ie17c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie17e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie17ec, NumPar, params);
    if (i>=0) {
        return(ie17ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp17e,mass);
        CacheShiftReal(ie17ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie18(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie18c, NumPar, params);
    if (i>=0) {
        return(ie18c[NumPar][i] );
    } else {
        double newResult = interpolate (temp18,mass);
        CacheShiftReal(ie18c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie18e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie18ec, NumPar, params);
    if (i>=0) {
        return(ie18ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp18e,mass);
        CacheShiftReal(ie18ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie19(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie19c, NumPar, params);
    if (i>=0) {
        return(ie19c[NumPar][i] );
    } else {
        double newResult = interpolate (temp19,mass);
        CacheShiftReal(ie19c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie19e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie19ec, NumPar, params);
    if (i>=0) {
        return(ie19ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp19e,mass);
        CacheShiftReal(ie19ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie20(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie20c, NumPar, params);
    if (i>=0) {
        return(ie20c[NumPar][i] );
    } else {
        double newResult = interpolate (temp20,mass);
        CacheShiftReal(ie20c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie20e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie20ec, NumPar, params);
    if (i>=0) {
        return(ie20ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp20e,mass);
        CacheShiftReal(ie20ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie21(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie21c, NumPar, params);
    if (i>=0) {
        return(ie21c[NumPar][i] );
    } else {
        double newResult = interpolate (temp21,mass);
        CacheShiftReal(ie21c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie21e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie21ec, NumPar, params);
    if (i>=0) {
        return(ie21ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp21e,mass);
        CacheShiftReal(ie21ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie22(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie22c, NumPar, params);
    if (i>=0) {
        return(ie22c[NumPar][i] );
    } else {
        double newResult = interpolate (temp22,mass);
        CacheShiftReal(ie22c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie22e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie22ec, NumPar, params);
    if (i>=0) {
        return(ie22ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp22e,mass);
        CacheShiftReal(ie22ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie23(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie23c, NumPar, params);
    if (i>=0) {
        return(ie23c[NumPar][i] );
    } else {
        double newResult = interpolate (temp23,mass);
        CacheShiftReal(ie23c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie23e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie23ec, NumPar, params);
    if (i>=0) {
        return(ie23ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp23e,mass);
        CacheShiftReal(ie23ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie24(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie24c, NumPar, params);
    if (i>=0) {
        return(ie24c[NumPar][i] );
    } else {
        double newResult = interpolate (temp24,mass);
        CacheShiftReal(ie24c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie24e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie24ec, NumPar, params);
    if (i>=0) {
        return(ie24ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp24e,mass);
        CacheShiftReal(ie24ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie25(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie25c, NumPar, params);
    if (i>=0) {
        return(ie25c[NumPar][i] );
    } else {
        double newResult = interpolate (temp25,mass);
        CacheShiftReal(ie25c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie25e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie25ec, NumPar, params);
    if (i>=0) {
        return(ie25ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp25e,mass);
        CacheShiftReal(ie25ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie26(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie26c, NumPar, params);
    if (i>=0) {
        return(ie26c[NumPar][i] );
    } else {
        double newResult = interpolate (temp26,mass);
        CacheShiftReal(ie26c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie26e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie26ec, NumPar, params);
    if (i>=0) {
        return(ie26ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp26e,mass);
        CacheShiftReal(ie26ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie27(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie27c, NumPar, params);
    if (i>=0) {
        return(ie27c[NumPar][i] );
    } else {
        double newResult = interpolate (temp27,mass);
        CacheShiftReal(ie27c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie27e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie27ec, NumPar, params);
    if (i>=0) {
        return(ie27ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp27e,mass);
        CacheShiftReal(ie27ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie28(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie28c, NumPar, params);
    if (i>=0) {
        return(ie28c[NumPar][i] );
    } else {
        double newResult = interpolate (temp28,mass);
        CacheShiftReal(ie28c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie28e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie28ec, NumPar, params);
    if (i>=0) {
        return(ie28ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp28e,mass);
        CacheShiftReal(ie28ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie29(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie29c, NumPar, params);
    if (i>=0) {
        return(ie29c[NumPar][i] );
    } else {
        double newResult = interpolate (temp29,mass);
        CacheShiftReal(ie29c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie29e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie29ec, NumPar, params);
    if (i>=0) {
        return(ie29ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp29e,mass);
        CacheShiftReal(ie29ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie30(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie30c, NumPar, params);
    if (i>=0) {
        return(ie30c[NumPar][i] );
    } else {
        double newResult = interpolate (temp30,mass);
        CacheShiftReal(ie30c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie30e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie30ec, NumPar, params);
    if (i>=0) {
        return(ie30ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp30e,mass);
        CacheShiftReal(ie30ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie31(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie31c, NumPar, params);
    if (i>=0) {
        return(ie31c[NumPar][i] );
    } else {
        double newResult = interpolate (temp31,mass);
        CacheShiftReal(ie31c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie31e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie31ec, NumPar, params);
    if (i>=0) {
        return(ie31ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp31e,mass);
        CacheShiftReal(ie31ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie32(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie32c, NumPar, params);
    if (i>=0) {
        return(ie32c[NumPar][i] );
    } else {
        double newResult = interpolate (temp32,mass);
        CacheShiftReal(ie32c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie32e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie32ec, NumPar, params);
    if (i>=0) {
        return(ie32ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp32e,mass);
        CacheShiftReal(ie32ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie33(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie33c, NumPar, params);
    if (i>=0) {
        return(ie33c[NumPar][i] );
    } else {
        double newResult = interpolate (temp33,mass);
        CacheShiftReal(ie33c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie33e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie33ec, NumPar, params);
    if (i>=0) {
        return(ie33ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp33e,mass);
        CacheShiftReal(ie33ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie34(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie34c, NumPar, params);
    if (i>=0) {
        return(ie34c[NumPar][i] );
    } else {
        double newResult = interpolate (temp34,mass);
        CacheShiftReal(ie34c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie34e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie34ec, NumPar, params);
    if (i>=0) {
        return(ie34ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp34e,mass);
        CacheShiftReal(ie34ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie35(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie35c, NumPar, params);
    if (i>=0) {
        return(ie35c[NumPar][i] );
    } else {
        double newResult = interpolate (temp35,mass);
        CacheShiftReal(ie35c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie35e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie35ec, NumPar, params);
    if (i>=0) {
        return(ie35ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp35e,mass);
        CacheShiftReal(ie35ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie36(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie36c, NumPar, params);
    if (i>=0) {
        return(ie36c[NumPar][i] );
    } else {
        double newResult = interpolate (temp36,mass);
        CacheShiftReal(ie36c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie36e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie36ec, NumPar, params);
    if (i>=0) {
        return(ie36ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp36e,mass);
        CacheShiftReal(ie36ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie37(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie37c, NumPar, params);
    if (i>=0) {
        return(ie37c[NumPar][i] );
    } else {
        double newResult = interpolate (temp37,mass);
        CacheShiftReal(ie37c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie37e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie37ec, NumPar, params);
    if (i>=0) {
        return(ie37ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp37e,mass);
        CacheShiftReal(ie37ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie38(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie38c, NumPar, params);
    if (i>=0) {
        return(ie38c[NumPar][i] );
    } else {
        double newResult = interpolate (temp38,mass);
        CacheShiftReal(ie38c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie38e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie38ec, NumPar, params);
    if (i>=0) {
        return(ie38ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp38e,mass);
        CacheShiftReal(ie38ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie39(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie39c, NumPar, params);
    if (i>=0) {
        return(ie39c[NumPar][i] );
    } else {
        double newResult = interpolate (temp39,mass);
        CacheShiftReal(ie39c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie39e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie39ec, NumPar, params);
    if (i>=0) {
        return(ie39ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp39e,mass);
        CacheShiftReal(ie39ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie40(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie40c, NumPar, params);
    if (i>=0) {
        return(ie40c[NumPar][i] );
    } else {
        double newResult = interpolate (temp40,mass);
        CacheShiftReal(ie40c, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ie40e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ie40ec, NumPar, params);
    if (i>=0) {
        return(ie40ec[NumPar][i] );
    } else {
        double newResult = interpolate (temp40e,mass);
        CacheShiftReal(ie40ec, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_taunu_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_taunu_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_taunu_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_pp_Hpm_taunu,mass);
        CacheShiftReal(ip_ex_pp_Hpm_taunu_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_taunu_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_taunu_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_taunu_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_pp_Hpm_taunu_e,mass);
        CacheShiftReal(ip_ex_pp_Hpm_taunu_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_taunu_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_taunu_CMS8_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_taunu_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_pp_Hp_taunu,mass);
        CacheShiftReal(ip_ex_pp_Hp_taunu_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_taunu_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_taunu_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_taunu_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_pp_Hp_taunu_e,mass);
        CacheShiftReal(ip_ex_pp_Hp_taunu_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_tb_ATLAS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_tb_ATLAS8_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_tb_ATLAS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_pp_Hpm_tb,mass);
        CacheShiftReal(ip_ex_pp_Hpm_tb_ATLAS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_tb_ATLAS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_tb_ATLAS8_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_tb_ATLAS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS8_pp_Hpm_tb_e,mass);
        CacheShiftReal(ip_ex_pp_Hpm_tb_ATLAS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_tb_CMS8(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_tb_CMS8_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_tb_CMS8_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_pp_Hp_tb,mass);
        CacheShiftReal(ip_ex_pp_Hp_tb_CMS8_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_tb_CMS8_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_tb_CMS8_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_tb_CMS8_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS8_pp_Hp_tb_e,mass);
        CacheShiftReal(ip_ex_pp_Hp_tb_CMS8_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_taunu_ATLAS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_taunu_ATLAS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_taunu_ATLAS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_Hpm_taunu,mass);
        CacheShiftReal(ip_ex_pp_Hpm_taunu_ATLAS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_taunu_ATLAS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_taunu_ATLAS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_taunu_ATLAS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_Hpm_taunu_e,mass);
        CacheShiftReal(ip_ex_pp_Hpm_taunu_ATLAS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_taunu_CMS13(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_taunu_CMS13_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_taunu_CMS13_cache[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_Hpm_taunu,mass);
        CacheShiftReal(ip_ex_pp_Hpm_taunu_CMS13_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hpm_taunu_CMS13_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hpm_taunu_CMS13_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hpm_taunu_CMS13_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (CMS13_pp_Hpm_taunu_e,mass);
        CacheShiftReal(ip_ex_pp_Hpm_taunu_CMS13_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_tb_ATLAS13_1(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_tb_ATLAS13_1_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_tb_ATLAS13_1_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_Hp_tb1,mass);
        CacheShiftReal(ip_ex_pp_Hp_tb_ATLAS13_1_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_tb_ATLAS13_1_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_tb_ATLAS13_1_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_tb_ATLAS13_1_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_Hp_tb1_e,mass);
        CacheShiftReal(ip_ex_pp_Hp_tb_ATLAS13_1_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_tb_ATLAS13_2(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_tb_ATLAS13_2_cache, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_tb_ATLAS13_2_cache[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_Hp_tb2,mass);
        CacheShiftReal(ip_ex_pp_Hp_tb_ATLAS13_2_cache, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_pp_Hp_tb_ATLAS13_2_e(double mass){
    int NumPar = 1;
    double params[] = {mass};

    int i = CacheCheckReal(ip_ex_pp_Hp_tb_ATLAS13_2_cache_e, NumPar, params);
    if (i>=0) {
        return(ip_ex_pp_Hp_tb_ATLAS13_2_cache_e[NumPar][i] );
    } else {
        double newResult = interpolate (ATLAS13_pp_Hp_tb2_e,mass);
        CacheShiftReal(ip_ex_pp_Hp_tb_ATLAS13_2_cache_e, NumPar, params, newResult);
        return newResult;
    }
}



double GeneralTHDMcache::ip_ex_bsgamma(double logtb, double logmHp){
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

// Function needed to calculate some loop functions

gslpp::complex GeneralTHDMcache::f_func(const double x) const{
    if(x<1) {
    gslpp::complex z = -gslpp::complex::i()*M_PI;
    return -pow(log((1.0+sqrt(1.0-x))/(1.0-sqrt(1.0-x)))+z,2)/4.0;
    }
    else {
        return pow(asin(sqrt(1.0/x)),2);
    }
}


gslpp::complex GeneralTHDMcache::g_func(const double x) const{
    if(x<1) {
    gslpp::complex z = -gslpp::complex::i()*M_PI;
    gslpp::complex gs1 = sqrt(1.0-x)*(log((1.0+sqrt(1.0-x))/(1.0-sqrt(1.0-x)))+z)/2.0;
    return gs1;
    }
    else {
        gslpp::complex gg1 = sqrt(x-1.0)*asin(sqrt(1.0/x));
        return gg1;
    }
}



gslpp::complex GeneralTHDMcache::Int1(const double tau, const double lambda) const{
    return tau*lambda/(tau-lambda)/2.0+tau*tau*lambda*lambda/((tau-lambda)
           *(tau-lambda))/2.0*(f_func(tau)-f_func(lambda))+tau*tau*lambda/((tau-lambda)
           *(tau-lambda))*(g_func(tau)-g_func(lambda));
}



gslpp::complex GeneralTHDMcache::Int2(const double tau, const double lambda) const{
    return -tau*lambda/(tau-lambda)/2.0*(f_func(tau)-f_func(lambda));
}

 //Loop functions needed for decays and cross sections


gslpp::complex GeneralTHDMcache::I_h_U(const double mHl2, const double Mu, const double Mc, const double Mt) const {
    int NumPar = 4;
    double params[] = {mHl2, Mu, Mc, Mt};

    int i = CacheCheck(I_h_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_U_cache[NumPar][i] );
    } else {
    	double TAUu=4.0*Mu*Mu/mHl2;
    	double TAUc=4.0*Mc*Mc/mHl2;
    	double TAUt=4.0*Mt*Mt/mHl2;
        gslpp::complex newResult = -(8./3.)*(TAUu*(1.0+(1.0-TAUu)*f_func(TAUu))
                         +TAUc*(1.0+(1.0-TAUc)*f_func(TAUc))+TAUt*(1.0+(1.0-TAUt)*f_func(TAUt)));
        CacheShift(I_h_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::I_HH_U(const double mHh2, const double Mc, const double Mt) const {
    int NumPar = 3;
    double params[] = {mHh2, Mc, Mt};

    int i = CacheCheck(I_HH_U_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_U_cache[NumPar][i] );
    } else {
    	double TAUc=4.0*Mc*Mc/mHh2;
    	double TAUt=4.0*Mt*Mt/mHh2;
        gslpp::complex newResult = -(8./3.)*(TAUc*(1.0+(1.0-TAUc)*f_func(TAUc))
                      +TAUt*(1.0+(1.0-TAUt)*f_func(TAUt)));
        CacheShift(I_HH_U_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::I_A_U(const double mA2, const double Mc, const double Mt) const {
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

gslpp::complex GeneralTHDMcache::I_h_D(const double mHl2, const double Md, const double Ms, const double Mb) const {
    int NumPar = 4;
    double params[] = {mHl2, Md, Ms, Mb};

    int i = CacheCheck(I_h_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_D_cache[NumPar][i] );
    } else {
    	double TAUd=4.0*Md*Md/mHl2;
    	double TAUs=4.0*Ms*Ms/mHl2;
    	double TAUb=4.0*Mb*Mb/mHl2;
        gslpp::complex newResult = -(2./3.)*(TAUd*(1.0+(1.0-TAUd)*f_func(TAUd))
                         +TAUs*(1.0+(1.0-TAUs)*f_func(TAUs))+TAUb*(1.0+(1.0-TAUb)*f_func(TAUb)));
        CacheShift(I_h_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::I_HH_D(const double mHh2, const double Ms, const double Mb) const {
    int NumPar = 3;
    double params[] = {mHh2, Ms, Mb};

    int i = CacheCheck(I_HH_D_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_D_cache[NumPar][i] );
    } else {
    	double TAUs=4.0*Ms*Ms/mHh2;
    	double TAUb=4.0*Mb*Mb/mHh2;
        gslpp::complex newResult = -(2./3.)*(TAUs*(1.0+(1.0-TAUs)*f_func(TAUs))
                      +TAUb*(1.0+(1.0-TAUb)*f_func(TAUb)));
        CacheShift(I_HH_D_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::I_A_D(const double mA2, const double Ms, const double Mb) const {
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

gslpp::complex GeneralTHDMcache::I_h_L(const double mHl2, const double Me, const double Mmu, const double Mtau) const {
    int NumPar = 4;
    double params[] = {mHl2, Me, Mmu, Mtau};

    int i = CacheCheck(I_h_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_h_L_cache[NumPar][i] );
    } else {
    	double TAUe=4.0*Me*Me/mHl2;
    	double TAUmu=4.0*Mmu*Mmu/mHl2;
    	double TAUtau=4.0*Mtau*Mtau/mHl2;
        gslpp::complex newResult = -2.0*(TAUe*(1.0+(1.0-TAUe)*f_func(TAUe))
                         +TAUmu*(1.0+(1.0-TAUmu)*f_func(TAUmu))
                         +TAUtau*(1.0+(1.0-TAUtau)*f_func(TAUtau)));
        CacheShift(I_h_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::I_HH_L(const double mHh2, const double Mmu, const double Mtau) const {
    int NumPar = 3;
    double params[] = {mHh2, Mmu, Mtau};

    int i = CacheCheck(I_HH_L_cache, NumPar, params);
    if (i>=0) {
        return ( I_HH_L_cache[NumPar][i] );
    } else {
    	double TAUmu=4.0*Mmu*Mmu/mHh2;
    	double TAUtau=4.0*Mtau*Mtau/mHh2;
        gslpp::complex newResult = -2.0*(TAUmu*(1.0+(1.0-TAUmu)*f_func(TAUmu))+
                           TAUtau*(1.0+(1.0-TAUtau)*f_func(TAUtau)));
        CacheShift(I_HH_L_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::I_A_L(const double mA2, const double Mmu, const double Mtau) const {
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

gslpp::complex GeneralTHDMcache::I_H_W(const double mH, const double MW) const {
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

gslpp::complex GeneralTHDMcache::I_H_Hp(const double mHpsq, const double mH) const {
    int NumPar = 2;
    double params[] = {mHpsq, mH};

    int i = CacheCheck(I_H_Hp_cache, NumPar, params);
    if (i>=0) {
        return ( I_H_Hp_cache[NumPar][i] );
    } else {
        double TAUhp=4.0*mHpsq/(mH*mH);
        gslpp::complex newResult = -TAUhp*(1.0-TAUhp*f_func(TAUhp));
        CacheShift(I_H_Hp_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::A_h_U(const double mHl2, const double cW2, const double Mu, const double Mc, const double Mt, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl2, cW2, Mu, Mc, Mt, MZ};

    int i = CacheCheck(A_h_U_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_U_cache[NumPar][i] );
    } else {
    	double TAUu=4.0*Mu*Mu/mHl2;
    	double TAUc=4.0*Mc*Mc/mHl2;
    	double TAUt=4.0*Mt*Mt/mHl2;
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


gslpp::complex GeneralTHDMcache::A_HH_U(const double mHh2, const double cW2, const double Mc, const double Mt, const double MZ) const {
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

gslpp::complex GeneralTHDMcache::A_A_U(const double mA2, const double cW2, const double Mc, const double Mt, const double MZ) const {
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



gslpp::complex GeneralTHDMcache::A_h_D(const double mHl2, const double cW2, const double Md, const double Ms, const double Mb, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl2, cW2, Md, Ms, Mb, MZ};

    int i = CacheCheck(A_h_D_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_D_cache[NumPar][i] );
    } else {
    	double TAUd=4.0*Md*Md/mHl2;
    	double TAUs=4.0*Ms*Ms/mHl2;
    	double TAUb=4.0*Mb*Mb/mHl2;
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


gslpp::complex GeneralTHDMcache::A_HH_D(const double mHh2, const double cW2, const double Ms, const double Mb, const double MZ) const {
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

gslpp::complex GeneralTHDMcache::A_A_D(const double mA2, const double cW2, const double Ms, const double Mb, const double MZ) const {
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

gslpp::complex GeneralTHDMcache::A_h_L(const double mHl2, const double cW2, const double Me, const double Mmu, const double Mtau, const double MZ) const {
    int NumPar = 6;
    double params[] = {mHl2, cW2, Me, Mmu, Mtau, MZ};

    int i = CacheCheck(A_h_L_cache, NumPar, params);
    if (i>=0) {
        return ( A_h_L_cache[NumPar][i] );
    } else {
    	double TAUe=4.0*Me*Me/mHl2;
    	double TAUmu=4.0*Mmu*Mmu/mHl2;
    	double TAUtau=4.0*Mtau*Mtau/mHl2;
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

gslpp::complex GeneralTHDMcache::A_HH_L(const double mHh2, const double cW2, const double Mmu, const double Mtau, const double MZ) const {
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
    


gslpp::complex GeneralTHDMcache::A_A_L(const double mA2, const double cW2, const double Mmu, const double Mtau, const double MZ) const {
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

gslpp::complex GeneralTHDMcache::A_H_W(const double mH, const double cW2, const double MW, const double MZ) const {
    int NumPar = 4;
    double params[] = {mH, cW2, MW, MZ};

    int i = CacheCheck(A_H_W_cache, NumPar, params);
    if (i>=0) {
        return ( A_H_W_cache[NumPar][i] );
    } else {
        double TAUw=4.0*MW*MW/(mH*mH);
        double LAMw=4.0*MW*MW/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = -sqrt(cW2/sW2)*(4.0*(3.0-sW2/cW2)*Int2(TAUw,LAMw)
                            +((1.0+2.0/TAUw)*sW2/cW2-(5.0+2.0/TAUw))*Int1(TAUw,LAMw));
        CacheShift(A_H_W_cache, NumPar, params, newResult);
        return newResult;
    }
}

gslpp::complex GeneralTHDMcache::A_H_Hp(const double mHpsq, const double mH, const double cW2, const double MZ) const {
    int NumPar = 4;
    double params[] = {mHpsq, mH, cW2, MZ};

    int i = CacheCheck(A_H_Hp_cache, NumPar, params);
    if (i>=0) {
        return ( A_H_Hp_cache[NumPar][i] );
    } else {
        double TAUhp=4.0*mHpsq/(mH*mH);
        double LAMhp=4.0*mHpsq/(MZ*MZ);
	double sW2=1.0-cW2;
        gslpp::complex newResult = (1.0-2.0*sW2)/sqrt(cW2*sW2)*Int1(TAUhp,LAMhp);
        CacheShift(A_H_Hp_cache, NumPar, params, newResult);
        return newResult;
    }
}

int GeneralTHDMcache::HSTheta (const double x) const{
    if(x<0) return 0.0;
    else return 1.0;
}


double GeneralTHDMcache::KaellenFunction(const double a2, const double b2, const double c2) const{
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

    
    double GeneralTHDMcache::cW2GTHDM(const double c02) const{
    return c02;
    }



    double GeneralTHDMcache::MWGTHDM(const double MW) const{
    return MW;
    }



    double GeneralTHDMcache::beta(const double mf, const double m_2) const
    {
            return sqrt(1.0-4.0*mf*mf/m_2);
    }
    
    double GeneralTHDMcache::lambdaijk(const double Ri1,const double Ri2,const double Ri3,const double Rj1,const double Rj2,const double Rj3, const double Rk1,const double Rk2,const double Rk3) const
    {
        return (1.0/2.0)*(Imlambdag_GTHDM*(-Ri3*Rj3*Rk3 - Ri2*Rj2*Rk3) - 3.0*Imlambdaf_GTHDM*Ri1*Rj1*Rk3 
                + 2.0*lambdaa_GTHDM*Ri1*Rj1*Rk1 + Relambdag_GTHDM*Ri2*Rj2*Rk2 + 3.0*Relambdaf_GTHDM*Ri1*Rj1*Rk2
                +(2.0*Relambdae_GTHDM + lambdac_GTHDM + lambdad_GTHDM)*Ri1*Rj1*Rk2 - (2.0*Relambdae_GTHDM - lambdac_GTHDM - lambdad_GTHDM)*Ri1*Rj3*Rk3
                + Relambdag_GTHDM*Ri2*Rj3*Rk3 - Imlambdae_GTHDM*Ri1*Rj2*Rk3);
    }
    
    double GeneralTHDMcache::lambdaipm(const double Ri1,const double Ri2,const double Ri3) const
    {
        return vev*(lambdac_GTHDM*Ri1 + Relambdag_GTHDM*Ri2 - Imlambdag_GTHDM*Ri3);
    }
    

       
void GeneralTHDMcache::computeSignalStrengths()
{
    
    
    double GF=1/(sqrt(2.0)*vev*vev);
    double sW2=1.0-cW2;

      //FLAG to select only the model in which all the couplings are the same (by families)
    
    if (!myGTHDM->getATHDMflag())
    {
        throw std::runtime_error("Direct Searches are only aviable in the A2HDM.");
    }
  
        /*complex i */
    
     gslpp::complex i = gslpp::complex::i();
     
   
    
    
    /*up, down and leptonic couplings */
    gslpp::complex su = myGTHDM->getNu_33();
    gslpp::complex sd = myGTHDM->getNd_33();
    gslpp::complex sl = myGTHDM->getNl_33();

    
    double m1_2 = 0.0;
    double m2_2 = 0.0;
    double m3_2 = 0.0;
    double R11 = 0.0;
    double R12 = 0.0;
    double R13 = 0.0;
    double R21 = 0.0;
    double R22 = 0.0;
    double R23 = 0.0;
    double R31 = 0.0;
    double R32 = 0.0;
    double R33 = 0.0;
    

        
    //If to always set 1 as the SM Higgs and 3 as the heaviest
    if(mH1sq == mHl*mHl )
    {
         m1_2 = mH1sq;
          
         R11 = R11_GTHDM;
         R12 = R12_GTHDM;
         R13 = R13_GTHDM;
         
        if(mH2sq<mH3sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH3sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;
        }
         else if(mH3sq<mH2sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH2sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;
        }
    }
    else if(mH2sq == mHl*mHl )
    {
         m1_2 = mH2sq;
         R11 = R21_GTHDM;
         R12 = R22_GTHDM;
         R13 = R23_GTHDM;
         
         if(mH1sq<mH3sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH3sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;

        }
         else if(mH3sq<mH1sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH1sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
  
    }
    else if(mH3sq == mHl*mHl )
    {
         m1_2 = mH3sq;

         R11 = R31_GTHDM;
         R12 = R32_GTHDM;
         R13 = R33_GTHDM;
         
          if(mH1sq<mH2sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH2sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;

        }
         else if(mH2sq<mH1sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH1sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
         
    }
    
    double m1 = sqrt(m1_2);
    double m2 = sqrt(m2_2);
    double m3 = sqrt(m3_2);
    
    
      //fermionic couplings for phi1
    
    gslpp::complex yu1 = R11 + (R12 - i*R13)*su.conjugate();
    gslpp::complex yd1 = R11 + (R12 + i*R13)*sd;
    gslpp::complex yl1 = R11 + (R12 + i*R13)*sl;
    
     //The Standard Model h branching ratios

    BrSM_htobb = 5.77e-1;
    BrSM_htotautau = 6.32e-2;
    BrSM_htogaga = 2.28e-3;
    double BrSM_htoWW = 2.15e-1;
    double BrSM_htoZZ = 2.64e-2;
    double BrSM_htogg = 8.57e-2;
    double BrSM_htoZga = 1.54e-3;
    double BrSM_htocc = 2.91e-2;
    
 
    //The ggH cross section in the SM at 8 TeV
    double SigmaggF8 = myGTHDM->computeSigmaggH(8.0);
    //The ggH cross section in the SM at 13 TeV.
    double SigmaggF13 = myGTHDM->computeSigmaggH(13.0);
    //The square of the top-quark contribution to the ggH cross section in the SM at 8 TeV
    double Sigmaggh_tt8 = myGTHDM->computeSigmaggH_tt(8.0);
    //The square of the top-quark contribution to the ggH cross section in the SM at 13 TeV
//    double Sigmaggh_tt13 = myTHDM->computeSigmaggH_tt(13.0);
    //The square of the bottom-quark contribution to the ggH cross section in the SM at 8 TeV
    double Sigmaggh_bb8 = myGTHDM->computeSigmaggH_bb(8.0);
    //The square of the bottom-quark contribution to the ggH cross section in the SM at 13 TeV
//    double Sigmaggh_bb13 = myTHDM->computeSigmaggH_bb(13.0);
    //The ttH production cross section in the SM at 8 TeV
    double Sigmatth8 = myGTHDM->computeSigmattH(8.0);
    //The ttH production cross section in the SM at 13 TeV
    double Sigmatth13 = myGTHDM->computeSigmattH(13.0);
    //The bbH production cross section in the SM at 13 TeV
    double Sigmabbh13 = ip_cs_pptobbH_13(mHl);
    //The VBF plus Vh production cross section in the SM at 13 TeV
    double SigmaVBFVh13 = (myGTHDM->computeSigmaVBF(13.0)+myGTHDM->computeSigmaWH(13.0)+myGTHDM->computeSigmaZH(13.0));

    
 //////gg
    
    
    //gg -> A (phi odd) production cross section ratio at 8 TeV, top loop only over total
    double rSigmagghO_t8 = ip_csr_ggA_t_8(m1);
    //gg -> A (phi odd) production cross section ratio at 8 TeV, bottom loop only over total
    double rSigmagghO_b8 = ip_csr_ggA_b_8(m1);
    
    //gg -> A (phiodd) production cross section at 8 TeV, total
    double SigmagghO_8 = ip_cs_ggtoA_8(m1);
    
    
    
    
    
    /* rh_ii is the ratio of the squared 2HDM vertex coupling of h to
     * the particle i and the respective squared SM coupling.*/
    
    /*
     double rh_QtQt= (yu1.real())*(yu1.real()) + (yu1.imag()*yu1.imag()*1/(beta(Mt, m1_2)*beta(Mt, m1_2))); 
     double rh_QcQc= (yu1.real())*(yu1.real()) + (yu1.imag()*yu1.imag()*1/(beta(Mc, m1_2)*beta(Mc, m1_2))); 
     double rh_VV=R11*R11;
     double rh_QbQb = (yd1.real())*(yd1.real()) + (yd1.imag()*yd1.imag()*1/(beta(Mb, m1_2)*beta(Mb, m1_2))); 
     double rh_tautau = (yl1.real())*(yl1.real()) + (yl1.imag()*yl1.imag()*1/(beta(Mtau, m1_2)*beta(Mtau, m1_2))); 
     double rh_mumu = (yl1.real())*(yl1.real()) + (yl1.imag()*yl1.imag()*1/(beta(Mmu, m1_2)*beta(Mmu, m1_2))); 
    double rh_gg=yu1.real()*yd1.real() + (yu1.real()*yu1.real() - yu1.real()*yd1.real())*(Sigmaggh_tt8/SigmaggF8)  + (yd1.real()*yd1.real() - yu1.real()*yd1.real())*(Sigmaggh_bb8/SigmaggF8) + (yu1.imag()*yu1.imag()+ (yu1.imag()*yu1.imag() - yu1.imag()*yd1.imag())*rSigmagghO_t8 + (yd1.imag()*yd1.imag() - yu1.imag()*yd1.imag())*rSigmagghO_b8)*(SigmagghO_8/SigmaggF8);
     */
    
     rh_QuQuE= yu1.real()*yu1.real(); 
     rh_QuQuO= yu1.imag()*yu1.imag(); 
     rh_QdQdE= yd1.real()*yd1.real(); 
     rh_QdQdO= yd1.imag()*yd1.imag(); 
     rh_QlQlE= yl1.real()*yl1.real(); 
     rh_QlQlO= yl1.imag()*yl1.imag(); 
     rh_ggE = yu1.real()*yd1.real() + (yu1.real()*yu1.real() - yu1.real()*yd1.real())*(Sigmaggh_tt8/SigmaggF8)  + (yd1.real()*yd1.real() - yu1.real()*yd1.real())*(Sigmaggh_bb8/SigmaggF8);
     rh_ggO = yu1.imag()*yu1.imag() + (yu1.imag()*yu1.imag() - yu1.imag()*yd1.imag())*rSigmagghO_b8  + (yd1.imag()*yd1.imag() - yu1.imag()*yd1.imag())*rSigmagghO_b8;
     rh_VV=R11*R11;
    
     /*Gamma_hgaga and Gamma_hZga expressions ...*/
    
    /*Decay to photons. The fermionic contribution has a CP-even part (HH) and a CP-odd (A)*/
    /*CP EVEN*/
    
   
    
    gslpp::complex fermU=I_h_U(m1_2,Mu,Mc,Mt);
    gslpp::complex fermD=I_h_D(m1_2,Md,Ms,Mb);
    gslpp::complex fermL=I_h_L(m1_2,Me, Mmu,Mtau);
    gslpp::complex I_hSM_W=I_H_W(mHl*mHl,MW);
    gslpp::complex I_h_W=R11*I_hSM_W;

    
    gslpp::complex I_hSM_F= fermU+ fermD+fermL;
    gslpp::complex I_hE_F= yu1.real()*fermU+ yd1.real()*fermD+yl1.real()*fermL;
                                                                               

                                     
    double lambdahHpHm =  lambdaipm(R11, R12, R13);
    gslpp::complex I_h_Hp=(vev*vev)/(2.0*mHpsq)*I_H_Hp(mHpsq,m1)*(lambdahHpHm);
    
    
    /*CP ODD */
            
    gslpp::complex I_h_Ux=I_A_U(m1_2,Mc,Mt);
    gslpp::complex I_h_Dx=I_A_D(m1_2,Ms,Mb);
    gslpp::complex I_h_Lx=I_A_L(m1_2,Mmu,Mtau);
                                                                               
    gslpp::complex I_hO_F = yu1.imag()*I_h_Ux + yd1.imag()*I_h_Dx + yl1.imag()*I_h_Lx;
    

    double Gamma_hgaga=(GF*Ale*Ale*m1*m1*m1/(sqrt(2.0)*128.0*M_PI*M_PI*M_PI))*((I_hE_F+I_h_W+I_h_Hp).abs2()+ (I_hO_F).abs2());
    double rh_gaga = ((I_hE_F+I_h_W+I_h_Hp).abs2()+ (I_hO_F).abs2())/(I_hSM_F +I_hSM_W ).abs2();
                                                                               
    /*Decay to Z gamma
    CP-EVEN PART*/

    gslpp::complex A_hE_Ux = A_h_U(m1_2,cW2,Mu,Mc,Mt,MZ);
    gslpp::complex A_hE_Dx = A_h_D(m1_2,cW2,Md,Ms,Mb,MZ);
    gslpp::complex A_hE_Lx  = A_h_L(m1_2,cW2,Me,Mmu,Mtau,MZ);
    gslpp::complex A_hSM_W = A_H_W(m1_2,cW2,MW,MZ);
    gslpp::complex A_h_W = R11*A_hSM_W;
    
    
    gslpp::complex A_hSM_F = (A_hE_Ux+ A_hE_Dx+ A_hE_Lx)/sqrt(sW2*cW2);                                                       
    gslpp::complex A_hE_F = (yu1.real()*A_hE_Ux+ yd1.real()*A_hE_Dx+ yl1.real()*A_hE_Lx)/sqrt(sW2*cW2);
  
        /*  REVISAR AIXO.  DEPEN DE LA BASE DEL POTENCIAL!!! 
     double lambdaphi3Hpg =  (lambda3*R31 + lambda7.real()*R32 - lambda7.imag()*R33)*/

    gslpp::complex A_h_Hp =(vev*vev)/(2.0*mHpsq)*A_H_Hp(mHpsq,m1,cW2,MZ)*(lambdahHpHm);

    /*CP-ODD PART*/
                                                                               
    gslpp::complex A_hO_Ux = A_A_U(m1_2,cW2,Mc,Mt,MZ);
    gslpp::complex A_hO_Dx = A_A_D(m1_2,cW2,Ms,Mb,MZ);
    gslpp::complex A_hO_Lx = A_A_L(m1_2,cW2,Mmu,Mtau,MZ);
                                                                               
    gslpp::complex A_hO_F=yu1.imag()*A_hO_Ux + yd1.imag()*A_hO_Dx + yl1.imag()*A_hO_Lx;
    
                                                                             
                                                                               
    double Gamma_hZga=HSTheta(m1-MZ)*GF*Ale*Ale*m1*m1*m1/(sqrt(2.0)*64.0*M_PI*M_PI*M_PI)*(1.0-MZ*MZ/(m1*m1))*(1.0-MZ*MZ/(m1*m1))*(1.0-MZ*MZ/(m1*m1))*((A_hE_F+A_h_W+A_h_Hp).abs2()+ A_hO_F.abs2());
    double rh_Zga = ((A_hE_F+A_h_W+A_h_Hp).abs2()+ A_hO_F.abs2())/(A_hSM_F +A_hSM_W ).abs2();

       
    /*Decay to gluons*/
                        
    double Gamma_hggSM=GF*Als*Als*m3*m3*m3/(sqrt(2.0)*16.0*M_PI*M_PI*M_PI)*(9.0/4.0)*(fermU/4.0+fermD).abs2();
     
    double Gamma_hgg=(rh_ggE)*GF*Als*Als*m3*m3*m3/(sqrt(2.0)*16.0*M_PI*M_PI*M_PI)*(9.0/4.0)*(fermU/4.0+fermD).abs2()
                        +rh_ggO*GF*Als*Als*m3*m3*m3/(sqrt(2.0)*16.0*M_PI*M_PI*M_PI)*(9.0/4.0)*(I_h_Ux/4.0+I_h_Dx).abs2();
     
    
   
    /* ggF_tth8 is the ratio of the THDM and SM cross sections for ggF or tth production at 8 TeV*/
   // ggF_tth8 = (SigmaggF8*rh_gg + Sigmatth8*rh_QtQt)/(SigmaggF8 + Sigmatth8);
    /* ggF_tth13 is the ratio of the THDM and SM cross sections for ggF or tth production at 13 TeV */
   // ggF_tth13 = (SigmaggF13*rh_gg + Sigmatth13*rh_QtQt)/(SigmaggF13 + Sigmatth13);
    /* pph13 is the ratio of the THDM and SM cross sections for an h production at 13 TeV */
    //pph13 = (SigmaggF13*rh_gg + SigmaVBFVh13*rh_VV + Sigmatth13*rh_QtQt + Sigmabbh13*rh_QbQb)/(SigmaggF13 + SigmaVBFVh13 + Sigmatth13 + Sigmabbh13);
    /* VBF_Vh is the ratio of the THDM and SM cross sections for VBF or Vh production */
    //VBF_Vh = rh_VV;
    
    
    
    sumModBRs = BrSM_htobb*(rh_QdQdE + rh_QdQdO/(beta(Mb, m1_2)*beta(Mb, m1_2))) 
            + rh_VV*(BrSM_htoWW+BrSM_htoZZ) 
            + BrSM_htotautau*(rh_QlQlE + rh_QlQlO/(beta(Mtau, m1_2)*beta(Mtau, m1_2))) 
            + rh_gaga*BrSM_htogaga 
            +BrSM_htogg*(Gamma_hgg/Gamma_hggSM)
            + rh_Zga*BrSM_htoZga;
            + BrSM_htocc*(rh_QuQuE + rh_QuQuO/(beta(Mc, m1_2)*beta(Mc, m1_2))) ;  
                

    Gamma_h = sumModBRs*myGTHDM->computeGammaHTotal();
    
    
    /*GTHDM_BR_h_bb = rh_QbQb*BrSM_htobb/sumModBRs;
    GTHDM_BR_h_gaga = rh_gaga*BrSM_htogaga/sumModBRs;
    GTHDM_BR_h_tautau = rh_tautau*BrSM_htotautau/sumModBRs;
    GTHDM_BR_h_WW = rh_VV*BrSM_htoWW/sumModBRs;
    GTHDM_BR_h_ZZ = rh_VV*BrSM_htoZZ/sumModBRs;
    GTHDM_BR_h_gg = rh_gg*BrSM_htogg/sumModBRs;
    GTHDM_BR_h_cc = rh_QcQc*BrSM_htocc/sumModBRs;*/
    
    GTHDM_BR_h_bb=(rh_QdQdE + rh_QdQdE/(beta(Mb, m1_2)*beta(Mb, m1_2)))*BrSM_htobb/sumModBRs;
    GTHDM_BR_h_WW = rh_VV*BrSM_htoWW/sumModBRs;
    GTHDM_BR_h_ZZ = rh_VV*BrSM_htoZZ/sumModBRs;
    GTHDM_BR_h_tautau = BrSM_htotautau*(rh_QlQlE + rh_QlQlE/(beta(Mtau, m1_2)*beta(Mtau, m1_2)))/sumModBRs;
    GTHDM_BR_h_cc =(rh_QuQuE + rh_QuQuE/(beta(Mc, m1_2)*beta(Mc, m1_2)))/sumModBRs;
    GTHDM_BR_h_gaga = rh_gaga*BrSM_htogaga/sumModBRs;
    GTHDM_BR_h_gg = (Gamma_hgg/Gamma_hggSM)*BrSM_htogg/sumModBRs;


}
    



    
double GeneralTHDMcache::computephi2quantities()
{
    
    
    double GF=1/(sqrt(2.0)*vev*vev);
    double sW2=1.0-cW2;

      //FLAG to select only the model in which all the couplings are the same (by families)
    
    if (!myGTHDM->getATHDMflag())
    {
        throw std::runtime_error("Direct Searches are only aviable in the A2HDM.");
    }
  
        /*complex i */
    
     gslpp::complex i = gslpp::complex::i();
     
   
    
    
    /*up, down and leptonic couplings */
    gslpp::complex su = myGTHDM->getNu_33();
    gslpp::complex sd = myGTHDM->getNd_33();
    gslpp::complex sl = myGTHDM->getNl_33();

    double m1_2 = 0.0;
    double m2_2 = 0.0;
    double m3_2 = 0.0;
    double R11 = 0.0;
    double R12 = 0.0;
    double R13 = 0.0;
    double R21 = 0.0;
    double R22 = 0.0;
    double R23 = 0.0;
    double R31 = 0.0;
    double R32 = 0.0;
    double R33 = 0.0;
    
    
    //If to always set 1 as the SM Higgs and 3 as the heaviest
    if(mH1sq == mHl*mHl )
    {
         m1_2 = mH1sq;
          
         R11 = R11_GTHDM;
         R12 = R12_GTHDM;
         R13 = R13_GTHDM;
         
        if(mH2sq<mH3sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH3sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;
        }
         else if(mH3sq<mH2sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH2sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;
        }
    }
    else if(mH2sq == mHl*mHl )
    {
         m1_2 = mH2sq;
         R11 = R21_GTHDM;
         R12 = R22_GTHDM;
         R13 = R23_GTHDM;
         
         if(mH1sq<mH3sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH3sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;

        }
         else if(mH3sq<mH1sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH1sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
  
    }
    else if(mH3sq == mHl*mHl )
    {
         m1_2 = mH3sq;

         R11 = R31_GTHDM;
         R12 = R32_GTHDM;
         R13 = R33_GTHDM;
         
          if(mH1sq<mH2sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH2sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;

        }
         else if(mH2sq<mH1sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH1sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
         
    }
    
      if (m1_2 < 0 || m2_2 < 0 || m3_2 < 0) 
                return std::numeric_limits<double>::quiet_NaN();
    
    double m1 = sqrt(m1_2);
    double m2 = sqrt(m2_2);
    double m3 = sqrt(m3_2);
    

    //fermionic couplings for phi2
    
    gslpp::complex yu2 = R21 + (R22 - i*R23)*su.conjugate();
    gslpp::complex yd2 = R21 + (R22 + i*R23)*sd;
    gslpp::complex yl2 = R21 + (R22 + i*R23)*sl;
    
    
    
    //These cross sections ratios are necessary for rphi2_gg
    //At 8 TeV
    
    //SM gg -> H (phi even) production cross section ratio at 8 TeV, top loop only over total
    double rSigmaggphi2E_t8 = ip_csr_ggH_t_8(m2);
    //SM gg -> H (phi even) production cross section ratio at 8 TeV, bottom loop only over total
    double rSigmaggphi2E_b8 = ip_csr_ggH_b_8(m2);
    //gg -> H (phieven) production cross section at 8 TeV, total
    double Sigmaggphi2E_8 = ip_cs_ggtoH_8(m2);

    
    //gg -> A (phi odd) production cross section ratio at 8 TeV, top loop only over total
    double rSigmaggphi2O_t8 = ip_csr_ggA_t_8(m2);
    //gg -> A (phi odd) production cross section ratio at 8 TeV, bottom loop only over total
    double rSigmaggphi2O_b8 = ip_csr_ggA_b_8(m2);
    
    //gg -> A (phiodd) production cross section at 8 TeV, total
    double Sigmaggphi2O_8 = ip_cs_ggtoA_8(m2);
    
    
    /* r_ii is the ratio of the squared 2HDM vertex coupling of phi2
     * to the particle phi2 and the respective squared SM coupling.
     * phi2 is fixed to be the non-SM and lightests (phi2), but can be translated*/
    
    /*
    double rphi2_QtQt= (yu2.real())*(yu2.real()) + (yu2.imag()*yu2.imag()*pow(beta(Mt, m2_2), -2.0)); 
    double rphi2_QcQc= (yu2.real())*(yu2.real()) + (yu2.imag()*yu2.imag()*pow(beta(Mc, m2_2), -2.0)); 
     * double rphi2_QbQb = (yd2.real())*(yd2.real()) + (yd2.imag()*yd2.imag()*pow(beta(Mb, m2_2), -2.0));
    double rphi2_tautau = (yl2.real())*(yl2.real()) + (yl2.imag()*yl2.imag()*pow(beta(Mtau, m2_2), -2.0));
    double rphi2_mumu = (yl2.real())*(yl2.real()) + (yl2.imag()*yl2.imag()*pow(beta(Mmu, m2_2), -2.0));
     double rphi2_gg=yu2.real()*yd2.real() + (yu2.real()*yu2.real() - yu2.real()*yd2.real())*rSigmaggphi2E_t8  + (yd2.real()*yd2.real() - yu2.real()*yd2.real())*rSigmaggphi2E_b8 + (yu2.imag()*yu2.imag()+ (yu2.imag()*yu2.imag() - yu2.imag()*yd2.imag())*rSigmaggphi2O_t8  + (yd2.imag()*yd2.imag() - yu2.imag()*yd2.imag())*rSigmaggphi2O_b8)*(Sigmaggphi2O_8/Sigmaggphi2E_8);

      */
    double rphi2_QuQuE= yu2.real()*yu2.real(); 
    double rphi2_QuQuO= yu2.imag()*yu2.imag(); 
    double rphi2_QdQdE= yd2.real()*yd2.real(); 
    double rphi2_QdQdO= yd2.imag()*yd2.imag(); 
    double rphi2_QlQlE= yl2.real()*yl2.real(); 
    double rphi2_QlQlO= yl2.imag()*yl2.imag(); 
     rphi2_ggE = yu2.real()*yd2.real() + (yu2.real()*yu2.real() - yu2.real()*yd2.real())*rSigmaggphi2E_t8  + (yd2.real()*yd2.real() - yu2.real()*yd2.real())*rSigmaggphi2E_b8;
     rphi2_ggO = yu2.imag()*yu2.imag() + (yu2.imag()*yu2.imag() - yu2.imag()*yd2.imag())*rSigmaggphi2O_t8  + (yd2.imag()*yd2.imag() - yu2.imag()*yd2.imag())*rSigmaggphi2O_b8;
     rphi2_VV=R21*R21;

    
  
    /*Gamma_phi2gaga and Gamma_phi2Zga expressions ...*/
    
    /*Decay to photons. The fermionic contribution has a CP-even part (HH) and a CP-odd (A)*/
    /*CP EVEN*/
   
                                                                                  
    gslpp::complex I_HH2_Ux=I_HH_U(m2_2,Mc,Mt);
    gslpp::complex I_HH2_Dx=I_HH_D(m2_2,Ms,Mb);
    gslpp::complex I_HH2_Lx=I_HH_L(m2_2,Mmu,Mtau);
    gslpp::complex I_phi2E_F= yu2.real()*I_HH2_Ux+ yd2.real()*I_HH2_Dx+yl2.real()*I_HH2_Lx;
                                                                               
    gslpp::complex I_phi2_W=R21*I_H_W(m2_2,MW);

    
    double lambdaphi2HpHm = lambdaipm(R21, R22, R23);                                 
    gslpp::complex I_phi2_Hp=(vev*vev)/(2.0*mHpsq)*I_H_Hp(mHpsq,m2)*(lambdaphi2HpHm);
    
    
    /*CP ODD */
            
    gslpp::complex I_A2_Ux=I_A_U(m2_2,Mc,Mt);
    gslpp::complex I_A2_Dx=I_A_D(m2_2,Ms,Mb);
    gslpp::complex I_A2_Lx=I_A_L(m2_2,Mmu,Mtau);
                                                                               
    gslpp::complex I_phi2O_F = yu2.imag()*I_A2_Ux + yd2.imag()*I_A2_Dx + yl2.imag()*I_A2_Lx;
                                                                             
    double Gamma_phi2gaga=(GF*Ale*Ale*m2*m2*m2/(sqrt(2.0)*128.0*M_PI*M_PI*M_PI))*((I_phi2E_F+I_phi2_W+I_phi2_Hp).abs2()
                        + (I_phi2O_F).abs2());
    
      
     
        /*Decay to Z gamma
    CP-EVEN PART*/

    gslpp::complex A_HH2_Ux = A_HH_U(m2_2,cW2,Mc,Mt,MZ);
    gslpp::complex A_HH2_Dx = A_HH_D(m2_2,cW2,Ms,Mb,MZ);
    gslpp::complex A_HH2_Lx = A_HH_L(m2_2,cW2,Mmu,Mtau,MZ);
                                                                               
    gslpp::complex A_phi2E_F = (yu2.real()*A_HH2_Ux+ yd2.real()*A_HH2_Dx+ yl2.real()*A_HH2_Lx)/sqrt(sW2*cW2);
    gslpp::complex A_phi2_W = R21*A_H_W(m2,cW2,MW,MZ);
  
        /*  REVISAR AIXO.  DEPEN DE LA BASE DEL POTENCIAL!!! 
     double lambdaphi3Hpg =  (lambda3*R31 + lambda7.real()*R32 - lambda7.imag()*R33)*/
    
    gslpp::complex A_phi2_Hp = (vev*vev)/(2.0*mHpsq)*A_H_Hp(mHpsq,m3,cW2,MZ)*(lambdaphi2HpHm);

    /*CP-ODD PART*/
                                                                               
    gslpp::complex A_A2_Ux = A_A_U(m2_2,cW2,Mc,Mt,MZ);
    gslpp::complex A_A2_Dx = A_A_D(m2_2,cW2,Ms,Mb,MZ);
    gslpp::complex A_A2_Lx = A_A_L(m2_2,cW2,Mmu,Mtau,MZ);
                                                                               
    gslpp::complex A_phi2O_F=yu2.imag()*A_A2_Ux + yd2.imag()*A_A2_Dx + yl2.imag()*A_A2_Lx;
    
                                                                             
                                                                               
    double Gamma_phi2Zga=HSTheta(m2-MZ)*GF*Ale*Ale*m2*m2*m2/(sqrt(2.0)*64.0*M_PI*M_PI*M_PI)*(1.0-MZ*MZ/(m2*m2))*(1.0-MZ*MZ/(m2*m2))*(1.0-MZ*MZ/(m2*m2))*((A_phi2E_F+A_phi2_W+A_phi2_Hp).abs2()
                        + A_phi2O_F.abs2());

    
    
    
    
    /*Decay to gluons*/
          
    
       double Gamma_phi2gg=(rphi2_ggE)*GF*Als*Als*m2*m2*m2/(sqrt(2.0)*16.0*M_PI*M_PI*M_PI)*(9.0/4.0)*(I_HH2_Ux/4.0+I_HH2_Dx).abs2()
                        +rphi2_ggO*GF*Als*Als*m2*m2*m2/(sqrt(2.0)*16.0*M_PI*M_PI*M_PI)*(9.0/4.0)*(I_A2_Ux/4.0+I_A2_Dx).abs2(); 
       
 
    //Cross-sections of ggF, bbF and VBF at 8 TeV Sigmaxx_H8 = Sigmaxx_H8SM*rphi2_xx
/*
 SigmaggF_phi2_8=ip_cs_ggtoH_8(m2)*rphi2_gg;
 SigmabbF_phi2_8=ip_cs_pptobbH_8(m2)*rphi2_QbQb;
 SigmaVBF_phi2_8=ip_cs_VBFtoH_8(m2)*rphi2_VV;
 SigmattF_phi2_8=ip_cs_pptottH_8(m2)*rphi2_QtQt;
 SigmaVH_phi2_8=(ip_cs_WtoWH_8(m2)+ip_cs_ZtoZH_8(m2))*rphi2_VV;*/
 
   
SigmaggF_phi2_8=ip_cs_ggtoH_8(m2)* rphi2_ggE + ip_cs_ggtoA_8(m2)* rphi2_ggO;
SigmabbF_phi2_8=ip_cs_pptobbH_8(m2)*rphi2_QdQdE + ip_cs_pptobbA_8(m2)*rphi2_QdQdO;
SigmaVBF_phi2_8=ip_cs_VBFtoH_8(m2)*rphi2_VV;
SigmattF_phi2_8=ip_cs_pptottH_8(m2)*rphi2_QuQuE + ip_cs_pptottA_8(m2)*rphi2_QuQuO;
SigmaVH_phi2_8=(ip_cs_WtoWH_8(m2)+ip_cs_ZtoZH_8(m2))*rphi2_VV;
        

//SM PREDICTIONS

double SigmaTotSM_phi2_8 = 1.0e-15;
                                                                               
if (m3>=20. && m3 <=2000.) {
    SigmaTotSM_phi2_8=ip_cs_ggtoH_8(m2)+ip_cs_VBFtoH_8(m2)+ip_cs_WtoWH_8(m2)+ip_cs_ZtoZH_8(m2)+ip_cs_pptottH_8(m2)+ip_cs_pptobbH_8(m2);
}
 SigmaSumphi2_8 = SigmaggF_phi2_8 + SigmaVBF_phi2_8 + SigmaVH_phi2_8 + SigmattF_phi2_8 + SigmabbF_phi2_8;

 /*   SigmaggF_phi2_13=ip_cs_ggtoH_13(m2)*rphi2_gg;
    SigmabbF_phi2_13=ip_cs_pptobbH_13(m2)*rphi2_QbQb;
    SigmaVBF_phi2_13=ip_cs_VBFtoH_13(m2)*rphi2_VV;
    SigmattF_phi2_13=ip_cs_pptottH_13(m2)*rphi2_QtQt;
    SigmaVH_phi2_13=(ip_cs_WtoWH_13(m2)+ip_cs_ZtoZH_13(m2))*rphi2_VV;*/
 
 
  
    SigmaggF_phi2_13=ip_cs_ggtoH_13(m2)* rphi2_ggE + ip_cs_ggtoA_13(m2)* rphi2_ggO;
    SigmabbF_phi2_13=ip_cs_pptobbH_13(m2)*rphi2_QdQdE + ip_cs_pptobbA_13(m2)*rphi2_QdQdO;
    SigmaVBF_phi2_13=ip_cs_VBFtoH_13(m2)*rphi2_VV;
    SigmattF_phi2_13=ip_cs_pptottH_13(m2)*rphi2_QuQuE + ip_cs_pptottA_13(m2)*rphi2_QuQuO;
    SigmaVH_phi2_13=(ip_cs_WtoWH_13(m2)+ip_cs_ZtoZH_13(m2))*rphi2_VV;


    
 
//    double SigmaTotSM_H13 = 1.0e-15;
//    if (mHh>=20. && mHh <=2000.) {
//            SigmaTotSM_H13=ip_cs_ggtoH_13(mHh)+ip_cs_VBFtoH_13(mHh)+ip_cs_WtoWH_13(mHh)+ip_cs_ZtoZH_13(mHh)+ip_cs_pptottH_13(mHh)+ip_cs_pptobbH_13(mHh);
//    }
    SigmaSumphi2_13 = SigmaggF_phi2_13 + SigmaVBF_phi2_13 + SigmaVH_phi2_13 + SigmattF_phi2_13 + SigmabbF_phi2_13;
     
    double BrSM_phi2tott=ip_Br_HPtott(m2);
    double BrSM_phi2tocc=ip_Br_HPtocc(m2);
    double BrSM_phi2tobb=ip_Br_HPtobb(m2);
    double BrSM_phi2totautau=ip_Br_HPtotautau(m2);
    double BrSM_phi2tomumu=ip_Br_HPtomumu(m2);
    double BrSM_phi2toWW =ip_Br_HPtoWW(m2);
    double BrSM_phi2toZZ =ip_Br_HPtoZZ(m2);

    double Gammaphi2totSM=ip_GammaHPtotSM(m2);
    
    
    
    /*Decay of phi2 to the others scalars*/


 double lambda112 = lambdaijk(R11, R12, R13, R11, R12, R13, R21, R22, R23) + lambdaijk(R11, R12, R13, R21, R22, R23, R11, R12, R13)+ lambdaijk(R21, R22, R23, R11, R12, R13, R11, R12, R13);
 
//phi2 -> phi1phi1
double Gammaphi2_phi1phi1=HSTheta(m2 - 2.0*m1)*sqrt(std::fabs(1.0 - (4.0*m1_2)/m2_2))*lambda112*lambda112/(32.0*m2*M_PI);
//phi2 ->H+H-
double Gammaphi2_HpHm=HSTheta(m2 - 2.0*sqrt(mHpsq))*sqrt(std::fabs(1.0 - (4.0*mHpsq)/m2_2))*lambdaphi2HpHm*lambdaphi2HpHm/(32.0*m2*M_PI);
//phi2 -> phi1 Z
double Gammaphi2_phi1Z=HSTheta(m2-(m1+MZ))*pow(KaellenFunction(m2_2,MZ*MZ,m1_2),3)*(R23*R12 + R22*R13)*(R23*R12 + R22*R13)/(2.0*M_PI*vev*vev);
/* phi2 -> H+W- */
double Gammaphi2_HpW=HSTheta(m2-sqrt(mHpsq)-MW)*pow(KaellenFunction(m2_2,MW*MW,mHpsq),3)*(R23-i*R22).abs2()/(M_PI*vev*vev);

/*
 Gammaphi2tot= ((BrSM_phi2tott*rphi2_QtQt+BrSM_phi2tocc*rphi2_QcQc)+BrSM_phi2tobb*rphi2_QbQb+(BrSM_phi2totautau*rphi2_tautau+BrSM_phi2tomumu*rphi2_mumu)+(BrSM_phi2toWW+BrSM_phi2toZZ)*rphi2_VV)*Gammaphi2totSM+Gamma_phi2gaga+Gamma_phi2Zga+Gamma_phi2gg + Gammaphi2_phi1phi1+Gammaphi2_HpHm+Gammaphi2_phi1Z+Gammaphi2_HpW;

 */

 
 Gammaphi2tot= (BrSM_phi2tott*(rphi2_QuQuE + rphi2_QuQuE/(beta(Mt, m2_2)*beta(Mt, m2_2)))
         +BrSM_phi2tocc*(rphi2_QuQuE + rphi2_QuQuE/(beta(Mc, m2_2)*beta(Mc, m2_2)))
         +BrSM_phi2tobb*(rphi2_QdQdE + rphi2_QdQdE/(beta(Mb, m2_2)*beta(Mb, m2_2)))
         +BrSM_phi2totautau*(rphi2_QlQlE + rphi2_QlQlE/(beta(Mtau, m2_2)*beta(Mtau, m2_2)))
         +(BrSM_phi2toWW+BrSM_phi2toZZ)*rphi2_VV)*Gammaphi2totSM+Gamma_phi2gaga+Gamma_phi2Zga+Gamma_phi2gg 
         + Gammaphi2_phi1phi1+Gammaphi2_HpHm+Gammaphi2_phi1Z
         +Gammaphi2_HpW;

 
 /*Br_phi2tott=BrSM_phi2tott*rphi2_QtQt*Gammaphi2totSM/Gammaphi2tot;
 Br_phi2tobb=BrSM_phi2tobb*rphi2_QbQb*Gammaphi2totSM/Gammaphi2tot;
 Br_phi2totautau=BrSM_phi2totautau*rphi2_tautau*Gammaphi2totSM/Gammaphi2tot;*/
 
 
 Br_phi2tott=BrSM_phi2tott*(rphi2_QuQuE + rphi2_QuQuE/(beta(Mt, m2_2)*beta(Mt, m2_2)))*Gammaphi2totSM/Gammaphi2tot;
 Br_phi2tobb=BrSM_phi2tobb*(rphi2_QdQdE + rphi2_QdQdE/(beta(Mb, m2_2)*beta(Mb, m2_2)))*Gammaphi2totSM/Gammaphi2tot;
 Br_phi2totautau=BrSM_phi2totautau*(rphi2_QlQlE + rphi2_QlQlE/(beta(Mtau, m2_2)*beta(Mtau, m2_2)))*Gammaphi2totSM/Gammaphi2tot;
 
 Br_phi2toWW=BrSM_phi2toWW*rphi2_VV*Gammaphi2totSM/Gammaphi2tot;
 Br_phi2toZZ=BrSM_phi2toZZ*rphi2_VV*Gammaphi2totSM/Gammaphi2tot;
 Br_phi2togaga=Gamma_phi2gaga/Gammaphi2tot;
 Br_phi2toZga=Gamma_phi2Zga/Gammaphi2tot;
 Br_phi2tophi1phi1=Gammaphi2_phi1phi1/Gammaphi2tot;
 Br_phi2toHpHm=Gammaphi2_HpHm/Gammaphi2tot;
 Br_phi2tophi1Z=Gammaphi2_phi1Z/Gammaphi2tot;
 Br_phi2toHpW=Gammaphi2_HpW/Gammaphi2tot;
 
 return 0.;
   
}


    
double GeneralTHDMcache::computephi3quantities()
{
    
    
    double GF=1/(sqrt(2.0)*vev*vev);
    double sW2=1.0-cW2;

      //FLAG to select only the model in which all the couplings are the same (by families)
    
    if (!myGTHDM->getATHDMflag())
    {
        throw std::runtime_error("Direct Searches are only aviable in the A2HDM.");
    }
  
        /*complex i */
    
     gslpp::complex i = gslpp::complex::i();
     
   
    
    
    /*up, down and leptonic couplings */
    gslpp::complex su = myGTHDM->getNu_33();
    gslpp::complex sd = myGTHDM->getNd_33();
    gslpp::complex sl = myGTHDM->getNl_33();

    
    double m1_2 = 0.0;
    double m2_2 = 0.0;
    double m3_2 = 0.0;
    double R11 = 0.0;
    double R12 = 0.0;
    double R13 = 0.0;
    double R21 = 0.0;
    double R22 = 0.0;
    double R23 = 0.0;
    double R31 = 0.0;
    double R32 = 0.0;
    double R33 = 0.0;
        
    //If to always set 1 as the SM Higgs and 3 as the heaviest
    if(mH1sq == mHl*mHl )
    {
         m1_2 = mH1sq;
          
         R11 = R11_GTHDM;
         R12 = R12_GTHDM;
         R13 = R13_GTHDM;
         
        if(mH2sq<mH3sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH3sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;
        }
         else if(mH3sq<mH2sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH2sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;
        }
    }
    else if(mH2sq == mHl*mHl )
    {
         m1_2 = mH2sq;
         R11 = R21_GTHDM;
         R12 = R22_GTHDM;
         R13 = R23_GTHDM;
         
         if(mH1sq<mH3sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH3sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;

        }
         else if(mH3sq<mH1sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH1sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
  
    }
    else if(mH3sq == mHl*mHl )
    {
         m1_2 = mH3sq;

         R11 = R31_GTHDM;
         R12 = R32_GTHDM;
         R13 = R33_GTHDM;
         
          if(mH1sq<mH2sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH2sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;

        }
         else if(mH2sq<mH1sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH1sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
         
    }
          
     if (m1_2 < 0 || m2_2 < 0 || m3_2 < 0) 
                return std::numeric_limits<double>::quiet_NaN();
    
    double m1 = sqrt(m1_2);
    double m2 = sqrt(m2_2);
    double m3 = sqrt(m3_2);
    
    //fermionic couplings for phi3
    
    gslpp::complex yu3 = R31 + (R32 - i*R33)*su.conjugate();
    gslpp::complex yd3 = R31 + (R32 + i*R33)*sd;
    gslpp::complex yl3 = R31 + (R32 + i*R33)*sl;
    
    
    //These cross sections ratios are necessary for rphi3_gg
    //At 8 TeV
    
    //SM gg -> H (phi even) production cross section ratio at 8 TeV, top loop only over total
    double rSigmaggphi3E_t8 = ip_csr_ggH_t_8(m3);
    //SM gg -> H (phi even) production cross section ratio at 8 TeV, bottom loop only over total
    double rSigmaggphi3E_b8 = ip_csr_ggH_b_8(m3);
    //gg -> H (phieven) production cross section at 8 TeV, total
    double Sigmaggphi3E_8 = ip_cs_ggtoH_8(m3);
    
    
    //gg -> A (phi odd) production cross section ratio at 8 TeV, top loop only over total
    double rSigmaggphi3O_t8 = ip_csr_ggA_t_8(m3);
    //gg -> A (phi odd) production cross section ratio at 8 TeV, bottom loop only over total
    double rSigmaggphi3O_b8 = ip_csr_ggA_b_8(m3);
    
    //gg -> A (phiodd) production cross section at 8 TeV, total
    double Sigmaggphi3O_8 = ip_cs_ggtoA_8(m3);
    
   

       /* r_ii is the ratio of the squared 2HDM vertex coupling of phi3
     * to the particle phi3 and the respective squared SM coupling.
     * phi is fixed to be the non-SM and heaviest (phi3), but can be translated*/

    
    /*double rphi3_QtQt= (yu3.real())*(yu3.real()) + (yu3.imag()*yu3.imag()*pow(beta(Mt, m3_2), -2.0)); 
    double rphi3_QcQc= (yu3.real())*(yu3.real()) + (yu3.imag()*yu3.imag()*pow(beta(Mc, m3_2), -2.0));
    double rphi3_QbQb = (yd3.real())*(yd3.real()) + (yd3.imag()*yd3.imag()*pow(beta(Mb, m3_2), -2.0));
    double rphi3_tautau = (yl3.real())*(yl3.real()) + (yl3.imag()*yl3.imag()*pow(beta(Mtau, m3_2), -2.0));
    double rphi3_mumu = (yl3.real())*(yl3.real()) + (yl3.imag()*yl3.imag()*pow(beta(Mmu, m3_2), -2.0));
    double rphi3_gg=yu3.real()*yd3.real() + (yu3.real()*yu3.real() - yu3.real()*yd3.real())*rSigmaggphi3E_t8  + (yd3.real()*yd3.real() - yu3.real()*yd3.real())*rSigmaggphi3E_b8 + (yu3.imag()*yu3.imag()+ (yu3.imag()*yu3.imag() - yu3.imag()*yd3.imag())*rSigmaggphi3O_t8  + (yd3.imag()*yd3.imag() - yu3.imag()*yd3.imag())*rSigmaggphi3O_b8)*(Sigmaggphi3O_8/Sigmaggphi3E_8);
     */ 
    double rphi3_QuQuE= yu3.real()*yu3.real(); 
    double rphi3_QuQuO= yu3.imag()*yu3.imag(); 
    double rphi3_QdQdE= yd3.real()*yd3.real(); 
    double rphi3_QdQdO= yd3.imag()*yd3.imag(); 
    double rphi3_QlQlE= yl3.real()*yl3.real(); 
    double rphi3_QlQlO= yl3.imag()*yl3.imag(); 
     rphi3_ggE = yu3.real()*yd3.real() + (yu3.real()*yu3.real() - yu3.real()*yd3.real())*rSigmaggphi3E_t8  + (yd3.real()*yd3.real() - yu3.real()*yd3.real())*rSigmaggphi3E_b8;
     rphi3_ggO = yu3.imag()*yu3.imag() + (yu3.imag()*yu3.imag() - yu3.imag()*yd3.imag())*rSigmaggphi3O_t8  + (yd3.imag()*yd3.imag() - yu3.imag()*yd3.imag())*rSigmaggphi3O_b8;
     rphi3_VV=R31*R31;
  
    /*Gamma_phi3gaga and Gamma_phi3Zga expressions ...*/
    
    /*Decay to photons. The fermionic contribution has a CP-even part (HH) and a CP-odd (A)*/
    /*CP EVEN*/


                                                                                   
    gslpp::complex I_HH_Ux=I_HH_U(m3_2,Mc,Mt);
    gslpp::complex I_HH_Dx=I_HH_D(m3_2,Ms,Mb);
    gslpp::complex I_HH_Lx=I_HH_L(m3_2,Mmu,Mtau);
    gslpp::complex I_phi3E_F= yu3.real()*I_HH_Ux+ yd3.real()*I_HH_Dx+yl3.real()*I_HH_Lx;
                                                                               
    gslpp::complex I_phi3_W=R31*I_H_W(m3_2,MW);


                          
    double lambdaphi3HpHm =  lambdaipm(R31, R32, R33);
    gslpp::complex I_phi3_Hp=(vev*vev)/(2.0*mHpsq)*I_H_Hp(mHpsq,m3)*(lambdaphi3HpHm);
    
   /* 
    std::cout << "I_H_Hp(mHpsq,m3)  = " <<  I_H_Hp(mHpsq,m3) << std::endl;
     std::cout << "mHpsq  = " <<  mHpsq << std::endl;
        std::cout << "m3 = " << m3 << std::endl;
    std::cout << "lambdaphi3HpHm = " <<  lambdaphi3HpHm << std::endl;
      std::cout << "I_phi3_Hp first  = " <<  I_phi3_Hp << std::endl;
    */
    
    /*CP ODD */
            
    gslpp::complex I_A_Ux=I_A_U(m3_2,Mc,Mt);
    gslpp::complex I_A_Dx=I_A_D(m3_2,Ms,Mb);
    gslpp::complex I_A_Lx=I_A_L(m3_2,Mmu,Mtau);
                                                                               
    gslpp::complex I_phi3O_F = yu3.imag()*I_A_Ux + yd3.imag()*I_A_Dx + yl3.imag()*I_A_Lx;
                                                                             
    double Gamma_phi3gaga=(GF*Ale*Ale*m3*m3*m3/(sqrt(2.0)*128.0*M_PI*M_PI*M_PI))*((I_phi3E_F+I_phi3_W+I_phi3_Hp).abs2()
    + (I_phi3O_F).abs2());
    
  /*  std::cout << " Gamma_phi3gaga first = " << Gamma_phi3gaga << std::endl;
    std::cout << " GF*Ale*Ale*m3*m3*m3/(sqrt(2.0)*128.0*M_PI*M_PI*M_PI)  = " << GF*Ale*Ale*m3*m3*m3/(sqrt(2.0)*128.0*M_PI*M_PI*M_PI) << std::endl;
    std::cout << " I_phi3E_F = " << I_phi3E_F << std::endl;
    std::cout << " I_phi3_W = " << I_phi3_W << std::endl;
    std::cout << " I_phi3_Hp= " << I_phi3_Hp << std::endl;
    std::cout << " I_phi3O_F= " << I_phi3O_F << std::endl;*/
    
                                                                              
    /*Decay to Z gamma
    CP-EVEN PART*/

    gslpp::complex A_HH_Ux = A_HH_U(m3_2,cW2,Mc,Mt,MZ);
    gslpp::complex A_HH_Dx = A_HH_D(m3_2,cW2,Ms,Mb,MZ);
    gslpp::complex A_HH_Lx = A_HH_L(m3_2,cW2,Mmu,Mtau,MZ);
                                                                               
    gslpp::complex A_phi3E_F = (yu3.real()*A_HH_Ux+ yd3.real()*A_HH_Dx+ yl3.real()*A_HH_Lx)/sqrt(sW2*cW2);
    gslpp::complex A_phi3_W = R31*A_H_W(m3,cW2,MW,MZ);
  
        /*  REVISAR AIXO.  DEPEN DE LA BASE DEL POTENCIAL!!! 
     double lambdaphi3Hpg =  (lambda3*R31 + lambda7.real()*R32 - lambda7.imag()*R33)*/

    gslpp::complex A_phi3_Hp = (vev*vev)/(2.0*mHpsq)*A_H_Hp(mHpsq,m3,cW2,MZ)*(lambdaphi3HpHm);

    /*CP-ODD PART*/
                                                                               
    gslpp::complex A_A_Ux = A_A_U(m3_2,cW2,Mc,Mt,MZ);
    gslpp::complex A_A_Dx = A_A_D(m3_2,cW2,Ms,Mb,MZ);
    gslpp::complex A_A_Lx = A_A_L(m3_2,cW2,Mmu,Mtau,MZ);
                                                                               
    gslpp::complex A_phi3O_F=yu3.imag()*A_A_Ux + yd3.imag()*A_A_Dx + yl3.imag()*A_A_Lx;
                                                                                 
    double Gamma_phi3Zga=HSTheta(m3-MZ)*GF*Ale*Ale*m3*m3*m3/(sqrt(2.0)*64.0*M_PI*M_PI*M_PI)*(1.0-MZ*MZ/(m3*m3))*(1.0-MZ*MZ/(m3*m3))*(1.0-MZ*MZ/(m3*m3))*((A_phi3E_F+A_phi3_W+A_phi3_Hp).abs2()
                        + A_phi3O_F.abs2());

    
    /*Decay to gluons */
                                                                               
   double Gamma_phi3gg=(rphi3_ggE)*GF*Als*Als*m3*m3*m3/(sqrt(2.0)*16.0*M_PI*M_PI*M_PI)*(9.0/4.0)*(I_HH_Ux/4.0+I_HH_Dx).abs2()
                        +rphi3_ggO*GF*Als*Als*m3*m3*m3/(sqrt(2.0)*16.0*M_PI*M_PI*M_PI)*(9.0/4.0)*(I_A_Ux/4.0+I_A_Dx).abs2();
    

//Cross-sections of ggF, bbF and VBF at 8 TeV Sigmaxx_H8 = Sigmaxx_H8SM*rphi3_xx

 /*SigmaggF_phi3_8=ip_cs_ggtoH_8(m3)*rphi3_gg;
 SigmabbF_phi3_8=ip_cs_pptobbH_8(m3)*rphi3_QbQb;
 SigmattF_phi3_8=ip_cs_pptottH_8(m3)*rphi3_QtQt;
*/

SigmaggF_phi3_8=ip_cs_ggtoH_8(m3)* rphi3_ggE + ip_cs_ggtoA_8(m3)* rphi3_ggO;
SigmabbF_phi3_8=ip_cs_pptobbH_8(m3)*rphi3_QdQdE + ip_cs_pptobbA_8(m3)*rphi3_QdQdO;
SigmaVBF_phi3_8=ip_cs_VBFtoH_8(m3)*rphi3_VV;
SigmattF_phi3_8=ip_cs_pptottH_8(m3)*rphi3_QuQuE + ip_cs_pptottA_8(m3)*rphi3_QuQuO;
SigmaVH_phi3_8=(ip_cs_WtoWH_8(m3)+ip_cs_ZtoZH_8(m3))*rphi3_VV;
                                                                               
//SM PREDICTIONS
 SigmaTotSM_phi3_8 = 1.0e-15;
                                                                               
if (m3>=20. && m3 <=2000.) {
    SigmaTotSM_phi3_8=ip_cs_ggtoH_8(m3)+ip_cs_VBFtoH_8(m3)+ip_cs_WtoWH_8(m3)+ip_cs_ZtoZH_8(m3)+ip_cs_pptottH_8(m3)+ip_cs_pptobbH_8(m3);
}
 SigmaSumphi3_8 = SigmaggF_phi3_8 + SigmaVBF_phi3_8 + SigmaVH_phi3_8 + SigmattF_phi3_8 + SigmabbF_phi3_8;

  /*  SigmaggF_phi3_13=ip_cs_ggtoH_13(m3)*rphi3_gg;
    SigmabbF_phi3_13=ip_cs_pptobbH_13(m3)*rphi3_QbQb;
    SigmattF_phi3_13=ip_cs_pptottH_13(m3)*rphi3_QtQt;*/
    
    SigmaggF_phi3_13=ip_cs_ggtoH_13(m3)* rphi3_ggE + ip_cs_ggtoA_13(m3)* rphi3_ggO;
    SigmabbF_phi3_13=ip_cs_pptobbH_13(m3)*rphi3_QdQdE + ip_cs_pptobbA_13(m3)*rphi3_QdQdO;
    SigmaVBF_phi3_13=ip_cs_VBFtoH_13(m3)*rphi3_VV;
    SigmattF_phi3_13=ip_cs_pptottH_13(m3)*rphi3_QuQuE + ip_cs_pptottA_13(m3)*rphi3_QuQuO;
    SigmaVH_phi3_13=(ip_cs_WtoWH_13(m3)+ip_cs_ZtoZH_13(m3))*rphi3_VV;

  
//    double SigmaTotSM_H13 = 1.0e-15;
//    if (mHh>=20. && mHh <=2000.) {
//            SigmaTotSM_H13=ip_cs_ggtoH_13(mHh)+ip_cs_VBFtoH_13(mHh)+ip_cs_WtoWH_13(mHh)+ip_cs_ZtoZH_13(mHh)+ip_cs_pptottH_13(mHh)+ip_cs_pptobbH_13(mHh);
//    }
    SigmaSumphi3_13 = SigmaggF_phi3_13 + SigmaVBF_phi3_13 + SigmaVH_phi3_13 + SigmattF_phi3_13 + SigmabbF_phi3_13;

    
double BrSM_phi3tott=ip_Br_HPtott(m3);
double BrSM_phi3tocc=ip_Br_HPtocc(m3);
double BrSM_phi3tobb=ip_Br_HPtobb(m3);
double BrSM_phi3totautau=ip_Br_HPtotautau(m3);
double BrSM_phi3tomumu=ip_Br_HPtomumu(m3);
double BrSM_phi3toWW =ip_Br_HPtoWW(m3);
double BrSM_phi3toZZ =ip_Br_HPtoZZ(m3);

 Gammaphi3totSM=ip_GammaHPtotSM(m3);


/*Decay of phi3 to the others scalars*/
double lambda123 = lambdaijk(R11, R12, R13, R21, R22, R23, R31, R32, R33) + lambdaijk(R21, R22, R23, R11, R12, R13, R31, R32, R33)  + lambdaijk(R21, R22, R23, R31, R32, R33, R11, R12, R33)  + lambdaijk(R11, R12, R13, R31, R32, R33, R21, R22, R23) + lambdaijk(R31, R32,R33, R11, R12, R13, R21, R22, R23)  + lambdaijk(R31, R32,R33, R21, R22, R23, R11, R12, R13) ;
double lambda223 = lambdaijk(R21, R22, R23, R21, R22, R23, R31, R32, R33) + lambdaijk(R21, R22, R23, R31, R32, R33, R21, R22, R23) + lambdaijk(R31, R32, R33, R21, R22, R23, R21, R22, R23);
double lambda113 = lambdaijk(R11, R12, R13, R11, R12, R13, R31, R32, R33) + lambdaijk(R11, R12, R13, R31, R32, R33, R11, R12, R13) + lambdaijk(R31, R32, R33, R11, R12, R13, R11, R12, R13);
//phi3 -> phi1 phi2
double Gammaphi3_phi1phi2=HSTheta(m3 - (m1+m2))*KaellenFunction(m3_2,m1_2,m2_2)*lambda123*lambda123/(8.0*m3_2*M_PI);
// phi3 -> phi2 phi2
double Gammaphi3_phi2phi2=HSTheta(m3 - 2.0*m2)*sqrt(std::fabs(1.0 - (4.0*m2_2)/m3_2))*lambda223*lambda223/(32.0*m3*M_PI);
//phi3 -> phi1phi1
double Gammaphi3_phi1phi1=HSTheta(m3 - 2.0*m1)*sqrt(std::fabs(1.0 - (4.0*m1_2)/m3_2))*lambda113*lambda113/(32.0*m3*M_PI);
//phi3 ->H+H-
double Gammaphi3_HpHm=HSTheta(m3 - 2.0*sqrt(mHpsq))*sqrt(std::fabs(1.0 - (4.0*mHpsq)/m3_2))*lambdaphi3HpHm*lambdaphi3HpHm/(32.0*m3*M_PI);
//phi3 -> phi1 Z
double Gammaphi3_phi1Z=HSTheta(m3-(m1+MZ))*pow(KaellenFunction(m3_2,MZ*MZ,m1_2),3)*(R33*R12 + R32*R13)*(R33*R12 + R32*R13)/(2.0*M_PI*vev*vev);
//phi3 -> phi2 Z
double Gammaphi3_phi2Z=HSTheta(m3-(m2+MZ))*pow(KaellenFunction(m3_2,MZ*MZ,m2_2),3)*(R33*R22 + R32*R23)*(R33*R22 + R32*R23)/(2.0*M_PI*vev*vev);
/* phi3 -> H+W- */
double Gammaphi3_HpW=HSTheta(m3-sqrt(mHpsq)-MW)*pow(KaellenFunction(m3_2,MW*MW,mHpsq),3)*(R33-i*R32).abs2()/(M_PI*vev*vev);
                                                                              
 /*Gammaphi3tot= ((BrSM_phi3tott*rphi3_QtQt+BrSM_phi3tocc*rphi3_QcQc)+BrSM_phi3tobb*rphi3_QbQb+(BrSM_phi3totautau*rphi3_tautau+BrSM_phi3tomumu*rphi3_mumu)+(BrSM_phi3toWW+BrSM_phi3toZZ)*rphi3_VV)*Gammaphi3totSM+Gamma_phi3gaga+Gamma_phi3Zga+Gamma_phi3gg + Gammaphi3_phi1phi1+Gammaphi3_phi2phi2+Gammaphi3_phi1phi2+Gammaphi3_HpHm+Gammaphi3_phi1Z+Gammaphi3_phi2Z+Gammaphi3_HpW;*/


 Gammaphi3tot= (BrSM_phi3tott*(rphi3_QuQuE + rphi3_QuQuE/(beta(Mt, m3_2)*beta(Mt, m3_2)))
         +BrSM_phi3tocc*(rphi3_QuQuE + rphi3_QuQuE/(beta(Mc, m3_2)*beta(Mc, m3_2)))
         +BrSM_phi3tobb*(rphi3_QdQdE + rphi3_QdQdE/(beta(Mb, m3_2)*beta(Mb, m3_2)))
         +BrSM_phi3totautau*(rphi3_QlQlE + rphi3_QlQlE/(beta(Mtau, m3_2)*beta(Mtau, m3_2)))
         +(BrSM_phi3toWW+BrSM_phi3toZZ)*rphi3_VV)*Gammaphi3totSM+Gamma_phi3gaga+Gamma_phi3Zga+Gamma_phi3gg 
         + Gammaphi3_phi1phi1+Gammaphi3_phi2phi2+Gammaphi3_phi1phi2+Gammaphi3_HpHm+Gammaphi3_phi1Z+Gammaphi3_phi2Z
         +Gammaphi3_HpW;
 
 /*std::cout << " Gammaphi3tot  = " << Gammaphi3tot  << std::endl;
 std::cout << " BrSM_phi3tott*...  = " << BrSM_phi3tott*(rphi3_QuQuE + rphi3_QuQuE/(beta(Mc, m3_2)*beta(Mc, m3_2))) << std::endl;
 std::cout << " BrSM_phi3tocc*...  = " << BrSM_phi3tocc*(rphi3_QuQuE + rphi3_QuQuE/(beta(Mc, m3_2)*beta(Mc, m3_2))) << std::endl;
 std::cout << " BrSM_phi3tobb*...  = " << BrSM_phi3tobb*(rphi3_QdQdE + rphi3_QdQdE/(beta(Mb, m3_2)*beta(Mb, m3_2))) << std::endl;
 std::cout << " BrSM_phi3totautau*...  = " << BrSM_phi3totautau*(rphi3_QlQlE + rphi3_QlQlE/(beta(Mtau, m3_2)*beta(Mtau, m3_2))) << std::endl;
 std::cout << " BrSM_phi3toWW  = " << (BrSM_phi3toWW+BrSM_phi3toZZ)*rphi3_VV << std::endl;

 std::cout << " Gammaphi3totSM  = " << Gammaphi3totSM << std::endl;

 std::cout << " Gamma_phi3gaga  = " << Gamma_phi3gaga << std::endl;


 std::cout << " Gamma_phi3Zga  = " << Gamma_phi3Zga << std::endl;
 std::cout << " Gamma_phi3gg  = " << Gamma_phi3gg << std::endl;
 std::cout << " Gammaphi3_phi1phi1  = " << Gammaphi3_phi1phi1 << std::endl;


 std::cout << " Gammaphi3_phi2phi2  = " << Gammaphi3_phi2phi2 << std::endl;
 std::cout << " Gammaphi3_phi1phi2  = " << Gammaphi3_phi1phi2 << std::endl;
 std::cout << " Gammaphi3_HpHm  = " << Gammaphi3_HpHm << std::endl;
 std::cout << " Gammaphi3_phi1Z  = " << Gammaphi3_phi1Z << std::endl;
 
  std::cout << " Gammaphi3_phi2Z  = " << Gammaphi3_phi2Z << std::endl;
 std::cout << " Gammaphi3_HpW  = " << Gammaphi3_HpW << std::endl; */

 
/*
  Br_phi3tott=BrSM_phi3tott*rphi3_QtQt*Gammaphi3totSM/Gammaphi3tot;
 Br_phi3tobb=BrSM_phi3tobb*rphi3_QbQb*Gammaphi3totSM/Gammaphi3tot;
 Br_phi3totautau=BrSM_phi3totautau*rphi3_tautau*Gammaphi3totSM/Gammaphi3tot;
 */
      


 Br_phi3tott=BrSM_phi3tott*(rphi3_QuQuE + rphi3_QuQuE/(beta(Mt, m3_2)*beta(Mt, m3_2)))*Gammaphi3totSM/Gammaphi3tot;
 Br_phi3tobb=BrSM_phi3tobb*(rphi3_QdQdE + rphi3_QdQdE/(beta(Mb, m3_2)*beta(Mb, m3_2)))*Gammaphi3totSM/Gammaphi3tot;
 Br_phi3totautau=BrSM_phi3totautau*(rphi3_QlQlE + rphi3_QlQlE/(beta(Mtau, m3_2)*beta(Mtau, m3_2)))*Gammaphi3totSM/Gammaphi3tot;

 Br_phi3toWW=BrSM_phi3toWW*rphi3_VV*Gammaphi3totSM/Gammaphi3tot;
 Br_phi3toZZ=BrSM_phi3toZZ*rphi3_VV*Gammaphi3totSM/Gammaphi3tot;
 Br_phi3togaga=Gamma_phi3gaga/Gammaphi3tot;
 Br_phi3toZga=Gamma_phi3Zga/Gammaphi3tot;
 Br_phi3tophi1phi1=Gammaphi3_phi1phi1/Gammaphi3tot;
 Br_phi3tophi2phi2=Gammaphi3_phi2phi2/Gammaphi3tot;
 
 Br_phi3tophi1phi2=Gammaphi3_phi1phi2/Gammaphi3tot;
 Br_phi3toHpHm=Gammaphi3_HpHm/Gammaphi3tot;
 Br_phi3tophi1Z=Gammaphi3_phi1Z/Gammaphi3tot;
 Br_phi3tophi2Z=Gammaphi3_phi2Z/Gammaphi3tot;
 Br_phi3toHpW=Gammaphi3_HpW/Gammaphi3tot;
 

   
 return 0.;


}



//Higgs direct searches

double GeneralTHDMcache::ComputeMediumHiggs()
{
   
      
       //FLAG to select only the model in which all the couplings are the same (by families)
    
    if (!myGTHDM->getATHDMflag())
    {
        throw std::runtime_error("Direct Searches are only aviable in the A2HDM.");
    }
  
        /*complex i */
    
     gslpp::complex i = gslpp::complex::i();
     
   
    
    
    /*up, down and leptonic couplings */
    gslpp::complex su = myGTHDM->getNu_33();
    gslpp::complex sd = myGTHDM->getNd_33();
    gslpp::complex sl = myGTHDM->getNl_33();

    
    double m1_2 = 0.0;
    double m2_2 = 0.0;
    double m3_2 = 0.0;
    double R11 = 0.0;
    double R12 = 0.0;
    double R13 = 0.0;
    double R21 = 0.0;
    double R22 = 0.0;
    double R23 = 0.0;
    double R31 = 0.0;
    double R32 = 0.0;
    double R33 = 0.0;
        
    //If to always set 1 as the SM Higgs and 3 as the heaviest
    if(mH1sq == mHl*mHl )
    {
         m1_2 = mH1sq;
          
         R11 = R11_GTHDM;
         R12 = R12_GTHDM;
         R13 = R13_GTHDM;
         
        if(mH2sq<mH3sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH3sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;
        }
         else if(mH3sq<mH2sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH2sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;
        }
    }
    else if(mH2sq == mHl*mHl )
    {
         m1_2 = mH2sq;
         R11 = R21_GTHDM;
         R12 = R22_GTHDM;
         R13 = R23_GTHDM;
         
         if(mH1sq<mH3sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH3sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;

        }
         else if(mH3sq<mH1sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH1sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
  
    }
    else if(mH3sq == mHl*mHl )
    {
         m1_2 = mH3sq;

         R11 = R31_GTHDM;
         R12 = R32_GTHDM;
         R13 = R33_GTHDM;
         
          if(mH1sq<mH2sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH2sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;

        }
         else if(mH2sq<mH1sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH1sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
        }
         
    }
    
     if (m1_2 < 0 || m2_2 < 0 || m3_2 < 0) 
                return std::numeric_limits<double>::quiet_NaN();
    
    double m1 = sqrt(m1_2);
    double m2 = sqrt(m2_2);
    double m3 = sqrt(m3_2);
      
    double Br_Ztoee=0.03363; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Ztomumu=0.03366; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Ztotautau=0.0337; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Ztoinv=0.2; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Wtoenu=0.1071; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Wtomunu=0.1063; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Wtotaunu=0.1138; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    

    
   //Theoretical expressions for the Heavy Higgs (phi2) cross sections times branching ratios at 8 TeV

    ggF_phi2_tautau_TH8=SigmaggF_phi2_8*Br_phi2totautau;
    bbF_phi2_tautau_TH8=SigmabbF_phi2_8*Br_phi2totautau;
    pp_phi2_gaga_TH8=SigmaSumphi2_8*Br_phi2togaga;
    ggF_phi2_gaga_TH8=SigmaggF_phi2_8*Br_phi2togaga;
    pp_phi2_Zga_llga_TH8=SigmaSumphi2_8*Br_phi2toZga*(Br_Ztoee+Br_Ztomumu);
    mu_pp_phi2_VV_TH8=SigmaSumphi2_8/SigmaTotSM_phi2_8*rphi3_VV*Gammaphi2totSM/Gammaphi2tot;
        
    ggF_phi2_ZZ_TH8=SigmaggF_phi2_8*Br_phi2toZZ;
    VBF_phi2_ZZ_TH8=SigmaVBF_phi2_8*Br_phi2toZZ;
    ggF_phi2_WW_TH8=SigmaggF_phi2_8*Br_phi2toWW;
    VBF_phi2_WW_TH8=SigmaVBF_phi2_8*Br_phi2toWW;
    ggF_phi2_phi1phi1_TH8=SigmaggF_phi2_8*Br_phi2tophi1phi1;
    pp_phi2_phi1phi1_TH8=SigmaSumphi2_8*Br_phi2tophi1phi1;
    
    ggF_phi2_phi1phi1_bbtautau_TH8=SigmaggF_phi2_8*Br_phi2tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_tautau*2.0;
    pp_phi2_phi1phi1_bbbb_TH8=SigmaSumphi2_8*Br_phi2tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_bb;
    pp_phi2_phi1phi1_gagabb_TH8=SigmaSumphi2_8*Br_phi2tophi1phi1*GTHDM_BR_h_gaga*GTHDM_BR_h_bb*2.0;
     
    ggF_phi2_tt_TH8=SigmaggF_phi2_8*Br_phi2tott;
    bbF_phi2_bb_TH8=SigmabbF_phi2_8*Br_phi2tobb;
    
    pp_phi2_phi1Z_bbll_TH8=SigmaSumphi2_8*Br_phi2tophi1Z*GTHDM_BR_h_bb*(Br_Ztoee+Br_Ztomumu);
    pp_phi2_phi1Z_tautaull_TH8=SigmaSumphi2_8*Br_phi2tophi1Z*GTHDM_BR_h_tautau*(Br_Ztoee+Br_Ztomumu);
    


       
THoEX_ggF_phi2_tautau_ATLAS8 = 0.0;
R_ggF_phi2_tautau_ATLAS8 = 0.0;
THoEX_ggF_phi2_tautau_CMS8 = 0.0;
R_ggF_phi2_tautau_CMS8 = 0.0;
THoEX_bbF_phi2_tautau_ATLAS8 = 0.0;
R_bbF_phi2_tautau_ATLAS8 = 0.0;
THoEX_bbF_phi2_tautau_CMS8 = 0.0;
R_bbF_phi2_tautau_CMS8 = 0.0;
THoEX_pp_phi2_gaga_ATLAS8 = 0.0;
R_pp_phi2_gaga_ATLAS8 = 0.0;
THoEX_ggF_phi2_gaga_CMS8 = 0.0;
R_ggF_phi2_gaga_CMS8 = 0.0;
THoEX_pp_phi2_Zga_llga_ATLAS8 = 0.0;
R_pp_phi2_Zga_llga_ATLAS8 = 0.0;
THoEX_pp_phi2_Zga_llga_CMS8 = 0.0;
R_pp_phi2_Zga_llga_CMS8 = 0.0;
THoEX_mu_pp_phi2_VV_CMS8 = 0.0;
R_mu_pp_phi2_VV_CMS8 = 0.0;
THoEX_ggF_phi2_ZZ_ATLAS8 = 0.0;
R_ggF_phi2_ZZ_ATLAS8 = 0.0;
THoEX_VBF_phi2_ZZ_ATLAS8 = 0.0;
 R_VBF_phi2_ZZ_ATLAS8 = 0.0;
THoEX_ggF_phi2_WW_ATLAS8 = 0.0;
R_ggF_phi2_WW_ATLAS8 = 0.0;
THoEX_VBF_phi2_WW_ATLAS8 = 0.0;
R_VBF_phi2_WW_ATLAS8 = 0.0;
THoEX_ggF_phi2_phi1phi1_ATLAS8 = 0.0;
R_VBF_phi2_WW_ATLAS8 = 0.0;
R_ggF_phi2_phi1phi1_ATLAS8 = 0.0;
THoEX_pp_phi2_phi1phi1_CMS8 = 0.0;


R_pp_phi2_phi1phi1_CMS8 = 0.0;
THoEX_ggF_phi2_phi1phi1_bbtautau_CMS8 = 0.0;
R_ggF_phi2_phi1phi1_bbtautau_CMS8 = 0.0;
THoEX_pp_phi2_phi1phi1_bbbb_CMS8 = 0.0;
R_pp_phi2_phi1phi1_bbbb_CMS8 = 0.0;
THoEX_pp_phi2_phi1phi1_gagabb_CMS8 = 0.0;
R_pp_phi2_phi1phi1_gagabb_CMS8 = 0.0;


THoEX_ggF_phi2_tt_ATLAS8 = 0.0;
R_ggF_phi2_tt_ATLAS8 = 0.0;
THoEX_bbF_phi2_bb_CMS8 = 0.0;
R_bbF_phi2_bb_CMS8 = 0.0;
//THoEX_pp_H_AZ_bbll_CMS8 = 0.0;
//R_pp_H_AZ_bbll_CMS8 = 0.0;
//THoEX_pp_H_AZ_tautaull_CMS8 = 0.0;
//R_pp_H_AZ_tautaull_CMS8 = 0.0;



   //Theoretical expressions for the Heavy Higgs cross sections times branching ratios at 13 TeV

    ggF_phi2_tautau_TH13=SigmaggF_phi2_13*Br_phi2totautau;
    bbF_phi2_tautau_TH13=SigmabbF_phi2_13*Br_phi2totautau;
    pp_phi2_gaga_TH13=SigmaSumphi2_13*Br_phi2togaga;
    ggF_phi2_gaga_TH13=SigmaggF_phi2_13*Br_phi2togaga;
    pp_phi2_Zga_TH13=SigmaSumphi2_13*Br_phi2toZga;
    ggF_phi2_Zga_TH13=SigmaggF_phi2_13*Br_phi2toZga;
    pp_phi2_ZZ_TH13=SigmaSumphi2_13*Br_phi2toZZ;
    ggF_phi2_ZZ_TH13=SigmaggF_phi2_13*Br_phi2toZZ;
    VBF_phi2_ZZ_TH13=SigmaVBF_phi2_13*Br_phi2toZZ;
    
    
    ggF_phi2_ZZ_llll_TH13=SigmaggF_phi2_13*Br_phi2toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    VBF_phi2_ZZ_llll_TH13=SigmaVBF_phi2_13*Br_phi2toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    pp_phi2_ZZ_llll_TH13=SigmaSumphi2_13*Br_phi2toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    VBF_VH_phi2_ZZ_llll_TH13=(SigmaVBF_phi2_13+SigmaVH_phi2_13)*Br_phi2toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    ggF_phi2_WW_TH13=SigmaggF_phi2_13*Br_phi2toWW;
    VBF_phi2_WW_TH13=SigmaVBF_phi2_13*Br_phi2toWW;
    ggF_VBF_phi2_WW_lnulnu_TH13=(SigmaggF_phi2_13+SigmaVBF_phi2_13)*Br_phi2toWW*(Br_Wtoenu+Br_Wtomunu)*(Br_Wtoenu+Br_Wtomunu);
    pp_phi2_VV_TH13=SigmaSumphi2_13*(Br_phi2toZZ+Br_phi2toWW);
    ggF_phi2_phi1phi1_TH13=SigmaggF_phi2_13*Br_phi2tophi1phi1;
    
    pp_phi2_phi1phi1_TH13=SigmaSumphi2_13*Br_phi2tophi1phi1;
;


    
    pp_phi2_phi1phi1_bbbb_TH13=SigmaSumphi2_13*Br_phi2tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_bb;
    ggF_phi2_phi1phi1_bbbb_TH13=SigmaggF_phi2_13*Br_phi2tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_bb;
    pp_phi2_phi1phi1_gagabb_TH13=SigmaSumphi2_13*Br_phi2tophi1phi1*GTHDM_BR_h_gaga*GTHDM_BR_h_bb*2.0;
    pp_phi2_phi1phi1_bbtautau_TH13=SigmaSumphi2_13*Br_phi2tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_tautau*2.0;
    pp_phi2_phi1phi1_bblnulnu_TH13=SigmaSumphi2_13*Br_phi2tophi1phi1*5.77e-1*2.15e-1*(Br_Wtoenu+Br_Wtomunu)*(Br_Wtoenu+Br_Wtomunu)*2.0;/*SM BR assumed in the CMS analysis!*/
    pp_phi2_phi1phi1_bbVV_TH13=SigmaSumphi2_13*Br_phi2tophi1phi1*2.0*GTHDM_BR_h_bb*(GTHDM_BR_h_WW*pow(Br_Wtoenu+Br_Wtomunu+Br_Wtotaunu*0.352,2)
                                                            +GTHDM_BR_h_ZZ*2.0*Br_Ztoinv*(Br_Ztoee+Br_Ztomumu+Br_Ztotautau*0.124));
   
            
            
            
    ttF_phi2_tt_TH13=SigmattF_phi2_13*Br_phi2tott;
    bbF_phi2_tt_TH13=SigmabbF_phi2_13*Br_phi2tott;
    pp_phi2_bb_TH13=SigmaSumphi2_13*Br_phi2tobb;
    
    

    //95% to 1 sigma conversion factor, roughly sqrt(3.84)
    double nftos=1.95996398454;

/*Ara aquests talls sempre se complixen en certes condicions m1 = 125, per lo que sempre entra dins del if 
 * i com m3> m2, m2>= 50 sempre es complix */  
  
    if(m2>=65.0 && m2<90.0)
    {

        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
    }
    else if(m2>=90.0 && m2<100.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        if(m1>=50.0 && m1<=1000.0)
        {

            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }     
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
    }
     else if(m2>=100.0 && m2<130.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;    
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
 
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=130.0 && m2<140.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=140.0 && m2<145.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }

        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=145.0 && m2<150.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=150.0 && m2<175.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=175.0 && m2<200.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
       if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=200.0 && m2<220.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=220.0 && m2<250.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=250.0 && m2<260.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=(ggF_phi2_gaga_TH8+ip_ex_gg_phi_gaga_CMS8_e(m2)-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }

        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;        
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;       
        }
    else if(m2>=260.0 && m2<270.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbtautau_CMS8=ggF_phi2_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m2);
        R_ggF_phi2_phi1phi1_bbtautau_CMS8=(1+(ggF_phi2_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m2))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;        
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_gagaWW_ATLAS13=ggF_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m2);
        R_ggF_phi2_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m2))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;   
    }
    else if(m2>=270.0 && m2<275.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbtautau_CMS8=ggF_phi2_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m2);
        R_ggF_phi2_phi1phi1_bbtautau_CMS8=(1+(ggF_phi2_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m2))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;   
       THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;        
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_gagaWW_ATLAS13=ggF_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m2);
        R_ggF_phi2_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m2))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
       }
    else if(m2>=275.0 && m2<300.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;   
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbtautau_CMS8=ggF_phi2_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m2);
        R_ggF_phi2_phi1phi1_bbtautau_CMS8=(1+(ggF_phi2_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m2))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;     
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos; 
        THoEX_pp_phi2_phi1phi1_bbgaga_ATLAS13=pp_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_ATLAS13=(1+(pp_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m2))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_gagaWW_ATLAS13=ggF_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m2);
        R_ggF_phi2_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m2))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=300.0 && m2<350.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;     
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbtautau_CMS8=ggF_phi2_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m2);
        R_ggF_phi2_phi1phi1_bbtautau_CMS8=(1+(ggF_phi2_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m2))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_ATLAS13=pp_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_ATLAS13=(1+(pp_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m2))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_gagaWW_ATLAS13=ggF_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m2);
        R_ggF_phi2_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m2))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
    }
        else if(m2>=350.0 && m2<400.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;     
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;      
        THoEX_pp_phi2_phi1phi1_bbgaga_ATLAS13=pp_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_ATLAS13=(1+(pp_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m2))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_gagaWW_ATLAS13=ggF_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m2);
        R_ggF_phi2_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m2))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
        }
    else if(m2>=400.0 && m2<500.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;     
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos; 
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_gagaWW_ATLAS13=ggF_phi2_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m2);
        R_ggF_phi2_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi2_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m2))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=500.0 && m2<550.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos; 
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;  
    }
    else if(m2>=550.0 && m2<600.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS8=pp_phi2_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m2);
        R_pp_phi2_gaga_ATLAS8=(1+(pp_phi2_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m2))/ip_ex_pp_phi_gaga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;    
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_CMS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m2);
        R_ggF_phi2_ZZ_llnunu_CMS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m2))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llnunu_CMS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m2);
        R_VBF_phi2_ZZ_llnunu_CMS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m2))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos; 
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=600.0 && m2<650.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=650.0 && m2<760.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m2))/ip_ex_gg_phi_gaga_CMS8_e(m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m2)-ip_ex_gg_phi_gaga_CMS8_e(m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m2)-ip_ex_gg_phi_gaga_CMS8_em2(m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos; 
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
         if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos; 
    }
     else if( m2>=760.0 &&  m2<850.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8( m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8( m2))/ip_ex_gg_phi_tautau_ATLAS8_e( m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8( m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8( m2))/ip_ex_gg_phi_tautau_CMS8_e( m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8( m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8( m2))/ip_ex_bb_phi_tautau_ATLAS8_e( m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8( m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8( m2))/ip_ex_bb_phi_tautau_CMS8_e( m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS8=ggF_phi2_gaga_TH8/ip_ex_gg_phi_gaga_CMS8( m2);
        R_ggF_phi2_gaga_CMS8=(1+(ggF_phi2_gaga_TH8-ip_ex_gg_phi_gaga_CMS8( m2))/ip_ex_gg_phi_gaga_CMS8_e( m2) ) * nftos;
//    LIMIT_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8( m2);
//    LIMEST_ggF_phi2_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8( m2)-ip_ex_gg_phi_gaga_CMS8_e( m2);
//    BANDSIZE_ggF_phi2_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2( m2)-ip_ex_gg_phi_gaga_CMS8_em2( m2);
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8( m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8( m2))/ip_ex_pp_A_Zga_llga_CMS8_e( m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8( m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8( m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e( m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8( m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8( m2))/ip_ex_gg_H_ZZ_ATLAS8_e( m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8( m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8( m2))/ip_ex_VBF_H_ZZ_ATLAS8_e( m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8( m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8( m2))/ip_ex_mu_pp_H_VV_CMS8_e( m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8( m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8( m2))/ip_ex_gg_H_WW_ATLAS8_e( m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8( m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8( m2))/ip_ex_VBF_H_WW_ATLAS8_e( m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8( m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8( m2))/ip_ex_gg_H_hh_ATLAS8_e( m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8( m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8( m2))/ip_ex_pp_H_hh_CMS8_e( m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8( m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8( m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e( m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8( m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8( m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e( m2) ) * nftos;
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8( m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8( m2))/ip_ex_gg_phi_tt_ATLAS8_e( m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8( m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8( m2))/ip_ex_bb_phi_bb_CMS8_e( m2) ) * nftos;
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1, m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1, m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1, m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1, m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1, m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
     }
    else if(m2>=850.0 && m2<900.0)
    {
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_bb_CMS8=bbF_phi2_bb_TH8/ip_ex_bb_phi_bb_CMS8(m2);
        R_bbF_phi2_bb_CMS8=(1+(bbF_phi2_bb_TH8-ip_ex_bb_phi_bb_CMS8(m2))/ip_ex_bb_phi_bb_CMS8_e(m2) ) * nftos;
       
        if(m1>=40.0 && m1<=910.0)
        {
        THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
 
        R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {

            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;               
          }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbgaga_CMS13=pp_phi2_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbgaga_CMS13=(1+(pp_phi2_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m2))/ip_ex_pp_H_hh_gagabb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m2))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbtautau1_CMS13=pp_phi2_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m2);
        R_pp_phi2_phi1phi1_bbtautau1_CMS13=(1+(pp_phi2_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m2))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bblnulnu_CMS13=pp_phi2_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m2);
        R_pp_phi2_phi1phi1_bblnulnu_CMS13=(1+(pp_phi2_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m2))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbVV_CMS13=pp_phi2_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m2);
        R_pp_phi2_phi1phi1_bbVV_CMS13=(1+(pp_phi2_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m2))/ip_ex_pp_H_hh_bbVV_CMS13_e(m2) ) * nftos;
   }
    else if(m2>=900.0 && m2<1000.0)
    {     
        THoEX_ggF_phi2_tautau_ATLAS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m2);
        R_ggF_phi2_tautau_ATLAS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m2))/ip_ex_gg_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS8=ggF_phi2_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m2);
        R_ggF_phi2_tautau_CMS8=(1+(ggF_phi2_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m2))/ip_ex_gg_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m2);
        R_bbF_phi2_tautau_ATLAS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m2))/ip_ex_bb_phi_tautau_ATLAS8_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS8=bbF_phi2_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m2);
        R_bbF_phi2_tautau_CMS8=(1+(bbF_phi2_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m2))/ip_ex_bb_phi_tautau_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_ATLAS8=ggF_phi2_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m2);
        R_ggF_phi2_ZZ_ATLAS8=(1+(ggF_phi2_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m2))/ip_ex_gg_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_ATLAS8=VBF_phi2_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m2);
        R_VBF_phi2_ZZ_ATLAS8=(1+(VBF_phi2_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m2))/ip_ex_VBF_H_ZZ_ATLAS8_e(m2) ) * nftos;
        THoEX_mu_pp_phi2_VV_CMS8=mu_pp_phi2_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m2);
        R_mu_pp_phi2_VV_CMS8=(1+(mu_pp_phi2_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m2))/ip_ex_mu_pp_H_VV_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_ATLAS8=ggF_phi2_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m2);
        R_ggF_phi2_phi1phi1_ATLAS8=(1+(ggF_phi2_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m2))/ip_ex_gg_H_hh_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_CMS8=pp_phi2_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m2);
        R_pp_phi2_phi1phi1_CMS8=(1+(pp_phi2_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m2))/ip_ex_pp_H_hh_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;       
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi2_phi1Z_bbll_CMS8=pp_phi2_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2);
            R_pp_phi2_phi1Z_bbll_CMS8=(1+(pp_phi2_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m2))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m2) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi2_phi1Z_tautaull_CMS8=pp_phi2_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2);
            R_pp_phi2_phi1Z_tautaull_CMS8=(1+(pp_phi2_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m2) ) * nftos;
        }
        THoEX_ttF_phi2_tt_ATLAS13=ttF_phi2_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m2);
        R_ttF_phi2_tt_ATLAS13=(1+(ttF_phi2_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m2))/ip_ex_tt_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tt_ATLAS13=bbF_phi2_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m2);
        R_bbF_phi2_tt_ATLAS13=(1+(bbF_phi2_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m2))/ip_ex_bb_phi_tt_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llll_ATLAS13=ggF_phi2_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m2);
        R_ggF_phi2_ZZ_llll_ATLAS13=(1+(ggF_phi2_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m2))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llll_ATLAS13=VBF_phi2_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m2);
        R_VBF_phi2_ZZ_llll_ATLAS13=(1+(VBF_phi2_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_VBF_phi2_WW_lnulnu_CMS13=ggF_VBF_phi2_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m2);
        R_ggF_VBF_phi2_WW_lnulnu_CMS13=(1+(ggF_VBF_phi2_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m2))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=1000.0 && m2<1100.0)
    {
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS8=pp_phi2_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS8=(1+(pp_phi2_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m2))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_gagabb_CMS8=pp_phi2_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m2);
        R_pp_phi2_phi1phi1_gagabb_CMS8=(1+(pp_phi2_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m2))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=1100.0 && m2<1200.0)
    {
        THoEX_pp_phi2_Zga_llga_CMS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m2);
        R_pp_phi2_Zga_llga_CMS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m2))/ip_ex_pp_A_Zga_llga_CMS8_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_pp_phi2_bb_CMS13=pp_phi2_bb_TH13/ip_ex_pp_phi_bb_CMS13(m2);
        R_pp_phi2_bb_CMS13=(1+(pp_phi2_bb_TH13-ip_ex_pp_phi_bb_CMS13(m2))/ip_ex_pp_phi_bb_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_llllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_llllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_CMS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m2);
        R_pp_phi2_phi1phi1_bbbb_CMS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m2))/ip_ex_pp_H_hh_bbbb_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=1200.0 && m2<1500.0)
    {
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_ATLAS8=ggF_phi2_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m2);
        R_ggF_phi2_WW_ATLAS8=(1+(ggF_phi2_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m2))/ip_ex_gg_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_ATLAS8=VBF_phi2_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m2);
        R_VBF_phi2_WW_ATLAS8=(1+(VBF_phi2_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m2))/ip_ex_VBF_H_WW_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;
    }
     else if(m2>=1500.0 && m2<1600.0)
    {
        THoEX_pp_phi2_Zga_llga_ATLAS8=pp_phi2_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m2);
        R_pp_phi2_Zga_llga_ATLAS8=(1+(pp_phi2_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m2))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;       
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;     
    }
    else if(m2>=1600.0 && m2<2000.0)
    {
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_llga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m2);
        R_pp_phi2_Zga_llga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m2))/ip_ex_pp_phi_Zga_llga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llqq_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m2);
        R_pp_phi2_ZZ_llqq_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m2))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;       
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;
  }
    else if(m2>=2000.0 && m2<2250.0)
    {
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_ATLAS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m2);
        R_ggF_phi2_tautau_ATLAS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m2))/ip_ex_gg_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_ATLAS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m2);
        R_bbF_phi2_tautau_ATLAS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m2))/ip_ex_bb_phi_tautau_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;
     }
    else if(m2>=2250.0 && m2<2400.0)
    {
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_ATLAS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m2);
        R_pp_phi2_Zga_ATLAS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m2))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;
         THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;
      }
    else if(m2>=2400.0 && m2<2500.0)
    {
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_llga_ATLAS13=ggF_phi2_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m2);
        R_ggF_phi2_Zga_llga_ATLAS13=(1+(ggF_phi2_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m2))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llnunu_CMS13=pp_phi2_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m2);
        R_pp_phi2_ZZ_llnunu_CMS13=(1+(pp_phi2_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m2))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;
    }
    else if(m2>=2500.0 && m2<2530.0)
    {
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_ZZ_llll_CMS13=pp_phi2_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m2);
        R_pp_phi2_ZZ_llll_CMS13=(1+(pp_phi2_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m2))/ip_ex_pp_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_VBF_VH_phi2_ZZ_llll_CMS13=VBF_VH_phi2_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2);
        R_VBF_VH_phi2_ZZ_llll_CMS13=(1+(VBF_VH_phi2_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m2))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;
     }
    else if(m2>=2530.0 && m2<2700.0)
    {
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_gaga_ATLAS13=pp_phi2_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m2);
        R_pp_phi2_gaga_ATLAS13=(1+(pp_phi2_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m2))/ip_ex_pp_phi_gaga_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos; 
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos; 
      }
    else if(m2>=2700.0 && m2<3000.0)
    {
        THoEX_ggF_phi2_tt_ATLAS8=ggF_phi2_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m2);
        R_ggF_phi2_tt_ATLAS8=(1+(ggF_phi2_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m2))/ip_ex_gg_phi_tt_ATLAS8_e(m2) ) * nftos;
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_pp_phi2_Zga_qqga_CMS13=pp_phi2_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m2);
        R_pp_phi2_Zga_qqga_CMS13=(1+(pp_phi2_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m2))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_qqllnunu_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2);
        R_ggF_phi2_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_qqllnunu_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2);
        R_VBF_phi2_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m2))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_llqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_llqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_ZZ_llqq_ATLAS13=VBF_phi2_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2);
        R_VBF_phi2_ZZ_llqq_ATLAS13=(1+(VBF_phi2_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m2))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_ZZ_nunuqq_ATLAS13=ggF_phi2_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2);
        R_ggF_phi2_ZZ_nunuqq_ATLAS13=(1+(ggF_phi2_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m2))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_lnuqq_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m2);
        R_ggF_phi2_WW_lnuqq_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m2))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_lnuqq_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2);
        R_VBF_phi2_WW_lnuqq_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m2))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_VBF_phi2_WW_enumunu_ATLAS13=VBF_phi2_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m2);
        R_VBF_phi2_WW_enumunu_ATLAS13=(1+(VBF_phi2_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m2))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_VV_qqqq_ATLAS13=pp_phi2_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m2);
        R_pp_phi2_VV_qqqq_ATLAS13=(1+(pp_phi2_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m2))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m2) ) * nftos;
        THoEX_pp_phi2_phi1phi1_bbbb_ATLAS13=pp_phi2_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m2);
        R_pp_phi2_phi1phi1_bbbb_ATLAS13=(1+(pp_phi2_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m2))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_phi1phi1_bbbb_CMS13=ggF_phi2_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m2);
        R_ggF_phi2_phi1phi1_bbbb_CMS13=(1+(ggF_phi2_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m2))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m2) ) * nftos;
    }
       else if(m2>=3000.0 && m2<3200.0)
    {
        THoEX_ggF_phi2_tautau_CMS13=ggF_phi2_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m2);
        R_ggF_phi2_tautau_CMS13=(1+(ggF_phi2_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m2))/ip_ex_gg_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_bbF_phi2_tautau_CMS13=bbF_phi2_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m2);
        R_bbF_phi2_tautau_CMS13=(1+(bbF_phi2_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m2))/ip_ex_bb_phi_tautau_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m2) ) * nftos;
    }      
    else if(m2>=3200.0 && m2<4000.0)
    {
        THoEX_ggF_phi2_gaga_CMS13=ggF_phi2_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m2);
        R_ggF_phi2_gaga_CMS13=(1+(ggF_phi2_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m2))/ip_ex_gg_phi_gaga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_Zga_CMS13=ggF_phi2_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m2);
        R_ggF_phi2_Zga_CMS13=(1+(ggF_phi2_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m2))/ip_ex_ggF_phi_Zga_CMS13_e(m2) ) * nftos;
        THoEX_ggF_phi2_WW_enumunu_ATLAS13=ggF_phi2_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m2);
        R_ggF_phi2_WW_enumunu_ATLAS13=(1+(ggF_phi2_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m2))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
    }      
    return 0.;

}


//Higgs direct searches

double GeneralTHDMcache::ComputeHeavyHiggs()
{
           //FLAG to select only the model in which all the couplings are the same (by families)
    

   
    if (!myGTHDM->getATHDMflag())
    {
        throw std::runtime_error("Direct Searches are only aviable in the A2HDM.");
    }
  
        /*complex i */
    
     gslpp::complex i = gslpp::complex::i();
     
   
    
    
    /*up, down and leptonic couplings */
    gslpp::complex su = myGTHDM->getNu_33();
    gslpp::complex sd = myGTHDM->getNd_33();
    gslpp::complex sl = myGTHDM->getNl_33();

    
    double m1_2 = 0.0;
    double m2_2 = 0.0;
    double m3_2 = 0.0;
    double R11 = 0.0;
    double R12 = 0.0;
    double R13 = 0.0;
    double R21 = 0.0;
    double R22 = 0.0;
    double R23 = 0.0;
    double R31 = 0.0;
    double R32 = 0.0;
    double R33 = 0.0;
     
     
    //If to always set 1 as the SM Higgs and 3 as the heaviest
    if(mH1sq == mHl*mHl )
    {
         m1_2 = mH1sq;
          
         R11 = R11_GTHDM;
         R12 = R12_GTHDM;
         R13 = R13_GTHDM;
         
        if(mH2sq<mH3sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH3sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;
        }
         else if(mH3sq<mH2sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH2sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;
        }
    }
    else if(mH2sq == mHl*mHl )
    {
         m1_2 = mH2sq;
         R11 = R21_GTHDM;
         R12 = R22_GTHDM;
         R13 = R23_GTHDM;
         
         if(mH1sq<mH3sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH3sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R31_GTHDM;
            R32 = R32_GTHDM;
            R33 = R33_GTHDM;
            
        }
         else if(mH3sq<mH1sq)
        {   
            m2_2 = mH3sq;
            m3_2 = mH1sq;
            R21 = R31_GTHDM;
            R22 = R32_GTHDM;
            R23 = R33_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
            
        }
  
    }
    else if(mH3sq == mHl*mHl )
    {
         m1_2 = mH3sq;

         R11 = R31_GTHDM;
         R12 = R32_GTHDM;
         R13 = R33_GTHDM;
         
          if(mH1sq<mH2sq)
        {   
            m2_2 = mH1sq;
            m3_2 = mH2sq;
            R21 = R11_GTHDM;
            R22 = R12_GTHDM;
            R23 = R13_GTHDM;
            R31 = R21_GTHDM;
            R32 = R22_GTHDM;
            R33 = R23_GTHDM;       
        }
         else if(mH2sq<mH1sq)
        {   
            m2_2 = mH2sq;
            m3_2 = mH1sq;
            R21 = R21_GTHDM;
            R22 = R22_GTHDM;
            R23 = R23_GTHDM;
            R31 = R11_GTHDM;
            R32 = R12_GTHDM;
            R33 = R13_GTHDM;
         }
         
    }

      if (m1_2 < 0 || m2_2 < 0 || m3_2 < 0) 
                return std::numeric_limits<double>::quiet_NaN();
    
    double m1 = sqrt(m1_2);
    double m2 = sqrt(m2_2);
    double m3 = sqrt(m3_2);

    
    double Br_Ztoee=0.03363; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Ztomumu=0.03366; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Ztotautau=0.0337; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Ztoinv=0.2; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Wtoenu=0.1071; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Wtomunu=0.1063; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    double Br_Wtotaunu=0.1138; //C. Patrignani et al.(Particle Data Group), Chin. Phys. C, 40, 100001 (2016)
    
  
    
    ggF_phi3_tautau_TH8=SigmaggF_phi3_8*Br_phi3totautau;
    bbF_phi3_tautau_TH8=SigmabbF_phi3_8*Br_phi3totautau;
    pp_phi3_gaga_TH8=SigmaSumphi3_8*Br_phi3togaga;
    ggF_phi3_gaga_TH8=SigmaggF_phi3_8*Br_phi3togaga;
    pp_phi3_Zga_llga_TH8=SigmaSumphi3_8*Br_phi3toZga*(Br_Ztoee+Br_Ztomumu);
    mu_pp_phi3_VV_TH8=SigmaSumphi3_8/SigmaTotSM_phi3_8*rphi3_VV*Gammaphi3totSM/Gammaphi3tot;
    
   /* std::cout << "mu_pp_phi3_VV_TH8 = " << mu_pp_phi3_VV_TH8 << std::endl;
    std::cout << "SigmaSumphi3_8 = " << SigmaSumphi3_8 << std::endl;
    std::cout << "SigmaTotSM_phi3_8 = " << SigmaTotSM_phi3_8 << std::endl;
    std::cout << "Gammaphi3totSM = " << Gammaphi3totSM << std::endl;
        std::cout << "Gammaphi3tot = " << Gammaphi3tot << std::endl;*/




    
    
    ggF_phi3_ZZ_TH8=SigmaggF_phi3_8*Br_phi3toZZ;
    VBF_phi3_ZZ_TH8=SigmaVBF_phi3_8*Br_phi3toZZ;
    ggF_phi3_WW_TH8=SigmaggF_phi3_8*Br_phi3toWW;
    VBF_phi3_WW_TH8=SigmaVBF_phi3_8*Br_phi3toWW;
    ggF_phi3_phi1phi1_TH8=SigmaggF_phi3_8*Br_phi3tophi1phi1;
    ggF_phi3_phi2phi2_TH8=SigmaggF_phi3_8*Br_phi3tophi2phi2;
    ggF_phi3_phi1phi2_TH8=SigmaggF_phi3_8*Br_phi3tophi1phi2;
    pp_phi3_phi1phi1_TH8=SigmaSumphi3_8*Br_phi3tophi1phi1;
    pp_phi3_phi2phi2_TH8=SigmaSumphi3_8*Br_phi3tophi2phi2;   
    pp_phi3_phi1phi2_TH8=SigmaSumphi3_8*Br_phi3tophi1phi2;
    
    ggF_phi3_phi1phi1_bbtautau_TH8=SigmaggF_phi3_8*Br_phi3tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_tautau*2.0;
    pp_phi3_phi1phi1_bbbb_TH8=SigmaSumphi3_8*Br_phi3tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_bb;
    pp_phi3_phi1phi1_gagabb_TH8=SigmaSumphi3_8*Br_phi3tophi1phi1*GTHDM_BR_h_gaga*GTHDM_BR_h_bb*2.0;
   
    ggF_phi3_phi2phi2_bbtautau_TH8=SigmaggF_phi3_8*Br_phi3tophi2phi2*Br_phi2tobb*Br_phi2totautau*2.0;
   
    pp_phi3_phi2phi2_bbbb_TH8=SigmaSumphi3_8*Br_phi3tophi2phi2*Br_phi2tobb*Br_phi2tobb;
    pp_phi3_phi2phi2_gagabb_TH8=SigmaSumphi3_8*Br_phi3tophi2phi2*Br_phi2togaga*Br_phi2tobb*2.0;
    ggF_phi3_tt_TH8=SigmaggF_phi3_8*Br_phi3tott;
    bbF_phi3_bb_TH8=SigmabbF_phi3_8*Br_phi3tobb;
    
    pp_phi3_phi1Z_bbll_TH8=SigmaSumphi3_8*Br_phi3tophi1Z*GTHDM_BR_h_bb*(Br_Ztoee+Br_Ztomumu);
    pp_phi3_phi2Z_bbll_TH8=SigmaSumphi3_8*Br_phi3tophi2Z*Br_phi2tobb*(Br_Ztoee+Br_Ztomumu);
    pp_phi3_phi1Z_tautaull_TH8=SigmaSumphi3_8*Br_phi3tophi1Z*GTHDM_BR_h_tautau*(Br_Ztoee+Br_Ztomumu);
    pp_phi3_phi2Z_tautaull_TH8=SigmaSumphi3_8*Br_phi3tophi2Z*Br_phi2totautau*(Br_Ztoee+Br_Ztomumu);
    
    
THoEX_ggF_phi3_tautau_ATLAS8 = 0.0;
R_ggF_phi3_tautau_ATLAS8 = 0.0;
THoEX_ggF_phi3_tautau_CMS8 = 0.0;
R_ggF_phi3_tautau_CMS8 = 0.0;
THoEX_bbF_phi3_tautau_ATLAS8 = 0.0;
R_bbF_phi3_tautau_ATLAS8 = 0.0;
THoEX_bbF_phi3_tautau_CMS8 = 0.0;
R_bbF_phi3_tautau_CMS8 = 0.0;
THoEX_pp_phi3_gaga_ATLAS8 = 0.0;
R_pp_phi3_gaga_ATLAS8 = 0.0;
THoEX_ggF_phi3_gaga_CMS8 = 0.0;
R_ggF_phi3_gaga_CMS8 = 0.0;
THoEX_pp_phi3_Zga_llga_ATLAS8 = 0.0;
R_pp_phi3_Zga_llga_ATLAS8 = 0.0;
THoEX_pp_phi3_Zga_llga_CMS8 = 0.0;
R_pp_phi3_Zga_llga_CMS8 = 0.0;
THoEX_mu_pp_phi3_VV_CMS8 = 0.0;
R_mu_pp_phi3_VV_CMS8 = 0.0;
THoEX_ggF_phi3_ZZ_ATLAS8 = 0.0;
R_ggF_phi3_ZZ_ATLAS8 = 0.0;
THoEX_VBF_phi3_ZZ_ATLAS8 = 0.0;
 R_VBF_phi3_ZZ_ATLAS8 = 0.0;
THoEX_ggF_phi3_WW_ATLAS8 = 0.0;
R_ggF_phi3_WW_ATLAS8 = 0.0;
THoEX_VBF_phi3_WW_ATLAS8 = 0.0;
R_VBF_phi3_WW_ATLAS8 = 0.0;
THoEX_ggF_phi3_phi1phi1_ATLAS8 = 0.0;
R_VBF_phi3_WW_ATLAS8 = 0.0;
THoEX_ggF_phi3_phi2phi2_ATLAS8 = 0.0;
R_ggF_phi3_phi1phi1_ATLAS8 = 0.0;
THoEX_pp_phi3_phi1phi1_CMS8 = 0.0;
R_ggF_phi3_phi2phi2_ATLAS8 = 0.0;
THoEX_pp_phi3_phi2phi2_CMS8 = 0.0;

R_pp_phi3_phi1phi1_CMS8 = 0.0;
THoEX_ggF_phi3_phi1phi1_bbtautau_CMS8 = 0.0;
R_ggF_phi3_phi1phi1_bbtautau_CMS8 = 0.0;
THoEX_pp_phi3_phi1phi1_bbbb_CMS8 = 0.0;
R_pp_phi3_phi1phi1_bbbb_CMS8 = 0.0;
THoEX_pp_phi3_phi1phi1_gagabb_CMS8 = 0.0;
R_pp_phi3_phi1phi1_gagabb_CMS8 = 0.0;

R_pp_phi3_phi2phi2_CMS8 = 0.0;
THoEX_ggF_phi3_phi2phi2_bbtautau_CMS8 = 0.0;
R_ggF_phi3_phi2phi2_bbtautau_CMS8 = 0.0;
THoEX_pp_phi3_phi2phi2_bbbb_CMS8 = 0.0;
R_pp_phi3_phi2phi2_bbbb_CMS8 = 0.0;
THoEX_pp_phi3_phi2phi2_gagabb_CMS8 = 0.0;
R_pp_phi3_phi2phi2_gagabb_CMS8 = 0.0;

THoEX_ggF_phi3_tt_ATLAS8 = 0.0;
R_ggF_phi3_tt_ATLAS8 = 0.0;
THoEX_bbF_phi3_bb_CMS8 = 0.0;
R_bbF_phi3_bb_CMS8 = 0.0;
//THoEX_pp_H_AZ_bbll_CMS8 = 0.0;
//R_pp_H_AZ_bbll_CMS8 = 0.0;
//THoEX_pp_H_AZ_tautaull_CMS8 = 0.0;
//R_pp_H_AZ_tautaull_CMS8 = 0.0;


/*std::cout << " m1 = " << m1 << std::endl;
std::cout << " m2 = " << m2 << std::endl;
std::cout << " m3 = " << m3 << std::endl;*/

   //Theoretical expressions for the Heavy Higgs cross sections times branching ratios at 13 TeV

    ggF_phi3_tautau_TH13=SigmaggF_phi3_13*Br_phi3totautau;
    bbF_phi3_tautau_TH13=SigmabbF_phi3_13*Br_phi3totautau;
    pp_phi3_gaga_TH13=SigmaSumphi3_13*Br_phi3togaga;
    ggF_phi3_gaga_TH13=SigmaggF_phi3_13*Br_phi3togaga;
    pp_phi3_Zga_TH13=SigmaSumphi3_13*Br_phi3toZga;
    ggF_phi3_Zga_TH13=SigmaggF_phi3_13*Br_phi3toZga;
    pp_phi3_ZZ_TH13=SigmaSumphi3_13*Br_phi3toZZ;
    ggF_phi3_ZZ_TH13=SigmaggF_phi3_13*Br_phi3toZZ;
    VBF_phi3_ZZ_TH13=SigmaVBF_phi3_13*Br_phi3toZZ;
    
    
    ggF_phi3_ZZ_llll_TH13=SigmaggF_phi3_13*Br_phi3toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    VBF_phi3_ZZ_llll_TH13=SigmaVBF_phi3_13*Br_phi3toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    pp_phi3_ZZ_llll_TH13=SigmaSumphi3_13*Br_phi3toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    VBF_VH_phi3_ZZ_llll_TH13=(SigmaVBF_phi3_13+SigmaVH_phi3_13)*Br_phi3toZZ*(Br_Ztoee+Br_Ztomumu)*(Br_Ztoee+Br_Ztomumu);
    ggF_phi3_WW_TH13=SigmaggF_phi3_13*Br_phi3toWW;
    VBF_phi3_WW_TH13=SigmaVBF_phi3_13*Br_phi3toWW;
    ggF_VBF_phi3_WW_lnulnu_TH13=(SigmaggF_phi3_13+SigmaVBF_phi3_13)*Br_phi3toWW*(Br_Wtoenu+Br_Wtomunu)*(Br_Wtoenu+Br_Wtomunu);
    pp_phi3_VV_TH13=SigmaSumphi3_13*(Br_phi3toZZ+Br_phi3toWW);
    ggF_phi3_phi1phi1_TH13=SigmaggF_phi3_13*Br_phi3tophi1phi1;
    ggF_phi3_phi2phi2_TH13=SigmaggF_phi3_13*Br_phi3tophi2phi2;
    ggF_phi3_phi1phi2_TH13=SigmaggF_phi3_13*Br_phi3tophi1phi2;
    pp_phi3_phi1phi1_TH13=SigmaSumphi3_13*Br_phi3tophi1phi1;
    pp_phi3_phi2phi2_TH13=SigmaSumphi3_13*Br_phi3tophi2phi2;
    pp_phi3_phi1phi2_TH13=SigmaSumphi3_13*Br_phi3tophi1phi2;


    
    pp_phi3_phi1phi1_bbbb_TH13=SigmaSumphi3_13*Br_phi3tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_bb;
    ggF_phi3_phi1phi1_bbbb_TH13=SigmaggF_phi3_13*Br_phi3tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_bb;
    pp_phi3_phi1phi1_gagabb_TH13=SigmaSumphi3_13*Br_phi3tophi1phi1*GTHDM_BR_h_gaga*GTHDM_BR_h_bb*2.0;
    pp_phi3_phi1phi1_bbtautau_TH13=SigmaSumphi3_13*Br_phi3tophi1phi1*GTHDM_BR_h_bb*GTHDM_BR_h_tautau*2.0;
    pp_phi3_phi1phi1_bblnulnu_TH13=SigmaSumphi3_13*Br_phi3tophi1phi1*5.77e-1*2.15e-1*(Br_Wtoenu+Br_Wtomunu)*(Br_Wtoenu+Br_Wtomunu)*2.0;/*SM BR assumed in the CMS analysis!*/
    pp_phi3_phi1phi1_bbVV_TH13=SigmaSumphi3_13*Br_phi3tophi1phi1*2.0*GTHDM_BR_h_bb*(GTHDM_BR_h_WW*pow(Br_Wtoenu+Br_Wtomunu+Br_Wtotaunu*0.352,2)
                                                            +GTHDM_BR_h_ZZ*2.0*Br_Ztoinv*(Br_Ztoee+Br_Ztomumu+Br_Ztotautau*0.124));
            
    pp_phi3_phi2phi2_bbbb_TH13=SigmaSumphi3_13*Br_phi3tophi2phi2*Br_phi2tobb*Br_phi2tobb;
    ggF_phi3_phi2phi2_bbbb_TH13=SigmaggF_phi3_13*Br_phi3tophi2phi2*Br_phi2tobb*Br_phi2tobb;
    pp_phi3_phi2phi2_gagabb_TH13=SigmaSumphi3_13*Br_phi3tophi2phi2*Br_phi2togaga*Br_phi2tobb*2.0;
    pp_phi3_phi2phi2_bbtautau_TH13=SigmaSumphi3_13*Br_phi3tophi2phi2*Br_phi2tobb*Br_phi2totautau*2.0;
    pp_phi3_phi2phi2_bblnulnu_TH13=SigmaSumphi3_13*Br_phi3tophi2phi2*5.77e-1*2.15e-1*(Br_Wtoenu+Br_Wtomunu)*(Br_Wtoenu+Br_Wtomunu)*2.0;/*SM BR assumed in the CMS analysis!*/
    pp_phi3_phi2phi2_bbVV_TH13=SigmaSumphi3_13*Br_phi3tophi2phi2*2.0*Br_phi2tobb*(Br_phi2toWW*pow(Br_Wtoenu+Br_Wtomunu+Br_Wtotaunu*0.352,2)
                                                            +Br_phi2toZZ*2.0*Br_Ztoinv*(Br_Ztoee+Br_Ztomumu+Br_Ztotautau*0.124));
        
            
    pp_phi3_phi1phi2_bbbb_TH13=SigmaSumphi3_13*Br_phi3tophi1phi2*GTHDM_BR_h_bb*Br_phi2tobb;
    ggF_phi3_phi1phi2_bbbb_TH13=SigmaggF_phi3_13*Br_phi3tophi1phi2*GTHDM_BR_h_bb*Br_phi2tobb;
    
    pp_phi3_phi1phi2_gagabb_TH13=SigmaSumphi3_13*Br_phi3tophi1phi2*(GTHDM_BR_h_gaga*Br_phi2tobb + Br_phi2togaga*GTHDM_BR_h_bb);
    pp_phi3_phi1phi2_bbtautau_TH13=SigmaSumphi3_13*Br_phi3tophi1phi2*(GTHDM_BR_h_bb*Br_phi2totautau+Br_phi2tobb*GTHDM_BR_h_tautau);
    pp_phi3_phi1phi2_bblnulnu_TH13=SigmaSumphi3_13*Br_phi3tophi1phi2*5.77e-1*2.15e-1*(Br_Wtoenu+Br_Wtomunu)*(Br_Wtoenu+Br_Wtomunu)*2.0;/*SM BR assumed in the CMS analysis!*/
    pp_phi3_phi1phi2_bbVV_TH13=SigmaSumphi3_13*Br_phi3tophi2phi2*(GTHDM_BR_h_bb*(Br_phi2toWW*pow(Br_Wtoenu+Br_Wtomunu+Br_Wtotaunu*0.352,2)
                                                            +Br_phi2toZZ*2.0*Br_Ztoinv*(Br_Ztoee+Br_Ztomumu+Br_Ztotautau*0.124))
                                                +Br_phi2tobb*(GTHDM_BR_h_WW*pow(Br_Wtoenu+Br_Wtomunu+Br_Wtotaunu*0.352,2)
                                                            +GTHDM_BR_h_ZZ*2.0*Br_Ztoinv*(Br_Ztoee+Br_Ztomumu+Br_Ztotautau*0.124)));
        
            
            
            
            
    ttF_phi3_tt_TH13=SigmattF_phi3_13*Br_phi3tott;
    bbF_phi3_tt_TH13=SigmabbF_phi3_13*Br_phi3tott;
    pp_phi3_bb_TH13=SigmaSumphi3_13*Br_phi3tobb;



    //95% to 1 sigma conversion factor, roughly sqrt(3.84)
    double nftos=1.95996398454;

   
    if(m3>=65.0 && m3<90.0)
    {
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
         if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
    }
    else if(m3>=90.0 && m3<100.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }     
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
    }
    
     else if(m3>=100.0 && m3<130.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
          if(m2>=50.0 && m2<=1000.0)
        {
           THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
           // R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
   
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }     

        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=130.0 && m3<140.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=140.0 && m3<145.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }

        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=145.0 && m3<150.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=150.0 && m3<175.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=175.0 && m3<200.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=200.0 && m3<220.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
                if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=220.0 && m3<250.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=250.0 && m3<260.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=(ggF_phi3_gaga_TH8+ip_ex_gg_phi_gaga_CMS8_e(m3)-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }

        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;        
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;       
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=260.0 && m3<270.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbtautau_CMS8=ggF_phi3_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi1_bbtautau_CMS8=(1+(ggF_phi3_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbtautau_CMS8=ggF_phi3_phi2phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi2phi2_bbtautau_CMS8=(1+(ggF_phi3_phi2phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbtautau_CMS8=ggF_phi3_phi1phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi2_bbtautau_CMS8=(1+(ggF_phi3_phi1phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;        
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_gagaWW_ATLAS13=ggF_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_gagaWW_ATLAS13=ggF_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi2phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_gagaWW_ATLAS13=ggF_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos; 
    }
    else if(m3>=270.0 && m3<275.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbtautau_CMS8=ggF_phi3_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi1_bbtautau_CMS8=(1+(ggF_phi3_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos; 
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbtautau_CMS8=ggF_phi3_phi2phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi2phi2_bbtautau_CMS8=(1+(ggF_phi3_phi2phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbtautau_CMS8=ggF_phi3_phi1phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi2_bbtautau_CMS8=(1+(ggF_phi3_phi1phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;        
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_gagaWW_ATLAS13=ggF_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_gagaWW_ATLAS13=ggF_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi2phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_gagaWW_ATLAS13=ggF_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos; 
    }
    else if(m3>=275.0 && m3<300.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;   
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbtautau_CMS8=ggF_phi3_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi1_bbtautau_CMS8=(1+(ggF_phi3_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;     
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbtautau_CMS8=ggF_phi3_phi2phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi2phi2_bbtautau_CMS8=(1+(ggF_phi3_phi2phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;      
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbtautau_CMS8=ggF_phi3_phi1phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi2_bbtautau_CMS8=(1+(ggF_phi3_phi1phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos; 
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos; 
        THoEX_pp_phi3_phi1phi1_bbgaga_ATLAS13=pp_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_ATLAS13=(1+(pp_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_gagaWW_ATLAS13=ggF_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_ATLAS13=pp_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_ATLAS13=(1+(pp_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_gagaWW_ATLAS13=ggF_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi2phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_ATLAS13=pp_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_ATLAS13=(1+(pp_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_gagaWW_ATLAS13=ggF_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=300.0 && m3<350.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;     
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbtautau_CMS8=ggF_phi3_phi1phi1_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi1_bbtautau_CMS8=(1+(ggF_phi3_phi1phi1_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbtautau_CMS8=ggF_phi3_phi2phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi2phi2_bbtautau_CMS8=(1+(ggF_phi3_phi2phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbtautau_CMS8=ggF_phi3_phi1phi2_bbtautau_TH8/ip_ex_gg_H_hh_bbtautau_CMS8(m3);
        R_ggF_phi3_phi1phi2_bbtautau_CMS8=(1+(ggF_phi3_phi1phi2_bbtautau_TH8-ip_ex_gg_H_hh_bbtautau_CMS8(m3))/ip_ex_gg_H_hh_bbtautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_ATLAS13=pp_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_ATLAS13=(1+(pp_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_gagaWW_ATLAS13=ggF_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_ATLAS13=pp_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_ATLAS13=(1+(pp_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_gagaWW_ATLAS13=ggF_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi2phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_ATLAS13=pp_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_ATLAS13=(1+(pp_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_gagaWW_ATLAS13=ggF_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
     }
    else if(m3>=350.0 && m3<400.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;     
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;      
        THoEX_pp_phi3_phi1phi1_bbgaga_ATLAS13=pp_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_ATLAS13=(1+(pp_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_gagaWW_ATLAS13=ggF_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_ATLAS13=pp_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_ATLAS13=(1+(pp_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_gagaWW_ATLAS13=ggF_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi2phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_ATLAS13=pp_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagabb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_ATLAS13=(1+(pp_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagabb_ATLAS13(m3))/ip_ex_pp_H_hh_gagabb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_gagaWW_ATLAS13=ggF_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=400.0 && m3<500.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;     
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos; 
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_gagaWW_ATLAS13=ggF_phi3_phi1phi1_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi1_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi1_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_gagaWW_ATLAS13=ggF_phi3_phi2phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi2phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi2phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
         THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_gagaWW_ATLAS13=ggF_phi3_phi1phi2_TH13/ip_ex_pp_H_hh_gagaWW_ATLAS13(m3);
        R_ggF_phi3_phi1phi2_gagaWW_ATLAS13=(1+(ggF_phi3_phi1phi2_TH13-ip_ex_pp_H_hh_gagaWW_ATLAS13(m3))/ip_ex_pp_H_hh_gagaWW_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
     }
    else if(m3>=500.0 && m3<550.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos; 
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
                if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=550.0 && m3<600.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS8=pp_phi3_gaga_TH8/ip_ex_pp_phi_gaga_ATLAS8(m3);
        R_pp_phi3_gaga_ATLAS8=(1+(pp_phi3_gaga_TH8-ip_ex_pp_phi_gaga_ATLAS8(m3))/ip_ex_pp_phi_gaga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;    
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_CMS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_CMS13(m3);
        R_ggF_phi3_ZZ_llnunu_CMS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_CMS13(m3))/ip_ex_gg_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llnunu_CMS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llnunu_CMS13(m3);
        R_VBF_phi3_ZZ_llnunu_CMS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llnunu_CMS13(m3))/ip_ex_VBF_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos; 
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=600.0 && m3<650.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=650.0 && m3<760.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
       
        
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos; 
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
                if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
     }
    else if(m3>=760.0 && m3<850.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS8=ggF_phi3_gaga_TH8/ip_ex_gg_phi_gaga_CMS8(m3);
        R_ggF_phi3_gaga_CMS8=(1+(ggF_phi3_gaga_TH8-ip_ex_gg_phi_gaga_CMS8(m3))/ip_ex_gg_phi_gaga_CMS8_e(m3) ) * nftos;
//    LIMIT_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3);
//    LIMEST_ggF_phi3_gaga_CMS8=0.0;
//    DEVIATION_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8(m3)-ip_ex_gg_phi_gaga_CMS8_e(m3);
//    BANDSIZE_ggF_phi3_gaga_CMS8=ip_ex_gg_phi_gaga_CMS8_ep2(m3)-ip_ex_gg_phi_gaga_CMS8_em2(m3);
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=850.0 && m3<900.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_bb_CMS8=bbF_phi3_bb_TH8/ip_ex_bb_phi_bb_CMS8(m3);
        R_bbF_phi3_bb_CMS8=(1+(bbF_phi3_bb_TH8-ip_ex_bb_phi_bb_CMS8(m3))/ip_ex_bb_phi_bb_CMS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbgaga_CMS13=pp_phi3_phi1phi1_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbgaga_CMS13=(1+(pp_phi3_phi1phi1_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbtautau1_CMS13=pp_phi3_phi1phi1_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi1_bbtautau1_CMS13=(1+(pp_phi3_phi1phi1_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bblnulnu_CMS13=pp_phi3_phi1phi1_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi1_bblnulnu_CMS13=(1+(pp_phi3_phi1phi1_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbVV_CMS13=pp_phi3_phi1phi1_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi1_bbVV_CMS13=(1+(pp_phi3_phi1phi1_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbgaga_CMS13=pp_phi3_phi2phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbgaga_CMS13=(1+(pp_phi3_phi2phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbtautau1_CMS13=pp_phi3_phi2phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi2phi2_bbtautau1_CMS13=(1+(pp_phi3_phi2phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bblnulnu_CMS13=pp_phi3_phi2phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi2phi2_bblnulnu_CMS13=(1+(pp_phi3_phi2phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbVV_CMS13=pp_phi3_phi2phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi2phi2_bbVV_CMS13=(1+(pp_phi3_phi2phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbgaga_CMS13=pp_phi3_phi1phi2_gagabb_TH13/ip_ex_pp_H_hh_gagabb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbgaga_CMS13=(1+(pp_phi3_phi1phi2_gagabb_TH13-ip_ex_pp_H_hh_gagabb_CMS13(m3))/ip_ex_pp_H_hh_gagabb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau_CMS13(m3))/ip_ex_pp_H_hh_bbtautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbtautau1_CMS13=pp_phi3_phi1phi2_bbtautau_TH13/ip_ex_pp_H_hh_bbtautau1_CMS13(m3);
        R_pp_phi3_phi1phi2_bbtautau1_CMS13=(1+(pp_phi3_phi1phi2_bbtautau_TH13-ip_ex_pp_H_hh_bbtautau1_CMS13(m3))/ip_ex_pp_H_hh_bbtautau1_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bblnulnu_CMS13=pp_phi3_phi1phi2_bblnulnu_TH13/ip_ex_pp_H_hh_bblnulnu_CMS13(m3);
        R_pp_phi3_phi1phi2_bblnulnu_CMS13=(1+(pp_phi3_phi1phi2_bblnulnu_TH13-ip_ex_pp_H_hh_bblnulnu_CMS13(m3))/ip_ex_pp_H_hh_bblnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbVV_CMS13=pp_phi3_phi1phi2_bbVV_TH13/ip_ex_pp_H_hh_bbVV_CMS13(m3);
        R_pp_phi3_phi1phi2_bbVV_CMS13=(1+(pp_phi3_phi1phi2_bbVV_TH13-ip_ex_pp_H_hh_bbVV_CMS13(m3))/ip_ex_pp_H_hh_bbVV_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=900.0 && m3<1000.0)
    {
        THoEX_ggF_phi3_tautau_ATLAS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_ATLAS8(m3);
        R_ggF_phi3_tautau_ATLAS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_ATLAS8(m3))/ip_ex_gg_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS8=ggF_phi3_tautau_TH8/ip_ex_gg_phi_tautau_CMS8(m3);
        R_ggF_phi3_tautau_CMS8=(1+(ggF_phi3_tautau_TH8-ip_ex_gg_phi_tautau_CMS8(m3))/ip_ex_gg_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_ATLAS8(m3);
        R_bbF_phi3_tautau_ATLAS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_ATLAS8(m3))/ip_ex_bb_phi_tautau_ATLAS8_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS8=bbF_phi3_tautau_TH8/ip_ex_bb_phi_tautau_CMS8(m3);
        R_bbF_phi3_tautau_CMS8=(1+(bbF_phi3_tautau_TH8-ip_ex_bb_phi_tautau_CMS8(m3))/ip_ex_bb_phi_tautau_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_ATLAS8=ggF_phi3_ZZ_TH8/ip_ex_gg_H_ZZ_ATLAS8(m3);
        R_ggF_phi3_ZZ_ATLAS8=(1+(ggF_phi3_ZZ_TH8-ip_ex_gg_H_ZZ_ATLAS8(m3))/ip_ex_gg_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_ATLAS8=VBF_phi3_ZZ_TH8/ip_ex_VBF_H_ZZ_ATLAS8(m3);
        R_VBF_phi3_ZZ_ATLAS8=(1+(VBF_phi3_ZZ_TH8-ip_ex_VBF_H_ZZ_ATLAS8(m3))/ip_ex_VBF_H_ZZ_ATLAS8_e(m3) ) * nftos;
        THoEX_mu_pp_phi3_VV_CMS8=mu_pp_phi3_VV_TH8/ip_ex_mu_pp_H_VV_CMS8(m3);
        R_mu_pp_phi3_VV_CMS8=(1+(mu_pp_phi3_VV_TH8-ip_ex_mu_pp_H_VV_CMS8(m3))/ip_ex_mu_pp_H_VV_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_ATLAS8=ggF_phi3_phi1phi1_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi1_ATLAS8=(1+(ggF_phi3_phi1phi1_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_CMS8=pp_phi3_phi1phi1_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi1_CMS8=(1+(pp_phi3_phi1phi1_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_ATLAS8=ggF_phi3_phi2phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi2phi2_ATLAS8=(1+(ggF_phi3_phi2phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_CMS8=pp_phi3_phi2phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi2phi2_CMS8=(1+(pp_phi3_phi2phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_ATLAS8=ggF_phi3_phi1phi2_TH8/ip_ex_gg_H_hh_ATLAS8(m3);
        R_ggF_phi3_phi1phi2_ATLAS8=(1+(ggF_phi3_phi1phi2_TH8-ip_ex_gg_H_hh_ATLAS8(m3))/ip_ex_gg_H_hh_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_CMS8=pp_phi3_phi1phi2_TH8/ip_ex_pp_H_hh_CMS8(m3);
        R_pp_phi3_phi1phi2_CMS8=(1+(pp_phi3_phi1phi2_TH8-ip_ex_pp_H_hh_CMS8(m3))/ip_ex_pp_H_hh_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;      
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        if(m2>=40.0 && m2<=910.0)
        {
            THoEX_pp_phi3_phi2Z_bbll_CMS8=pp_phi3_phi2Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3);
            R_pp_phi3_phi2Z_bbll_CMS8=(1+(pp_phi3_phi2Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m2,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m2,m3) ) * nftos;
        }
        if(m2>=50.0 && m2<=1000.0)
        {
            THoEX_pp_phi3_phi2Z_tautaull_CMS8=pp_phi3_phi2Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3);
            R_pp_phi3_phi2Z_tautaull_CMS8=(1+(pp_phi3_phi2Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m2,m3) ) * nftos;
        }
        if(m1>=40.0 && m1<=910.0)
        {
            THoEX_pp_phi3_phi1Z_bbll_CMS8=pp_phi3_phi1Z_bbll_TH8/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3);
            R_pp_phi3_phi1Z_bbll_CMS8=(1+(pp_phi3_phi1Z_bbll_TH8-ip_ex_pp_H_AZ_bbll_CMS8(m1,m3))/ip_ex_pp_H_AZ_bbll_CMS8(m1,m3) ) * nftos;
        }
          if(m1>=50.0 && m1<=1000.0)
        {
            THoEX_pp_phi3_phi1Z_tautaull_CMS8=pp_phi3_phi1Z_tautaull_TH8/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3);
            R_pp_phi3_phi1Z_tautaull_CMS8=(1+(pp_phi3_phi1Z_tautaull_TH8-ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3))/ip_ex_pp_H_AZ_tautaull_CMS8(m1,m3) ) * nftos;
        }
        THoEX_ttF_phi3_tt_ATLAS13=ttF_phi3_tt_TH13/ip_ex_tt_phi_tt_ATLAS13(m3);
        R_ttF_phi3_tt_ATLAS13=(1+(ttF_phi3_tt_TH13-ip_ex_tt_phi_tt_ATLAS13(m3))/ip_ex_tt_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tt_ATLAS13=bbF_phi3_tt_TH13/ip_ex_bb_phi_tt_ATLAS13(m3);
        R_bbF_phi3_tt_ATLAS13=(1+(bbF_phi3_tt_TH13-ip_ex_bb_phi_tt_ATLAS13(m3))/ip_ex_bb_phi_tt_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llll_ATLAS13=ggF_phi3_ZZ_llll_TH13/ip_ex_gg_H_ZZ_llll_ATLAS13(m3);
        R_ggF_phi3_ZZ_llll_ATLAS13=(1+(ggF_phi3_ZZ_llll_TH13-ip_ex_gg_H_ZZ_llll_ATLAS13(m3))/ip_ex_gg_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llll_ATLAS13=VBF_phi3_ZZ_llll_TH13/ip_ex_VBF_H_ZZ_llll_ATLAS13(m3);
        R_VBF_phi3_ZZ_llll_ATLAS13=(1+(VBF_phi3_ZZ_llll_TH13-ip_ex_VBF_H_ZZ_llll_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llll_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_VBF_phi3_WW_lnulnu_CMS13=ggF_VBF_phi3_WW_lnulnu_TH13/ip_ex_ggVV_H_WW_lnulnu_CMS13(m3);
        R_ggF_VBF_phi3_WW_lnulnu_CMS13=(1+(ggF_VBF_phi3_WW_lnulnu_TH13-ip_ex_ggVV_H_WW_lnulnu_CMS13(m3))/ip_ex_ggVV_H_WW_lnulnu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=1000.0 && m3<1100.0)
    {
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS8=pp_phi3_phi1phi1_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS8=(1+(pp_phi3_phi1phi1_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_gagabb_CMS8=pp_phi3_phi1phi1_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi1_gagabb_CMS8=(1+(pp_phi3_phi1phi1_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS8=pp_phi3_phi2phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS8=(1+(pp_phi3_phi2phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_gagabb_CMS8=pp_phi3_phi2phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi2phi2_gagabb_CMS8=(1+(pp_phi3_phi2phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;   
        THoEX_pp_phi3_phi1phi2_bbbb_CMS8=pp_phi3_phi1phi2_bbbb_TH8/ip_ex_pp_phi_hh_bbbb_CMS8(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS8=(1+(pp_phi3_phi1phi2_bbbb_TH8-ip_ex_pp_phi_hh_bbbb_CMS8(m3))/ip_ex_pp_phi_hh_bbbb_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_gagabb_CMS8=pp_phi3_phi1phi2_gagabb_TH8/ip_ex_pp_phi_hh_gagabb_CMS8(m3);
        R_pp_phi3_phi1phi2_gagabb_CMS8=(1+(pp_phi3_phi1phi2_gagabb_TH8-ip_ex_pp_phi_hh_gagabb_CMS8(m3))/ip_ex_pp_phi_hh_gagabb_CMS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=1100.0 && m3<1200.0)
    {
        THoEX_pp_phi3_Zga_llga_CMS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_A_Zga_llga_CMS8(m3);
        R_pp_phi3_Zga_llga_CMS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_A_Zga_llga_CMS8(m3))/ip_ex_pp_A_Zga_llga_CMS8_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_pp_phi3_bb_CMS13=pp_phi3_bb_TH13/ip_ex_pp_phi_bb_CMS13(m3);
        R_pp_phi3_bb_CMS13=(1+(pp_phi3_bb_TH13-ip_ex_pp_phi_bb_CMS13(m3))/ip_ex_pp_phi_bb_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_llllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_llllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_CMS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi1_bbbb_CMS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_CMS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi2phi2_bbbb_CMS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_CMS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_CMS13(m3);
        R_pp_phi3_phi1phi2_bbbb_CMS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_CMS13(m3))/ip_ex_pp_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=1200.0 && m3<1500.0)
    {
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_ATLAS8=ggF_phi3_WW_TH8/ip_ex_gg_H_WW_ATLAS8(m3);
        R_ggF_phi3_WW_ATLAS8=(1+(ggF_phi3_WW_TH8-ip_ex_gg_H_WW_ATLAS8(m3))/ip_ex_gg_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_ATLAS8=VBF_phi3_WW_TH8/ip_ex_VBF_H_WW_ATLAS8(m3);
        R_VBF_phi3_WW_ATLAS8=(1+(VBF_phi3_WW_TH8-ip_ex_VBF_H_WW_ATLAS8(m3))/ip_ex_VBF_H_WW_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        
    
    }
    else if(m3>=1500.0 && m3<1600.0)
    {
        THoEX_pp_phi3_Zga_llga_ATLAS8=pp_phi3_Zga_llga_TH8/ip_ex_pp_phi_Zga_llga_ATLAS8(m3);
        R_pp_phi3_Zga_llga_ATLAS8=(1+(pp_phi3_Zga_llga_TH8-ip_ex_pp_phi_Zga_llga_ATLAS8(m3))/ip_ex_pp_phi_Zga_llga_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;       
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;     
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;   
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
 
    }
    else if(m3>=1600.0 && m3<2000.0)
    {
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_llga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_CMS13(m3);
        R_pp_phi3_Zga_llga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_CMS13(m3))/ip_ex_pp_phi_Zga_llga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llqq_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llqq_CMS13(m3);
        R_pp_phi3_ZZ_llqq_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llqq_CMS13(m3))/ip_ex_pp_H_ZZ_llqq_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;       
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=2000.0 && m3<2250.0)
    {
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_ATLAS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_ATLAS13(m3);
        R_ggF_phi3_tautau_ATLAS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_ATLAS13(m3))/ip_ex_gg_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_ATLAS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_ATLAS13(m3);
        R_bbF_phi3_tautau_ATLAS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_ATLAS13(m3))/ip_ex_bb_phi_tautau_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
         THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
          }
    else if(m3>=2250.0 && m3<2400.0)
    {
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_ATLAS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_llga_ATLAS13(m3);
        R_pp_phi3_Zga_ATLAS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_llga_ATLAS13(m3))/ip_ex_pp_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;
         THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=2400.0 && m3<2500.0)
    {
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_llga_ATLAS13=ggF_phi3_Zga_TH13/ip_ex_gg_phi_Zga_llga_ATLAS13(m3);
        R_ggF_phi3_Zga_llga_ATLAS13=(1+(ggF_phi3_Zga_TH13-ip_ex_gg_phi_Zga_llga_ATLAS13(m3))/ip_ex_gg_phi_Zga_llga_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llnunu_CMS13=pp_phi3_ZZ_TH13/ip_ex_pp_H_ZZ_llnunu_CMS13(m3);
        R_pp_phi3_ZZ_llnunu_CMS13=(1+(pp_phi3_ZZ_TH13-ip_ex_pp_H_ZZ_llnunu_CMS13(m3))/ip_ex_pp_H_ZZ_llnunu_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=2500.0 && m3<2530.0)
    {
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_ZZ_llll_CMS13=pp_phi3_ZZ_llll_TH13/ip_ex_pp_H_ZZ_llll_CMS13(m3);
        R_pp_phi3_ZZ_llll_CMS13=(1+(pp_phi3_ZZ_llll_TH13-ip_ex_pp_H_ZZ_llll_CMS13(m3))/ip_ex_pp_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_VBF_VH_phi3_ZZ_llll_CMS13=VBF_VH_phi3_ZZ_llll_TH13/ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3);
        R_VBF_VH_phi3_ZZ_llll_CMS13=(1+(VBF_VH_phi3_ZZ_llll_TH13-ip_ex_VBF_VH_H_ZZ_llll_CMS13(m3))/ip_ex_VBF_VH_H_ZZ_llll_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=2530.0 && m3<2700.0)
    {
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_gaga_ATLAS13=pp_phi3_gaga_TH13/ip_ex_pp_phi_gaga_ATLAS13(m3);
        R_pp_phi3_gaga_ATLAS13=(1+(pp_phi3_gaga_TH13-ip_ex_pp_phi_gaga_ATLAS13(m3))/ip_ex_pp_phi_gaga_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos; 
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos; 
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
    }
    else if(m3>=2700.0 && m3<3000.0)
    {
        THoEX_ggF_phi3_tt_ATLAS8=ggF_phi3_tt_TH8/ip_ex_gg_phi_tt_ATLAS8(m3);
        R_ggF_phi3_tt_ATLAS8=(1+(ggF_phi3_tt_TH8-ip_ex_gg_phi_tt_ATLAS8(m3))/ip_ex_gg_phi_tt_ATLAS8_e(m3) ) * nftos;
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_Zga_qqga_CMS13=pp_phi3_Zga_TH13/ip_ex_pp_phi_Zga_qqga_CMS13(m3);
        R_pp_phi3_Zga_qqga_CMS13=(1+(pp_phi3_Zga_TH13-ip_ex_pp_phi_Zga_qqga_CMS13(m3))/ip_ex_pp_phi_Zga_qqga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_qqllnunu_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3);
        R_ggF_phi3_ZZ_qqllnunu_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_gg_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_qqllnunu_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3);
        R_VBF_phi3_ZZ_qqllnunu_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13(m3))/ip_ex_VBF_H_ZZ_qqllnunu_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_llqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_llqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_llqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_llqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_ZZ_llqq_ATLAS13=VBF_phi3_ZZ_TH13/ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3);
        R_VBF_phi3_ZZ_llqq_ATLAS13=(1+(VBF_phi3_ZZ_TH13-ip_ex_VBF_H_ZZ_llqq_ATLAS13(m3))/ip_ex_VBF_H_ZZ_llqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_ZZ_nunuqq_ATLAS13=ggF_phi3_ZZ_TH13/ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3);
        R_ggF_phi3_ZZ_nunuqq_ATLAS13=(1+(ggF_phi3_ZZ_TH13-ip_ex_gg_H_ZZ_nunuqq_ATLAS13(m3))/ip_ex_gg_H_ZZ_nunuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_lnuqq_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_lnuqq_ATLAS13(m3);
        R_ggF_phi3_WW_lnuqq_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_lnuqq_ATLAS13(m3))/ip_ex_gg_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_lnuqq_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3);
        R_VBF_phi3_WW_lnuqq_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_lnuqq_ATLAS13(m3))/ip_ex_VBF_H_WW_lnuqq_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_VBF_phi3_WW_enumunu_ATLAS13=VBF_phi3_WW_TH13/ip_ex_VBF_H_WW_enumunu_ATLAS13(m3);
        R_VBF_phi3_WW_enumunu_ATLAS13=(1+(VBF_phi3_WW_TH13-ip_ex_VBF_H_WW_enumunu_ATLAS13(m3))/ip_ex_VBF_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_VV_qqqq_ATLAS13=pp_phi3_VV_TH13/ip_ex_pp_H_VV_qqqq_ATLAS13(m3);
        R_pp_phi3_VV_qqqq_ATLAS13=(1+(pp_phi3_VV_TH13-ip_ex_pp_H_VV_qqqq_ATLAS13(m3))/ip_ex_pp_H_VV_qqqq_ATLAS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi1_bbbb_ATLAS13=pp_phi3_phi1phi1_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi1_bbbb_ATLAS13=(1+(pp_phi3_phi1phi1_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi1_bbbb_CMS13=ggF_phi3_phi1phi1_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi1_bbbb_CMS13=(1+(ggF_phi3_phi1phi1_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi2phi2_bbbb_ATLAS13=pp_phi3_phi2phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi2phi2_bbbb_ATLAS13=(1+(pp_phi3_phi2phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi2phi2_bbbb_CMS13=ggF_phi3_phi2phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi2phi2_bbbb_CMS13=(1+(ggF_phi3_phi2phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
        THoEX_pp_phi3_phi1phi2_bbbb_ATLAS13=pp_phi3_phi1phi2_bbbb_TH13/ip_ex_pp_H_hh_bbbb_ATLAS13(m3);
        R_pp_phi3_phi1phi2_bbbb_ATLAS13=(1+(pp_phi3_phi1phi2_bbbb_TH13-ip_ex_pp_H_hh_bbbb_ATLAS13(m3))/ip_ex_pp_H_hh_bbbb_ATLAS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_phi1phi2_bbbb_CMS13=ggF_phi3_phi1phi2_bbbb_TH13/ip_ex_ggF_H_hh_bbbb_CMS13(m3);
        R_ggF_phi3_phi1phi2_bbbb_CMS13=(1+(ggF_phi3_phi1phi2_bbbb_TH13-ip_ex_ggF_H_hh_bbbb_CMS13(m3))/ip_ex_ggF_H_hh_bbbb_CMS13_e(m3) ) * nftos;
     }
       else if(m3>=3000.0 && m3<3200.0)
    {
        THoEX_ggF_phi3_tautau_CMS13=ggF_phi3_tautau_TH13/ip_ex_gg_phi_tautau_CMS13(m3);
        R_ggF_phi3_tautau_CMS13=(1+(ggF_phi3_tautau_TH13-ip_ex_gg_phi_tautau_CMS13(m3))/ip_ex_gg_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_bbF_phi3_tautau_CMS13=bbF_phi3_tautau_TH13/ip_ex_bb_phi_tautau_CMS13(m3);
        R_bbF_phi3_tautau_CMS13=(1+(bbF_phi3_tautau_TH13-ip_ex_bb_phi_tautau_CMS13(m3))/ip_ex_bb_phi_tautau_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
    }
    else if(m3>=3200.0 && m3<4000.0)
    {
        THoEX_ggF_phi3_gaga_CMS13=ggF_phi3_gaga_TH13/ip_ex_gg_phi_gaga_CMS13(m3);
        R_ggF_phi3_gaga_CMS13=(1+(ggF_phi3_gaga_TH13-ip_ex_gg_phi_gaga_CMS13(m3))/ip_ex_gg_phi_gaga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_Zga_CMS13=ggF_phi3_Zga_TH13/ip_ex_ggF_phi_Zga_CMS13(m3);
        R_ggF_phi3_Zga_CMS13=(1+(ggF_phi3_Zga_TH13-ip_ex_ggF_phi_Zga_CMS13(m3))/ip_ex_ggF_phi_Zga_CMS13_e(m3) ) * nftos;
        THoEX_ggF_phi3_WW_enumunu_ATLAS13=ggF_phi3_WW_TH13/ip_ex_gg_H_WW_enumunu_ATLAS13(m3);
        R_ggF_phi3_WW_enumunu_ATLAS13=(1+(ggF_phi3_WW_TH13-ip_ex_gg_H_WW_enumunu_ATLAS13(m3))/ip_ex_gg_H_WW_enumunu_ATLAS13_e(m3) ) * nftos;
    }
  
    
    return 0.;
} 
    


    

    
    
double GeneralTHDMcache::updateCache()
{      
    mHl=myGTHDM->getMHl();
    mH1sq=mHl*mHl;
    mH2sq=myGTHDM->getmH2sq();
    mH3sq=myGTHDM->getmH3sq();
    vev=myGTHDM->v();
    tanb=myGTHDM->gettanb();
    cosb=myGTHDM->getcosb();
    sinb=myGTHDM->getsinb();
    cosa1=myGTHDM->getcosalpha1();
    sina1=myGTHDM->getsinalpha1();
    cosa2=myGTHDM->getcosalpha2();
    sina2=myGTHDM->getsinalpha2();
    cosa3=myGTHDM->getcosalpha3();
    sina3=myGTHDM->getsinalpha3();
    Relambda5=myGTHDM->getRelambda5();
    Imlambda5=myGTHDM->getImlambda5();
    mHpsq=myGTHDM->getmH2sq();
    Relambda6=myGTHDM->getRelambda6();
    Relambda7=myGTHDM->getRelambda7();

    /*The Mij_2 are defined such that Msqdiag = -2*RT*M_2*R with the rotation Matrix R
     * and Msqdiag containing the physical mass squares on the diagonal. */

    M11_2 = -0.5*(mH1sq*cosa1*cosa1*cosa2*cosa2
                  +mH2sq*sina1*sina1*cosa2*cosa2 + mH3sq*sina2*sina2);
    M12_2 = 0.5*cosa2*((mH1sq-mH2sq)*cosa1*cosa3*sina1
                       +(-mH3sq+mH1sq*cosa1*cosa1+mH2sq*sina1*sina1)*sina2*sina3);
    M13_2 = 0.5*cosa2*(cosa3*(-mH3sq+mH1sq*cosa1*cosa1+mH2sq*sina1*sina1)*sina2
                       +(mH2sq-mH1sq)*cosa1*sina1*sina3);
    M22_2 = -0.5*(mH3sq*cosa2*cosa2*sina3*sina3
                  +mH1sq*(cosa3*sina1+cosa1*sina2*sina3)*(cosa3*sina1+cosa1*sina2*sina3)
                  +mH2sq*(cosa1*cosa3-sina1*sina2*sina3)*(cosa1*cosa3-sina1*sina2*sina3));
    M23_2 = 0.5*((mH2sq-mH1sq)*cosa1*(cosa3*cosa3-sina3*sina3)*sina1*sina2
                 +cosa1*cosa1*cosa3*(mH2sq-mH1sq*sina2*sina2)*sina3
                 -cosa3*sina3*(mH3sq*cosa2*cosa2+sina1*sina1*(-mH1sq+mH2sq*sina2*sina2)));
    M33_2 = -0.5*(mH3sq*cosa2*cosa2*cosa3*cosa3
                  +mH2sq*(cosa3*sina1*sina2+cosa1*sina3)*(cosa3*sina1*sina2+cosa1*sina3)
                  +mH1sq*(cosa1*cosa3*sina2-sina1*sina3)*(cosa1*cosa3*sina2-sina1*sina3));

    //Remaining general potential parameters
    m11sq     = M11_2 - M33_2 - M12_2*tanb + 0.5*Relambda5*vev*vev
                + (M33_2-0.5*Relambda5*vev*vev)*(cosb*cosb-sinb*sinb)
                + 0.5*vev*vev*((Relambda6-Relambda7)*sinb*cosb+Relambda7*tanb);

    m22sq     = M11_2 - M33_2 + M12_2/tanb + 0.5*Relambda5*vev*vev
                - (M33_2-0.5*Relambda5*vev*vev)*(cosb*cosb-sinb*sinb)
                + 0.25*vev*vev*(Relambda6+Relambda7+(Relambda6-Relambda7)*(cosb*cosb-sinb*sinb))/tanb;

    Rem12sq   = 0.25*vev*vev*(Relambda6+Relambda7+(Relambda6-Relambda7)*(cosb*cosb-sinb*sinb))
                - (2.0*M33_2-Relambda5*vev*vev)*sinb*cosb;

    Imm12sq   = M13_2;

    lambda1   = (-2.0*(M11_2-M22_2+M33_2) + Relambda5*vev*vev
                 - (2.0*M22_2-2.0*M33_2+Relambda5*vev*vev)/(cosb*cosb)
                 + (4.0*M12_2-2.0*Relambda6*vev*vev)*tanb)/(vev*vev);

    lambda2   = (-2.0*(M11_2-M22_2+M33_2) + Relambda5*vev*vev
                 - (2.0*M22_2-2.0*M33_2+Relambda5*vev*vev)/(sinb*sinb)
                 - (4.0*M12_2+2.0*Relambda7*vev*vev)/tanb)/(vev*vev);

    lambda3   = -(2.0*(M11_2-M22_2-M33_2-mHpsq) + Relambda5*vev*vev
                  + (2.0*M12_2+Relambda6*vev*vev)/tanb
                  - (2.0*M12_2-Relambda7*vev*vev)*tanb)/(vev*vev);

    lambda4   = Relambda5 - (2.0*mHpsq+4.0*M33_2)/(vev*vev);

    Imlambda6 = (2.0*M13_2-(2.0*M23_2+0.5*Imlambda5*vev*vev)*tanb)/(vev*vev);

    Imlambda7 = 2.0*M13_2/(vev*vev) + (-0.5*Imlambda5+(2.0*M23_2)/(vev*vev))/tanb;

    //Higgs potential parameters

    m11sqH     = M11_2;
    m22sqH     = M11_2-2.0*M33_2+Relambda5*vev*vev
                 +(M12_2+0.5*(Relambda6*vev*vev))/tanb
                 -(M12_2-0.5*(Relambda7*vev*vev))*tanb;
    Rem12sqH   = -M12_2;
    Imm12sqH   = M13_2;
    lambda1H   = -2.0*M11_2/(vev*vev);
    lambda2H   = -2.0*((2.0*M12_2+Relambda7*vev*vev)/tanb
                       +M11_2-4.0*M22_2+4.0*M33_2-2.0*Relambda5*vev*vev
                       +(M22_2-M33_2+0.5*Relambda5*vev*vev)/(sinb*sinb*cosb*cosb)
                       -2.0*M12_2*tanb+Relambda6*vev*vev*tanb)/(vev*vev);
    lambda3H   = -((2.0*(M11_2-2.0*M33_2-mHpsq+Relambda5*vev*vev)
                    +(2.0*M12_2+Relambda6*vev*vev)/tanb
                    -(2.0*M12_2-Relambda7*vev*vev)*tanb)/(vev*vev));
    lambda4H   = -2.0*(M22_2+M33_2+mHpsq)/(vev*vev);
    Relambda5H = -2.0*(M22_2-M33_2)/(vev*vev);
    Imlambda5H = 4.0*M23_2/(vev*vev);
    Relambda6H = -2.0*M12_2/(vev*vev);
    Imlambda6H = 2.0*M13_2/(vev*vev);
    Relambda7H = (-2.0*M12_2+(Relambda6-Relambda7)*vev*vev
                  +(2.0*M22_2-2.0*M33_2+Relambda5*vev*vev)*(tanb-1.0/tanb))/(vev*vev);
    Imlambda7H = 2.0*(M13_2-M23_2*(tanb-1.0/tanb))/(vev*vev)-0.5*Imlambda5/(sinb*cosb);


    M2 = Rem12sq/(sinb*cosb);



//    R11_GTHDM = cosalpha1*cosalpha2;
//    R12_GTHDM = sinalpha1*cosalpha2;
//    R13_GTHDM = -sinalpha2;
//    R21_GTHDM = cosalpha1*sinalpha2*sinalpha3 - sinalpha1*cosalpha3;
//    R22_GTHDM = sinalpha1*sinalpha2*sinalpha3 + cosalpha1*cosalpha3;
//    R23_GTHDM = cosalpha2*sinalpha3;
//    R31_GTHDM = cosalpha1*sinalpha2*cosalpha3 + sinalpha1*sinalpha3;
//    R32_GTHDM = sinalpha1*sinalpha2*cosalpha3 - cosalpha1*sinalpha3;
//    R33_GTHDM = cosalpha2*cosalpha3;

//    M13_2 = -vev*vev*(sinb*cosb*Imlambda5 + cosb*cosb*Imlambda6 + sinb*sinb*Imlambda7);
//    M23_2 = -vev*vev*((cosb*cosb - sinb*sinb)*Imlambda5 + 2.*sinb*cosb*(Imlambda7 - Imlambda6))/2.;

//        std::cout<<"mH1sq before ordering = "<<mH1sq<<std::endl;
//        std::cout<<"mH2sq before ordering = "<<mH2sq<<std::endl;
//        std::cout<<"mH3sq before ordering = "<<mH3sq<<std::endl;

    if(mH1sq<mH3sq && mH3sq<mH2sq)
    {
        //1<3<2 swap 2 and 3
        mHlight_2  = mH1sq;
        mHmedium_2 = mH3sq;
        mHheavy_2  = mH2sq;
    }
    else if(mH3sq<mH2sq && mH2sq<mH1sq)
    {
        //3<2<1 swap 1 and 3
        mHlight_2  = mH3sq;
        mHmedium_2 = mH2sq;
        mHheavy_2  = mH1sq;
    }
    else if(mH2sq<mH1sq && mH1sq<mH3sq)
    {
        //2<1<3 swap 1 and 2
        mHlight_2  = mH2sq;
        mHmedium_2 = mH1sq;
        mHheavy_2  = mH3sq;
    }
    else if(mH2sq<mH3sq && mH3sq<mH1sq)
    {
        //2<3<1: 3->2, 1->3, 2->1
        mHlight_2  = mH2sq;
        mHmedium_2 = mH3sq;
        mHheavy_2  = mH1sq;
    }
    else if(mH3sq<mH1sq && mH1sq<mH2sq)
    {
        //3<1<2 3->1, 1->2, 2->3
        mHlight_2  = mH3sq;
        mHmedium_2 = mH1sq;
        mHheavy_2  = mH2sq;
    }
    
    else if(mH1sq<mH2sq && mH2sq<mH3sq)
    {
        //1<2<3 ok
        mHlight_2  = mH1sq;
        mHmedium_2 = mH2sq;
        mHheavy_2  = mH3sq;
    }

//    M11_2 = (mH1sq*cosalpha1*cosalpha1*cosalpha2*cosalpha2 + mH2sq*sinalpha1*sinalpha1*cosalpha2*cosalpha2 + mH3sq*sinalpha2*sinalpha2);
//
//    M12_2 = (mH1sq*cosalpha1*cosalpha2*(cosalpha1*sinalpha2*sinalpha3 - cosalpha3*sinalpha1)
//             + mH2sq*cosalpha2*sinalpha1*(cosalpha1*cosalpha3 + sinalpha1*sinalpha2*sinalpha3)
//             - mH3sq*cosalpha2*sinalpha2*sinalpha3);
//
////    M13_2 = ?
//
//    M22_2 = (mH1sq*(cosalpha1*sinalpha2*sinalpha3 - cosalpha3*sinalpha1)*(cosalpha1*sinalpha2*sinalpha3 - cosalpha3*sinalpha1)
//             + mH2sq*(cosalpha1*cosalpha3 + sinalpha1*sinalpha2*sinalpha3)*(cosalpha1*cosalpha3 + sinalpha1*sinalpha2*sinalpha3)
//             + mH3sq*cosalpha2*cosalpha2*sinalpha3*sinalpha3);
//
////    M23_2 = ?
//
//    M33_2 = (mH1sq*(cosalpha1*cosalpha3*sinalpha2 + sinalpha1*sinalpha3)*(cosalpha1*cosalpha3*sinalpha2 + sinalpha1*sinalpha3)
//             + mH2sq*(cosalpha3*sinalpha1*sinalpha2 - cosalpha1*sinalpha3)*(cosalpha3*sinalpha1*sinalpha2 - cosalpha1*sinalpha3)
//             + mH3sq*cosalpha2*cosalpha2*cosalpha3*cosalpha3);
//
//    m11_2_GTHDM = M2_GTHDM*(1. - cosb*cosb + 3.*sinb*sinb)/4. + (M12_2*tanb - M11_2)/2.;
//    m22_2_GTHDM = M2_GTHDM*(1. + 3.*cosb*cosb - sinb*sinb)/4. - (M12_2/tanb + M11_2)/2.;
//    Imm12_2_GTHDM = 0.5*(cosb*sinb*Imlambda5 + cosb*cosb*Imlambda6 + sinb*sinb*Imlambda7)*vev*vev;
//    lambda1_GTHDM = (M11_2 + tanb*tanb*(M22_2-M2_GTHDM) - 2.0*tanb*M12_2)/(vev*vev) + tanb*(tanb*tanb*Relambda7 - 3.0*Relambda6)/2.0;
//    lambda2_GTHDM = (M11_2 + (M22_2-M2_GTHDM)/(tanb*tanb) + 2.0*M12_2/tanb)/(vev*vev) + (0.5*Relambda6/(tanb*tanb) - 1.5*Relambda7)/tanb;
//    lambda3_GTHDM = (M11_2 - M22_2 - M2_GTHDM + (1.0/tanb - tanb)*M12_2 + 2.0*mHpsq)/(vev*vev) - (Relambda6/tanb + tanb*Relambda7)/2.0;
//    lambda4_GTHDM = (M2_GTHDM + M33_2 - 2.0*mHpsq)/(vev*vev) - 0.5*(Relambda6/tanb + tanb*Relambda7);
//    Relambda5_GTHDM = (M2_GTHDM - M33_2)/(vev*vev) - 0.5*(Relambda6/tanb + tanb*Relambda7);
//    
    
    //Parameters in the potential in the Higgs basis, as defined in 1106.0034, Eq. (119)-(129)
    
    maa_2_GTHDM = m11sq*cosb*cosb + m22sq*sinb*sinb - Rem12sq*(2.0*sinb*cosb);
    mbb_2_GTHDM = m22sq*sinb*sinb + m22sq*cosb*cosb + Rem12sq*(2.0*sinb*cosb);
    Remab_2_GTHDM = (m11sq - m22sq)*(2.0*sinb*cosb)/2.0 + Rem12sq*(cosb*cosb - sinb*sinb);
    Immab_2_GTHDM = Imm12sq;

    lambdaa_GTHDM = lambda1 *cosb*cosb*cosb*cosb + lambda2 *sinb*sinb*sinb*sinb 
            + (1.0/2.0)*(lambda3 + lambda4 +Relambda5 )*(2.0*sinb*cosb)*(2.0*sinb*cosb) 
            + 2.0*(2.0*sinb*cosb)*(cosb*cosb*Relambda6 + sinb*sinb*Relambda7);
    lambdab_GTHDM = lambda1 *sinb*sinb*sinb*sinb + lambda2 *cosb*cosb*cosb*cosb 
            + (1.0/2.0)*(lambda3 + lambda4 +Relambda5 )*(2.0*sinb*cosb)*(2.0*sinb*cosb) 
            - 2.0*(2.0*sinb*cosb)*(sinb*sinb*Relambda6 + cosb*cosb*Relambda7);
    lambdac_GTHDM = lambda3 +(1.0/4.0)*(2.0*sinb*cosb)*(2.0*sinb*cosb)*(lambda1 +lambda2  - 2.0*(lambda3 + lambda4 +Relambda5 ))
               - (2.0*sinb*cosb)*(cosb*cosb - sinb*sinb)*(Relambda6 - Relambda7);
    lambdad_GTHDM = lambda4 +(1.0/4.0)*(2.0*sinb*cosb)*(2.0*sinb*cosb)*(lambda1 +lambda2  - 2.0*(lambda3 + lambda4 +Relambda5 ))
            - (2.0*sinb*cosb)*(cosb*cosb - sinb*sinb)*(Relambda6 - Relambda7);
     Relambdae_GTHDM = (1.0/4.0)*(2.0*sinb*cosb)*(2.0*sinb*cosb)*(lambda1 +lambda2  - 2.0*(lambda3 + lambda4 +Relambda5 ))
            + Relambda5  - (2.0*sinb*cosb)*(cosb*cosb - sinb*sinb)*(Relambda6-Relambda7);
     Imlambdae_GTHDM = (cosb*cosb - sinb*sinb)*(Imlambda5) -(2.0*sinb*cosb)*(Imlambda6-Imlambda7);
    Relambdaf_GTHDM  = -(1.0/2.0)*(2.0*sinb*cosb)*(lambda1 *cosb*cosb - lambda2 *sinb*sinb -(lambda3 + lambda4 +Relambda5 )*(cosb*cosb - sinb*sinb))
            +cosb*(cosb*cosb*cosb - 3.0*sinb*sinb*cosb)*Relambda6 + sinb*(3.0*sinb*cosb*cosb - sinb*sinb*sinb)*Relambda7;
     Imlambdaf_GTHDM =  (1.0/2.0)*(2.0*sinb*cosb)*Imlambda5 + cosb*cosb*Imlambda6 + sinb*sinb*Imlambda7;
    Relambdag_GTHDM = -(1.0/2.0)*(2.0*sinb*cosb)*(lambda1 *sinb*sinb - lambda2 *cosb*cosb + (lambda3 + lambda4 +Relambda5 )*(cosb*cosb - sinb*sinb) )
            +sinb*(3.0*sinb*cosb*cosb - sinb*sinb*sinb)*Relambda6 +cosb*(cosb*cosb*cosb - 3.0*sinb*sinb*cosb)*Relambda7; 
     Imlambdag_GTHDM = -(1.0/2.0)*(2.0*sinb*cosb)*Imlambda5+ sinb*sinb*Imlambda6 + cosb*cosb*Imlambda7;
          
   
    
    Mu_GTHDM.assign(0,0, myGTHDM->getQuarks(QCD::UP).getMass());
    Mu_GTHDM.assign(1,1, myGTHDM->getQuarks(QCD::CHARM).getMass());
    Mu_GTHDM.assign(2,2, myGTHDM->getQuarks(QCD::TOP).getMass());
    
    Md_GTHDM.assign(0,0, myGTHDM->getQuarks(QCD::DOWN).getMass());
    Md_GTHDM.assign(1,1, myGTHDM->getQuarks(QCD::STRANGE).getMass());
    Md_GTHDM.assign(2,2, myGTHDM->getQuarks(QCD::BOTTOM).getMass());
    
    Ml_GTHDM.assign(0,0, myGTHDM->getLeptons(StandardModel::ELECTRON).getMass());
    Ml_GTHDM.assign(1,1, myGTHDM->getLeptons(StandardModel::MU).getMass());
    Ml_GTHDM.assign(2,2, myGTHDM->getLeptons(StandardModel::TAU).getMass());
    
    if(myGTHDM->getATHDMflag() == true)
    {
        sigmau_ATHDM = myGTHDM->getNu_33()/myGTHDM->getQuarks(StandardModel::TOP).getMass();
        sigmad_ATHDM = myGTHDM->getNd_33()/myGTHDM->getQuarks(StandardModel::DOWN).getMass();
        sigmal_ATHDM = myGTHDM->getNl_33()/myGTHDM->getLeptons(StandardModel::TAU).getMass();
        
        Nu_GTHDM.assign(0,0, sigmau_ATHDM*Mu_GTHDM(0,0));
        Nu_GTHDM.assign(1,1, sigmau_ATHDM*Mu_GTHDM(1,1));
        Nu_GTHDM.assign(2,2, sigmau_ATHDM*Mu_GTHDM(2,2));
        
        Nd_GTHDM.assign(0,0, sigmad_ATHDM*Mu_GTHDM(0,0));
        Nd_GTHDM.assign(1,1, sigmad_ATHDM*Md_GTHDM(1,1));
        Nd_GTHDM.assign(2,2, sigmad_ATHDM*Mu_GTHDM(2,2));
        
        Nl_GTHDM.assign(0,0, sigmal_ATHDM*Ml_GTHDM(0,0));
        Nl_GTHDM.assign(1,1, sigmal_ATHDM*Ml_GTHDM(1,1));
        Nl_GTHDM.assign(2,2, sigmal_ATHDM*Ml_GTHDM(2,2));
    }
    else
    {
        Nu_GTHDM.assign(0,0, myGTHDM->getNu_11());
        Nu_GTHDM.assign(0,1, myGTHDM->getNu_12());
        Nu_GTHDM.assign(0,2, myGTHDM->getNu_13());
        Nu_GTHDM.assign(1,0, myGTHDM->getNu_21());
        Nu_GTHDM.assign(1,1, myGTHDM->getNu_22());
        Nu_GTHDM.assign(1,2, myGTHDM->getNu_23());
        Nu_GTHDM.assign(2,0, myGTHDM->getNu_31());
        Nu_GTHDM.assign(2,1, myGTHDM->getNu_32());
        Nu_GTHDM.assign(2,2, myGTHDM->getNu_33());
    
        Nd_GTHDM.assign(0,0, myGTHDM->getNd_11());
        Nd_GTHDM.assign(0,1, myGTHDM->getNd_12());
        Nd_GTHDM.assign(0,2, myGTHDM->getNd_13());
        Nd_GTHDM.assign(1,0, myGTHDM->getNd_21());
        Nd_GTHDM.assign(1,1, myGTHDM->getNd_22());
        Nd_GTHDM.assign(1,2, myGTHDM->getNd_23());
        Nd_GTHDM.assign(2,0, myGTHDM->getNd_31());
        Nd_GTHDM.assign(2,1, myGTHDM->getNd_32());
        Nd_GTHDM.assign(2,2, myGTHDM->getNd_33());
    
        Nl_GTHDM.assign(0,0, myGTHDM->getNl_11());
        Nl_GTHDM.assign(0,1, myGTHDM->getNl_12());
        Nl_GTHDM.assign(0,2, myGTHDM->getNl_13());
        Nl_GTHDM.assign(1,0, myGTHDM->getNl_21());
        Nl_GTHDM.assign(1,1, myGTHDM->getNl_22());
        Nl_GTHDM.assign(1,2, myGTHDM->getNl_23());
        Nl_GTHDM.assign(2,0, myGTHDM->getNl_31());
        Nl_GTHDM.assign(2,1, myGTHDM->getNl_32());
        Nl_GTHDM.assign(2,2, myGTHDM->getNl_33());
    }
       
    //Definition of Yukawa matrices
    Yu1_GTHDM = (cosb*Mu_GTHDM - sinb*Nu_GTHDM)*sqrt(2.)/vev;
    Yu2_GTHDM = (cosb*Nu_GTHDM + sinb*Mu_GTHDM)*sqrt(2.)/vev;
    Yd1_GTHDM = (cosb*Md_GTHDM - sinb*Nd_GTHDM)*sqrt(2.)/vev;
    Yd2_GTHDM = (cosb*Nd_GTHDM + sinb*Md_GTHDM)*sqrt(2.)/vev;
    Yl1_GTHDM = (cosb*Ml_GTHDM - sinb*Nl_GTHDM)*sqrt(2.)/vev;
    Yl2_GTHDM = (cosb*Nl_GTHDM + sinb*Ml_GTHDM)*sqrt(2.)/vev;

//    std::cout<<"mH1sq = "<<mH1sq<<std::endl;
//    std::cout<<"mH2sq = "<<mH2sq<<std::endl;
//    std::cout<<"mH3sq = "<<mH3sq<<std::endl;
//    std::cout<<"M11_2 = "<<M11_2<<std::endl;
//    std::cout<<"M12_2 = "<<M12_2<<std::endl;
//    std::cout<<"M22_2 = "<<M22_2<<std::endl;
//    std::cout<<"M33_2 = "<<M33_2<<std::endl;
//    std::cout<<"m11_2_GTHDM = "<<m11_2_GTHDM<<std::endl;
//    std::cout<<"m22_2_GTHDM = "<<m22_2_GTHDM<<std::endl;
//    std::cout<<"Imm12_2_GTHDM = "<<Imm12_2_GTHDM<<std::endl;
//    std::cout<<"lambda1_GTHDM = "<<lambda1_GTHDM<<std::endl;
//    std::cout<<"lambda2_GTHDM = "<<lambda2_GTHDM<<std::endl;
//    std::cout<<"lambda3_GTHDM = "<<lambda3_GTHDM<<std::endl;
//    std::cout<<"lambda4_GTHDM = "<<lambda4_GTHDM<<std::endl;
//    std::cout<<"Relambda5_GTHDM = "<<Relambda5_GTHDM<<std::endl;
        
//    Q_THDM=myTHDM->getQ_THDM();
////    m12_2=myTHDM->getm12_2();
//    MW=MWTHDM(myTHDM->Mw_tree());
//    cW2=cW2THDM(myTHDM->c02());
//    Ale=myTHDM->getAle();
//    Als=myTHDM->getAlsMz();
//    Mt=myTHDM->getQuarks(QCD::TOP).getMass();
//    Mb=myTHDM->getQuarks(QCD::BOTTOM).getMass();   
//    Mtau=myTHDM->getLeptons(StandardModel::TAU).getMass();
//    Mc=myTHDM->getQuarks(QCD::CHARM).getMass();
//    Ms=myTHDM->getQuarks(QCD::STRANGE).getMass();
//    Mmu=myTHDM->getLeptons(StandardModel::MU).getMass();
//    Mu=myTHDM->getQuarks(QCD::UP).getMass();
//    Md=myTHDM->getQuarks(QCD::DOWN).getMass();
//    Me=myTHDM->getLeptons(StandardModel::ELECTRON).getMass();
//    MZ=myTHDM->getMz();
//    modelflag=myTHDM->getModelTypeflag();
//    WFRflag=myTHDM->getWFRflag();
    
    


    computeSignalStrengths();
    computephi2quantities();
    computephi3quantities();
    ComputeHeavyHiggs();
    ComputeMediumHiggs();
 
    return mH1sq;
}
