/* 
 * File:   EWSMTwoFermionsLEP2.cpp
 * Author: mishima
 */

#include <stdexcept>
#include <cmath>
#include "EWSMTwoFermionsLEP2.h"
#include "EWSMThreeLoopEW.h"


EWSMTwoFermionsLEP2::EWSMTwoFermionsLEP2(const StandardModel& SM_i) : SM(SM_i), 
        myCache(SM_i), myOneLoopEW(myCache) {
    bDebug = SM_i.isBDebug();
}


//////////////////////////////////////////////////////////////////////// 

complex EWSMTwoFermionsLEP2::Vpol_inv(const double s) const {
    complex V_inv;
    if (bDebug)
        V_inv = 1.0/complex(1.0715119759, -0.0186242179, false); // for debug
    else {
        //!!!!!!
        V_inv = SM.getAle()/SM.alphaMz(); //!!TEST
        //V_inv = 1.0 - SM.DeltaAlphaLepton(s) - SM.getDAle5Mz(); // !!TEST
        //V_inv = 1.0 - myOneLoopEW.DeltaAlpha_l(s) - SM.getDAle5Mz()
        //        - myOneLoopEW.DeltaAlpha_t(s);
        //V_inv = 1.0/complex(1.0715119759, 0.0, false); //!!TEST
        //V_inv = 1.0/complex(1.0715119759, -0.0186242179, false); //!!TEST
        //!!!!!!
    }
    return V_inv;    
}


complex EWSMTwoFermionsLEP2::chi_Z(const double s, const double Mw, 
                                   const double GammaZ) const {
    double Mz = SM.getMz();
    complex denom = complex(s - Mz*Mz, GammaZ/Mz*s, false);
    double prefactor = SM.getGF()*Mz*Mz/(sqrt(2.0)*8.0*M_PI*SM.getAle());
    
    return ( prefactor*s/denom );
}

    
complex EWSMTwoFermionsLEP2::rho_ef(const double s, const double Mw, const double I3f, 
                                    const double Qf, const double mfp) const {
    complex G = complex(1.0, 0.0, false);
    
    return G;       
}

complex EWSMTwoFermionsLEP2::kappa_e(const double s, const double Mw, const double I3f, 
                                     const double Qf) const {
    complex G = complex(1.0, 0.0, false);
    
    return G;       
}


complex EWSMTwoFermionsLEP2::kappa_f(const double s, const double Mw, const double I3f, 
                                     const double Qf, const double mfp) const {
    complex G = complex(1.0, 0.0, false);
    
    return G;       
}


complex EWSMTwoFermionsLEP2::kappa_ef(const double s, const double Mw, const double I3f, 
                                      const double Qf, const double mfp) const {
    complex G = complex(1.0, 0.0, false);
    
    return G;       
}


complex EWSMTwoFermionsLEP2::I2e(const double s, const double Mw, const double I3f, 
                                 const double Qf) const {
    double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
    double alpha = SM.getAle()/Vpol_inv(s).real();
    double ReKappa_e = 1.0;
    return ( 35.0*alpha*alpha/18.0*( 1.0 - 8.0/3.0*ReKappa_e*sW2 ) );
}


complex EWSMTwoFermionsLEP2::I2f(const double s, const double Mw, const double I3f, 
                                 const double Qf, const double mfp) const {
    double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
    double alpha = SM.getAle()/Vpol_inv(s).real();
    double ReKappa_f = 1.0;
    return ( 35.0*alpha*alpha/18.0*( 1.0 - 8.0/3.0*ReKappa_f*sW2 ) );
}


complex EWSMTwoFermionsLEP2::G_e(const double s, const double Mw, const double I3f, 
                                 const double Qf) const {
    double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
    return ( 1.0 - 4.0*( kappa_e(s,Mw,I3f,Qf)*sW2 + I2e(s,Mw,I3f,Qf)) ); 
}


complex EWSMTwoFermionsLEP2::G_f(const double s, const double Mw, const double I3f, 
                                 const double Qf, const double mfp) const {
    double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
    return ( 1.0 - 4.0*fabs(Qf)*( kappa_f(s,Mw,I3f,Qf,mfp)*sW2 + I2f(s,Mw,I3f,Qf,mfp)) );     
}


complex EWSMTwoFermionsLEP2::G_ef(const double s, const double Mw, const double I3f, 
                                  const double Qf, const double mfp) const {
    double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
    return ( - 1.0 + G_e(s,Mw,I3f,Qf) + G_f(s,Mw,I3f,Qf,mfp) 
             + 16.0*fabs(Qf)
               *( kappa_ef(s,Mw,I3f,Qf,mfp)*sW2*sW2 
                 + (kappa_e(s,Mw,I3f,Qf)*I2e(s,Mw,I3f,Qf) 
                    + kappa_f(s,Mw,I3f,Qf,mfp)*I2f(s,Mw,I3f,Qf,mfp))*sW2 ) );
}

   
double EWSMTwoFermionsLEP2::G_1(const double s, const double Mw, 
                                const double GammaZ, const double I3f, 
                                const double Qf, const double mfp,
                                const bool bWeak) const {
    complex Vpol = 1.0/Vpol_inv(s);
    complex rhoef, Ge, Gf, Gef;
    if (bWeak) {
        rhoef = rho_ef(s, Mw, I3f, Qf, mfp);
        Ge = G_e(s, Mw, I3f, Qf);
        Gf = G_f(s, Mw, I3f, Qf, mfp);
        Gef = G_ef(s, Mw, I3f, Qf, mfp);
    } else {
        double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
        rhoef = 1.0;
        Ge = 1.0 - 4.0*sW2;
        Gf = 1.0 - 4.0*fabs(Qf)*sW2;
        Gef = - 1.0 + Ge + Gf + 16.0*fabs(Qf)*sW2*sW2;
    }
    
    return ( Qf*Qf*Vpol.abs2() 
             + 2.0*fabs(Qf)*(Vpol.conjugate()*rhoef*Gef*chi_Z(s,Mw,GammaZ)).real() 
             + rhoef.abs2()*(Gef.abs2() + Gf.abs2() + Ge.abs2() + 1.0) 
               *chi_Z(s,Mw,GammaZ).abs2() );
}


double EWSMTwoFermionsLEP2::G_2(const double s, const double Mw, 
                                const double GammaZ, const double I3f, 
                                const double Qf, const double mfp,
                                const bool bWeak) const {
    complex Vpol = 1.0/Vpol_inv(s);
    complex rhoef, Ge, Gf, Gef;
    if (bWeak) {
        rhoef = rho_ef(s, Mw, I3f, Qf, mfp);
        Ge = G_e(s, Mw, I3f, Qf);
        Gf = G_f(s, Mw, I3f, Qf, mfp);
        Gef = G_ef(s, Mw, I3f, Qf, mfp);
    } else {
        double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
        rhoef = 1.0;
        Ge = 1.0 - 4.0*sW2;
        Gf = 1.0 - 4.0*fabs(Qf)*sW2;
        Gef = - 1.0 + Ge + Gf + 16.0*fabs(Qf)*sW2*sW2;
    }   

    return ( Qf*Qf*Vpol.abs2() 
             + 2.0*fabs(Qf)*(Vpol.conjugate()*rhoef*Gef*chi_Z(s,Mw,GammaZ)).real() 
             + rhoef.abs2()*(Gef.abs2() + Gf.abs2())*chi_Z(s,Mw,GammaZ).abs2() ); 
}


double EWSMTwoFermionsLEP2::G_3(const double s, const double Mw, 
                                const double GammaZ, const double I3f, 
                                const double Qf, const double mfp,
                                const bool bWeak) const {
    complex Vpol = 1.0/Vpol_inv(s);
    complex rhoef, Ge, Gf, Gef;
    if (bWeak) {
        rhoef = rho_ef(s, Mw, I3f, Qf, mfp);
        Ge = G_e(s, Mw, I3f, Qf);
        Gf = G_f(s, Mw, I3f, Qf, mfp);
        Gef = G_ef(s, Mw, I3f, Qf, mfp);
    } else {
        double Mz = SM.getMz(), sW2 = 1.0 - Mw*Mw/(Mz*Mz);
        rhoef = 1.0;
        Ge = 1.0 - 4.0*sW2;
        Gf = 1.0 - 4.0*fabs(Qf)*sW2;
        Gef = - 1.0 + Ge + Gf + 16.0*fabs(Qf)*sW2*sW2;
    }  

    return ( 2.0*fabs(Qf)*(Vpol.conjugate()*chi_Z(s,Mw,GammaZ)).real() 
             + 2.0*(Ge*Gf.conjugate() + Gef).real()*chi_Z(s,Mw,GammaZ).abs2() );
}


////////////////////////////////////////////////////////////////////////




