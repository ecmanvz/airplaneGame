# c++_project_game

A simple airplane game was also made in the project.

## Getting Started

• Airplane consists of 5 characters.<br>
• Gun bullet consists of a single character.<br>
• Enemy is square shaped.<br>
• The plane only moves up and down.<br>

### Prerequisites

What things you need to install the software and how to install them

```javascript
//#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

const int mermi_sayisi_max = 100;
const int dusman_sayisi_max = 50;
const int dusman_uretme_araligi = 30;
```

### Installing

A step by step series of examples that tell you how to get a development env running

```javascript
//ön yükleme ön hazırlık
	void oyna();
	void kaybettiniz();
	void mermi_kontrol(Dusman*, Sahne*);
	void ucak_kontrol(Ucak*, Sahne*);
```

And repeat

```javascript
int main()
{
	srand(time(NULL));

	Oynatici oynatici;

	system("pause");
}
```


