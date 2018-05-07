#ifndef CIRCLEPREDICTION_H
#define CIRCLEPREDICTION_H

#include <iostream>


using namespace std; 
void generateCircleFile(string NucleusFile,string file_dir){
	// string c_str="mkdir Prediction";
	// system(c_str.c_str());
	//string file_dir="./Prediction/";

	ifstream nucleusFile(NucleusFile);
	if(nucleusFile.good()){

	}
    else {
        cout<<NucleusFile<<" file open fail"<<endl;
        return ;	
    }
    string line;
    string filename=NucleusFile.substr(NucleusFile.find_last_of('/'));
    ofstream c_file(file_dir+filename+".Predict");
    while(getline(nucleusFile,line)){
        if(line.substr(0,2)=="id"){
            stringstream ss(line);
            string dummy;
            for(int i=0;i<15;i++){
                ss>>dummy;
            }
            string id;
            while(ss>>id){
                if(id=="-1")break;
                c_file<<id<<" ";
            }
            c_file<<'\n';
        }
    }
    c_file.close();
    

}
#endif