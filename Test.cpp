#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
 
// define a class to store student data
class student
{
   int rollno;
   char name[30];
   float eng;
   float math;
   float science;
   float total;
public:
   student() { }               //constructor
   void setData()              //function to get data for user
   {      
   	cout<<"Enter student details:";
   	cin.ignore();
   	cout<<"\nName:";
   	cin.getline(name,30);
   	cout<<"\nRoll No.:";
   	cin>>rollno;
   	cout<<"\nEnglish :";
   	cin>>eng;
   	cout<<"\nMaths:";
   	cin>>math;
   	cout<<"\nScience:";
   	cin>>science;
   	total=eng+math+science;
   }
    
   void displayData()           //function to display data of student
   {
   	 cout << "\nRoll No. : " << rollno << endl;
   cout << "\nName : " << name << endl;
   cout << "\nEnglish: " << eng << endl;
   cout << "\nMaths: " << math << endl;
   cout << "\nScience: " << science << endl;   
   }
   int getroll()                 //function to get roll no. of the student
   {       
   	return rollno;
   }
   void update()                //function to update the record
     {
   	   char ch='y';
   	   int c;
   	   float m;
   	   char a[30];
   	   while(ch=='y'){
   	   	    cout<<"What u want to update : 1.Name\t2.English marks\t3.Maths marks\t4.Science marks : ";
   	   	    cin>>c;
   	   	    switch(c)
   	   	    {
   	   	    	case 1:
   	   	    		cin.ignore();
   	   	    		cout<<"Enter name : ";
   	   	    		cin.getline(a,30);
   	   	    		strcpy(name,a);
   	   	    		break;
   	   	    	case 2:
   	   	    		cout<<"Enter english marks : ";
   	   	    		cin>>m;
   	   	    		eng=m;
   	   	    		total=eng+math+science;
   	   	    		break;
   	   	    	case 3:
   	   	    		cout<<"Enter maths marks : ";
   	   	    		cin>>m;
   	   	    		math=m;
   	   	    		total=eng+math+science;
   	   	    		break;
   	   	    	case 4:
   	   	    		cout<<"Enter science marks : ";
   	   	    		cin>>m;
   	   	    		science=m;
   	   	    		total=eng+math+science;
   	   	    		break;
   	   	    	default:
   	   	    		break;
				  }
			cout<<"Want to update anything else:(y/n)  ";
			cin>>ch;
		  }
	   
   	
   }
};
int main()
{
   student s,s1;
   fstream file;                     //create input/output stream
   int ch=1,c,r,p;
   char a;
   while(ch!=0){
   	c=1;
   	cout << "\nPlease choose your choice " << endl;
    cout << "\n1.Add\t2.View\t3.Delete   4.Update\t\t(Press 0 to exit)" << endl;
    cin>>ch;
    switch(ch){
    	case 1:
    		{
			 s.setData();
    		file.open("test.dat", ios :: in);   
    		c=1;
    		if(file){
    			while(!file.eof())
    		  {
    		 	file.read((char *)&s1, sizeof(s1));
    			if(s1.getroll()==s.getroll())
    			{
    				c=0;
    				cout<<"Student with Roll no.: "<<s.getroll()<<" already exists";             //error if rollno exists already
    				file.close();
    				break;
				}
			  }
		     file.close();			}
    		if(c==1)
    		{
    			file.open("test.dat", ios :: app);
    		file.write((char *)&s, sizeof(s));
    		file.close();
    		cout<<"Student added";
			}
    		break;
    	}
    	case 2:
    		{
    		file.open("test.dat", ios :: in); //file must exist
    		cout<<"a)All records \t b)Specific"<<endl;
    		cin>>a;
    		if(a=='a')
			{
				while(!file.eof())
				{
					file.read((char *)&s1, sizeof(s1));
					s1.displayData();
				}
				file.close();
				break;
			}
			else if(a=='b'){
				cout<<"Enter roll no.";
				cin>>r;
				while(!file.eof())
				{
					file.read((char *)&s1, sizeof(s1));
					if(r==s1.getroll())
					{ 
					    c=0;
						s1.displayData();
						break;
					}	
					
				}
				file.close();
				if(c==1)
				{
					cout<<"Given roll no doesn't exist";
				}
				break;
			}}
		case 3:
		   {
			cout<<"Enter the roll no.of the student to be deleted : ";
			cin>>r;
			file.open("test.dat",ios::in);         //test.txt must exist
			fstream file1;
		    file1.open("temp.dat",ios::out);
			while(!file.eof())
				{
					file.read((char *)&s1, sizeof(s1));
					if(r==s1.getroll())
					{ 
					    c=0;
					    cout<<"Record Deleted of the given roll no."<<endl;
					}	
					else
					{
						file1.write((char *)&s1,sizeof(s1));
					}
				}
				file.close();
				file1.close();
				if(c==1)
				{
					cout<<"Given roll no doesn't exist";
				}
				remove("test.dat");
				rename("temp.dat","test.dat");
				break;
			}
		case 4:
		    {
			cout<<"Enter the roll no.of the student to be updated : ";
			cin>>r;
			file.open("test.dat",ios::in|ios::app|ios::binary);         //test.txt must exist
			while(!file.eof())
				{
					p=file.tellg();
					file.read((char *)&s1, sizeof(s1));
					if(r==s1.getroll())
					{ 
					    c=0;
					    s1.update();
					    file.seekp(p);
					    file.write((char *)&s1,sizeof(s1));
					    cout<<"\nRecord updated of the given roll no."<<endl;
					    break;
					}	
				}
				file.close();
				if(c==1)
				{
					cout<<"Given roll no doesn't exist";
			    }
			break;
		}
    	default:
    		break; 		
	}
   }
    
 return 0;
   
}
