/****************************************************************************
**						SAKARYA ÜNÝVERSÝTESÝ
**				BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**					BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**					 PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**					ÖDEV NUMARASI…...:PROJE ÖDEVÝ
**					ÖÐRENCÝ ADI......:ECEM AMANVERMEZ
**					ÖÐRENCÝ NUMARASI.:
**					DERS GRUBU.......:2A
****************************************************************************/


//#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

const int mermi_sayisi_max = 100;
const int dusman_sayisi_max = 50;
const int dusman_uretme_araligi = 30;

//-------------------------------------------------------//

class Sekil
{
protected:

	int en;
	int boy;

public:
	int aktif;
	int X;// = baslangicX;
	int Y;// = baslangicY;
	char karakter;

	int genislik();
	int yukseklik();
	//Sekil();
	//~Sekil();
};

int Sekil::genislik()
{
	return en;
}

int Sekil::yukseklik()
{
	return boy;
}

//-------------------------------------------------------//

class Kursor
{
	void kurusorGorunum(bool);
public:
	void gitXY(int, int);

	Kursor();
	~Kursor();
};

Kursor::Kursor()
{
	kurusorGorunum(false);
}


Kursor::~Kursor()
{
}

void Kursor::gitXY(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void Kursor::kurusorGorunum(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

//-------------------------------------------------------//

class Sahne
{


	int en;
	int boy;

public:

	char karakter;

	Kursor kursor;

	char sahne[80][25];

	void sifirla();
	void sinirOlustur();
	void ciz();

	int genislik();
	int yukseklik();

	char konumdaki_karakter(int, int);

	Sahne();
	~Sahne();
};

Sahne::Sahne()
{
	karakter = 219;
	en = 80;
	boy = 25;
}


Sahne::~Sahne()
{
}

void Sahne::sifirla()
{
	for (int y = 0; y < boy; y++)
	{
		for (int x = 0; x < en; x++)
		{
			sahne[x][y] = ' ';
		}
	}
}

void Sahne::sinirOlustur()
{
	for (int x = 0; x < en; x++)
	{
		sahne[x][0] = karakter;
		sahne[x][boy - 1] = karakter;
	}
	for (int y = 0; y < boy; y++)
	{
		sahne[0][y] = karakter;
		sahne[en - 1][y] = karakter;


	}
}

void Sahne::ciz()
{
	kursor.gitXY(0, 0);
	for (int y = 0; y < boy; y++)
	{
		for (int x = 0; x < en; x++)
		{
			cout << sahne[x][y];
		}
		cout << endl;
	}
}

int Sahne::genislik()
{
	return en;
}

int Sahne::yukseklik()
{
	return boy;
}

char Sahne::konumdaki_karakter(int x, int y)
{
	return sahne[x][y];
}

//-------------------------------------------------------//

class Ucak :public Sekil
{
	char sekil[3][5];
public:
	void olustur(Sahne*);
	void sil(Sahne*);
	void hareket(Sahne*, bool);
	Ucak();
	~Ucak();
};

Ucak::Ucak()
{
	X = 1;
	Y = 1;
	karakter = 178;
	en = 3;
	boy = 5;
	aktif = true;
}


Ucak::~Ucak()
{
}

void Ucak::olustur(Sahne* s)
{
	s->sahne[X][Y] = karakter;
	s->sahne[X + 1][Y + 1] = karakter;
	s->sahne[X + 2][Y + 2] = karakter;
	s->sahne[X + 1][Y + 3] = karakter;
	s->sahne[X][Y + 4] = karakter;
}

void Ucak::sil(Sahne* s)
{
	s->sahne[X][Y] = ' ';
	s->sahne[X + 1][Y + 1] = ' ';
	s->sahne[X + 2][Y + 2] = ' ';
	s->sahne[X + 1][Y + 3] = ' ';
	s->sahne[X][Y + 4] = ' ';
}

void Ucak::hareket(Sahne* s, bool yon)
{

	if (Y >= s->yukseklik() - (boy + 1))
		Y = s->yukseklik() - (boy + 1);
	else
	{
		if (yon)
		{
			sil(s);
			Y++;
			olustur(s);
		}
	}
	if (Y <= 1)
		Y = 1;
	else
	{
		if (!yon && (aktif == true))
		{
			sil(s);
			Y--;
			olustur(s);
		}
	}
	//s->ciz();
}

//-------------------------------------------------------//


class Mermi :public Sekil
{
	char sekil[1][1];
public:
	void olustur(Sahne*);
	void sil(Sahne*);
	void hareket(Sahne*, bool);
	Mermi();
	Mermi(Ucak* u);
	~Mermi();
};

Mermi::Mermi()
{
	X = 5;
	Y = 5;
	karakter = '-';
	en = 1;
	boy = 1;
	aktif = false;
}

Mermi::Mermi(Ucak* u)
{
	X = u->genislik() + 1;
	Y = u->Y + (u->yukseklik() / 2);
	karakter = '-';
	en = 1;
	boy = 1;
	aktif = false;
}


Mermi::~Mermi()
{
}

void Mermi::olustur(Sahne * s)
{
	s->sahne[X][Y] = karakter;
}

void Mermi::sil(Sahne * s)
{
	s->sahne[X][Y] = ' ';
}

void Mermi::hareket(Sahne * s, bool yon)
{


	if (X >= s->genislik() - (en + 1))
	{
		X = s->genislik() - (en + 1);
		aktif = false;
		sil(s);
	}
	else
	{
		if (yon && aktif == true)
		{
			sil(s);
			X++;
			olustur(s);
		}
	}
}

//-------------------------------------------------------//

class Dusman :public Sekil
{
	char sekil[2][2];
public:
	void olustur(Sahne*);
	void sil(Sahne*);
	void hareket(Sahne*, bool);
	Dusman();
	Dusman(Sahne*);
	~Dusman();
};

Dusman::Dusman()
{
	X = 70;
	Y = 5;
	karakter = 177;
	en = 2;
	boy = 2;
	aktif = false;
}

Dusman::Dusman(Sahne * s)
{
	int sinir = s->yukseklik() - 5;
	int random = rand() % sinir + 2;
	X = s->genislik() - 3;
	Y = random;
	karakter = 177;
	en = 2;
	boy = 2;
	aktif = false;
}


Dusman::~Dusman()
{
}

void Dusman::olustur(Sahne *s)
{
	s->sahne[X][Y] = karakter;
	s->sahne[X][Y + 1] = karakter;
	s->sahne[X + 1][Y] = karakter;
	s->sahne[X + 1][Y + 1] = karakter;
}

void Dusman::sil(Sahne *s)
{
	s->sahne[X][Y] = ' ';
	s->sahne[X][Y + 1] = ' ';
	s->sahne[X + 1][Y] = ' ';
	s->sahne[X + 1][Y + 1] = ' ';
}

void Dusman::hareket(Sahne *s, bool yon)
{
	if (X <= 1)
	{
		X = 1;
		aktif = false;
		sil(s);
	}
	else
	{
		if (!yon && aktif == true)
		{
			sil(s);
			X--;
			olustur(s);
		}
	}
}

//-------------------------------------------------------//

class Oynatici
{
	Sahne* sahne;
	Ucak* ucak;

	Mermi* mermi;
	Mermi* mermiler[mermi_sayisi_max];

	int mermi_sayac;
	int mermi_sayisi;

	Dusman* dusman;
	Dusman* dusmanlar[dusman_sayisi_max];

	int dusman_sayac;
	int dusman_sayisi;
	int dusman_zaman_sayac;


public:
	Oynatici();
	~Oynatici();

	//ön yükleme ön hazýrlýk
	void oyna();
	void kaybettiniz();
	void mermi_kontrol(Dusman*, Sahne*);
	void ucak_kontrol(Ucak*, Sahne*);
};

Oynatici::Oynatici()
{
	sahne = new Sahne();
	ucak = new Ucak();

	dusman = new Dusman(sahne);
	dusman->aktif = true;

	mermi_sayac = 0;
	mermi_sayisi = 0;

	dusman_sayac = 0;
	dusman_sayisi = 0;
	dusman_zaman_sayac = 0;

	mermiler[0] = new Mermi();
	dusmanlar[0] = new Dusman();
	dusmanlar[0]->aktif = true;

	sahne->sifirla();
	sahne->sinirOlustur();
	ucak->olustur(sahne);
	sahne->ciz();

	oyna();

	kaybettiniz();
}

Oynatici::~Oynatici()
{
}

void Oynatici::oyna()
{

	while (ucak->aktif) //ucak ölmediyse
	{
		if (mermiler[mermi_sayac]->aktif)
		{
			for (size_t i = 1; i < mermi_sayisi + 1; i++)
			{
				mermiler[i]->hareket(sahne, 1); //saga haraket
			}
		}

		dusman_zaman_sayac++;
		if (dusmanlar[dusman_sayac]->aktif)
		{
			for (size_t i = 1; i < dusman_sayisi + 1; i++)
			{
				mermi_kontrol(dusmanlar[i], sahne);

				dusmanlar[i]->hareket(sahne, 0); //sola haraket
			}
		}

		if (dusman_zaman_sayac > dusman_uretme_araligi)
		{
			if (dusman_sayac < dusman_sayisi_max - 1)
			{
				dusman_sayac++;
				dusman_sayisi++;
				dusmanlar[dusman_sayac] = new Dusman(sahne);
				dusmanlar[dusman_sayac]->aktif = true;
			}

			if (dusman_sayisi > dusman_sayisi_max - 2)
			{
				if (dusmanlar[dusman_sayisi_max - 1]->aktif == false) {
					/*for (size_t i = 0; i <= dusman_sayisi; i++)
					{
						dusmanlar[i]->aktif = false;
						dusmanlar[i]->sil(sahne);
					}*/
					dusman_sayac = 0;
					dusman_sayisi = 0;
				}
			}
			//dusmanlar[0]->aktif = true;
			dusman_zaman_sayac = 0;
		}


		if (_kbhit())
		{
			char ch = _getch();
			switch (ch)
			{
			case 72: //yukarý ok
				ucak->hareket(sahne, 0);
				break;
			case 80: // aþaðý ok
				ucak->hareket(sahne, 1);
				break;
			case ' ': // space
				if (mermi_sayac < mermi_sayisi_max - 1)
				{
					mermi_sayac++;
					mermi_sayisi++;
					mermiler[mermi_sayac] = new Mermi(ucak);
					mermiler[mermi_sayac]->aktif = true;
				}

				if (mermi_sayisi > mermi_sayisi_max - 2)
				{
					if (mermiler[mermi_sayisi_max - 2]->aktif == false) {
						for (size_t i = 1; i < mermi_sayisi; i++)
						{
							mermiler[i]->aktif = false;
							mermiler[i]->sil(sahne);
						}
						mermi_sayac = 0;
						mermi_sayisi = 0;
					}
				}
				break;
			default:
				break;
			}
		}
		ucak_kontrol(ucak, sahne);
		sahne->ciz();
	}
}

void Oynatici::kaybettiniz()
{
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout << "                   KAYBETTINIZ !!! ";
	cout << endl << endl << endl << endl << endl;
}

void Oynatici::mermi_kontrol(Dusman * d, Sahne * s)
{
	if ((s->konumdaki_karakter(d->X - 1, d->Y) == '-') ||
		(s->konumdaki_karakter(d->X - 1, d->Y + 1) == '-'))
	{
		d->aktif = false;
		d->sil(s);
	}
}

void Oynatici::ucak_kontrol(Ucak* u, Sahne * s)
{
	if ((s->konumdaki_karakter(u->X + 1, u->Y) == dusman->karakter) ||
		(s->konumdaki_karakter(u->X + 2, u->Y + 1) == dusman->karakter) ||
		(s->konumdaki_karakter(u->X + 3, u->Y + 2) == dusman->karakter) ||
		(s->konumdaki_karakter(u->X + 2, u->Y + 3) == dusman->karakter) ||
		(s->konumdaki_karakter(u->X + 1, u->Y + 4) == dusman->karakter))
	{
		u->aktif = false;
		u->sil(s);
	}
}

int main()
{
	srand(time(NULL));

	Oynatici oynatici;

	system("pause");
}
