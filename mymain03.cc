
//program for plotting and pdf

#include "Pythia8/Pythia.h"        
using namespace Pythia8;   
  
int main() {              


	Pythia pythia;
	pythia.readString("Beams:frameType = 4");
	pythia.readString("Beams:LHEF = wjets_0.lhe");
	pythia.init();


	// Initialise a histogram
	Hist pTW("pT of W-jets_", 100, 0, 100);
	
	int nAbort = 10;
	int iAbort = 0;
	double pTa = 0;
	int nEvent = pythia.mode("Main:numberOfEvents");

	for (int iEvent = 0; iEvent < nEvent; ++iEvent){
		 if (!pythia.next()) {
     			 if (pythia.info.atEndOfFile()) break;
			      if (++iAbort < nAbort) continue;
			      	break;
   		 }

		for (int i = 1; i < pythia.event.size(); ++i)
			if( pythia.event[i].idAbs() == 24 ){
			pTa = pythia.event[i].pT();
				break;
			} 

		pTW.fill(pTa);
	}

	//Fill the histogram
	
	cout <<  pythia.event.size();
	cout << pTW;



HistPlot hpl("Wjet_1_pT"); 
hpl.frame( "pTdist", "Wjet pT distributions", "pT (GeV)", "sigma");
hpl.add(pTW);
hpl.plot();



	return 0;
}




