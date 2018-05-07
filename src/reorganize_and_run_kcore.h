#ifndef REORGANIZEANDRUNKCORE_H
#define REORGANIZEANDRUNKCORE_H


#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
// #include "simplehash.h"
#include "CirclePrediction.h"

using namespace std; 

void reorganize_and_run_kcore(vector<unordered_map<int,vector<int>>>&ego_net,string file_name){

  string dirname=file_name+"_kcore";
  string cmd1="rm -r "+dirname;
  system(cmd1.c_str());
  string cmd2="mkdir "+dirname;
  system(cmd2.c_str());
  string cmd3="mkdir "+dirname+"/kcore_out";
  system(cmd3.c_str());

  //Run kcore_decomposition which generate each ego's huerarchy and nucleius
 


  for(int i=0;i<ego_net.size();i++){
    string cmd="./nd/nucleus data/temp/"+file_name+"_ego_"+to_string(i)+"_minus_ego.mtx 12 YES "+dirname;    
    system(cmd.c_str());

  }
  cout<<"Output the Prediction....."<<endl;
  string c_str="mkdir Prediction";
  system(c_str.c_str());
  for(int i=0;i<ego_net.size();i++){
    string fname=file_name+"_ego_"+to_string(i)+"_minus_ego.mtx_12_Hierarchy";
    generateCircleFile("./"+dirname+"/kcore_out/"+fname,"./Prediction/");
  }

  cout<<"Romoving temp data......"<<endl;
  system("rm -r data/temp");
  string cmd4="rm -r "+dirname;
  system(cmd4.c_str());



}





#endif

