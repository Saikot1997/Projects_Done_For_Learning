#include <iostream>


using namespace std;

int x;
int y;
int ScannedData = 1122;// a sample customised data used to compare sensor data for face scanner
int Scan;
int Press = 3344;// a sample customized data to compare sensor data for fingerprint scanner



int main()

{
	while (1)
	{
		cout << "How do you want to open the door ?" << endl;

		cout << "Please select a number of your choice on the selectionmenu" << endl;
		cout << "Selectionbutton\n" << endl;
		cout << "\tFINGERPRINT\t\t\tFACESCANNER\t\t\tKEY" << endl;
		cout << "\t1\t\t\t\t2\t\t\t\t3" << endl;

		cin >> x;

		if (x == 1) {
			cout << "BlueCircle" << endl;
			cout << "Press your thumb within the blue circle." << endl;
			cin >> y;

			if (y == Press)
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
			cin >> Scan;
			if (Scan == ScannedData)
			{
				cout << "Accepted!! The door is now open. You can enter into the house." << endl;
			}
			else
			{
				cout << "Rejected!! Scan again or go back to main menu " << endl;
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
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
	}

	return 0;
}