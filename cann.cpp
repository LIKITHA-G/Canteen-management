#include<iostream>
#include<fstream>
#include<windows.h>
#include<dos.h>
#include<stdio.h>
#include<cstdlib>
#include<string>
#include<conio.h>


using namespace std;

COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
class store{
	public:
        
		void storepage()
        {
            storepageswitch();
        }

    


int can_flag=0,no=0;
char can_ind[5];

struct canteen{
	char ind[5],
	     item_id[5],
		 item_name[20],
	     cost[20],
	     quantity[20],
		 rating[5];
}can[20];

struct secind{
	char item_name[20],
	    item_id[5],
	    ind[5];
}sec[20],found[20];

struct index{
	char item_id[20],ind[20];
}in[20],temp;

void sort_index()
{
	int i,j;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(in[j].item_id,in[j+1].item_id)>0)
	{
		temp =in[j];
		in[j]=in[j+1];
		in[j+1]=temp;
	}
}

void sort_secind()
{
	int i,j;
	secind temp;
	for(i=0;i<no-1;i++)
	for(j=0;j<no-i-1;j++)
	if(strcmp(sec[j].item_name,sec[j+1].item_name)>0)
	{
		temp =sec[j];
		sec[j]=sec[j+1];
		sec[j+1]=temp;
	}
	else if(strcmp(sec[j].item_name,sec[j+1].item_name)==0)
	{
	if(strcmp(sec[j].item_id,sec[j+1].item_id)>0)
	{
		temp =sec[j];
		sec[j]=sec[j+1];
		sec[j+1]=temp;
	}
}
}

void ret_rec(char *ind)
{
	int flag=0;
	for(int i=0;i<no;i++)
	{
		if(strcmp(can[i].ind,ind)==0)
		{
			strcpy(can_ind,ind);
			can_flag=1;
			cout<<"Item found\n";
			cout<<can[i].item_id<<"|"<<can[i].item_name<<"|"<<can[i].cost<<"|"<<can[i].quantity<<"|"<<can[i].rating<<"\n";
			flag=1;
		}
	}
	if(!flag)
	{
		cout<<"Item search failed\n";
	}
}

void search_index(char *item_id)
{
	int flag=0;
for(int i=0;i<no;i++)
	{
		if(strcmp(in[i].item_id,item_id)==0)
		{	
		ret_rec(in[i].ind);
		flag=1;
}
}
if(!flag)
	{
		cout<<"Index search failed\n";
	}
}

void search(char *it_name)
{
	char it_id[20];
	int flag1=0;
	int k=0,i;
	for(i=0;i<no;i++)
	{
	if(strcmp(sec[i].item_name,it_name)==0)
	{
		strcpy(found[k].item_id,sec[i].item_id);
		strcpy(found[k].item_name,sec[i].item_name);
		strcpy(found[k].ind,sec[i].ind);
		flag1=1;
		k++;
	}
	}
	if(!flag1)
	{
		cout<<"sec ind search failed\n";
		return;
	}
	cout<<"\n Records matching are:";
	for(i=0;i<k;i++)
	cout<<"\n"<<found[i].item_name<<" "<<found[i].item_id;
	cout<<"\n Choose an Item id";
	cin>>it_id;
	flag1=0;
	for(i=0;i<k;i++)
	if(strcmp(found[i].item_id,it_id)==0)
	{
		search_index(it_id);
		flag1=1;
	}
	if(!flag1)
	{
		cout<<"wrong item id search failed\n";
	}
	}



int search_item(char *it_id,int j)
{
	int flag=0;
for(int i=0;i<j;i++)
	{
		if(strcmp(can[i].item_id,it_id)==0)
		{	
		flag=1;
		break;
        }
}
if(flag)
return 1;
else
return -1;
}

void del(char *it_name)
{
	can_flag=0;
	int fr=0;
	search(it_name);
	if(!can_flag)
	{
		cout<<"Deletion failed\n";
		return;
	}
	for(int i=0;i<no;i++)
	{
	if(strcmp(can[i].ind,can_ind)==0)
	{
		fr=i;
		break;
	}
}
	for(int i=fr;i<no-1;i++)
	{
	can[i]=can[i+1];
	char str[3];
	sprintf(str,"%d",i);
	strcpy(can[i].ind,str);
	}
	no--;
	
	fstream f1,f2,f3;
	f1.open("canteen1.txt",ios::out);
	f2.open("index.txt",ios::out);
	f3.open("secind.txt",ios::out);
	for(int i=0;i<no;i++)
	{
		strcpy(sec[i].item_name,can[i].item_name);
		strcpy(sec[i].item_id,can[i].item_id);
		strcpy(in[i].item_id,can[i].item_id);
		strcpy(sec[i].ind,can[i].ind);
		strcpy(in[i].ind,can[i].ind);
	}
	sort_index();
	sort_secind();
	for(int i=0;i<no;i++)
	{
	 f1<<can[i].ind<<"|"<<can[i].item_id<<"|"<<can[i].item_name<<"|"<<can[i].cost<<"|"<<can[i].quantity<<"|"<<can[i].rating<<"\n";
	 f2<<in[i].item_id<<"|"<<in[i].ind<<"\n";
	 f3<<sec[i].item_name<<"|"<<sec[i].item_id<<"|"<<sec[i].ind<<"\n";
	}
	f1.close();
	f2.close();
	f3.close();
	cout<<"Deletion successful";
	}
	
	void orderfood()
	{
		system("CLS");
    gotoxy(40,1);cout<<"\nJSSATE CANTEEN";
    gotoxy(40,2);
                	int choice,i,flag1,flag;
	fstream file1,file2,file3;
	char ind[5],
	     it_id[20],
	     it_name[20],
	     item_id[5],
		 item_name[20],
	     cost[20],
	     quantity[20],
		 rating[5];
				file3.open("index.txt",ios::out);
				file1.open("canteen1.txt",ios::app|ios::out);
				file2.open("secind.txt",ios::out);
				if(!file1)
				{
					cout<<"file couldnt be added";
					exit(0);
				}
				int n;
				cout<<"\nEnter no of food items\n";
				cin>>n;
				for(int i=no;i<no+n;i++)
				{
				label: cout<<"\nEnter "<<i+1<<" item name:\n";
					cout<<"Enter Item id:"; cin>>can[i].item_id;
					cout<<"Enter Item Name:"; cin>>can[i].item_name;
					cout<<"Enter Cost:"; cin>>can[i].cost;
					cout<<"Enter Quantity:"; cin>>can[i].quantity;
					cout<<"Enter rating:"; cin>>can[i].rating;
					int q=search_item(can[i].item_id,i);
					if(q==1)
					{
						cout<<"Duplicate entry, Enter again\n";
						goto label;
					}
					file1<<i<<"|"<<can[i].item_id<<"|"<<can[i].item_name<<"|"<<can[i].cost<<"|"<<can[i].quantity<<"|"<<can[i].rating<<"\n";
				}
				file1.close();
				no=no+n;
				file1.open("canteen1.txt",ios::in);
				for(int i=0;i<no;i++)
				{
					file1.getline(ind,5,'|');
					file1.getline(item_id,5,'|');
					file1.getline(item_name,20,'|');
					file1.getline(cost,20,'|');
					file1.getline(quantity,20,'|');
					file1.getline(rating,5,'\n');
					strcpy(can[i].ind,ind);
					strcpy(sec[i].ind,ind);
					strcpy(in[i].ind,ind);
					strcpy(sec[i].item_name,item_name);
					strcpy(sec[i].item_id,item_id);
					strcpy(in[i].item_id,item_id);
				}
				sort_index();
				sort_secind();
				cout<<"\nThe sorted secondary index contents are:\n";
				for(i=0;i<no;i++)
				 cout<<sec[i].item_name<<" "<<sec[i].item_id<<" "<<sec[i].ind<<endl;
				 cout<<"\nThe sorted index contents are:\n";
				for(i=0;i<no;i++)
				 cout<<in[i].item_id<<" "<<in[i].ind<<endl;			 
				for(int i=0;i<no;i++)
				 file2<<sec[i].item_name<<"|"<<sec[i].item_id<<"|"<<sec[i].ind<<"\n";
				for(int i=0;i<no;i++)
				 file3<<in[i].item_id<<"|"<<in[i].ind<<"\n";			 
				
				file1.close();
				file2.close();
				file3.close();
				cout<<endl<<"     PRESS ANY KEY TO CONTINUE";
    cout<<"     ";getch();
    storepage();
			}
	
	void bill()
	{
	system("CLS");
    gotoxy(40,1);cout<<"JSSATE CANTEEN";
    gotoxy(40,2);cout<<"----------------";
	    int choice,i,flag1,flag;
     	fstream file1,file2,file3;
	    char ind[5],
	     it_id[20],
	     it_name[20],
	     item_id[5],
		 item_name[20],
	     cost[20],
	     quantity[20],
		 rating[5];
			fstream f1;
			f1.open("canteen1.txt",ios::in);
			if(!f1)
			{
				cout<<"File not found";
				exit(0);
			}
			cout<<"\n  ID    NAME   COST  QUANTITY  RATINGS\t\n\n";
			i=0;
			while(i!=no)
			{
					f1.getline(ind,5,'|');
					f1.getline(item_id,5,'|');
					f1.getline(item_name,20,'|');
					f1.getline(cost,20,'|');
					f1.getline(quantity,20,'|');
					f1.getline(rating,5,'\n');
			cout<<"\n"<<item_id<<"\t"<<item_name<<"\t"<<cost<<"\t"<<quantity<<"\t"<<rating<<"\t\n";
			i++;
	    	}
			int totalcost=0;
            cout<<"\nTotal number of food items ordered :"<<i<<"\n";
			for(int f=0;f<i;f++)
			{
			 totalcost = totalcost+(cost[f]*quantity[f]);
			}
			printf("\nYou will have to pay Rs.70\n",totalcost);
			cout<<"Thank you, JSSATE\n";
			
			f1.close();
			cout<<endl<<"     PRESS ANY KEY TO CONTINUE";
    cout<<"     ";getch();
    storepage();
		}
	

void foodsearch()
{
 system("CLS");
    gotoxy(40,1);cout<<"JSSATE CANTEEN\n";
    gotoxy(40,2);
    char it_name[20];
				cout<<"\nEnter Item name to be searched\n";
				cin>>it_name;
				search(it_name);
				cout<<endl<<"     PRESS ANY KEY TO CONTINUE";
    cout<<"     ";getch();
    storepage();
}

void deletefood()
{
	system("CLS");
    gotoxy(40,1);cout<<"JSSATE CANTEEN";
    gotoxy(40,2);
     char it_name[20];
				cout<<"\nEnter Item name to be deleted\n";
				cin>>it_name;
				del(it_name);
					cout<<endl<<"     PRESS ANY KEY TO CONTINUE";
    cout<<"     ";getch();
    storepage();
}
    
storepageswitch()
{
system("CLS");
    gotoxy(40,1);cout<<"JSSATE CANTEEN";
    gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
		int choice;
		cout<<"\n\nJSSATE CANTEEN MANAGEMENT\n";
		cout<<"\n1.Order Food\n2.Search Item\n3.Delete Item\n4.Generate Bill\n5.Exit\n";
		cout<<"Enter your choice\n";
		cin>>choice;
		switch(choice)
		{
		case 1:
			orderfood();
			break;
			storepageswitch();
		case 2:{
			    foodsearch();
				break;
				
			}
		case 3:{
			    deletefood();
				break;
		}
		case 4:{
			 bill();
			break;
		}
	case 5:{
		cout<<"JSSATE CANTEEN \n";
		cout<<"Thank You\n";
		break;
	}
	default:
	cout<<"Invalid Choice\n";
	 cout<<"     ENTER CHOICE"<<endl;
                cout<<"     ";cin>>choice;
	break;		
}
}
};



class employee
{
    public:
        int ch,age;
        char name[50];
        long int sal;
        void addemp();
        void displayemp();
        void removeemp();
        void editemp();
        void emppageswitch();
        void emppage()
        {
            system("CLS");
            gotoxy(40,1);cout<<"JSSATE CANTEEN";
            gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
            cout<<"     1. DISPLAY ALL EMPLOYEE DETAILS"<<endl;
            cout<<"     2. ADD NEW EMPLOYEE DETAILS"<<endl;
            cout<<"     3. REMOVE OLD EMPLOYEE DETAILS"<<endl;
            cout<<"     4. EXIT"<<endl<<endl;
            cout<<"     ENTER CHOICE"<<endl;
            cout<<"     ";cin>>ch;
            emppageswitch();
        }
};
void employee::emppageswitch()
{
    while(ch!=1||ch!=2||ch!=3||ch!=4)
    {
        switch(ch)
        {
            case 1:
                displayemp();
                break;
            case 2:
                addemp();
                break;
            case 3:
                removeemp();
                break;
            case 4:
                exit(0);
          		break;
            default:
                cout<<endl<<"     INVALID CHOICE"<<endl;
                cout<<"     ENTER CHOICE"<<endl;
                cout<<"     ";cin>>ch;
                break;
        }
    }
}
void employee::addemp()
{
    system("CLS");
    gotoxy(40,1);cout<<"JSSATE CANTEEN";
    gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
    ofstream newemployee("EMPLOYEE.txt",ios::app);
    cout<<"     ENTER NAME OF EMPLOYEE"<<endl;
    cout<<"     ";cin>>name;
    cin.sync();
    cout<<"     ENTER AGE OF EMPLOYEE"<<endl;
    cout<<"     ";cin>>age;
    cout<<"     ENTER SALARY OF EMPLOYEE"<<endl;
    cout<<"     ";cin>>sal;
    newemployee<<name<<' '<<age<<' '<<sal<<endl;
    newemployee.close();
    cout<<endl<<"     EMPLOYEE ADDED"<<endl;
    cout<<endl<<"     PRESS ANY KEY TO CONTINUE";
    cout<<"     ";getch();
    emppage();
}
void employee::displayemp()
{
    system("CLS");
    gotoxy(40,1);cout<<"JSSATE CANTEEN";
    gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
    ifstream employee("EMPLOYEE.txt");
    cout<<"     EMPLOYEE - AGE - SALARY"<<endl;
    cout<<"     -----------------------"<<endl;
    while (employee>>name>>age>>sal)
    {
        cout<<"     "<<name<<" - "<<age<<" - "<<sal<<endl ;
    }
    employee.close();
    cout<<endl<<"     PRESS ANY KEY TO CONTINUE"<<endl;
    cout<<"     ";getch();
    emppage();
}
void employee::removeemp()
{
    system("CLS");
    gotoxy(40,1);cout<<"JSSATE CANTEEN";
    gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
    char tname[50];
    ifstream emp1("EMPLOYEE.txt");
    ofstream emp2("temp.txt");
    cout<<"     ENTER THE NAME OF EMPLOYEE WISH TO REMOVE"<<endl;
    cout<<"     ";cin>>tname;
    while(emp1>>name>>age>>sal)
    {
        if(strcmp(name,tname)!=0)
        {
            emp2<<name<<' '<<age<<' '<<sal<<endl;
        }
    }
    emp1.close();
    emp2.close();
    remove("EMPLOYEE.txt");
    rename("temp.txt","EMPLOYEE.txt");
    cout<<endl<<"     EMPLOYEE REMOVED"<<endl;
    cout<<endl<<"     PRESS ANY KEY TO CONTINUE"<<endl;
    cout<<"     ";getch();
    emppage();
}
class login
{
  public:
      string pass="";
      int ch;
      char c;
      void loginpageswitch();
      void homepageswitch();
      void employeelogin();
      void ownerlogin();
      void emp();
      void own();
      void homepage()
      {
          system("CLS");
          gotoxy(40,1);cout<<"WELCOME TO JSSATE CANTEEN";
          gotoxy(40,2);cout<<"----------------------------"<<endl<<endl;
          cout<<"     1. LOGIN"<<endl;
          cout<<"     2. EXIT"<<endl<<endl;
          cout<<"     ENTER CHOICE"<<endl;
          cout<<"     ";cin>>ch;
          homepageswitch();
      }
      void loginpage()
      {
      	loginpage:;
          system("CLS");
          gotoxy(40,1);cout<<"JSSATE CANTEEN";
          gotoxy(40,2);cout<<"-----------------"<<endl<<endl;
          cout<<"     1. OWNER LOGIN"<<endl;
          cout<<"     2. EMPLOYEE LOGIN"<<endl;
          cout<<"     3. EXIT"<<endl<<endl;
          cout<<"     ENTER CHOICE"<<endl;
          cout<<"     ";cin>>ch;
          loginpageswitch();
      }
};
void login::homepageswitch()
{
    while(ch!=1||ch!=2)
    {
        switch(ch)
        {
        case 1:
            loginpage();
            break;
        case 2:
            exit(0);
            break;
        default:
            cout<<endl<<"     INVALID CHOICE"<<endl;
            cout<<"     ENTER CHOICE"<<endl;
            cout<<"     ";cin>>ch;
        }
    }
}
void login::loginpageswitch()
{
    while(ch!=1||ch!=2||ch!=3)
    {
        switch(ch)
        {
            case 1:
                ownerlogin();
                break;
            case 2:
                employeelogin();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout<<endl<<"     INVALID CHOICE"<<endl;
                cout<<"     ENTER CHOICE"<<endl;
                cout<<"     ";cin>>ch;
        }
    }
}
void login::ownerlogin()
{
    while(pass!="OWN")
    {
        pass="";
        cout<<endl<<"     ENTER OWNER PASSWORD"<<endl;
        cout<<"     ";c=_getch();
        while(c!=13)
        {
            pass.push_back(c);
            cout<<"*";
            c=getch();
        }
        if(pass=="OWN")
         {
             cout<<endl<<"     OWNER ACCESS GRANTED"<<endl;
             cout<<endl<<"     PRESS ANY KEY TO CONTINUE"<<endl;
             cout<<"     ";getch();
             own();
         }
        else
        {
            cout<<endl<<"     INVALID PASSWORD"<<endl;
        }
    }
}
void login::employeelogin()
{
    while(pass!="EMP")
    {
        pass="";
        cout<<"     ENTER EMPLOYEE PASSWORD"<<endl;
        cout<<"     ";c=_getch();
        while(c!=13)
        {
            pass.push_back(c);
            cout<<"*";
            c=getch();
        }
        if(pass=="EMP")
        {
            cout<<endl<<"     EMPLOYEE ACCESS GRANTED"<<endl;
            cout<<endl<<"     PRESS ANY KEY TO CONTINUE"<<endl;
            cout<<"     ";getch();
            emp();
        }
        else
        {
            cout<<endl<<"     INVALID PASSSWORD"<<endl;
        }
    }
}
void login::emp()
{
    store s;
    s.storepage();
}
void login::own()
{
    employee e;
    e.emppage();
}

void empjump()
{
    employee e;
    e.emppage();
}
int main()
{
    system("title CANTEEN MANAGEMENT SYSYTEM");
    system("color 71");
    login l;
    l.homepage();
    return 0;
}
