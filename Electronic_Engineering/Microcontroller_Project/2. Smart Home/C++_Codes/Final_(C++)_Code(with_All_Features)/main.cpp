#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>



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

    cout<<"Air purifier has started purifying the air" <<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
   }

   else
    {

    cout<<" Air purifier has been turned off by the system, Air Quality is Okk now"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    }


}




void SmartDoor()

{

                int x;
                int y;
                int Scan;
                bool SelectionButton ;
                bool OpenDoor;
                bool Press;



		cout << "How do you want to open the door ?" << endl;

		cout << "Please select a number of your choice on the selectionmenu" << endl;
		cout << "Selectionbutton\n" << endl;
		cout << "\tFINGERPRINT\t\t\tFACESCANNER\t\t\tKEY" << endl;
		cout << "\t1\t\t\t\t2\t\t\t\t3" << endl;

		cin >> x;

		if (x == 1) {
			cout << "BlueCircle" << endl;
			cout << "Press your thumb within the blue circle." << endl;
			cin >> Press;

			if (Press == 1)
			{
				cout << "Accepted!! The door is now open. You can enter into the house." << endl;
			}
			else
			{
				cout << "Rejected!! Press again or go back to main menu" << endl;

			}


		}
		else if (x == 2)
		{
			cout << "Green Circle" << endl;
			cout << "Stand in front of the Green Circle and Open your eyes" << endl;
			cout << "Press 4 to scan" << endl;
			cin >> Scan;
			if (Scan == 4)
			{
				cout << "FaceScanner- Value" << endl;
				cin >> y;
				if (y == 123)
				{
					cout << "Accepted!! The door is now open. You can enter into the house." << endl;
				}
				else
				{
					cout << "Rejected!! Scan again or go back to main menu " << endl;
				}

			}

			else
			{
				cout << "Please stand in front of the scanner or go back to Menu" << endl;
				/*void Timer::setTimeout(auto function, int delay) {
					this->clear = false;
					std::thread t([=]() {
						if (this->clear) return;
						std::Scan::sleep_for(std::chrono::10000(delay));
						if (this->clear) return;
						function();
					});
					t.detach();*/
			}
		}
		else if (x == 3)
		{
			cout << "Please use your Key to open the door." << endl;
		}
		else
		{
			cout << "Invalid" << endl;
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
    cout<<"(3) Smart Door "<<endl;
    cout<<"(4) Luminence Control System"<<endl;
    cin>>p;



if(p == 2)
    {
        air();
    }
else if(p == 3)
{
    SmartDoor();
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

else if (p==4)
{
    int b; //light from bulbs
	int f; //window film level
	int l; //luminance = light from bulbs - window film level
	int e; //expected luminance

	//l = b-f; luminance should= light from bulbs - window film level

	cout<<"Current luminance in the room: ";
	cin>>l;
	cout<<"\nEnter expected illuminance: ";
	cin>>e;

	cout<<"\nCurrent luminance of light bulbs: ";
	cin>>b;
	cout<<"\nCurrent window film level: ";
	cin>>f;

	//When inputed luminance doesnt equal to light from bulbs + sunlight(!film) => sth kaputt
	if (l != b-f){
		cout<<"\nCalling a technician for you...\n";

    }

	//when current luminance is the expectation
	else if (l==e){
		cout<<"\nLuminance is at expected level.\n";

	}

	else{
		l == b-f; //luminance should= light from bulbs - window film level
		//when current luminance is higher than expectation
		for (l > 0; l > e; b--){
			if (l == e){
				cout<<"\nLuminance is at expected level.\n";
			}
			else if (b <= 0){
				if (l == e){
					cout<<"\nLuminance is at expected level.\n";
					}
					else if (l > e){
						f++;
						if (l == e){
							cout<<"\nLuminance is at expected level.\n";
							}
					}
				}
		}

		//when current luminance is lower than expectation but light still exsist
		for (l > 0; l < e; f--){
			if (l == e){
				cout<<"\nLuminance is at expected level.\n";
			}

			else if (f <= 0){
				if (l == e){
					cout<<"Luminance is at expected level.\n";
					}
					else if (l < e){
						b++;
						if (l == e){
							cout<<"Luminance is at expected level.\n";
						}
					}
			}
		}

		//when there's no light at all
		for (l <= 0; l < e; b++){
			if (l == e){
				cout<<"Luminance is at expected level\n";
			}
		}
	}
}

else
    {
     cout << "Invalid input. Please try again" << endl;
    }


 }

getch();

  }
