#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

fstream file;
int n,fxpos,fypos,delay;
string game;

struct play{
	string name;
	int punt;
}record[11];

struct cart{
	int x;
	int y;
}pos[100];

void visual(){
	system("cls");
	int tab[15][30]={0};
	for(int i=0;i<15;i++)
		for(int j=0;j<30;j++){
			if(i==0||i==14||j==0||j==29)	
				tab[i][j]=2;
			if(i==fypos&&j==fxpos)
				tab[i][j]=3;
			for(int k=0;k<n;k++)
				if(j==pos[k].x&&i==pos[k].y)
					tab[i][j]=1;
		}
	for(int i=0;i<15;i++){
		for(int j=0;j<30;j++){
			switch(tab[i][j]){
				case 1:{
					cout<<"O";
					break;
				}
				case 2:{
					cout<<"#";
					break;
				}
				case 3:{
					cout<<"@";
					break;
				}
				default:{
					cout<<" ";
					break;
				}
			}
		}
		cout<<endl;
	}
	cout<<endl<<endl<<"Punteggio: "<<n<<endl;
}

void fruit(){
	fxpos=rand()%28+1;
	fypos=rand()%13+1;
	for(int i=0;i<n;i++)
		if(pos[i].x==fxpos&&pos[i].y==fypos)
			fruit();
}

void eat(){
	if(pos[0].x==fxpos&&pos[0].y==fypos){
		fruit();
		n++;
	}
}

bool hit(){
	for(int i=1;i<n;i++)
		if(pos[0].x==pos[i].x&&pos[0].y==pos[i].y)
			return true;
	return false;
}

void snake(){
	for(int i=1;i<100;i++){
		pos[i].x=-1;
		pos[i].y=-1;
	}
	pos[0].x=1;
	pos[0].y=1;
	system("color 03");
	int iner=0,c=0;
	fruit();
	while(GetAsyncKeyState(27)>=0&&pos[0].x>0&&pos[0].x<29&&pos[0].y>0&&pos[0].y<14&&n<100){
		eat();
		visual();
		delay=150-(3*(n/5));
		Sleep(delay);
		for(int i=n-1;i>0;i--){
			pos[i].x=pos[i-1].x;
			pos[i].y=pos[i-1].y;
		}
		if((GetAsyncKeyState(37)!=0&&iner!=4&&c>0)||(GetAsyncKeyState(37)<0&&iner!=4))
			iner=3;
		else
			if((GetAsyncKeyState(38)!=0&&iner!=2&&c>0)||(GetAsyncKeyState(38)<0&&iner!=2))
				iner=1;
			else
				if((GetAsyncKeyState(39)!=0&&iner!=3&&c>0)||(GetAsyncKeyState(39)<0&&iner!=3))
					iner=4;
				else
					if((GetAsyncKeyState(40)!=0&&iner!=1&&c>0)||(GetAsyncKeyState(40)<0&&iner!=1))
						iner=2;
		switch(iner){
			case 1:{
				pos[0].y--;
				c++;
				break;
			}
			case 2:{
				pos[0].y++;
				c++;
				break;
			}
			case 3:{
				pos[0].x--;
				c++;
				break;
			}
			case 4:{
				pos[0].x++;
				c++;
				break;
			}
		}
		if(hit()==true&&iner!=0)
			break;
	}
	Sleep(1000);
	system("cls");
	if(n==100){
		system("color 20");
		cout<<"HAI VINTO!!!\n";
	}
	else{
		system("color 40");
		cout<<"GAMEOVER\n";
	}
	Sleep(2000);
}

void input_output(){
	system("cls");
	int k;
	file.open("record.txt",ios::in);
	file>>k;
	for(int i=0;i<k;i++)
		file>>record[i].name>>record[i].punt;
	for(int i=0;i<=k;i++)
		if(n>=record[i].punt&&(n<record[i-1].punt||i==0)){
			for(int j=k-1;j>=i;j--)
				record[j+1]=record[j];
			record[i].name=game;
			record[i].punt=n;
		}
	file.close();
	file.open("record.txt",ios::out);
	if(k<10&&n>0)
		k+=1;
	file<<k<<endl;
	cout<<"Record dei giocatori:\n\nNome\t\t\tPunteggio\n\n";
	for(int i=0;i<k;i++){
		if(record[i].name.length()<8)
			cout<<record[i].name<<"\t\t\t"<<record[i].punt<<endl;
		else
			cout<<record[i].name<<"\t\t"<<record[i].punt<<endl;
		file<<record[i].name<<" "<<record[i].punt<<endl;
	}
	file.close();
}

void menu();

void rule(){
	system("cls");
	cout<<"\t\t\t\t\t#####\t#   #\t#####\t#   #\t#####\n\t\t\t\t\t#    \t##  #\t#   #\t#  # \t#    \n\t\t\t\t\t#####\t# # #\t#####\t###  \t#####\n\t\t\t\t\t    #\t#  ##\t#   #\t#  # \t#    \n\t\t\t\t\t#####\t#   #\t#   #\t#   #\t#####\tby Maini Alessandro";
	cout<<"\n\n\nPer iniziare a giocare premere a lungo una freccia nella direzione di spostamento desiderata\nPer muoversi durante il gioco usare i tasti freccia\nPer uscire dal gioco premere a lungo il tasto Esc\nPer vincere bisogna totalizzare 100 punti (i punti vengono mostrati in basso)\nPer aumentare i punti il serpente deve magiare le chiocciole\nPer non perdere il serpente deve evitare di scontrarsi con la propria coda o con le pareti dell'arena di gioco\n\nBuona fortuna!!\n\nPremi un tasto per tornare al menu iniziale\n";
	system("PAUSE");
	menu();
}

void regist(){
	system("color 0c");
	system("cls");
	cout<<"\t\t\t\t\t#####\t#   #\t#####\t#   #\t#####\n\t\t\t\t\t#    \t##  #\t#   #\t#  # \t#    \n\t\t\t\t\t#####\t# # #\t#####\t###  \t#####\n\t\t\t\t\t    #\t#  ##\t#   #\t#  # \t#    \n\t\t\t\t\t#####\t#   #\t#   #\t#   #\t#####\tby Maini Alessandro";
	cout<<"\n\n\nInserisci il tuo nome (max. 14 caratteri - no spazi):\n";
	do{
		cin>>game;
	}while(game.length()>14);
	Sleep(2000);
}

void menu(){
	int s=0;
	string risp;
	system("cls");
	system("color 0c");
	cout<<"\t\t\t\t\t#####\t#   #\t#####\t#   #\t#####\n\t\t\t\t\t#    \t##  #\t#   #\t#  # \t#    \n\t\t\t\t\t#####\t# # #\t#####\t###  \t#####\n\t\t\t\t\t    #\t#  ##\t#   #\t#  # \t#    \n\t\t\t\t\t#####\t#   #\t#   #\t#   #\t#####\tby Maini Alessandro";
	cout<<"\n\n\n1) Gioca\n2) Regole\n3) Classifica\n4) Esci\n";
	do{
		cin>>s;
	}while(s<1||s>4);
	switch(s){
		case 1:{
			do{
				n=1;
				regist();
				snake();
				input_output();
				Sleep(3000);
				cout<<"\n\nVuoi fare un'altra partita? (s/n)\n";
				cin>>risp;
				system("cls");
			}while(risp=="S"||risp=="s"||risp=="Si"||risp=="si"||risp=="SI");
			menu();
		}
		case 2:{
			rule();
		}
		case 3:{
			n=-1;
			input_output();
			cout<<"\n\nPremi un tasto per tornare al menu iniziale\n";
			system("PAUSE");
			menu();			
		}
		case 4:{
			exit(0);
		}
	}
}
