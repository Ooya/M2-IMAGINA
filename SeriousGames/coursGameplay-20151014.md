## Conception d'un gameplay

1. Coeur(s) de gameplay
	- Se poser la question : que va faire le joueur pendant 80%-90% du temps
	- On peut utiliser la classification des genres des jeux pour identifier les coeurs
	- Différents types :
		- Mono-core : un seul coeur de gameplay
		- 2 cores : combinaison entre deux coeurs
		- Multi-core : proposition de plusieurs coeurs
2. Contrôles
	- Permet de spécifier comment le joueur contrôle les entités/environnement du jeu
	- On va lister les actions possibles pour un joueur dans le jeu
	- Pour chaque action : donner les modalités d'interaction
	- Il est important de spécifier le(s) device(s) utilisé(s) pour l'interaction : manette, clavier, souris, kinect...
3. Caméra
	- Spécifier la (les) vue(s) du jeu
	- Type de caméra et son comportement
	- Cohérence entre le type de la caméra et le genre !
	- *Exemple* :
		- Mobile/Statique/Contrôlée par une IA
		- Vue 2D/ISO/3D
		- Objective/Subjective
4. Les acteurs du jeu *(characters)*
	- Spécifier les principaux acteurs du jeu
	- Spécifier les rôles/actions possibles
	- Modalités de contrôle
5. Feedback
	- Spécifier comment communiquer au joueur certains états du jeu
	- Le feedback est toujours en réaction à une action/évenement
		- Annoncer succès/échec
		- Rendre compte des performances
6. Assistance
	- Spécifier les éléments qui vont aider/assister le joueur qui font partie des scènes
	- *Exemple :*
		- Panneaux d'indication
		- PNJ utilitaires
7. Boucles de jeu (OCR+Means)
	- Boucle O-C-R : Objectif, Challenge, Reward
		- M : Means (Moyen)
		- Objectif : spéficier un état qui décide si la boucle est terminée ou non
		- Challenge : spécifier pourquoi le joueur ne peut pas atteindre directement l'objectif
		- Reward : récompense donnée au joueur un fois l'objectif atteint
		- Means : Lister les moyens mis à disposition pour atteindre l'objectif
	- Les boucles OCR+M sont composées : Boucle Micro, Moyenne et Macro
		- Boucle Micro : objectifs élémentaires (niveau scène)
		- Boucle Moyenne : composition de boucles (niveau scene et level)
		- Boucle Macro : boucles générales (niveau jeu)
8. Règles du jeu
9. Menus
	- Spécifier les éléments de l'interface utilisateur
	- fonctions + places sur la scene
	- Il est important de spécifier ces éléments en amont
