/*****************************************
 * Yiyang Zhao
 * yz3504
 * Programming Project 3 - Game
 ****************************************/ 

public class Game{
    
    private int marbles;
    private Human humanPlayer;
    private Computer computerPlayer;
    private int compFirst;
    private int numTaken;
    private Boolean valid;
    
    public Game(int difficulty){
        //initialize pile size: between 10 and 100, inclusive
        marbles = (int)(Math.random() * 91 + 10);
        System.out.println("The initial size of the pile is " + marbles + ".");

        humanPlayer = new Human();
        computerPlayer = new Computer(difficulty);
        //random integer 0 or 1 to determine who plays first
        compFirst = (int)(Math.random()*2);  
    }
     
    public void play(){
        /*if computer goes first, add a round for the computer at first
          before going into the human-computer loop. */
        if (compFirst == 1){
            System.out.println("The computer goes first.");
            compPlay();
        } else {
            System.out.println("You can go first.");
        }
        
        //Take turns to play: human-comp-human-comp-... if there are marbles.
        while (marbles > 0){
            valid = false;//not valid move until checked
            youPlay();
            //move on to the computer's turn only if there are marbles left
            if (marbles > 0){
                compPlay();
                if (marbles == 0){
                    //computer took the last marble
                    System.out.println("===========GAME OVER===========\n"
                                       +"You win! ^_^");
                }
            } else {
                //user took the last marble
                System.out.println("===========GAME OVER===========\n"
                                   +"You lose! X_X");
            }
        }//end while      
    }// end play
    
    //call method move() in class Computer, let computer play
    public void compPlay(){
        System.out.println("--------COMPUTER'S TURN--------");
        computerPlayer.move(marbles);
        numTaken = computerPlayer.getChoice();
        marbles -= numTaken;//pile size decreases
        
        System.out.println("The computer took " + numTaken + " marble(s).");
        System.out.println("Marble(s) left: " + marbles);        
    }    
    
    //call method move() in class Human, let user play
    public void youPlay(){
        System.out.println("-----------YOUR TURN-----------");
        System.out.println("How many marbles are you taking?");
        
        while (valid == false){
            humanPlayer.move();
            numTaken = humanPlayer.getChoice();
            checkV();
        }//only move on to the next stage if it is a legal value to take
        
        marbles -= numTaken;
        System.out.println("You took " + numTaken + " marble(s).");  
        System.out.println("Marble(s) left: " + marbles);            
    }
        
    public void checkV(){
        //check validity of user's move
        if (numTaken != 0 && (numTaken <= (int)marbles/2 || numTaken ==1)){
            valid = true;//break out of while loop
        }
        else{
            System.out.println("Illegal move!\nPlease enter a number that is "
                               +"at least 1 but at most half of the marbles.");
        }
    }//end of checkV
    // you may wish to add more methods here
    


}