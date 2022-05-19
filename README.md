# Build/Buy Lag Fix Sims 4
<div align="center">
	<br>
	<img src="header.png" width="960" height="248">
	<br>
</div>

<!----------------------------------------------------------------------------------------->

<h1>Quel est le problème ?</h1>
<p>Lorsque vous entrez ou sortez du mode construction/achat dans le jeu, certains joueurs subissent des baisses de FPS très ennuyeuses. Celles-ci se corrigent après un certain temps, ou en appuyant deux fois sur ESC. En général, ce n'est pas un gros problème, mais si vous changez très fréquemment de jeu c'est tout simplement chiant, donc voici ma solution.</p>

<!----------------------------------------------------------------------------------------->

<h1>Pour l'installer :</h1>
<p>Vous aurez besoin d'un loader ASI pour charger le plugin. Je suggère Ultimate ASI Loader de ThirteenAG.</p>
<p>Vous pouvez le trouver ici : <br>https://github.com/ThirteenAG/Ultimate-ASI-Loader/</p>
<p>Rendez-vous dans les releases et téléchargez la version x64 de l'ASI loader. Ensuite, téléchargez la dernière version de mon plugin.</p>
<ul>
<li>Extrayez dinput8.dll (l'ASI loader) à la racine du répertoire des Sims 4, se trouvant normalement ici : <br> The Sims 4\Game\Bin et renommez-le en version.dll.</li>
<li>Extrayez le contenu de BBLagFix.zip dans le même répertoire. Vous pouvez aussi construire le plugin vous-même, mais vous aurez besoin des fichiers ini (version.ini et BBLagFix.ini).</li>
</ul>

<!----------------------------------------------------------------------------------------->

<h1>Une mise à jour du jeu a cassé le patch ? Pas de panique...</h1>
<p>Pour mettre à jour le patch avec les nouvelles versions des sims 4, il vous sera nécessaire de vous rendre dans le fichier BBLagFix.ini</p>
<p>De modifier les valeurs nommées Adress, Expected, Target avec les valeurs correspondantes à la version actuelle du jeu.</p>

# Adresse pour le patch 1.87.40.1030
> Address = 0x140C8083D
> 
> Expected = 0xE081C71774
> 
> Target = 0xE081C717EB
