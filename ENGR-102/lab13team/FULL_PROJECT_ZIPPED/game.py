from PIL import Image, ImageTk
import turtle
import time
import core

def pt_core2ui(pt):
    return ((int(pt[0])-12)-204, -(int(pt[1])-12)+204)

# def pt_ui2core(pt):
    # return (str((pt[0]+204)+12), str(-(pt[1]+204)+12))
    
def core_find_close_pt(ptls, pt):
    for i, ptl in enumerate(ptls):
        ptl = pt_core2ui(ptl)
        if abs(ptl[0] - pt[0]) < 10 and abs(ptl[1] - pt[1]) < 10:
            return i
    return None

ROLL = 99

class Game():
    def __init__(self, **kwargs):

        self.roll_phase = False
        self.turn = "green"
        
        self.home_coords = [] 
        for _, coords in core.colorCoords.items():
            for i, coord in enumerate(coords):
                self.home_coords.append(coord)
        
        # Set up the screen
        self.screen = turtle.Screen()
        self.screen.tracer(0)
        self.screen.title("Trouble!")
        self.screen.setup(width=500, height=500)
        
        self.instrlabel = turtle.Turtle()
        self.instrlabel.hideturtle()  
        self.instrlabel.penup()
        self.instrlabel.goto(0, -235)  
        self.instrlabel.write("Instructions: roll dice, and move piece if prompted.", align="center", font=("Arial", 12, "bold"))
        
        # turtle.register_shape("board.gif")
        turtle.register_shape("cred.gif")
        turtle.register_shape("cyellow.gif")
        turtle.register_shape("cblue.gif")
        turtle.register_shape("cgreen.gif")
        turtle.register_shape("cwhite.gif")
        
        for i in range(1, 7):
            turtle.register_shape(f"dice{i}.gif")
            
        self.state = None
        self.stator_cb = lambda x : x    
        
        self.init_turn_label()
        self.init_op_label()
        
        self.screen.bgpic("board.gif")
        
        self.update_turn_label()
        
        self.render_board()
        
        self.roll()
        
        self.screen.onclick(self.handle_click)
        
    def handle_click(self, x, y):
        # print(f"Clicked at {x}, {y}")
        if -40 < x < 40 and -40 < y < 40 and self.state == ROLL:
            self.roll()
        
        if self.state == core.MOVE:
            i = core_find_close_pt(core.colorCoords[self.turn], (x, y))
            if i is not None:
                if i >= core.homePieces[self.turn]:
                    self.stator_cb(str(4-i))
        elif self.state == core.TAKEORMOVE:
            i = core_find_close_pt(core.colorCoords[self.turn], (x, y))
            if i is not None:
                if i >= core.homePieces[self.turn]:
                    self.stator_cb(str(4-i)) 
                else:
                    self.stator_cb(str(0))
        
    def init_turn_label(self):
        self.turnlabel = turtle.Turtle()
        self.turnlabel.hideturtle()  
        self.turnlabel.penup()
        self.turnlabel.goto(0, 130)  
        self.turnlabel.write("...", align="center", font=("Arial", 16, "bold"))
        
    def update_turn_label(self): 
        self.turnlabel.clear()
        self.turnlabel.write("It's " + self.turn + "'s turn", align="center", font=("Arial", 16, "bold"))
        
    def init_op_label(self):
        self.oplabel = turtle.Turtle()
        self.oplabel.hideturtle()
        self.oplabel.penup()
        self.oplabel.goto(0, 100) 
        self.oplabel.write("...", align="center", font=("Arial", 12, "bold"))
        
    def update_op_label(self, txt): 
        self.oplabel.clear()
        self.oplabel.write(txt, align="center", font=("Arial", 12, "bold"))
    
    def next_color(self):
        if self.turn == "green":
            self.turn = "yellow"
        elif self.turn == "yellow":
            self.turn = "blue"
        elif self.turn == "blue":
            self.turn = "red"
        elif self.turn == "red":
            self.turn = "green"
        self.update_turn_label()

    def fillpt(self, pt, color):
        # self.board_img.paste(img, (max(pt[0]-12, 0), max(pt[1]-12, 0)), img)
        # pt = (pt[0]-12, pt[1]-12) 
        overlay = turtle.Turtle()
        overlay.shape(f"c{color}.gif")
        overlay.penup() 
        overlay.goto(pt[0], pt[1])
        
    def roll(self):
        dice_roll = core.rollDice()
        overlay = turtle.Turtle()
        overlay.shape(f"dice{dice_roll}.gif")
        overlay.penup() 
        overlay.goto(0, 0)  
        self.calculate_options(dice_roll)
        
    def calculate_options(self, dice_roll):
        self.render_board()
        self.state, txt, callback = core.turn(self.turn, dice_roll)
        self.update_op_label(txt)
        
        def cont(i):
            callback(i)
            self.next_color()
            self.render_board()
            if self.state == core.MOVE or self.state == core.TAKEORMOVE:
                self.oplabel.clear()
            self.state = ROLL
        
        self.stator_cb = cont
        
        if self.state == core.NOPLAY or self.state == core.TAKEOUT:
            # time.sleep(.5)
            cont(0)
        
    def render_board(self):
        for coord in core.regularCoords + self.home_coords:
            self.fillpt(pt_core2ui(coord), "white")
            
        for color, coords in core.colorCoords.items():
            for i, coord in enumerate(coords):
                self.fillpt(pt_core2ui(coord), color)
                
        self.screen.update()
        
if __name__ == '__main__':
    game = Game()
    game.screen.mainloop()