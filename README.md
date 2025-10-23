# Hashfinder
Hashfinder est un programme écrit en C permettant de générer une liste de condensats (hashes) à partir d'un dictionnaire.

Plusieurs algorithmes de hachage sont pris en compte : SHA512, SHA384, SHA256, SHA224 et MD5.

Par la suite, il est possible de rechercher un hash dans la liste de condensats et d'obtenir son clair (mot de passe d'origine).
## Partie génération
### Commande : 
`./hashfinder -g -f <fichier_entrée> -o <fichier_sortie> [-algo <algorithme>]`

### Paramètres
 - `-g` Mode génération 

 - `-f` Le fichier d'entrée (par exemple rockyou/rockyou_14M.txt qui regroupe 14 millions de mots de passe provenant d'un data breach en 2009 : [rockyou.txt](https://github.com/RykerWilder/rockyou.txt))


 - `-o` Le fichier de sortie (par exemple t3c/rockyou.t3c)

- -`algo` (optionel) L'algorithme de hachage [SHA512, SHA384, SHA256, SHA224, MD5]. Par défaut, SHA256 est utilisé.

### Exemple
`./hashfinder -g -f rockyou/rockyou.txt -o t3c/rockyou.t3c -algo SHA256`

## Partie recherche 
### Commande :
`./hashfinder -l -f <fichier_table>`
### Paramètres :
- -`l` Mode Lookup

- -`f` le fichier t3c (par exemple /t3c/rockyou.t3c)


Après le chargement en mémoire du fichier, vous serez invité à entrer des hashes pour en obtenir leur clair.

Les hashes peuvent aussi être fournis par le flux standard d'entrée : 

`echo "8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92" | ./hashfinder -l -f t3c/rockyou.t3c`

ou depuis un fichier

`cat document_avec_hash.txt | ./hashfinder -l -f t3c/rockyou.t3c`

## DockerFile
### Build:
Compiler le programme avec Docker :

``` bash
docker build -t hashfinder-builder -f Dockerfile.build .

docker run --rm -v $(pwd):/app hashfinder-builder make
```

Vous obtiendrez dans votre répertoire l'exécutable du programme, fonctionnel pour Linux.

Si vous êtes sur un autre système, référez vous à la partie [Makefile](#Makefile-(sans-docker)) ou bien lancer le programme avec les dockerfiles suivants.

### Éxécuter le programme
#### Mode génération
````
docker build -t hashfinder-generate -f Dockerfile.mode_generate .

docker run --rm -it -v $(pwd)/t3c:/app/t3c hashfinder-generate

````


Dans le `Dockerfile.mode_generate`, la commande génère un t3c à partir du fichier rockyou/rockyou.txt. Vous pouvez ajouter un fichier et modifier cette commande.

#### Mode recherche
``` bash
docker build -t hashfinder-lookup -f Dockerfile.mode_lookup .

docker run --rm -it hashfinder-lookup #l'option -it est indispensable pour intéragir avec le programme
```

## Makefile (sans Docker)
Vous pouvez compiler le programmme directement avec la commande `make`.

```bash 
make clean && make
```

Ensuite, exécutez le programme obtenu :
```bash 
./hashfinder -g -f rockyou/rockyou.txt -o t3c/rockyou.t3c

./hashfinder -l -f t3c/rockyou.t3c
```
### Prérequis
- GCC
- OpenSSL (libssl-dev sur Ubuntu)
- Make

``` bash 
sudo apt-get update
sudo apt-get install -y build-essential libssl-dev
```

