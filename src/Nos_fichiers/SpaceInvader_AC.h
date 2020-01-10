#pragma once

/*!
  * \file SpaceInvader_AC.h
  * \author Alain Casali Marc Laporte
  * \date 7 janvier 2016
  * \brief Fichier décrivant l'ensemble des signatures vers les fonctions utilisées dans le jeu
  * \version 1.0
  * \bug Aucun connu
  */

#include "MyType_AC.h"
namespace nsSpaceInvader_AC
{
    /*!
    * \fn Couleur
     * \param[in] Coul couleur du texte
     * \brief Fonction permettant de changer la couleur du texte.
     */
    void Couleur (const std::string & Coul);

    /*!
     * \fn ClearScreen
     * \brief Fonction effaçant le contenu de l'écran
     */
    void ClearScreen ();

    /*!
     * \fn void PutCVPosition (const CVPosition & VPos, char Car, CVString & Space)
     * \brief Permet d'insérer le carcactère passé en second paramètre à toutes les positions souhaitées (1er paramètre) de l'espace de jeu (3ème paramètre).
     * \param[in] VPos Vecteur de CPosition
     * \param[in] Car Caractère à insérer dans l'esapce
     * \param\[in, out] Space Espace de jeu
     */
    void PutCVPosition (const CVPosition & VPos, char Car, CVString & Space);

    /*!
     * \brief Vide l'espace de jeu, puis insère tous les objets du jeu.
     * \param Obj [in] Liste des objets à insérer
     * \param Space [in, out] Espace de jeu
     */
    void PutAllObjects (const CAObject & Obj, CVString & Space);

    /*!
     * \brief Permet d'afficher l'espace de jeu.
     * \param [in] Space Espace de jeu
     */
    void DisplaySpace (const CVString & Space);

    /*!
     * \brief Permet d'initialiser l'espace de jeu et de définir les coordonnées des objets à placer au lancement du jeu.
     * \param Space [out] Espace de jeu
     * \param Obj [ou] Liste des objets à placer au début du jeu
     */
    void InitSpace (CVString & Space, CAObject & Obj);

    /*!
     * \brief Trouve le maximum d'un vecteur de CPosition de la coordonées en X (abscisse).
     * \param VPos [in] Vecteur de CPosition
     * \param MaxPos [out] Valeur maximale pour X
     */
    void MaxX (const CVPosition & VPos, CPosition & MaxPos);

    /*!
     * \brief Trouve le maximum d'un vecteur de CPosition de la coordonées en Y (ordonnée).
     * \param VPos [in] Vecteur de CPosition
     * \param MaxPos [out] Valeur maximale pour Y
     */
    void MaxY (const CVPosition & VPos, CPosition & MaxPos);

    /*!
     * \brief Trouve le minimum d'un vecteur de CPosition de la coordonées en X (abscisse).
     * \param VPos [in] Vecteur de CPosition
     * \param MinPos [out] Valeur minimale pour X
     */
    void MinX (const CVPosition & VPos, CPosition & MinPos);

    /*!
     * \brief Simule un déplacement gauche en retranchant une unité de déplacement à toutes les abscisses des objets en paramètre.
     * \param VPos [in, out] Vecteur de CPosition
     * \return Vrai si la plus petite des abscisses ne vaut pas 0, faux sinon
     */
    bool MoveLeft (CVPosition & VPos);

    /*!
     * \brief Simule un déplacement droit en ajoutant une unité de déplacement à toutes les abscisses des objets en paramètre.
     * \param Space [in] Espace de jeu
     * \param VPos [in, out] Vecteur de CPosition
     * \return Vrai si la plus grande des abscisses ne vaut pas n'est pas sur la dernière case de l'espace de jeu, faux sinon
     */
    bool MoveRight (const CVString & Space, CVPosition & VPos);

    /*!
     * \brief Simule un déplacement bas en ajoutant une unité de déplacement à toutes les ordonnées des objets en paramètre.
     * \param VPos [in, out] Vecteur de CPosition
     */
    void MoveDown (CVPosition & VPos);

    /*!
     * \brief Simule un déplacement haut en ajoutant une unité de déplacement à toutes les ordonnées des objets en paramètre.
     * \param VPos [in, out] Vecteur de CPosition
     */
    void MoveUp (CVPosition & VPos);

    /*!
     * \brief Simule le jeu du joueur. C'est ici que le joueur choisit ce qu'il fait. S'il décide de tirer, une tropille est lancée, d'une position au hasard, au dessus d'une de ses positions.
     * \param Space [in] Espace de jeu
     * \param Obj [in, out] Liste des objets du jeu
     */
    void ManageMe (const CVString & Space, CAObject &Obj);

    /*!
     * \brief ManageInvaders Simule le jeu de l'envahisseur.
     * \param Space [in] Espace de jeu
     * \param Obj [in, out] Liste des objets du jeu
     * \param Direction [in, out] Sens de déplacement de l'envahisseur
     * \param WhatInvaderDo [in, out] Ce que doit faire l'envahisseur (se déplacer ou lancer un missile, d'une position au hasard, au dessous d'une de ses positions).
     */
    void ManageInvaders (const CVString & Space, CAObject &Obj, unsigned & Direction, unsigned & WhatInvaderDo);

    /*!
     * \brief Gère les collisions entre les objets et les vaisseaux. Si une collision est détéctée (même coordonées pour un objet et une partie d'un vaisseau), l'objet et la partie du vaisseau diparaissent
     * \param Objects [in, out] Vecteur des positions des objects à traiter
     * \param StarShips [in, out] Vecteur des positions des vaisseaux à traiter
     */
    void CollisionBetweenObjectsAndShips (CVPosition & Objects, CVPosition & StarShips);

    /*!
     * \brief Gère les collisions (multiples) entre les missiles et les tropilles
     * \param Missiles [in, out] Vecteur des positions des missiles
     * \param Torpedos [in, out] Vecteur des positions des torpilles
     */
    void CollisionBetweenMissilesAndTorpedos (CVPosition & Missiles, CVPosition & Torpedos);

    /*!
     * \brief Gère toutes les collisions du jeu
     * \param [in, out] Obj Liste des objets du jeu
     */
    void ManageCollisions (CAObject & Obj);

    /*!
     * \brief Teste si l'envahisseur ou si le joueur ont gagné.
     * \param Space [in] Espace de jeu
     * \param Obj [in] Liste des objets du jeu
     * \return 0 si ni l'envahisseur ou le joueur ont gagné, 1 si c'est l'envahiseur et 2 si c'est le joueur
     */
    unsigned Victory (const CVString & Space, const CAObject & Obj);

    /*!
     * \brief Supprime les missiles qui sortent de l'espace de jeu.
     * \param [in] Space Espace de jeu
     * \param Missiles [in, out] Vecteur des positions des missiles
     */
    void DeleteMissiles (const CVString & Space, CVPosition & Missiles);

    /*!
     * \brief Supprime les tropilles qui sortent de l'espace de jeu.
     * \param Torpedos [in, out] Vecteur des positions des torpilles
     */
    void DeleteTorpedos (CVPosition & Torpedos);

    /*!
     * \brief Fonction principale du jeu sans option.
     */
    unsigned SpaceInvaders (void);

    /*!
     * \fn void ShowFile (const string & FileName)
     * \brief Permet d'afficher le contenu d'un fichier à l'écran.
     * \param FileName [in] Chemin vers le fichier à afficher
     */
    void ShowFile (const std::string & FileName);

    /*!
     * \fn void set_input_mode (void)
     * \brief Permet d'activer la saisie à la volée. Utile pour gérer les déplacement du joueur sans appuyer sur la touche entrée.
     * si le joueur ne joue pas pendant 3 10ème de seconde, alors il pert une action. <br><br>
     * voir : http://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html et http://man7.org/linux/man-pages/man3/termios.3.html
     */
    void set_input_mode (void);

    void reset_input_mode(void);

    /*!
     * \fn int ppal()
     * \brief Fonction principale du jeu.
     * <ol>
     *  <li> Initilalise la graine du générateur aléatoire,
     *  <li> active la saisie à la volée,
     *  <li> lance le jeu et
     *  <li> affiche le résultat
     * </ol>
     */
    int ppal (const std::string & Path);
}//namespace
