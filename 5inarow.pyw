#Gomoku

from copy import *
from graphics import *

global board


#-------------------------BASICS-------------------------
def initialisation(win):
    for i in range(3,19):
        Line(Point(6,i),Point(21,i)).draw(win)
    for i in range(6,22):
        Line(Point(i,3),Point(i,18)).draw(win)
    Text(Point(25,16),"Hello").draw(win)
    return win

def setting(win):
    Rectangle(Point(6,16),Point(7,15)).draw(win)
    t1 = Text(Point(8.5,15.5),"Black")
    t1.setSize(22)
    t1.draw(win)
    Rectangle(Point(13,16),Point(14,15)).draw(win)
    t2 = Text(Point(15.5,15.5),"White")
    t2.setSize(22)
    t2.draw(win)
    t3 = Text(Point(9,13),"Difficulty Level")
    t3.setSize(22)
    t3.draw(win)
    Rectangle(Point(6,11.5),Point(7,10.5)).draw(win)
    t4 = Text(Point(8.5,11),"Easy")
    t4.setSize(20)
    t4.draw(win)
    Rectangle(Point(6,9.5),Point(7,8.5)).draw(win)
    t5 = Text(Point(9,9),"Medium")
    t5.setSize(20)
    t5.draw(win)
    Rectangle(Point(6,7.5),Point(7,6.5)).draw(win)
    t6 = Text(Point(8.5,7),"Hard")
    t6.setSize(20)
    t6.draw(win)
    Rectangle(Point(24,1.5),Point(26,0.5)).draw(win)
    Text(Point(25,1),"Confirm").draw(win)
    while True:
        p = win.getMouse()
        if 24 <= p.getX() <= 26 and 0.5 <= p.getY() <= 1.5:
            win.close()
            return "home"
    
def gameover(win,board,numb,numw,save):
    endtext=Text(Point(7,1),"")
    if  JJH:
        endtext.setText("Black wins!")
    if  GCGXF:
        endtext.setText("White wins!")
    if UGUG:
        endtext.setText("Draw!")
    endtext.setSize(20)
    endtext.setFill('red')
    endtext.draw(win)
    Text(Point(7,0.5),"The game has been saved, click anywhere to rewatch.").draw(win)
    f=open("savedata.dat","w")
    for i in range(len(save)):
        f.write(str(save[i][0])+" "+str(save[i][1])+"\n")
    f.close()
    return win

#-------------------------MODES-------------------------
def AI_Mode():
    #Initialisation
    save = []
    win = GraphWin("5-In-A-Row against AI", 720, 480)
    win.setCoords(0,0,30,20)
    win.setBackground("white")
    setting(win)
    win = GraphWin("5-In-A-Row against AI", 720, 480)
    win.setCoords(0,0,30,20)
    win.setBackground("white")
    win = initialisation(win)
    board = [[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
    Rectangle(Point(24,1.5),Point(26,0.5)).draw(win)
    Text(Point(25,1),"Home").draw(win)
    while True:
        p = win.getMouse()
        if 24 <= p.getX() <= 26 and 0.5 <= p.getY() <= 1.5:
            win.close()
            return "home"

def MultiPlayer():
    win = GraphWin("5-In-A-Row against AI", 720, 480)
    win.setCoords(0,0,30,20)
    win.setBackground("white")
    win = initialisation(win)
    Rectangle(Point(24,1.5),Point(26,0.5)).draw(win)
    Text(Point(25,1),"Home").draw(win)
    while True:
        p = win.getMouse()
        if 24 <= p.getX() <= 26 and 0.5 <= p.getY() <= 1.5:
            win.close()
            return "home"

def rewatch():
    wohaibuhui

           
#-------------------------SETUP-------------------------
def main():
    mode=0
    while mode!=4:
        ini_win = GraphWin("Gomoku", 720,480)
        ini_win.setCoords(0,0,36,24)
        ini_win.setBackground('white')
        t = Text(Point(8,12),"Gomoku")
        t.setSize(28)
        t.setOutline('black')
        t.draw(ini_win)
        Rectangle(Point(18,18),Point(26,16)).draw(ini_win)
        t1 = Text(Point(22,17),"Single Player")
        Rectangle(Point(18,13),Point(26,11)).draw(ini_win)
        t2 = Text(Point(22,12),"MultiPlayer")
        Rectangle(Point(18,8),Point(26,6)).draw(ini_win)
        t3 = Text(Point(22,7),"Watch Again")
        Rectangle(Point(30,2),Point(33,1)).draw(ini_win)
        t4 = Text(Point(31.5,1.5),"Exit")
        t1.setSize(22)
        t2.setSize(22)
        t3.setSize(22)
        t4.setSize(16)
        t1.draw(ini_win)
        t2.draw(ini_win)
        t3.draw(ini_win)
        t4.draw(ini_win)
        while True:
            p = ini_win.getMouse()
            if 30 <= p.getX() <= 33 and 1 <= p.getY() <= 2: #Exit
                mode = 4
                ini_win.close()
                break 
            if p.getX() >= 18 and p.getX() <= 26:
                if 16 <= p.getY() <= 18: #Single Player
                    ini_win.close()
                    mode=1
                    break
                if 11 <= p.getY() <= 13: #MultiPlayer
                    ini_win.close()
                    mode=2
                    break
                if 6 <= p.getY() <= 8: #Watch Again
                    ini_win.close()
                    mode=3
                    break
        getReturn = 'home'
        if mode == 1:
            getReturn = AI_Mode()
        if mode == 2:
            getReturn = MultiPlayer()
        if mode == 3:
            rewatch()
#--------------------------------------------------

main()
 
