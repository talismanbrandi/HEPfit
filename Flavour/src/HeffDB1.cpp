/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */
    
#include "HeffDB1.h"
#include "gslpp_complex.h"

using namespace gslpp;

HeffDB1::HeffDB1(const StandardModel & SM) :
        model(SM), 
        coeffnlep00qcd (10, NDR, NLO, NLO_ew), coeffnlep00 (12, NDR, NLO, NLO_ew),
        coeffnlep10qcd (10, NDR, NLO, NLO_ew), coeffnlep10 (12, NDR, NLO, NLO_ew),
        coeffnlep01 (10, NDR, NLO), coeffnlep01A(10, NDR, NLO), coeffnlep01B(4, NDR, NLO), coeffnlep00CC(10, NDR, NLO),
        coeffnlep11 (10, NDR, NLO), coeffnlep11A(10, NDR, NLO), coeffnlep11B(4, NDR, NLO), coeffnlep10CC(10, NDR, NLO),
        coeffsmumu (6, NDR, NLO), coeffdmumu (6, NDR, NLO),
        coeffsnunu (1, NDR, NLO), coeffdnunu (1, NDR, NLO),
        coeffBKstarll (19,NDR, NLO),
        u(10, NDR, NLO, NLO_ew, SM),
        evolDF1BKstarll(13, NDR, NLO, SM),
        nlep (12, 0.), nlep2(10, 0.), nlepCC(4, 0.){
}

HeffDB1::~HeffDB1() {
}

/*******************************************************************************
 * evolution Wilson Coefficients b-> nonlep.                                   * 
 * Buras base                                                                  *
 * deltaB=1   deltaC=0   deltaS=0                                              *
 ******************************************************************************/
vector<complex>** HeffDB1::ComputeCoeffBnlep00(double mu, schemes scheme) {
    
     std::vector<WilsonCoefficient>& mcb = model.getMyMatching()->CMbnlep( 0);
     std::vector<WilsonCoefficient>& mcbCC = model.getMyMatching()->CMbnlepCC( 0);
    
    coeffnlep00qcd.setMu(mu); //inizializes to zero the coefficients
    coeffnlep00CC.setMu(mu);
    coeffnlep00.setMu(mu);
    
    orders_ew ordDF1ew = coeffnlep00.getOrder_ew();
    orders ordDF1 =  coeffnlep00.getOrder();
    
    for (unsigned int i = 0; i < mcb.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            for (int k = LO; k <= j; k++) {        
                
                //Evolves the LO terms and the ones proportional to alpha_s 
                coeffnlep00qcd.setCoeff(*coeffnlep00qcd.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcb[i].getMu(), orders(k), NULL_ew, mcb[i].getScheme())*
                    (*(mcb[i].getCoeff(orders(j - k)))), orders(j));
                
                
                //Evolves terms proportional to alpha_e and alpha_e/aplha_s
                coeffnlep00qcd.setCoeff(*coeffnlep00qcd.getCoeff(orders_ew(j+4)) +
                    u.Df1Evolnlep(mu, mcb[i].getMu(), NNLO, orders_ew(k+4), mcb[i].getScheme()) *
                    (*(mcb[i].getCoeff(orders(j - k)))), orders_ew(j+4));
                
                
                //Evolves the current*current part of the hamiltonian (the one non-proportional to lambda_t) 
                coeffnlep00CC.setCoeff(*coeffnlep00CC.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcbCC[i].getMu(), orders(k), NULL_ew, mcbCC[i].getScheme()) *
                    (*(mcbCC[i].getCoeff(orders(j - k)))), orders(j)); 
   
            }
        }
        
                coeffnlep00qcd.setCoeff(*coeffnlep00qcd.getCoeff(orders_ew(NLO_ew)) +
                    u.Df1Evolnlep(mu, mcb[i].getMu(), orders(LO), NULL_ew,  mcb[i].getScheme()) *
                    (*(mcb[i].getCoeff(orders_ew(NLO_ew)))), orders_ew(NLO_ew));       
        
    }
        
    coeffnlep00qcd.setScheme(scheme);
    coeffnlep00CC.setScheme(scheme);
    
    //Puts all together in a wilson coefficient object of 12 component: 
    //the first 10 terms are the ones proportional to lambda_t
    //the last two are the remainder current*current operators 
    for (int j=LO; j <= ordDF1; j++) {
        nlep2 = *coeffnlep00qcd.getCoeff(orders(j));
        for (int i = 0; i < 10; i++){
            nlep.assign(i, nlep2(i));
        }
        nlep2 = *coeffnlep00CC.getCoeff(orders(j));
        for (int i = 10; i < 12; i++){
            nlep.assign(i, nlep2(i-10));
        }        
    coeffnlep00.setCoeff(nlep, orders(j));
    }
    for (int k=LO_ew; k <= ordDF1ew; k++) {
        nlep2 = *coeffnlep00qcd.getCoeff(orders_ew(k));
        for (int l = 0; l < 10; l++){
            nlep.assign(l, nlep2(l));;
        }       
    coeffnlep00.setCoeff(nlep, orders_ew(k));
    }
    
    return coeffnlep00.getCoeff();
}

/*******************************************************************************
 * evolution Wilson Coefficienys b-> nonlep.                                   * 
 * Buras base                                                                  *
 * deltaB=1   deltaC=0   deltaS=1                                              *
 ******************************************************************************/
vector<complex>** HeffDB1::ComputeCoeffBnlep10(double mu, schemes scheme) {
    
     std::vector<WilsonCoefficient>& mcb = model.getMyMatching()->CMbnlep( 1);
     std::vector<WilsonCoefficient>& mcbCC = model.getMyMatching()->CMbnlepCC( 1);
    
    coeffnlep10qcd.setMu(mu);
    coeffnlep10CC.setMu(mu);
    coeffnlep10.setMu(mu);
    
    orders_ew ordDF1ew = coeffnlep10.getOrder_ew();
    orders ordDF1 =  coeffnlep10.getOrder();
    
    for (unsigned int i = 0; i < mcb.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            for (int k = LO; k <= j; k++)   {
                
                //Evolves the LO terms and the ones proportional to alpha_s 
                coeffnlep10qcd.setCoeff(*coeffnlep10qcd.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcb[i].getMu(), orders(k), NULL_ew,  mcb[i].getScheme()) *
                    (*(mcb[i].getCoeff(orders(j - k)))), orders(j));
                
                //Evolves terms proportional to alpha_e and alpha_e/aplha_s
                coeffnlep10qcd.setCoeff(*coeffnlep10qcd.getCoeff(orders_ew(j+4)) +
                    u.Df1Evolnlep(mu, mcb[i].getMu(), NNLO, orders_ew(k+4), mcb[i].getScheme()) *
                    (*(mcb[i].getCoeff(orders(j - k)))), orders_ew(j+4));
                
                //Evolves the current*current part of the hamiltonian (the one non-proportional to lambda_t)
                coeffnlep10CC.setCoeff(*coeffnlep10CC.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcbCC[i].getMu(), orders(k), NULL_ew, mcbCC[i].getScheme()) *
                    (*(mcbCC[i].getCoeff(orders(j - k)))), orders(j)); 
        
            }
        }
            
        coeffnlep10qcd.setCoeff(*coeffnlep10qcd.getCoeff(orders_ew(NLO_ew)) +
                    u.Df1Evolnlep(mu, mcb[i].getMu(), orders(LO), NULL_ew, mcb[i].getScheme()) *
                    (*(mcb[i].getCoeff(orders(LO_ew)))), orders_ew(NLO_ew));
    }        
    
    coeffnlep10qcd.setScheme(scheme);
    coeffnlep10CC.setScheme(scheme);
    
    //Puts all together in a wilson coefficient object of 12 component: 
    //the first 10 terms are the one proportional to lambda_t
    //the last two are the remainder current*current operators 
    
    for (int j=LO; j <= ordDF1; j++) {
        nlep2 = *coeffnlep10qcd.getCoeff(orders(j));
        for (int i = 0; i < 10; i++){
            nlep.assign(i, nlep2(i));
        }
        nlep2 = *coeffnlep10CC.getCoeff(orders(j));
        for (int i = 10; i < 12; i++){
            nlep.assign(i, nlep2(i-10));
        }        
    coeffnlep10.setCoeff(nlep, orders(j));
    }
    for (int k=LO_ew; k <= ordDF1ew; k++) {
        nlep2 = *coeffnlep10qcd.getCoeff(orders_ew(k));
        for (int l = 0; l < 10; l++){
            nlep.assign(l, nlep2(l));;
        }       
    coeffnlep10.setCoeff(nlep, orders_ew(k));
    }
    
    return coeffnlep10.getCoeff();
}

/*******************************************************************************
 * evolution Wilson Coefficienys b-> nonlep.                                   * 
 * Buras base                                                                  *
 * deltaB=1   deltaC=1   deltaS=0                                              *
 ******************************************************************************/
vector<complex>** HeffDB1::ComputeCoeffBnlep01(double mu, schemes scheme) {
    
     std::vector<WilsonCoefficient>& mcbCC1 =model.getMyMatching()->CMbnlepCC( 2);
     std::vector<WilsonCoefficient>& mcbCC2 = model.getMyMatching()->CMbnlepCC( 3);
    
    coeffnlep01.setMu(mu);
    coeffnlep01A.setMu(mu);
    coeffnlep01B.setMu(mu);
    
    orders ordDF1 = coeffnlep01A.getOrder();
    
    //evolution of the current*current terms
    for (unsigned int i = 0; i < mcbCC1.size(); i++)
        for (int j = LO; j <= ordDF1; j++)
            for (int k = LO; k <= j; k++){
                
                coeffnlep01A.setCoeff(*coeffnlep01A.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcbCC1[i].getMu(), orders(k), NULL_ew, mcbCC1[i].getScheme()) *
                    (*(mcbCC1[i].getCoeff(orders(j - k)))), orders(j)); 
                
                coeffnlep01B.setCoeff(*coeffnlep01B.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcbCC2[i].getMu(), orders(k), NULL_ew, mcbCC2[i].getScheme()) *
                    (*(mcbCC2[i].getCoeff(orders(j - k)))), orders(j)); 
            }
        
    coeffnlep01A.setScheme(scheme);
    coeffnlep01B.setScheme(scheme);
    coeffnlep01.setScheme(scheme);
    
    //Puts all together in a wilson coefficient object of 4 components
    for (int j=LO; j <= ordDF1; j++) {
        nlep2 = *coeffnlep01A.getCoeff(orders(j));
        for (int i = 0; i < 2; i++){
            nlep.assign(i, nlep2(i));
        }
        nlep2 = *coeffnlep01A.getCoeff(orders(j));
        for (int i = 2; i < 4; i++){
            nlep.assign(i, nlep2(i-2));
        }        
    coeffnlep01.setCoeff(nlep, orders(j));
    }    
    return coeffnlep01.getCoeff();   
    
}

/*******************************************************************************
 * evolution Wilson Coefficienys b-> nonlep.                                   * 
 * Buras base                                                                  *
 * deltaB=1   deltaC=1   deltaS=1                                              *
 ******************************************************************************/
vector<complex>** HeffDB1::ComputeCoeffBnlep11(double mu, schemes scheme) {
    
     std::vector<WilsonCoefficient>& mcbCC1 = model.getMyMatching()->CMbnlepCC( 2);
     std::vector<WilsonCoefficient>& mcbCC2 = model.getMyMatching()->CMbnlepCC( 3);
    
    coeffnlep11.setMu(mu);
    coeffnlep11A.setMu(mu);
    coeffnlep11B.setMu(mu);
    
    orders ordDF1 = coeffnlep11A.getOrder();
    
    for (unsigned int i = 0; i < mcbCC1.size(); i++)
        for (int j = LO; j <= ordDF1; j++)
            for (int k = LO; k <= j; k++){
                
                coeffnlep11A.setCoeff(*coeffnlep11A.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcbCC1[i].getMu(), orders(k), NULL_ew, mcbCC1[i].getScheme()) *
                    (*(mcbCC1[i].getCoeff(orders(j - k)))), orders(j)); 
        
                coeffnlep11B.setCoeff(*coeffnlep11B.getCoeff(orders(j)) +
                    u.Df1Evolnlep(mu, mcbCC2[i].getMu(), orders(k), NULL_ew, mcbCC2[i].getScheme()) *
                    (*(mcbCC2[i].getCoeff(orders(j - k)))), orders(j)); 
            }
        
    coeffnlep11A.setScheme(scheme);
    coeffnlep11B.setScheme(scheme);
    coeffnlep11.setScheme(scheme);
    
   for (int j=LO; j <= ordDF1; j++) {
        nlep2 = *coeffnlep11A.getCoeff(orders(j));
        for (int i = 0; i < 2; i++){
            nlep.assign(i, nlep2(i));
        }
        nlep2 = *coeffnlep11A.getCoeff(orders(j));
        for (int i = 2; i < 4; i++){
            nlep.assign(i, nlep2(i-2));
        }        
    coeffnlep11.setCoeff(nlep, orders(j));
    }    
    return coeffnlep11.getCoeff();   
    
}

vector<complex>** HeffDB1::ComputeCoeffsmumu() {
    
     std::vector<WilsonCoefficient>& mcb = model.getMyMatching() -> CMbsmm();
    coeffsmumu.resetCoefficient();
    orders ordDF1 = coeffsmumu.getOrder();
    
    for (unsigned int i = 0; i < mcb.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            coeffsmumu.setCoeff(*coeffsmumu.getCoeff(orders(j))
                                    + *mcb[i].getCoeff(orders(j)), orders(j));
        }  
    }
    
    return coeffsmumu.getCoeff(); 
}

vector<complex>** HeffDB1::ComputeCoeffdmumu() {
    
     std::vector<WilsonCoefficient>& mcb = model.getMyMatching() -> CMbdmm();
    coeffdmumu.resetCoefficient();
    orders ordDF1 = coeffdmumu.getOrder();
    
    for (unsigned int i = 0; i < mcb.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            coeffdmumu.setCoeff(*coeffdmumu.getCoeff(orders(j))
                                    + *mcb[i].getCoeff(orders(j)), orders(j));
        }
    }
    return coeffdmumu.getCoeff(); 
} 

vector<complex>** HeffDB1::ComputeCoeffsnunu() {
    
     std::vector<WilsonCoefficient>& mcb = model.getMyMatching() -> CMBXsnn();
    
    orders ordDF1 = coeffsnunu.getOrder();
    
    for (unsigned int i = 0; i < mcb.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            coeffsnunu.setCoeff(*coeffsnunu.getCoeff(orders(j))
                                    + *mcb[i].getCoeff(orders(j)), orders(j));
        }
    }
     
    return coeffsnunu.getCoeff(); 
} 

vector<complex>** HeffDB1::ComputeCoeffdnunu() {
    
     std::vector<WilsonCoefficient>& mcb = model.getMyMatching() -> CMBXdnn();
    
    orders ordDF1 = coeffdnunu.getOrder();
    
    for (unsigned int i = 0; i < mcb.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            coeffdnunu.setCoeff(*coeffdnunu.getCoeff(orders(j))
                                    + *mcb[i].getCoeff(orders(j)), orders(j));
        }
    }
    
    return coeffdnunu.getCoeff(); 
} 

vector<complex>** HeffDB1::ComputeCoeffBKstarll(double mu, schemes scheme) {
    
    const std::vector<WilsonCoefficient>& mc = model.getMyMatching() -> CMBKstarll();
    
    coeffBKstarll.setMu(mu); 
    
    orders ordDF1 = coeffBKstarll.getOrder();
    for (unsigned int i = 0; i < mc.size(); i++){
        for (int j = LO; j <= ordDF1; j++){
            for (int k = LO; k <= j; k++){
                coeffBKstarll.setCoeff(*coeffBKstarll.getCoeff(orders(j)) +
                    evolDF1BKstarll.Df1Evolbsg(mu, mc[i].getMu(), orders(k), mc[i].getScheme()) *
                    (*(mc[i].getCoeff(orders(j - k)))), orders(j));
            }
        }
    }
    
    coeffBKstarll.setScheme(scheme);
   
    return coeffBKstarll.getCoeff();
}
