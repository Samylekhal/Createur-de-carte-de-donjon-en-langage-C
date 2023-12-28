Mode d'emploi de la bibliothèque projet.c Du dungeon crawler



Le dossier comporte quatre fichiers essentiels :


_ projet.c contenant l'intégralité des fonctions codée du dungeon crawler

_ projet.h regroupant les fonctions, structure et variables utilisées pour la bibliothèque.

_ demo.c un fichier contenant un main et une fonction DJC créeant un donjon de test sous le nom projet.txt (nom modifiable) permettant de montrer les capacités de la bibliothèque.

_ Et le Makefile regroupant le tout



_ pour créer votre donjon, vous avez deux possibilités :


1) Utiliser le fichier demo.c et créer une nouvelle fonction vous permettant de créer le donjon à savoir que la fonction devra se terminer par sauvegarderSalle afin d'afficher tout ce que vous avez fait avant dans le txt. Une fois la fonction créée, enregistrée le fichier et utiliser sur l'invite de commande (ici powershell) les commandes "make all" puis "./projet.exe"



2) Vous pouvez aussi utiliser un nouveau fichier créer par vous même, mais cela demandera quelque prérequis qui sont les suivants :

_ ajouter l'include projet.h en tête de votre fichier c en spécifiant sa position dans le pc si vous le faites dans un dossier différent de celui de projet.

_ modifier le makefile en conséquent en y ajoutant votre fichier à l'intérieur.

_ veillez à retirer le main de demo.c pour pouvoir l'utiliser sur votre nouveau fichier.