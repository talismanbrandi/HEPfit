/*
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef NPEPSILONS_PURENP_H
#define	NPEPSILONS_PURENP_H

#include "NPbase.h"

/**
 * @class NPEpsilons_pureNP
 * @brief A model class for new physics in the form of contributions to the
 * \f$\delta\,\varepsilon_{1,2,3,b}\f$ parameters.
 * @ingroup NewPhysics
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This is a Model class containing parameters and functions to work 
 * with the modified epsilon parameters \f$\delta\,\varepsilon_{1,2,3,b}\f$
 * which parameterize only new physics contributions to the electroweak
 * precision observables. 
 * See \cite Altarelli:1990zd, \cite Altarelli:1991fk,\cite Altarelli:1993sz
 * for the original epsilon parameterization.
 *
*
 * @anchor NPEpsilons_pureNPInitialization
 * <h3>Initialization</h3>
 *
 * After creating an instance of the current class with the constructor
 * NPEpsilons_pureNP(), it is required to call the initialization method
 * InitializeModel(), inherited from NPEffective class.
 * In the Monte Carlo run, the constructor as well as the initialization
 * method are called in InputParser::ReadParameters().
 *
 *
 * @anchor NPEpsilons_pureNPParameters
 * <h3>%Model parameters</h3>
 *
 * The model parameters of %NPEpsilons_pureNP are summarized below:
 * <table class="model">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="mod_name">%delEps_1 </td>
 *   <td class="mod_symb">\f$\delta\,\varepsilon_1\f$</td>
 *   <td class="mod_desc">The new physics contribution to \f$\varepsilon_1\f$.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%delEps_2 </td>
 *   <td class="mod_symb">\f$\delta\,\varepsilon_2\f$</td>
 *   <td class="mod_desc">The new physics contribution to \f$\varepsilon_2\f$.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%delEps_3 </td>
 *   <td class="mod_symb">\f$\delta\,\varepsilon_3\f$</td>
 *   <td class="mod_desc">The new physics contribution to \f$\varepsilon_3\f$.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%delEps_b </td>
 *   <td class="mod_symb">\f$\delta\,\varepsilon_b\f$</td>
 *   <td class="mod_desc">The new physics contribution to \f$\varepsilon_b\f$.</td>
 * </tr>
 * </table>
 *
 *
 * @anchor NPEpsilons_pureNPFlags
 * <h3>%Model flags</h3>
 *
 * There is no model flag in the current class.
 *
 *
 * @anchor NPEpsilons_pureNPFunctions
 * <h3>Important member functions</h3>
 *
 * Compared to the base class NPbase, the functions for the following quantities
 * are reimplemented in the current class:
 *
 * @li @f$M_W@f$&nbsp;&nbsp; (with Mw()),
 * @li @f$\Gamma_W@f$&nbsp;&nbsp; (with GammaW()),
 * @li @f$\delta g_V^f@f$&nbsp;&nbsp;(with deltaGVl() and deltaGVq()),
 * @li @f$\delta g_A^f@f$&nbsp;&nbsp;(with deltaGAl() and deltaGAq()),
 *
 * where @f$\Gamma_W@f$ is not available, since it cannot be simply parameterized
 * by the epsilon parameters.
 * In addition, the functions for the epsilon parameters are also provided:
 *
 * @li @f$\varepsilon_1@f$, @f$\varepsilon_2@f$, @f$\varepsilon_3@f$ and
 * @f$\varepsilon_b@f$&nbsp;&nbsp;
 * (with epsilon1(), epsilon2(), epsilon3() and epsilonb()).
 * 
 */
class NPEpsilons_pureNP : public NPbase {
public:
    
    /**
     * @brief The number of the model parameters in %NPEpsilons_pureNP.
     */
    static const int NEPSILONpureNPvars = 4;
    
    /**
     * @brief A string array containing the labels of the model parameters in %NPEpsilons_pureNP.
     */
    static const std::string EPSILONpureNPvars[NEPSILONpureNPvars];

    /**
     * @brief The default constructor.
     */
    NPEpsilons_pureNP();
    
    /**
     * @brief @copybrief Model::Update()
     * @copydetails Model::Update()
     */
    virtual bool Update(const std::map<std::string, double>& DPars);
    
    /**
     * @brief @copybrief Model::CheckParameters()
     * @copydetails Model::CheckParameters()
     */
    virtual bool CheckParameters(const std::map<std::string, double>& DPars);

    ////////////////////////////////////////////////////////////////////////
    
    /**
     * @brief The parameter \f$\varepsilon_1\f$.
     * @return the sum of the SM prediction for \f$\varepsilon_1\f$
     * and the new physics contribution \f$\delta\,\varepsilon_1\f$
     */
    double epsilon1() const;

    /**
     * @brief The parameter \f$\varepsilon_2\f$.
     * @return the sum of the SM prediction for \f$\varepsilon_2\f$
     * and the new physics contribution \f$\delta\,\varepsilon_2\f$

     */
    double epsilon2() const;
    
    /**
     * @brief The parameter \f$\varepsilon_3\f$.
     * @return the sum of the SM prediction for \f$\varepsilon_3\f$
     * and the new physics contribution \f$\delta\,\varepsilon_3\f$
     */
    double epsilon3() const;
    
    /**
     * @brief The parameter \f$\varepsilon_b\f$.
     * @return the sum of the SM prediction for \f$\varepsilon_b\f$
     * and the new physics contribution \f$\delta\,\varepsilon_b\f$
     */
    double epsilonb() const;


    ////////////////////////////////////////////////////////////////////////

    /**
     * @brief @copybrief StandardModel::Mw()
     * @details
     * @f[
     * M_W =
     * M_{W,\mathrm{SM}}
     * \left\{
     * 1 - \frac{1}{2(c_{W,\mathrm{SM}}^2 - s_{W,\mathrm{SM}}^2)}
     * \big[
     * - c_0^2\, \delta\varepsilon_1 + (c_0^2-s_0^2)\, \delta\varepsilon_2
     * + 2s_0^2\, \delta\varepsilon_3
     * \big]
     * \right\}.
     * @f]
     * @return @f$M_W@f$ in GeV
     */
    virtual double Mw() const;

    /**
     * @brief @copybrief StandardModel::GammaW()
     * 
     * @warning This function is not available.
     */
    virtual double GammaW() const;


    ////////////////////////////////////////////////////////////////////////

    /**
     * @brief @copybrief NPbase::deltaGVq()
     * @details
     * @f[
     * \delta g_V^q
     * = \Big( g_{V,\mathrm{SM}}^q - g_{A,\mathrm{SM}}^q \Big)
     *   \frac{\delta\,\varepsilon_3-c_0^2\,\delta\,\varepsilon_1}{c_0^2 - s_0^2}
     * + \frac{g_{V,\mathrm{SM}}^q}{2} \delta\,\varepsilon_1
     * @f]
     * for @f$q\neq b@f$, and
     * @f[
     * \delta g_V^q
     * = \Big(g_{V,\mathrm{SM}}^q - g_{A,\mathrm{SM}}^q \Big)
     * \bigg( \frac{\delta\,\varepsilon_3-c_0^2\,\delta\,\varepsilon_1}{c_0^2 - s_0^2}
     * - \delta\,\varepsilon_b \bigg)
     * +
     * \frac{g_{V,\mathrm{SM}}^f}{2}
     * \big(\delta\,\varepsilon_1 + 2\delta\,\varepsilon_b\big)
     * @f]
     * for @f$q=b@f$.
     * @param[in] q name of a quark (see QCD::quark)
     * @return @f$\delta g_V^q@f$
     */  
    virtual double deltaGV_f(const Particle p) const;

    /**
     * @brief @copybrief NPbase::deltaGAq()
     * @details
     * @f[
     * \delta g_A^q = \frac{I_3^q}{2}\delta\,\varepsilon_1
     * @f]
     * for @f$q\neq b@f$, and
     * @f[
     * \delta g_A^q 
     * = \frac{I_3^q}{2}\big( \delta\,\varepsilon_1 + 2\,\delta\,\varepsilon_b \big)
     * @f]
     * for @f$q=b@f$.
     * @param[in] q name of a quark (see QCD::quark)
     * @return @f$\delta g_A^q@f$
     */
    virtual double deltaGA_f(const Particle p) const;


    ////////////////////////////////////////////////////////////////////////
protected:

    double deltaEps_1;///< The new physics contribution to \f$\varepsilon_1\f$.
    double deltaEps_2;///< The new physics contribution to \f$\varepsilon_2\f$.
    double deltaEps_3;///< The new physics contribution to \f$\varepsilon_3\f$.
    double deltaEps_b;///< The new physics contribution to \f$\varepsilon_b\f$.

    /**
     * @brief @copybrief Model::setParameter()
     * @copydetails Model::setParameter()
     */
    virtual void setParameter(const std::string name, const double& value);

    
};

#endif	/* NPEPSILONS_PURENP_H */

