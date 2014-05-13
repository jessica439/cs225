#include <iostream>
#include "png.h"
#include "rgbapixel.h"
using namespace std;
int main(){
	int count = 0;
	PNG pic("output.png");
	for (size_t i = 0;i<pic.width();i++){
		if(pic(i,0)->red!=0){
			cout<<"red: "<<(int)pic(i,0)->red<<endl;
			count++;
		}
		if(pic(i,0)->green!=0){
			cout<<"green: "<<(int)pic(i,0)->green<<endl;
			count++;	
		}
		if(pic(i,0)->blue!=0){
			cout<<"blue: "<<(int)pic(i,0)->blue<<endl;
			count++;
		}
		if(pic(i,0)->alpha!=0){
			cout<<"alpha: "<<(int)pic(i,0)->alpha<<endl;
			count++;
		}
		cout<<endl;
	}
	cout<<count<<endl;

}
