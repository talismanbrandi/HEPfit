/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */
    
#include "HeffDF1bsg.h"

using namespace gslpp;

HeffDF1bsg::HeffDF1bsg(const StandardModel & SM, StandardModelMatching & SM_Matching) :
        model(SM), modelmatching(SM_Matching), coeffbsg(10, NDR, NLO), 
        evolDF1bsg(10, NDR, NLO, SM) {
}

HeffDF1bsg::~HeffDF1bsg() {
}

/*******************************************************************************
 * evoulution Wilson Coefficien b-> s gamma                                    * 
 * Misiak base                                                                 *
 ******************************************************************************/
vector<complex>** HeffDF1bsg::ComputeCoeffBsg(double mu, schemes scheme) {
    
    const std::vector<WilsonCoefficient>& mc = modelmatching.CMbsg();
    
    coeffbsg.setMu(mu); 
    
    orders ordDF1 = coeffbsg.getOrder();
    for (unsigned int i = 0; i < mc.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            for (int k = LO; k <= j; k++){
                coeffbsg.setCoeff(*coeffbsg.getCoeff(orders(j)) +
                    evolDF1bsg.Df1Evolbsg(mu, mc[i].getMu(), orders(k), mc[i].getScheme()) *
                    (*(mc[i].getCoeff(orders(j - k)))), orders(j));
            }
        }
    }
    
    coeffbsg.setScheme(scheme);
   
    return coeffbsg.getCoeff();
}

