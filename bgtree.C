#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include<iostream>
double avg(vector<double> v){
  double sum=0;
  for(int i=0;i<30;i++){
    sum=sum+v.at(i);
  }
  double mean=sum/30;
  return mean;
}
void bgtree(){
  TFile hfile("Background_Tree2.root","RECREATE","Background file tree");
  TTree *tree = new TTree("BT","Background Tree");
  struct hist { TH2F *plots[100]; };
  hist h;
  vector<double> myvariables(900);
  int count=0;
  TF1 *f1 = new TF1("f1","gaus(0)",-10,10);
  f1->SetParameters(1,0,3);
  TF1 *f2 = new TF1("f2","TMath::Landau(x,[0],[1])",-10,10);
  f2->SetParameters(0,3);
  for(int i=0;i<30;i++){
    for(int j=0;j<30;j++){
      string str="Bin";
      string str1=to_string(i);
      string str2=to_string(j);
      str.append(str1);
      str.append(str2);
      const char* ch=str.c_str();
      tree->Branch(ch,&(myvariables.at(count)),"myvariables.at(count)/D");
      count++;
    }
  }
  for(int i=0;i<100;i++){
    string str=to_string(i);
    const char* ch=str.c_str();
    h.plots[i]= new TH2F(ch,"",30,-15,15,30,-15,15);
    TCanvas *c1=new TCanvas("c1","c1",500,800);
    vector<double> x(30);
    vector<double> y(30);
    gStyle->SetOptStat(0);
    gStyle->SetPadTopMargin(0.);
    gStyle->SetPadRightMargin(0.);
    gStyle->SetPadBottomMargin(0.);
    gStyle->SetPadLeftMargin(0.);
    
    for(int j=0;j<30;j++){
      x.at(j)=f1->GetRandom();
      y.at(j)=f2->GetRandom();
    }
    double meanx=avg(x);
    double meany=avg(y);
    for(int j=0;j<30;j++){
      h.plots[i]->Fill((x.at(j)-meanx),(y.at(j)-meany));
    }
    string str2="background";
     string str3=str2.append(str);
     string str4=".jpg";
     string str5=str3.append(str4);
     const char* ch1=str5.c_str();
     h.plots[i]->Scale(1/h.plots[i]->Integral());
     h.plots[i]->GetXaxis()->SetLabelSize(0);
     h.plots[i]->GetXaxis()->SetTickLength(0);
     h.plots[i]->GetYaxis()->SetTickLength(0);
     h.plots[i]->GetYaxis()->SetLabelSize(0);
     h.plots[i]->GetXaxis()->SetAxisColor(0);
     h.plots[i]->GetYaxis()->SetAxisColor(0);
     h.plots[i]->Draw();
     
     c1->SaveAs(ch1);
     c1->Close();
     delete c1;
    int no=0;
    for(int j=0;j<30;j++){
      for(int k=0;k<30;k++){
	double intensity=h.plots[i]->GetBinContent(j,k);
	//	if(intensity==0) intensity=6;
	myvariables.at(no)=intensity;
	no++;
      }
    }
    tree->Fill();
  }
    hfile.Write();
    hfile.Close();
}
