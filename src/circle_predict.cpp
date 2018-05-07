#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
struct simplehash{
    template <class T1, class T2>
    bool operator()(const pair<T1,T2>& p)const{
        auto h1 = hash<T1>();
        auto h2 = hash<T2>();
        return h1(p.first)^h2(p.second);
    }
};
int main(int argc, const char * argv[]) {
    
    
    string file_dir="./";
    string file_name=argv[1];
    //string file_name="110701307803962595019.edges";
    ifstream edge_file(file_dir+file_name+".edges");
    if(edge_file.good())cout<<file_name<<" file open success"<<endl;
    else {
        cout<<"file open fail"<<endl;
        return 0;
    }
    
    int num_vertex;
    int num_edge;
    
    
    string edg_str;
    getline(edge_file,edg_str);
    
    int counter=1;
    cout<<"Reorganizing edges....."<<endl;
    unordered_set<string>vertices;//mapping original id to a new id starting from 1
    unordered_set<pair<string,string>,simplehash>edges;
    string outputFileName=file_name+"_edgeNormalized.mtx";
    ofstream p_file(file_dir+outputFileName);
    while(getline(edge_file,edg_str)){
        stringstream ss(edg_str);
        string u;
        string v;
        ss>>u>>v;
        //cout<<u<<","<<v<<endl;
        vertices.insert(u);
        vertices.insert(v);
        if(edges.count({u,v})==0&&edges.count({v,u})==0){
            edges.insert({u,v});
        }
        
    }
    
    num_vertex=int(vertices.size());
    num_edge=int(edges.size());
    //cout<<"V="<<num_vertex<<", E="<<num_edge<<endl;
    p_file<<num_vertex<<" "<<num_edge<<"\n";
    for(auto e:edges){
        p_file<<e.first<<" "<<e.second<<"\n";
    }
    p_file.close();
    cout<<"Running Ktruss...."<<endl;
    string cmd="./../../..//backup/nd_ori/nucleus ./"+outputFileName+" 23 YES";
    //string cmd="./..//nd/nucleus ..//data/temp/ego_"+to_string(i)+"_minus_ego.mtx 12 YES";
    
    system(cmd.c_str());
    //output predict circle:
    ifstream nucleusFile(outputFileName+"_23_Hierarchy");
    string line;
    cout<<"Outputing Circle Prediction file....."<<endl;
    ofstream c_file(file_dir+file_name+".Predict");
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
                //cout<<id<<" ";
                c_file<<id<<" ";
            }
            //cout<<endl;
            c_file<<'\n';
        }
    }
    c_file.close();
    ifstream c_file_origin(file_dir+file_name+".circles");
    cout<<"Outputing Circle GroundTrue File....."<<endl;
    ofstream groundTrueCircle(file_dir+file_name+".GroundTrue");
    while(getline(c_file_origin,line)){
        stringstream ss(line);
        string dummy;
        ss>>dummy;
        int id;
        while(ss>>id){
            groundTrueCircle<<id<<" ";
        }
        groundTrueCircle<<"\n";
    }
    c_file_origin.close();
    groundTrueCircle.close();
    

}