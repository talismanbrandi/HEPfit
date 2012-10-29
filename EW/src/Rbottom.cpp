/* 
 * File:   Rbottom.cpp
 * Author: mishima
 */

#include "Rbottom.h"
#include "sigmaHadron.h"
#include <EWSM.h>


double Rbottom::getThValue() { 
    double R0_b;
    if (bCHMN)  
        R0_b = myEW_CHMN.R_b();
    else {    
        if (SM.getEWSM()->isBoolR0bApproximate() && SM.ModelName()!="NewPhysicsEpsilons") 
            R0_b = SM.getEWSM()->R0_bottom_SM();// use an approximate formula
        else
            R0_b = myEW.Gamma_q(SM.BOTTOM)/myEW.Gamma_had();
        
        if ( myEW.checkModelForSTU() ) {
            if(bBURGESS) {
                // TEST: the fit result by Gfitter in arXiv:1209.2716, 
                //       corresponding to MH=125.7 and Mt=173.52 
                //R0_b = 0.21474;
                
                double delta_b = - 0.00171*myEW.S() + 0.00416*myEW.T();
                double delta_had = - 0.00901*myEW.S() + 0.0200*myEW.T();
                R0_b *= 1.0 + delta_b/myEW.Gamma_q(SM.BOTTOM) 
                        - delta_had/myEW.Gamma_had();
            } else {
                double alpha = myEW.alpha0();  
                double c2 = myEW.c02();
                double s2 = myEW.s02();
                double s4 = s2*s2;
                R0_b += 6.0*alpha*(9.0-36.0*s2+16.0*s4)
                        /pow(45.0-84.0*s2+88.0*s4, 2.0)/(c2-s2)
                        *( myEW.S() - 4.0*c2*s2*myEW.T() );
            }
        }
    }
    
    return R0_b;
}
        

