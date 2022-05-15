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

    public void afficheLabyrinthe(){
        int size;
		for(int i=0; i<this.largeur; i++){
			System.out.print("----");
		}
		System.out.println();
		for(int j=0; j<this.largeur; j++){
			for(int k=0; k<this.hauteur; k++){
				size = String.valueOf(this.tab[j][k]).length();
				if(size == 1){
					System.out.print("| " + this.tab[j][k] + " ");
				}else{
					System.out.print("| " + this.tab[j][k] + " ");
				}
			}
			System.out.println("|");
			for(int l=0; l<this.largeur; l++){
				System.out.print("----");
			}
			System.out.println();
		}
    }
}