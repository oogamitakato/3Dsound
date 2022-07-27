#pragma once
#pragma once
#include "DxLib.h"
#include "Object.h"
#include <list>
#include <stdio.h>
#include <memory.h>
#include <queue>
#include <vector>


const int MapHeight = 20;
const int MapWidth = 20;
const int Infinity = 100000;

// 削除結果
enum EraseResult
{
	NotFound,		// 未発見
	Erased,			// 削除
	CouldntErased	// 削除できない
};

typedef struct Cell {

	Cell() :
		X(-1),
		Y(-1)
	{
	}

	Cell(int x, int y)
	{
		X = x;
		Y = y;
	}

	int X;		// 列
	int Y;		// 行
};

// ノード
struct Node
{
	Node() :
		Node(0, 0)
	{
	}

	Node(int x, int y) :
		Position(x, y),
		HeuristicCost(Infinity),
		TotalCost(0)
	{
		AdjacentNodes.clear();
	}

	Cell Position;		// ノード座標
	std::vector<Node*> AdjacentNodes;	// 隣接ノード(辺)
	float HeuristicCost;	// ヒューリスティックコスト
	float TotalCost;	// コスト(ヒューリスティックコスト込み)
};

static int CostTable[MapHeight][MapWidth] =
{
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,0,0,0,1,0,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,0,1,0,1,0,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	                                         //
	0,1,0,1,0,1,0,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,0,1,0,1,0,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,0,1,1,1,0,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
                                             //
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
                                             //
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
};

static Node Map[MapHeight][MapWidth];

//経路探索回数
static int count = 0;

static int goal_count;

//音が壁からどのくらい漏れるか
static int leakingVolume = 10;

// コスト初期化
void InitCost(int heuristic_cost, int total_cost);

bool IsEqualCell(const Cell& a, const Cell& b);

bool IsCellWithinTheRange(int routeX, int routeY);

// 昇順ソート用関数
bool Less(Node* a, Node* b);

// オープンリストに追加
bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost);

// ヒューリスティクスコスト計算
float CalculateHeuristic(const Node* node, const Node* Goal);

EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost);

// ノードの作成
void CreateMap();

void AStar(Cell start, Cell goal, Object obj);
void AStarDraw(Cell start, Cell goal, Object obj);