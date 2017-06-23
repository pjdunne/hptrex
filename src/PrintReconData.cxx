#include "TFile.h"
#include "TTree.h"
#include "TTRExPattern.hxx"

int main(int argc, char * argv[]) {

  TFile * inFile = new TFile(argv[1]);

  TTree * ReconTree = (TTree*)inFile->Get("TPCRecon");
  TTree * TruthTree = (TTree*)inFile->Get("Truth");  
  
  trex::WritableEvent * event=0;
  ReconTree->SetBranchAddress("event", &event);

  std::vector<trex::TTrueTrack> * tracks=0;
  TruthTree->SetBranchAddress("tracks", &tracks);
  
  for(int i=0;i<ReconTree->GetEntries();++i){
    ReconTree->GetEntry(i);
    TruthTree->GetEntry(i);
 
    std::cout<<"Size of true tracks vector: "<<tracks->size()<<std::endl;
    for(auto iTrk=tracks->begin();iTrk!=tracks->end();++iTrk){
      std::cout<<"**ID: "<<iTrk->GetTrackID()<<", PDG: "<<iTrk->GetTrackPDG()<<", Parent ID: "<<iTrk->GetTrackParentID()<<std::endl;
    }

    std::vector<trex::WritablePattern>& pats = event->patterns;
    int patSize = pats.size(); 
    std::cout << "Size of pattern vector: " << patSize << std::endl;
    
    for(int i=0; i<patSize; ++i){
      std::cout<<"**"<<pats[i].Paths.size()<<std::endl;
      for(auto iPath=pats[i].Paths.begin();iPath!=pats[i].Paths.end();++iPath){
	std::cout<<"****"<<(*iPath)[0].GetTrueTrackID()<<std::endl;
      }
    }
  }   
}
