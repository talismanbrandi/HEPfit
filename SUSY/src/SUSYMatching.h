/* 
 * File:   SUSYMatching.h
 * Author: girardi_mac
 *
 * Created on 14 maggio 2012, 11.53
 */

#ifndef SUSYMATCHING_H
#define	SUSYMATCHING_H

#include "SUSY.h"
#include "StandardModelMatching.h"

#define LEPS 1.e-5     // tolerance in the limit of S(x,y) to S(x) 
#define SUSYLEPS 1.e-5 // tolerance in the limits of D0[x,y,z,t] and D2[x,y,z,t]
       


class SUSYMatching : public StandardModelMatching{
public:
    SUSYMatching(const SUSY & SUSY_i);
    
    /**
     * 
     * @brief \f$ \Delta B = 2 \f$, \f$ B_{d} \f$ 
     * @return return the vector of SUSY Wilson coefficients
     */
    virtual const std::vector<WilsonCoefficient>& CMdbd2();
    
    /**
     * 
     * @brief \f$ \Delta B = 2 \f$, \f$ B_{s} \f$ 
     * @return return the vector of SUSY Wilson coefficients
     */
    virtual const std::vector<WilsonCoefficient>& CMdbs2();
    
//    /**
//     * 
//     * @brief \f$ \Delta C = 2 \f$,
//     * @return return the vector of SUSY Wilson coefficients
//     */
    virtual const std::vector<WilsonCoefficient>& CMdd2();
    
    /**
     * 
     * @brief \f$ \Delta S = 2 \f$ 
     * @return return the vector of SUSY Wilson coefficients
     */
    virtual const std::vector<WilsonCoefficient>& CMdk2();
    
//    /** 
//     * 
//     * @brief operator basis: 
//     * @brief current current; qcd penguins; magnetic and chromomagnetic penguins; semileptonic  
//     * @param a, a=0 deltaS=0 deltaC=0;  a=1 deltaS=1 deltaC=0;
//     * @return Wilson coefficients Buras base for non-leptonic B decays 
//     */
//    virtual const std::vector<WilsonCoefficient>& CMbnlep(const int& a);
//    
//    /**
//     * 
//     * @brief operator basis: - current current opertors  
//     * @param a, a=0 deltaS=0 deltaC=0;  a=1 1,0 ;  a=2 0,1 ; a=3 1,1 
//     * @return Wilson coefficients, Buras basis, for non-leptonic B decays 
//     */
//    virtual const std::vector<WilsonCoefficient>& CMbnlepCC(const int& a);
    
    /** 
     * 
     * @brief operator basis: current current; qcd penguins; 
     * magnetic and chromomagnetic penguins; semileptonic 
     * @return Wilson coefficients, Misiak basis, for \f$ B \rightarrow X_{s} \gamma, l^{+} l{-} \f$
     */
    virtual const std::vector<WilsonCoefficient>& CMbsg();
    
//    /**
//     * 
//     * @brief current-current oerators, Misiak basis
//     * @return Wilson coefficients for \f$ D^{0} \rightarrow \pi \pi , K K \f$
//     */
//    virtual const std::vector<WilsonCoefficient>& CMd1();
//    
//    /**
//     * 
//     * @brief current-current oerators, Buras basis
//     * @return Wilson coefficients for \f$ D^{0} \rightarrow \pi \pi , K K \f$
//     */
//    virtual const std::vector<WilsonCoefficient>& CMd1Buras();

   
    /** Large tan beta correction to CKM, down-quark mass **/
    
    void Comp_DeltaMd();
    void Comp_mySUSY_CKM();
    
    /** Quark Masses run to the SUSY scale Q **/
    void Comp_mySUSYMQ();
    
    

private:
    const SUSY & mySUSY;
    WilsonCoefficient mcdbd2, mcdbd2Hp, mcdbd2gg, mcdbd2ChiChi, mcdbd2Chi0Chi0, mcdbd2Chi0g,
                      mcdbd2HpT, mcdbd2ggT, mcdbd2ChiChiT, mcdbd2Chi0Chi0T, mcdbd2Chi0gT;
    WilsonCoefficient mcdbs2, mcdbs2Hp, mcdbs2gg, mcdbs2ChiChi, mcdbs2Chi0Chi0, mcdbs2Chi0g,
                      mcdbs2HpT, mcdbs2ggT, mcdbs2ChiChiT, mcdbs2Chi0Chi0T, mcdbs2Chi0gT;
    WilsonCoefficient mcdk2, mcdk2Hp, mcdk2gg, mcdk2ChiChi, mcdk2Chi0Chi0, mcdk2Chi0g,
                      mcdk2HpT, mcdk2ggT, mcdk2ChiChiT, mcdk2Chi0Chi0T, mcdk2Chi0gT;
    WilsonCoefficient mcdd2, mcdd2Hp, mcdd2gg, mcdd2ChiChi, mcdd2Chi0Chi0, mcdd2Chi0g,
                      mcdd2HpT, mcdd2ggT, mcdd2ChiChiT, mcdd2Chi0Chi0T, mcdd2Chi0gT;
    
    WilsonCoefficient mcbsg, mcbnlep, mcbnlepCC, mcd1, mcd1Buras;
    
    
    
    std::vector<WilsonCoefficient> vmdbd2;                           
    std::vector<WilsonCoefficient> vmdbs2;
    std::vector<WilsonCoefficient> vmdk2;
    std::vector<WilsonCoefficient> vmdd2;
    std::vector<WilsonCoefficient> vmcbsg;
    
    /** Passarino Veltman functions, Dk with k = 0,2 , and their limits **/
    
    gslpp::complex Dk(double x, double y, double z, double t,int k);
    
    double DL(double a, double b, double c,int k);
    double DLL(double a, double b,int k);
    double DLLp(double a, double b,int k);
    double DLLL(double a,int k);
    
    
    /** Calcolous of Charged Higgs contributions **/
    gslpp::vector<complex> CdF2dHp(int b, int q, int Dmixingflag);
    
    /** Calcolous Gluinos Box **/
    gslpp::vector<complex> CdF2dgg(int b, int q, int Dmixingflag);
    
    /** Calcolous Neutralino - Gluino Box **/
    gslpp::vector<complex> CdF2dChi0g(int b, int q, int Dmixingflag);
    
    /** Calcolous Charginos contribution to Wilson Coefficents **/
    gslpp::vector<complex> CdF2dChiChi(int b, int q, int Dmixingflag);
    
    /** Calcolous Neutralino contribution to Wilson Coefficents **/
    gslpp::vector<complex> CdF2dChi0Chi0(int b, int q, int Dmixingflag);
    
    /** Feynmann rule for the Chargino - down quark - up squarks vertex with tan beta correction  **/
    gslpp::complex VChiUdL(int j, int k, int b);
    gslpp::complex VdUCL(int b, int k, int j);
    gslpp::complex VdUCR(int b, int k, int j, int flag);
    
    /** Feynmann rule for the Neutralino - down quark - down squarks vertex with tan beta correction  **/
    gslpp::complex VdDNL(int b, int k, int j, int flag);
    gslpp::complex VdDNR(int b, int k, int j, int flag);
    
    /** Feynmann rule for the Chargino - up quark - down squarks vertex with tan beta correction  **/
    gslpp::complex VuDCL(int b, int k, int j);
    gslpp::complex VuDCR(int b, int k, int j);
    
    /** Vertices Neutralino (N) - up quark (u) - up squarks (U) from Buras arXiv:hep-ph/0210145v2 
        in SLHA convention usefull in D - Dbar mixing **/
    
    gslpp::complex VuUN(int b, int k, int j, const std::string);
  
  
    /** Rules to include in the same formulas the D - D bar mixing  **/
    gslpp::complex VdUCL(int b, int k, int j, int Dmixingflag);
    gslpp::complex VdUCR(int b, int k, int j, int flag, int Dmixingflag);
    
    gslpp::complex VdDNL(int b, int k, int j, int flag, int Dmixingflag);
    gslpp::complex VdDNR(int b, int k, int j, int flag, int Dmixingflag);
    
    
    
    
    
    
    
    
    double CL(double a, double b, int k);
    double CLL(double a, int k);
    double Ck(double x, double y, double z,int k);
    double BL(double a, int k);
    double Bk(double x, double y, int k);
    
    gslpp::complex DeltaMd(int J, int I);
    
    
    gslpp::complex Eps_J(int J);
    gslpp::complex Lambda0EpsY(int J, int I);
    gslpp::complex DeltaDL(int J, int I);
    gslpp::complex DeltaDR(int J, int I);
    
    
    gslpp::complex xdS(int S);
    gslpp::complex xuS(int S);
    gslpp::complex XRLS(int J, int I, int S);
    gslpp::complex XLRS(int J, int I, int S);
    
    
   
    
    gslpp::complex PHLR(int j, int i);
    gslpp::complex DeltaFHL(int j, int i);
    gslpp::complex PHRL(int j, int i);
    gslpp::complex VUDHH(int i, int j);
    gslpp::complex PGLR(int j, int i);
    gslpp::complex PGRL(int j, int i);
    gslpp::complex PLRk(int j, int i, int k);
    gslpp::complex PRLk(int j, int i, int k);
    
    gslpp::complex PRLk(int j, int i, int k, int Dmixingflag);
    gslpp::complex PLRk(int j, int i, int k, int Dmixingflag);
    
    gslpp::matrix<complex> mySUSY_CKM();
    
    gslpp::complex EpsPrime(int J, int I);
    gslpp::vector<complex> CalcC7(int b, int q);
    double F7k(double x, int k);
   
    
    gslpp::matrix<complex> myCKM_cache;
    gslpp::matrix<complex> DeltaMd_cache;
    gslpp::vector<double> mySUSYMQ;
    
    double CWbsgArrayLO[10], CWbsgArrayNLO[10];
    double CWD1ArrayLO[10], CWD1ArrayNLO[10];
    double CWbnlepArrayLOqcd[10], CWbnlepArrayNLOqcd[10];
    double CWbnlepArrayLOew[10], CWbnlepArrayNLOew[10];
    
    double sw, swa, swb, swc; //sen(theta_W) tree level
    double xcachea, xcacheb, xcachec; // caching
};

#endif	/* SUSYMATCHING_H */

