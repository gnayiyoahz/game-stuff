/*****************************************
 * Yiyang Zhao
 * yz3504
 * Programming Project 3 - Computer
 ****************************************/ 

import java.util.stream.IntStream;

public class Computer{
    
    private int mode;
    private int choice;
    
    public Computer(int m){
        mode = m;
        choice = -1;
    }
    
    public void move(int marblesLeft){
        //create a list of strategic numbers = 2^k-1 
        int[] strategyList = {63,31,15,7,3};
        //to see whether a computer can adopt a "smart" strategy
        Boolean cannot = IntStream.of(strategyList).anyMatch(x -> x == marblesLeft);
        
        if (mode == 1 || cannot){
            //"stupid" mode OR the strategy cannot be used in "smart" mode
            //random, legal move
            choice = (int)(Math.random() * (int)(marblesLeft/2)) + 1;
        } else {
            //(mode == 2 && !cannot)
            //"smart" mode AND the strategy can be used
            //take a strategic move
            if (marblesLeft == 1 || marblesLeft == 2){
                choice = 1;
                
            } else {
                int strategyNum = 63;
                int i = 1;
                
                //finding a strategyNum that is legal: 
                //largest number in the list that is smaller than "marblesLeft"
                while (marblesLeft < strategyNum && i <= 4){
                    strategyNum = strategyList[i];
                    i++;
                }
                //leave a "strategyNum" number of marbles for user
                choice = marblesLeft - strategyNum;
            }
        } 
        
    }//end move   
    
    public int getChoice(){
        return choice;
    }
   
}
