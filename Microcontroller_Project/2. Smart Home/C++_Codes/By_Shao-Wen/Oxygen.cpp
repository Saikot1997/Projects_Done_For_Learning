#include<iostream>
using namespace std;

//Air permiability control for the window 

#include<iostream>
using namespace std;

//Air permiability control for the window 

int main(){
	//int q=21; //ideal air quality/oxygen level(21%)
	int o; //current oxygen level(%) in  the room 
	int p; //air permiability level of windows
	
	//21 = o+p = o1 
	//adjusted new oxygen level = current oxygen level + oxygen through the window(air permiability) = ideal oxygen level = 21
	
	
	cout<<"Current oxygen level(%): ";
	cin>>o;
	
	
	
	//when room oxygen is at ideal percentage(= ideal air pressure)
	if (o==21){
		cout<<"\nAir quality is at ideal level."<<endl;
		return 0;
	}
	
	//Survival protection: when there's no oxygen 
	else if (o<=0){
		cout<<"\nDangerous air quality."<<endl;
		p = 21 - o;
		cout<<"\nAir permiability level of windows is adjusted to %d."<<" "<<p<<endl;
		cout<<"\nAir quality is adjusted to ideal level."<<endl;
	
		return 0;
	}
	
	else{
		p = 21 - o;
		cout<<"\nAir permiability level of windows is adjusted to %d."<<" "<<p<<endl;
		cout<<"\nAir quality is adjusted to ideal level."<<endl;
		
		return 0;
	}
}
