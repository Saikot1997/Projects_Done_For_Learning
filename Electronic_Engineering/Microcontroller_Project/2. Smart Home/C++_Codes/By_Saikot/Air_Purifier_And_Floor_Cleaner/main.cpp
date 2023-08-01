#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include<stdlib.h>



using namespace std;


 class sensor // Class for Automatic floor cleaner
{
    public:
    sensor(string dayName , int hour, int min)
    {
       cout<<" Automatic floor cleaner received the time to start  cleaning floor on"<<"  "<<dayName<<"  "<<hour<<":"<<min<<" 'o clock"<<endl;
       cout<<endl;
       cout<<endl;
       cout<<endl;
    };

};


void air()
{
   int exp  ;
   int xy;
   bool machine;
   cout<< "set your desired Air Quality level out of 100 (75 suggested)   "<<endl;
   cin>>exp;
   if(exp<0 || exp> 100)

   {
       cout<<"invalid input, Please try again."<<endl;
   }
   else
        {
	   cout << "Expected Air Quality level = " << exp << endl;
	   xy = rand() % 100;
           cout<<"instantenous sensor data = "<<xy<<endl;
        }



   if(xy<exp)
   {
    machine=1;
    cout<<"Air purifier has started purifying the air" <<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
   }

   else
    {
    machine=0;
    cout<<" Air purifier has been turned of by the system, Air Quality is Okk now"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    }


}


  int main()
  {

 while(1)
 {
     int p;

    cout<<"Which Feature you want to use"<<endl;
    cout<<"(1) Automatic floor cleaning " <<endl;
    cout<<"(2) Air purifier "<<endl;
    cin>>p;



if(p == 2)
    {
        air();
    }

else if (p==1)
{
       // current date/time based on current system
   time_t now = time(0);

   // convert now to string form
   char* dt = ctime(&now);
   cout << "The local date and time is: " << dt<< endl;


   string x;
   int y,z;
   cout << "Write down the day name" << endl;
   cin>>x;
   cout << "Which hour? ( in 24 hours clock system) " << endl;
   cin>>y;
   cout << "Minute? " << endl;
   cin>>z;
   sensor  startTime(x,y,z);
    }

else {    {
     cout << "Invalid input. Please try again" << endl;
    }
}

 }

getch();

  }
