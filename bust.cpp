#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string.h>
using namespace std;


class passenger
{
	int seat;
	char gender;
	char name[10];
	char ph[13];
	int fare;
    public:
		
        void read_data();
        void show_data();
        void bookticket();
        void read_rec();
        void viewdetails();
        void cancellation();

};
int validate_ph(char ph[])
{
	int i=0;
    while(ph[i]!='\0')
    {
    	if(!isdigit(ph[i]))
    	{
    		return 1;
    		
		}
		i++;
	}
	if(strlen(ph)!=10)
	{
		return 1;
	}
	return 0;
}


void passenger::read_data()
{
    cout<<"\nEnter seat Number: ";
    cin>>seat;
    while(seat>29||seat<1)
    {
    	cout<<"\nEnter a valid seat number 0-29";
    	cin>>seat;
    	
	}
    cout<<"Enter gender: ";
    cin>>gender;
    while(gender!='m'&&gender!='f')
    {
    	cout<<"\nenter m/f";
    	cin>>gender;
	}
    cout<<"Enter Name: ";
    cin>>name;
    cout<<"Enter phone no: ";
    cin>>ph;
    while(validate_ph(ph))
    {
    	cout<<"\nenter a valid phone number";
    	cin>>ph;
	}
    cout<<endl;
}

void passenger::show_data()
{
    cout<<"\nseat Number: "<<seat<<endl;
    cout<<"gender: "<<gender<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"phone no:  "<<ph<<endl;
    cout<<"ticket fare:"<<fare<<endl;
    cout<<"-------------------------------"<<endl;
}

void passenger::bookticket()
{
	cout<<"\nRoutes available:\n\n1.chennai <-> madurai\n2.madurai<->bengaluru\n3.bengaluru<->chennai";
	int i,j;
	    int a[3][10];
	    for(i=0;i<3;i++)
	    {
	    	for(j=0;j<10;j++)
	    	{
	    		a[i][j]=i*10+j;
			}
		}
    	cout<<"\n\nEnter the following details\n\n";
        cout<<"FROM POINT\t:";
        char from[10];
        char to[10];
        cin>>from;
        cout<<"TO point\t:";
        cin>>to;
        if((strcmp(from,to)==0)||((strcmp(from,"chennai")!=0)&&(strcmp(from,"madurai")!=0)&&(strcmp(from,"bengaluru")!=0))||((strcmp("chennai",to)!=0)&&(strcmp("madurai",to)!=0)&&(strcmp("bengaluru",to)!=0)))
        {
        	cout<<"\nEnter a valid route!!\n";
        	return;
		}
	    cout<<"Date of Journey [dd/mm/yy]\t:";
        char date1[20];
        int date[20];
        cin>>date1;
        date[0]=date1[0]-'0';
        date[1]=date1[1]-'0';
        date[2]=date1[3]-'0';
        date[3]=date1[4]-'0';
        date[4]=date1[6]-'0';
        date[5]=date1[7]-'0';
        //cin>>date;
        if((date[0]*10+date[1]<1)||(date[0]*10+date[1]>30)||(date[2]*10+date[3]!=11)||(date[4]*10+date[5]!=17))
        {
        	cout<<"\nEnter valid date";
        	return;
		}
        char filen[20];
        filen[0]=from[0];
        filen[1]=from[1];
        filen[2]=to[0];
        filen[3]=to[1];
        filen[4]=date1[0];
        filen[5]=date1[1];
        filen[6]=date1[3];
        filen[7]=date1[4];
        filen[8]=date1[6];
        filen[9]=date1[7];
        filen[10]='.';
        filen[11]='t';
        filen[12]='x';
        filen[13]='t';
        filen[14]='\0';
        ifstream infile;
    infile.open(filen, ios::binary);
    if(infile)
    {
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            i=seat/10;
            j=seat%10;
            a[i][j]=gender;
        }
    }
}
    infile.close();
    cout<<"\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    cout<<"\n                 LAYOUT OF SEATS\n";
    cout<<" ---------------------------------------------------\n";
    for(i=0;i<3;i++)
    {
    	for(j=0;j<10;j++)
    	{
			if(i==0)
			{
			if(a[i][j]>29)
			cout<<" | "<<(char)a[i][j]<<" ";
			else
    		cout<<" | "<<a[i][j]<<" ";
		    }
		    else
		    {
				
			if(a[i][j]>29)
			cout<<" | "<<(char)a[i][j]<<" ";
			else
    		cout<<" | "<<a[i][j];
				}
		}
		cout<<" |\n";
	cout<<" ---------------------------------------------------\n";
		if(i==1)
		{cout<<"\n";
		cout<<" ---------------------------------------------------\n";
		}
		
	}
	cout<<"\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
        ofstream outfile;
        outfile.open(filen, ios::binary|ios::app);
        read_data();
        if(((strcmp(from,"chennai")==0)&&(strcmp(to,"madurai")==0))||((strcmp(from,"madurai")==0)&&(strcmp(to,"chennai")==0)))
        {
        	fare=250;
		  }  
		else if(((strcmp(from,"bengaluru")==0)&&(strcmp(to,"madurai")==0))||((strcmp(from,"madurai")==0)&&(strcmp(to,"bengaluru")==0)))
	    {
	    	fare=300;
		}
		else
		{
			fare=200;
		}
		
		i=seat/10;
        j=seat%10;
        if(a[i][j]>29)
        {
		cout<<"THE SEAT IS ALREADY BOOKED!!";
		outfile.close();
		return;
	    }
        outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
        outfile.close();
      cout<<"\n***********************************************************************";
      cout<<"\nTICKET HAS BEEN BOOKED";
      cout<<"\nYOUR TICKET DETAILS ARE\n";
      show_data();
}
void passenger::read_rec()
{
	cout<<"\nEnter the following details\n\n";
        cout<<"FROM POINT\t:";
        char from[10];
        char to[10];
        cin>>from;
        cout<<"TO point\t:";
        cin>>to;
        if((strcmp(from,to)==0)||((strcmp(from,"chennai")!=0)&&(strcmp(from,"madurai")!=0)&&(strcmp(from,"bengaluru")!=0))||((strcmp("chennai",to)!=0)&&(strcmp("madurai",to)!=0)&&(strcmp("bengaluru",to)!=0)))
        {
        	cout<<"\nEnter a valid route!!!";
        	return;
		}
        cout<<"Date of journey [dd/mm/yy]\t:";
        char date1[20];
        int date[20];
        cin>>date1;
        date[0]=date1[0]-'0';
        date[1]=date1[1]-'0';
        date[2]=date1[3]-'0';
        date[3]=date1[4]-'0';
        date[4]=date1[6]-'0';
        date[5]=date1[7]-'0';
        if((date[0]*10+date[1]<1)||(date[0]*10+date[1]>30)||(date[2]*10+date[3]!=11)||(date[4]*10+date[5]!=17))
        {
        	cout<<"\nEnter valid date!!!";
        	return;
		}
        char filen[20];
        filen[0]=from[0];
        filen[1]=from[1];
        filen[2]=to[0];
        filen[3]=to[1];
        filen[4]=date1[0];
        filen[5]=date1[1];
        filen[6]=date1[3];
        filen[7]=date1[4];
        filen[8]=date1[6];
        filen[9]=date1[7];
        filen[10]='.';
        filen[11]='t';
        filen[12]='x';
        filen[13]='t';
        filen[14]='\0';
    ifstream infile;
    infile.open(filen, ios::binary);
    if(!infile)
    {
        cout<<"\n\nError in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****************TICKET DETAILS*******************"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            show_data();
        }
    }
    infile.close();
}
void passenger::cancellation()
{
	cout<<"\nEnter the following details\n\n";
        cout<<"FROM POINT\t:";
        char from[10];
        char to[10];
        cin>>from;
        cout<<"TO point\t:";
        cin>>to;
        if((strcmp(from,to)==0)||((strcmp(from,"chennai")!=0)&&(strcmp(from,"madurai")!=0)&&(strcmp(from,"bengaluru")!=0))||((strcmp("chennai",to)!=0)&&(strcmp("madurai",to)!=0)&&(strcmp("bengaluru",to)!=0)))
        {
        	cout<<"\nEnter a valid route!!!";
        	return;
		}
        cout<<"Date of journey [dd/mm/yy]\t:";
        char date1[20];
        int date[20];
        cin>>date1;
        date[0]=date1[0]-'0';
        date[1]=date1[1]-'0';
        date[2]=date1[3]-'0';
        date[3]=date1[4]-'0';
        date[4]=date1[6]-'0';
        date[5]=date1[7]-'0';
        if((date[0]*10+date[1]<1)||(date[0]*10+date[1]>30)||(date[2]*10+date[3]!=11)||(date[4]*10+date[5]!=17))
        {
        	cout<<"\nEnter valid date";
        	return;
		}
        char filen[20];
        filen[0]=from[0];
        filen[1]=from[1];
        filen[2]=to[0];
        filen[3]=to[1];
        filen[4]=date1[0];
        filen[5]=date1[1];
        filen[6]=date1[3];
        filen[7]=date1[4];
        filen[8]=date1[6];
        filen[9]=date1[7];
        filen[10]='.';
        filen[11]='t';
        filen[12]='x';
        filen[13]='t';
        filen[14]='\0';
    int n;
    ifstream infile;
    infile.open(filen, ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count=0;
    cout<<"\n Enter seat Number to CANCEL: ";
    cin>>n;
    if(n>29||n<1)
    {
    	cout<<"\nEnter a valid seat number 0-29";
    	return;
    	
	}
    fstream tmpfile;
    tmpfile.open("tmpfile.txt", ios::out|ios::binary);
    infile.seekg(0);
    while(!infile.eof())
    {
		if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
		{
		if(n==seat)
		{
			count++;
			continue;}
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
    }
    if(count==0)
    cout<<"\nTICKET HAD NOT BEEN BOOKED!!!\n";
    infile.close();
    tmpfile.close();
    remove(filen);
    rename("tmpfile.txt",filen);

   cout<<"\n----------YOUR TICKET HAS BEEN CANCELLED!!!!---------------\n";
}
void passenger::viewdetails()
{
	cout<<"\nEnter the following details\n\n";
        cout<<"FROM POINT\t:";
        char from[10];
        char to[10];
        cin>>from;
        cout<<"TO point\t:";
        cin>>to;
        if((strcmp(from,to)==0)||((strcmp(from,"chennai")!=0)&&(strcmp(from,"madurai")!=0)&&(strcmp(from,"bengaluru")!=0))||((strcmp("chennai",to)!=0)&&(strcmp("madurai",to)!=0)&&(strcmp("bengaluru",to)!=0)))
        {
        	cout<<"\nEnter a valid route\n";
        	return;
		}
        cout<<"Date of journey [dd/mm/yy]\t:";
        char date1[20];
        int date[20];
        cin>>date1;
        date[0]=date1[0]-'0';
        date[1]=date1[1]-'0';
        date[2]=date1[3]-'0';
        date[3]=date1[4]-'0';
        date[4]=date1[6]-'0';
        date[5]=date1[7]-'0';
        //cin>>date;
        if((date[0]*10+date[1]<1)||(date[0]*10+date[1]>30)||(date[2]*10+date[3]!=11)||(date[4]*10+date[5]!=17))
        {
        	cout<<"\nEnter valid date\n";
        	return;
		}
        char filen[20];
        filen[0]=from[0];
        filen[1]=from[1];
        filen[2]=to[0];
        filen[3]=to[1];
        filen[4]=date1[0];
        filen[5]=date1[1];
        filen[6]=date1[3];
        filen[7]=date1[4];
        filen[8]=date1[6];
        filen[9]=date1[7];
        filen[10]='.';
        filen[11]='t';
        filen[12]='x';
        filen[13]='t';
        filen[14]='\0';
    int n;
    ifstream infile;
    infile.open(filen, ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    int count=0;
    cout<<"\n Enter seat Number to view: ";
    cin>>n;
    
    if(n>29||n<1)
    {
    	cout<<"\nEnter a valid seat number 0-29";
    	return;
    	
	}
    infile.seekg(0);
    while(!infile.eof())
    {
		if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
		{
		if(n==seat)
		{
			count++;
			show_data();
			break;}
	}
    }
    if(count==0)
    cout<<"TICKET HAS BEEN BOOKED!!!";
    infile.close();

}

int main()
{
    passenger p;
    while(1)
    {
	cout<<"\n-----------------------------BUS TICKET RESERVATION SYSTEM------------------------------------\n";
	cout<<"\n\nEnter the choice\n1.Ticket booking\n2.Cancellation of ticket\n3.View ticket details\n4.Read_rec\n5.Exit\n";
	int ch;
	cin>>ch;
	switch(ch)
	{
		case 1:
			p.bookticket();
			break;
		case 2:
			p.cancellation();
            break;
		case 3:
			p.viewdetails();
			break;
		case 4:
			p.read_rec();
			break;
		case 5:
			exit(0);
			break;
		default:
			cout<<"Enter valid choice";
			break;
			}
	}
			return 0;
}
