/*!
  * \file SpaceInvader_AC.cpp
  * \author Alain Casali Marc Laporte
  * \date 7 janvier 2016
  * \brief Projet de C++ simulant un SpaceInvader
  * \version 1.0
  * \bug Aucun connu
  */

#include <unistd.h>


#include <iostream>
#include <fstream>
#include <cstdlib> //rand ()
#include <ctime> //time ()
#include <termios.h> //termios
#include <cstdio> // getchar
#include <iomanip>
#include "MyType_AC.h"
#include "SpaceInvader_AC.h"
#include "MyConst_AC.h"
#include "nsutil.h"

using namespace std;
using namespace nsSpaceInvader_AC;

namespace nsSpaceInvader_AC
{
unsigned score;
unsigned vies;


void HighScore(unsigned score, const string & file)
{
    ifstream fichier(file);
    unsigned val;
    string name;
    vector <string> names;
    vector <unsigned> scores;

    // Test si fichier existe, sinon le cree
    if (!fichier)
    {
        ofstream f(file);
        // Initialise avec un score à 0
        f << ".................." << " " << 0 << endl;
        f.close();
    }
    fichier.close();

    // Lecture du fichier
    fichier.open(file);
    while(!fichier.eof())
    {
        fichier >> name;
        fichier >> val;
        names.push_back(name);
        scores.push_back(val);
    }
    // efface la derniere ligne lue (endl)
    names.pop_back();
    scores.pop_back();

    fichier.close();

    // Si score dans highscore alors on demande le nom du gagnant
    if (scores.size() < 10 || score > scores[scores.size()-1])
    {
        // Insertion du nom du gagnant dans le tableau
        cout << "Entrez votre nom : ";
        cin >> name;

        names.push_back(name);
        scores.push_back(score);

        // tri du tableau
        unsigned maxpos, max;
        for (unsigned i=0; i < names.size(); i++)
        {
            max = scores[i];
            for (unsigned j=i+1; j < names.size(); j++)
            {
                if (scores[j] > max)
                {
                    max= scores[j];
                    maxpos = j;
                }
                if (max != scores[i])
                {
                    swap(scores[i], scores[j]);
                    swap(names[i], names[j]);
                }
            }
        }

        // Ecriture du fichier du nouveau tableau
        ofstream f(file);
        cout << "----------------------------------------" << endl;
        cout << "High score" << endl << endl;

        for (unsigned i=0; (i < names.size()) && i < 10; i++)
        {
            if (i==0)
            {
                Couleur (KYellow);
            }
            cout << i+1 << setw(20) << names[i] << setw(10) << scores[i] << endl;
            Couleur (KReset);
            f << names[i] << " " << scores[i] << endl;
        }
    }
}

void AfficheScore()
{
    cout << "Score" << setw(KSizeSpace-3) << "Vies" << endl;
    cout << score << setw(KSizeSpace+2-to_string(score).size()) << vies << endl;
}

void Couleur (const string & Coul)
{
    cout << "\033[" << Coul <<"m";
} //Couleur ()

void ClearScreen ()
{
    cout << "\033[H\033[2J";
}

void PutCVPosition (const CVPosition & VPos, char Car, CVString & Space)
{
    for (const CPosition & Pos : VPos)
        Space[Pos.first][Pos.second] = Car;
}// PutCVPosition ()

void PutAllObjects (const CAObject & Obj, CVString & Space)
{
    for (string & Line : Space) Line = KEmptyLine;
    PutCVPosition (Obj[0], KInsideInvader, Space);
    PutCVPosition (Obj[1], KMissile, Space);
    PutCVPosition (Obj[2], KInsideMe, Space);
    PutCVPosition (Obj[3], KTorpedo, Space);
}// PutAllObjects ()

void DisplaySpace (const CVString & Space)
{
    ClearScreen();
    AfficheScore();
    cout << string (Space[0].size() + 2, '-') << endl;
    for (const string & Line : Space)
    {
        cout <<'|';
        for (const char Cel : Line)
        {
            switch (Cel)
            {
            case KInsideInvader:
            case KMissile:
                Couleur (KInvadersColor);
                break;
            case KInsideMe:
            case KTorpedo:
                Couleur (KMyColor);
            }
            cout << Cel;
            Couleur (KReset);
        }
        cout <<'|';
        cout << endl;
    }
    cout << string (Space[0].size() + 2, '-') << endl;
}// DisplaySpace2 ()

void InitSpace (CVString & Space, CAObject & Obj)
{
    //l'espace de jeu
    Space.resize(KSizeLine);
    for (string & Line : Space)
        Line = KEmptyLine;
    //les envahisseurs
    Obj[0].resize(KInvadersSize);
    for (unsigned i (0); i < Obj[0].size (); ++i)
        Obj[0][i] = make_pair (0, i + KBegInvader);

    //moi
    Obj[2].resize(KMySize);
    for (unsigned i(0); i < Obj[2].size(); ++i)
        Obj[2][i] = make_pair (Space.size () -1, KBegMe +i);
} //InitSpace ()


void MaxX (const CVPosition & VPos, CPosition & MaxPos)
{
    MaxPos = VPos [0];
    for (unsigned i (1); i < VPos.size(); ++i)
        if (MaxPos.second < VPos[i].second)
            MaxPos = VPos[i];
}// MaxX ()

void MaxY (const CVPosition & VPos, CPosition & MaxPos)
{
    MaxPos = VPos [0];
    for (unsigned i (1); i < VPos.size(); ++i)
        if (MaxPos.first < VPos[i].first)
            MaxPos = VPos[i];
} // MaxY ()


void MinX (const CVPosition & VPos, CPosition & MinPos)
{
    MinPos = VPos [0];
    for (unsigned i (1); i < VPos.size(); ++i)
        if (MinPos.second > VPos[i].second)
            MinPos = VPos[i];
}// MinX ()

bool MoveLeft (CVPosition & VPos)
{
    CPosition MinPos;
    MinX (VPos, MinPos);
    if (0 == MinPos.second) return false;
    for (CPosition & Pos : VPos)
        -- Pos.second;
    return true;
} // MoveLeft ()

bool MoveRight (CVPosition & VPos)
{
    CPosition MaxPos;
    MaxX (VPos, MaxPos);
    if (KSizeSpace-1 == MaxPos.second) return false;

    for (CPosition & Pos : VPos)
        ++ Pos.second;
    return true;
} //MoveRight ()

void MoveDown (CVPosition & VPos)
{
    for (CPosition & Pos : VPos)
        ++ Pos.first;
}// MoveDown ()

void MoveUp (CVPosition & VPos)
{
    for (CPosition & Pos : VPos)
        -- Pos.first;
} //MoveUp ()

void ManageMe (CAObject &Obj)
{
    char Move;
    //fonction en C qui permet de lire un caractère. cin ne fonctionnant pas dans cette configuration
    //cin >> Move;
    read (STDIN_FILENO, &Move, 1);
    switch (Move)
    {
    case KLeft:
        MoveLeft (Obj[2]);
        break;
    case KRight :
        MoveRight (Obj[2]);
        break;
    case KShoot:
        Obj[3].push_back(Obj[2][rand () % Obj[2].size ()]);
        break;
    }
}// ManageMe ()

void ManageInvaders (CAObject &Obj, unsigned & Direction, unsigned & WhatInvaderDo)
{
    //on decide de ce qu'on fait
    //la on bouge l'invader
    if (WhatInvaderDo++ != KMissileRatio)
    {
        switch (Direction)
        {
        case 0:
            if (!MoveRight(Obj[0]))
            {
                MoveDown(Obj[0]);
                ++Direction;
            }
            break;
        case 1:
            if (!MoveLeft(Obj[0]))
            {
                MoveDown(Obj[0]);
                Direction = 0;
            }
        }
    }
    //sinon on lance un missile d'une des cases en dessous de l'invader
    //peut importe ou
    else
    {
        Obj[1].push_back(Obj[0][rand () % Obj[0].size ()]);
        WhatInvaderDo = 0;
    }
}// ManageInvaders ()

void CollisionBetweenObjectsAndShips (CVPosition & Objects, CVPosition & StarShips, const bool countScore)
{
    for (unsigned i (0); i < Objects.size (); ++i)
    {
        //collision entre les missiles et moi
        for (unsigned j (0); j < StarShips.size (); )
        {
            if (Objects[i] == StarShips[j])
            {
                if (countScore == true)
                {
                    score = score+10;
                }
                StarShips.erase (StarShips.begin () +j);
                Objects.erase (Objects.begin () +i);

            }
            else ++j;
        }
    }
}//CollisionBetweenMissilesAndI ()

void CollisionBetweenMissilesAndTorpedos (CVPosition & Missiles, CVPosition & Torpedos)
{
    //la boucle est un peu bizare, mais elle permet de gérer
    //deux colisions en même temps entre deux missiles et torpilles
    //sur deux case differentes
    //tout ça à cause du .erase () qui supprime la case courante
    //=> on ne doit pas incrementer l'indice de boucle dans ce cas

    for (unsigned i (0); i < Missiles.size (); )
    {
        //collision entre les missiles et les torpilles
        unsigned j (0);
        for (; j < Torpedos.size (); ++j)
        {
            if (Missiles[i] != Torpedos[j]) continue;
            score = score+1;
            Torpedos.erase (Torpedos.begin () +j);
            Missiles.erase (Missiles.begin () +i);
            break;
        }

        if (j == Torpedos.size ()) ++i;
    }
}//CollisionBetweenMissilesAndTorpedos ()

void ManageCollisions (CAObject & Obj)
{
    CollisionBetweenMissilesAndTorpedos (Obj[1], Obj[3]);
    CollisionBetweenObjectsAndShips     (Obj[1], Obj[2], false);  //Moi
    CollisionBetweenObjectsAndShips     (Obj[3], Obj[0], true);  //Invaders
} //ManageCollisions

unsigned Victory (const CVString & Space, const CAObject & Obj)
{
    if (0 == Obj[0].size ()) return 2;
    else if (0 == Obj[2].size() || Obj[0][0].first == Space.size()-1) return 1;

    return 0;
} //Victory ()

void DeleteMissiles (const CVString & Space, CVPosition & Missiles)
{
    for (unsigned i (0); i < Missiles.size(); )
    {
        if (Missiles[i].first == Space.size())
            Missiles.erase(Missiles.begin()+i);
        else ++i;
    }
}//DeleteMissiles ()

void DeleteTorpedos (CVPosition & Torpedos)
{
    for (unsigned i (0); i < Torpedos.size(); )
    {
        if (unsigned (-1) == Torpedos[i].first)
            Torpedos.erase(Torpedos.begin()+i);
        else  ++i;
    }
} //DeleteTorpedos ()

void StartMenu (const string & Path)
{
    char C=' ';

    while (true)
    {
        ClearScreen();
        DisplaysDoc("../src/Nos_fichiers/Invader.txt", 33, 5);
        DisplaysDoc("../src/Nos_fichiers/SpaceInvadertext.txt", 11, 14);
        GotoXY(29,22);
        cout << "Press enter to continue" << endl;
        getchar();
        GotoXY(29,22);
        cout << "                       " ;

        // Menu
        int X (4);
        int Y (18);
        GotoXY(X,++Y);
        cout << "1 : Start" << endl;
        GotoXY(X,++Y);
        cout << "2 : Show config" << endl;
        GotoXY(X,++Y);
        cout << "3 : Show regle" << endl;
        GotoXY(X,++Y);
        cout << "4 : Credits" << endl;
        GotoXY(X,++Y);
        cout << "5 : Exit" << endl;

        cin >> C;

        switch (C)
        {
            case '1'    :
                score = 0;
                vies = 3;
                ClearScreen();
                set_input_mode ();
                ShowFile (1 == SpaceInvaders () ? Path + "lost.txt" : Path + "win.txt");
                reset_input_mode();
                HighScore(score, Path + "highscore.txt");
                sleep(5);
            break;
            case '2'   :
                cout << "Config";
                break;

            case '3'   :
                cout << "Config 3";
                break;
            case '4'   :
                ClearScreen();
                DisplaysDoc("../Project-SpaceInvader/assets/Credit.txt");
                break;
            case '5'   :
                ClearScreen();
                DisplaysDoc("../Project-SpaceInvader/assets/End.txt", 20, 10);
                GotoXY(0,23);
                exit(0);
                break;

            case 'r' | 'R'  :
                cout << "R mode";
                break;
        }
    }
}

unsigned SpaceInvaders (void)
{
    CVString Space;
    CAObject Obj;
    InitSpace (Space, Obj);

    unsigned Direction (0);
    unsigned WhatInvaderDo (0);
    unsigned Vict (0);
    unsigned WhoIsToPlay (0);
    while (1 != Vict && 2 != Vict)
    {
        //On met tous les objets dans la matrice
        PutAllObjects (Obj, Space);

        //on affiche la matrice
        DisplaySpace (Space);

        //c'est a qui de jouer?
        if (KRatioMeInvaders != WhoIsToPlay++)
            ManageMe(Obj);
        else
        {
            ManageInvaders(Obj, Direction, WhatInvaderDo);
            WhoIsToPlay = 0;
        }
        //dans tous les cas :
        //on fait descendre les missiles
        MoveDown (Obj[1]);
        //on fait monter les torpilles
        MoveUp (Obj[3]);
        //on gere les collisions
        ManageCollisions (Obj);
        //On supprime les missiles qui sortent de l'air de jeu
        DeleteMissiles (Space, Obj[1]);
        //On supprime les torpilles qui sortent de l'air de jeu
        DeleteTorpedos (Obj[3]);
        //on teste si quelqu'un a gagner
        Vict = Victory (Space, Obj);
        if (Vict == 1)
        {
            if(vies > 1)
            {
                vies--;
                InitSpace (Space, Obj);
                Vict = 0;
            }
        }
    }
    PutAllObjects (Obj, Space);
    DisplaySpace (Space);
    return Vict;
} // SpaceInvaders ()

void ShowFile (const string & FileName)
{
    ifstream ifs (FileName);
    for (string Line; getline (ifs, Line);)
        cout << Line << endl;
    cout << endl;
} //ShowFile ()


struct termios saved_attributes;

void reset_input_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, & saved_attributes);
}
//http://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html
void set_input_mode (void)
{
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO))
    {
        fprintf (stderr, "Not a terminal.\n");
        exit (EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes);
    atexit (reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 0;
    tattr.c_cc[VTIME] = 3;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

int ppal(const string & Path )
{
    srand (time(NULL));
    //set_input_mode ();
    StartMenu(Path);
    return 0;
} //ppal ()
}
