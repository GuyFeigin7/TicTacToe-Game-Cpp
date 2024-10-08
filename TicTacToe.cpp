#include <iostream>
#include <vector>
#include <ctime> // time()
#include <cstdlib> // system()

void DrawBoard(const std::vector<std::vector<char>>& board);
std::pair<int, int> PlayerMove(std::vector<std::vector<char>>& board, char player);
bool CheckWinner(const std::vector<std::vector<char>>& board, const std::pair<int, int>& last_move, char player);
bool CheckTie(const std::vector<std::vector<char>>& board);
void ClearBoard(std::vector<std::vector<char>>& board);
void ClearScreen();
void ChooseSize();

int SIZE = 3;

int main()
{
    char player1 = 'X';
    char player2 = 'O';
    bool running = true;
    bool playAgain = true;
    int turn = 1;

    ChooseSize();

    std::vector<std::vector<char>> board(SIZE, std::vector<char>(SIZE));
    ClearBoard(board);
    DrawBoard(board);

    while (playAgain)
    {
        while (running)
        {
            char player = (turn > 0) ? player1 : player2;

            std::pair<int, int> last_move = PlayerMove(board, player);
            DrawBoard(board);
            if (CheckWinner(board, last_move, player))
            {
                std::cout << "Player " << player << " won!\n";
                running = false;
                break;
            }
            else if (CheckTie(board))
            {
                std::cout << "It's a tie!\n";
                running = false;
                break;
            }

            turn *= -1;
        }

        std::cout << "\nDo you want to play again? (Y/N): ";
        char choice;
        std::cin >> choice;
        playAgain = (choice == 'Y' || choice == 'y');
        running = playAgain;
        if (playAgain)
        {
            ClearBoard(board);
            DrawBoard(board);
        }
    }

    return 0;
}

void DrawBoard(const std::vector<std::vector<char>>& board)
{
    ClearScreen();
    std::cout << "\n";

    for (int row = 0; row < SIZE; ++row)
    {
        for (int col = 0; col < SIZE; ++col)
        {
            std::cout << " " << board[row][col] << " "; // Print the current cell
            if (col < SIZE - 1)
            {
                std::cout << "|"; // Print the column separator 
            }
        }
        std::cout << "\n";
        if (row < SIZE - 1)
        {
            for (int i = 0; i < SIZE; ++i)
            {
                std::cout << "---"; // Print separator between rows
                if (i < SIZE - 1)
                {
                    std::cout << "+"; // Add sign between horizontal seperators
                }
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n";
}

std::pair<int, int> PlayerMove(std::vector<std::vector<char>>& board, char player)
{
    int row, col;

    std::cout << "Player: " << player << " move.\n";

    while (true)
    {
        std::cout << "Enter the row number for your marker: ";
        while (!(std::cin >> row))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');  // Ignore the invalid input up to the next newline
            std::cout << "Invalid input! Please enter a valid number: ";
        }

        std::cout << "Enter the column number for your marker: ";
        while (!(std::cin >> col))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');  // Ignore the invalid input up to the next newline
            std::cout << "Invalid input! Please enter a valid number: ";
        }

        --row;
        --col;

        if (row >= SIZE || row < 0 || col >= SIZE || col < 0)
        {   
            std::cout << "Invalid input. Try again.\n";
        }
        else if (board[row][col] != ' ')
        {
            std::cout << "There is already a marker on this spot. Try again.\n";
        }
        else
        {
            board[row][col] = player;
            break;
        }
    }

    return std::pair<int, int>(row, col); 
}

bool CheckWinner(const std::vector<std::vector<char>>& board, const std::pair<int, int>& last_move, char player)
{
    // Check row
    for (int col = 0; col < SIZE; ++col)
    {   
        if (board[last_move.first][col] != player)
        {
            break;
        }
        if (col == SIZE - 1)
        {
            return true;
        }
    }

    // Check column
    for (int row = 0; row < SIZE; ++row)
    {
        if (board[row][last_move.second] != player)
        {
            break;
        }
        if (row == SIZE - 1)
        {
            return true;
        }
    }

    // Check diagonals
    for (int row = 0, col = 0; row < SIZE; ++row)
    {
        if (board[row][col] != player)
        {
            break;
        }
        if (row == SIZE - 1)
        {
            return true;
        }
        ++col;
    } 

    for (int row = SIZE - 1, col = 0; row < SIZE; ++row)
    {
        if (board[row][col] != player)
        {
            break;
        }
        if (row == 0)
        {
            return true;
        }
    }

    return false;
}

bool CheckTie(const std::vector<std::vector<char>>& board)
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

void ClearBoard(std::vector<std::vector<char>>& board)
{
    for (int i = 0; i < SIZE; ++i)
    {
       for (int j = 0; j < SIZE; ++j)
       {
            board[i][j] = ' ';
       }
    }
}

void ClearScreen() 
{
    system("clear");  // Clear screen on Linux
}

void ChooseSize()
{
    std::cout << "Choose board size (minimum is 3 x 3): ";
    while (!(std::cin >> SIZE))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n'); 
        std::cout << "Invalid input! Please enter a valid number: ";
    }

    if (SIZE < 3)
    {
        SIZE = 3;
    }
}