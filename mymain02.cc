// program for merging

#include "Pythia8/Pythia.h"        
      
using namespace Pythia8;   
  
int main() {              


	Pythia pythia;

	int nAbort = 10;
	int iAbort = 0;

	double pT0 = 0;
	double pT1 = 0;
	double pT2 = 0;	
     	double weight  = pythia.info.mergingWeight();
	
	pythia.settings.readString("Merging:TMS = 20");
	pythia.settings.readString("Merging:nJetMax = 3");
	pythia.settings.readString("Merging:Process = pp>e+ve");
	pythia.readString("Beams:frameType = 4");
	int nEvent = pythia.mode("Main:numberOfEvents");
		

		// Initialise a histogram
		Hist pTW2("pT of W-jets_2", 100, 0, 100);
		pythia.init();
		pythia.readString("Beams:LHEF = wjets_2.lhe");
		
		for (int iEvent = 0; iEvent < nEvent; ++iEvent){
			 if (!pythia.next()) {
	     			 if (pythia.info.atEndOfFile()) break;
				 else continue;
	   		 }

			for (int i = 1; i < pythia.event.size(); ++i)
				if( pythia.event[i].idAbs() == 24 ){
				pT2 = pythia.event[i].pT();
					break;
				} 

			pTW2.fill(pT2 ,weight);
		
		}

				
		// Initialise a histogram
		Hist pTW0("pT of W-jets_0", 100, 0, 100);
		pythia.init();			
		pythia.readString("Beams:LHEF = wjets_0.lhe");
		
		for (int iEvent = 0; iEvent < nEvent; ++iEvent){
			 if (!pythia.next()) {
	     			 if (pythia.info.atEndOfFile()) break;
				      if (++iAbort < nAbort) continue;
				      	break;
	   		 }

			for (int i = 1; i < pythia.event.size(); ++i)
				if( pythia.event[i].idAbs() == 24 ){
				pT0 = pythia.event[i].pT();
					break;
				} 

			pTW0.fill(pT0 ,weight);
		
		}

		// Initialise a histogram
		Hist pTW1("pT of W-jets_1", 100, 0, 100);
		pythia.init();
		pythia.readString("Beams:LHEF = wjets_1.lhe");
		

		for (int iEvent = 0; iEvent < nEvent; ++iEvent){
			 if (!pythia.next()) {
	     			 if (pythia.info.atEndOfFile()) break;
				      if (++iAbort < nAbort) continue;
				      	break;
	   		 }

			for (int i = 1; i < pythia.event.size(); ++i)
				if( pythia.event[i].idAbs() == 24 ){
				pT1 = pythia.event[i].pT();
					break;
				} 

			pTW1.fill(pT1 ,weight);
		
		}


	cout<<pTW0;
	cout<<pTW1;
	cout<<pTW2;

	Hist pTWSum("pT of W-boson, merged prediction", 100, 0., 300.);
	pTWSum = pTW0 + pTW1 + pTW2;
	cout << pTWSum;
	
	HistPlot hpl("Wjet_combined"); 
	hpl.frame( "Wjet_pTdist_combined", "Wjet pT distributions", "pT (GeV)", "sigma");
	hpl.add(pTWSum);
	hpl.plot();


return 0;
}
