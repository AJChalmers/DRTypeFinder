// Program to read from file into arrays, and to output values for D/R type analysis
// V1: Copy of program ReadingFromFileIntoArrays_V4, fitted to do stuff with the arrays, output results
	// Note: Temp and temp zone findings not working right? Keeps getting either 0 or last num.
// V2: Goal is to fix problems with V1 and make working program. -Still not fixed, arrays are being filled with last number in file.
// V3: Reworking reading from files to reading from one file-> this works
	// Note: It seems array is being completely filled from 0 to nArray with each entry from file each iteration.
// V4: Fixed the arrays! Seems array needed at least one index filled before being filled.
// V5: Program is now working.
	// Note: Truncated files will result in truncated results!! 
	// Note: sqrt function giving different numbers here then in excel? -No, error in Co and Vo indices.
// V6: Optimized version of V5, allowing multiple files do be done at once with the same relative zones.
	// Note: Sometimes program will fail to operate if the first file is not found. Restart program.

# include <iostream>
# include <fstream>
# include <math.h>
# include <iomanip>
# include <cmath>
# include <stdlib.h>
# include <cstdlib>

using namespace std;

int main(){
	
	cout<<"This program takes files with columns | Mdis | rho | pressure | vel_km_per_s | temperature | that are placed in its directory."<<endl;

	//////// Controls ////////
	
	const int NumOfZones = 300;
	const int nArray = NumOfZones + 1;
	int NumOfFiles = 1;
	
	cout<<"Enter the number of files to read: "<<endl;
	cin>>NumOfFiles;
	
	// Note: Program picks first number before specified values for temp
	double To;
	cout<<"Enter the temp for the neutral side:"<<endl;
	cin>>To;
	
	double Ti;
	cout<<"Enter the temp for the ionized side:"<<endl;
	cin>>Ti;
	
	///////////////////////////////
	
	ifstream inFile;
	double Mdis[nArray];
	double rho[nArray];
	double pressure[nArray];
	double vel_km_per_s[nArray];
	double Temp[nArray];
	
	for(int i = 0; i < NumOfFiles; i++){
		
		Space(2);
		
		////////// Reading Files into Arrays ////////////
			
			///// Finding File //////
			int TryAgain = 1;
			while(TryAgain == 1){
				char InputFileName[30];
				cout<<"Enter Input File "<<(i+1)<<"'s Name (Max Char=30): "<<endl;
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
				if(inFile.good()){
					cout<<"File is ready for reading"<<endl;
				}
			}
				
			//reading file
			if(inFile.is_open()){
			
				// Putting cursor at start of file
				inFile.clear();
				
				
				inFile >> Mdis[0] >> rho[0] >> pressure[0] >> vel_km_per_s[0] >> Temp[0];
				cout<<"zone"<<setw(10)<<"Mdis"<<setw(15)<<"rho"<<setw(15)<<"pressure"<<setw(15)<<"vel_km_per_s"<<setw(15)<<"Temp"<<endl;
				for (int a = 1; a <= NumOfZones; a++){
					
					inFile >> Mdis[a] >> rho[a] >> pressure[a] >> vel_km_per_s[a] >> Temp[a];
					cout<<(a+1)<<setw(10)<<Mdis[a]<<setw(15)<<rho[a]<<setw(15)<<pressure[a]<<setw(15)<<vel_km_per_s[a]<<setw(15)<<Temp[a]<<endl;
						
				}
					
				// Close the file.
				inFile.close();
			}
			
			
			if(!inFile.is_open()){
				cout<<"File closed successfully"<<endl;
			}
			
			//test loop 
			// cout<<"Lookup table test..."<<endl;
			// for(int a = 0; a < NumOfZones; a++){
				// cout<<(a+1)<<setw(10)<<Mdis[a]<<setw(15)<<rho[a]<<setw(15)<<pressure[a]<<setw(15)<<vel_km_per_s[a]<<setw(15)<<Temp[a]<<endl;
			// }
			
			Space(2);
		
		///////////////////////////////////////////////////////////////////////
		
		//// Making Output arrays ////
		
		// Temp Finder Loop 1 - Neutral side
		for(int a = 0; a < nArray && Temp[a] < To; a++){
		
			double To_found = Temp[a];
			int To_zone = a + 1;
			//cout<<"To_found: "<<To_found<<endl;
			//cout<<"To_zone: "<<To_zone<<endl;
			
		}
		cout<<"Final To_found: "<<To_found<<endl;
		cout<<"Final To_zone: "<<To_zone<<endl;
		Space(1);
		
		// Temp Finder Loop 2 - Ionized side
		for(int a = 0; a < nArray && Temp[a] < Ti; a++){
			
			double Ti_found = Temp[a];
			int Ti_zone = a + 1;
			//cout<<"Ti_found: "<<Ti_found<<endl;
			//cout<<"Ti_zone: "<<Ti_zone<<endl;
			
		}
		cout<<"Final Ti_found: "<<Ti_found<<endl;
		cout<<"Final Ti_zone: "<<Ti_zone<<endl;
		Space(1);
		
			
		Space(1);
		
		int Response1 = 0;
		while(Response1 != 1){
			cout<<"Enter the desired output file "<<i+1<<"'s name (Max Char=30): "<<endl;
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
		}
		if(outputfile1.good()){
			cout<<OutputFileName<<" is ready"<<endl;
			Space(1);
		}

		//const int nArray2 = nArray - Ti_zone;
		
		double Co;
		double Vo;
		double Co[nArray];
		double Ci[nArray];
		double Vo[nArray];
		double Vd[nArray];
		double Vr[nArray];
		
		////// Calculations ///////
		
		double Co = sqrt(pressure[To_zone-1]/rho[To_zone-1]);
		double Vo = vel_km_per_s[To_zone-1];
		
		outputfile1<<setw(2)<<"N_zone"<<setw(25)<<"Co"<<setw(25)<<"Vo"<<endl;
		outputfile1<<setw(2)<<To_zone<<setprecision(17)<<setw(25)<<Co<<setw(25)<<setw(25)<<Vo<<endl;
		
		// Calculation loop, starting at Ti_zone that was found
		outputfile1<<setw(2)<<"zone"<<setw(25)<<"Ci"<<setw(25)<<"Vd"<<setw(25)<<"Vr"<<endl;
		for(int c = Ti_zone-1; c < NumOfZones; c++){
			//Co[c] = Co;
			//Vo[c] = Vo;
			Ci[c] = sqrt(pressure[c]/rho[c]);
			Vd[c] = Ci[c] - sqrt((Ci[c]*Ci[c])-(Co*Co)); 
			Vr[c] = Ci[c] + sqrt((Ci[c]*Ci[c])-(Co*Co)); 
			
			outputfile1<<setw(2)<<(c+1)<<setprecision(17)<<setw(25)<<Ci[c]<<setw(25)<<Vd[c]<<setw(25)<<Vr[c]<<endl;
			
		}
		
		outputfile1.close();
		if(!outputfile1.is_open()){
			cout<<"File was filled and closed successfully"<<endl;
		}
		
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



