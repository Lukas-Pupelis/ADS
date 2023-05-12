/*
VIP bank. We have a task to research two queue forming processes for the bank: 
With a distinct VIP queue and VIP cashiers.
Or a common queue for both ordinary and VIP clients, but VIP clients
have a priority.
Data file needs to be named "data.txt"
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <list>
using namespace std;

const unsigned int MAX_T = 500;
float prastovos1 = 0;
float virsvalandziai1 = 0;

float prastovos2 = 0;
float virsvalandziai2 = 0;
int virsminutes1 = 0;
int virsminutes2 = 0;

void readFromFile(string filename, ofstream &out, int &papTikimybe, int &vipTikimybe, int &kasSkaicius, int &vipKasSkaicius, int &papLaikas, int &vipLaikas, int &dienosIlgis, float &valAtlyginimas);   
void bendraEile(ofstream &out, int papTikimybe, int vipTikimybe, int kasSkaicius, int vipKasSkaicius, int papLaikas, int vipLaikas, int dienosIlgis, float valAtlyginimas);
void atskirosEiles(ofstream &out, int papTikimybe, int vipTikimybe, int kasSkaicius, int vipKasSkaicius, int papLaikas, int vipLaikas, int dienosIlgis, float valAtlyginimas); 

int main()
{
	int papTikimybe, vipTikimybe, kasSkaicius, vipKasSkaicius, papLaikas, vipLaikas, dienosIlgis; 
	float valAtlyginimas;
	
	ofstream out("protokolas.txt", ios::trunc);
	
	system("cls");
	cout << "Uzduotis - VIP bankas (ADT: eile, prioritetine eile)."<< endl;
	cout << "Programos tikslas istirti, kuris eiliu organizavimo procesas yra geresnis: su atskira VIP eile ir VIP kasininkais ar" << endl;
	cout << "bendra eile ir bendrais kasininkais, bet VIP klientai yra aptarnaujami be eiles." << endl << endl;
	cout << "Pradiniai duomenys:" << endl;
	
	out << "Uzduotis - VIP bankas (ADT: eile, prioritetine eile)."<< endl;
	out << "Programos tikslas istirti, kuris eiliu organizavimo procesas yra geresnis: su atskira VIP eile ir VIP kasininkais ar" << endl;
	out << "bendra eile ir bendrais kasininkais, bet VIP klientai yra aptarnaujami be eiles." << endl << endl;
	out << "PIRMA DALIS. Duomenys" << endl << endl;
	
	readFromFile("data.txt", out, papTikimybe, vipTikimybe, kasSkaicius, vipKasSkaicius, papLaikas, vipLaikas, dienosIlgis, valAtlyginimas);
	
	out << endl;
	out << "ANTRA DALIS. Vykdymas." << endl << endl;
	out << "Procesas1: bendra eile pas tuos pacius kasininkus, VIP turi prioriteta." << endl;
	
	bendraEile(out, papTikimybe, vipTikimybe, kasSkaicius, vipKasSkaicius, papLaikas, vipLaikas, dienosIlgis, valAtlyginimas);
	
	out << "Procesas2: atskiros VIP ir paprastu klientu eiles pas atskirus kasininkus." << endl << endl;
	atskirosEiles(out, papTikimybe, vipTikimybe, kasSkaicius, vipKasSkaicius, papLaikas, vipLaikas, dienosIlgis, valAtlyginimas);
	
	out << endl;
	out << "TRECIA DALIS. Rezultatai." << endl;
	cout << endl;
	cout << "Rezultatai:" << endl;
	
	out << "1) Proceso1 prastovu ir virsvalandziu suma: " << fixed << setprecision(2) << (prastovos1+virsvalandziai1) << " eur." << endl;
	cout << "Proceso1 prastovu ir virsvalandziu suma: " << fixed << setprecision(2) << (prastovos1+virsvalandziai1) << " eur." << endl;
	
	out << "2) Proceso2 prastovu ir virsvalandziu suma: " << fixed << setprecision(2) << (prastovos2+virsvalandziai2) << " eur." << endl;
	cout << "Proceso2 prastovu ir virsvalandziu suma: " << fixed << setprecision(2) << (prastovos2+virsvalandziai2) << " eur." << endl;
	
	if((prastovos1+virsvalandziai1) < (prastovos2+virsvalandziai2))
	{
		out << "3) Bankui tikslingesnis procesas1." << endl;
		cout << "Bankui tikslingesnis procesas1." << endl;
	}
	else if((prastovos1+virsvalandziai1) > (prastovos2+virsvalandziai2))
	{
		out << "3) Bankui tikslingesnis procesas2." << endl;
		cout << "Bankui tikslingesnis procesas2." << endl;
	}
	return 0;
}

void readFromFile(string filename, ofstream &out, int &papTikimybe, int &vipTikimybe, int &kasSkaicius, int &vipKasSkaicius, int &papLaikas, int &vipLaikas, int &dienosIlgis, float &valAtlyginimas)
{
	ifstream in(filename);
	
		if(!in)
		{
			cout << "Failo " << "''data.txt'' " << " neimanoma atidaryti" << endl;
			out << endl << "TRECIA DALIS. Rezultatai" << endl;
			out << "  1) Programa sekmingai nebaige darbo" << endl;
			cout << "Uzdaroma programa..." << endl;
			exit(0);
		}
		
	string tmp;
	
	in >> papTikimybe;
	cout << "Paprasto kliento atejimo tikimybe: " << papTikimybe << " %" << endl;
	out << "Paprasto kliento atejimo tikimybe: " << papTikimybe << " %" << endl; 
	getline(in, tmp);
	
	in >> vipTikimybe;	
	cout << "VIP kliento atejimo tikimybe: " << vipTikimybe << " %" << endl;
	out << "VIP kliento atejimo tikimybe: " << vipTikimybe << " %" << endl; 
	getline(in, tmp);
	
	in >> kasSkaicius;
	cout << "Paprastu kasininku skaicius: " << kasSkaicius << endl;
	out << "Paprastu kasininku skaicius: " << kasSkaicius << endl; 
	getline(in, tmp);
	
	in >> vipKasSkaicius;
	cout << "VIP kasininku skaicius: " << vipKasSkaicius << endl;
	out << "VIP kasininku skaicius: " << vipKasSkaicius << endl; 
	getline(in, tmp);
	
	in >> papLaikas;
	cout << "Paprastu klientu aptarnavimo laikas: " << papLaikas << " min." << endl;
	out << "Paprastu klientu aptarnavimo laikas: " << papLaikas << " min." << endl; 
	getline(in, tmp);
	
	in >> vipLaikas;
	cout << "VIP klientu aptarnavimo laikas: " << vipLaikas << " min." << endl;
	out << "VIP klientu aptarnavimo laikas: " << vipLaikas << " min." << endl; 
	getline(in, tmp);
	
	in >> dienosIlgis;
	cout << "Darbo dienos ilgis: " << dienosIlgis << " val." << endl;
	out << "Darbo dienos ilgis: " << dienosIlgis << " val." << endl; 
	getline(in, tmp);
	
	in >> valAtlyginimas;
	cout << "Valandinis atlyginimas: " <<  fixed << setprecision(2) << valAtlyginimas << " eur." << endl;
	out << "Valandinis atlyginimas: " <<  fixed << setprecision(2) << valAtlyginimas << " eur." << endl; 
	getline(in, tmp);
	
	in.close();
}	

void bendraEile(ofstream &out, int papTikimybe, int vipTikimybe, int kasSkaicius, int vipKasSkaicius, int papLaikas, int vipLaikas, int dienosIlgis, float valAtlyginimas)
{
	queue<int> vip;
	queue<int> pap;
	queue<int> vipapt;
	queue<int> papapt;

	int bendrasKasSkaicius;
	srand(0);
	bool yraKasininku = true;
	bool atejoVip = false;
	bool atejoPap = false;
	
	float prastovos = 0;
	float virsvalandziai = 0;
	
	bendrasKasSkaicius = (kasSkaicius + vipKasSkaicius);
	int laikasMin = dienosIlgis * 60;
	float minAtlyginimas = (valAtlyginimas / 60);
	
	int SkaitliukasVip[bendrasKasSkaicius] = {0};
	int SkaitliukasPap[bendrasKasSkaicius] = {0};
	int kasSkaitliukas[bendrasKasSkaicius] = {0};
	
	int vipKlientoNum = 0;
	int papKlientoNum = 0;
	
	int papaptEile[laikasMin] = {0};
	int vipaptEile[laikasMin] = {0};
	int laisviKasininkai = bendrasKasSkaicius;
	
	int ksk;
	
	for(int i = 0; i < laikasMin; i++)
	{
		
		out << "   T = " << i+1 << " min." << endl; 
		
		atejoVip = ((rand() % 100) < vipTikimybe);
		atejoPap = ((rand() % 100) < papTikimybe);
		
		if(atejoVip && atejoPap)
		{
			atejoPap = false;
		}
	
		int kiek0 = 0;
		
		for(int j = 0; j < bendrasKasSkaicius; j++)
		{
			if(kasSkaitliukas[j] == 0)
			{
				kiek0++;
			}	
		}
		
		ksk = (bendrasKasSkaicius - kiek0);
		
		if(kiek0 > 0)
		{ 
			yraKasininku = true;
			
			if(kiek0 < bendrasKasSkaicius)
			{
				out << "	1.1) Laisvu kasininku: " << kiek0 << "/" << bendrasKasSkaicius << endl;
				out << "	1.2) Dirbantys kasininkai: ";
			}
			else out << "	1) Laisvu kasininku: " << kiek0 << "/" << bendrasKasSkaicius << endl;
			
			
			for (int j = 0; j < bendrasKasSkaicius; j++)
			{
				if(kasSkaitliukas[j] > 0 && ksk > 1)
				{
					out << "kas" << (j+1) << ", "; 
					ksk--;
				}
				else if(kasSkaitliukas[j] > 0 && ksk == 1) 
					out << "kas" << (j+1) << ".";
			}
			if(kiek0 < bendrasKasSkaicius) 
				out << endl;
			
			prastovos = (kiek0 * minAtlyginimas);
			prastovos1 += prastovos;
			out << "	2) Prastovos: " << prastovos << " eur." << endl;
		}
		else
		{	
		yraKasininku = false;
		out << "	1) Laisvu kasininku nera." << endl;
		out << "	2) Prastovos: 0 eur." << endl;
		
		}
		
		if(!atejoVip && !atejoPap)
		{
			out << "	3) Naujas klientas neatvyko." << endl;
		}
		
		if(yraKasininku && atejoVip)
		{
			for(int j = 0; j < bendrasKasSkaicius; j++)
			{
					if(kasSkaitliukas[j] == 0)
					{
						vipKlientoNum++;
						out << "	3) Atvyko VIP klientas" << vipKlientoNum << "," << " ji prieme kasininkas" << (j+1) << "." << endl;
						kasSkaitliukas[j] = vipLaikas;
						SkaitliukasVip[j] = vipLaikas;
						j = bendrasKasSkaicius;
						vipapt.push(vipKlientoNum);
						vipaptEile[vipKlientoNum] = vipLaikas;
						
					}	
			}
		}
		else if(yraKasininku && atejoPap)
		{
			for(int j = 0; j < bendrasKasSkaicius; j++)
			{
					if(kasSkaitliukas[j] == 0)
					{
						papKlientoNum++;
						out << "	3) Atvyko paprastas klientas" << papKlientoNum << "," << " ji prieme kasininkas" << (j+1) << "." << endl;
						kasSkaitliukas[j] = papLaikas;
						SkaitliukasPap[j] = papLaikas;
						j = bendrasKasSkaicius;
						papapt.push(papKlientoNum);
						papaptEile[papKlientoNum] = papLaikas;
					}	
			}
		}
		else if(!yraKasininku && atejoVip)
		{
			vipKlientoNum++;
			out << "	3) Atvyko VIP klientas" << vipKlientoNum << ", bet laisvu kasininku nera." << endl;
			vip.push(vipKlientoNum);
		}
		else if(!yraKasininku && atejoPap)
		{
			papKlientoNum++;
			out << "	3) Atvyko paprastas klientas" << papKlientoNum << ", bet laisvu kasininku nera." << endl;
			pap.push(papKlientoNum);
		}
		
		if(pap.empty() && vip.empty())
		{
			out << "	4) Nera klientu, laukianciu eileje." << endl;
			out << endl;
		}	
		else
		{
			unsigned int vipSize = vip.size();
			out << "	4.1) VIP klientu eileje: " << vipSize << endl;

			unsigned int papSize = pap.size();
			out << "	4.2) paprastu klientu eileje: " << papSize << endl;
			
			out << "	4.3) Bendra eile: ";
			queue<int>v(vip);
			queue<int>p(pap);
			
					while (!v.empty())
					{							
						if(v.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{	
								out << "vk" << v.front() << ", ";
								v.pop();
							}
						}
						else if (v.size() > 1 || p.size() > 0)
						{
							out << "vk" << v.front() << ", ";
							v.pop();
						}
						else
						{
							out << "vk" << v.front() << ".";
							v.pop();
						}
					}
									
					while (!p.empty())
					{	
						if(p.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{
								out << "pk" << p.front() << ", ";
								p.pop();
							}	
						}	
						else if (p.size() > 1)
						{
							out << "pk" << p.front() << ", ";
							p.pop();
						}
						else
						{
							out << "pk" << p.front() << ".";
							p.pop();
						}
					}
			out << endl << endl;
		}

		for(int j = 0; j < bendrasKasSkaicius; j++)
		{
			if(SkaitliukasVip[j] == 0 && !vip.empty())
			{
				vipapt.pop();
				vipapt.push(vip.front());
				vip.pop();
				kasSkaitliukas[j] = vipLaikas;
				SkaitliukasVip[j] = vipLaikas;
			}
			else if(SkaitliukasPap[j] == 0 && !pap.empty())
			{
				papapt.pop();
				papapt.push(pap.front());
				pap.pop();
				kasSkaitliukas[j] = papLaikas;
				SkaitliukasPap[j] = papLaikas;
			}
			else if(SkaitliukasVip[j] == 0 && !vipapt.empty())
			{
				vipapt.pop();
			}
			else if(SkaitliukasPap[j] == 0 && !papapt.empty())
			{
				papapt.pop();
			}		
		}
		out << endl << endl;
		
		for(int j = 0; j < bendrasKasSkaicius; j++)
		{
			if(kasSkaitliukas[j] > 0)
			{	
			kasSkaitliukas[j]--;
			}
			
			if(SkaitliukasVip[j] > 0)
			{	
			SkaitliukasVip[j]--;
			}
			
			if(SkaitliukasPap[j] > 0)
			{	
			SkaitliukasPap[j]--;
			}
		}	

		laisviKasininkai = kiek0;	
	}
	int uzimtiKasininkai = 	(bendrasKasSkaicius - laisviKasininkai);
	int papildomasMomentas = laikasMin;
	out << "Darbo laikas baigesi." << endl;
	out << "Pradedami skaiciuoti virsvalandziai." << endl << endl;
	while(!(vip.empty()) || !(pap.empty()) || (laisviKasininkai != bendrasKasSkaicius))
	{
		virsminutes1++;
		papildomasMomentas++;
		out << "   T = " << papildomasMomentas << " min." << endl;
		ksk = (bendrasKasSkaicius - laisviKasininkai);
		
		if(laisviKasininkai > 0)
		{
			yraKasininku = true;

			if(laisviKasininkai < bendrasKasSkaicius)
			{
				out << "	1.1) Laisvu kasininku: " << laisviKasininkai << "/" << bendrasKasSkaicius << endl;
				out << "	1.2) Dirbantys kasininkai: ";
			}
			for (int j = 0; j < bendrasKasSkaicius; j++)
			{
				if(kasSkaitliukas[j] > 0 && ksk > 1)
				{
					out << "kas" << (j+1) << ", "; 
					ksk--;
				}
				else if(kasSkaitliukas[j] > 0 && ksk == 1) 
					out << "kas" << (j+1) << ".";
			}
			if(laisviKasininkai < bendrasKasSkaicius) 
				out << endl;
			
			else out << "	1) Laisvu kasininku: " << laisviKasininkai << "/" << bendrasKasSkaicius << endl;
			virsvalandziai = (uzimtiKasininkai * (minAtlyginimas * 2));
			virsvalandziai1 += virsvalandziai;
			out << "	2) Virsvalandziai: " << virsvalandziai << " eur." << endl;
		}
		else
		{	
		yraKasininku = false;
		out << "	1) Visi kasininkai uzimti." << endl;
		virsvalandziai = (bendrasKasSkaicius * (minAtlyginimas * 2));
		virsvalandziai1 += virsvalandziai;
		out << "	2) Virsvalandziai: " << virsvalandziai << " eur." << endl;		
		}
		
		if(pap.empty() && vip.empty())
		{
			out << "	3) Nera klientu, laukianciu eileje." << endl;
			out << endl;
		}	
		else
		{
			unsigned int vipSize = vip.size();
			out << "	3.1) VIP klientu eileje: " << vipSize << endl;
			
			unsigned int papSize = pap.size();
			out << "	3.2) paprastu klientu eileje: " << papSize << endl;

			out << "	3.3) Bendra eile: ";
			queue<int>v(vip);
			queue<int>p(pap);
			
					while (!v.empty())
					{	
						if(v.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{
								out << "vk" << v.front() << ", ";
								v.pop();
							}	
						}
						else if (v.size() > 1 || p.size() > 0)
						{
							out << "vk" << v.front() << ", ";
							v.pop();
						}
						else
						{
							out << "vk" << v.front() << ".";
							v.pop();
						}
					}
									
					while (!p.empty())
					{	
						if(p.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{
								out << "pk" << p.front() << ", ";
								p.pop();
							}
						}	
						else if (p.size() > 1)
						{
							out << "pk" << p.front() << ", ";
							p.pop();
						}
						else
						{
							out << "pk" << p.front() << ".";
							p.pop();
						}
					}
			out << endl;
		}
		
		for(int j = 0; j < bendrasKasSkaicius; j++)
		{
			if(kasSkaitliukas[j] > 0)
			{	
			kasSkaitliukas[j]--;
			}
			
			if(SkaitliukasVip[j] > 0)
			{	
			SkaitliukasVip[j]--;
			}
			
			if(SkaitliukasPap[j] > 0)
			{	
			SkaitliukasPap[j]--;
			}
		}
		for(int j = 0; j < bendrasKasSkaicius; j++)
		{
			if(SkaitliukasVip[j] == 0 && !vip.empty())
			{
				vip.pop();
			}
			if(SkaitliukasPap[j] == 0 && !pap.empty())
			{
				pap.pop();
			}	
		}
		int k = 0;
		for(int j = 0; j < bendrasKasSkaicius; j++)
		{
			if(kasSkaitliukas[j] == 0)
			{
				k++;
			}	
		}
		laisviKasininkai = k;
		uzimtiKasininkai = (bendrasKasSkaicius - laisviKasininkai);
		
	}	
		
}

void atskirosEiles(ofstream &out, int papTikimybe, int vipTikimybe, int kasSkaicius, int vipKasSkaicius, int papLaikas, int vipLaikas, int dienosIlgis, float valAtlyginimas)
{
	queue<int> pap;
	queue<int> vip;
	queue<int> vipapt;
	queue<int> papapt;
	srand(0);
	bool yraPapKasininku = true;
	bool yraVipKasininku = true;
	bool atejoVip = false;
	bool atejoPap = false;
	
	float prastovos = 0;
	float virsvalandziai = 0;
	
	int laikasMin = dienosIlgis * 60;
	float minAtlyginimas = (valAtlyginimas / 60);
	
	int SkaitliukasVip[vipKasSkaicius] = {0};
	int SkaitliukasPap[kasSkaicius] = {0};
	
	int vipKlientoNum = 0;
	int papKlientoNum = 0;
	
	int papEile[laikasMin] = {0};
	int vipEile[laikasMin] = {0};
	int laisviPapKasininkai;
	int laisviVipKasininkai;
	int ksk;
	
	for(int i = 0; i < laikasMin; i++)
	{
		
		out << "   T = " << i+1 << " min." << endl; 
		
		atejoVip = ((rand() % 100) < vipTikimybe);
		atejoPap = ((rand() % 100) < papTikimybe);
		
		if(atejoVip && atejoPap)
		{
			atejoPap = false;
		}
	
		int kiek0 = 0;
		
		for(int j = 0; j < kasSkaicius; j++)
		{
			if(SkaitliukasPap[j] == 0)
			{
				kiek0++;
			}	
		}
		laisviPapKasininkai = kiek0;
		
		kiek0 = 0;
		
		for(int j = 0; j < vipKasSkaicius; j++)
		{
			if(SkaitliukasVip[j] == 0)
			{
				kiek0++;
			}	
		}
		laisviVipKasininkai = kiek0;
		
		if(laisviVipKasininkai > 0)
		{
			yraVipKasininku = true;
			
			if(laisviVipKasininkai < vipKasSkaicius)
			{
				out << "	1.1) Laisvu VIP kasininku: " << laisviVipKasininkai << "/" << vipKasSkaicius << endl;
				out << "	1.2) Dirbantys VIP kasininkai: ";
			}
			else out << "	1) Laisvu VIP kasininku: " << laisviVipKasininkai << "/" << vipKasSkaicius << endl;
			
			ksk = (vipKasSkaicius - laisviVipKasininkai);
			
			for (int j = 0; j < vipKasSkaicius; j++)
			{
				if(SkaitliukasVip[j] > 0 && ksk > 1)
				{
					out << "vkas" << (j+1) << ", "; 
					ksk--;
				}
				else if(SkaitliukasVip[j] > 0 && ksk == 1) 
					out << "vkas" << (j+1) << ".";
			}
			if(laisviVipKasininkai < vipKasSkaicius) 
				out << endl;
			
			prastovos = (laisviVipKasininkai * minAtlyginimas);
			prastovos2 += prastovos;
			out << "	2) VIP kasininku prastovos: " << prastovos << " eur." << endl;
		}
		else
		{	
		yraVipKasininku = false;
		out << "	1) Laisvu VIP kasininku nera." << endl;
		out << "	2) VIP kasininku prastovos: 0 eur." << endl;		
		}
		
		if(laisviPapKasininkai > 0)
		{
			yraPapKasininku = true;
			if(laisviPapKasininkai < kasSkaicius)
			{
				out << "	3.1) Laisvu paprastu kasininku: " << laisviPapKasininkai << "/" << kasSkaicius << endl;
				out << "	3.2) Dirbantys paprasti kasininkai: ";
			}
			else out << "	3) Laisvu paprastu kasininku: " << laisviPapKasininkai << "/" << kasSkaicius << endl;
			
			ksk = (kasSkaicius - laisviPapKasininkai);
			
			for (int j = 0; j < kasSkaicius; j++)
			{
				if(SkaitliukasPap[j] > 0 && ksk > 1)
				{
					out << "pkas" << (j+1) << ", "; 
					ksk--;
				}
				else if(SkaitliukasPap[j] > 0 && ksk == 1) 
					out << "pkas" << (j+1) << ".";
			}
			if(laisviPapKasininkai < kasSkaicius) 
				out << endl;
			
			prastovos = (laisviPapKasininkai * minAtlyginimas);
			prastovos2 += prastovos;
			out << "	4) Paprastu kasininku prastovos: " << prastovos << " eur." << endl;
		}
		else
		{	
		yraPapKasininku = false;
		out << "	3) Laisvu paprastu kasininku nera." << endl;
		out << "	4) Paprastu kasininku prastovos: 0 eur" << endl;		
		}
		
		if(!atejoVip && !atejoPap)
		{
			out << "	5) Naujas klientas neatvyko." << endl;
		}
		
		if(yraVipKasininku && atejoVip)
		{
			for(int j = 0; j < vipKasSkaicius; j++)
			{
					if(SkaitliukasVip[j] == 0)
					{
						vipKlientoNum++;
						out << "	5) Atvyko VIP klientas" << vipKlientoNum << "," << " ji prieme VIP kasininkas" << (j+1) << "." << endl;
						SkaitliukasVip[j] = vipLaikas;
						j = vipKasSkaicius;
						
					}	
			}
		}
		else if(yraPapKasininku && atejoPap)
		{
			for(int j = 0; j < kasSkaicius; j++)
			{
					if(SkaitliukasPap[j] == 0)
					{
						papKlientoNum++;
						out << "	5) Atvyko paprastas klientas" << papKlientoNum << "," << " ji prieme paprastas kasininkas" << (j+1) << "." << endl;
						SkaitliukasPap[j] = papLaikas;
						j = kasSkaicius;
					}	
			}
		}
		else if(!yraVipKasininku && atejoVip)
		{
			out << "	5) Atvyko VIP klientas, bet laisvu VIP kasininku nera." << endl;
			vipKlientoNum++;
			vip.push(vipKlientoNum);
		}
		else if(!yraPapKasininku && atejoPap)
		{
			out << "	5) Atvyko paprastas klientas, bet laisvu paprastu kasininku nera." << endl;
			papKlientoNum++;
			pap.push(papKlientoNum);
		}
		
		if(pap.empty() && vip.empty())
		{
			out << "	6) Nera klientu, laukianciu eileje." << endl;
			out << endl;
		}	
		else
		{
			unsigned int vipSize = vip.size();
			out << "	6.1) VIP klientu eileje: " << vipSize << endl;

			if(vipSize > 0)
			{
				
			out << "	6.2) VIP eile: ";
			
			queue<int>v(vip);
			
					while (!v.empty())
					{	
						if(v.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{
								out << "vk" << v.front() << ", ";
								v.pop();
							}
						}	
						else if (v.size() > 1)
						{
							out << "vk" << v.front() << ", ";
							v.pop();
						}
						else
						{
							out << "vk" << v.front() << ".";
							v.pop();
						}
					}
			
			
			}
			else out << "	6.2) VIP eile tuscia ";
			
			out << endl;
			
			unsigned int papSize = pap.size();
			out << "	6.3) paprastu klientu eileje: " << papSize << endl;
			
			if(papSize > 0)
			{
				
			out << "	6.4) Paprasta eile: ";
			
			queue<int>p(pap);
			
					while (!p.empty())
					{	
						if(p.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{
								out << "pk" << p.front() << ", ";
								p.pop();
							}
						}						
						else if (p.size() > 1)
						{
							out << "pk" << p.front() << ", ";
							p.pop();
						}
						else
						{
							out << "pk" << p.front() << ".";
							p.pop();
						}
					}
			
			
			}
			else out << "	6.4) Paprasta eile tuscia. ";
			
			out << endl;
		}
		out << endl;
		
		for(int j = 0; j < kasSkaicius; j++)
		{			
			if(SkaitliukasPap[j] > 0)
			{	
			SkaitliukasPap[j]--;
			}
		}
		for(int j = 0; j < vipKasSkaicius; j++)
		{			
			if(SkaitliukasVip[j] > 0)
			{	
			SkaitliukasVip[j]--;
			}
		}
		
		for(int j = 0; j < kasSkaicius; j++)
		{
			if(SkaitliukasPap[j] == 0 && !pap.empty())
			{
				pap.pop();
			}	
		}
		for(int j = 0; j < vipKasSkaicius; j++)
		{
			if(SkaitliukasVip[j] == 0 && !vip.empty())
			{
				vip.pop();
			}	
		}
		
	}
	
	int uzimtiVipKasininkai = (vipKasSkaicius - laisviVipKasininkai);
	int uzimtiPapKasininkai = (kasSkaicius - laisviPapKasininkai);
	int papildomasMomentas = laikasMin;
	out << "Darbo laikas baigesi." << endl;
	out << "Pradedami skaiciuoti virsvalandziai." << endl << endl;
	
	while(!(vip.empty()) || !(pap.empty()) || (laisviVipKasininkai != vipKasSkaicius) || (laisviPapKasininkai != kasSkaicius))
	{
		papildomasMomentas++;
		out << "   T = " << papildomasMomentas << " min." << endl;
		virsminutes2++;
		
		if(laisviVipKasininkai > 0)
		{
			yraVipKasininku = true;
			if(laisviVipKasininkai < vipKasSkaicius)
			{
				out << "	1.1) Laisvu VIP kasininku: " << laisviVipKasininkai << "/" << vipKasSkaicius << endl;
				out << "	1.2) Dirbantys VIP kasininkai: ";
			}
			else out << "	1) Laisvu VIP kasininku: " << laisviVipKasininkai << "/" << vipKasSkaicius << endl;
			
			ksk = (vipKasSkaicius - laisviVipKasininkai);
			
			for (int j = 0; j < vipKasSkaicius; j++)
			{
				if(SkaitliukasVip[j] > 0 && ksk > 1)
				{
					out << "vkas" << (j+1) << ", "; 
					ksk--;
				}
				else if(SkaitliukasVip[j] > 0 && ksk == 1) 
					out << "vkas" << (j+1) << ".";
			}
			if(laisviVipKasininkai < vipKasSkaicius) 
				out << endl;
			
			virsvalandziai = (uzimtiVipKasininkai * (minAtlyginimas * 2));
			virsvalandziai2 += virsvalandziai;
			out << "	2) VIP kasininku virsvalandziai: " << virsvalandziai << " eur." << endl;
		}
		else
		{	
		yraVipKasininku = false;
		out << "	1) Uzimtu VIP kasininku nera." << endl;
		out << "	2) Virsvalandziai: 0 eur." << endl;		
		}
		
		if(laisviPapKasininkai > 0)
		{
			yraPapKasininku = true;
			if(laisviPapKasininkai < kasSkaicius)
			{
				out << "	3.1) Laisvu paprastu kasininku: " << laisviPapKasininkai << "/" << kasSkaicius << endl;
				out << "	3.2) Dirbantys paprasti kasininkai: ";
			}
			else out << "	3) Laisvu paprastu kasininku: " << laisviPapKasininkai << "/" << kasSkaicius << endl;
			
			ksk = (kasSkaicius - laisviPapKasininkai);
			
			for (int j = 0; j < kasSkaicius; j++)
			{
				if(SkaitliukasPap[j] > 0 && ksk > 1)
				{
					out << "pkas" << (j+1) << ", "; 
					ksk--;
				}
				else if(SkaitliukasPap[j] > 0 && ksk == 1) 
					out << "pkas" << (j+1) << ".";
			}
			if(laisviPapKasininkai < kasSkaicius) 
				out << endl;
			
			virsvalandziai = (uzimtiPapKasininkai * (minAtlyginimas * 2));
			virsvalandziai2 += virsvalandziai;
			out << "	4) Paprastu kasininku virsvalandziai: " << virsvalandziai << " eur." << endl;
		}
		else
		{	
		yraPapKasininku = false;
		out << "	3) Uzimtu paprastu kasininku nera." << endl;
		out << "	4) Paprastu Kasininku virsvalandziai: 0 eur." << endl;		
		}
		
		if(pap.empty() && vip.empty())
		{
			out << "	5) Nera klientu, laukianciu eileje." << endl;
			out << endl;
		}	
		else
		{
			unsigned int vipSize = vip.size();
			out << "	5.1) VIP klientu eileje: " << vipSize << endl;
			
			if(vipSize > 0)
			{
				
			out << "	5.2) VIP eile: ";
			
			queue<int>v(vip);
			
					while (!v.empty())
					{	
						if(v.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{
								out << "vk" << v.front() << ", ";
								v.pop();
							}
						}	
						else if (v.size() > 1)
						{
							out << "vk" << v.front() << ", ";
							v.pop();
						}
						else
						{
							out << "vk" << v.front() << ".";
							v.pop();
						}
					}
			}
			else out << "	5.2) VIP eile tuscia. ";
			
			out << endl;
			
			unsigned int papSize = pap.size();
			out << "	5.3) paprastu klientu eileje: " << papSize << endl;
			out << endl;
			
			if(papSize > 0)
			{
				
			out << "	5.4) Paprasta eile: ";
			
			queue<int>p(pap);
			
					while (!p.empty())
					{	
						if(p.size() > 3)
						{
							for (int j = 0; j < 3; j++)
							{
								out << "pk" << p.front() << ", ";
								p.pop();
							}
						}	
						else if (p.size() > 1)
						{
							out << "pk" << p.front() << ", ";
							p.pop();
						}
						else
						{
							out << "pk" << p.front() << ".";
							p.pop();
						}
					}
			
			
			}
			else out << "	5.4) Paprasta eile tuscia ";
			
			out << endl << endl;
		}
		
		for(int j = 0; j < kasSkaicius; j++)
		{			
			if(SkaitliukasPap[j] > 0)
			{	
			SkaitliukasPap[j]--;
			}
		}
		for(int j = 0; j < vipKasSkaicius; j++)
		{			
			if(SkaitliukasVip[j] > 0)
			{	
			SkaitliukasVip[j]--;
			}
		}
		
		for(int j = 0; j < kasSkaicius; j++)
		{
			if(SkaitliukasPap[j] == 0 && !pap.empty())
			{
				pap.pop();
			}	
		}
		for(int j = 0; j < vipKasSkaicius; j++)
		{
			if(SkaitliukasVip[j] == 0 && !vip.empty())
			{
				vip.pop();
			}	
		}
		
		int k = 0;		
		for(int j = 0; j < kasSkaicius; j++)
		{			
			if(SkaitliukasPap[j] == 0)
			{	
			k++;
			}
		}
		laisviPapKasininkai = k;
		uzimtiPapKasininkai = (kasSkaicius - laisviPapKasininkai);
		k = 0;
		for(int j = 0; j < vipKasSkaicius; j++)
		{			
			if(SkaitliukasVip[j] == 0)
			{	
			k++;
			}
		}
		laisviVipKasininkai = k;
		uzimtiVipKasininkai = (vipKasSkaicius - laisviVipKasininkai);
		
	}

}
