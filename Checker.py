N = 8
M = 8
n_players = 2
marks = ['w', 'b']
grid = [[' ']*(M) for _ in range(N)]
def clear_grid():
    for i in range(N):
        for j in range(M):
            grid[i][j] = ' '

def set_elements():
    mark = 'w'
    grid[0][0], grid[0][2], grid[0][4], grid[0][6] = mark,mark,mark,mark
    grid[1][1], grid[1][3], grid[1][5], grid[1][7] = mark,mark,mark,mark
    grid[2][0], grid[2][2], grid[2][4], grid[2][6] = mark,mark,mark,mark
    mark = 'b'
    grid[5][1] = mark
    grid[5][3], grid[5][5], grid[5][7] = mark,mark,mark
    grid[6][0], grid[6][2], grid[6][4], grid[6][6] = mark,mark,mark,mark
    grid[7][1], grid[7][3], grid[7][5], grid[7][7] = mark,mark,mark,mark

def print_grid():
    for i in range(N):
        print("  -----------------------------------------------")
        for j in range(M):
            if grid[i][j] == 'B' or grid[i][j] == 'W':
                print(" | ", chr(ord(grid[i][j]) - 32), end = ' ')
            else:
                print(" | ", grid[i][j], end = ' ')
        print(" | ")
    print("  -----------------------------------------------")

def valid_position( i,  j,  i2,  j2,  mark):
    if not grid[i][j] == mark or not grid[i2][j2] == ' ':
        return False
    if (i < 0 or i > N ) or (j < 0 or j > N) or (i2 < 0 or i2 > N) or (j2 < 0 or j2 > N):
        return False
    return True

def move_mark( i,  j,  i2,  j2):
    grid[i2][j2] = grid[i][j]
    grid[i][j] = ' '
    if grid[i2][j2] == 'w' and i2 == N-1:
        grid[i2][j2] = 'W'
    if grid[i2][j2] == 'b' and i2 == 0:
        grid[i2][j2] = 'B'

def out( i, j, i2, j2):
    if not grid[i][j] == 'W' or not grid[i][j] == 'B':
        if grid[i][j] == 'b' and grid[i-1][j+1] == 'w' and i2 == i - 2 and j2 == j + 2:
            grid[i-1][j+1] = ' '
            return True
        elif grid[i][j] == 'b' and grid[i-1][j-1] == 'w' and i2 == i - 2 and j2 == j - 2:
            grid[i-1][j-1] = ' '
            return True
        elif grid[i][j] == 'w' and grid[i+1][j-1] == 'b' and i2 == i + 2 and j2 == j - 2:
            grid[i+1][j-1] = ' '
            return True
        elif grid[i][j] == 'w' and grid[i+1][j+1] == 'b' and i2 == i + 2 and j2 == j + 2:
            grid[i+1][j+1] = ' '
            return True
        return False
    else:
        if not grid[i][j] == grid[i-1][j+1] and not grid[i-1][j+1] == ' ' and not grid[i][j] == ' ' and i2 == i - 2 and j2 == j + 2:
            grid[i-1][j+1] = ' '
            return True
        elif not grid[i][j] == grid[i-1][j-1] and not grid[i-1][j-1] == ' ' and not grid[i][j] == ' ' and i2 == i - 2 and j2 == j - 2:
            grid[i-1][j-1] = ' '
            return True
        elif not grid[i][j] == grid[i+1][j-1] and not grid[i+1][j-1] == ' ' and not grid[i][j] == ' ' and  i2 == i + 2 and j2 == j - 2:
            grid[i+1][j-1] = ' '
            return True
        elif not grid[i][j] == grid[i+1][j+1] and not grid[i+1][j+1] == ' ' and not grid[i][j] == ' ' and  i2 == i + 2 and j2 == j + 2:
            grid[i+1][j+1] = ' '
            return True
        return False

def valid_move(i, j, i2, j2):
    if out(i,j,i2,j2):
        return True
    else:
        if grid[i][j] == 'w' and (i2 <= i or not i2 == i + 1):
            return False
        if grid[i][j] == 'w' and not ((j2 == j + 1) and not (j2 == j - 1)):
            return False
        if grid[i][j] == 'b' and (i2 >= i or not i2 == i - 1):
            return False
        if grid[i][j] == 'b' and not ((j2 == j + 1) and not (j2 == j - 1)):
            return False
        if (grid[i][j] == 'W' or grid[i][j] == 'B') and not (abs(i - i2) == abs(j - j2)) or (abs(i - i2) == abs(j - j2) and not abs(i-i2) == 1):
            return False
    return True
def win():
    w = 0
    b = 0
    for k in range(N):
        for l in range(M):
            if grid[k][l] == 'w' or grid[k][l] == 'W':
                w += 1
            if grid[k][l]  == 'b' or  grid[k][l] == 'B':
                b += 1
    if b == 0 :
        print("W win !!")
        return True
    elif w == 0:
        print("B win !!")
        return True
    else:
        return False
def read_input(i , j, i2, j2, mark):
    i, j, i2, j2 = map(int, input("Enter cells indices: ").split())
    while not valid_position(i,j,i2,j2,mark) or not valid_move(i,j,i2,j2):
        i, j, i2, j2 = map(int, input("Enter valid cells indices : ").split())
    return i,j,i2,j2

def play():
    print("Checker Game...")
    print("-------------------------")
    player = 0
    while (True):
        print_grid()
        print("Player ", marks[player], " is playing now")
        i,j,i2,j2 = 0,0,0,0
        i,j,i2,j2 = read_input(i, j, i2, j2, marks[player])
        move_mark(i,j,i2,j2)
        if win():
            print_grid()
            break
        player = (player + 1) % n_players

while True:
    clear_grid()
    set_elements()
    play()
    c = input("Play Again [Y/N]")
    if not c == 'y' and not c == 'Y':
        break
