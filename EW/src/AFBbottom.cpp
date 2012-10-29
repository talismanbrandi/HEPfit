/* 
 * File:   AFBbottom.cpp
 * Author: mishima
 */

#include "AFBbottom.h"


double AFBbottom::getThValue() {   
    double AFB_b;
    if (bCHMN) 
        AFB_b = myEW_CHMN.AFB_q(SM.BOTTOM);
    else {
        AFB_b = 3.0/4.0*myEW.A_l(SM.ELECTRON)*myEW.A_q(SM.BOTTOM);
        
        if ( myEW.checkModelForSTU() ) {
            if(bBURGESS) {
                // TEST: the fit result by Gfitter in arXiv:1209.2716, 
                //       corresponding to MH=125.7 and Mt=173.52 
                //AFB_b = 0.1032;
                
                AFB_b += - 0.0188*myEW.S() + 0.0131*myEW.T();
            } else {
                double alpha = myEW.alpha0();          
                double c2 = myEW.c02();
                double s2 = myEW.s02();
                double s4 = s2*s2;
                double s6 = s4*s2;        
                double s8 = s6*s2;
            
                AFB_b -= 18.0*alpha*s2*(15.0-76.0*s2+152.0*s4-160.0*s6+64.0*s8)
                         /pow(1.0-4.0*s2+8.0*s4, 2.0)
                         /pow(9.0-12.0*s2+8.0*s4, 2.0)/(c2-s2)
                         *( myEW.S() - 4.0*c2*s2*myEW.T() ); 
            }
        }
    }
    
    return AFB_b;
}
