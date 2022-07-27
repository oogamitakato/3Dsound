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

// �폜����
enum EraseResult
{
	NotFound,		// ������
	Erased,			// �폜
	CouldntErased	// �폜�ł��Ȃ�
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

	int X;		// ��
	int Y;		// �s
};

// �m�[�h
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

	Cell Position;		// �m�[�h���W
	std::vector<Node*> AdjacentNodes;	// �אڃm�[�h(��)
	float HeuristicCost;	// �q���[���X�e�B�b�N�R�X�g
	float TotalCost;	// �R�X�g(�q���[���X�e�B�b�N�R�X�g����)
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

//�o�H�T����
static int count = 0;

static int goal_count;

//�����ǂ���ǂ̂��炢�R��邩
static int leakingVolume = 10;

// �R�X�g������
void InitCost(int heuristic_cost, int total_cost);

bool IsEqualCell(const Cell& a, const Cell& b);

bool IsCellWithinTheRange(int routeX, int routeY);

// �����\�[�g�p�֐�
bool Less(Node* a, Node* b);

// �I�[�v�����X�g�ɒǉ�
bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost);

// �q���[���X�e�B�N�X�R�X�g�v�Z
float CalculateHeuristic(const Node* node, const Node* Goal);

EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost);

// �m�[�h�̍쐬
void CreateMap();

void AStar(Cell start, Cell goal, Object obj);
void AStarDraw(Cell start, Cell goal, Object obj);