# Structure d'un jeu

- Etat
	- initiaux
	- finaux
- Actions
	- dilemne
	- vivants
- Règles
- Agents (rationnels)
- Buts
	- Je peux les atteindre
	- Je peux les manquer
- **Facteurs d'échecs**

### Structure du jeu d'échecs

- **Etat** : Matrice de 8x8, 16 pièces blanches et 16 noires, une boîte qui sert de cimetière
	- **initial** formation de départ de part et d'autre du plateau : une ligne de pions et une ligne tour, cheval, fou, roi, dame, fou, cheval, tour.
	- **finaux** un roi est en position d'*échec et mat*, (il ne peut plus se déplacer)
	- le *Pat*, quand un joueur ne peut plus jouer mais n'est pas *mat*
	- la règle des *cinquantes coups*
- **Actions**
	- Déplacer une pièce sur le plateau en respectant ses règles
	- Manger une pièce adverse et se déplacant dessus, elle est éliminée du jeu
- **Règles** : Les blancs commencent
	- Les pions bougent d'une case vers l'avant, et mangent d'une case en diagonale. S'il n'a pas bougé de la partie, il peut avancer de deux cases vers l'avant.
	- Le roi avance d'une seule case dans n'importe qu'elle direction
	- La dame avance d'autant de case que nécessaire dans n'importe quelle direction
	- Le fou se déplace en diagonale seulement
	- Le cheval se déplace en "L"
	- La tour se déplace en ligne droite (horizontal ou vertical)
	- Grand roque, petit roque
- **Agents** Deux joueurs
- **Buts** Battre l'adversaire avec un échec & mat, éviter de perdre
- **Facteur d'échec** L'adversaire

## Le cheval chess

- **Etat** Même échiquier que le jeu classique
	- **initial** Une reine pondeuse (H1) et deux chevals (G1 et H2), dans deux coins opposés.
	- **final** echec et mat d'une des deux reines.
- **Actions** Déplacement de la reine qui fait *spawn* un cheval sur son ancien emplacement. 
	- Manger une pièce en se déplacant dessus
- **Règles** Les blancs commencent
	- La reine se déplace comme un Roi classique
	- A chaque tour de jeu, le joueur choisi de déplacer sa reine ou de déplacer un de ses chevals
	- Le nombre de chevals est illimité
- **Agents** deux joueurs
- **Buts** Mettre en échec le roi adverse, éviter de perdre
- **Facteur d'échec** L'adversaire
