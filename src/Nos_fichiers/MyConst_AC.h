#pragma once

/*!
  * \file MyConst_AC.h
  * \author Alain Casali Marc Laporte
  * \date 7 janvier 2016
  * \brief Fichier décrivant l'ensemble des constantes utilisées dans le jeu
  * \version 1.0
  * \bug Aucun connu
  */

namespace nsSpaceInvader_AC
{
    //Constantes de couleur
    /*!
     * \brief Alias remetant la couleur du texte du terminal à sa valeur par défaut.
     */
    const std::string KReset   ("0");

    /*!
     * \brief Alias mettant en noir la couleur du texte du terminal.
     */
    const std::string KNoir    ("30");
    /*!
     * \brief Alias mettant en rouge la couleur du texte du terminal.
     */
    const std::string KRouge   ("31");

    /*!
     * \brief Alias mettant en vert la couleur du texte du terminal.
     */
    const std::string KVert    ("32");

    /*!
     * \brief Alias mettant en jaune la couleur du texte du terminal.
     */
    const std::string KJaune   ("33");

    /*!
     * \brief Alias mettant en bleu la couleur du texte du terminal.
     */
    const std::string KBleu    ("34");

    /*!
     * \brief Alias mettant en mangenta la couleur du texte du terminal.
     */
    const std::string KMAgenta ("35");

    /*!
     * \brief Alias mettant en cyan la couleur du texte du terminal.
     */
    const std::string KCyan    ("36");

    // Constantes pour les touches
    /*!
     * \brief Alias vers la touche servant à se déplacer à droite.
     */
    const char KRight               = 'x';  // déplacement vers la droite

    /*!
     * \brief Alias vers la touche servant à se déplacer à gauche.
     */
    const char KLeft                = 'w';  // Déplacement vers la gauche

    /*!
     * \brief Alias vers la touche servant à lancer une torpille.
     */
    const char KShoot               = ' ';  // Lancer de torpille

    //  Constantes liées à l'envahisseur
    /*!
     * \brief Couleur de l'envahisseur.
     */
    const std::string KInvadersColor (KJaune);  // Couleur de l'envahisseur

    /*!
     * \brief Caractèrere formant l'envahisseur.
     */
    const char KInsideInvader       = 'W';  // caractèrere formant l'envahisseur

    /*!
     * \brief Caractèrere formant le missile.
     */
    const char KMissile             = 'T';  // missile

    /*!
     * \brief Nombre de caractères qui forment l'envahisseur.
     */
    const unsigned KInvadersSize    =  5;   // nombre de caractères qui forment l'envahisseur

    /*!
     * \brief Nombre de fois où l'envahisseur tire un missile par rapport à son déplacement.
     */
    const unsigned KMissileRatio = 2; // nombre de fois où l'envahisseur tire un missile par rapport à son déplacement

    // Constantes liées au joueur
    /*!
     * \brief Couleur liée à mes objets (vaisseaux et tropilles).
     */
    const std::string KMyColor (KVert); // Ma couleur

    /*!
     * \brief Caractèrere formant mon vaisseau.
     */
    const char KInsideMe            = 'A'; // caractèrere formant mon vaisseau

    /*!
     * \brief Caractèrere formant ma torpille.
     */
    const char KTorpedo             = '|'; // caractèrere formant ma torpille

    /*!
     * \brief Nombre de caractères qui forment mon vaisseau.
     */
    const unsigned KMySize          = 4; //  nombre de caractères qui forment mon vaisseau


    /*!
     * \brief Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur.
     */
    const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


    // Constantes liées à l'eapace (l'écran)
    /*!
     * \brief Alias vers une case vide à l'écran.
     */
    const char KEmpty               = ' ';  // case vide de l'écran
    /*!
     * \brief Nombre de lignes de l'écran (de l'espace).
     */
    const unsigned KSizeLine   = 10;   // Nombre de lignes de l'écran (de l'espace)

    /*!
     * \brief Nombre de colonnes de l'écran (de l'espace).
     */
    const unsigned KSizeSpace  = 10;   // Nombre de colonnes de l'écran (de l'espace)

    /*!
     * \brief Numéro de colonne où commence l'envahisseur.
     */
    const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur

    /*!
     * \brief Numéro de colonne où commence le joueur.
     */
    const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur

    /*!
     * \brief Alias vers une ligne vide de l'esapce.
     */
    const std::string KEmptyLine (KSizeLine, KEmpty);  // Une ligne vide de la matrice
}//namespace
