#include <iostream>
using namespace std;
int main(){
	int b; //light from bulbs
	int s; //sunlight through window; adjusted transmittance level of window
	int c; //current luminance
	int e; //expected luminance
	int s0; //initial sunlight level
	
	cout<<"Current luminance in the room: ";
	cin>>c;
	cout<<endl<<"Enter expected luminance: ";
	cin>>e;
	cout<<endl<<"Current sunlight level: ";
	cin>>s0;
	
	//e = c +(b+s);
	// expectation = current luminance + (bulb+sunlight)
	
	//when current luminance is the expectation
	if (e==c){ 
		cout<<endl<<"Luminance is at expected level."<<endl;
		return 0;
	}
	
	//window transmits more light than current luminance => illogical
	else if (s0 > c){
		cout<<endl<<"Calling a technician for you..."<<endl;
	return 0;
	}
	
	//expect more light during night time/gloomy day
	else if (e > c && s0 <= 0){
		b = e-c;
		cout<<endl<<"Bulb luminance is increased by %d %. "<<" "<<b<<endl;
		cout<<endl<<"Luminance is now at expected level. "<<endl;
		return 0;
	}
	
	//expect more light during daytime
	else if (e > c && s0 > 0){
		s = e-c;
		cout<<endl<<"Window transmittance is increased by %d %."<<" "<<s<<endl;
		cout<<endl<<"Luminance is now at expected level."<<endl;
		return 0;
	}
	
	//expect less light during night time/gloomy day
	else if (e < c && s0 <= 0){
		b = c-e;
		cout<<endl<<"Bulb luminance is decreased by %d %. "<<" "<<b<<endl;
		cout<<endl<<"Luminance is now at expected level. "<<endl;
		return 0;
	}
	
	//expect less light during daytime
	else if (e < c && s0 > 0){
		s = c-e;
		cout<<endl<<"Window transmittance is decreased by %d %."<<" "<<s<<endl);
		cout<<endl<<"Luminance is now at expected level. "<<endl;
		return 0;
	}
}
