/*****************************************
 * Yiyang Zhao
 * yz3504
 * Programming Project 3 - Human
 ****************************************/ 

import java.util.Scanner;

public class Human{
   
    private int choice;
    private Scanner input;
    
    public Human(){
        input = new Scanner(System.in);
        choice = -1;
    }
    
    //obtain user input number as choice
    public void move(){
        choice = input.nextInt();  
    }

    //public get method for choice
    public int getChoice(){
        return choice;
    }
    
    
}
