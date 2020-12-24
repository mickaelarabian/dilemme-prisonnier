# Dilemme du prisonnier

## Contexte

L’ICS (institue of Cognitives Sciences) est un laboratoire interdisciplinaire qui intègre l'expertise de
chercheurs des Sciences de la Vie et de médecine avec celle de chercheurs des Sciences Humaines et Sociales pour étudier la nature et la spécificité de l'esprit humain.

L’un des doctorants travaille sur la théorie des jeux, à la frontière de la psychologie et des
mathématiques, et notamment sur les jeux a somme non constante.

Le doctorant à accumuler des données expérimentales. Il a
besoin que des volontaires jouent l’un contre l’autre un nombre de fois à définir, sans jamais savoir
qui sont leurs adversaires.
Les deux volontaires s'affrontent sur plusieurs rounds définient comme des
confrontations trahison-collaboration.

## Documentation

### Règles du jeu

Dans ce dilemme du prisonnier deux joueurs s'affrontent sous forme de round:
    
    - Si les deux joueurs coopéeres, ils prendront respectivement 6 mois de prison

    - Si les deux joueurs trahissent ils prendront 5 ans de prisons
    
    - Si un joueur trahi alors que l'autre coopéere, la victime prendra 10 ans.

L'objectif finale est d'avoir la plus petite peine à la fin de la partie.

A l'issue de la partie, les résultats sont disponnibles dans le dossier `results` afin d'établir des statistiques par la suite.

### Installation et execution

L'installation et l'execution nécessite l'utilisation d'un terminal linux.

#### Etape 1 : Installation

```
# Installer la bibliothèque GTK
$ sudo apt-get -y install libgtk-3-dev

Cloner le projet sur les diférentes machines
$ git clone https://gitlab.com/athenais.thiburce/group-5-dilemmeduprisonnier.git

# Se déplacer dans le projet
$ cd group-5-dilemmeduprisonnier
```

#### Etape 2: Compilation et execution

```
# Compiler le projet
$ make all

# Compiler uniquement le serveur/client
$ make server
$ make client

# Executer le server/client
$ make runS
$ make runC

Vous pouvez jouer !

```

#### Etape 3: Les tests

```
# Compilation des tests du server/client
$ make testServer
$ make testClient

# Execution des tests server/client
$ make runUnitServer
$ make runUnitClient
```

#### Etape 4: La documentation

```
# Générer et ouvrir la documentation
$ make documentation
```


### Configuration

La configuration se fait à l'aide de fichiers de configurations sous fomre de clé/valeur présents dans `/config/configClient.cfg` et `/config/configServer.cfg`

Si vous souhaitez jouer directement en local sur la même machine aucune modification est nécéssaire. Dans le cas contraire, veuillez renseigner l'adresse ip et port du serveur.

Les peines de prison peuvent être égalmeent modifié en cas de besoin dans le fichier ``/config/configServer.cfg``

Pour vous aider à repérer l'emplacement des fichiers de configurations. Référez-vous à l'achitecture présente juste en dessous.

### Architecture

```
.
├── client_app
│   ├── controller
│       ├── controller.c
│       └── controller.h
│   ├── glade
│       └── Interface.glade
│   ├── socket
│       ├── socket.c
│       └── socket.h
│   ├── tests
│       ├── fixtures
│           ├── fixtures.c
│           └── fixtures.h
│       ├── unit
│           ├── controller.test.c
│           ├── controller.test.h
│           ├── socket.test.c
│           └── socket.test.h
│       └── main.c
│   ├── views
│   └── main.c
├── server_app
│   └── src
│       ├── controller.c
│       ├── controller.h
│       ├── file.c
│       ├── file.h
│       ├── game.c
│       ├── game.h
│       ├── gameArray.c
│       └── gameArray.c
│   ├── tests
│       └── fixtures
│           ├── fixtures.c
│           └── fixtures.h
│       ├── unit
│           ├── file.test.c
│           ├── file.test.h
│           ├── game.test.c
│           ├── game.test.h
│           ├── gameArray.test.c
│           ├── gameArray.test.h
│           ├── protocol.test.c
│           ├── protocol.test.h
│           ├── srvcxnmanager.test.c
│           ├── srvcxnmanager.test.h
│           ├── utils.test.c
│           └── utils.test.h
│       └── main.test.c
│   ├── utils
│       ├── utils.c
│       └── utils.h
│   ├── main.c
│   ├── srvcxnmanager.c
│   └── srvcxnmanager.h
├── results
├── config
│   ├── gameConfig
│       └── gameConfig.h
│   ├── config.c
│   ├── config.h
│   ├── configClient.cfg
│   └── configServer.cfg
├── protocol
│   ├── protocol.c
│   └── protocol.h
├── .gitignore
├── .gitlab-ci.yml
├── Doxyfile
├── Makefile
└── README.md