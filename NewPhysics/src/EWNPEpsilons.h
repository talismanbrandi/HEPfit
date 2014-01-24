/*
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef EWNPEPSILONS_H
#define	EWNPEPSILONS_H

#include <EWSM.h>
#include <EWepsilons.h>

/**
 * @class EWNPEpsilons
 * @brief A class for new physics in the form of contributions to the \f$\varepsilon_{1,2,3,b}\f$ parameters.
 * @ingroup NewPhysics
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class contains the necesary functions to compute new physics tree-level corrections to electroweak precision
 * observables, in the form of contributions to the \f$\varepsilon_{1,2,3,b}\f$ parameters. These corrections are
 * parameterized in terms of the \f$\varepsilon_i\f$ contributions to \f$M_W\f$, and to \f$Z\f$-pole observables
 * through the corrections to the different neutral-current effective couplings to leptons and quarks.
 */
class EWNPEpsilons : public EWSM {
public:

    EWNPEpsilons(const StandardModel& SM_i);


    ////////////////////////////////////////////////////////////////////////

    double Mw_NPEpsilons() const;


    ////////////////////////////////////////////////////////////////////////

    /**
     * @param[in] l name of a lepton
     * @return the effective neutral-current coupling @f$\rho_Z^l@f$ including the \f$\varepsilon_i\f$ contributions 
     */
    virtual complex rhoZ_l(const StandardModel::lepton l) const;

    /**
     * @param[in] q name of a quark
     * @return the effective neutral-current coupling @f$\rho_Z^q@f$ including the \f$\varepsilon_i\f$ contributions
     */
    virtual complex rhoZ_q(const StandardModel::quark q) const;

    /**
     * @param[in] l name of a lepton
     * @return the effective neutral-current coupling @f$\kappa_Z^l@f$ including the \f$\varepsilon_i\f$ contributions 
     */
    virtual complex kappaZ_l(const StandardModel::lepton l) const;

    /**
     * @param[in] q name of a quark
     * @return the effective neutral-current coupling @f$\kappa_Z^q@f$ including the \f$\varepsilon_i\f$ contributions
     */
    virtual complex kappaZ_q(const StandardModel::quark q) const;

    /**
     * @param[in] l name of a lepton
     * @return the effective neutral-current vector coupling @f$g_V^l@f$ including the \f$\varepsilon_i\f$ contributions
     */
    virtual complex gVl(const StandardModel::lepton l) const;

    /**
     * @param[in] q name of a quark
     * @return the effective neutral-current vector coupling @f$g_V^q@f$ including the \f$\varepsilon_i\f$ contributions
     */
    virtual complex gVq(const StandardModel::quark q) const;

    /**
     * @param[in] l name of a leptonn
     * @return the effective neutral-current axial-vector coupling @f$g_A^l@f$ including the \f$\varepsilon_i\f$ contributions
     */
    virtual complex gAl(const StandardModel::lepton l) const;

    /**
     * @param[in] q name of a quark
     * @return the effective neutral-current axial-vector coupling @f$g_A^q@f$ including the \f$\varepsilon_i\f$ contributions
     */
    virtual complex gAq(const StandardModel::quark q) const;


    ////////////////////////////////////////////////////////////////////////
private:
    const StandardModel& SM;
    EWepsilons* myEWepsilons;
    
};

#endif	/* EWNPEPSILONS_H */
