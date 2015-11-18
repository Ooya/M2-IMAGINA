# Introduction au Pattern Entity-System

## Contexte

- Phase de conception GDD -> OK
- Choix des technologies du moteur de jeu
- Choix des pratiques/patterns
- Phase de prototypage informatique
- Modélisation des acteurs du jeu en mode "game objects"
- Ajout de gameobjects utiles mais pas visibles...

## Première approche avec l'OO

- Class
- Attribut
- Operation
- Objet
- Héritage entre classes

### Difficultés avec l'OO

- Problème avec les longues chaines d'héritage...
- Ambiguïté des opérations (problème de l'héritage multiple)
- Difficulé à définir clairement l'état du processus (au sens OS) du jeu : problème de la sauvegarde
- Réutilisation inter projets de jeux

## Le design pattern Entity/System

- Ses principes
	- Data-Driven
	- Composition over inheritance
- Pourquoi ?
	- Flexibilité dans la définition des acteurs
	- Réutilisation logicielle
	- Meilleur contrôle des dynamiques et des interactions
- Prix : Performance

## Concepts de base

* Entity
    - Indentifiable
    - Un simple _container_
    - Peut définir une hiérarchie : sous entités
* Component
    - Contient les données
    - Comportements associés aux données
    - Ajouter/etirer (dynamiquement) à des entités

### Concepts de base v2

- Introduction du concept de system/processor
- Entity
- Component
    + Contient uniquement des données !
- System/processor
    + Code lié à un aspect particulier
    + Chaque système est _indépendant_
    + Itérer sur les entités qui possèdent les composants liés à l'aspect traité

## Simple implémentation de d'E/S

- Entity
    + id:Integer
    + components:List
- ComponentType: Enum
- EntityManager
    + ComponentType->[Entity]
- Component
    + type: ComponentType
    + data: Map
- System/Processor
    + onUpdate()

### Amélioration 1

- Amélioration : Communication inter systèmes
- Interaction entre systèmes
    + Modification des données des components
    + Avec des primitives de communication
    + Pattern : Observer
        * Enregistrement d'un système auprès d'une source d'évenement
        * Déclenchementt d'un évenement
        * Handle de l'évènement pas les systèmes
    + Pattern : Message passing
        * Envoyer explicitement un message
        * Destinataire du message Délégué Component Systeme

### Amélioration 2

- Amélioration : Machine à états
- Les composants sont ajoutés/retirés avec une FSM
- L'entité sera dynamiquement traitée par des systèmes différents selon son état
- Gestion facile des facettes (aspects différents) d'une entité !

## Exemple Version simplifiée d'_Asteroid_

### Components

- GameStateComponent: lives, level, hits, isPlaying
- Position: point rotation
- Collision: radius
- DeathLag: time
- Display: viewToDisplay
- Motion: velocity, angularVelocity
- MotionControl: left, right, acceleration
- AnimationComponent
- AsteroidComponent: fsm
    + alive -> Motion, Collision, Display
    + destroyed -> DeathLag, Animation
- SpaceShipComponent fsm
    + playing -> Motion, MotionControl, Collision, Display
    + destroyed -> Display, DeathLag, Animation
- HudComponent: hudView
- Audio sound
- WaitForClickComponent

### Les entités

- AsteroidEntity
    + Ast$eroidComponent
    + Position
    + Sound
- SpaceShipEntity
    + Ast$SpaceShipComponent
    + Position
    + Sound
- ......Entity

### Les systèmes

- AudioSystem
- CollisionSystem
- DeathLagSystem
- HudSystem
- MotionControlSystem
- MovementSystem
- RenderSystem
- GameDynamicsSystem
