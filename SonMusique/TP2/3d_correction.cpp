/*==============================================================================
Event 3D Example
Copyright (c), Firelight Technologies Pty, Ltd 2012-2014.

This example demonstrates how to position events in 3D for spatialization.
==============================================================================*/
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "common.h"
#include <ctime>

// Plateau de jeu = tableau de caractères

const int SCREEN_WIDTH = NUM_COLUMNS;
const int SCREEN_HEIGHT = 16;
char screenBuffer[(SCREEN_WIDTH + 1) * SCREEN_HEIGHT + 1] = {0};
void initializeScreenBuffer();
void actualiseAffichage() ;

// Pépite = position (x,z)
// pos_vers_index : traduction des coordonnées (x,z) en indice dans le tableau du plateau.

typedef struct {int x, z;} Tpos ;
int pos_vers_index(Tpos p) ;
Tpos pepite ;
bool yapepite = false ;
void creePepite () ;

// Serpent = tableau de positions (x,z)

typedef struct {Tpos tabPos[SCREEN_WIDTH*SCREEN_HEIGHT]; int longueur;} Tsnake ;
Tsnake snake ;
void initSnake () ;

// Direction du serpent

typedef enum {HAUT, BAS, GAUCHE, DROITE} Tdirection ;
Tdirection direction=DROITE ;

// Déroulement du jeu : fonctions déclenchées en cas de gain et de perte, 
// tests de collision avec un mur ou la queue du serpent, d'ingestion de pépite,
// période d'actualisation de la position du serpent (en secondes),
// progression du serpent d'un cran

bool gagne=false ;
bool perdu=false ;
bool dansLeMur() ;
bool dansLaQueue() ;
bool mangePepite(Tpos tete) ;
float bpm = 80.0f ;
float periode = 60/(2*bpm) ;
void avanceSnake() ;
void actualisePositions(FMOD_3D_ATTRIBUTES *L, FMOD_3D_ATTRIBUTES *E) ;


// Corps des fonctions

int FMOD_Main()
{
	double temps, tempsGrille ;
    void *extraDriverData = NULL;
    FMOD_STUDIO_PLAYBACK_STATE encours ;
	
	/* INITIALISATION DU MOTEUR AUDIO */

    Common_Init(&extraDriverData);

    FMOD::Studio::System* system = NULL;
    ERRCHECK( FMOD::Studio::System::create(&system) );

    // The example Studio project is authored for 5.1 sound, so set up the system output mode to match
    FMOD::System* lowLevelSystem = NULL;
    ERRCHECK( system->getLowLevelSystem(&lowLevelSystem) );
	ERRCHECK( lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0) );

    ERRCHECK( system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL|FMOD_3D_WORLDRELATIVE, extraDriverData) );

	/* CHARGEMENT DES BANQUES DE SONS */

	FMOD::Studio::Bank* masterBank = NULL;
    ERRCHECK( system->loadBankFile(Common_MediaPath("Master Bank.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );
    
	FMOD::Studio::Bank* stringsBank = NULL;
    ERRCHECK( system->loadBankFile(Common_MediaPath("Master Bank.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );
    
	/* CHARGEMENT DES EVENEMENTS DE LA BANQUE PRINCIPALE */

    FMOD::Studio::EventDescription* eventDescription = NULL;
    FMOD::Studio::EventInstance *evDebut=NULL, *evMusique=NULL, *evSerpent=NULL, *evPepite=NULL, *evFin=NULL;
    FMOD::Studio::ParameterInstance *Pbpm=NULL, *Plongueur=NULL, *Pyapepite=NULL, *Pgagne=NULL;

	/* (... CREATION D'UNE INSTANCE POUR CHAQUE EVENEMENT DU PROJET ...) */
	/* (... AFFECTATION DE VARIABLES PERMETTANT DE PILOTER CES INSTANTCE ...) */

	ERRCHECK( system->getEvent("event:/Debut de partie", &eventDescription) );
    ERRCHECK( eventDescription->createInstance(&evDebut) );

	ERRCHECK( system->getEvent("event:/Musique", &eventDescription) );
    ERRCHECK( eventDescription->createInstance(&evMusique) );
    ERRCHECK( evMusique->getParameter("bpm", &Pbpm) );
    ERRCHECK( Pbpm->setValue(80) );
	ERRCHECK( evMusique->start() );

	ERRCHECK( system->getEvent("event:/Serpent", &eventDescription) );
    ERRCHECK( eventDescription->createInstance(&evSerpent) );
    ERRCHECK( evSerpent->getParameter("Longueur", &Plongueur) );

	ERRCHECK( system->getEvent("event:/Pepite", &eventDescription) );
    ERRCHECK( eventDescription->createInstance(&evPepite) );
    ERRCHECK( evPepite->getParameter("Yapepite", &Pyapepite) );

	ERRCHECK( system->getEvent("event:/Fin de partie", &eventDescription) );
    ERRCHECK( eventDescription->createInstance(&evFin) );
    ERRCHECK( evFin->getParameter("Gagne", &Pgagne) );

	tempsGrille = clock() / (double)CLOCKS_PER_SEC ;

	initSnake() ;
    ERRCHECK( Plongueur->setValue(1) );
	creePepite() ;
    ERRCHECK( Pyapepite->setValue(1) );
	actualiseAffichage() ;

	ERRCHECK( evDebut->start() );

	// Attributs 3D des différentes sources

	FMOD_3D_ATTRIBUTES attributes = { { 0 } };
	attributes.up.y = 1.0f ;

	FMOD_3D_ATTRIBUTES pepiteAttributes=attributes, listenerAttributes=attributes ;

	actualisePositions(&listenerAttributes,&pepiteAttributes) ;

	/* (... ACTUALISATION DES ATTRIBUTS 3D DES EVENEMENTS (voir fonction actualisePositions) ...) */
	/* (... SIGNALEMENT DES NOUVEAUX ATTRIBUTS AU SYSTEME AUDIO ET AUX INSTANCES DES EVENEMENTS ...) */
	/* (... DEMARRAGES AUDIO DU SERPENT ET DE LA PEPITE ...) */

	ERRCHECK( system->setListenerAttributes(&listenerAttributes) );
	ERRCHECK( evSerpent->set3DAttributes(&listenerAttributes) );
	ERRCHECK( evPepite->set3DAttributes(&pepiteAttributes) );

	ERRCHECK( evSerpent->start() );
	ERRCHECK( evPepite->start() );

	ERRCHECK( system->update() );

    do
    {
        Common_Update();
        
        if (Common_BtnPress(BTN_LEFT))			direction = GAUCHE ;
        if (Common_BtnPress(BTN_RIGHT))			direction = DROITE ;
        if (Common_BtnPress(BTN_UP)) 			direction = HAUT ;        
        if (Common_BtnPress(BTN_DOWN)) 			direction = BAS ;

        Common_Draw("==================================================");
        Common_Draw("Event 3D Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2014-2014.");
        Common_Draw("==================================================");
        Common_Draw(screenBuffer);
        Common_Draw("Use the arrow keys (%s, %s, %s, %s) to control the event position", 
            Common_BtnStr(BTN_LEFT), Common_BtnStr(BTN_RIGHT), Common_BtnStr(BTN_UP), Common_BtnStr(BTN_DOWN));
		Common_Draw("Press %s to quit",Common_BtnStr(BTN_QUIT));

        Common_Sleep(50);

		temps = clock() / (double)CLOCKS_PER_SEC ;

		if (temps - tempsGrille > periode)
		{
			while (temps - tempsGrille > periode)
				tempsGrille += periode ;

			avanceSnake() ;
			/* (... PILOTAGE DU SON DU SERPENT AVEC LE PARAMETRE Plongueur ...) */
			ERRCHECK(Plongueur->setValue((float)snake.longueur)) ;

			if (snake.longueur == 5) gagne = true ;
			else if (dansLeMur() || dansLaQueue())
				perdu = true ;
			else
			{
				/*  (... PILOTAGE DU SON DE LA PEPITE AVEC LE PARAMETRE Pyapepite ...) */
				ERRCHECK(Pyapepite->setValue(yapepite?1.0f:0.0f)) ;

				ERRCHECK( system->update() );

				if (!yapepite) 
				{
					creePepite() ;

					/*  (... PILOTAGE DU SON DE LA PEPITE AVEC LE PARAMETRE Pyapepite ...) */
					ERRCHECK(Pyapepite->setValue(yapepite?1.0f:0.0f)) ;

					bpm += 20 ;
					periode = 60/(2*bpm) ;
					/*  (... PILOTAGE DU RYTHME MUSICAL AVEC LE PARAMETRE Pbpm ...) */
				    ERRCHECK(Pbpm->setValue(bpm)) ;
				}

				/* (... ACTUALISATION DES PARAMETRES 3D (VOIR CI-DESSUS) ...) */
				actualisePositions(&listenerAttributes,&pepiteAttributes) ;
				ERRCHECK( system->setListenerAttributes (&listenerAttributes) );
				ERRCHECK( evSerpent->set3DAttributes(&listenerAttributes) );
				ERRCHECK( evPepite->set3DAttributes(&pepiteAttributes) );

				ERRCHECK( system->update() );

				actualiseAffichage();
			}
		}

	} while (!Common_BtnPress(BTN_QUIT) && !perdu && !gagne);

	/* (... ARRET DES SONS EN COURS ... ) */
	ERRCHECK(evMusique->stop(FMOD_STUDIO_STOP_IMMEDIATE));
	ERRCHECK(evSerpent->stop(FMOD_STUDIO_STOP_IMMEDIATE));
	ERRCHECK(evPepite->stop(FMOD_STUDIO_STOP_IMMEDIATE));

	/* (... PILOTAGE DU SON DE FIN AVEC LE PARAMETRE Pgagne ...) */
	if (gagne)
	    ERRCHECK( Pgagne->setValue(1) );
	else if (perdu)
	    ERRCHECK( Pgagne->setValue(0) );
	/* (... DEMARRAGE DU SON DE FIN ...) */
	ERRCHECK( evFin->start() );

	ERRCHECK( system->update() );
	Common_Sleep(50) ;

	/* (... MAINTIEN DU JEU TANT QUE LE SON DE FIN N'EST PAS TERMINE ...) */
	do
	{
		evFin->getPlaybackState(&encours) ;
		if (encours==FMOD_STUDIO_PLAYBACK_PLAYING) Common_Sleep(50) ;
	} while(encours==FMOD_STUDIO_PLAYBACK_PLAYING) ;

    ERRCHECK( system->release() );

    Common_Close();

    return 0;
}

void actualisePositions(FMOD_3D_ATTRIBUTES *L, FMOD_3D_ATTRIBUTES *E)
{
	float  r1 = (float)(snake.tabPos[0].x - pepite.x), r2 = (float)(snake.tabPos[0].z - pepite.z) ;
	float  r = sqrt(r1*r1 + r2*r2) ;
	float  V = 1.0f / periode ;

	/* (... REMPLACER LES 0 PAR LES VALEURS REELLES ...) */
	E->position.x = (float)pepite.x;
    E->position.z = (float)pepite.z;
	E->forward.x = r1/r ;
	E->forward.z = r2/r ;

	switch (direction)
	{
		case DROITE : L->forward.x =  1.0f; L->forward.z =  0.0f; L->velocity.x =    V; L->velocity.z = 0.0f; break ;
		case GAUCHE : L->forward.x = -1.0f; L->forward.z =  0.0f; L->velocity.x =   -V; L->velocity.z = 0.0f; break ;
		case HAUT   : L->forward.x =  0.0f; L->forward.z =  1.0f; L->velocity.x = 0.0f; L->velocity.z =    V; break ;
		case BAS    : L->forward.x =  0.0f; L->forward.z = -1.0f; L->velocity.x = 0.0f; L->velocity.z =   -V; break ;
	}

	L->position.x = (float)snake.tabPos[0].x ;
	L->position.z = (float)snake.tabPos[0].z ;
}

void initSnake ()
{
	snake.longueur=1 ;
	snake.tabPos[0].x=0 ;
	snake.tabPos[0].z=0 ;
}

void creePepite ()
{
	Tpos pepiteTmp ;
	int i ;

	do
	{
		pepiteTmp.x=rand()% SCREEN_WIDTH - SCREEN_WIDTH/2 ;
		pepiteTmp.z=rand()% SCREEN_HEIGHT  - SCREEN_HEIGHT/2 ;
		i = 0 ;
		while (i<snake.longueur && (snake.tabPos[i].x!=pepiteTmp.x || snake.tabPos[i].z!=pepiteTmp.z))
			i++ ;
	}
	while (i<snake.longueur || pos_vers_index(pepiteTmp)==-1) ;
	
	pepite=pepiteTmp ;
	yapepite = true ;
}

bool dansLeMur()
{
	Tpos tete = snake.tabPos[0] ;
	return (tete.x < -SCREEN_WIDTH/2 + 1) || (tete.x > SCREEN_WIDTH/2 - 2) || (tete.z < -SCREEN_HEIGHT/2 + 1) || (tete.z > SCREEN_HEIGHT/2 - 1) ;
}

bool dansLaQueue()
{
	int i=1 ;
	Tpos tete = snake.tabPos[0] ;
	while (i<snake.longueur && (tete.x != snake.tabPos[i].x || tete.z != snake.tabPos[i].z))
		i++ ;
	return (i<snake.longueur) ;
}

bool mangePepite (Tpos tete)
{
	return (tete.x == pepite.x)&&(tete.z == pepite.z) ;
}

void avanceSnake ()
{
	Tpos tete = snake.tabPos[0] ;
	switch (direction)
	{
		case BAS    : tete.z -- ; break ;
		case HAUT   : tete.z ++ ; break ;
		case GAUCHE : tete.x -- ; break ;
		case DROITE : tete.x ++ ; break ;
	}
	if (mangePepite(tete))
	{
		snake.longueur ++ ;
		yapepite = false ;
	}
	for (int i=snake.longueur-1 ; i>0 ; i--)
		snake.tabPos[i]=snake.tabPos[i-1] ;
	snake.tabPos[0]=tete ;
}

int pos_vers_index(Tpos p)
{
    int row = -p.z + (SCREEN_HEIGHT / 2);
	int col =  p.x + (SCREEN_WIDTH  / 2);
    
    if (0 < row && row < SCREEN_HEIGHT && 0 < col && col < SCREEN_WIDTH)
    {
        return (row * (SCREEN_WIDTH + 1)) + col;
    }
    
    return -1;
}

void initializeScreenBuffer()
{
    memset(screenBuffer, ' ', sizeof(screenBuffer));

    int idx = SCREEN_WIDTH;
    for (int i = 0; i < SCREEN_HEIGHT; ++i)
    {
        screenBuffer[idx] = '\n';
        idx += SCREEN_WIDTH + 1;
    }

    screenBuffer[(SCREEN_WIDTH + 1) * SCREEN_HEIGHT] = '\0';
}

void actualiseAffichage()
{
	initializeScreenBuffer() ;

	for (int i=0 ; i<snake.longueur ; i++)
		screenBuffer[pos_vers_index(snake.tabPos[i])]='x' ;
	screenBuffer[pos_vers_index(pepite)]='o' ;

}
