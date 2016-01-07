/* 
 * Copyright (C) 2012 HEPfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef THDMCACHE_H
#define	THDMCACHE_H

#include <cmath>
#include "PVfunctions.h"
#include "THDM.h"

#include <stdexcept>
#include "gslpp.h"

/**
 * @class THDMcache
 * @ingroup THDM
 * @brief A class for the caching of some THDM objects.
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details At the moment only the Passarino-Veltman functions for STU are cached.
 * The tables are also read here.
 */
class THDMcache {
    
public:

    /**
     * @brief THDMcache constructor.
     * @details Reads all the tables values and stores them in the memory.
     */
    THDMcache(const StandardModel& SM_i);

    /**
     * @brief THDMcache destructor.
     * @details Reads all the tables values and stores them in the memory.
     */
    ~THDMcache()
    {}
    
    /**
     * @brief Cache size.
     * @details Determines the size of the cache. If it is set to 5, the cache will remember the last five function calls and store their results.
     */
    static const int CacheSize = 5;

    /**
     * @brief Check whether for the latest set of parameters a value is in the cache.
     * @details Takes a complex value.
     */
    int CacheCheck(const gslpp::complex cache[][CacheSize],
                   const int NumPar, const double params[]) const;

    /**
     * @brief Check whether for the latest set of parameters a value is in the cache.
     * @details Takes a real value.
     */
    int CacheCheckReal(const double cache[][CacheSize],
                   const int NumPar, const double params[]) const;

    /**
     * @brief Adds a new result and its parameters into the cache.
     * @details The new values are added on top. The oldest set on the stack is deleted. Takes a complex value.
     */
    void CacheShift(gslpp::complex cache[][CacheSize], const int NumPar,
                    const double params[], const gslpp::complex newResult) const; 

    /**
     * @brief Adds a new result and its parameters into the cache.
     * @details The new values are added on top. The oldest set on the stack is deleted. Takes a real value.
     */
    void CacheShiftReal(double cache[][CacheSize], const int NumPar,
                    const double params[], const double newResult) const; 

    /**
     * @return an object of PVfunctions class
     */
    const PVfunctions getPV() const {
        return PV;
    }

    /**
     * @brief This function reads values from a table and returns them as an array.
     * @return the tabled values
     */
    gslpp::matrix<double> readTable(std::string filename, int rowN, int colN);

    /**
     * @brief Linearly interpolates a table with one parameter dimension.
     * @return the interpolated value
     */
    double interpolate (gslpp::matrix<double> arrayTab, double x);

    /**
     * @brief Linearly interpolates a table with two parameter dimensions.
     * @return the interpolated value
     */
    double interpolate2D (gslpp::matrix<double> arrayTab, double x, double y);

    /**
     * @brief Fills all required arrays with the values read from the tables.
     */
    void read();

    /**
     * @brief SM Higgs branching ratio tables (obtained with HDECAY 6.10), depending on the Higgs mass.
     */
    gslpp::matrix<double> br_tt, br_bb, br_tautau, br_cc, br_mumu, br_ZZ, br_WW;

    /**
     * @brief LHC production cross section percentage contributions (derived from the cross sections provided by the LHC Higgs Cross Section Working Group), depending on the Higgs mass.
     */
    gslpp::matrix<double> pc_ggF, pc_VBF, pc_WH, pc_ZH, pc_ttH;

    /**
     * @brief Total SM decay width (obtained with HDECAY 6.10), depending on the Higgs mass.
     */
    gslpp::matrix<double> GammaHtotSM;

    /**
     * @brief HIGLU v4.00 cross sections, depending on the Higgs mass.
     */
    gslpp::matrix<double> cs_ggH, cs_ggH_tt, cs_ggH_bb, cs_ggA, cs_ggA_tt, cs_ggA_bb;

    /**
     * @brief HiggsBounds 4.1.0 @f$b\bar b \to H@f$ cross sections, depending on the Higgs mass.
     */
    gslpp::matrix<double> cs_bbFtoHP;

    /**
     * @brief ATLAS @f$95\%@f$ upper cross section limits, depending on the Higgs mass.
     */
    gslpp::matrix<double> ATLAS_ggF_phi_gaga, ATLAS_ggF_phi_tautau, ATLAS_bbF_phi_tautau, ATLAS_ggF_A_hZ_tautauZ, ATLAS_ggF_A_hZ_bbZ, ATLAS_pp_phi_tt, ATLAS_ggF_H_WW, ATLAS_VBF_H_WW, ATLAS_ggF_H_hh;

    /**
     * @brief CMS @f$95\%@f$ upper signal strength limits, depending on the Higgs mass.
     */
    gslpp::matrix<double> CMS_pp_H_ZZ;

    /**
     * @brief CMS @f$95\%@f$ upper cross section limits, depending on the Higgs mass.
     */
    gslpp::matrix<double> CMS_ggF_A_hZ_bbll, CMS_pp_H_hh_gagabb, CMS_pp_H_hh_bbbb, CMS_bbF_phi_bb, CMS_ggF_phi_tautau, CMS_bbF_phi_tautau, CMS_ggF_phi_gaga, CMS_ggF_H_hh_bbtautau, CMS_ggF_A_hZ_tautaull;

    /**
     * @brief @f$b\to s \gamma@f$ table, depending on logtb and the logarithm of the charged Higgs mass.
     */
    gslpp::matrix<double> arraybsgamma;

    /**
     * @brief Interpolating function for the SM branching ratio to two top quarks.
     * @return @f$BR^{\text{SM}}(H\to t\bar t)@f$
     */
    double ip_Br_HPtott(double mass);

    /**
     * @brief Interpolating function for the SM branching ratio to two bottom quarks.
     * @return @f$BR^{\text{SM}}(H\to b\bar b)@f$
     */
    double ip_Br_HPtobb(double mass);

    /**
     * @brief Interpolating function for the SM branching ratio to two tau leptons.
     * @return @f$BR^{\text{SM}}(H\to \tau\tau)@f$
     */
    double ip_Br_HPtotautau(double mass);

    /**
     * @brief Interpolating function for the SM branching ratio to two charm quarks.
     * @return @f$BR^{\text{SM}}(H\to c\bar c)@f$
     */
    double ip_Br_HPtocc(double mass);

    /**
     * @brief Interpolating function for the SM branching ratio to two muons.
     * @return @f$BR^{\text{SM}}(H\to \mu \mu)@f$
     */
    double ip_Br_HPtomumu(double mass);

    /**
     * @brief Interpolating function for the SM branching ratio to two @f$Z@f$ bosons.
     * @return @f$BR^{\text{SM}}(H\to ZZ)@f$
     */
    double ip_Br_HPtoZZ(double mass);

    /**
     * @brief Interpolating function for the SM branching ratio to two @f$W@f$ bosons.
     * @return @f$BR^{\text{SM}}(H\to WW)@f$
     */
    double ip_Br_HPtoWW(double mass);

    /**
     * @brief Interpolating function for the SM percentage contribution of gluon-gluon fusion to the total Higgs production cross section.
     * @return @f$pc(gg\to H)@f$
     */
    double ip_pc_ggFtoHP(double mass);

    /**
     * @brief Interpolating function for the SM percentage contribution of vector boson fusion to the total Higgs production cross section.
     * @return @f$pc(VV\to H)@f$
     */
    double ip_pc_VBFtoHP(double mass);

    /**
     * @brief Interpolating function for the SM percentage contribution of @f$W@f$ Higgsstrahlung to the total Higgs production cross section.
     * @return @f$pc(W\to WH)@f$
     */
    double ip_pc_WHP_HP(double mass);

    /**
     * @brief Interpolating function for the SM percentage contribution of @f$Z@f$ Higgsstrahlung to the total Higgs production cross section.
     * @return @f$pc(Z\to ZH)@f$
     */
    double ip_pc_ZHP_HP(double mass);

    /**
     * @brief Interpolating function for the SM percentage contribution of @f$t\bar t@f$ associated production to the total Higgs production cross section.
     * @return @f$pc(t\bar t\to H)@f$
     */
    double ip_pc_ttFtoHP(double mass);

    /**
     * @brief Interpolating function for the total SM Higgs decay width.
     * @return @f$\Gamma^{\text{tot}}_H@f$
     */
    double ip_GammaHPtotSM(double mass);

    /**
     * @brief Interpolating function for the SM Higgs production cross section via gluon-gluon fusion.
     * @return @f$\sigma(gg\to H)@f$
     */
    double ip_cs_ggFtoHP(double mass);

    /**
     * @brief Interpolating function for the SM Higgs production cross section via gluon-gluon fusion (top-loop only).
     * @return @f$\sigma_t(gg\to H)@f$
     */
    double ip_cs_ggHP_tt(double mass);

    /**
     * @brief Interpolating function for the SM Higgs production cross section via gluon-gluon fusion (bottom-loop only).
     * @return @f$\sigma_b(gg\to H)@f$
     */
    double ip_cs_ggHP_bb(double mass);

    /**
     * @brief Interpolating function for the production cross section of a pseudoscalar via gluon-gluon fusion.
     * @return @f$\sigma(gg\to A)@f$
     */
    double ip_cs_ggA(double mass);

    /**
     * @brief Interpolating function for the production cross section of a pseudoscalar via gluon-gluon fusion (top-loop only).
     * @return @f$\sigma_t(gg\to A)@f$
     */
    double ip_cs_ggA_tt(double mass);

    /**
     * @brief Interpolating function for the production cross section of a pseudoscalar via gluon-gluon fusion (bottom-loop only).
     * @return @f$\sigma_b(gg\to A)@f$
     */
    double ip_cs_ggA_bb(double mass);

    /**
     * @brief Interpolating function for the bottom quark associated production cross section of a Higgs.
     * @return @f$\sigma(b\bar b\to H)@f$
     */
    double ip_cs_bbFtoHP(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a gluon-gluon produced scalar resonance decaying to two photons.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to \gamma \gamma)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1407.6583, Figure 4 @cite Aad:2014ioa.
     */
    double ip_ex_ggF_phi_gaga_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a gluon-gluon produced scalar resonance decaying to two tau leptons.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to \tau \tau)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1409.6064, Figure 11a @cite Aad:2014vgg.
     */
    double ip_ex_ggF_phi_tautau_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a bottom quark produced scalar resonance decaying to two tau leptons.
     * @return @f$[\sigma_{bb\to \phi}\cdot BR(\phi\to \tau \tau)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1409.6064, Figure 11b @cite Aad:2014vgg.
     */
    double ip_ex_bbF_phi_tautau_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a gluon-gluon produced pseudoscalar resonance decaying to @f$hZ@f$ of which the Higgs further decays to a @f$\tau@f$ lepton pair.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hZ\to \tau \tau Z)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1502.04478, Figure 3a @cite Aad:2015wra.
     */
    double ip_ex_ggF_A_hZ_tautauZ_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a gluon-gluon produced pseudoscalar resonance decaying to @f$hZ@f$ of which the Higgs further decays to a bottom quark pair.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hZ\to b\bar b Z)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1502.04478, Figure 3b @cite Aad:2015wra.
     */
    double ip_ex_ggF_A_hZ_bbZ_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on scalar resonance decaying to a top quark pair.
     * @return @f$[\sigma_{pp\to \phi}\cdot BR(\phi\to t\bar t)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1505.07018, Figure 11d @cite Aad:2015fna.
     */
    double ip_ex_pp_phi_tt_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a gluon-gluon produced scalar resonance decaying to two @f$W@f$ bosons.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to WW)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1509.00389, Figure 13, left @cite Aad:2015agg.
     */
    double ip_ex_ggF_H_WW_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a vector boson fusion produced scalar resonance decaying to two @f$W@f$ bosons.
     * @return @f$[\sigma_{VV\to \phi}\cdot BR(\phi\to WW)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1509.00389, Figure 13, right @cite Aad:2015agg.
     */
    double ip_ex_VBF_H_WW_ATLAS(double mass);

    /**
     * @brief Interpolating function for the ATLAS upper limit on a gluon-gluon produced scalar resonance decaying to two @f$h@f$ bosons.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hh)]_{\text{ATLAS,95\%}}@f$
     * @details Taken from arXiv:1509.04670, Figure 6 @cite Aad:2015xja.
     */
    double ip_ex_ggF_H_hh_ATLAS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a scalar resonance decaying to two @f$Z@f$ bosons.
     * @return @f$[\mu_H(H\to ZZ)]_{\text{CMS,95\%}}@f$
     * @details Taken from arXiv:1504.00936, Figure 7, bottom right @cite Khachatryan:2015cwa.
     */
    double ip_ex_pp_H_ZZ_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a gluon-gluon produced pseudoscalar resonance decaying to @f$hZ@f$ which further decay to a bottom quark pair and a light lepton pair.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hZ\to b\bar b \ell \ell)]_{\text{CMS,95\%}}@f$
     * @details Taken from arXiv:1504.04710, Figure 3 @cite Khachatryan:2015lba.
     */
    double ip_ex_ggF_A_hZ_bbll_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a scalar resonance decaying to two @f$h@f$ bosons which further decay to a photon pair and a bottom quark pair.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hh\to \gamma \gamma b\bar b)]_{\text{CMS,95\%}}@f$
     * @details Taken from CMS-PAS-HIG-13-032, Figure 8 @cite CMS:2014ipa.
     */
    double ip_ex_pp_phi_hh_gagabb_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a scalar resonance decaying to two @f$h@f$ bosons which further decay to two bottom quark pairs.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hh\to b\bar b b\bar b)]_{\text{CMS,95\%}}@f$
     * @details Taken from arXiv:1503.04114, Figure 5, left @cite Khachatryan:2015yea.
     */
    double ip_ex_pp_phi_hh_bbbb_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a bottom quark produced scalar resonance decaying to two bottom quarks.
     * @return @f$[\sigma_{bb\to \phi}\cdot BR(\phi\to b\bar b)]_{\text{CMS,95\%}}@f$
     * @details Taken from CMS-HIG-14-017, Figure 6 @cite Khachatryan:2015tra.
     */
    double ip_ex_bbF_phi_bb_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a gluon-gluon produced scalar resonance decaying to two tau leptons.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to \tau \tau)]_{\text{CMS,95\%}}@f$
     * @details Taken from CMS-PAS-HIG-14-029, Figure 10-a @cite CMS:2015mca.
     */
    double ip_ex_ggF_phi_tautau_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a bottom quark produced scalar resonance decaying to two tau leptons.
     * @return @f$[\sigma_{bb\to \phi}\cdot BR(\phi\to \tau \tau)]_{\text{CMS,95\%}}@f$
     * @details Taken from CMS-PAS-HIG-14-029, Figure 10-b @cite CMS:2015mca.
     */
    double ip_ex_bbF_phi_tautau_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a gluon-gluon produced scalar resonance decaying to two photons.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to \gamma \gamma)]_{\text{CMS,95\%}}@f$
     * @details Taken from arXiv:1506.02301, Figure 7, left @cite Khachatryan:2015qba.
     */
    double ip_ex_ggF_phi_gaga_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a gluon-gluon produced scalar resonance decaying to two @f$h@f$ bosons which further decay to a bottom quark pair and a @f$\tau@f$ lepton pair.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hh\to b\bar b \tau \tau)]_{\text{CMS,95\%}}@f$
     * @details Taken from arXiv:1510.01181, Figure 8, bottom right @cite Khachatryan:2015tha.
     */
    double ip_ex_ggF_H_hh_bbtautau_CMS(double mass);

    /**
     * @brief Interpolating function for the CMS upper limit on a gluon-gluon produced pseudoscalar resonance decaying to @f$hZ@f$ which further decay to a @f$\tau@f$ lepton pair and a light lepton pair.
     * @return @f$[\sigma_{gg\to \phi}\cdot BR(\phi\to hZ\to \tau \tau \ell \ell)]_{\text{CMS,95\%}}@f$
     * @details Taken from arXiv:1510.01181, Figure 10, left @cite Khachatryan:2015tha.
     */
    double ip_ex_ggF_A_hZ_tautaull_CMS(double mass);

    /**
     * @brief Interpolating function for the NNLO value for the branching ratio of @f$b\to s \gamma@f$ decays in the THDM.
     * @return @f$BR(B\to X_s \gamma)@f$
     * @details Values derived with the help of the authors of @cite Misiak:2015xwa.
     */
    double ip_ex_bsgamma(double logtb, double logmHp);

    /*One-loop functions*/

    gslpp::complex B0_MZ2_0_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const;
    gslpp::complex B0_MZ2_0_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const;
    gslpp::complex B0_MZ2_0_MZ2_mHh2(const double MZ2, const double mHh2) const;
    gslpp::complex B0_MZ2_0_MZ2_mHl2(const double MZ2, const double mHl2) const;
    gslpp::complex B0_MZ2_MW2_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const;
    gslpp::complex B0_MZ2_MW2_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const;
    gslpp::complex B0_MZ2_MZ2_MZ2_mHh2(const double MZ2, const double mHh2) const;
    gslpp::complex B0_MZ2_MZ2_MZ2_mHl2(const double MZ2, const double mHl2) const;

    gslpp::complex B00_MZ2_0_mA2_mHp2(const double MZ2, const double mA2, const double mHp2) const;
    gslpp::complex B00_MZ2_0_mHh2_mA2(const double MZ2, const double mHh2, const double mA2) const;
    gslpp::complex B00_MZ2_0_mHh2_mHp2(const double MZ2, const double mHh2, const double mHp2) const;
    gslpp::complex B00_MZ2_0_mHl2_mA2(const double MZ2, const double mHl2, const double mA2) const;
    gslpp::complex B00_MZ2_0_mHl2_mHp2(const double MZ2, const double mHl2, const double mHp2) const;
    gslpp::complex B00_MZ2_0_mHp2_mHp2(const double MZ2, const double mHp2) const;
    gslpp::complex B00_MZ2_0_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const;
    gslpp::complex B00_MZ2_0_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const;
    gslpp::complex B00_MZ2_0_MZ2_mHh2(const double MZ2, const double mHh2) const;
    gslpp::complex B00_MZ2_0_MZ2_mHl2(const double MZ2, const double mHl2) const;
    gslpp::complex B00_MZ2_MW2_mA2_mHp2(const double MZ2, const double MW2, const double mA2, const double mHp2) const;
    gslpp::complex B00_MZ2_MW2_mHh2_mHp2(const double MZ2, const double MW2, const double mHh2, const double mHp2) const;
    gslpp::complex B00_MZ2_MW2_mHl2_mHp2(const double MZ2, const double MW2, const double mHl2, const double mHp2) const;
    gslpp::complex B00_MZ2_MW2_mHp2_mHp2(const double MZ2, const double MW2, const double mHp2) const;
    gslpp::complex B00_MZ2_MW2_MW2_mHh2(const double MZ2, const double MW2, const double mHh2) const;
    gslpp::complex B00_MZ2_MW2_MW2_mHl2(const double MZ2, const double MW2, const double mHl2) const;
    gslpp::complex B00_MZ2_MZ2_mHh2_mA2(const double MZ2, const double mHh2, const double mA2) const;
    gslpp::complex B00_MZ2_MZ2_mHl2_mA2(const double MZ2, const double mHl2, const double mA2) const;
    gslpp::complex B00_MZ2_MZ2_mHp2_mHp2(const double MZ2, const double mHp2) const;
    gslpp::complex B00_MZ2_MZ2_MZ2_mHh2(const double MZ2, const double mHh2) const;
    gslpp::complex B00_MZ2_MZ2_MZ2_mHl2(const double MZ2, const double mHl2) const;

    double ghHpHm(const double mHp2, const double tanb, const double m12_2, const double bma, const double mHl, const double vev) const;
    double g_HH_HpHm(const double mHp2, const double mHh2, const double tanb, const double m12_2, const double bma, const double vev) const;

    gslpp::complex I_h_U(const double mHl, const double Mu, const double Mc, const double Mt) const;
    gslpp::complex I_HH_U(const double mHh2, const double Mc, const double Mt) const;
    gslpp::complex I_A_U(const double mA2, const double Mc, const double Mt) const;
    gslpp::complex I_h_D(const double mHl, const double Md, const double Ms, const double Mb) const;
    gslpp::complex I_HH_D(const double mHh2, const double Ms, const double Mb) const;
    gslpp::complex I_A_D(const double mA2, const double Ms, const double Mb) const;
    gslpp::complex I_h_L(const double mHl, const double Me, const double Mmu, const double Mtau) const;
    gslpp::complex I_HH_L(const double mHh2, const double Mmu, const double Mtau) const;
    gslpp::complex I_A_L(const double mA2, const double Mmu, const double Mtau) const;
    gslpp::complex I_H_W(const double mH, const double MW) const;
    gslpp::complex I_H_Hp(const double mHp2, const double mH) const;

    gslpp::complex A_h_U(const double mHl, const double cW2, const double Mu, const double Mc, const double Mt, const double MZ) const;
    gslpp::complex A_HH_U(const double mHh2, const double cW2, const double Mc, const double Mt, const double MZ) const;
    gslpp::complex A_A_U(const double mA2, const double cW2, const double Mc, const double Mt, const double MZ) const;
    gslpp::complex A_h_D(const double mHl, const double cW2, const double Md, const double Ms, const double Mb, const double MZ) const;
    gslpp::complex A_HH_D(const double mHh2, const double cW2, const double Ms, const double Mb, const double MZ) const;
    gslpp::complex A_A_D(const double mA2, const double cW2, const double Ms, const double Mb, const double MZ) const;
    gslpp::complex A_h_L(const double mHl, const double cW2, const double Me, const double Mmu, const double Mtau, const double MZ) const;
    gslpp::complex A_HH_L(const double mHh2, const double cW2, const double Mmu, const double Mtau, const double MZ) const;
    gslpp::complex A_A_L(const double mA2, const double cW2, const double Mmu, const double Mtau, const double MZ) const;
    gslpp::complex A_H_W(const double mH, const double cW2, const double MW, const double MZ) const;
    gslpp::complex A_H_Hp(const double mHp2, const double mH, const double cW2, const double MZ) const;

    /**
     * @brief Kaellen function
     * @return @f$\kappa(a,b,c)=\frac{1}{2a}\sqrt{a^2+b^a+c^2-2ab-2ac-2bc}@f$
     */
    double KaellenFunction(const double a2, const double b2, const double c2) const;

    double cW2THDM(const double c02) const;
    double MWTHDM(const double MW) const;

    
    
    void computeSignalStrengthQuantities();

    void computeHHquantities();

    void computeAquantities();

    ////////////////////////////////////////////////////////////////////////////
    void updateCache();

    /**
     * @brief SM branching ratio of @f$h\to b \bar b@f$.
     * @return @f$BR{\text SM}(h\to b \bar b)@f$
     */
    double BrSM_htobb;

    /**
     * @brief SM branching ratio of @f$h\to \gamma \gamma@f$.
     * @return @f$BR{\text SM}(h\to \gamma \gamma)@f$
     */
    double BrSM_htogaga;

    /**
     * @brief SM branching ratio of @f$h\to \tau \tau@f$.
     * @return @f$BR{\text SM}(h\to \tau \tau)@f$
     */
    double BrSM_htotautau;

    /**
     * @brief Squared relative coupling of @f$h@f$ to two down type quarks.
     * @return @f$r^{(h)}_{Q_dQ_d}@f$
     * @details Depends on the type of @f$Z_2@f$ symmetry.
     */
    double rh_QdQd;

    /**
     * @brief Squared relative coupling of @f$h@f$ to two massive vector bosons.
     * @return @f$r^{(h)}_{WW}=r^{(h)}_{ZZ}@f$
     */
    double rh_VV;

    /**
     * @brief Squared relative coupling of @f$h@f$ to two charged leptons.
     * @return @f$r^{(h)}_{\ell \ell}@f$
     * @details Depends on the type of @f$Z_2@f$ symmetry.
     */
    double rh_ll;

    /**
     * @brief Squared relative coupling of @f$h@f$ to two photons.
     * @return @f$r^{(h)}_{\gamma \gamma}@f$
     * @details Depends on the type of @f$Z_2@f$ symmetry.
     */
    double rh_gaga;

    /**
     * @brief Squared relative coupling of @f$h@f$ to two gluons.
     * @return @f$r^{(h)}_{gg}@f$
     * @details Depends on the type of @f$Z_2@f$ symmetry.
     */
    double rh_gg;

    /**
     * @brief Ratio of THDM and SM cross sections for ggF and tth production of h.
     * @return @f$\sigma^{\text THDM}_{\text ggF+tth}/\sigma^{\text SM}_{\text ggF+tth}@f$
     */
    double ggF_tth;

    /**
     * @brief Ratio of THDM and SM cross sections for VBF and Vh production of h.
     * @return @f$\sigma^{\text THDM}_{\text VBF+Vh}/\sigma^{\text SM}_{\text VBF+Vh}@f$
     */
    double VBF_Vh;

    /**
     * @brief Sum of the modified branching ratios.
     * @return @f$\sum _i r^{(h)}_{i} BR^{\text SM}(h\to i)@f$
     */
    double sumModBRs;

    /**
     * @brief Total h decay rate in the THDM.
     * @return @f$\Gamma_h@f$
     */
    double Gamma_h;

    /**
     * @brief Squared relative coupling of @f$h@f$ to a @f$Z@f$ boson and a photon.
     * @return @f$r^{(h)}_{Z\gamma}@f$
     * @details Depends on the type of @f$Z_2@f$ symmetry.
     */
    double rh_Zga;

    /**
     * @brief Squared relative coupling of @f$h@f$ to two up type quarks.
     * @return @f$r^{(h)}_{Q_uQ_u}@f$
     */
    double rh_QuQu;

    double THDM_BR_h_bb;
    double THDM_BR_h_gaga;
    double THDM_BR_h_tautau;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to H\to \tau\tau@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to H}\cdot BR^{\text{THDM}}(H\to \tau\tau)@f$
     */
    double ggF_H_tautau_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$b\bar b\to H\to \tau\tau@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{b\bar b\to H}\cdot BR^{\text{THDM}}(H\to \tau\tau)@f$
     */
    double bbF_H_tautau_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to H\to \gamma\gamma@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to H}\cdot BR^{\text{THDM}}(H\to \gamma\gamma)@f$
     */
    double ggF_H_gaga_TH;  

    /**
     * @brief Signal strength for the process @f$pp\to H\to ZZ@f$ at the LHC with 8 TeV.
     * @return @f$\mu_H^{\text{THDM}}(H\to ZZ)=[\sigma^{\text{THDM}}_{pp\to H}\cdot BR^{\text{THDM}}(H\to ZZ)] / [\sigma^{\text{SM}}_{pp\to H}\cdot BR^{\text{SM}}(H\to ZZ)]@f$
     */
    double pp_H_ZZ_TH; 

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to H\to WW@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to H}\cdot BR^{\text{THDM}}(H\to WW)@f$
     */
    double ggF_H_WW_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$VV\to H\to WW@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{VV\to H}\cdot BR^{\text{THDM}}(H\to WW)@f$
     */
    double VBF_H_WW_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to H\to hh@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to H}\cdot BR^{\text{THDM}}(H\to hh)@f$
     */
    double ggF_H_hh_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$pp\to H\to hh@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{pp\to H}\cdot BR^{\text{THDM}}(H\to hh)@f$
     */
    double pp_H_hh_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to H\to hh\to b\bar b \tau\tau@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to H}\cdot BR^{\text{THDM}}(H\to hh\to b\bar b \tau\tau)@f$
     */
    double ggF_H_hh_bbtautau_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$pp\to H\to hh\to b\bar b b\bar b@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{pp\to H}\cdot BR^{\text{THDM}}(H\to hh\to b\bar b b\bar b)@f$
     */
    double pp_H_hh_bbbb_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$pp\to H\to hh\to \gamma\gamma b\bar b@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{pp\to H}\cdot BR^{\text{THDM}}(H\to hh\to \gamma\gamma b\bar b)@f$
     */
    double pp_H_hh_gagabb_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$pp\to H\to t\bar t@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{pp\to H}\cdot BR^{\text{THDM}}(H\to t\bar t)@f$
     */
    double pp_H_tt_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$b\bar b\to H\to b\bar b@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{b\bar b\to H}\cdot BR^{\text{THDM}}(H\to b\bar b)@f$
     */
    double bbF_H_bb_TH;

    /**
     * @brief Total decay width of the heavy CP-even Higgs @f$H@f$.
     * @return @f$\Gamma_H@f$
     */
    double GammaHtot;

//    /**
//     * @brief Squared relative coupling of @f$H@f$ to two photons.
//     * @return @f$r^{(H)}_{\gamma \gamma}@f$
//     * @details Depends on the type of @f$Z_2@f$ symmetry.
//     */
//    double rHH_gaga;

    /**
     * @brief Squared relative coupling of @f$H@f$ to two gluons.
     * @return @f$r^{(H)}_{gg}@f$
     * @details Depends on the type of @f$Z_2@f$ symmetry.
     */
    double rHH_gg;

    /**
     * @brief @f$H@f$ branching ratio to two light Higgs bosons.
     * @return @f$BR(H\to hh)@f$
     */
    double Br_Htohh;

    /**
     * @brief @f$H@f$ branching ratio to two CP-odd Higgs bosons.
     * @return @f$BR(H\to AA)@f$
     */
    double Br_HtoAA;

    /**
     * @brief @f$H@f$ branching ratio to two charged Higgs bosons.
     * @return @f$BR(H\to H^\pm H^\mp)@f$
     */
    double Br_HtoHpHm;

    /**
     * @brief @f$H@f$ branching ratio to two light Higgs bosons.
     * @return @f$BR(H\to hh)@f$
     */
    double Br_HtoAZ;

    /**
     * @brief @f$H@f$ branching ratio to two light Higgs bosons.
     * @return @f$BR(H\to hh)@f$
     */
    double Br_HtoHpW;

    double THoEX_ggF_H_tautau_ATLAS;
    double THoEX_ggF_H_tautau_CMS;
    double THoEX_bbF_H_tautau_ATLAS;
    double THoEX_bbF_H_tautau_CMS;
    double THoEX_ggF_H_gaga_ATLAS;
    double THoEX_ggF_H_gaga_CMS;
    double THoEX_pp_H_ZZ_CMS;
    double THoEX_ggF_H_WW_ATLAS;
    double THoEX_VBF_H_WW_ATLAS;
    double THoEX_ggF_H_hh_ATLAS;
    double THoEX_ggF_H_hh_bbtautau_CMS;
    double THoEX_pp_H_hh_bbbb_CMS;
    double THoEX_pp_H_hh_gagabb_CMS;
    double THoEX_pp_H_tt_ATLAS;
    double THoEX_bbF_H_bb_CMS;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to A\to \tau\tau@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to A}\cdot BR^{\text{THDM}}(A\to \tau\tau)@f$
     */
    double ggF_A_tautau_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$b\bar b\to A\to \tau\tau@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{b\bar b\to A}\cdot BR^{\text{THDM}}(A\to \tau\tau)@f$
     */
    double bbF_A_tautau_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to A\to \gamma\gamma@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to A}\cdot BR^{\text{THDM}}(A\to \gamma\gamma)@f$
     */
    double ggF_A_gaga_TH;
    /**
     * @brief Cross section times branching ratio for the process @f$gg\to A\to hZ@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to A}\cdot BR^{\text{THDM}}(A\to hZ)@f$
     */
    double ggF_A_hZ_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to A\to hZ \to b\bar b \ell \ell@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to A}\cdot BR^{\text{THDM}}(A\to hZ \to b\bar b \ell \ell)@f$
     */
    double ggF_A_hZ_bbll_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to A\to hZ \to b\bar b Z@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to A}\cdot BR^{\text{THDM}}(A\to hZ \to b\bar b Z)@f$
     */
    double ggF_A_hZ_bbZ_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to A\to hZ \to \tau \tau \ell \ell@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to A}\cdot BR^{\text{THDM}}(A\to hZ \to \tau \tau \ell \ell)@f$
     */
    double ggF_A_hZ_tautaull_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$gg\to A\to hZ \to \tau \tau Z@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{gg\to A}\cdot BR^{\text{THDM}}(A\to hZ \to \tau \tau Z)@f$
     */
    double ggF_A_hZ_tautauZ_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$pp\to A\to t\bar t@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{pp\to A}\cdot BR^{\text{THDM}}(A\to t\bar t)@f$
     */
    double pp_A_tt_TH;

    /**
     * @brief Cross section times branching ratio for the process @f$b\bar b\to A\to b\bar b@f$ at the LHC with 8 TeV.
     * @return @f$\sigma^{\text{THDM}}_{b\bar b\to A}\cdot BR^{\text{THDM}}(A\to b\bar b)@f$
     */
    double bbF_A_bb_TH;

    /**
     * @brief Total decay width of the CP-odd Higgs @f$A@f$.
     * @return @f$\Gamma_A@f$
     */
    double GammaAtot;

//    /**
//     * @brief Squared relative coupling of @f$A@f$ to two photons.
//     * @return @f$r^{(A)}_{\gamma \gamma}@f$
//     * @details Depends on the type of @f$Z_2@f$ symmetry.
//     */
//    double rA_gaga;

    /**
     * @brief Squared relative coupling of @f$A@f$ to two gluons.
     * @return @f$r^{(A)}_{gg}@f$
     * @details Depends on the type of @f$Z_2@f$ symmetry.
     */
    double rA_gg;

    /**
     * @brief @f$A@f$ branching ratio to an @f$H@f$ and a @f$Z@f$ boson.
     * @return @f$BR(A\to HZ)@f$
     */
    double Br_AtoHZ;

    /**
     * @brief @f$A@f$ branching ratio to an @f$h@f$ and a @f$Z@f$ boson.
     * @return @f$BR(A\to hZ)@f$
     */
    double Br_AtohZ;

    /**
     * @brief @f$A@f$ branching ratio to a charged Higgs and a @f$W^\mp@f$ boson.
     * @return @f$BR(A\to H^\pm W^\mp)@f$
     */
    double Br_AtoHpW;

    double THoEX_ggF_A_tautau_ATLAS;
    double THoEX_ggF_A_tautau_CMS;
    double THoEX_bbF_A_tautau_ATLAS;
    double THoEX_bbF_A_tautau_CMS;
    double THoEX_ggF_A_gaga_ATLAS;
    double THoEX_ggF_A_gaga_CMS;
    double THoEX_ggF_A_hZ_bbll_CMS;
    double THoEX_ggF_A_hZ_bbZ_ATLAS;
    double THoEX_ggF_A_hZ_tautaull_CMS;
    double THoEX_ggF_A_hZ_tautauZ_ATLAS;
    double THoEX_pp_A_tt_ATLAS;
    double THoEX_bbF_A_bb_CMS;

private:

    const PVfunctions PV;
    const THDM * myTHDM;

    double bma;
    double tanb;
    double m12_2;
    double mHh2;
    double mA2;
    double mHp2;
    double MW;
    double cW2;
    double mHl;
    double vev;
    double Ale;
    double Als;
    double Mt;
    double Mb;
    double Mtau;
    double Mc;
    double Ms;
    double Mmu;
    double Mu;
    double Md;
    double Me;
    double MZ;
    std::string modelflag;

    ////////////////////////////////////////////////////////////////////////////
    //Caches

    /*One-loop functions*/

    mutable gslpp::complex B0_MZ2_0_MW2_mHh2_cache[4][CacheSize];
    mutable gslpp::complex B0_MZ2_0_MW2_mHl2_cache[4][CacheSize];
    mutable gslpp::complex B0_MZ2_0_MZ2_mHh2_cache[3][CacheSize];
    mutable gslpp::complex B0_MZ2_0_MZ2_mHl2_cache[3][CacheSize];
    mutable gslpp::complex B0_MZ2_MW2_MW2_mHh2_cache[4][CacheSize];
    mutable gslpp::complex B0_MZ2_MW2_MW2_mHl2_cache[4][CacheSize];
    mutable gslpp::complex B0_MZ2_MZ2_MZ2_mHh2_cache[3][CacheSize];
    mutable gslpp::complex B0_MZ2_MZ2_MZ2_mHl2_cache[3][CacheSize];

    mutable gslpp::complex B00_MZ2_0_mA2_mHp2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_0_mHh2_mA2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_0_mHh2_mHp2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_0_mHl2_mA2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_0_mHl2_mHp2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_0_mHp2_mHp2_cache[3][CacheSize];
    mutable gslpp::complex B00_MZ2_0_MW2_mHh2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_0_MW2_mHl2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_0_MZ2_mHh2_cache[3][CacheSize];
    mutable gslpp::complex B00_MZ2_0_MZ2_mHl2_cache[3][CacheSize];
    mutable gslpp::complex B00_MZ2_MW2_mA2_mHp2_cache[5][CacheSize];
    mutable gslpp::complex B00_MZ2_MW2_mHh2_mHp2_cache[5][CacheSize];
    mutable gslpp::complex B00_MZ2_MW2_mHl2_mHp2_cache[5][CacheSize];
    mutable gslpp::complex B00_MZ2_MW2_mHp2_mHp2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_MW2_MW2_mHh2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_MW2_MW2_mHl2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_MZ2_mHh2_mA2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_MZ2_mHl2_mA2_cache[4][CacheSize];
    mutable gslpp::complex B00_MZ2_MZ2_mHp2_mHp2_cache[3][CacheSize];
    mutable gslpp::complex B00_MZ2_MZ2_MZ2_mHh2_cache[3][CacheSize];
    mutable gslpp::complex B00_MZ2_MZ2_MZ2_mHl2_cache[3][CacheSize];

    mutable double ip_Br_HPtott_cache[2][CacheSize];
    mutable double ip_Br_HPtobb_cache[2][CacheSize];
    mutable double ip_Br_HPtotautau_cache[2][CacheSize];
    mutable double ip_Br_HPtocc_cache[2][CacheSize];
    mutable double ip_Br_HPtomumu_cache[2][CacheSize];
    mutable double ip_Br_HPtoZZ_cache[2][CacheSize];
    mutable double ip_Br_HPtoWW_cache[2][CacheSize];
    mutable double ip_pc_ggFtoHP_cache[2][CacheSize];
    mutable double ip_pc_VBFtoHP_cache[2][CacheSize];
    mutable double ip_pc_WHP_HP_cache[2][CacheSize];
    mutable double ip_pc_ZHP_HP_cache[2][CacheSize];
    mutable double ip_pc_ttFtoHP_cache[2][CacheSize];
    mutable double ip_GammaHPtotSM_cache[2][CacheSize];
    mutable double ip_cs_ggFtoHP_cache[2][CacheSize];
    mutable double ip_cs_ggHP_tt_cache[2][CacheSize];
    mutable double ip_cs_ggHP_bb_cache[2][CacheSize];
    mutable double ip_cs_ggA_cache[2][CacheSize];
    mutable double ip_cs_ggA_tt_cache[2][CacheSize];
    mutable double ip_cs_ggA_bb_cache[2][CacheSize];
    mutable double ip_cs_bbFtoHP_cache[2][CacheSize];
    mutable double ip_ex_ggF_phi_tautau_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_bbF_phi_tautau_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_ggF_A_hZ_tautauZ_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_ggF_A_hZ_bbZ_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_pp_phi_tt_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_ggF_H_WW_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_VBF_H_WW_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_ggF_H_hh_ATLAS_cache[2][CacheSize];
    mutable double ip_ex_pp_H_ZZ_CMS_cache[2][CacheSize];
    mutable double ip_ex_ggF_A_hZ_bbll_CMS_cache[2][CacheSize];
    mutable double ip_ex_pp_phi_hh_gagabb_CMS_cache[2][CacheSize];
    mutable double ip_ex_pp_phi_hh_bbbb_CMS_cache[2][CacheSize];
    mutable double ip_ex_bbF_phi_bb_CMS_cache[2][CacheSize];
    mutable double ip_ex_ggF_phi_tautau_CMS_cache[2][CacheSize];
    mutable double ip_ex_bbF_phi_tautau_CMS_cache[2][CacheSize];
    mutable double ip_ex_ggF_phi_gaga_CMS_cache[2][CacheSize];
    mutable double ip_ex_ggF_H_hh_bbtautau_CMS_cache[2][CacheSize];
    mutable double ip_ex_ggF_A_hZ_tautaull_CMS_cache[2][CacheSize];
    mutable double ip_ex_bsgamma_cache[3][CacheSize];

    mutable double ghHpHm_cache[7][CacheSize];
    mutable double g_HH_HpHm_cache[7][CacheSize];

    mutable gslpp::complex I_h_U_cache[5][CacheSize];
    mutable gslpp::complex I_HH_U_cache[4][CacheSize];
    mutable gslpp::complex I_A_U_cache[4][CacheSize];
    mutable gslpp::complex I_h_D_cache[5][CacheSize];
    mutable gslpp::complex I_HH_D_cache[4][CacheSize];
    mutable gslpp::complex I_A_D_cache[4][CacheSize];
    mutable gslpp::complex I_h_L_cache[5][CacheSize];
    mutable gslpp::complex I_HH_L_cache[4][CacheSize];
    mutable gslpp::complex I_A_L_cache[4][CacheSize];
    mutable gslpp::complex I_H_W_cache[3][CacheSize];
    mutable gslpp::complex I_H_Hp_cache[3][CacheSize];

    mutable gslpp::complex A_h_U_cache[7][CacheSize];
    mutable gslpp::complex A_HH_U_cache[6][CacheSize];
    mutable gslpp::complex A_A_U_cache[6][CacheSize];
    mutable gslpp::complex A_h_D_cache[7][CacheSize];
    mutable gslpp::complex A_HH_D_cache[6][CacheSize];
    mutable gslpp::complex A_A_D_cache[6][CacheSize];
    mutable gslpp::complex A_h_L_cache[7][CacheSize];
    mutable gslpp::complex A_HH_L_cache[6][CacheSize];
    mutable gslpp::complex A_A_L_cache[6][CacheSize];
    mutable gslpp::complex A_H_W_cache[5][CacheSize];
    mutable gslpp::complex A_H_Hp_cache[5][CacheSize];

    mutable double KaellenFunction_cache[4][CacheSize];

    /**
     * @brief f function for the gamma gamma coupling to h, H and A
     * @return @f$f(x)@f$
     * @details The definition can be found in (2.19) of @cite Gunion:1989we.
     */
    gslpp::complex f_func(const double x) const;

    /**
     * @brief g function for the Int1 function
     * @return @f$g(x)@f$
     * @details The definition can be found in (2.24) of @cite Gunion:1989we.
     */
    gslpp::complex g_func(const double x) const;

    /**
     * @brief @f$I_1@f$ function for Z gamma coupling to h, H and A
     * @return @f$I_1(\tau,\lambda)@f$
     * @details The definition can be found in (2.24) of @cite Gunion:1989we.
     */
    gslpp::complex Int1(const double tau, const double lambda) const;

    /**
     * @brief @f$I_2@f$ function for Z gamma coupling to h, H and A
     * @return @f$I_2(\tau,\lambda)@f$
     * @details The definition can be found in (2.24) of @cite Gunion:1989we.
     */
    gslpp::complex Int2(const double tau, const double lambda) const;

    /**
     * @brief Heaviside @f$\Theta@f$ function
     * @return @f$\Theta(x)@f$
     * @details Gives 1 for @f$x\geq 0@f$ and 0 for @f$x<0@f$.
     */
    int HSTheta (const double x) const;
};

#endif	/* THDMCACHE_H */
