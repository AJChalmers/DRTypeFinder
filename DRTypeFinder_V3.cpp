// Program to read from file into arrays, and to output values for D/R type analysis
// V1: Copy of program ReadingFromFileIntoArrays_V4, fitted to do stuff with the arrays, output results
	// Note: Temp and temp zone findings not working right? Keeps getting either 0 or last num.
// V2: Goal is to fix problems with V1 and make working program. -Still not fixed, arrays are being filled with last number in file.
// V3: Reworking reading from files to reading from one file-> this works
	// Note: It seems array is being completely filled from 0 to nArray with each entry from file each iteration.

# include <iostream>
# include <fstream>
# include <math.h>
# include <iomanip>
# include <cmath>
# include <stdlib.h>
# include <cstdlib>

using namespace std;

int main(){
	
	///// Controls /////
	
	const int NumOfZones = 300;
	const int nArray = NumOfZones + 1;
	int NumOfFiles = 1;
	
	//cout<<"Enter the number of files to read (Usually 5): "<<endl;
	//cin>>NumOfFiles;
	
	ifstream inFile;
	double Mdis;
	double rho;
	double pressure;
	double vel_km_per_s;
	double Temp;
	
	double Mdis[nArray];
	double rho[nArray];
	double pressure[nArray];
	double vel_km_per_s[nArray];
	double Temp[nArray];
	
	////////// Reading Files into Arrays ////////////
	
	cout<<"This program takes a file with columns Mdis, rho, pressure, vel_km_per_s, temperature that is placed in its directory."<<endl;
	
	for(int i = 0; i < NumOfFiles; i++){
		
		///// Finding File //////
		int TryAgain = 1;
		while(TryAgain == 1){
			char InputFileName[30];
			cout<<"Enter Input Files Name (Max Char=30): "<<endl;
			cin>>InputFileName;
			
			inFile.open(InputFileName,ios::in);
			
			// Warning if file cant be opened
			if(!inFile.is_open()){ 
				cout << "Error opening file. \n";
				cout << "Giving Retry... \n";
			}
			if(inFile.is_open()){
				cout<<"File was opened successfully"<<endl;
				TryAgain = 0;
			}
		}
			
		if(inFile.is_open()){
		
			// Putting cursor at start of file
			inFile.clear();
				
				cout<<"Mdis"<<setw(15)<<"rho"<<setw(15)<<"pressure"<<setw(15)<<"vel_km_per_s"<<setw(15)<<"Temp"<<endl;
				for (int a = 0; a < NumOfZones; a++){
						inFile >> Mdis[a] >> rho[a] >> pressure[a] >> vel_km_per_s[a] >> Temp[a];
						cout<<Mdis[a]<<setw(15)<<rho[a]<<setw(15)<<pressure[a]<<setw(15)<<vel_km_per_s[a]<<setw(15)<<Temp[a]<<endl;
						
						//test loop 
						cout<<"Lookup table test inside loop..."<<endl;
						for(int b = 0; b < nArray; b++){
							cout<<Mdis[b]<<setw(10)<<rho[b]<<setw(10)<<pressure[b]<<setw(10)<<vel_km_per_s[b]<<setw(10)<<Temp[b]<<endl;
						}
						
				}
				
			// Close the file.
			//inFile.close();
		}
		
		
		if(!inFile.is_open()){
			cout<<"File closed successfully"<<endl;
		}
		
		//test loop 
		cout<<"Lookup table test..."<<endl;
		for(int a = 0; a < nArray; a++){
			cout<<Mdis[a]<<setw(10)<<rho[a]<<setw(10)<<pressure[a]<<setw(10)<<vel_km_per_s[a]<<setw(10)<<Temp[a]<<endl;
		}
		
		Space(2);
	}
	
	///////////////////////////////////////////////////////////////////////
	
	//// Making Output arrays ////
	
	double To;
	double Ti;

	// Note: Program picks first number before specified values for temp
	cout<<"Enter the temp for the neutral side:"<<endl;
	cin>>To;
	
	// Temp Finder Loop 1 - Neutral side
	for(int a = 0; a < nArray; a++){
	
		if(Temp[a] < To){
			double To_found = Temp[a];
			double To_zone = a + 1;
			cout<<"To_found: "<<To_found<<endl;
			cout<<"To_zone: "<<To_zone<<endl;
		}
	}
	cout<<"Final To_found: "<<To_found<<endl;
	cout<<"Final To_zone: "<<To_zone<<endl;
	Space(1);
	
	cout<<"Enter the temp for the ionized side:"<<endl;
	cin>>Ti;
	
	// Temp Finder Loop 2 - Ionized side
	for(int a = 0; a < nArray; a++){
		
		if(Temp[a] < Ti){
			double Ti_found = Temp[a];
			double Ti_zone = a + 1;
			cout<<"Ti_found: "<<Ti_found<<endl;
			cout<<"Ti_zone: "<<Ti_zone<<endl;
		}
	}
	cout<<"Final Ti_found: "<<Ti_found<<endl;
	cout<<"Final Ti_zone: "<<Ti_zone<<endl;
	Space(1);
	
		
	Space(1);
	
	int Response1 = 0;
	while(Response1 != 1){
		cout<<"Enter the desired output file name (Max Char=30): "<<endl;
		char OutputFileName[30];
		cin>>OutputFileName;
		Space(1);
		
		cout<<"Is this correct? Enter 1 for yes and 0 for no."<<endl;
		cout<<"File name: "<<OutputFileName<<endl;
		cin>>Response1;
		Space(1);
	}
	
	ofstream outputfile1(OutputFileName);
	
	if(outputfile1){
		cout<<"File created successfully"<<endl;
		Space(2);
	}
	
	
	const int nArray2 = nArray - Ti_zone;
	
	double Co[nArray2];
	double Ci[nArray2];
	double Vo[nArray2];
	double Vd[nArray2];
	double Vr[nArray2];
	
	////// Calculations ///////
	
	double Co = sqrt(pressure[To_zone]/rho[To_zone]);
	double Vo = vel_km_per_s[Ti_Zone];
	
	outputfile1<<"Co"<<endl;
	outputfile1<<Co<<endl;
	outputfile1<<"Vo"<<endl;
	outputfile1<<Vo<<endl;
	
	// Calculation loop, starting at Ti_zone that was found
	outputfile1<<"Co"<<setw(10)<<"Vo"<<setw(10)<<"Ci"<<setw(10)<<"Vd"<<setw(10)<<"Vr"<<endl;
	for(int c = Ti_zone; c < NumOfZones; c++){
		Co[c] = Co;
		Vo[c] = Vo;
		Ci[c] = sqrt(pressure[c]/rho[c]);
		Vd[c] = Ci[c] - sqrt((Ci[c]*Ci[c])-(Co*Co)); 
		Vr[c] = Ci[c] + sqrt((Ci[c]*Ci[c])-(Co*Co)); 
		
		outputfile1<<Co[c]<<setw(10)<<Vo[c]<<setw(10)<<Ci[c]<<setw(10)<<Vd[c]<<setw(10)<<Vr[c]<<endl;
		
	}
	
	return 0;
}



void Space(int Size){
	int i = 0;
	while (i < Size){
		cout<<" "<<endl;
		i = i + 1;
	}
}



