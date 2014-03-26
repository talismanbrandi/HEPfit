/* 
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "HiggsObservable.h"
#include <BAT/BCMath.h>
#include <TNamed.h>
#include <TFile.h>
#include <TROOT.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <string>
#include <sstream>

HiggsObservable::~HiggsObservable()
{
}

void HiggsObservable::setParametricLikelihood(std::string filename, std::vector<ThObservable*> thObsV)
{
    this->filename = filename;
    this->thObsV = thObsV;
    std::ifstream ifile(filename.c_str());
    if (!ifile.is_open())
        throw std::runtime_error("\nERROR: " + filename + " does not exist. Make sure to specify a valid Higgs parameters configuration file.\n");
    std::string line;
    bool IsEOF = false;
    int i = 0, nrows = 0;
    do {
        IsEOF = getline(ifile, line).eof();
        if (*line.rbegin() == '\r') line.erase(line.length() - 1); // for CR+LF
        if (line.empty() || line.at(0) == '#')
            continue;
        boost::char_separator<char> sep(" ");
        boost::tokenizer<boost::char_separator<char> > tok(line, sep);
        boost::tokenizer<boost::char_separator<char> >::iterator beg = tok.begin();
        if (beg->compare("size") == 0) {
            nrows = atoi((*(++beg)).c_str());
            channels = TMatrixD(nrows, thObsV.size() + 2);
            continue;
        }
        // Read the necessary information from the config file. Each row contains:
        // ggH fraction
        // VBF fraction
        // VH fraction (ttH is computed as 1-ggH-VBF-VH)
        // average value of mu
        // left-side error
        // right-side error
        for(int j = 0; j < thObsV.size() +  2; j++)
            channels(i, j) = atof((*(++beg)).c_str());

        i++;

    } while (!IsEOF);
    if (i != nrows)
    {
        std::stringstream ss;
        ss << "\nERROR: " << filename << " should contain " << nrows << " measurements, but I have read " << i << " ones instead.\n";
        throw std::runtime_error(ss.str());
    }
    
}

double HiggsObservable::computeWeight()
{
    double logprob = 0;

    for(int i = 0; i < channels.GetNrows(); i++){
        double mu = 0, sum = 0.;
        for (int j = 0; j < thObsV.size() - 1; j++){
            mu += channels(i,j) * thObsV.at(j)->computeThValue();
            sum += channels(i,j);
        }
        mu += (1. - sum) * thObsV.at(thObsV.size() - 1)->computeThValue();
        logprob += LogSplitGaussian(mu*tho->computeThValue(),channels(i,3),channels(i,4),channels(i,5));
    }
    
    return (logprob);
}


