// Program to read from file into arrays, and to output values for D/R type analysis
// V1: Copy of program ReadingFromFileIntoArrays_V4, fitted to do stuff with the arrays, output results
	// Note: Temp and temp zone findings not working right? Keeps getting either 0 or last num.

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
	int NumOfFiles;
	
	cout<<"Enter the number of files to read (Usually 5): "<<endl;
	cin>>NumOfFiles;
	
	ifstream infile;
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
	
	for(int i = 0; i < NumOfFiles; i++){
		
		///// Finding File //////
		int TryAgain = 1;
		while(TryAgain == 1){
			char InputFileName[30];
			cout<<"Enter Input File "<<i+1<<"s Name (Max Char=30): "<<endl;
			cin>>InputFileName;
			
			infile.open(InputFileName);
			
			// Warning if file cant be opened
			if(!infile.is_open()){ 
				cout << "Error opening file. \n";
				cout << "Giving Retry... \n";
			}
			if(infile.is_open()){
				cout<<"File was opened successfully"<<endl;
				TryAgain = 0;
			}
		}
			
		if(infile.is_open()){
		
			//cout<<"Enter the output file name: "<<endl;
			//ofstream outputfile1("FreeFall_Analytical_wArrays_output.dat");
		
			// Putting cursor at start of file
			infile.clear();
		
		
			// Mdis loop //
			if(i == 0){
				for (int a = 0; a < NumOfZones; a++){
						infile >> Mdis[a];
						cout<<Mdis[a]<<endl;
				}
			}
			
			// rho loop //
			if(i == 1){
				for (int a = 0; a < NumOfZones; a++){
						infile >> rho[a];
						cout<<rho[a]<<endl;
				}
			}
			
			// pressure loop //
			if(i == 2){
				for (int a = 0; a < NumOfZones; a++){
						infile >> pressure[a];
						cout<<pressure[a]<<endl;
				}
			}
			
			// vel_km_per_s loop //
			if(i == 3){
				for (int a = 0; a < NumOfZones; a++){
						infile >> vel_km_per_s[a];
						cout<<vel_km_per_s[a]<<endl;
				}
			}
			
			// Temp loop //
			if(i == 4){
				for (int a = 0; a < NumOfZones; a++){
						infile >> Temp[a];
						cout<<Temp[a]<<endl;
				}
			}
		}
		
		// Close the file.
		infile.close();
		
		if(!infile.is_open()){
			cout<<"File closed successfully"<<endl;
		}
		
		Space(2);
	}
	
	///////////////////////////////////////////////////////////////////////
	
	//// Making Output arrays ////
	
	double To;
	double Ti;

	// Note: Program picks first number after specified values for temp
	cout<<"Enter the temp for the neutral side:"<<endl;
	cin>>To;
	
	// Temp Finder Loop 1 - Neutral side
	for(int T1 = 0; T1 < NumOfZones && Temp[T1] < To; T1++){
		double To_found = Temp[T1];
		double To_zone = T1 + 1;
	}
	cout<<"To_found: "<<To_found<<endl;
	cout<<"To_zone: "<<To_zone<<endl;
	Space(1);
	
	cout<<"Enter the temp for the ionized side:"<<endl;
	cin>>Ti;
	
	// Temp Finder Loop 2 - Ionized side
	for(int T2 = 0; T2 < NumOfZones && Temp[T2] < Ti; T2++){
		double Ti_found = Temp[T2];
		double Ti_zone = T2 + 1;
	}
	cout<<"Ti_found: "<<Ti_found<<endl;
	cout<<"Ti_zone: "<<Ti_zone<<endl;
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



