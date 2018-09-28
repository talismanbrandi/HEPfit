/* 
 * Copyright (C) 2012 HEPfit Collaboration
 *
 *
 * For the licensing terms see doc/COPYING.
 */

#include "WilsonCoefficientNew.h"
#include <sstream>
#include <stdexcept>

WilsonCoefficientNew::WilsonCoefficientNew(unsigned int dim, schemes scheme, orders_qcd order_qcd_i, orders_qed order_qed_i)
: WilsonTemplateNew<gslpp::vector<gslpp::complex> >(dim, scheme, order_qcd_i, order_qed_i) {
};

Expanded<gslpp::complex> WilsonCoefficientNew::getCoeffElement(uint i) const {
    Expanded<gslpp::complex> ret;

    if (i >= size) {
        std::stringstream out;
        out << i;
        throw std::runtime_error("WilsonTemplate::getCoeff(): requested element " + out.str() +
                " not present in the object");
    }
    std::vector<std::vector<gslpp::complex> > obj(wilson.getN1());
    for (uint j = 0; j < wilson.getN1(); j++)
        for (uint k = 0; k < wilson.getN2(); k++)
            obj[j].push_back(wilson.getOrd(j, k)(i));
    return (Expanded<gslpp::complex>(obj));
};

void WilsonCoefficientNew::setCoeff(unsigned int i, gslpp::complex z, orders_qcd order_qcd_i, orders_qed order_qed_i) {
    if (i >= size) {
        std::stringstream out;
        out << i;
        throw std::runtime_error("WilsonTemplate::setCoeff(): coefficient index "
                + out.str() + " out of range");
    }
    if (order_qcd_i > order_qcd || order_qed_i > order_qed) {
        std::stringstream out;
        out << order_qcd_i << " and " << order_qed_i;
        throw std::runtime_error("WilsonTemplate::setCoeff(): order " + out.str() +
                " not implemented ");
    }
    gslpp::vector<gslpp::complex> tmp = wilson.getOrd(order_qcd_i, order_qed_i);
    tmp.assign(i, z);
    wilson.setOrd(order_qcd_i, order_qed_i, tmp);
}

void WilsonCoefficientNew::setCoeff(const gslpp::vector<gslpp::complex>& v, orders_qcd order_qcd_i, orders_qed order_qed_i) {
    setWilson(v, order_qcd_i, order_qed_i);
}

void WilsonCoefficientNew::resetCoeff() {
    resetWilson();
}

gslpp::vector<gslpp::complex> WilsonCoefficientNew::getCoeff(orders_qcd order_qcd_i, orders_qed order_qed_i) const {
    return getWilson(order_qcd_i, order_qed_i);
}

Expanded<gslpp::vector<gslpp::complex> > WilsonCoefficientNew::getCoeff() const {
    return getWilson();
}

void WilsonCoefficientNew::setCoeff(const Expanded<gslpp::vector<gslpp::complex> > wc) {
    wilson = wc;
}
