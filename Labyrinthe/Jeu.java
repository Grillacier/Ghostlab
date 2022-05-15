import java.util.*;
import java.util.Scanner;


public class Jeu {
    private Scanner sc;

    //Construction du constructeur
    public Jeu(){
        this.sc = new Scanner(System.in);
    }

    public void newGame(){
       System.out.println("------------");
       System.out.println("| GhostLab |");
       System.out.println("------------");
       System.out.println("Entrez votre prenom :");
       String name = sc.nextLine();
       System.out.println("Bienvenue sur GhostLab, "+name+" !");
    }

    public static void main(String[] args) {
        Jeu j = new Jeu();
        Configuration c = new Configuration(4, 4);
        j.newGame();
        System.out.println("Voici le labyrinthe : ");
        c.afficheLabyrinthe();
    }
}
