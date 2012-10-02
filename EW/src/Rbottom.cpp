/* 
 * File:   Rbottom.cpp
 * Author: mishima
 */

#include "Rbottom.h"
#include <EWSM.h>


double Rbottom::getThValue() { 
    double R0_b;
    if (bCHMN)  
        R0_b = myEW_CHMN.R_b();
    else {    
        if (SM.getEWSM()->isBoolR0bApproximate()) 
            R0_b = SM.getEWSM()->R0_bottom_SM();// use an approximate formula
        else {
            R0_b = myEW.Gamma_q(SM.BOTTOM)/myEW.Gamma_had();
            
            if ( myEW.checkModelForSTU() ) {
                double alpha = SM.alphaMz();
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
        

