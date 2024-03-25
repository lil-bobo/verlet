# Intégration de Verlet

Équation utile pour calculer la trajectoir de particules en simulation.

## Équation

$$
\vec{x}(t + \Delta t) = 2 \vec{x}(t) - \vec{x}(t - \Delta t) + \vec{a}(t)\Delta t^2 + O(t^4)
$$

En posant $\vec{x}_{n+1} = \vec{x}(t + \Delta t)$ et $\vec{x}_{n} = \vec{x}(t)$ et $\vec{x}_{n-1} = \vec{x}(t - \Delta t)$, on a l'équation suivante
$$
\vec{x}_{n+1} = \vec{x}_n + \vec{x}_n - \vec{x}_{n-1} + \vec{a}\Delta t^2 + O(t^4)
$$

qui devient en identifiant $ \vec{v}_{n-1}\Delta t = \vec{x}_n - \vec{x}_{n-1} $

 $$ \vec{x}(t) = \vec{x}_n + \vec{v}(t)\Delta + \vec{a}\Delta t^4$$

et éventuellement en identifiant $\vec{v}_n = \vec{v}_{n-1} + \vec{a}\Delta t$ l'équation suivante
$$\vec{x}_{n+1} = \vec{x}_n + \vec{v}_n \Delta t$$

## Dimension 2

On décide dans un premier temps d'implémenter un moteur physique simple en 2D. L'intérêt est de comprendre à quoi ressemble la trajectoire d'une particule dans un espace plus simple que la 3 dimension mais plus complet que la 1 dimension de sorte à voir des résultats concrets.

On implémente alors une structure de données de vecteurs 2 dimensions (`/lib/vectors.hpp`). Avec l'équation précedemment présentée, on est capable de déterminer l'effet de la gravité sur le corps étudié. On introduit alors les *contraintes* pour que l'étude de la chute libre ne se limite à une chute infinie

### Contraintes
On appelle **contrainte** une zone où notre particule ne peut pas être présente. Il est plutot simple de créer une contrainte qui prend la forme d'un plan : la balle ne peut pas tomber à l'infinie sous la force de gravité. Il est même possible de la faire rebondir. Cependant, il faut garder en tête que l'objectif de toutes ces recherches est d'être utilisables dans la simulation d'une partie de golf. Donc un simple plan est trop peu pour nous. En effet, on remarque que tout devient plus compliqué quand on ce n'est pas plan : les vecteurs normaux font apparition. On suppose que les forces et composantes caractéristique de la particule sont réfléchies de la même manière que la lumière.

#### TODO

- Il faut créer un programme capable de détecter les contraintes et de modifier les vecteurs de sorte que la simulation reste réaliste.
    - On créer une structure de données qui représente la particule (position, vitesse et accelération à choisir judicieusement selon l'équation qu'on souhaite utiliser)
    - Créer un *solveur* qui va mettre à jour les informations caractéristiques de la particule (contraites, déplacements etc)
- Afficher une particule dans son environnement avec `SFML`