Models   {#PageModels}
==========================================================

Here is a list of all available models with links to the summary
tables of model parameters and flags. The parameters and flags 
are inherited from a parent model class to a child model class: 

MODEL_GRAPH_INHERITE_SVG

where Model is a template class of models, and NPbase and NPEffective
are auxiliary classes. 
A complete list of observables are available at the documentation of
@ref ListOfObservables "ThFactory", where not all the observables can
be used in each model. Below we also list the available observables for
each model. 

## QCD:

  - %Model parameters: [@ref QCDParameters "Summary table"]
  - %Model flags: None
  - %Observables: None

## StandardModel:

  - %Model parameters: [@ref StandardModelParameters "Summary table"]
  - %Model flags: [@ref StandardModelFlags "Summary table"]
  - %Observables: Mw, GammaW, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom, 
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon1",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon2",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon3",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilonb"

## NPEpsilons:

  - %Model parameters: [@ref NPEpsilonsParameters "Summary table"]
  - %Model flags: [@ref NPEpsilonsFlags "Summary table"]
  - %Observables: Mw, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom,
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon1",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon2",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon3",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilonb"

## NPEpsilons_pureNP:

  - %Model parameters: [@ref NPEpsilons_pureNPParameters "Summary table"]
  - %Model flags: None
  - %Observables: Mw, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom,
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon1",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon2",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon3",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilonb"

## NPSTU:

  - %Model parameters: [@ref NPSTUParameters "Summary table"]
  - %Model flags: None
  - %Observables: Mw, GammaW, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom,
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon1",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon2",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilon3",
	@ref NewPhysicsParams::NewPhysicsParams() "epsilonb"

## NPHiggs:

  - %Model parameters: [@ref NPHiggsParameters "Summary table"]
  - %Model flags: None
  - %Observables: Mw, GammaW, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom,
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl"

## NPZbbbar:

  - %Model parameters: [@ref NPZbbbarParameters "Summary table"]
  - %Model flags: [@ref NPZbbbarFlags "Summary table"]
  - %Observables: Mw, GammaW, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom,
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl",
    @ref NewPhysicsParams::NewPhysicsParams() "deltaGVb",
    @ref NewPhysicsParams::NewPhysicsParams() "deltaGAb",
    @ref NewPhysicsParams::NewPhysicsParams() "deltaGRb",
    @ref NewPhysicsParams::NewPhysicsParams() "deltaGLb",
    @ref NewPhysicsParams::NewPhysicsParams() "deltaRhoZb",
    @ref NewPhysicsParams::NewPhysicsParams() "deltaKappaZb"

## NPZbbbarLR (a variant of NPZbbbar): 

  - %Model parameters: [@ref NPZbbbarParameters "Summary table"],
    where deltaGLb and deltaGRb must be used, instead of deltaGVb and
    deltaGAb in %NPZbbbar above.
  - %Model flags: Same as %NPZbbbar above. 
  - %Observables: Same as %NPZbbbar above. 

## NPEffective1:

  - %Model parameters: [@ref NPEffective1Parameters "Summary table"]
  - %Model flags: None
  - %Observables: Mw, GammaW, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom,
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl",
    @ref NewPhysicsParams::NewPhysicsParams() "cHQ1pPLUScHQ2p_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "cHQ2pMINUScHQ2_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "cHQ3pPLUScHQ3_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "c_Ae_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "c_GammaZ_uds_NP"

## NPEffective2:

  - %Model parameters: [@ref NPEffective2Parameters "Summary table"]
  - %Model flags: None
  - %Observables: Mw, GammaW, GammaZ, sigmaHadron, sin2thetaEff,
    PtauPol, Alepton, Acharm, Abottom, AFBlepton, AFBcharm, AFBbottom,
    Rlepton, Rcharm, Rbottom,
    @ref StandardModelParams::StandardModelParams() "Mz",
    @ref StandardModelParams::StandardModelParams() "mHl",
    @ref NewPhysicsParams::NewPhysicsParams() "cHQ1pPLUScHQ2p_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "cHQ2pMINUScHQ2_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "cHQ3pPLUScHQ3_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "c_Ae_NP",
    @ref NewPhysicsParams::NewPhysicsParams() "c_GammaZ_uds_NP"

