#include <stdio.h>
#include <stack>
#include <fstream>
#include <vector>
#include <iostream>
#include <ncurses.h>
#define M_ROWS 41
#define M_COLS 121
struct Node
{
    Node()
    {
    }
    Node(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Node *root = nullptr;
    int x, y;
};
struct Tile
{
    bool visited = false;
    char e;
};

static Tile map[M_ROWS][M_COLS];
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

bool load_map(const std::string path)
{
    std::ifstream fs(path);
    if (!fs.is_open())
        return false;
    int i = 0;
    while (!fs.eof())
    {
        std::string line;
        std::getline(fs, line);
        for (size_t j = 0; j < line.size(); j++)
        {
            map[i][j].e = line[j];
        }
        i++;
    }
    fs.close();
    return true;
}
void draw_map()
{
    for (int i = 0; i < M_ROWS; i++)
    {
        for (int j = 0; j < M_COLS; j++)
        {
            auto e = map[i][j].e;
            if (e == '#')
            {
                attron(COLOR_PAIR(1));
                mvaddch(i, j, e);
                attroff(COLOR_PAIR(1));
            }
            else
            {
                attron(COLOR_PAIR(3));
                mvaddch(i, j, e);
                attroff(COLOR_PAIR(3));
            }
        }
    }
}
std::vector<Node *> getNeighbours(Node *node)
{
    std::vector<Node *> neighbours;
    int x = node->x;
    int y = node->y;
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if ((i != y && j != x) || i < 0 || i >= M_ROWS || j < 0 || j >= M_COLS)
            {
                continue;
            }
            else if (!map[i][j].visited && map[i][j].e != '#')
            {
                neighbours.push_back(new Node(j, i));
                neighbours[neighbours.size() - 1]->root = node;
            }
        }
    }
    return neighbours;
}
void traverse(Node *node)
{
    if (node != nullptr)
    {
        traverse(node->root);
        clear();
        draw_map();
        attron(COLOR_PAIR(2));
        map[node->y][node->x].e = '.';
        mvaddch(node->y, node->x, '@');
        attroff(COLOR_PAIR(2));
        refresh();
        msleep(16);
    }
}
void dfs()
{
    std::stack<Node *> open_list;
    open_list.push(new Node(30, 1));
    Node *sol = nullptr;
    bool found = false;
    while (!open_list.empty())
    {
        auto curr = open_list.top();
        open_list.pop();
        if (curr->y == 40 && curr->x == 119)
        {
            found = true;
            break;
        }
        map[curr->y][curr->x].visited = true;
        auto neighbours = getNeighbours(curr);
        for (size_t i = 0; i < neighbours.size(); i++)
        {
            auto child = neighbours[i];
            if (!map[child->y][child->x].visited)
            {
                if (child->y == 40 && child->x == 119)
                {
                    sol = child;
                    found = false;
                    break;
                }
                else
                    open_list.push(neighbours[i]);
            }
        }
    }
    if (found)
        traverse(sol);
}
int main()
{
    if (load_map("/home/isai/map.txt"))
    {
        initscr();
        start_color();
        noecho();
        keypad(stdscr, true);
        nodelay(stdscr, true);
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
        curs_set(false);
        dfs();
        getchar();
        endwin();
    }
    else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
