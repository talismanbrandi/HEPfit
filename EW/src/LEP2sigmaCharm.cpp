/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <Math/Functor.h>
#include <Math/Integrator.h>
#include <Math/AllIntegrationTypes.h>
#include "LEP2sigmaCharm.h"


double LEP2sigmaCharm::computeThValue() 
{ 
    Mw = SM.Mw(); 
    GammaZ = myEW.Gamma_Z();

    if (!checkSMparams(s, Mw, GammaZ)) {
        mq_cache = m_q(SM.CHARM, sqrt_s);
        
        if (!flag[ISR])
            SMresult_cache = sigma_NoISR_q();
        else {
            ROOT::Math::Functor1D wf(this, &LEP2sigmaCharm::Integrand_sigmaWithISR_q);
            ROOT::Math::Integrator ig(wf, ROOT::Math::IntegrationOneDim::kADAPTIVESINGULAR);
            ig.SetAbsTolerance(1.E-13); // desired absolute error
            ig.SetRelTolerance(1.E-4); // desired relative error
            SMresult_cache = ig.Integral(0.0, 1.0-0.85*0.85); // interval
            //std::cout << SMresult_cache << " +- " << ig.Error() << std::endl;
        }
        
        if (flag[WeakBox]) {
            ROOT::Math::Functor1D wf_box(this, &LEP2sigmaCharm::Integrand_dsigmaBox_q);
            ROOT::Math::Integrator ig_box(wf_box, ROOT::Math::IntegrationOneDim::kADAPTIVESINGULAR);
            ig_box.SetAbsTolerance(1.E-16); // desired absolute error
            ig_box.SetRelTolerance(1.E-4); // desired relative error
            double sigma_box = ig_box.Integral(-1.0, 1.0); // interval
            SMresult_cache += sigma_box;
            //std::cout << sigma_box << " +- " << ig_box.Error() << std::endl;
        }
        
        if ( checkLEP2NP() && !bSigmaForAFB && SM.IsFlagFixedAllSMparams()) {
            double ObParam[7];
             for (int i=0; i<7; i++) {
                 SetObParam((LEP2oblique::Oblique)i, ObParam);
                 Coeff_cache[i] 
                         = myLEP2oblique.sigma_q_LEP2_NP(StandardModel::CHARM, s, mq_cache, ObParam);
             }
        }
    }
    double sigma_charm = SMresult_cache;
    
    if ( checkLEP2NP() && !bSigmaForAFB) {
        double obliqueShat = (static_cast<const NPbase*> (&SM))->obliqueShat();
        double obliqueThat = (static_cast<const NPbase*> (&SM))->obliqueThat();
        double obliqueUhat = (static_cast<const NPbase*> (&SM))->obliqueUhat();
        double obliqueV = (static_cast<const NPbase*> (&SM))->obliqueV();
        double obliqueW = (static_cast<const NPbase*> (&SM))->obliqueW();
        double obliqueX = (static_cast<const NPbase*> (&SM))->obliqueX();
        double obliqueY = (static_cast<const NPbase*> (&SM))->obliqueY();
        if ( SM.IsFlagFixedAllSMparams() ) {
            sigma_charm += Coeff_cache[myLEP2oblique.Shat]*obliqueShat
                         + Coeff_cache[myLEP2oblique.That]*obliqueThat
                         + Coeff_cache[myLEP2oblique.Uhat]*obliqueUhat
                         + Coeff_cache[myLEP2oblique.V]*obliqueV
                         + Coeff_cache[myLEP2oblique.W]*obliqueW
                         + Coeff_cache[myLEP2oblique.X]*obliqueX
                         + Coeff_cache[myLEP2oblique.Y]*obliqueY;
        } else {
            double ObParam[7] = {obliqueShat, obliqueThat, obliqueUhat,
                                 obliqueV, obliqueW, obliqueX, obliqueY};
            sigma_charm += myLEP2oblique.sigma_q_LEP2_NP(StandardModel::CHARM, s, mq_cache, ObParam);
        }
    }
    
    return ( sigma_charm*GeVminus2_to_nb*1000.0 );
}
        
