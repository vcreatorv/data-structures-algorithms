#include <iostream>
#include <array>
#include <cassert>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>


const int SIZE = 4;
const int FIELD_SIZE = SIZE * SIZE;
const std::array<char, FIELD_SIZE> finishField = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

class GameState
{
public:
    GameState(const std::array<char, FIELD_SIZE>& field) : field(field)
    {
        emptyPos = -1;
        for (int i = 0; i < FIELD_SIZE; i++)
        {
            if (field[i] == 0)
            {
                emptyPos = i;
                break;
            }
        }
        assert(emptyPos != -1);
    }

    bool IsComplete() const
    {
        return field == finishField;
    }

    int CalculateManhattan() const 
    {
        int distance = 0;
        for (int i = 0; i < FIELD_SIZE; ++i) 
        {
            if (field[i] != 0) 
            {
                int targetX = (field[i] - 1) / SIZE;
                int targetY = (field[i] - 1) % SIZE;
                int currentX = i / SIZE;
                int currentY = i % SIZE;
                distance += std::abs(targetX - currentX) + std::abs(targetY - currentY);
            }
        }
        return distance;
    }

    bool CanMoveLeft() const
    {
        return emptyPos % SIZE != SIZE - 1;
    }

    bool CanMoveRight() const
    {
        return emptyPos % SIZE != 0;
    }

    bool CanMoveUp() const
    {
        return emptyPos < SIZE * (SIZE - 1);
    }

    bool CanMoveDown() const
    {
        return emptyPos > SIZE - 1;
    }

    GameState MoveLeft() const
    {
        assert(CanMoveLeft());
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos + 1]);
        newState.emptyPos++;
        return newState;
    }

    GameState MoveRight() const
    {
        assert(CanMoveRight());
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos - 1]);
        newState.emptyPos--;
        return newState;
    }

    GameState MoveUp() const
    {
        assert(CanMoveUp());
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos + 4]);
        newState.emptyPos += 4;
        return newState;
    }

    GameState MoveDown() const
    {
        assert(CanMoveDown());
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos - 4]);
        newState.emptyPos -= 4;
        return newState;
    }

    bool operator==(const GameState& other) const
    {
        return field == other.field;
    }
    
    bool operator<(const GameState &other) const
    {
        return field < other.field;
    }

private:
    std::array<char, FIELD_SIZE> field;
    int emptyPos;

    friend struct GameStateHasher;
};

struct GameStateHasher
{
    size_t operator()(const GameState& state) const
    {
        size_t hash = 0;
        for (const auto& val : state.field)
        {
            hash = hash * 31 + val;
        }
        return hash;
    }
};

std::string GetSolution(const std::array<char, FIELD_SIZE>& field)
{
    GameState startState(field);

    if (startState.IsComplete()) return "0";

    std::unordered_map<GameState, char, GameStateHasher> visited;
    visited[startState] = 'S';

    std::priority_queue<std::pair<int, GameState>> queue;
    queue.push({-startState.CalculateManhattan(), startState});

    while (!queue.empty())
    {
        GameState state = queue.top().second;
        queue.pop();

        if (state.IsComplete())
        {
            break;
        }

        if (state.CanMoveLeft())
        {
            GameState newState = state.MoveLeft();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'L';
                queue.push({-newState.CalculateManhattan(), newState});
            }
        }


        if (state.CanMoveRight())
        {
            GameState newState = state.MoveRight();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'R';
                queue.push({-newState.CalculateManhattan(), newState});
            }
        }

        if (state.CanMoveUp())
        {
            GameState newState = state.MoveUp();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'U';
                queue.push({-newState.CalculateManhattan(), newState});
            }
        }

        if (state.CanMoveDown())
        {
            GameState newState = state.MoveDown();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'D';
                queue.push({-newState.CalculateManhattan(), newState});
            }
        }
    }

    std::string path;
    GameState state(finishField);

    while (visited[state] != 'S')
    {
        char move = visited[state];
        switch (move)
        {
        case 'L':
            state = state.MoveRight();
            path += 'L';
            break;
        case 'R':
            state = state.MoveLeft();
            path += 'R';
            break;
        case 'D':
            state = state.MoveUp();
            path += 'D';
            break;
        case 'U':
            state = state.MoveDown();
            path += 'U';
            break;
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

int main()
{
    std::array<char, FIELD_SIZE> field;
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        int puzzle;
        std::cin >> puzzle;
        field[i] = puzzle;
    }

    std::string path = GetSolution(field);
    std::cout << path.length() << '\n' << path << std::endl;
    return 0;
}
