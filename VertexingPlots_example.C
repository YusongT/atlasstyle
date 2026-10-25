//The function plots distribution that is passed as the first atribute for the sample that is passed as a second atribute.
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
// #include "atlasstyle-00-04-02/AtlasUtils.h"
// #include "atlasstyle-00-04-02/AtlasStyle.h"
// #include "atlasstyle-00-04-02/AtlasLabels.h"
#include "atlasstyle-00-04-02/AtlasStyle.C"
#include "atlasstyle-00-04-02/AtlasLabels.C"
#include "atlasstyle-00-04-02/AtlasUtils.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <string>
#include <iomanip>
#include <TFile.h>
#include <TTree.h>
#include <TFolder.h>
#include <TH1F.h>
#include <TH2D.h>
#include "TEfficiency.h"
#include <TTreeFormula.h>
#include <TCollection.h>
#include <TList.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TMath.h>

// single mu 2.4-3.2 - 
// single mu 3.2-4.3 - 
// VBF - 
// single pi plus - 

using namespace std;

TString translate(TString process = "ttbarMu200"){
  if (process == "ttbarMu200"){return "2019-03-03-ESD_ttbar_mu200_withTimingImprovedPileupTruth";}
  else if (process == "VBF"){return "VBFH125_ZZ4nu_0_ALL.IDPVM.root";}
  else return 1;
}

TString translateName(TString process = "ttbarMu200"){
  if (process == "ttbarMu200old"){return "t#bar{t} < #mu > = 200, ITk Step 3.0";}
  else if (process == "VBFMu200old"){return "VBF H(inv) < #mu > = 200, Step 3.0";}
  else if (process == "ttbarMu200"){return "t#bar{t} < #mu > = 200, Step 3.1";}
  else if (process == "VBFMu200"){return "VBF H #rightarrow inv. < #mu > = 200, Step 3.1";}
  else if (process == "VBFMu200_Alex"){return "VBF H #rightarrow inv. < #mu > = 200, Step 3.1";}
  else return "";
}

void plotBasicsFor1Smaple(TString process = "ttbarMu200"){
  SetAtlasStyle();

    TString fileName = "ttbar_17_01_AlexTrackTime.root";

  TFile *f = new TFile(fileName);
  f->cd();
  // TLatex latex;
  // latex.SetTextSize(0.035);
  // latex.SetTextAlign(11); 
  TString sampleName = translateName(process);
  
  TH1F *h_reso_HS = new TH1F("h_reso_HS","Vertex time resolution",30,0,30);
  h_reso_HS = (TH1F*)f->Get("IDPerformanceMon/Vertices/Detailed/timingVtx_resolutionHS")->Clone("h_reso_HS");
  TH1F *h_reso_PU = new TH1F("h_reso_PU","Vertex time resolution",30,0,30);
  h_reso_PU = (TH1F*)f->Get("IDPerformanceMon/Vertices/Detailed/timingVtx_resolutionPU")->Clone("h_reso_PU");
  TCanvas *c_timeresoHSPU = new TCanvas("c_timeresoHSPU", "c_timeresoHSPU", 800, 600);
  c_timeresoHSPU->cd();
  // Upper plot will be in pad1
  //  h_reso_HS->SetStats(0);
  TLegend *legend_timeresoHSPU=new TLegend(0.70,0.80,0.90,0.90);
  h_reso_HS->SetFillStyle(6);
  h_reso_PU->SetFillStyle(6);  
  h_reso_HS->SetTitle("Vertex time resolution"); 
  h_reso_HS->SetLineColor(2);
  h_reso_HS->SetMarkerColor(2);
  h_reso_PU->SetLineColor(4);
  h_reso_PU->SetMarkerColor(4);
  gPad->SetLogy();
  h_reso_HS->DrawNormalized("E1");
  h_reso_PU->DrawNormalized("E1 same");
  legend_timeresoHSPU->SetFillColor(0);
  legend_timeresoHSPU->SetTextSize(0.04);
  legend_timeresoHSPU->SetFillColor(0);
  legend_timeresoHSPU->SetBorderSize(0);
  legend_timeresoHSPU->AddEntry(h_reso_HS,"HS");
  legend_timeresoHSPU->AddEntry(h_reso_PU,"PU");
  legend_timeresoHSPU->Draw();
  //  latex.DrawLatex(-2.75,0.15,sampleName);
  //  c_timeresoHSPU->Update();
  TString plotName_timeresoHSPU = process + "/" + process + "_timingVtx_resolution.eps";
  c_timeresoHSPU->cd();
  ATLASLabel(0.2,0.87,"Internal");
  myText(0.2,0.82, 1, "Simulation");
  myText(0.2,0.77, 1, sampleName);
  c_timeresoHSPU->Print(plotName_timeresoHSPU);


}



