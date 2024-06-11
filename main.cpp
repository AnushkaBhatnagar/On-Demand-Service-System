#include <iostream>
#include <regex>  //login testcases
#include "input.hpp" //to mask the password
#include <fstream> 
#include <stdio.h>
#include <string.h>
#include <iostream> 
#include <vector>

using namespace std;

class Services;
class Bill;
class Employee;
class Customer
{
  string name, email, phone, address, password;
  public:
  int flag = true;
  void Register()
  {
    int f1 = true, f2 = true, f3 = true;
    cout << endl << "REGISTRATION" << endl;
    cout << "Name: ";
    getline(cin >> ws, name);
    while (f1)
    {
      cout << "Email: ";
      cin >> email;
      const regex pattern1("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
      if(regex_match(email, pattern1))
      {
        f1 = false;
        break;
      }
      else
      {
        cout << "Invalid Email-Id." << endl;
      }
    }
    while (f2)
    {
      const regex pattern2("(0|91)?[7-9][0-9]{9}");
      cout << "Phone Number: ";
      cin >> phone;
      if(regex_match(phone, pattern2))
      {
        f2 = false;
        break;
      }
      else
      {
        cout << "Invalid Phone Number." << endl;
      }
    }
    cout << "Address: ";
    getline(cin>>ws,address);
    while(f3)
    {
      cout << "Password: ";
      cin >> password;
      bool hasLower = false, hasUpper = false;
      bool hasDigit = false, specialChar = false;
      string normalChars = "abcdefghijklmnopqrstu" "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
      for (int i = 0; i < password.length(); i++) 
      {
        if (islower(password[i]))
          hasLower = true;
        if (isupper(password[i]))
          hasUpper = true;
        if (isdigit(password[i]))
          hasDigit = true;
        size_t special = password.find_first_not_of(normalChars);
        if (special != string::npos)
          specialChar = true;
      }
      if (hasDigit == true && hasLower == true && hasUpper == true && specialChar == true && password.length() > 6 && password.length() < 15)
      {
        f3 = false;
        cout<<endl<<"You have been registered sucessfully!"<<endl<<"Proceed to Login with the registered phone number."<< endl;
        break;
      }
      else
      {
        cout << "Invalid Password." << endl;
        cout<<"Password should have a length of 7 characters and atmax 15 characters. It should also contain uppercase characters, lowercase characters, digits and special characters."<<endl;
      }
    }
    details(name, phone, password);
  }

  void details(string name, string phone, string password)
  {
    ofstream file;
    file.open("customer.txt" , ios::app);
    vector <string> details;
    {
      details.push_back(name);
      details.push_back(phone);
      details.push_back(password);
    }
    for(string i:details)
    {
      file << i << endl;
    }
    file.close();
  }

  int login()
  {
    string no;
    cout << endl << "LOGIN" << endl;
    cout<<"Enter Phone Number: ";
    cin>>no;
    g:
    char c=' ';
    string pass="";
    cout<<"Enter Password: ";
    while(c!=10)
    {
      c=getch();
      if(c!=10)
      {
        pass=pass+c;
        cout<<"*";
      }
    }

    ifstream op("customer.txt");
    if(!op.is_open()) std::cout << "ERROR: File Open" <<endl;
    cout<<endl<< "----------------------"<<endl;
    string name1, phone1, password1, name;
    int w=0;
    while(op.peek()!=EOF)
    {
      getline(op, name1);
      getline(op, phone1);
      getline(op, password1);
      if(phone1 == no)
      {
        phone = phone1;
        password = password1;
        name = name1;
        //w=1;
      }
    }
    if(no!=phone&&pass!=password)
    {
      cout<<endl<<"The phone number and password entered are not registered on system. Please enter the information again."<<endl;
      login();
    }
    else if(no!=phone&&pass==password)
    {
      cout<<endl<<"The phone number entered is not registered on system. Please enter the information again."<<endl;
      login();
    }
    else if(no==phone&&pass!=password)
    {
      cout<<endl <<"The password entered is invalid. Please enter the information again."<<endl;
      goto g;
    }
    else
    {
      cout<<endl<<endl<<"Log-in Successful!"<<endl;
      cout<<"Welcome, "<<name<<"!"<<endl<<endl;
    }
    return 1;
  }
};

class Services
{
  protected:
  int on, q, mainservice; //serial no. and quantity entered by user
  string sno, name, price; //to get information from the 4 service files
  string serv, service; //original, original+csv
  string opted[4]; //contains names of all services selected by user
  int x=0,w,j=0; //x is used for checking if sno entered by user is correct
  //w is for checking if user wants to continue or not
  //j keeps track of the number of main services that the user has opted for (will be <=4)
  public:
  void retrieve(ifstream& ip) //accessing the 4 service files
  { //the 4 service files follow the same format
    getline(ip,sno,',');
    getline(ip,name,',');
    getline(ip,price,'\n');
  }
  void selectservices()
  {
    char f='y',ch='y';
    int i=0;
    bool flag=false; //checks whether service opted for by user has already been selected or not
    while(f=='y'||f=='Y')
    {
      flag=false; //for each iteration
      serv="",service="";
      cout<< "Please select a service!"<<endl<<endl;
      cout<<"1. Cleaning \n2. Salon \n3. Pest Control \n4. Painting\n";
      cout<<"Enter name of the service: "<<endl;
      getline(cin>>ws,serv);
      service=serv+".csv";
      ifstream ip(service); 
      if(!ip.is_open()) 
      {
        std::cout << "ERROR: File Open" <<endl;
        cout << endl<<"Sorry! No results found for this service. Please try for another option." << endl;
        continue;
      }
      for(int k=0;k<4;k++)
      {
        if(opted[k]==serv) //checks whether the service entered by user is present in the array 
        {
          flag=true; //meaning service name is present in the list
        }
      }
      if(flag==false) //service name is not present, so we include it
      {
        opted[j]=serv;
        j++;
      }
      cout<<endl<<"The services offered under "<<serv<<" are:"<<endl;
      display(ip);
      while(ch=='Y' || ch == 'y')
      {
        x=0;
        select_serialno:
        cout << endl<<"Select Serial Number: ";
        cin >> on; 
        if(serv=="Cleaning"||serv=="Pest Control"||serv=="Painting")
        cout<<"Enter the number of rooms to be serviced: ";
        else if(serv=="Salon")
        cout<<"Enter the number of people for whom the service is required: ";
   	    cin >> q; //storing quantity (no. of rooms or people)
        string str_q=to_string(q);
        ifstream jp(service); //******check for a way to get ip back to start
        addtocart(on,str_q,jp);
        if(x == 0)
        {
          cout << "Wrong Serial Number! Try another option."<< endl;
          goto select_serialno;
        }
        cout<<endl<<"Do you wish to add another service? y/n"<<endl;
        cin>>ch;
        if(ch=='y'||ch=='Y')
        {
          cout<<endl<<"Do you wish to add another service under "<<serv<<" or choose another?"<<endl;
          cout<<"Press 1 for same and 2 for different"<<endl;
          cin>>w;
          if(w==2)
          break; //inner loop terminated, we now go to the outer while loop for f
        }
        else //user does not wish to add another service
        {
          f='n'; //outer loop will terminate
          ip.close();
          jp.close();
        }
      } 
    }
  }
 void display(ifstream& ip) //called from selectservices()
  {
    int i=0; //so the first row doesn't get printed
    while(ip.peek()!=EOF) //runs until we reach end of file
    {
      retrieve(ip);
      if(i!=0)
      {
        cout<<endl<<"Sr No: "<< sno << endl;
        cout<<"Service: " << name << endl;
        if(serv=="Cleaning"||serv=="Pest Control"||serv=="Painting")
        cout<<"Price per Room: Rs. "<<price<<endl;
        else if(serv=="Salon")
        cout<<"Price per Person: Rs. "<<price<<endl;
        cout<< "-------------------"<<endl;
      }
      i=1;
    }
    ip.close();
  }
  void addtocart(int on,string q,ifstream& jp) //called from selectservices()
  {
   int i=0;
   ofstream file;
   file.open("cart.txt",ios::app);
   vector <string> list; //list is any name for vector
   while(jp.peek()!=EOF)
   {
     retrieve(jp);
     if(i!=0) //to not print the 1st row
     {
        if(on == stoi(sno)) //serial no. entered by user== serial no. present in services (.csv file)
        {
          x=1; //serial number is present
          list.push_back(name);
          list.push_back(price);
          list.push_back(q);
        }
      }
      i=1;
    }
    for(string z:list)
    {
      file << z << endl;
    }
    jp.close();
    file.close();
  }
};

class Bill 
{
  double amt, tip, cvv; //information is private
  string name, validity, accno, pwd;
  long int cardno;

  public:

  void viewbill()
  {
    string name, price, q;
    ifstream op("cart.txt");
    if(!op.is_open()) std::cout << "ERROR: File Open" <<endl;
    while(op.peek()!=EOF)
    {
      getline(op, name);
      getline(op, price);
      getline(op, q);
      cout<< name<< "   x "<<q << endl;
      cout <<"Rs. " <<price << endl;
      cout<<endl;
      amt= amt+ (stof(price)*stoi(q));
    }
    cout<<endl<<"Total Amount: Rs. "<<amt<<" /-"<<endl;
    op.close();
  }
  
  void calculateBill()
  {
    int t, c, k=0, p;
    cout<<"Thank you for selecting the services!"<<endl;
    cout<<"Do you wish to tip the employee?\n1.YES\n2.NO"<<endl;
    cin>>t;
    if (t==1)
    {
      cout<<"Enter the amount you want to tip: ";
      cin>>tip;
      cout<<endl<<"Thank You for providing the tip!"<<endl;
      amt = amt+tip;
      cout<<endl<<"Your final amount to be paid is: "<<amt<<" /-"<<endl;
    }
    else
    {
      cout<<endl<<"Your final Bill Amount to be paid is: Rs.  "<<amt<<" /-"<<endl;
    } 
    cout<<endl<<"Please enter your preferred method of payment: "<<endl;
    do
    {
      k = 0;
      cout<<"1. Cash at the time of service\n2. Card\n3. Net Banking"<<endl;
      cin>>c; 
      switch(c)
      {
        case 1:
        cout<<endl<<"The final amount payable at the time of service is: Rs. "<<amt<<" /-"<<endl;
        break;
        case 2:
        cout<<endl<<"Enter the name on the card: ";
        getline(cin>>ws,name);
        cout<<"Enter card number: ";
        cin>>cardno;
        cout<<"Enter validity of your card in (MM/YY) format): ";
        getline(cin>>ws,validity);
        cout<<"Enter 3 digit CVV: ";
        cin>>cvv;
        cout<<endl<<"Payment succesful!"<<endl;
        cout<<endl<<"Rs. "<<amt<<" /- have been deducted from your account.\n\nThank you for chosing our services :)"<<endl;
        break;       
        case 3:
        cout<<endl<<"Select any one net banking option as per your choice: "<<endl;
        cout<<"Enter: \n1.Paytm\n2.GPay\n3.UPI\n";
        cin>>p;
        if(p==1)
        {
          cout<<endl<<"Enter Account Number: ";
          getline(cin>>ws,accno);
          cout<<"Enter the password:";
          getline(cin>>ws,pwd);
          cout<<endl<<"Payment Succesful!"<<endl;
          cout<<endl<<"Rs. "<<amt<<" /- have been deducted from your account.\nThank You for using our Services!"<<endl;
        }
        else if(p==2)
        {
          cout<<endl<<"Enter Account Number: ";
          cin>>accno;
          cout<<"Enter Password: ";
          cin>>pwd;
          cout<<endl<<"Payment Succesful!"<<endl;
          cout<<endl<<"Rs. "<<amt<<" /- have been deducted from your account.\n\nThank You for using our Services!"<<endl;
        }
        else if(p==3)
        {
          cout<<endl<<"Enter Account Number: ";
          cin>>accno;
          cout<<"Enter Password: ";
          cin>>pwd;
          cout<<endl<<"Payment Succesful!"<<endl;
          cout<<endl<<"Rs. "<<amt<<" /- have been deducted from your account"<<endl<<endl<<"Thank You for using our Services!"<<endl;
        }
        else
        {
          cout<<endl<<"Please chose a valid option"<<endl;
          k = 1;
        }
        break;
        default:
        cout<<endl<<"Please chose a valid option"<<endl;
        k = 1;
        break;
      }
    }while(k!=0);
  }
};
class Employee : public Services
{
  string sr_no, emp_name, emp_phoneno, emp_area, emp_ser;
  public:
  void assign()
  {
    int i;
    ifstream ep("Employee.csv");
    if(!ep.is_open()) std::cout << "ERROR: File Open" <<endl;
    cout<<endl<< "----------------------"<<endl;
    while(ep.peek()!=EOF)
    {
      getline(ep, sr_no,',');
      getline(ep, emp_name,',');
      getline(ep, emp_ser,',');
      getline(ep, emp_phoneno,',');
      getline(ep, emp_area,'\n');
      for(i=0;i<j;i++)
      {
        if(emp_ser==opted[i])
        {
          cout<<endl<<"Your booking has been confirmed for "<<emp_ser<<"!\n";
          cout<<"Employee Assigned for "<<emp_ser<<" is: "<<emp_name<<endl;
          cout<<"Employee's Phone Number: "<<emp_phoneno<<endl;
        }
      }
    }
    ep.close();
  }
};

int main() 
{
  Customer obj1;
  Employee obj2;
  Bill obj3;
  int c,success=0,choice, a;
  cout << endl<<"Welcome!"<<endl<<endl;
  cout<<"Do you wish to:\n1. Register\n2. Login\n";
  cin>>c;
  while(c!=1&&c!=2)
  {
    cout<<"Value entered is invalid. Please enter again:"<<endl;
    cin>>c;
  }
  if(c==1)
  {
    obj1.Register();
    success=obj1.login();
  }
  else //c=2
  success=obj1.login();
  if(success==1)
  {
    obj2.selectservices();
    cout<<endl<<"The bill generated is as follows: "<<endl<<endl;
    obj3.viewbill();
    obj3.calculateBill();
    obj2.assign();
    ofstream file; 
    file.open("cart.txt");
    file.close(); //deletes contents of the file as we're operating it without append
  }
}