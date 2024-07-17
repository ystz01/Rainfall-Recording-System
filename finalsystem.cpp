#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;
double rainfall[12];
string name;
string Month[] = {"January", "February", "March", "April", "May", "June", "July", "August", 
"September", "October", "November", "December"};
void login();	//function declaration for login
void inputdata();//function declaration for inputdata
void showgraph();//function declaration for showgraph
void showreport();//function declaration for showreport
int main(){
	login();//call login function
	int choose;
	do{	
		cout<<"Please select the function to use it."<<endl;
		cout<<"1 Input data"<<endl;
		cout<<"2 Show Report"<<endl;
		cout<<"3 Show Graph"<<endl;
		cout<<"4 EXIT"<<endl;
		cout<<"Please Enter:";
		cin>>choose;
		switch(choose){
			case 1:
				inputdata();
				break;
			case 2:
				showreport();
				break;
			case 3:
				showgraph();
				break;
			case 4:
				cout<<endl;
				cout<<"Program End."<<endl;
				break;
			default:
				cout<<"Invalid Choice. Enter Again."<<endl;
				cout<<endl;
				break;
		}
	}while(choose!=4);
	return 0;
}

//login function
void login(){
	string pwd;
	cout<<"##########-Rainfall Record System-##########"<<endl;
	cout<<endl;
	cout<<"Please enter your name: ";	//Enter name
	getline(cin,name);
	cout<<"Please enter system password: ";//Enter Password
	getline(cin,pwd);
	while(pwd!="@bc123def"){ //if password incorrect,loop
		cout<<"Password Error! Enter again: ";
		getline(cin,pwd);
	}
	cout<<endl;
	cout<<"Welcome, "<<name<<endl;
}
//Input data Function
void inputdata(){
	ofstream outfile; // Create an output file stream
    string stateName;
    string Filename;
    time_t now = time(0); // Get the current time
    tm* localtm = localtime(&now); // Convert to local time(human readable time)
    stringstream ss;
    ss << (localtm->tm_year + 1900) << "-" << (localtm->tm_mon + 1) << "-" << localtm->tm_mday;//convert date to yyyy-mm-dd
    string entry_date = ss.str();
	
	cout<<endl;
	cout<<"#######----Input data----#######"<<endl;
    cout << "Enter the File name for input data: ";
    cin.ignore(); // Clear any pending newline characters
    getline(cin, Filename);
    
    // Check if the filename has a ".txt" extension
    //Filename.substr(filename.length() - 4) != ".txt" check last 4place is .txt or not
    if (Filename.length() < 4 || Filename.substr(Filename.length() - 4) != ".txt") {
        // If it doesn't have ".txt", add it
        Filename += ".txt";
    }
    
    outfile.open(Filename.c_str()); // Open the specified file 
    
	
    if (outfile.is_open()) { //check the valid of the file
		outfile << "Date of Data Entry: "<<entry_date<<endl;
		outfile<<"Data Entry By: "<<name<<endl;
        cout << "Enter the name of the state: ";
        getline(cin, stateName);
		
        outfile <<"State: "<<stateName << endl;
        for (int i = 0; i < 12; i++) {
            do {
                cout << "Enter rainfall for " <<setw(12)<<left<< Month[i] << " (in centimeters): ";
                cin >> rainfall[i];
                if(rainfall[i] > 0 && rainfall[i] <= 45){
                	outfile << Month[i] << ":" << rainfall[i] << endl;//Output eg: January:
				}
                

                if (rainfall[i] < 0 || rainfall[i] > 45) {
                    cout << "Invalid Rainfall! Rainfall must be between 0 and 45 centimeters. Please Re-Enter." << endl;
               }
            } while (rainfall[i] < 0 || rainfall[i] > 45);
        }
    
        outfile.close(); // Close the file
        cout<<endl;
        cout<<"#######----MESSAGE----#######"<<endl;
        cout<<"Data Successfully export to "<<Filename<<endl;
        cout<<"######----MESSAGE END----######"<<endl;
        cout<<endl;
    } else {
        cout << "Error opening the file." << endl;
    }
    cout<<endl;
}

//Report Function
void showreport(){
	ifstream infile;
	string filename;
	double total=0;
	double avg;
	string message;
	string statename;
	string dateofentry,user_name;
	cout<<endl;
	cout<<"#######----Show Report----#######"<<endl;
	cout << "Enter the file name you want to open: ";
	cin.get();
	getline(cin, filename);
	
	// Check if the filename has a ".txt" extension
    //Filename.substr(filename.length() - 4) != ".txt" check last 4place is .txt or not
    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") {
        // If it doesn't have ".txt", add it
        filename += ".txt";
    }
	  infile.open(filename.c_str());
	  if (!infile.is_open()) {	//Error message for file that can't open
			cout << "Error: file could not open or the file is not exist." << endl;
			cout<<endl;
	    
	  }
	  else{
	  // Declare a vector to store the number values.
	  vector<int> number_values;
		
	  // Read each line of the file.
	  string line;
	  while (getline(infile, line)) {
	  	int pos = line.find(":"); // find the position of a colon (":")
	    if (pos != string::npos) {	//check if the colon (":") was found in the line string
	        string label = line.substr(0, pos);//extract label(Before ":") from line and store in label
	        string value = line.substr(pos + 1);//extract value(after ":") from line and store in value
	
	        if (label == "State") {
	                statename = value;
	        }else if (label != "Date of Data Entry" && label != "Data Entry By") {
	                // Assuming the lines that are not date of entry or data entry by contain rainfall data
	                int number_value_int;
	                stringstream ss(value);
	                ss >> number_value_int;
	
	                if (ss) {
	                    number_values.push_back(number_value_int);
	                }
	            }
	        }
		}
		
	  // Close the text file.
	  infile.close();
	
	  // Print the number values using a for loop.
	  cout<<endl;
	  cout<<"===========Output==========="<<endl;
	  cout<<endl;
	  cout<<"Report of RainFall for "<<statename<<":"<<endl;
	  for (int i = 0; i < number_values.size(); i++) {
	    total=total+number_values[i];
	    cout<<setw(12)<<left<< Month[i]<<": "<<number_values[i] <<"cm"<< endl;
	  }
		avg=total/12;
		if (avg == 0) {
			message= "No rain";
		}else if (avg > 0 && avg <= 15) {
			message="less amount of rain";
		}else if (avg > 15 && avg <= 30) {
		    message= "moderate amount of rain";
		 }else if (avg > 30) {
		    message="heavy amount of rain fall.";
		 }
		cout<<endl;
		cout <<"Total rainfall = " << total <<"cm"<< endl;
		cout <<"Average rainfall in a year= "<< avg <<"cm"<< endl;
		cout<<statename<<" has "<<message<<". "<<endl;
		cout<<endl;
		cout<<"==============Output End============="<<endl;
		cout<<endl;
	}

}

//Show graph function
void showgraph(){
	ofstream outfile;
	ifstream infile;
	string gfile;
	string state_name,date_entry,username;
	
	cout<<endl;
	cout<<"#######----Show Graph----#######"<<endl;
	cout << "Enter the File name to show the data in graph:";
    cin.ignore(); // Clear any pending newline characters
    getline(cin, gfile);
    
    // Check if the filename has a ".txt" extension
    //gfile.length() < 4 || gfile.substr(gfile.length() - 4) != ".txt" check last 4place is .txt or not
    if (gfile.length() < 4 || gfile.substr(gfile.length() - 4) != ".txt") {
        // If it doesn't have ".txt", add it
        gfile += ".txt";
    }
	  infile.open(gfile.c_str());
	  if (!infile.is_open()) {
		cout << "Error: file could not open or file do not exist." << endl;
		cout<<endl;
	    
	  }
	  else{
	  	// Declare a vector to store the number values.
	  	vector<int> number_values;
		
	  	// Read each line of the file.
	  	string line;

	  	while (getline(infile, line)) {
	
	    // Split the line into two parts: the month and the number value.
	    string month, number_value;
	    int pos = line.find(":"); // find the position of a colon (":")
	    month = line.substr(0, pos);//extract month(Before ":") from line
	    number_value = line.substr(pos + 1);//extract rainfall value of each month(after ":") from line
	    if (pos != string::npos) {//check if the colon (":") was found in the line string
            string label = line.substr(0, pos);//extract value(after ":") from line and store in label
            string value = line.substr(pos + 1);//extract value(after ":") from line and store in value

            // Trim leading and trailing spaces from the value
            value = value.substr(value.find_first_not_of(" \t"));

            if (label == "Date of Data Entry") {
                date_entry = value;
            }
            else if (label == "Data Entry By") {
                username = value;
            }
            else if (label == "State") {
                state_name = value;
            }else{
            	// Convert the number_value to an integer using stringstream.
			    int number_value_int;
			    stringstream ss(number_value);
			    ss >> number_value_int;
			
			    if (!ss) {//Error message if the string can't convert to integer using stringstream
			      cout << "Error converting to integer: " << number_value << endl;
			    }
			
			    // Add the number value to the vector.
			    number_values.push_back(number_value_int);
	  		}
		}
	}
	    
	
	  // Close the text file.
	  infile.close();
	  
	  //Print the data into txt file
	  outfile.open("rainfall_chart.txt");
	  outfile<<"Date of Data Entry: "<<date_entry<<endl;
	  outfile<<"Data Entry by: "<<username<<endl;
	  outfile<<"RAINFALL FOR A YEAR IN "<<state_name<<endl;
	  outfile<<endl;
	  for (int i = 0; i < number_values.size(); i++) {	
	    outfile<<setw(12)<<left<< Month[i]<<" |";//Label for each month
		for(int j=0;j<(int)number_values[i];j++){	
			outfile<<"*";//Use symbol "*" to represent bar in char
		}
		outfile<<endl;
		outfile<<endl;
	  }
	  outfile.close();//close file
	  cout<<endl;
	  cout<<"#######----MESSAGE----#######"<<endl;
	  cout << "Rainfall chart has been saved to 'rainfall_chart.txt'." << endl;
	  cout<<"######----MESSAGE END----######"<<endl;
	  cout<<endl;
	  }

	}

