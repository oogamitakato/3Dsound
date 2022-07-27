#include "Astar.h"
#include <math.h>


// �R�X�g������
void InitCost(int heuristic_cost, int total_cost)
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Map[y][x].HeuristicCost = heuristic_cost;
			Map[y][x].TotalCost = total_cost;
		}
	}
}

// �Z����r
bool IsEqualCell(const Cell& a, const Cell& b)
{
	if (a.X == b.X &&
		a.Y == b.Y)
	{
		return true;
	}

	return false;
}


// �Z���͈̓`�F�b�N�֐�
bool IsCellWithinTheRange(int x, int y)
{
	if (x >= 0 &&
		x < MapWidth &&
		y >= 0 &&
		y < MapHeight)
	{
		return true;
	}

	return false;
}

// �����\�[�g�p�֐�
bool Less(Node* a, Node* b)
{
	if (a->TotalCost < b->TotalCost)
	{
		return true;
	}

	return false;
}

// �I�[�v�����X�g�ɒǉ�
bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost)
{
	bool can_update = true;

	std::list<Node*> node_list[] =
	{
		close_list,
		open_list
	};

	for (std::list<Node*>& list : node_list)
	{
		// ���X�g�ɓ����m�[�h�������ă��X�g�̕��̃R�X�g�������Ȃ�폜
		if (EraseNode(list, adjacent_node, cost) == EraseResult::CouldntErased)
		{
			can_update = false;
		}
	}

	if (can_update == true)
	{
		open_list.push_back(adjacent_node);
		return true;
	}

	return false;
}

// �q���[���X�e�B�N�X�R�X�g�v�Z
float CalculateHeuristic(const Node* node, const Node* Goal)
{
	float x = fabsf(float(Goal->Position.X - node->Position.X));
	float y = fabsf(float(Goal->Position.Y - node->Position.Y));

	return sqrtf(x * x + y * y);
}

EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost)
{
	// �N���[�Y���X�g�`�F�b�N
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// �m�[�h�Ɠ����Z�������邩���ׂ�
		if (IsEqualCell(new_node->Position, (*itr)->Position) == true)
		{
			// �R�X�g�̔�r
			if (new_cost < (*itr)->TotalCost)
			{
				list.erase(itr);
				return EraseResult::Erased;
			}
			else
			{
				return EraseResult::CouldntErased;
			}
		}
	}

	return EraseResult::NotFound;
}


// �m�[�h�̍쐬
void CreateMap()
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Map[y][x].Position.X = x;
			Map[y][x].Position.Y = y;

			Cell adjacent_cells[] =
			{
				Cell{x, y - 1},
				Cell{x - 1, y },
				Cell{x + 1, y},
				Cell{x, y + 1 },
			};

			// �אڃm�[�h�̒ǉ�
			for (const Cell& cell : adjacent_cells)
			{
				if (IsCellWithinTheRange(cell.X, cell.Y) == true &&
					CostTable[cell.Y][cell.X] == 1)
				{
					Map[y][x].AdjacentNodes.push_back(&Map[cell.Y][cell.X]);
				}
			}
		}
	}
}

void AStar(Cell start, Cell goal, Object obj)
{
	std::list<Node*> open_list;
	std::list<Node*> close_list;

	const Node* start_node = &Map[start.X][start.Y];
	const Node* goal_node = &Map[goal.X][goal.Y];

	//�X�V�����m�[�h�ʒu�ۑ��p
	Cell last_update_cells[MapHeight][MapWidth];

	//�O���t�̏�����
	InitCost(Infinity, 0);

	//�X�^�[�g�m�[�h�̎w��
	open_list.push_back(&Map[start.Y][start.X]);

	//�o�H�T����
	count = 0;

	//���[�g�m�肵����̃S�[���ɂ��ǂ蒅���܂ł̉�
	goal_count = 0;

	//�I�[�v�����X�g���Ȃ��Ȃ�܂ŉ�
	while (open_list.empty() == false)
	{
		count++;

		//�m�[�h�擾
		Node* search_node = (*open_list.begin());

		//�T�����X�g���珜�O
		open_list.erase(open_list.begin());

		//�S�[���ɓ��B������I���
		if (IsEqualCell(search_node->Position, goal) == true)
		{
			// �N���[�Y���X�g�ɍŌ�̃m�[�h��ǉ�����
			close_list.push_back(search_node);
			break;
		}

		for (Node* adjacent_node : search_node->AdjacentNodes)
		{
			//�v�Z���s���Ă��Ȃ������ꍇ�����v�Z
			if (adjacent_node->HeuristicCost == Infinity)
			{
				// �q���[���X�e�B�N�X�R�X�g�v�Z
				adjacent_node->HeuristicCost = CalculateHeuristic(adjacent_node, goal_node);
			}

			//�m�[�h�ԃR�X�g
			float edge_cost = CostTable[adjacent_node->Position.Y][adjacent_node->Position.X];
			//�擾�m�[�h�̃g�[�^���X�R�A
			float node_cost = search_node->TotalCost;

			/*
				�g�[�^���R�X�g�Z�o
					�m�[�h�ԃR�X�g + �q���[���X�e�B�b�N�R�X�g + �擾�m�[�h�̃g�[�^���R�X�g
			*/
			float total_cost = edge_cost + adjacent_node->HeuristicCost + node_cost;

			//�m�[�h�ǉ�
			if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost) == true)
			{
				// �g�[�^���R�X�g���X�V
				adjacent_node->TotalCost = total_cost;

				if (adjacent_node->Position.Y == 0 && adjacent_node->Position.X == 2)
				{
					int xx = 0;
					xx = 100;
				}

				// �o�H���X�V�����Z����ۑ�
				last_update_cells[adjacent_node->Position.Y][adjacent_node->Position.X] = search_node->Position;
			}
		}

		bool is_add_close = true;

		//�N���[�Y���X�g�`�F�b�N
		for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
		{
			//�m�[�h�Ɠ����Z�������邩���ׂ�
			if (IsEqualCell(search_node->Position, (*itr)->Position) == true)
			{
				is_add_close = false;
				break;
			}
		}

		//�����m�[�h���Ȃ������̂Œǉ�
		if (is_add_close == true)
		{
			//���̃m�[�h�̒T���I��
			close_list.push_back(search_node);
		}

		//�����\�[�g
		open_list.sort(Less);
	}

	// �o�H����
	std::list<Cell> route_list;

	// �S�[���Z�����畜������
	route_list.push_back(goal);
	while (route_list.empty() == false)
	{
		Cell route = route_list.front();

		// �X�^�[�g�ʒu�Ȃ�I��
		if (IsEqualCell(route, start) == true)
		{
			// ���������o�H��\��
			for (Cell& cell : route_list)
			{
				//DrawFormatString(0, goal_count * 20, GetColor(255, 255, 255), "x = %d y = %d", cell.X, cell.Y);
				goal_count++;
			}

			break;
		}
		else
		{
			if (IsCellWithinTheRange(route.X, route.Y) == true)
			{
				// �ǉ�
				route_list.push_front(last_update_cells[route.Y][route.X]);
			}
			else
			{

				break;
			}
		}
	}

	//goal_count�̐��ɉ����ĉ��ʂ�������
	if (goal_count > 0)
	{
		obj.volume = (obj.maxVolume - goal_count * 10) + leakingVolume;
	}
	else
	{
		obj.volume = leakingVolume;
	}

	ChangeVolumeSoundMem(obj.volume, obj.sound);
	//DrawFormatString(0, 390, GetColor(255, 255, 255), "����:%d", obj.volume);
}

void AStarDraw(Cell start, Cell goal, Object obj)
{
	DrawFormatString(0, 350, GetColor(255, 255, 255), "�T���� = %d\n", count);
	DrawFormatString(0, 370, GetColor(255, 255, 255), "�S�[���܂ł̃u���b�N�� = %d\n", goal_count);
}
