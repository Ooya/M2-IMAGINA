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
- **But** Battre l'adversaire avec un échec & mat