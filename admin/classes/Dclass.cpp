#include <bits/stdc++.h>
#include "Pclass.cpp"
using namespace std;

class doctor:virtual public patient{
private:
	//removeFromQueue(LDAP);
public:
	int LDAP;
	char name[15];
	char speciality[15];
	bool available;
	int patientQ[15];
	doctor(){
		for (int i = 0; i < 15; ++i)
			patientQ[i]=0;
	};
	doctor(int x){
		LDAP=x;
		for (int i = 0; i < 15; ++i)
			patientQ[i]=0;	
	}

	void updateRecords(patient* p){
		ifstream fin;
		ofstream fout;
		patient* p1;
		fin.open("../records/records.txt");
		fout.open("../records/tempFiles/tempRecords.txt");
		while(fin.read(reinterpret_cast<char*>(p1), sizeof(patient)))
			if(p1->LDAP==p->LDAP)
				fout.write(reinterpret_cast<char*>(p), sizeof(patient));
			else
				fout.write(reinterpret_cast<char*>(p1), sizeof(patient));
		fin.close();fout.close();
		fin.open("../records/tempFiles/tempRecords.txt");
		fout.open("../records/records.txt");
		while(fin.read(reinterpret_cast<char*>(p1), sizeof(patient)))
			fout.write(reinterpret_cast<char*>(p1), sizeof(patient));
		fin.close();fout.close();
		return;				
	}
	void notifyAdmin(int x){
		struct leave{
			int patientLDAP,startingDate,startingMonth,endDate,endMonth;
		}s;
		s.patientLDAP=x;
		cout<<"Starting date (DD,MM): "<<endl;
		//cin>>s.startingDate>>s.startingMonth;
		cout<<"End date (DD,MM): "<<endl;
		//cin>>s.endDate>>s.endMonth;
		ofstream fout;
		fout.open("admin/records/leave.txt",ios_base::app);
		//string s2="reinterpret_cast<char*>(&s), sizeof(leave)";
		cout<<fout.write(reinterpret_cast<char*>(&s),sizeof(s));
		fout.close();
		ifstream fin;
		fin.open("admin/records/leave.txt");
		cout<<"leave here----> "<<fin.read(reinterpret_cast<char*>(&s), sizeof(leave));
		fin.close();
		// while()
		// 	cout<<s.patientLDAP<<" ";
		// cout<<endl;
	}

	int nextPatient(){
		int next=patientQ[0];
		return next;
	}

	void onlineDiscussion(int p){
		cout<<"Online Discussion"<<endl;
		return;
	}	
	void treatPatients(){
		int next=nextPatient();
		patient* p=new patient(next);
		if(next==0){
			cout<<"No patients in the queue"<<endl;
			return;
		}
		cout<<endl<<"Next Patient: "<<'P'<<p->LDAP<<endl;
		

		p=writePrescription(p);
		cout<<"Medical Leave Required?(1/0)"<<endl;
		bool leave;
		cin>>leave;
		if(leave)
			notifyAdmin(p->LDAP);
		updateRecords(p);
		return;
	}
	friend patient* writePrescription(patient* p);   //  IN LOGIN.CPP
	
};
