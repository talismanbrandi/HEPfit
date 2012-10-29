/* 
 * File:   Mw.cpp
 * Author: mishima
 */

#include "Mw.h"


double Mw::getThValue() {
    double myMw;
    if (bCHMN)  
        myMw = myEW_CHMN.Mw();
    else {
        myMw = SM.Mw();    

        if ( myEW.checkModelForSTU() ) {
            if(bBURGESS) {
                // TEST: the fit result by Gfitter in arXiv:1209.2716, 
                //       corresponding to MH=125.7 and Mt=173.52 
                //myMw = 80.367; 
                
                myMw *= 1.0 - 0.00723/2.0*myEW.S() + 0.0111/2.0*myEW.T() + 0.00849/2.0*myEW.U();
            } else {
                double alpha = myEW.alpha0();  
                double c = sqrt(myEW.c02());
                double c2 = myEW.c02();
                double s2 = myEW.s02();
                
                myMw -= alpha*c*SM.getMz()/4.0/(c2-s2)
                        *( myEW.S() - 2.0*c2*myEW.T() - (c2-s2)*myEW.U()/2.0/s2 );
            }
        }
    }
    
    return myMw;
}

