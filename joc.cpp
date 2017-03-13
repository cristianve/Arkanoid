#include "Joc.h"
//hola
Sprite digits[10];
float scale;

//========================================================================
//POSICIONS MARCADORS
int m_iniPuntsX ;
int m_iniPuntsY ;
int m_iniVidesX ;
int m_iniVidesY ;
int m_iniNivellX;
int m_iniNivellY;
int m_pasDigit;

//========================================================================
//Mida i nombre maons mur
int m_midaMaoX;
int m_midaMaoY;

// Mida Pantalla
int m_midaX;
int m_midaY;

//========================================================================
// Inici del taulell respecte la cantonada superior esquerre
int m_iniPantallaX;
int m_iniPantallaY;


// Fi del taulell respecte la cantonada inferior dreta
int m_fiPantallaX;
int m_fiPantallaY;

//Mides i pas de bola
int m_midaBolaX;
int m_midaBolaY;

int m_pasBolaX;
int m_pasBolaY;
//Mides i pas de VAUS
int m_midaVausX;
int m_midaVausY;

int m_pasVausX;

// Retorna un nombre aleatori entre min i max amb un pas enter
// si donem min = 1 max=100 i pas=10 donara nombres possibles:1,10,20,30,40,50,60,70,80,90,100
int aleatori(int min, int max, int pas)
{
	int aleat = ( ( rand() %( ((max-min)/pas) - 1) ) * pas ) + min; 
	return aleat;
}

// Dibuixa un numero a la pantalla, a la posicío (posX,posY) utilitzant els gràfics de la llibreria
// S'utilitza per mostrar la puntuació
void drawNombre(int valor, int posX, int posY)
{
	int divisor = 100;
	int posXActual = posX;
	int nActual = valor;
	bool primerDigit = true;
	int pasDigit = 20*scale;//CHANGE

	while (divisor > 0)
	{
		int d = nActual / divisor;
		nActual = nActual % divisor;
		divisor = divisor / 10;

		if ((d > 0) || !primerDigit || (divisor == 0))
		{
			digits[d].Draw(posXActual, posY);
			primerDigit = false;
		}

		posXActual += m_pasDigit;
	}
}

//-----------------------------------------
// mouBola
// in: posicio actual bola x,y; direccio actual bola dirX,dirY
// out novaposicio bola x,y; novadireccio bola dirX,dirY
// Controla que no arribem als contorns laterals de la pantalla (si arriba canvia el sentit dirX)
// Controla que no arribem a inici(adalt) i final(abaix) de pantalla (si arriba canvia sentit dirY)
//-----------------------------------------
/*void mouBola(int &x, int &y, int &dirX, int &dirY)
{
	y += dirY; 
	x += dirX;

	if (x <= m_iniPantallaX || x >= m_fiPantallaX - m_midaBolaX)
	{	
		dirX*=-1;
		x += dirX;
	}	

	if (y == m_iniPantallaY || y == m_fiPantallaY -m_midaBolaY)
		dirY*=-1;	
				 	
}
//-----------------------------------------
// mouVaus
// in: x posicio vaus x, pasvausx direccio i mida moviment vaus (positiu o negatiu en eix x)
// out: nova posicio x de vaus
//-----------------------------------------
/*int mouVaus(int x, int dir)
{
	int xNew; 
	xNew = x+dir;

	return xNew;	
}*/

//-----------------------------------------
// inicialitzarJoc
// in:res
// out: posicio vaus en x vausX, posicio bola (bolaX, bolaY), direccio del moviment de la bola (dirX, dirY)
// la posicio de vaus en x es tria de forma aleatoria en un nombre entre INIPANTALLA i FIPANTALLA-MIDAVAUSX
// com vaus es mou de pasvauxX en pausvausx posicions hem de triar multiples d'aquest nombre.
// la posicio de bolaX es la mateixa que la de vaus i la seva direccio en x es tria aleatoria entre -1 0 i 1
// la posicio en y de vaus es fixe i la de la bola inicial es a sobre de vaus. la direccio de vaus en y es cap adalt -1
//-----------------------------------------
void inicialitzarJoc(Bola bola, Vaus vaus)
{
	// Inicialització de la posició de la vaus i la bola
	// Vaus es mou PASVAUSX posicions. Inici esta a multiple de PASVAUSX+INIPANTALLAX

	// vausX = aleatori(m_iniPantallaX, m_fiPantallaX - m_midaVausX, m_pasVausX);
	vaus.setXY(aleatori(m_iniPantallaX, m_iniPantallaX - m_midaVausX, m_pasVausX), m_fiPantallaY); //VAUS Y= m_fiPantallaY- m_midaVausY

	//bolaX  = vausX; 
	//bolaY  = m_fiPantallaY - m_midaVausY;

	bola.setXY(vaus.getX(), m_fiPantallaY - m_midaVausY);



	//dirX = aleatori(-1, 1, 1);

	bola.setDirX(aleatori(-1, 1, 1));


	bola.setDirY(-1);
	//dirY = -1;
}

//-----------------------------------------
// rebotBolaVaus:segons en quina posicio de vaus rebota la bola ho fa amb una inclinacio o una altre.
// Als extrems es mes inclinada -2 o 2 segons sigui a l esquerra o la dreta, si es mes centrada es -1 i 1 i si es al centre es 0
// in: posicio en x de vausX, i bolaX, aquesta funcio es crida quan ja es sap que vaus i la bola han colisionat
// out: la nova direccio en x de la bola
//-----------------------------------------
/*
int rebotBolaVaus(int vausX, int bolaX)
{
	int aux = (vausX - bolaX) / 10;
	int novaDirX;

	if (aux >= -1)
		novaDirX = -2;
	else if (aux >= -3)
		novaDirX = -1;
	else if (aux >= -5)
		novaDirX = -0;
	else if (aux >= -7)
		novaDirX = 1;
	else if (aux >= -9)
		novaDirX = 2;

	return novaDirX;
}*/

void initScale()
{
	//POSICIONS MARCADORS
	m_iniPuntsX= INIPUNTSX*scale;
	m_iniPuntsY= INIPUNTSY*scale;
	m_iniVidesX= INIVIDESX*scale;
	m_iniVidesY= INIVIDESY*scale;
	m_iniNivellX= ININIVELLX*scale;
	m_iniNivellY= ININIVELLY*scale;
	m_pasDigit = PASDIGIT*scale;

	//Mida i nombre maons mur
	m_midaMaoX = MIDAMAOX*scale;
	m_midaMaoY = MIDAMAOY*scale;
	
	// Mida Pantalla
	m_midaX= MIDAX*scale;
	m_midaY= MIDAY*scale;

	//========================================================================
	// Inici del taulell respecte la cantonada superior esquerre
	m_iniPantallaX= INIPANTALLAX*scale;
	m_iniPantallaY= INIPANTALLAY*scale;

	//========================================================================
	// Fi del taulell respecte la cantonada inferior dreta
	m_fiPantallaX= FIPANTALLAX*scale;
	m_fiPantallaY= FIPANTALLAY*scale;

	// Fi del taulell respecte la cantonada inferior dreta
	m_fiPantallaX= FIPANTALLAX*scale;
	m_fiPantallaY= FIPANTALLAY*scale;

	//Mides i pas de bola
	m_midaBolaX= MIDABOLAX*scale;
	m_midaBolaY= MIDABOLAY*scale;

	m_pasBolaX= PASBOLAX*scale;
	m_pasBolaY= PASBOLAY*scale;
	//Mides i pas de VAUS
	m_midaVausX = MIDAVAUSX*scale;
	m_midaVausY= MIDAVAUSY*scale;

	m_pasVausX= PASVAUSX*scale;

}
//-----------------------------------------
// joc: porta el control de tot el joc, pantalles, vides etc
// ara nomes acaba si perdem totes les vides (3) perque no tenim el mur
// quan tinguem el mur al destruir-la tota ens augmentara el nivell i ens donara punts
// in: nivell: segons sigui mes alt la bola anira mes depressa
//-----------------------------------------
int joc(int nivell,bool baixares)
{
	// ********************************************
	// Inicialització de la part gràfica del joc
	// *******************************************
	//Inicialitza Part grafica

	if (baixares)
		scale = 0.8;
	else
		scale = 1;
	initScale();

	Game jocLib(m_midaX, m_midaY);
	// Inicialitzacions necessàries
	

	jocLib.Init();
	

	// Assignacio del grafic del fons
	// Veiem dues maneres d'assignar una imatge.
	// Aqui primer la definim i despres li assignem una imatge
	Sprite fons;
	fons.Create("data/fons.png");
	fons.SetScale(scale);
	
	// Assignacio del grafic de la nau vaus
	// Aqui directament definim i assignem una imatge
	/*Sprite vaus("data/vaus.png");
	vaus.SetScale(scale);
	int vausX;*/

	Vaus vaus;
	vaus.init();
	vaus.SetScale(scale);//NEW



	//Assignacio del grafic de la pilota
	/*Sprite bola("data/bola.png");
	bola.SetScale(scale);
	int bolaX, dirX;
	int bolaY, dirY; */
	Bola bola;
	bola.init();
	bola.SetScale(scale);//NEW


	// *****************************************************************************
	// PER AFEGIR: Crear gràfic pels maons i inicialitzar estructura per guardar mur
	// *****************************************************************************

	Sprite mao;
	mao.Create("data/maoGroc.png");

	int mur[MAXMAONSX];

	////////////////////////////////////////////////////////
	//Definicio dels digits per pintar per pantalla resultats
	digits[0].Create("data/numeros/numero0000.png");
	digits[1].Create("data/numeros/numero0001.png");
	digits[2].Create("data/numeros/numero0002.png");
	digits[3].Create("data/numeros/numero0003.png");
	digits[4].Create("data/numeros/numero0004.png");
	digits[5].Create("data/numeros/numero0005.png");
	digits[6].Create("data/numeros/numero0006.png");
	digits[7].Create("data/numeros/numero0007.png");
	digits[8].Create("data/numeros/numero0008.png");
	digits[9].Create("data/numeros/numero0009.png");

	for (int i = 0; i < 10; i++)
	{
		digits[i].SetScale(scale);
	}


	// ************************************************************
	// Inicialitzacions dels paràmetres del joc
	// ************************************************************
	int velocitatJoc = INITVELOCITATJOC;
	int contVBola;
	int vides = INITVIDES;
	int punts = INITPUNTS;

	//Inizialitzar llavor per a la funció rand()
	srand((unsigned)time(NULL));


	// ****************************************************************************
	// Bucle principal del joc
	// Hi ha dos bucles anidats: l'exterior controla tota la partida mentre que 
	// l'interior controla un nivell del joc fins que ens quedem sense vides
	// *****************************************************************************
	do{
		// *************************************************************************
		// Inicialització de la posició de la nau i de la bola i dels gràfics
		// ************************************************************************
		inicialitzarJoc(bola,vaus);
		// ***********************************************************************
		// PER AFEGIR: Inicialitzar estructura mur
		for (int i = 0; i < MAXMAONSX; i++)  mur[i] = 1;
		// ***********************************************************************
		//Mostrem finestra
		jocLib.Video_ShowWindow();
	
		//Pintem Fons
		fons.Draw(0,0);
		//Pintem vaus
		vaus.draw();
		//Pintem Pilota
		bola.draw();
		// ***********************************************************************
		// PER AFEGIR: Dibuixar mur
		for (int i = 0; i < MAXMAONSX; i++)
		{
			if (mur[i] == 1)
			{
			
				mao.Draw(m_iniPantallaX + i*m_midaMaoX, m_iniPantallaY);
			}
		}
		// ***********************************************************************
		// Pintem marcadors
		m_iniPuntsX = m_iniPuntsX;

		drawNombre(punts, m_iniPuntsX, m_iniPuntsY);
		drawNombre(vides, m_iniVidesX, m_iniVidesY);
		drawNombre(nivell, m_iniNivellX, m_iniNivellY);

		// Actualitza la pantalla i ara veiem tot el que hem pintat
		jocLib.VideoUpdate();

		// Inicialització de variable que permet indicar velocitat de la bola segons nivell
		// quan contbola arriba a zero permet moure la bola. aixo deixa temps per moure la vaus.
		contVBola = velocitatJoc/nivell;

		do
		{
			// ******************************************************************
			// Captura i processa les tecles que s'hagin pressionat
			// ******************************************************************

			// Captura els events que s'han produit en el darrer cicle
			jocLib.ProcessEvents();

			// Captura del moviment de la nau vaus fet pel jugador
			if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
			{
				//si hem donat a fletxa esquerra nou la vaus a esquerra si no sortim de tauler
				/*if (vausX >= m_iniPantallaX + m_pasVausX)
					vausX = mouVaus(vausX, -m_pasVausX);*/

				if (vaus.getX() >= INIPANTALLAX + PASVAUSX)
					vaus.mouLeft(INIPANTALLAX);

			}
			else if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
			{
				//si hem donat a fletxa dreta nou la vaus a dreta si no sortim de tauler
				/*if (vausX <= m_fiPantallaX - (m_midaVausX + m_pasVausX))
				vausX = mouVaus(vausX, m_pasVausX);*/
				
				
				if (vaus.getX() <= m_fiPantallaX - (m_midaVausX + m_pasVausX))
					vaus.mouRight(m_fiPantallaX);
			}


			// ********************************************************************************
			// PER AFEGIR: Comprovar si s'ha pressionat la tecla ESPAI per fer una pausa al joc
			// Recordeu que s'ha de fer un jocLib.ProcessEvents(); cada cop que voleu llegir events de teclat
			// ********************************************************************************
			else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
			{
				jocLib.ProcessEvents();
				while (!Keyboard_GetKeyTrg(KEYBOARD_SPACE))
					jocLib.ProcessEvents();
			}
			// ********************************************************************************
			// MOVIMENT DE LA BOLA
			// ********************************************************************************
			// Moviment de la pilota amb retard respecte la nau, controlat per contVBola
			contVBola--;
			if(!contVBola)
			{
				// movem la bola segons dirX i dirY controlant marges
				//mouBola(bolaX, bolaY, dirX, dirY);
				bola.mou(m_iniPantallaX, m_fiPantallaX, m_iniPantallaY, m_fiPantallaY);
				
				

				//posa comptador una altra vegada a inici per poder moure vaus
				contVBola = velocitatJoc/nivell;
			
				// ******************************************************************************
				// PER MODIFICAR: Quan tinguem el mur s'haurà de comprovar si la bola toca el mur
				// i si és així, mirar si destrueix algun dels blocs
			


				


				// ******************************************************************************
				// Comprovem si la bola arriba al límit superior del tauler
				
				/*if(bolaY == m_iniPantallaY)
				{
				// sumem un punt si toquem al marge superior
				// aixo canviara quan tinguem el mur, nomes suma si derruim mao
				punts += 1;
				}*/
				
				if (bola.getY() <= m_iniPantallaY + m_midaMaoY)
				{

					bola.changeDirY();
					for (int i = 0; i < m_midaMaoX; i++)
					{

						int LimiteIzquierda = m_iniPantallaX + i*m_midaMaoX;		////////////////////////////////
						int LimiteDerecha = m_iniPantallaX + (i + 1)*m_midaMaoX;	 ////////////////////////////////////////

						if (bola.getX() > LimiteIzquierda && bola.getX() < LimiteDerecha)
						{
							mur[i] = 0;
						}
					}
					// sumem un punt si toquem al marge superior
					// aixo canviara quan tinguem el mur, nomes suma si derruim mao
					punts += 1;
				}
			
				// Comprovem si la bola arriba al límit inferior de la pantalla i, en aquest cas
				// si rebota a la nau o s'escapa i perdem una vida
				/*if(bolaY == m_fiPantallaY-m_midaBolaY)
				{
				if(bolaX < vausX-m_midaBolaX || bolaX > vausX+m_midaVausX+m_midaBolaX)
				{
				vides--;
				inicialitzarJoc(bola,vaus);
				}
				else
				{
				bola.setDirX = rebotBolaVaus(vaus.getX(), bola.getX());
				}
				}*/

				if (bola.getY() == m_fiPantallaY - m_midaBolaY) 

				{
					if (bola.getX() < vaus.getX() - m_midaBolaX || bola.getX() > vaus.getX() + m_midaVausX + m_midaBolaX)
					{
						vides--;
						inicialitzarJoc(bola, vaus);

					}
					else
					{
						bola.changeDirX();
						//dirX = rebotBolaVaus(vaus.getX, bola.getX);////////////////////////////////////////////////////////////////////////////////////////////
					}
				}


				// **************************************************************************
				// PER AFEGIR: Comprovar si s'ha destruit el mur. En aquest cas, sumar punts,
				// crear de nou el mur i canviar de nivell
				// **************************************************************************
			}
		
			// ***********************************************************************
			// Dibuixar tots els gràfics del joc
			// ***********************************************************************
			//Pintem Fons
			fons.Draw(0, 0);
			//Pintem Vaus
			vaus.draw();
			//Pintem bola
			bola.draw();
			//Pintem Marcadors
			// ***********************************************************************
			// PER AFEGIR: Dibuixar mur

			for (int i = 0; i < MAXMAONSX; i++)
			{
				if (mur[i] == 1)
				{
					
					mao.Draw(m_iniPantallaX + i*m_midaMaoX, m_iniPantallaY);
				}
			}
			// ***********************************************************************
			drawNombre(punts, m_iniPuntsX, m_iniPuntsY);
			drawNombre(vides, m_iniVidesX, m_iniVidesY);
			drawNombre(nivell, m_iniNivellX, m_iniNivellY);

			// Actualitza la pantalla
			jocLib.VideoUpdate();
		
			// ***********************************************************************
			// Sortirem del primer bucle si pressionem ESC o ens quedem sense vides
			// ***********************************************************************
		}while( (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)) && (vides>0)); 
		// ********************************************************************************
		// PER AFEGIR: Sortirem del bucle també si s'ha destruit tot el mur. En aquest cas
		// incrementarem de nivell
		// *********************************************************************************

		// *********************************************************************************
		// Sortirem del segon bucle quan haguem superat tots els nivells, pressionem ESC
		// o ens quedem sense vides
		// *********************************************************************************
	}while((nivell<4) && (vides>0) && (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)));
	
	system("PAUSE");

	return punts;
}
