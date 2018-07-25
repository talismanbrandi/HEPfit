/* 
 * Copyright (C) 2012 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef WILSONTEMPLATE_H
#define WILSONTEMPLATE_H

#include "OrderScheme.h"
#include "Expanded.h"
#include <sstream>
#include <stdexcept>

/**
 * @class WilsonTemplate
 * @ingroup StandardModel
 * @brief A template class for the Wilson coefficients. 
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details 
 */

// T is the type (double or complex) of the gslpp::vector of Wilson coefficients

template <class T> class WilsonTemplate {
public:

    WilsonTemplate(unsigned int size_i, schemes scheme_i, orders_qcd order_qcd_i,
            orders_qed order_qed_i = QED0) {
        T el(size_i, 0.);

        size = size_i;
        scheme = scheme_i;
        order_qcd = order_qcd_i;
        order_qed = order_qed_i;
        mu = -1.;

        std::vector<std::vector<T> > obj;
        std::vector<T> tmp;
        if (order_qcd < FULLNLO && order_qed < FULLQED1) {
            for (int j = 0; j <= order_qed; j++)
                tmp.push_back(el);
            for (int i = 0; i <= order_qcd; i++)
                obj.push_back(tmp);
        } else
            throw std::runtime_error("WilsonTemplate::WilsonTemplate(): order_qcd and/or order_qed out of range");

        wilson = Expanded<T>(obj);
    };

    orders_qcd getOrder_QCD() const {
        return order_qcd;
    }

    orders_qed getOrder_QED() const {
        return order_qed;
    }

    double getMu() const {
        return mu;
    }

    void resetWilson() {
        T zz(size, 0.);

        for (int i = LO; i <= order_qcd; i++)
            for (int j = QED0; j <= order_qed; j++)
                wilson.setOrd(i, j, zz);
    }

    void setMu(double mu) {
        this->mu = mu;
        resetWilson();
    }

    schemes getScheme() const {
        return scheme;
    }

    void setScheme(schemes scheme) {
        this->scheme = scheme;
    }

    unsigned int getSize() const {
        return size;
    }

    T& getWilson(orders_qcd order_qcd_i, orders_qed order_qed_i = QED0) const {
        if (order_qcd_i > order_qcd || order_qed_i > order_qed) {
            std::stringstream out;
            out << order_qcd_i << " and " << order_qed_i;
            throw std::runtime_error("WilsonTemplate::getCoeff(): requested order " + out.str() +
                    " not present in the object");
        }
        return wilson.getOrd(order_qcd_i, order_qed_i);
    };

    Expanded<T> getWilson() const {
        return wilson;
    }

    void setWilson(const T& v, orders_qcd order_qcd_i, orders_qed order_qed_i = QED0) {
        if (order_qcd_i > order_qcd || order_qed_i > order_qed) {
            std::stringstream out;
            out << order_qcd_i << " and " << order_qed_i;
            throw std::runtime_error("WilsonTemplate::setElem(): order " + out.str() +
                    " not implemented ");
        }
        if (v.size() != size)
            throw std::runtime_error("WilsonTemplate::setElem(): wrong size");

        wilson.setOrd(order_qcd_i, order_qed_i, v);
    };

protected:
    Expanded<T> wilson;
    unsigned int size;
    double mu;
    schemes scheme;
    orders_qcd order_qcd;
    orders_qed order_qed;

};

#endif /* WILSONTEMPLATE_H */

