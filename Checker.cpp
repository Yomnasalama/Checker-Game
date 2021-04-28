#include <bits/stdc++.h>
using namespace std;
const int N = 8;
const int n_players = 2;
char marks[n_players] = {'w', 'b'};
struct marks_player
{
    bool isKing = false;
    char mark = ' ';
};
marks_player grid[N][N];
void clear_grid()
{
    for(int i=0;i < N; i++)
    {
        for(int j=0;j < N; j++)
            grid[i][j].mark = ' ';
    }
}
void set_elements()
{
    marks_player player;
    player.mark = 'w';
    grid[0][0] = player; grid[0][2] = player; grid[0][4] = player; grid[0][6] = player;
    grid[1][1] = player; grid[1][3] = player; grid[1][5] = player; grid[1][7] = player;
    grid[2][0] = player; grid[2][2] = player; grid[2][4] = player; grid[2][6] = player;
    player.mark = 'b';
    grid[5][1] = player; grid[5][3] = player; grid[5][5] = player; grid[5][7] = player;
    grid[6][0] = player; grid[6][2] = player; grid[6][4] = player; grid[6][6] = player;
    grid[7][1] = player; grid[7][3] = player; grid[7][5] = player; grid[7][7] = player;
}
void print_grid()
{
 for(int i=0;i<8;i++)
 {
  cout<<"  --------------------------------"<<endl;
  for(int j = 0; j < N; j++)
  {
      if(grid[i][j].isKing)
        cout<<" | " << char(int(grid[i][j].mark) - 32);
      else
        cout<<" | " << grid[i][j].mark;
  }
  cout << " | " << endl;
 }
 cout<<"  --------------------------------"<<endl;
}
bool valid_position(int i, int j, int i2, int j2, char mark)
{
    if(grid[i][j].mark != mark || grid[i2][j2].mark != ' ')
        return false;
    if((i < 0 || i > N ) || (j < 0 || j > N) || (i2 < 0 || i2 > N ) || (j2 < 0 || j2 > N))
        return false;
    return true;
}
void move_mark(int i, int j, int i2, int j2)
{
    grid[i2][j2] = grid[i][j];
    grid[i][j].mark = ' ';
    grid[i][j].isKing = false;
    if (grid[i2][j2].mark == 'w' && i2 == N-1)
        grid[i2][j2].isKing = true;
    if(grid[i2][j2].mark == 'b' && i2 == 0)
        grid[i2][j2].isKing = true;
}
bool out (int i, int j, int i2, int j2)
{
    if(!grid[i][j].isKing)
    {
        if (grid[i][j].mark == 'b' && grid[i-1][j+1].mark == 'w' && i2 == i - 2 && j2 == j + 2)
        {
            grid[i-1][j+1].mark = ' ';
            return true;
        }
        else if (grid[i][j].mark == 'b' && grid[i-1][j-1].mark == 'w' && i2 == i - 2 && j2 == j - 2)
        {
            grid[i-1][j-1].mark = ' ';
            return true;
        }
        else if (grid[i][j].mark == 'w' && grid[i+1][j-1].mark == 'b' && i2 == i + 2 && j2 == j - 2)
        {
            grid[i+1][j-1].mark = ' ';
            return true;
        }
        else if (grid[i][j].mark == 'w' && grid[i+1][j+1].mark == 'b' && i2 == i + 2 && j2 == j + 2)
        {
            grid[i+1][j+1].mark = ' ';
            return true;
        }
        return false;
    }
    else
    {
        if (grid[i][j].mark != grid[i-1][j+1].mark && grid[i-1][j+1].mark != ' ' && grid[i][j].mark != ' '  && i2 == i - 2 && j2 == j + 2)
        {
            grid[i-1][j+1].mark = ' ';
            return true;
        }
        else if (grid[i][j].mark != grid[i-1][j-1].mark && grid[i-1][j-1].mark != ' ' && grid[i][j].mark != ' ' && i2 == i - 2 && j2 == j - 2)
        {
            grid[i-1][j-1].mark = ' ';
            return true;
        }
        else if (grid[i][j].mark != grid[i+1][j-1].mark && grid[i+1][j-1].mark != ' ' && grid[i][j].mark != ' ' &&  i2 == i + 2 && j2 == j - 2)
        {
            grid[i+1][j-1].mark = ' ';
            return true;
        }
        else if (grid[i][j].mark != grid[i+1][j+1].mark && grid[i+1][j+1].mark != ' ' && grid[i][j].mark != ' ' &&  i2 == i + 2 && j2 == j + 2)
        {
            grid[i+1][j+1].mark = ' ';
            return true;
        }
        return false;
    }
}
bool valid_move(int i, int j, int i2, int j2)
{
    if(out(i,j,i2,j2))
        return true;
    else
    {
        if((grid[i][j].mark == 'w') && (i2 <= i || i2 != i + 1) && (!grid[i][j].isKing))
                return false;
        if((grid[i][j].mark == 'w') && ((j2 != j + 1) && (j2 != j - 1)) && (!grid[i][j].isKing))
                return false;
        if((grid[i][j].mark == 'b') && (i2 >= i || i2 != i - 1) && (!grid[i][j].isKing))
                return false;
        if((grid[i][j].mark == 'b') && ((j2 != j + 1) && (j2 != j - 1))&& (!grid[i][j].isKing))
                return false;
         if((grid[i][j].isKing) && (abs(i - i2) != abs(j - j2)) || (abs(i - i2) == abs(j - j2) && abs(i-i2) != 1))
                return false;
    }
    return true;
}
bool win()
{
    int w = 0, b = 0;
    for(int k = 0; k  < N; k++)
    {
        for(int l = 0; l < N; l++)
        {
            if(grid[k][l].mark == 'w')
                w++;
            if(grid[k][l].mark == 'b')
                b++;
        }
    }
    if(b == 0)
    {
        cout<<"W win !!"<<endl;
        return true;
    }
    else if(w == 0)
    {
        cout<<"B win !!"<<endl;
        return true;
    }
    else
        return false;
}
int read_input(int &i , int &j, int &i2, int &j2,char mark)
{
    cout<<"Enter cells indices: "<<endl;
    cin>>i>>j>>i2>>j2;
    while(!valid_position(i,j,i2,j2,mark) || !valid_move(i,j,i2,j2))
    {
        cout<<"Enter valid cells indices :\ "<<endl;
         cin>>i>>j>>i2>>j2;
    }
}
void play()
{
        cout<<"Checker Game..."<<endl;
        cout<<"-------------------------"<<endl;
        int player = 0;
        while (true)
        {
            print_grid();
            cout<<"Player "<<marks[player]<<" is playing now"<<endl;
            int i,j,i2,j2;
            read_input(i,j,i2,j2,marks[player]);
            move_mark(i,j,i2,j2);
            if(win())
              {
                 print_grid();
                 break;
              }
            player = (player + 1) % n_players;
        }
}
int main()
{
    while(true)
    {
        clear_grid();
        set_elements();
        play();
        char c;
        cout<<"Play Again [Y/N]";
        cin>>c;
        if(c != 'y' && c!= 'Y')
            break;
    }
}
