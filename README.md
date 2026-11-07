## Image

Une librairie d'outils de rendu CPU utilisant la librairie SDL3.

#### Compilation :

(Re)Compilez `libimage.so` avec :

    $ make lib

#### Utilisation :

Copiez `image.h` et `libimage.so` dans votre projet, `#include "image.h"`
dans votre code.

Puis compilez avec les flags adéquats :

    $ gcc -o your_project your_project.c -L./ -Wl,-rpath=./ -limage

#### Demo :

Affiche diverses rendus sur du texte :

    $ make demo
