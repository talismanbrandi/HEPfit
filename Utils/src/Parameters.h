/* 
 * Copyright (C) 2012-2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <string>
#include <map>
#include <vector>
#include <gslpp_matrix_double.h>
#include <gslpp_matrix_complex.h>

#ifndef PARAMETERS_H
#define PARAMETERS_H

/**
 * @addtogroup Utils 
 * @brief A module for utilities.
 * @{
 */

/**
 * @class Parameters
 * @brief Parameters Class, used to store the parameters for a given model.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 */
class Parameters {
  public:
    static const int NumberOfTypes = 7;
    static const std::string TypeList[NumberOfTypes]; 
    enum MapType {INT, DOUBLE, COMPLEX, STRING, DOUBLE_MATRIX, COMPLEX_MATRIX, DOUBLE_VECTOR};

    /**
     * @brief Void constructor.
     */
    Parameters() 
    {};

    /**
     * Parameters copy constructor.
     * @param P parameters to be copied
     */
    Parameters(Parameters& P);
    virtual ~Parameters() 
    {};

    /**
     * get the Integers map.
     * @return the Integers map
     */
    std::map<std::string, int> getInts() const;

    /**
     * get the Doubles map.
     * @return the Doubles map
     */
    std::map<std::string, double> getDoubles() const;

    /**
     * get the Complexes map.
     * @return the Complexes map
     */
    std::map<std::string, gslpp::complex> getComplexes() const;

    /**
     * get the Strings map.
     * @return the Strings map
     */
    std::map<std::string, std::string> getStrings() const;

    /**
     * get the Double Matrices map.
     * @return the Double Matrices map
     */
    std::map<std::string, gslpp::matrix<double> > getDoubleMatrices() const;

    /**
     * get the Complex Matrices map.
     * @return the Complex Matrices map
     */
    std::map<std::string, gslpp::matrix<gslpp::complex> > getComplexMatrices() const;

    /**
     * get the Double Vectors map.
     * @return the Double Vectors map
     */
    std::map<std::string, std::vector<double> > getDoubleVectors() const;

    /**
     * Set the value of an integer.
     * @param s the key
     * @param i the value
     */
    void Set(std::string s, int i);

    /**
     * Set the value of a double.
     * @param s the key
     * @param d the value
     */
    void Set(std::string s, double d);

    /**
     * Set the value of a complex.
     * @param s the key
     * @param z the value
     */
    void Set(std::string s, gslpp::complex z);

    /**
     * Set the value of a string.
     * @param s the key
     * @param t the value
     */
    void Set(std::string s, std::string t);

    /**
     * Set the value of a Double Matrix.
     * @param s the key
     * @param md the value
     */
    void Set(std::string s, gslpp::matrix<double> md);

    /**
     * Set the value of a Complex Matrix.
     * @param s the key
     * @param mc the value
     */
    void Set(std::string s, gslpp::matrix<gslpp::complex> mc);

    /**
     * Set the value of a Double Vector.
     * @param s the key
     * @param v the value
     */
    void Set(std::string s, std::vector<double> v);

    /**
     * Get the value of an integer.
     * @param s the key
     * @param i the value
     */
    void Get(std::string s, int& i) const;
     /**
     * Get the value of a double.
     * @param s the key
     * @param d the value
     */
    void Get(std::string s, double& d) const;

    /**
     * Get the value of a complex.
     * @param s the key
     * @param z the value
     */
    void Get(std::string s, gslpp::complex& z) const;

    /**
     * Get the value of a string.
     * @param s the key
     * @param t the value
     */
    void Get(std::string s, std::string& t) const;

    /**
     * Get the value of a Double Matrix.
     * @param s the key
     * @param md the value
     */
    void Get(std::string s, gslpp::matrix<double>& md) const;

    /**
     * Get the value of a Complex Matrix.
     * @param s the key
     * @param mc the value
     */
    void Get(std::string s, gslpp::matrix<gslpp::complex>& mc) const;

    /**
     * Get the value of a Double Vector.
     * @param s the key
     * @param v the value
     */
    void Get(std::string s, std::vector<double>& v) const;

    int Find(std::string s) const;

  private:
    std::map<std::string, int> Ints;
    std::map<std::string, double> Doubles;
    std::map<std::string, gslpp::complex> Complexes;
    std::map<std::string, std::string> Strings;
    std::map<std::string, gslpp::matrix<double> > DoubleMatrices;
    std::map<std::string, gslpp::matrix<gslpp::complex> > ComplexMatrices;
    std::map<std::string, std::vector<double> > DoubleVectors;

    void InOtherMaps(std::string s, MapType m) const;
    void InMap(std::string s, MapType m) const;
};

/** 
 * @}
 */

#endif	/* PARAMETERS_H */
