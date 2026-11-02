## Text

Une librairie d'outils de rendu avancé de texte utilisant les librairies SDL3 et SDL3_ttf.

#### Compilation :

(Re)Compilez `libtext.so` avec :

    $ make lib

#### Utilisation :

Copiez `text.h` et `libtext.so` dans votre projet, `#include "text.h"` dans votre code.

Puis compilez avec les flags adéquats :

    $ gcc -o your_project your_project.c -L./ -Wl,-rpath=./ -ltext

#### Demo :

Affiche diverses rendus de texte :

    $ make demo
