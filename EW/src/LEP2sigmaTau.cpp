/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <Math/Functor.h>
#include <Math/Integrator.h>
#include <Math/AllIntegrationTypes.h>
#include "LEP2sigmaTau.h"


double LEP2sigmaTau::computeThValue() 
{ 
    Mw = SM.Mw(); 
    GammaZ = myEW.Gamma_Z();

    if (!checkSMparams(s, Mw, GammaZ)) {
        ml_cache = m_l(SM.TAU);        

        if (!flag[ISR])
            SMresult_cache = sigma_NoISR_l();
        else {
            ROOT::Math::Functor1D wf(this, &LEP2sigmaTau::Integrand_sigmaWithISR_l);
            ROOT::Math::Integrator ig(wf, ROOT::Math::IntegrationOneDim::kADAPTIVESINGULAR);
            ig.SetAbsTolerance(1.E-14); // desired absolute error
            ig.SetRelTolerance(1.E-4); // desired relative error
            SMresult_cache = ig.Integral(0.0, 1.0-0.85*0.85); // interval
            //std::cout << SMresult_cache << " +- " << ig.Error() << std::endl;
            // results: 6.8e-9 -- 2.2e-8
        }
                
        if (flag[WeakBox]) {
            ROOT::Math::Functor1D wf_box(this, &LEP2sigmaTau::Integrand_dsigmaBox_l);
            ROOT::Math::Integrator ig_box(wf_box, ROOT::Math::IntegrationOneDim::kADAPTIVESINGULAR);
            ig_box.SetAbsTolerance(1.E-17); // desired absolute error
            ig_box.SetRelTolerance(1.E-4); // desired relative error
            double sigma_box = ig_box.Integral(-1.0, 1.0); // interval
            SMresult_cache += sigma_box;
            //std::cout << sigma_box << " +- " << ig_box.Error() << std::endl;
            // results: 3.6e-12 -- 2.9e-10
        }

        if ( checkLEP2NP() && !bSigmaForAFB && SM.IsFlagFixedAllSMparams() ) {
            double ObParam[7];
            for (int i=0; i<7; i++) {
                SetObParam((LEP2oblique::Oblique)i, ObParam);
                Coeff_cache[i] 
                    = myLEP2oblique.sigma_l_LEP2_NP(StandardModel::TAU, s, ml_cache, ObParam);
            }
        }
    }
    double sigma_tau = SMresult_cache;
    
    #ifdef LEP2TEST
    sigma_tau = myTEST.sigmaTauTEST(sqrt_s)/GeVminus2_to_nb/1000.0;
    #endif 
    
    if ( checkLEP2NP() && !bSigmaForAFB ) {
        double obliqueShat = (static_cast<const NPbase*> (&SM))->obliqueShat();
        double obliqueThat = (static_cast<const NPbase*> (&SM))->obliqueThat();
        double obliqueUhat = (static_cast<const NPbase*> (&SM))->obliqueUhat();
        double obliqueV = (static_cast<const NPbase*> (&SM))->obliqueV();
        double obliqueW = (static_cast<const NPbase*> (&SM))->obliqueW();
        double obliqueX = (static_cast<const NPbase*> (&SM))->obliqueX();
        double obliqueY = (static_cast<const NPbase*> (&SM))->obliqueY();
        if ( SM.IsFlagFixedAllSMparams() ) {
            sigma_tau += Coeff_cache[myLEP2oblique.Shat]*obliqueShat
                       + Coeff_cache[myLEP2oblique.That]*obliqueThat
                       + Coeff_cache[myLEP2oblique.Uhat]*obliqueUhat
                       + Coeff_cache[myLEP2oblique.V]*obliqueV
                       + Coeff_cache[myLEP2oblique.W]*obliqueW
                       + Coeff_cache[myLEP2oblique.X]*obliqueX
                       + Coeff_cache[myLEP2oblique.Y]*obliqueY;
        } else {
            double ObParam[7] = {obliqueShat, obliqueThat, obliqueUhat,
                                 obliqueV, obliqueW, obliqueX, obliqueY};
            sigma_tau += myLEP2oblique.sigma_l_LEP2_NP(StandardModel::TAU, s, ml_cache, ObParam);
        }
    }
    
    return ( sigma_tau*GeVminus2_to_nb*1000.0 );
}
        

