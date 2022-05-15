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

    /*public void nouvelleConfiguration(){
        for(int i=0; i<this.hauteur; i++){
            for(int j=0; j<this.largeur; j++){
                initialisationLabyrinthe();
            }
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
        Configuration conf = new Configuration(4,4);
        conf.initialisationLabyrinthe();
        j.newGame();
        System.out.println("Voici le labyrinthe : ");
        System.out.println("Légende : 0 = mur et 1 = case libre");
        conf.afficheLabyrinthe();
    }
}