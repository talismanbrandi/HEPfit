/* 
 * Copyright (C) 2012 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */
    
#include "HeffDF1bsg.h"
#include "StandardModel.h"
#include "EvolDB1bsg.h"

HeffDF1bsg::HeffDF1bsg(const StandardModel & SM) 
:       model(SM), coeffbsg(10, NDR, NLO), 
        evolDB1bsg(new EvolDB1bsg(13, NDR, NLO, SM)) 
{}

HeffDF1bsg::~HeffDF1bsg() 
{}

/*******************************************************************************
 * evoulution Wilson Coefficien b-> s gamma                                    * 
 * Misiak base                                                                 *
 ******************************************************************************/
gslpp::vector<gslpp::complex>** HeffDF1bsg::ComputeCoeffBsg(double mu, schemes scheme) 
{
    
    const std::vector<WilsonCoefficient>& mc = model.getMatching().CMbsg();
    
    coeffbsg.setMu(mu); 
    
    orders_qcd ordDF1 = coeffbsg.getOrder();
    for (unsigned int i = 0; i < mc.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            for (int k = LO; k <= j; k++){
                coeffbsg.setCoeff(*coeffbsg.getCoeff(orders_qcd(j)) +
                    evolDB1bsg->Df1Evolbsg(mu, mc[i].getMu(), orders_qcd(k), mc[i].getScheme()) *
                    (*(mc[i].getCoeff(orders_qcd(j - k)))), orders_qcd(j));
            }
        }
    }
    
    coeffbsg.setScheme(scheme);
   
    return coeffbsg.getCoeff();
}

