import java.util.*;

public class Configuration {
    private int hauteur, largeur;
    private int x, y;
    private int[][] tab;

    public Configuration(int hauteur, int largeur){
        this.hauteur = hauteur;
        this.largeur = largeur;
        this.tab = new int[hauteur][largeur];
    }

    public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public void setX(int x) {
		this.x = x;
	}

	public void setY(int y) {
		this.y = y;
	}

	public int getHauteur() {
		return hauteur;
	}

	public int getLargeur() {
		return largeur;
	}

	public int[][] getTableau() {
		return tab;
	}

	public void setTableau(int[][] tableau) {
		this.tab = tableau;
	}
     
    //les cases disponibles sont les cases 1 et les murs sont les 0

    public void initialisationLabyrinthe(){
        Random rand = new Random();
        for(int i=0; i<this.hauteur; i++){
            for(int j=0; j<this.largeur; j++){
                this.tab[i][j] = rand.nextInt(2);
                //System.out.print(tab[i][j]+" ");
            }
        }
        System.out.println();
    }

    public void bonneConfiguration(){
            //System.out.println("HAUT");
            

            for(int i=0; i<this.hauteur; i++){
                for(int j=0; j<this.largeur; j++){
                    if (i-1>0 && i+1<hauteur && j-1>0 && j+1<largeur) { 
                        if(tab[i-1][j]==0 && tab[i+1][j]==0 && tab[i][j-1]==0 && tab[i][j+1]==0){
                            if (tab[i][j]==1) { 
                                tab[i][j]=0; 
                            }
                        }
                    }
                }
            }

            /*System.out.println("BAS");
            if (a + 1 < hauteur) { 
                if (tab[a + 1][b] == 0) {
                    tab[a + 1][b] = 1;
                }
            initialisationLabyrinthe(a + 1, b,compteur+1);
            }

            System.out.println("GAUCHE");
            if (b - 1 >= 0) {
                if (tab[a][b - 1] == 0) { 
                    tab[a][b - 1] = 1;
                }
                initialisationLabyrinthe(a, b - 1, compteur+1);
            }

            System.out.println("DROITE");
            if (b + 1 < largeur) {
                if (tab[a][b + 1] == 0) {
                    tab[a][b + 1] = 1;
                }
                initialisationLabyrinthe(a, b + 1, compteur+1);
            }*/
        
    }

    /*public void initialisationLabyrinthe(int a, int b, int compteur){
        this.tab[a][b]=1;

        Random rand = new Random();
        int dir = rand.nextInt(4);
        System.out.println(dir);

        if(compteur<=100){
            if(dir==0){
                System.out.println("HAUT");
                if (a-1 >= 0) { 
                    if (tab[a - 1][b]==0) { 
                        tab[a - 1][b]=1; 
                    }
                    initialisationLabyrinthe(a-1,b,compteur+1);
                }
            }else if(dir==1){
                System.out.println("BAS");
                if (a + 1 < hauteur) { 
                    if (tab[a + 1][b] == 0) {
                        tab[a + 1][b] = 1;
                    }
                initialisationLabyrinthe(a + 1, b,compteur+1);
                }
            }else if(dir==2){
                System.out.println("GAUCHE");
                if (b - 1 >= 0) {
                    if (tab[a][b - 1] == 0) { 
                        tab[a][b - 1] = 1;
                    }
                    initialisationLabyrinthe(a, b - 1, compteur+1);
                }
            }else if(dir==3){
                System.out.println("DROITE");
                if (b + 1 < largeur) {
                    if (tab[a][b + 1] == 0) {
                        tab[a][b + 1] = 1;
                    }
                    initialisationLabyrinthe(a, b + 1, compteur+1);
                }
            }
            System.out.println(compteur);
        }
    }*/


    public void afficheLabyrinthe(){
		for(int i=0; i<this.largeur; i++){
			System.out.print("----");
		}
		System.out.println();
		for(int j=0; j<this.largeur; j++){
			for(int k=0; k<this.hauteur; k++){
				System.out.print("| " + this.tab[j][k] + " ");
			}
			System.out.println("|");
			for(int l=0; l<this.largeur; l++){
				System.out.print("----");
			}
			System.out.println();
		}
    }

    public static void main(String[] args) {
        Jeu j = new Jeu();
        Configuration conf = new Configuration(7,7);
        conf.initialisationLabyrinthe();
        conf.bonneConfiguration();
        j.newGame();
        System.out.println("Voici le labyrinthe : ");
        System.out.println("Légende : 0 = mur et 1 = case libre");
        conf.afficheLabyrinthe();
    }
}