#include "Astar.h"
#include <math.h>


// コスト初期化
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

// セル比較
bool IsEqualCell(const Cell& a, const Cell& b)
{
	if (a.X == b.X &&
		a.Y == b.Y)
	{
		return true;
	}

	return false;
}


// セル範囲チェック関数
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

// 昇順ソート用関数
bool Less(Node* a, Node* b)
{
	if (a->TotalCost < b->TotalCost)
	{
		return true;
	}

	return false;
}

// オープンリストに追加
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
		// リストに同じノードがあってリストの方のコストが高いなら削除
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

// ヒューリスティクスコスト計算
float CalculateHeuristic(const Node* node, const Node* Goal)
{
	float x = fabsf(float(Goal->Position.X - node->Position.X));
	float y = fabsf(float(Goal->Position.Y - node->Position.Y));

	return sqrtf(x * x + y * y);
}

EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost)
{
	// クローズリストチェック
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// ノードと同じセルがあるか調べる
		if (IsEqualCell(new_node->Position, (*itr)->Position) == true)
		{
			// コストの比較
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


// ノードの作成
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

			// 隣接ノードの追加
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

	//更新したノード位置保存用
	Cell last_update_cells[MapHeight][MapWidth];

	//グラフの初期化
	InitCost(Infinity, 0);

	//スタートノードの指定
	open_list.push_back(&Map[start.Y][start.X]);

	//経路探索回数
	count = 0;

	//ルート確定した後のゴールにたどり着くまでの回数
	goal_count = 0;

	//オープンリストがなくなるまで回す
	while (open_list.empty() == false)
	{
		count++;

		//ノード取得
		Node* search_node = (*open_list.begin());

		//探索リストから除外
		open_list.erase(open_list.begin());

		//ゴールに到達したら終わり
		if (IsEqualCell(search_node->Position, goal) == true)
		{
			// クローズリストに最後のノードを追加する
			close_list.push_back(search_node);
			break;
		}

		for (Node* adjacent_node : search_node->AdjacentNodes)
		{
			//計算を行っていなかった場合だけ計算
			if (adjacent_node->HeuristicCost == Infinity)
			{
				// ヒューリスティクスコスト計算
				adjacent_node->HeuristicCost = CalculateHeuristic(adjacent_node, goal_node);
			}

			//ノード間コスト
			float edge_cost = CostTable[adjacent_node->Position.Y][adjacent_node->Position.X];
			//取得ノードのトータルスコア
			float node_cost = search_node->TotalCost;

			/*
				トータルコスト算出
					ノード間コスト + ヒューリスティックコスト + 取得ノードのトータルコスト
			*/
			float total_cost = edge_cost + adjacent_node->HeuristicCost + node_cost;

			//ノード追加
			if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost) == true)
			{
				// トータルコストを更新
				adjacent_node->TotalCost = total_cost;

				if (adjacent_node->Position.Y == 0 && adjacent_node->Position.X == 2)
				{
					int xx = 0;
					xx = 100;
				}

				// 経路を更新したセルを保存
				last_update_cells[adjacent_node->Position.Y][adjacent_node->Position.X] = search_node->Position;
			}
		}

		bool is_add_close = true;

		//クローズリストチェック
		for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
		{
			//ノードと同じセルがあるか調べる
			if (IsEqualCell(search_node->Position, (*itr)->Position) == true)
			{
				is_add_close = false;
				break;
			}
		}

		//同じノードがなかったので追加
		if (is_add_close == true)
		{
			//このノードの探索終了
			close_list.push_back(search_node);
		}

		//昇順ソート
		open_list.sort(Less);
	}

	// 経路復元
	std::list<Cell> route_list;

	// ゴールセルから復元する
	route_list.push_back(goal);
	while (route_list.empty() == false)
	{
		Cell route = route_list.front();

		// スタート位置なら終了
		if (IsEqualCell(route, start) == true)
		{
			// 復元した経路を表示
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
				// 追加
				route_list.push_front(last_update_cells[route.Y][route.X]);
			}
			else
			{

				break;
			}
		}
	}

	//goal_countの数に応じて音量を下げる
	if (goal_count > 0)
	{
		obj.volume = (obj.maxVolume - goal_count * 10) + leakingVolume;
	}
	else
	{
		obj.volume = leakingVolume;
	}

	ChangeVolumeSoundMem(obj.volume, obj.sound);
	//DrawFormatString(0, 390, GetColor(255, 255, 255), "音量:%d", obj.volume);
}

void AStarDraw(Cell start, Cell goal, Object obj)
{
	DrawFormatString(0, 350, GetColor(255, 255, 255), "探索回数 = %d\n", count);
	DrawFormatString(0, 370, GetColor(255, 255, 255), "ゴールまでのブロック数 = %d\n", goal_count);
}
