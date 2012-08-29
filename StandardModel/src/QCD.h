/* 
 * File:   QCD.h
 * Author: marco
 *
 * Created on February 17, 2011, 2:13 PM
 */

#ifndef QCD_H
#define	QCD_H

#include "Model.h"
#include "Meson.h"
#include "OrderScheme.h"
#define MEPS 1.e-10 // mass precision

class QCD: public Model {
public:
    enum meson {B_D, B_S, B_P, K_0, K_P, D_0, MESON_END}; 
    enum quark {UP,DOWN,CHARM,STRANGE,TOP,BOTTOM};
                           // update StandardModel::lepton if changed!!!!!!

    static const int NQCDvars = 42;//26;

    /**
     * array containing the labels under which all QCD parameters must be
     * stored in a Parameters object
     */

    static const std::string QCDvars[NQCDvars];

    virtual std::string ModelName() const {
        return "QCD";
    }
    
    /**
     * Constructor for QCD
     * @param a Parameters object that must contain all the labels appearing in QCDvars
     */
 //   QCD(const Parameters&);
    
    QCD() : BBs(5), BBd(5), BD(5), BK(5) {
        Nc=3.;
        CF = Nc/2.-1./(2.*Nc);
        quarks[UP].setCharge(2./3.);
        quarks[UP].setMass_scale(2.);
        quarks[CHARM].setCharge(2./3.);
        quarks[TOP].setCharge(2./3.);
        quarks[DOWN].setCharge(-1./3.);
        quarks[DOWN].setMass_scale(2.);
        quarks[STRANGE].setCharge(-1./3.);
        quarks[STRANGE].setMass_scale(2.);
        quarks[BOTTOM].setCharge(-1./3.); 
        //to be moved to the Als class
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
                als_cache[j][i] = 0.;
            for (int j = 0; j < 6; j++)
                mrun_cache[j][i] = 0.;
            for (int j = 0; j < 4; j++)
                lambda5_cache[j][i] = 0.;
            for (int j = 0; j < 4; j++)
                mp2mbar_cache[j][i] = 0.;
        }
    };

    /**
     * the @f$\beta_0@f$ coefficient
     * @param nf the number of active flavours
     * @return the @f$\beta_0@f$ coefficient
     */
    double Beta0(double nf) const;

    /**
     * the @f$\beta_1@f$ coefficient
     * @param nf the number of active flavours
     * @return the @f$\beta_1@f$ coefficient
     */
    double Beta1(double nf) const;

    /**
     * the @f$\beta_2@f$ coefficient
     * @param nf the number of active flavours
     * @return the @f$\beta_2@f$ coefficient
     */
    double Beta2(double nf) const;

    /**
     * the number of active flavour at scale @f$\mu@f$
     * @param mu the scale @f$\mu@f$ in GeV
     * @return the number of active flavour at scale @f$\mu@f$
     */
    double Nf(double mu) const;

    /**
     * the strong running coupling @f$\alpha_s@f$ in the @f$\overline{\mathrm{MS}}@f$ scheme
     * @param mu the scale @f$\mu@f$ in GeV
     * @param lam @f$\Lambda_\mathrm{QCD}@f$ with @f$n_f@f$ active flavours in GeV
     * @param nf the number of active flavours @f$n_f@f$
     * @param order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return @f$\alpha_s@f$
     */
    double Als(double mu, double lam, double nf, orders order) const;

    /**
     * the strong running coupling @f$\alpha_s@f$ in the @f$\overline{\mathrm{MS}}@f$ scheme
     * @param mu the scale @f$\mu@f$ in GeV
     * @param nf the number of active flavours
     * @param alsi the initial condition @f$\alpha_s(m_i)@f$
     * @param mi the scale @f$m_i@f$ in GeV
     * @param order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return @f$\alpha_s@f$
     */
    double Als(double mu, double nf, double alsi, double mi, orders order) const;

    /**
     * the strong running coupling @f$\alpha_s@f$ in the @f$\overline{\mathrm{MS}}@f$ scheme
     * @param mu the scale @f$\mu@f$ in GeV
     * @param nfmu the number of active flavours at the scale @f$\mu@f$
     * @param order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return @f$\alpha_s@f$
     */
    double Als(double mu, double nfmu, orders order) const;

    /**
     * the strong running coupling @f$\alpha_s@f$ in the @f$\overline{\mathrm{MS}}@f$ scheme
     * @param mu the scale @f$\mu@f$ in GeV
     * @param order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return @f$\alpha_s@f$
     */
    double Als(double mu, orders order = FULLNLO) const;

    /**
     * @f$\Lambda_\mathrm{QCD}@f$ with five active flavours in GeV
     * @param order (=LO, FULLNLO, FULLNNLO)
     * @return @f$\Lambda_\mathrm{QCD}@f$
     */
    double Lambda5(orders order) const;

    double Lambda(double mu, orders order) const;  

    double Lambda(double muMatching, double mf, double nfNEW, double nfORG, 
                  double LambdaORG, orders order) const;
    
    /**
     *
     * @return @f$\alpha_s(Mz)@f$
     */
    double getAlsMz() const {
        return AlsMz;
    }

    /**
     * set the initial condition @f$\alpha_s(Mz)@f$
     * @param AlsMz the initial condition @f$\alpha_s(Mz)@f$
     */
    void setAlsMz(double AlsMz) {
        this->AlsMz = AlsMz;
    }

    /**
     *
     * @return the scale Mz at which the initial condition for @f$\alpha_s(Mz)@f$ is given
     */
    double getMz() const {
        return Mz;
    }

    /**
     * set the scale M at which the initial condition for @f$\alpha_s(M)@f$ is given
     * @param M the scale M in GeV
     */
    void setMz(double Mz) {
        this->Mz = Mz;
    }

    /**
     *
     * @return the number of colours
     */
    double getNc() const {
        return Nc;
    }

    /**
     * set the number of colours
     * @param Nc the number of colours
     */
    void setNc(double Nc) {
        this->Nc = Nc;
    }

    /**
     *
     * @return the threshold between six- and five-flavour theory in GeV
     */
    double getMut() const {
        return mut;
    }

    /**
     * set the threshold between six- and five-flavour theory
     * @param mut the threshold between six- and five-flavour theory in GeV
     */
    void setMut(double mut) {
        this->mut = mut;
    }

    /**
     *
     * @return the threshold between five- and four-flavour theory in GeV
     */
    double getMub() const {
        return mub;
    }

    /**
     * set the threshold between five- and four-flavour theory
     * @param mub the threshold between five- and four-flavour theory in GeV
     */
    void setMub(double mub) {
        this->mub = mub;
    }

    /**
     *
     * @return the threshold between four- and three-flavour theory in GeV
     */
    double getMuc() const {
        return muc;
    }

    /**
     * set the threshold between four- and three-flavour theory
     * @param muc the threshold between four- and three-flavour theory in GeV
     */
    void setMuc(double muc) {
        this->muc = muc;
    }

    /**
     * @return the pole mass of the top quark
     */
    double getMtpole() const {
        return mtpole;
    }
    
    /**
     * the running quark mass @f$m(\mu)@f$
     * @param mu the scale @f$\mu@f$ in GeV
     * @param m the @f$\overline{\mathrm{MS}}@f$ mass @f$m(m)@f$
     * @param order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return the running quark mass @f$m(\mu)@f$
     */
    double Mrun(double mu, double m, orders order = FULLNLO) const;
    
    /**
     * runs the quark mass from @f$\mu_i@f$ to @f$\mu_f@f$
     * @param mu_f the scale @f$\mu_f@f$ in GeV
     * @param mu_i the scale @f$\mu_i@f$ in GeV
     * @param m the @f$\overline{\mathrm{MS}}@f$ mass @f$m(mu_i)@f$
      * @param order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return the running quark mass @f$m(\mu_f)@f$
     */
    double Mrun(double mu_f, double mu_i, double m, orders order = FULLNLO) const;

    /**
     * runs the quark mass from @f$\mu_i@f$ to @f$\mu_f@f$ at fixed nf
     * @param mu_f the scale @f$\mu_f@f$ in GeV
     * @param mu_i the scale @f$\mu_i@f$ in GeV
     * @param m the @f$\overline{\mathrm{MS}}@f$ mass @f$m(mu_i)@f$
     * @param nf the number of active flavours
     * @param order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return the running quark mass @f$m(\mu_f)@f$
     */
    double Mrun(double mu_f, double mu_i, double m, double nf, orders order = FULLNLO) const;

    /**
     * convert the @f$\overline{\mathrm{MS}}@f$ mass @f$m(m)@f$ to the pole mass
     * @param mbar the @f$\overline{\mathrm{MS}}@f$ mass @f$m(m)@f$ in GeV
     * @return the pole mass in GeV
     */
    double Mbar2Mp(double mbar) const;

    /**
     * convert the pole mass to the @f$\overline{\mathrm{MS}}@f$ mass @f$m(m)@f$
     * @param mp the pole mass in GeV
     * @return the @f$\overline{\mathrm{MS}}@f$ mass @f$m(m)@f$ in GeV
     */
    double Mp2Mbar(double mp) const;

    
    double MS2DRqmass(const double& MSscale, const double& MSbar) const;
    
    
    /**
     * convert @f$\overline{\mathrm{MS}}@f$ to @f$\overline{\mathrm{DR}}@f$ quark masses
     * @param MSbar the @f$\overline{\mathrm{MS}}@f$ mass @f$m(m)@f$
     * @return the @f$\overline{\mathrm{DR}}@f$ mass @f$m(m)@f$
     */
    double MS2DRqmass(const double& MSbar) const;
    
    /**
     * Initializes the QCD parameters found in the argument
     * @param a map containing the parameters (all as double) to be updated
     * "AlsMz"
     * "Mz"
     * "mup" @f$\overline{\mathrm{MS}}@f$ mass @f$m_u(2\mathrm{GeV})@f$
     * "mdown" @f$\overline{\mathrm{MS}}@f$ mass @f$m_d(2\mathrm{GeV})@f$
     * "mcharm" @f$\overline{\mathrm{MS}}@f$ mass @f$m_c(m_c)@f$
     * "mstrange" @f$\overline{\mathrm{MS}}@f$ mass @f$m_s(2\mathrm{GeV})@f$
     * "mtop" the top quark pole mass @f$m_t@f$
     * "mbottom" @f$\overline{\mathrm{MS}}@f$ mass @f$m_b(m_b)@f$
     * "mut"
     * "mub"
     * "muc"
     * "MBd"
     * "MBs"
     * "MBp"
     * "MK0"
     * "MKp"
     * "MD"
     * "FBs"
     * "FBsoFBd"
     * "FD"
     * "BBsoBBd"
     * "BBs1"
     * "BBs2"
     * "BBs3"
     * "BBs4"
     * "BBs5"
     * "BBsscale"
     * "BBsscheme"
     * "BD1"
     * "BD2"
     * "BD3"
     * "BD4"
     * "BD5"
     * "BDscale"
     * "BDscheme"
     * "BK1"
     * "BK2"
     * "BK3"
     * "BK4"
     * "BK5"
     * "BKscale"
     * "BKscheme"
     */
    virtual bool Init(const std::map<std::string, double>&);

    /**
     * Checks that all required parameters are present
     * @param a map containing the parameters (all as double) to be updated
     */
    virtual bool CheckParameters(const std::map<std::string, double>&);

    /**
     * updates the QCD parameters found in the argument
     * @param a map containing the parameters (all as double) to be updated
     */
    virtual bool Update(const std::map<std::string, double>&);

    /**
     * updates the QCD parameters found in the argument
     * @param a Parameters object containing the parameters to be updated
     */
//   void update(const Parameters&);
    
    virtual bool PreUpdate();
     
    virtual bool PostUpdate();
     
    virtual bool SetFlag(const std::string, const bool&);
     
    Meson getMesons(const int i) const {
        return mesons[i];
    }

    Particle getQuarks(const int i) const {
        return quarks[i];
    }

    double Thresholds(int i) const;

    double AboveTh(double mu) const;

    double BelowTh(double mu) const;

    double getCF() const {
        return CF;
    }

    BParameter getBBd() const {
        return BBd;
    }

    BParameter getBBs() const {
        return BBs;
    }
    
    BParameter getBD() const {
        return BD;
    }
    
    BParameter getBK() const {
        return BK;
    }
    
    /*BParameter getBD() const {
        return BD;
    }*/

protected:
    double Nc, CF, AlsMz, Mz, mut, mub, muc, mtpole;
    Particle quarks[6];
    Meson mesons[MESON_END];
    BParameter BBs, BBd, BD, BK;
    virtual void SetParameter(const std::string, const double&);
    bool computeYu, computeYd;

private:
    mutable double als_cache[5][5], lambda5_cache[4][5], 
                   mp2mbar_cache[4][5], mrun_cache[6][5];
    bool computeFBd, computeBd, computemt;
    double BBsoBBd, FBsoFBd;
    double ZeroNf5(double *x, double *) const;
    double Mp2Mbara(double * mu, double * mp) const;
    void CacheShift(double cache[][5], int n) const;
};

#endif	/* QCD_H */
